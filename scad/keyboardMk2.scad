_m3BoltHoleDiameter = 3.2 + 0.2; // plus padding
_m3BoltHoleRadius = _m3BoltHoleDiameter/2;

_m2BoltHoleDiameter = 2.2 + 0.45; // plus padding
_m2BoltHoleRadius = _m2BoltHoleDiameter/2;

_backplateRowCount = 4;
_backplateColumnCount = 6;

_switchLength = 15;
_switchWidth = 15;

_switchPaddingLength = 2.25;
_switchPaddingWidth = 2.25;

_key1uLength = _switchLength+(_switchPaddingLength*2);
_key1uWidth = _switchWidth+(_switchPaddingWidth*2);

_keyCapSpacingOffset = 0.5;
_keyCapDepth = 10;
_keyCapWallThickness = 2;
_keyCapRoundingRadius = 3;
_keyCapLowTopThicknessPadding = 0;
_keyCapMedLowTopThicknessPadding = 1;
_keyCapMedTopThicknessPadding = 2;
_keyCapMedHighTopThicknessPadding = 3;

_keyCapShankOffsetRiserLength = 7.01; // Warning: Careful when modifying. This is a tuned value.
_keyCapShankOffsetRiserWidth = 4.55; // Warning: Careful when modifying. This is a tuned value.
_keyCapShankOffsetTowardSwitch = 3;

_keyCap1uLength = _key1uLength - _keyCapSpacingOffset;
_keyCap1uWidth = _key1uWidth - _keyCapSpacingOffset;

_keySwitchCutoutLength = 13.90; //14.05
_keySwitchCutoutWidth = 13.90; //14.05

_backplateLength = (_key1uLength * _backplateColumnCount);
_backplateWidth = (_key1uWidth * _backplateRowCount);
_backplateDepth = 5;
_backplateRoundingRadius = 1.25;
_backplateGrooveDepth = 1;

_backplateOffsetFromHousing = 7;

_housingLengthPadding = 5;
_housingWidthPadding = 5;
_housingBodyDepth = 18;
_housingWallThickness = 5;
_housingLength = _backplateLength + (_housingLengthPadding*2);
_housingWidth = _backplateWidth + (_housingWidthPadding*2);
_housingBackplateCutoutPadding = 1.25;
_housingBodyRoundingRadius = 4;

_housingCornerSupportLegLength = 10;
_housingSupportDepth = _backplateOffsetFromHousing;
_housingCornerSupportLegWidth = 5;
_housingHalfWidthSupportLength = _housingCornerSupportLegWidth;
_housingHalfWidthSupportWidth = _housingCornerSupportLegLength;
_housingSupportExposureIntoHousing = 3;

_housingBoltSetLengthOffset = 20;
_housingBoltSetWidthOffset = 15;

_arduinoMicroBodyLength = 19.2;
_arduinoMicroBodyWidth = 45.5; //this is faarr too long and was originally measured off of a nano

_arduinoBackstopDepth = 2.5;
_arduinoBackstopWidth = 7.5;

_arduinoHolderTabInnerDiameter = _m2BoltHoleDiameter;
_arduinoHolderTabInnerRadius = _arduinoHolderTabInnerDiameter/2;
_arduinoHolderTabDepth = 1.75;
_arduinoHolderTabWidth = 4;
_arduinoHolderTabLength = 16;

_riserBoltHeadCutoutDepth = 3;

_riserTopDiameter = 6;
_riserTopRadius = _riserTopDiameter/2;
_riserBottomDiameter = 8;
_riserBottomRadius = _riserBottomDiameter/2;
_riserHeight = _backplateOffsetFromHousing;
_riserCutoutDiameter = 3.6;
_riserCutoutRadius = _riserCutoutDiameter/2;
_riserCutoutDepth = 4;

/// MAIN START ///

echo(str("_key1uLength = ", _key1uLength));
echo(str("_key1uWidth = ", _key1uWidth));

keyboard();
//backplate(true);
//housing();

