_m3BoltHoleDiameter = 3.2 + 0.2; // plus padding
_m3BoltHoleRadius = _m3BoltHoleDiameter/2;

_m2BoltHoleDiameter = 2.2 + 0.45; // plus padding
_m2BoltHoleRadius = _m2BoltHoleDiameter/2;

MX_SWITCH_TYPE = "mx";
KAILH_SWITCH_TYPE = "kailh";

_mainBackplateRowCount = 3;
_mainBackplateColumnCount = 5;
_pinkyBackplateRowCount = 1;
_pinkyBackplateColumnCount = 1;
_thumbBackplateRowCount = 1;
_thumbBackplateColumnCount = 3;

// MX Switch Variables
_mxSwitchLength = 15;
_mxSwitchWidth = 15;

_mxSwitchPaddingLength = 2.25;
_mxSwitchPaddingWidth = 2.25;

_mxKey1uLength = _mxSwitchLength+(_mxSwitchPaddingLength*2);
_mxKey1uWidth = _mxSwitchWidth+(_mxSwitchPaddingWidth*2);

_mxKeySwitchCutoutLength = 13.90;
_mxKeySwitchCutoutWidth = 13.90;

_mxBackplateDepth = 5;
_mxBackplateRoundingRadius = 1.25;
_mxBackplateGrooveDepth = 1;

_mxMainBackplateLength = (_mxKey1uLength * _mainBackplateColumnCount);
_mxMainBackplateWidth = (_mxKey1uWidth * _mainBackplateRowCount);
_mxPinkyBackplateLength = (_mxKey1uLength * _pinkyBackplateColumnCount);
_mxPinkyBackplateWidth = (_mxKey1uWidth * _pinkyBackplateRowCount);
_mxThumbBackplateLength = (_mxKey1uLength * _thumbBackplateColumnCount);
_mxThumbBackplateWidth = (_mxKey1uWidth * _thumbBackplateRowCount);

_mxHousingLengthPadding = 5;
_mxHousingWidthPadding = 5;
_mxHousingBodyDepth = 18;
_mxHousingWallThickness = 5;
_mxHousingBaseThickness = 5;
_mxHousingBackplateCutoutPadding = 1.25;
_mxHousingBodyRoundingRadius = 4;

_mxBackplateOffsetFromHousing = _mxHousingBaseThickness + 0;

// Kailh Switch Variables
_kailhSwitchLength = 15;
_kailhSwitchWidth = 15;

_kailhSwitchPaddingLength = 2.25;
_kailhSwitchPaddingWidth = 2.25;

_kailhKey1uLength = _kailhSwitchLength+(_kailhSwitchPaddingLength*2);
_kailhKey1uWidth = _kailhSwitchWidth+(_kailhSwitchPaddingWidth*2);

_kailhKeySwitchCutoutLength = 13.90;
_kailhKeySwitchCutoutWidth = 13.90;

/// MAIN START ///

keyboard(MX_SWITCH_TYPE, isLeftSide=true);

/// MAIN END ///

module keyboard(switchType, isLeftSide)
{
    if (switchType == MX_SWITCH_TYPE)
    {
        union()
        {
            mxHousing(isLeftSide);
            translate([0,0,_mxBackplateOffsetFromHousing])
                mxBackplate(isLeftSide);
        }
    }
    else if (switchType == KAILH_SWITCH_TYPE)
    {
        //todo
    }
}

//Bodies
module mxHousing(isLeftSide)
{
    difference()
    {
        union()
        {
            translate([0,_mxKey1uWidth*(3),0])
                translate([-_mxHousingWallThickness,-_mxHousingWallThickness,0]) // Zero on origin
                    housingSubModule(MX_SWITCH_TYPE, _mxPinkyBackplateLength, _mxPinkyBackplateWidth);
            translate([_mxKey1uLength*(1),_mxKey1uWidth*(1),0])
                translate([-_mxHousingWallThickness,-_mxHousingWallThickness,0]) // Zero on origin
                    housingSubModule(MX_SWITCH_TYPE, _mxMainBackplateLength, _mxMainBackplateWidth);
            translate([_mxKey1uLength*(4),0,0])
                translate([-_mxHousingWallThickness,-_mxHousingWallThickness,0]) // Zero on origin
                    housingSubModule(MX_SWITCH_TYPE, _mxThumbBackplateLength, _mxThumbBackplateWidth);
        }
        //todo cut out excess
    }
}

module housingSubModule(switchType, backplateLength, backplateWidth)
{
    if (switchType == MX_SWITCH_TYPE)
    {
        difference()
        {
            mxHousingLength = backplateLength + (_mxHousingWallThickness*2);
            mxHousingWidth = backplateWidth + (_mxHousingWallThickness*2);
            roundedCube(size = [mxHousingLength, mxHousingWidth, _mxHousingBodyDepth], radius=_mxHousingBodyRoundingRadius, apply_to="all");

            // Housing body cut out.
            wallThicknessLessToleranceGap = _mxHousingWallThickness-(_mxHousingBackplateCutoutPadding);
            translate([wallThicknessLessToleranceGap, wallThicknessLessToleranceGap, _mxHousingBaseThickness])
            {
                roundedCube(size=[backplateLength+(_mxHousingBackplateCutoutPadding*2), backplateWidth+(_mxHousingBackplateCutoutPadding*2), _mxHousingBodyDepth], radius=_mxBackplateRoundingRadius, apply_to="zmax");
            }
        }
    }
}

module mxBackplate(isLeftSide)
{
    if (isLeftSide)
    {
        union()
        {
            translate([0,_mxKey1uWidth*(3),0])
                backplateSubModule(MX_SWITCH_TYPE, _pinkyBackplateRowCount, _pinkyBackplateColumnCount);
            translate([_mxKey1uLength*(1),_mxKey1uWidth*(1),0])
                backplateSubModule(MX_SWITCH_TYPE, _mainBackplateRowCount, _mainBackplateColumnCount);
            translate([_mxKey1uLength*(4),0,0])
                backplateSubModule(MX_SWITCH_TYPE, _thumbBackplateRowCount, _thumbBackplateColumnCount);
        }
    }
}

module backplateSubModule(switchType, rowCount, columnCount)
{
    for (i=[0:rowCount-1])
        for (j=[0:columnCount-1])
        {
            if (switchType == MX_SWITCH_TYPE)
            {
                translate([_mxKey1uLength*j,_mxKey1uWidth*i, 0])
                    mxKey1u();
            }
            else if (switchType == KAILH_SWITCH_TYPE)
            {
                //todo
            }
        }
}

module mxKey1u()
{
    difference()
    {
        roundedCube(size = [_mxKey1uLength, _mxKey1uWidth, _mxBackplateDepth], radius=1.25, apply_to="zmax");

        translate([_mxKey1uLength/2, _mxKey1uWidth/2, -1]) //forward to final position
            translate([-_mxKeySwitchCutoutLength/2, -_mxKeySwitchCutoutWidth/2, 0]) //back to origin
                cube([_mxKeySwitchCutoutLength, _mxKeySwitchCutoutWidth, _mxBackplateDepth+2]);
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
