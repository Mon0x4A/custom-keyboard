// Constants
_m3BoltHoleDiameter = 3.2 + 0.2; // plus padding
_m3BoltHoleRadius = _m3BoltHoleDiameter/2;

_m2BoltHoleDiameter = 2.2 + 0.45; // plus padding
_m2BoltHoleRadius = _m2BoltHoleDiameter/2;

MX_SWITCH_TYPE = "mx";
KAILH_SWITCH_TYPE = "kailh";

KEY_1U_MODIFIER = 1;
KEY_1_25U_MODIFIER = 1.25;

// General Variables
_mainBackplateRowCount = 3;
_mainBackplateColumnCount = 5;
_pinkyBackplateRowCount = 1;
_pinkyBackplateColumnCount = 1;
_thumbBackplateRowCount = 1;
_thumbBackplateColumnCount = 3;

_switchLength = 15;
_switchWidth = 15;

_switchPaddingLength = 2.25;
_switchPaddingWidth = 2.25;

_key1uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1uWidth = (_switchWidth*KEY_1U_MODIFIER)+(_switchPaddingWidth*2);
_key1_25uLength = (_switchLength*KEY_1U_MODIFIER)+(_switchPaddingLength*2);
_key1_25uWidth = (_switchWidth*KEY_1_25U_MODIFIER)+(_switchPaddingWidth*2);

_keySwitchCutoutLength = 13.90;
_keySwitchCutoutWidth = 13.90;

_backplateRoundingRadius = 1.25;
_backplateGrooveDepth = 1;

_mainBackplateLength = (_key1uLength * _mainBackplateColumnCount);
_mainBackplateWidth = (_key1uWidth * _mainBackplateRowCount);
_pinkyBackplateLength = (_key1_25uLength * _pinkyBackplateColumnCount);
_pinkyBackplateWidth = (_key1_25uWidth * _pinkyBackplateRowCount);
_thumbBackplateLength = (_key1_25uLength * _thumbBackplateColumnCount);
_thumbBackplateWidth = (_key1_25uWidth * _thumbBackplateRowCount);

_housingWallThickness = 3.5;
_housingBaseThickness = 3;
_housingBackplateCutoutPadding = 1.25;
_housingBodyRoundingRadius = 4;

// MX Switch Variables
_mxBackplateDepth = 5;
_mxHousingBodyDepth = 18;
_mxBackplateOffsetFromHousing = _housingBaseThickness + 0;

// Kailh Switch Variables
_kailhBackplateDepth = 3;
_kailhHousingBodyDepth = 10;
_kailhBackplateRiserHeight = 3;
_kailhBackplateOffsetFromHousing = _housingBaseThickness + _kailhBackplateRiserHeight;

// Ardiuno Variables
_arduinoMicroBodyLength = 19.2;
_arduinoMicroBodyWidth = 36.2;

_arduinoHousingLengthEdgePadding = 6;
_arduinoHousingWidthEdgePadding = 6;
_arduinoHousingBaseLength = _arduinoMicroBodyLength + (_arduinoHousingLengthEdgePadding*2);
_arduinoHousingBaseWidth = _arduinoMicroBodyWidth + (_arduinoHousingWidthEdgePadding*2);
_arduinoHousingBaseDepth = 3;

_arduinoLengthPlacment = _key1uWidth*(6)+1.3;
_arduinoWidthPlacment = 24.5;

/// MAIN START ///

//keyboard(KAILH_SWITCH_TYPE, isLeftSide=true);
//arduinoHousing();
kailhKeycapShank();

/// MAIN END ///

module keyboard(switchType, isLeftSide)
{
    backplateDepth = (switchType == MX_SWITCH_TYPE) ? _mxBackplateDepth : _kailhBackplateDepth;
    backplateOffsetFromHousing = (switchType == MX_SWITCH_TYPE) ? _mxBackplateOffsetFromHousing : _kailhBackplateOffsetFromHousing;
    housingDepth = (switchType == MX_SWITCH_TYPE) ? _mxHousingBodyDepth : _kailhHousingBodyDepth;
    union()
    {
        housing(housingDepth);
        translate([0,0,backplateOffsetFromHousing])
            backplate(backplateDepth);
        translate([_arduinoLengthPlacment,_arduinoWidthPlacment,0])
            arduinoHousing();
    }
}

//Bodies
module housing(housingDepth)
{
    difference()
    {
        union()
        {
            translate([0,_key1uWidth*(3),0])
                translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                    housingSubModule(_pinkyBackplateLength, _pinkyBackplateWidth, housingDepth);
            translate([_key1_25uLength*(1),_key1_25uWidth*(1),0])
                translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                    housingSubModule(_mainBackplateLength, _mainBackplateWidth, housingDepth);
            translate([_key1uLength*(4),0,0])
                translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                    housingSubModule(_thumbBackplateLength, _thumbBackplateWidth, housingDepth);
        }
        //todo cut out excess
    }
}