//housingBackplateEdgeSupportSet();
//arduinoMicroPunch();
//keyCap1u(_keyCapMedHighTopThicknessPadding);
//arduinoHolderTab(false);
//key1u();

//arduinoHousingTest();
//backplateSupportHousingTest();

/// MAIN END ///

module keyboard()
{
    union()
    {
        translate([_housingLengthPadding, _housingWidthPadding, 0])
        {
            backplate(includeBoltHoles=true);
        }

        translate([0, 0, -_backplateOffsetFromHousing-_housingWallThickness])
        {
            housing();

             ////Note: Comment this in to see the internal plate clearance
             //translate([_housingLengthPadding, _housingWidthPadding,0])
             //    cube([_backplateLength, _backplateWidth, _housingWallThickness]);
             //arduinoCenteringLength = (_housingLength - _arduinoMicroBodyLength)/2;
             //translate([arduinoCenteringLength, _backplateWidth-36, _housingWallThickness-3])
             //{
             //    scale([1, 1, 1])
             //        arduinoMicroPunch();
             //}
             translate([_housingLengthPadding, _housingWidthPadding, _housingWallThickness])
                 mountingRiserSet();
        }

    }
}

//Bodies
module housing()
{
    union()
    {
        arduinoCenteringLength = (_housingLength - _arduinoMicroBodyLength)/2;
        arduinoPositioningWidth = _backplateWidth-38.25;
        arduinoDepthOffset = _housingWallThickness - 1.25;

        difference()
        //union()
        {
            difference()
            {
                housingBody();

                // Housing body cut out.
                translate([_housingLengthPadding-(_housingBackplateCutoutPadding), _housingWidthPadding-(_housingBackplateCutoutPadding), _housingWallThickness])
                {
                    roundedCube(size=[_backplateLength+(_housingBackplateCutoutPadding*2), _backplateWidth+(_housingBackplateCutoutPadding*2), _housingBodyDepth], radius=_backplateRoundingRadius, apply_to="zmax");
                }
            }

            translate([arduinoCenteringLength, arduinoPositioningWidth, arduinoDepthOffset])
                scale([1, 1, 1])
                    arduinoMicroPunch();

            // Ardiuno connector wall cutout
            archPortRadius = _arduinoMicroBodyLength/2.5;
            archPortCenteringOffset = (_arduinoMicroBodyLength - (archPortRadius*2))/2;
            translate([arduinoCenteringLength + archPortCenteringOffset, arduinoPositioningWidth + _arduinoMicroBodyWidth-5, _housingWallThickness + 1])
                scale([1, 1, 0.9])
                    halfCylinder(height=10, radius=_arduinoMicroBodyLength/2.5);

            translate([arduinoCenteringLength, arduinoPositioningWidth, _housingWallThickness-3])
            {
                // Arduino holding bolt inserts
                forwardOffsetFromArduinoRear = 11.5;
                forwardOffsetFromArduinoSides = 8;
                translate([-forwardOffsetFromArduinoSides, forwardOffsetFromArduinoRear, 0])
                    cylinder(r=_riserCutoutRadius, h=_housingWallThickness, $fn=100);
                translate([_arduinoMicroBodyLength + forwardOffsetFromArduinoSides, forwardOffsetFromArduinoRear, 0])
                    cylinder(r=_riserCutoutRadius, h=_housingWallThickness, $fn=100);
                rearOffsetFromArduinoRear = 35.5;
                rearOffsetFromArduinoSides = 5;
                translate([-rearOffsetFromArduinoSides, rearOffsetFromArduinoRear, 0])
                    cylinder(r=_riserCutoutRadius, h=_housingWallThickness, $fn=100);
                translate([_arduinoMicroBodyLength + rearOffsetFromArduinoSides, rearOffsetFromArduinoRear, 0])
                    cylinder(r=_riserCutoutRadius, h=_housingWallThickness, $fn=100);
            }
        }

