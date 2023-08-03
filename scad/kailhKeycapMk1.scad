//Constants
KEY_1U_MODIFIER = 1;
KEY_1_25U_MODIFIER = 1.25;

//Variables
_switchLength = 15;
_switchWidth = 15;

_switchPaddingLength = 2.25;
_switchPaddingWidth = 2.25;

_kailhKeyCapDepth = 2.5;

_key1uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1uWidth = (_switchWidth*KEY_1U_MODIFIER)+(_switchPaddingWidth*2);
_key1_25uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1_25uWidth = (_switchWidth*KEY_1_25U_MODIFIER)+(_switchPaddingWidth*2);

_keyCapSpacingOffset = 0.5;
_keyCapWallThickness = 2;
_keyCapRoundingRadius = 3;

_keyCap1uLength = _key1uLength - _keyCapSpacingOffset;
_keyCap1uWidth = _key1uWidth - _keyCapSpacingOffset;
_keyCap1_25uLength = _key1_25uLength - _keyCapSpacingOffset;
_keyCap1_25uWidth = _key1_25uWidth - _keyCapSpacingOffset;

_capInterfaceShankCenterToCenter = 6.25;


/// MAIN START ///

kailhKeyCapTop(_key1uLength, _key1uWidth, _kailhKeyCapDepth);
//kailhKeyCapTop(_key1_25uWidth, _key1uWidth, _kailhKeyCapDepth);
//kailhKeycapShank();

/// MAIN END ///


//Bodies
module kailhKeyCapTop(length, width, depth)
{
    shankInterfaceWidth = 3.3;
    shankInterfaceCutoutDepth = 1.5;
    shankInterfaceLength = 1.9;
    totalCapInterfaceLength = _capInterfaceShankCenterToCenter+shankInterfaceLength;

    difference()
    {
        union()
        {
            difference()
            {
                baseCapDepth = 20;
                // Form the base cap
                difference()
                {
                    roundedCube(size=[length, width, baseCapDepth], radius = _keyCapRoundingRadius, apply_to="zmin");
                    cutoutCubeSize = [length-(_keyCapWallThickness*2), width-(_keyCapWallThickness*2), baseCapDepth];
                    translate([_keyCapWallThickness, _keyCapWallThickness, _keyCapWallThickness])
                        roundedCube(size=cutoutCubeSize, radius = _keyCapRoundingRadius, apply_to="zmin");
                }
                // Cut to the desired depth
                translate([-1,-1,depth])
                    cube([length+2,width+2, baseCapDepth]);
            }

            // Bar to thicken shank interface area
            thickeningBarLengthPadding = 3;
            thickeningBarWidthPadding = 6;
            thickeningBarLength = length-thickeningBarLengthPadding*2;
            thickeningBarWidth = width-thickeningBarWidthPadding*2;
            roundedCubeDepthAdjustment = 0.1;
            translate([(length-thickeningBarLength)/2, (width-thickeningBarWidth)/2, roundedCubeDepthAdjustment])
                cube([thickeningBarLength, thickeningBarWidth, depth-roundedCubeDepthAdjustment]);
        }

        // Cut out the interface for the shank
        translate([(length-totalCapInterfaceLength)/2,(width-shankInterfaceWidth)/2, depth-shankInterfaceCutoutDepth])
            union()
            {
                cube([shankInterfaceLength,shankInterfaceWidth,shankInterfaceCutoutDepth+1]);
                translate([_capInterfaceShankCenterToCenter,0,0])
                    cube([shankInterfaceLength,shankInterfaceWidth,shankInterfaceCutoutDepth+1]);
            }
    }
}

module kailhKeycapShank()
{
    // Note: This is setting that might have to be tweaked depending
    // on the printer's resolution. Lower the number for tighter gaps.
    printingGapTolerance = 0.05;

    switchInterfaceShankLength = 4.25;
    switchInterfaceShankWidth = 1.20 - printingGapTolerance;
    switchInterfaceShankDepth = 3 - printingGapTolerance;
    switchInterfaceShankCenterToCenter = 5.70;
    capInterfaceShankLength = 1.5;
    capInterfaceShankWidth = 1.5-printingGapTolerance;
    capInterfaceShankDepth = switchInterfaceShankDepth-printingGapTolerance;
    shankInterfaceConnectorLength = 1.25;
    shankInterfaceConnectorWidth = 12;
    shankInterfaceConnectorDepth = switchInterfaceShankDepth;

    union()
    {
        //Cap interface
        translate([0,0,0])
            cube([capInterfaceShankLength, capInterfaceShankWidth, capInterfaceShankDepth]);
        translate([0,_capInterfaceShankCenterToCenter,0])
            cube([capInterfaceShankLength, capInterfaceShankWidth, capInterfaceShankDepth]);

        //Interface connector
        shankInterfaceCenteringWidth = ((_capInterfaceShankCenterToCenter+capInterfaceShankWidth)-shankInterfaceConnectorWidth)/2;
        translate([capInterfaceShankLength,shankInterfaceCenteringWidth,0])
            cube([shankInterfaceConnectorLength, shankInterfaceConnectorWidth, shankInterfaceConnectorDepth]);

        //Switch interface
        centeringWidth = ((shankInterfaceConnectorWidth-(switchInterfaceShankCenterToCenter+switchInterfaceShankWidth))/2)+shankInterfaceCenteringWidth;
        translate([0,centeringWidth,0])
        {
            translate([capInterfaceShankLength+shankInterfaceConnectorLength,0,0])
                cube([switchInterfaceShankLength, switchInterfaceShankWidth, switchInterfaceShankDepth]);
            translate([capInterfaceShankLength+shankInterfaceConnectorLength, switchInterfaceShankCenterToCenter,0])
                cube([switchInterfaceShankLength, switchInterfaceShankWidth, switchInterfaceShankDepth]);
        }
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