module housingSubModule(backplateLength, backplateWidth, housingDepth)
{
    difference()
    {
        housingLength = backplateLength + (_housingWallThickness*2);
        housingWidth = backplateWidth + (_housingWallThickness*2);
        roundedCube(size = [housingLength, housingWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="all");

        // Housing body cut out.
        wallThicknessLessToleranceGap = _housingWallThickness-(_housingBackplateCutoutPadding);
        translate([wallThicknessLessToleranceGap, wallThicknessLessToleranceGap, _housingBaseThickness])
        {
            roundedCube(size=[backplateLength+(_housingBackplateCutoutPadding*2), backplateWidth+(_housingBackplateCutoutPadding*2), housingDepth], radius=_backplateRoundingRadius, apply_to="zmax");
        }
    }
}

module backplate(backplateDepth)
{
    union()
    {
        translate([0,_key1uWidth*(3),0])
            backplateSubModule(_pinkyBackplateRowCount, _pinkyBackplateColumnCount, _key1_25uLength, _key1_25uWidth, backplateDepth);
        translate([_key1_25uLength*(1),_key1_25uWidth*(1),0])
            backplateSubModule(_mainBackplateRowCount, _mainBackplateColumnCount, _key1uLength, _key1uWidth, backplateDepth);
        translate([_key1uLength*(4),0,0])
            backplateSubModule(_thumbBackplateRowCount, _thumbBackplateColumnCount, _key1_25uLength, _key1_25uWidth, backplateDepth);
    }
}

module backplateSubModule(rowCount, columnCount, keyLength, keyWidth, backplateDepth)
{
    for (i=[0:rowCount-1])
        for (j=[0:columnCount-1])
        {
            translate([keyLength*j,keyWidth*i, 0])
                keyUnit(keyLength, keyWidth, backplateDepth);
        }
}

module keyUnit(length, width, depth)
{
    difference()
    {
        roundedCube(size = [length, width, depth], radius=1.25, apply_to="zmax");

        translate([length/2, width/2, -1]) //forward to final position
            translate([-_keySwitchCutoutLength/2, -_keySwitchCutoutWidth/2, 0]) //back to origin
                cube([_keySwitchCutoutLength, _keySwitchCutoutWidth, depth+2]);
    }
}

module arduinoHousing()
{
    union()
    {
        difference()
        {
            arbitraryDepth = 10;
            housingSubModule(_arduinoHousingBaseLength-(_housingBodyRoundingRadius*2), _arduinoHousingBaseWidth-(_housingBodyRoundingRadius*2), arbitraryDepth);
            //translate([0,0,_arduinoHousingBaseDepth])
            //    cube([_arduinoHousingBaseLength, _arduinoHousingBaseWidth, arbitraryDepth]);
        }

        paddingOffsetAdjustment = 0.25;
        translate([_arduinoHousingLengthEdgePadding-paddingOffsetAdjustment, _arduinoHousingWidthEdgePadding-paddingOffsetAdjustment, 0])
            arduinoMicroPunch();
    }
}

module kailhKeycapTop(length, width)
{
}

module kailhKeycapShank()
{
    printingTolerance = 0.05;
    switchInterfaceShankLength = 4.25;
    switchInterfaceShankWidth = 1.20 - printingTolerance;
    switchInterfaceShankDepth = 3 - printingTolerance;
    switchInterfaceShankCenterToCenter = 5.70;
    capInterfaceShankLength = 2;
    capInterfaceShankWidth = 1.5-printingTolerance;
    capInterfaceShankDepth = switchInterfaceShankDepth-printingTolerance;
    capInterfaceShankCenterToCenter = switchInterfaceShankCenterToCenter;
    shankInterfaceConnectorLength = 1;
    shankInterfaceConnectorWidth = 8;
    shankInterfaceConnectorDepth = switchInterfaceShankDepth;

    union()
    {
        //Cap interface
        translate([0,0,0])
            cube([capInterfaceShankLength, capInterfaceShankWidth, capInterfaceShankDepth]);
        translate([0,capInterfaceShankCenterToCenter,0])
            cube([capInterfaceShankLength, capInterfaceShankWidth, capInterfaceShankDepth]);

        //Interface connector
        shankInterfaceCenteringWidth = ((capInterfaceShankCenterToCenter+capInterfaceShankWidth)-shankInterfaceConnectorWidth)/2;
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

//Punches
module arduinoMicroPunch()
{
    arduinoMicroBodyLength = _arduinoMicroBodyLength;
    arduinoMicroBodyWidth = _arduinoMicroBodyWidth;
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