        // Arduino backstop block
        translate([arduinoCenteringLength, arduinoPositioningWidth, arduinoDepthOffset])
        {
            difference()
            {
                cube([_arduinoMicroBodyLength, _arduinoBackstopWidth, _arduinoBackstopDepth]);
                // Rear nut insert.
                translate([_arduinoMicroBodyLength/2, _arduinoBackstopWidth/2, 0])
                    cylinder(r=_riserCutoutRadius, h=_housingWallThickness, $fn=100);
            }
        }

        // Backplate mounting risers
        translate([_housingLengthPadding, _housingWidthPadding, _housingWallThickness])
            mountingRiserSet();

        // Corner/wall backplate support risers
        translate([_housingLengthPadding, _housingWidthPadding, _housingWallThickness])
            housingBackplateEdgeSupportSet();
    }
}

module housingBody()
{
    union()
    {
        bodyLength = _backplateLength + (_housingLengthPadding*2);
        bodyWidth = _backplateWidth + (_housingWidthPadding*2);
        roundedCube(size = [bodyLength, bodyWidth, _housingBodyDepth], radius=_housingBodyRoundingRadius, apply_to="all");
    }
}

module housingBackplateEdgeSupportSet()
{
    union()
    {
        //Corner backplate supports
        cornerZeroingWithWallOffset = 3.75;

        //SW (closest to origin)
        translate([-cornerZeroingWithWallOffset + _housingSupportExposureIntoHousing, -cornerZeroingWithWallOffset + _housingSupportExposureIntoHousing, 0])
            rotate([0, 0, 0])
                housingCornerSupport();

        //NW
        backplateWidthZeroingSpace = _backplateWidth + _housingWidthPadding - 1.25;
        translate([-cornerZeroingWithWallOffset + _housingSupportExposureIntoHousing, backplateWidthZeroingSpace - _housingSupportExposureIntoHousing, 0])
            rotate([0, 0, -90])
                housingCornerSupport();

        //NE
        backplateLengthZeroingSpace = _backplateLength + _housingLengthPadding - 1.25;
        translate([backplateLengthZeroingSpace - _housingSupportExposureIntoHousing, backplateWidthZeroingSpace - _housingSupportExposureIntoHousing, 0])
            rotate([0, 0, 180])
                housingCornerSupport();

        //SE
        translate([backplateLengthZeroingSpace - _housingSupportExposureIntoHousing, -_housingWidthPadding + 1.25 + _housingSupportExposureIntoHousing, 0])
            rotate([0, 0, 90])
                housingCornerSupport();


        //Mid backplate supports.
        //"west"
        midSupportZeroingLengthOffset = 6.25;
        translate([-midSupportZeroingLengthOffset + _housingSupportExposureIntoHousing, (_backplateWidth)/2 - _housingHalfWidthSupportWidth + _housingWidthPadding, 0])
            cube([_housingHalfWidthSupportLength, _housingHalfWidthSupportWidth, _housingSupportDepth]);

        //"east"
        translate([_backplateLength + _housingLengthPadding - 3.75 - _housingSupportExposureIntoHousing, (_backplateWidth)/2 - _housingHalfWidthSupportWidth + _housingWidthPadding, 0])
            cube([_housingHalfWidthSupportLength, _housingHalfWidthSupportWidth, _housingSupportDepth]);

        //"south"
        translate([_backplateLength/2 - _housingHalfWidthSupportWidth/2, -3.25, 0])
            cube([_housingHalfWidthSupportWidth, _housingHalfWidthSupportLength, _housingSupportDepth]);

        //"north" - mini supports around arduino
        translate([_backplateLength*(1/3) - _housingHalfWidthSupportWidth/4, _backplateWidth - 1.75, 0])
            cube([_housingHalfWidthSupportWidth/2, _housingHalfWidthSupportLength, _housingSupportDepth]);
        translate([_backplateLength*(2/3) - _housingHalfWidthSupportWidth/4, _backplateWidth - 1.75, 0])
            cube([_housingHalfWidthSupportWidth/2, _housingHalfWidthSupportLength, _housingSupportDepth]);
    }
}

