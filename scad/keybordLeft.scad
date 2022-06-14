_m3BoltHoleDiameter = 3.2 + 0.2; // plus padding
_m3BoltHoleRadius = _m3BoltHoleDiameter/2;

_backplateRowCount = 6;
_backplateColumnCount = 8;

_switchLength = 15;
_switchWidth = 15;

_switchPaddingLength = 2;
_switchPaddingWidth = 2;

_key1uLength = _switchLength+(_switchPaddingLength*2);
_key1uWidth = _switchWidth+(_switchPaddingWidth*2);

_keyCapSpacingOffset = 0.5;
_keyCapDepth = 10;
_keyCapWallThickness = 2;
_keyCapRoundingRadius = 3;

_keyCapShankOffsetRiserLength = 7.2;
_keyCapShankOffsetRiserWidth = 4.8;
_keyCapShankOffsetTowardSwitch = 3;

_keyCap1uLength = _key1uLength - _keyCapSpacingOffset;
_keyCap1uWidth = _key1uWidth - _keyCapSpacingOffset;

_key2uLength = (_switchLength*2)+(_switchPaddingLength*4);
_key2uWidth = _switchWidth+(_switchPaddingWidth*2);

_keyCap2uLength = _key2uLength - _keyCapSpacingOffset;
_keyCap2uWidth = _key2uWidth - _keyCapSpacingOffset;

_backplateLength = (_key1uLength * _backplateColumnCount);
_backplateWidth = (_key1uWidth * _backplateRowCount);
_backplateDepth = 4;
_backplateRoundingRadius = 1.25;

_housingLengthPadding = 5;
_housingWidthPadding = 5;
_housingBodyDepth = 18;
_housingWallThickness = 5;
_housingLength = _backplateLength + (_housingLengthPadding*2);
_housingWidth = _backplateWidth + (_housingWidthPadding*2);

_arduinoMicroBodyLength = 19.2;

_riserBoltHeadCutoutDepth = 3;

/// MAIN START ///

echo(str("_key1uLength = ", _key1uLength));
echo(str("_key1uWidth = ", _key1uWidth));
echo(str("_key2uLength = ", _key2uLength));
echo(str("_key2uWidth = ", _key2uWidth));

//keyboard();
//backplate(includeBoltHoles=true);
//housing();
//arduinoMicroPunch();
keyCap1u();
//riserBoltPunch();
//backplateTest();

/// MAIN END ///

module keyboard()
{
    union()
    {
        translate([_housingLengthPadding, _housingWidthPadding, -7])
        {
            backplate(includeBoltHoles=true);
        }

        translate([0, 0, -_housingBodyDepth])
        {
            // housing();

            //Note: Comment this in to see the internal plate clearance
            translate([_housingLengthPadding, _housingWidthPadding,0])
                cube([_backplateLength, _backplateWidth, _housingWallThickness]);

            arduinoCenteringLength = (_housingLength - _arduinoMicroBodyLength)/2;
            translate([arduinoCenteringLength, _backplateWidth-36, _housingWallThickness-3])
            {
                scale([1, 1, 1])
                    arduinoMicroPunch();
            }
        }

    }
}

module housing()
{
    difference()
    //union()
    {
        difference()
        {
            housingBody();

            translate([_housingLengthPadding, _housingWidthPadding, _housingWallThickness])
            {
                roundedCube(size=[_backplateLength, _backplateWidth, _housingBodyDepth], radius=_backplateRoundingRadius, apply_to="zmax");
            }
        }

        arduinoCenteringLength = (_housingLength - _arduinoMicroBodyLength)/2;
        translate([arduinoCenteringLength, _backplateWidth-36, _housingWallThickness-3])
        {
            scale([1, 1, 1])
                arduinoMicroPunch();
        }
    }

}

module housingBody()
{
    union()
    {
        bodyLength = _backplateLength + (_housingLengthPadding*2);
        bodyWidth = _backplateWidth + (_housingWidthPadding*2);
        roundedCube(size = [bodyLength, bodyWidth, _housingBodyDepth], radius=4, apply_to="all");
    }
}

