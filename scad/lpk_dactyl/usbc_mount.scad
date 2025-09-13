
_plugWallThickness = 0.75;
_plugLength = 13;
_plugWidth = 6;
_plugDepth = 3;

_plugCutoutLength = _plugLength - _plugWallThickness*2;
_plugCutoutWidth = _plugWidth - _plugWallThickness*2;
_plugCutoutDepth = _plugDepth + 2;

_capBrimThickness = 1;
_capLength = _plugLength + _capBrimThickness*2;
_capWidth = _plugWidth + _capBrimThickness*2;
_capDepth = 1.5;

_usbcPlugDiameter = 3.4;
_usbcPlugLength = 9.75;

///MAIN START///

cap();

///MAIN END///

module cap()
{
    difference()
    {
        union()
        {
            difference()
            {
                cube([_plugLength, _plugWidth, _plugDepth]);
                translate([_plugWallThickness, _plugWallThickness, -1])
                cube([_plugCutoutLength, _plugCutoutWidth, _plugCutoutDepth]);
            }
            translate([-_capBrimThickness, -_capBrimThickness, _plugDepth])
            roundedCube(size=[_capLength,_capWidth,_capDepth], apply_to="zmax");
        }

        translate([(_plugLength-_usbcPlugLength), _plugWidth/2, _plugDepth-1])
        usbcPunch(_capDepth+2);
    }
}

//Punches
module usbcPunch(depth)
{
    hull()
    {
        cylinder(d=_usbcPlugDiameter, h=depth, $fn=100);
        translate([_usbcPlugLength-_usbcPlugDiameter, 0, 0])
        cylinder(d=_usbcPlugDiameter, h=depth, $fn=100);
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