module housingCornerSupport()
{
    union()
    {
        // "core"
        translate([-_housingCornerSupportLegWidth/2, -_housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegWidth, _housingCornerSupportLegWidth, _housingSupportDepth]);

        // "legs"
        translate([_housingCornerSupportLegWidth/2, -_housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegLength, _housingCornerSupportLegWidth, _housingSupportDepth]);

        translate([-_housingCornerSupportLegWidth/2, _housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegWidth, _housingCornerSupportLegLength, _housingSupportDepth]);
    }
}

module backplate(includeBoltHoles)
{
    difference()
    {
        intersection()
        {
            roundedCube(size=[_backplateLength, _backplateWidth, _backplateDepth], radius=_backplateRoundingRadius, apply_to="zmax");
            union()
            {
                for(i=[0:_backplateRowCount])
                {
                    for(j=[0:_backplateColumnCount])
                    {
                        translate([_key1uLength*j,_key1uWidth*i, 0])
                            key1u();
                    }
                }
            }
        }

        if (includeBoltHoles)
        {
            riserBoltPunchSet();
        }
    }
}

module key1u()
{
    difference()
    //union()
    {
        //cube([_key1uLength, _key1uWidth, _backplateDepth]);
        roundedCube(size = [_key1uLength, _key1uWidth, _backplateDepth], radius=1.25, apply_to="zmax");

        // //Note: Comment this in for switch model view
        // translate([_key1uLength/2, _key1uWidth/2, _backplateDepth])
        // {
        //     switchPunch();
        // }

        translate([_key1uLength/2, _key1uWidth/2, -1]) //forward to final position
            translate([-_keySwitchCutoutLength/2, -_keySwitchCutoutWidth/2, 0]) //back to origin
                cube([_keySwitchCutoutLength, _keySwitchCutoutWidth, _backplateDepth+2]);
    }
}

module mountingRiserSet()
{
    //SW
    translate([(_key1uLength*2), (_key1uWidth*1), 0])
        mountingRiser();

    //SE
    translate([(_key1uLength*4), (_key1uWidth*1), 0])
        mountingRiser();

    //NE
    translate([(_key1uLength*4), (_key1uWidth*3), 0])
        mountingRiser();

    //NW
    translate([(_key1uLength*2), (_key1uWidth*3), 0])
        mountingRiser();
}

module mountingRiser()
{
    difference()
    //union()
    {
        cylinder(r2=_riserTopRadius, r1=_riserBottomRadius, h=_riserHeight, $fn=100);
        translate([0,0,_riserHeight-_riserCutoutDepth])
            cylinder(r=_riserCutoutRadius, h=_riserHeight, $fn=100);
    }
}

module keyCap1u(topThicknessPadding)
{
    union()
    {
        cutoutZTranslation = _keyCapWallThickness + topThicknessPadding;
        difference()
        //union()
        {
            roundedCube(size=[_keyCap1uLength, _keyCap1uWidth, _keyCapDepth + topThicknessPadding], radius = _keyCapRoundingRadius, apply_to="zmin");

            cutoutCubeSize = [_keyCap1uLength-(_keyCapWallThickness*2), _keyCap1uWidth-(_keyCapWallThickness*2), _keyCapDepth];
            translate([_keyCapWallThickness, _keyCapWallThickness, cutoutZTranslation])
                roundedCube(size=cutoutCubeSize, radius = _keyCapRoundingRadius, apply_to="zmin");
        }

        //shank connector
        translate([_keyCap1uLength/2, _keyCap1uWidth/2, cutoutZTranslation])
        {
            keyCapShankConnector();
        }
    }
}

module keyCapShankConnector()
{
    union()
    {
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
                    crossPunchFinLength = 4.3; // Warning: Careful when modifying. This is a tuned value.
                    crossPunchFinWidth = 1.21; // Warning: Careful when modifying. This is a tuned value.
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

module arduinoHolderTab(includePressureTab)
{
    union()
    {
        _tabLength = _arduinoHolderTabLength;
        _tabWidth = _arduinoHolderTabWidth;
        _tabDepth = _arduinoHolderTabDepth;