module backplate(includeBoltHoles)
{
    difference()
    //union()
    {
        plate();

        if (includeBoltHoles)
        {
            riserBoltPunchSet();
        }
    }
}

module plate()
{
    union()
    {
        backplateGrooveDepth = 1;
        roundedCube(size=[_backplateLength, _backplateWidth, _backplateDepth - backplateGrooveDepth], radius=_backplateRoundingRadius, apply_to="zmax");

        //[0,0] is the upper left corner of the keyboard.
        translate([0, _key1uWidth*5, 0])
            row0();
        translate([0, _key1uWidth*4, 0])
            row1();
        translate([0, _key1uWidth*3, 0])
            row2();
        translate([0, _key1uWidth*2, 0])
            row3();
        translate([0, _key1uWidth*1, 0])
            row4();
        translate([0, 0, 0])
            row5();
    }
}

module row0()
{
    union()
    {
        key1u();
        translate([(_key1uLength*1), 0, 0])
            key1u();
        translate([(_key1uLength*2), 0, 0])
            key1u();
        translate([(_key1uLength*3), 0, 0])
            key1u();
        translate([(_key1uLength*4), 0, 0])
            key1u();
        translate([(_key1uLength*5), 0, 0])
            key1u();
        translate([(_key1uLength*6), 0, 0])
            key1u();
        translate([(_key1uLength*7), 0, 0])
            key1u();
    }
}

module row1()
{
    row0();
}

module row2()
{
    union()
    {
        key2u();
        translate([(_key2uLength), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*2), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*3), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*4), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*5), 0, 0])
            key1u();
    }
}

module row3()
{
    row0();
}

module row4()
{
    row2();
}

module row5()
{
    union()
    {
        key2u();
        translate([(_key2uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength*1+_key1uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength*1+_key1uLength*2), 0, 0])
            key2u();
        translate([(_key2uLength*2+_key1uLength*2), 0, 0])
            key2u();
    }
}

module key1u()
{
    difference()
    //union()
    {
        //cube([_key1uLength, _key1uWidth, _backplateDepth]);
        roundedCube(size = [_key1uLength, _key1uWidth, _backplateDepth], radius=1.25, apply_to="zmax");

        translate([_key1uLength/2, _key1uWidth/2, _backplateDepth])
        {
            switchPunch();
        }
    }
}

module key2u()
{
    difference()
    //union()
    {
        //cube([_key2uLength, _key2uWidth, _backplateDepth]);
        roundedCube(size = [_key2uLength, _key2uWidth, _backplateDepth], radius=_backplateRoundingRadius, apply_to="zmax");

        translate([_key2uLength/2, _key2uWidth/2, _backplateDepth])
        {
            switchPunch();
        }
    }
}

module switchPunch()
{
    translate([0,0,13.15])
    {
        scale([1,1,1])
        {
            import("../resources/stl/switch_mx.stl");
        }
    }
}

module arduinoMicroPunch()
{
    arduinoMicroBodyLength = _arduinoMicroBodyLength;//19.2;
    arduinoMicroBodyWidth = 43;
    arduinoMicroBodyDepth = 3.9;

    miniUsbPortLength = 7.8;
    miniUsbPortWidth = 9.5 + 10; //plus an extention for hole punching
    miniUsbPortDepth = 4.5;
    miniUsbDepthCutInToBody = 2;

    miniUsbOnBoardWidth = 7;
    miniUsbPortOverhang = 2;

    union()
    {
        cube([arduinoMicroBodyLength, arduinoMicroBodyWidth, arduinoMicroBodyDepth]);

        translate([(arduinoMicroBodyLength-miniUsbPortLength)/2, arduinoMicroBodyWidth-(miniUsbOnBoardWidth), arduinoMicroBodyDepth-miniUsbDepthCutInToBody])
        {
            cube([miniUsbPortLength, miniUsbPortWidth, miniUsbPortDepth]);
        }
    }
}

module riserBoltPunchSet()
{
    // Center
    translate([_backplateLength/2, _backplateWidth/2, ])
        riserBoltPunch();

