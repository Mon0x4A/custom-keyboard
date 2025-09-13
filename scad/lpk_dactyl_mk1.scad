
KEY_1U_MODIFIER = 1;
KEY_1_25U_MODIFIER = 1.25;

_backplateDepth = 3;
_housingWallThickness = 2.85;
_roundingRadius = 1.25;

_keySwitchCutoutLength = 13.86;
_keySwitchCutoutWidth = 13.86;
_switchLength = 15;
_switchWidth = 15;
_switchPaddingLength = 2.25;
_switchPaddingWidth = 2.25;

_key1uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1uWidth = (_switchWidth*KEY_1U_MODIFIER)+(_switchPaddingWidth*2);
_key1_25uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1_25uWidth = (_switchWidth*KEY_1_25U_MODIFIER)+(_switchPaddingWidth*2);

_columnPadding = 1;

_homeIndexDepth = 15;

_baseLength = 80;
_baseWidth = 51.25;
_baseDepth = _homeIndexDepth;

/// MAIN START ///
keyboard();
/// MAIN END ///

//Bodies
module keyboard()
{
    union()
    {
        keyboardPad();
        translate([-21, 8.5, 0])
            keyboardBase();
    }
}

module keyboardBase()
{
    union()
    {
        //cube([_baseLength, _baseWidth, _baseDepth]);
        roundedCube(size = [_baseLength, _baseWidth, _baseDepth], radius=_roundingRadius, apply_to="zmax");
    }
}

module keyboardPad()
{
    translate([13,-_key1uWidth-_columnPadding-1,51])
    rotate([0, -40, 0])
    union()
    {
        translate([0, 0, 0])
        keyUnit(_key1uLength, _key1uWidth, _key1uWidth, 0, 0);
        translate([-_key1uLength-_columnPadding, _key1uWidth*-0.25, 0])
        keyUnit(_key1uLength, _key1uWidth, _key1uWidth, 0, 0);
    }


    translate([0, 0, 65])
    rotate([0, 50, 0])
    union()
    {
        translate([(_key1uLength+_columnPadding)*0, 0, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, -20, 0);
        translate([(_key1uLength+_columnPadding)*0, _key1uWidth, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 0, 0);
        translate([(_key1uLength+_columnPadding)*0, _key1uWidth*2, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 20, 0);

        translate([(_key1uLength+_columnPadding)*1, _key1uWidth*1.5, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 0, 0);
        translate([(_key1uLength+_columnPadding)*1, _key1uWidth*2.5, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 20, 0);

        translate([(_key1uLength+_columnPadding)*2, _key1uWidth*1.25, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 0, 0);

        translate([(_key1uLength+_columnPadding)*3, _key1uWidth*2, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 20, 0); //TODO YROT
        translate([(_key1uLength+_columnPadding)*3, _key1uWidth*0.5, 0])
        keyUnit(_key1uLength, _key1uWidth, _homeIndexDepth, 0, 0);
    }
}

module keyUnit(length, width, depth, rotX, rotY)
{
    trigDepthDelta = abs(((width*sin(rotX))/sin(90-rotY)));
    translate([0, rotX > 0 ? 2*sin(rotX) : -2*sin(rotX), depth+(rotX > 0 ? 0 : trigDepthDelta)])
        rotate([rotX, rotY, 0])
            keyFace(_key1uLength, _key1uWidth, _backplateDepth);

    keyStand(_key1uLength, _key1uWidth, depth, _housingWallThickness, rotX, rotY,0);
}

module keyFace(length, width, depth)
{
    difference()
    {
        roundedCube(size = [length, width, depth], radius=_roundingRadius, apply_to="zmax");

        translate([length/2, width/2, -1]) //forward to final position
            translate([-_keySwitchCutoutLength/2, -_keySwitchCutoutWidth/2, 0]) //back to origin
                cube([_keySwitchCutoutLength, _keySwitchCutoutWidth, depth+2]);
    }
}

module keyStand(length, width, depth, wallThickness, rotX, rotY, rotZ)
{
    $fn=100;
    trigDepthDelta = abs(((width*sin(rotX))/sin(90-rotY)));
    totalDepth = depth + trigDepthDelta;
    difference()
    {
        linear_extrude(totalDepth)
            difference()
            {
                minkowski()
                {
                    square(length, width);
                    circle(r=_roundingRadius);
                }

                translate([wallThickness, wallThickness, 0])
                    square(length-(wallThickness*2), width-(wallThickness*2));
            }

        translate([-wallThickness, -wallThickness, depth + (rotX > 0 ? 0 : trigDepthDelta+2)])
        rotate([rotX, 0, 0])
        cube([length+(wallThickness*2), width+(wallThickness*2), 100]);
    }

}

//Utility
/// Builds a cube with rounded corners
/// size - dimension vector
/// center - centered on xyz planes?
/// radius - rounding radius
/// apply_to - which sides to round
module roundedCube(size = [1, 1, 1], center = false, radius = 0.5, apply_to = "all")
{
    // If single value, convert to [x, y, z] vector
    size = (size[0] == undef) ? [size, size, size] : size;

    translate_min = radius;
    translate_xmax = size[0] - radius;
    translate_ymax = size[1] - radius;
    translate_zmax = size[2] - radius;

    diameter = radius * 2;

    obj_translate = (center == false) ?
        [0, 0, 0] : [
            -(size[0] / 2),
            -(size[1] / 2),
            -(size[2] / 2)
        ];

    translate(v = obj_translate) {
        hull() {
            for (translate_x = [translate_min, translate_xmax]) {
                x_at = (translate_x == translate_min) ? "min" : "max";
                for (translate_y = [translate_min, translate_ymax]) {
                    y_at = (translate_y == translate_min) ? "min" : "max";
                    for (translate_z = [translate_min, translate_zmax]) {
                        z_at = (translate_z == translate_min) ? "min" : "max";

                        translate(v = [translate_x, translate_y, translate_z])
                        if (
                            (apply_to == "all") ||
                            (apply_to == "xmin" && x_at == "min") || (apply_to == "xmax" && x_at == "max") ||
                            (apply_to == "ymin" && y_at == "min") || (apply_to == "ymax" && y_at == "max") ||
                            (apply_to == "zmin" && z_at == "min") || (apply_to == "zmax" && z_at == "max")
                        ) {
                            sphere(r = radius, $fn=20);
                        } else {
                            rotate =
                                (apply_to == "xmin" || apply_to == "xmax" || apply_to == "x") ? [0, 90, 0] : (
                                (apply_to == "ymin" || apply_to == "ymax" || apply_to == "y") ? [90, 90, 0] :
                                [0, 0, 0]
                            );
                            rotate(a = rotate)
                            cylinder(h = diameter, r = radius, center = true, $fn=20);
                        }
                    }
                }
            }
        }
    }
}