        _washerDepth = _tabDepth;
        _washerThickness = 2;
        _washerInnerDiameter = _arduinoHolderTabInnerDiameter;
        _washerInnerRadius = _washerInnerDiameter/2;
        _washerOuterRadius = _washerInnerRadius + _washerThickness;
        difference()
        {
            cylinder(r=_washerOuterRadius, h=_washerDepth, center=false, $fn=200);
            translate([0, 0, -1])
                cylinder(r=_washerInnerRadius, h=_washerDepth+2, center=false, $fn=200);
        }

        translate([_washerInnerRadius,-_tabWidth/2,0])
            cube([_tabLength, _tabWidth, _tabDepth]);

        if (includePressureTab)
        {
            pressureTabLength = 4;
            pressureTabDepth = 2;
            translate([_tabLength-pressureTabLength+_washerInnerRadius, -_tabWidth/2, _tabDepth])
                cube([pressureTabLength, _tabWidth, pressureTabDepth]);
        }
    }
}

//Punches
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
    arduinoMicroBodyWidth = _arduinoMicroBodyWidth; //43;
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
    //SW
    translate([(_key1uLength*2), (_key1uWidth*1), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //SE
    translate([(_key1uLength*4), (_key1uWidth*1), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //NE
    translate([(_key1uLength*4), (_key1uWidth*3), _riserBoltHeadCutoutDepth])
        riserBoltPunch();

    //NW
    translate([(_key1uLength*2), (_key1uWidth*3), _riserBoltHeadCutoutDepth])
        riserBoltPunch();
}

module riserBoltPunch()
{
    union()
    {
        //Traditional bolt punch
        boltHeadCutoutRadius = 2.1;
        boltHeadCutoutDepth = 3;

        cylinder(r=boltHeadCutoutRadius, h=boltHeadCutoutDepth+1, $fn=100);

        boltPunchDepth = _backplateDepth+1;
        translate([0,0,-boltPunchDepth])
               cylinder(r=_m2BoltHoleRadius, h=boltPunchDepth+2, $fn=100);
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

/// Builds a cylinder sliced in half along the diameter.
/// height - height of the cylinder
/// depth - radius of the cylinder
module halfCylinder(height, radius)
{
    difference()
    //union()
    {
        translate([radius, 0, 0])
            rotate([-90, 0, 0])
                cylinder(r=radius, h=height, $fn=100);

        translate([-1, -1, -radius-1])
            cube([(radius*2)+2, height+2, radius+1]);
    }
}

//Prototyping Methods
module arduinoHousingTest()
{
    echo("ArduinoHousingTest");
    difference()
    {
        housing();

        cutoutCubeLength = _housingLength/2.5;
        cutoutCubeWidth = _housingWidth+2;
        cutoutCubeDepth = _housingBodyDepth+1;

        //Side cut outs
        translate([-1,-1,-1])
            cube([cutoutCubeLength, cutoutCubeWidth, cutoutCubeDepth]);

        translate([_housingLength-cutoutCubeLength+1,-1,-1])
            cube([cutoutCubeLength, cutoutCubeWidth, cutoutCubeDepth]);

        //Front cut out
        translate([-1,-8,-1]) //-8 to include the center riser
            cube([_housingLength+2, cutoutCubeWidth/2, cutoutCubeDepth]);
    }
}

module backplateSupportHousingTest()
{
    difference()
    {
        housing();

        cutoutCubeLength = _housingLength;
        cutoutCubeWidth = _housingWidth+2;
        cutoutCubeDepth = _housingBodyDepth+1;

        translate([17, -1, -1])
            cube([cutoutCubeLength, cutoutCubeWidth, cutoutCubeDepth]);

        translate([-1, -1, -1])
            cube([cutoutCubeLength, cutoutCubeWidth/2.5, cutoutCubeDepth]);
    }
}