    //SW
    translate([(_key1uLength*2), (_key1uWidth*1), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //SE
    translate([(_key1uLength*6), (_key1uWidth*1), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //NE
    translate([(_key1uLength*6), (_key1uWidth*5), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //NW
    translate([(_key1uLength*2), (_key1uWidth*5), _riserBoltHeadCutoutDepth])
        riserBoltPunch();
}

module riserBoltPunch()
{
    union()
    {
        //Traditional bolt punch
        boltHeadCutoutRadius = 2;
        boltHeadCutoutDepth = 3;

        cylinder(r=boltHeadCutoutRadius, h=boltHeadCutoutDepth+1, $fn=100);

        threadedInsertRadius = 2.1;
        boltPunchDepth = _backplateDepth+1;
        translate([0,0,-boltPunchDepth])
                // Threaded insert "bolt" punch
               cylinder(r=1.15, h=boltPunchDepth+2, $fn=100);
        //     cylinder(r=_m3BoltHoleRadius, h=boltPunchDepth+1, $fn=100);

        

    }
}

module keyCap1u()
{
    union()
    {
        difference()
        //union()
        {
            roundedCube(size=[_keyCap1uLength, _keyCap1uWidth, _keyCapDepth], radius = _keyCapRoundingRadius, apply_to="zmin");

            cutoutCubeSize = [_keyCap1uLength-(_keyCapWallThickness*2), _keyCap1uWidth-(_keyCapWallThickness*2), _keyCapDepth];
            translate([_keyCapWallThickness, _keyCapWallThickness, _keyCapWallThickness])
                roundedCube(size=cutoutCubeSize, radius = _keyCapRoundingRadius, apply_to="zmin");
        }

        //shank connector
        translate([_keyCap1uLength/2, _keyCap1uWidth/2, _keyCapWallThickness])
        {
            union()
            {
                // translate([0,0,_keyCapShankOffsetTowardSwitch])
                //     scale([1,1,1])
                //         translate([0, 0, -1.5]) // Get to origin.
                //             import("../resources/stl/cap-shank.stl");

                // Shank
                translate([-_keyCapShankOffsetRiserLength/2, -_keyCapShankOffsetRiserWidth/2, 0])
                {
                    translate([0,0,_keyCapShankOffsetTowardSwitch])
                        difference()
                        //union()
                        {
                            shankConnectorDepth = 3.8;
                            roundedCube(size=[_keyCapShankOffsetRiserLength, _keyCapShankOffsetRiserWidth, shankConnectorDepth], radius=0.4, apply_to="none");

                            //crossPunch
                            crossPunchFinLength = 4.5;
                            crossPunchFinWidth = 1.32;
                            crossPunchFinAdditionalCut = 2;

                            translate([_keyCapShankOffsetRiserLength/2, _keyCapShankOffsetRiserWidth/2, -1])
                                union()
                                {
                                    translate([-crossPunchFinLength/2, -crossPunchFinWidth/2, 0])
                                        roundedCube(size=[crossPunchFinLength, crossPunchFinWidth, shankConnectorDepth+2], radius=0.25, apply_to="none");
                                    rotate([0,0,90])
                                        translate([-(crossPunchFinLength+crossPunchFinAdditionalCut)/2, -crossPunchFinWidth/2, 0])
                                            roundedCube(size=[crossPunchFinLength+crossPunchFinAdditionalCut, crossPunchFinWidth, shankConnectorDepth+2], radius=0.25, apply_to="none");
                                }
                        }

                    roundedCube(size=[_keyCapShankOffsetRiserLength, _keyCapShankOffsetRiserWidth, _keyCapShankOffsetTowardSwitch], radius=0.4, apply_to="none");
                }


            }
        }
    }

}

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

//Prototyping Methods
module backplateTest()
{
    difference()
    {
        union()
        {
            translate([0, _key1uWidth, 0])
            {
                key1u();
                translate([(_key1uLength*1), 0, 0])
                    key1u();
            }
            key2u();

            backplateGrooveDepth = 1;
            roundedCube(size=[(_key1uLength*2), (_key1uWidth*2), _backplateDepth - backplateGrooveDepth], radius=_backplateRoundingRadius, apply_to="zmax");
        }

        translate([_key1uLength, _key1uWidth, _riserBoltHeadCutoutDepth])
            riserBoltPunch();
    }
}