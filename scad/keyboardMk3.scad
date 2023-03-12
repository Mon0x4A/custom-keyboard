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

_housingCornerSupportLegLength = 8.5;
_housingCornerSupportLegWidth = 3;
_housingStraightSupportLength = _housingCornerSupportLegWidth;
_housingStraightSupportWidth = _housingCornerSupportLegLength;
_housingSupportExposureIntoHousing = 3;

_insetNutCutoutDiameter = 3.6;
_insetNutCutoutRadius = _insetNutCutoutDiameter/2;
_arduinoInsetNutCutoutDepth = 3;
_arduinoNutInsertLengthCenterToCenter = 22;
_arduinoNutInsertWidthCenterToCenter = 40;

_riserBoltHeadCutoutDepth = 3;

_riserTopDiameter = 6;
_riserTopRadius = _riserTopDiameter/2;
_riserBottomDiameter = 8;
_riserBottomRadius = _riserBottomDiameter/2;
_riserCutoutDiameter = 3.6;
_riserCutoutRadius = _riserCutoutDiameter/2;
_riserCutoutDepth = 4;

// MX Switch Variables
_mxBackplateDepth = 5;
_mxHousingBodyDepth = 18;
_mxBackplateOffsetFromHousing = _housingBaseThickness + 0;

// Kailh Switch Variables
_kailhBackplateDepth = 3;
_kailhHousingBodyDepth = 10;
_kailhBackplateRiserHeight = 3;
_kailhBackplateOffsetFromHousing = _housingBaseThickness + _kailhBackplateRiserHeight;
_kailhKeyCapDepth = 2.5;

//Keycap Variables
_keyCapSpacingOffset = 0.5;
_keyCapWallThickness = 2;
_keyCapRoundingRadius = 3;

_keyCap1uLength = _key1uLength - _keyCapSpacingOffset;
_keyCap1uWidth = _key1uWidth - _keyCapSpacingOffset;
_keyCap1_25uLength = _key1_25uLength - _keyCapSpacingOffset;
_keyCap1_25uWidth = _key1_25uWidth - _keyCapSpacingOffset;

// Ardiuno Variables
_arduinoMicroBodyLength = 19.2;
_arduinoMicroBodyWidth = 36.2;

_arduinoHousingLengthEdgePadding = 6;
_arduinoHousingWidthEdgePadding = 6;
_arduinoHousingBaseLength = _arduinoMicroBodyLength + (_arduinoHousingLengthEdgePadding*2);
_arduinoHousingBaseWidth = _arduinoMicroBodyWidth + (_arduinoHousingWidthEdgePadding*2);
_arduinoHousingBaseDepth = 4;

_arduinoLengthPlacment = _key1uWidth*(6)+1.3;
_arduinoWidthPlacment = 24.5;

/// MAIN START ///

keyboard(KAILH_SWITCH_TYPE, isLeftSide=true);
//arduinoHousing();
//kailhKeyCapTop(_key1uLength, _key1uWidth, _kailhKeyCapDepth);
//kailhKeycapShank();

/// MAIN END ///
module keyboard(switchType, isLeftSide)
{
    if (isLeftSide)
    {
        keyboardAssembly(switchType);
    }
    else
    {
        mirror([1,0,0])
            keyboardAssembly(switchType);
    }
}

module keyboardAssembly(switchType)
{
    backplateDepth = (switchType == MX_SWITCH_TYPE) ? _mxBackplateDepth : _kailhBackplateDepth;
    backplateOffsetFromHousing = (switchType == MX_SWITCH_TYPE) ? _mxBackplateOffsetFromHousing : _kailhBackplateOffsetFromHousing;
    housingDepth = (switchType == MX_SWITCH_TYPE) ? _mxHousingBodyDepth : _kailhHousingBodyDepth;
    union()
    {
        housing(housingDepth);
        translate([0,0,backplateOffsetFromHousing])
            backplate(backplateDepth);
        //Arduino enclosure
        translate([_arduinoLengthPlacment,_arduinoWidthPlacment,0])
            arduinoHousing();
        //Backplate mounting risers
        translate([0,0,_housingBaseThickness])
            backplateMountingRiserSet(backplateDepth);
        //Housing backplate supports
        housingBackplateEdgeSupportSet(backplateOffsetFromHousing-_housingBaseThickness);
    }
}

//Bodies
module housing(housingDepth)
{
    union()
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

            // Housing submodule overlay cutouts
            union()
            {
                cutoutOverhang = 5;
                pinkyWallCutoutLength = _pinkyBackplateLength+(_housingBackplateCutoutPadding*2)+cutoutOverhang;
                pinkyWallCutoutWidth = _pinkyBackplateWidth+(_housingBackplateCutoutPadding*2);
                translate([-_housingBackplateCutoutPadding,_key1uWidth*(3)-_housingBackplateCutoutPadding,_housingBaseThickness])
                    roundedCube(size = [pinkyWallCutoutLength, pinkyWallCutoutWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="zmax");

                mainWallCutoutLength = _mainBackplateLength+(_housingBackplateCutoutPadding*2);
                mainWallCutoutWidth = _mainBackplateWidth+(_housingBackplateCutoutPadding*2);
                translate([_key1_25uLength*(1)-_housingBackplateCutoutPadding,_key1_25uWidth*(1)-_housingBackplateCutoutPadding,_housingBaseThickness])
                    roundedCube(size = [mainWallCutoutLength, mainWallCutoutWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="zmax");

                thumbWallCutoutLength = _thumbBackplateLength+(_housingBackplateCutoutPadding*2);
                thumbWallCutoutWidth = _thumbBackplateWidth+(_housingBackplateCutoutPadding*2);
                translate([_key1uLength*(4)-_housingBackplateCutoutPadding,-_housingBackplateCutoutPadding,_housingBaseThickness])
                    roundedCube(size = [thumbWallCutoutLength, thumbWallCutoutWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="zmax");
            }

            // Arduino-adjacent wall cutouts
            arduinoHousingCutoutWidthOffset = -0.1;
            arduinoHousingCutoutLengthOffset = -0.6;
            arduinoHousingCutoutDifferenceFromRoundedMeasure = -1.1;
            arduinoHousingCutoutExtraLength = 2;
            translate([_arduinoLengthPlacment+arduinoHousingCutoutLengthOffset,_arduinoWidthPlacment+arduinoHousingCutoutWidthOffset,_housingBaseThickness])
                cube([_arduinoHousingBaseLength, _arduinoHousingBaseWidth+arduinoHousingCutoutDifferenceFromRoundedMeasure, housingDepth]);
        }

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

//todo port over housing supports for backplate into submodule space?
//need to avoid larger cutouts, so maybe it goes in the housing itself...
module housingBackplateEdgeSupportSet(supportDepth)
{
    union()
    {
        riserInwardsLengthAdjustment = 0.25;
        riserInwardsWidthAdjustment = 0.25;
        //Corner backplate supports
        //Pinky Corners
        translate([riserInwardsLengthAdjustment,_key1uLength*(3)+_pinkyBackplateWidth-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingCornerSupport(supportDepth);
        translate([riserInwardsLengthAdjustment,_key1uLength*(3)+riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 0])
                housingCornerSupport(supportDepth);
        translate([_key1_25uLength*(1)+riserInwardsLengthAdjustment,_key1uWidth*(3)+riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 180])
                housingCornerSupport(supportDepth);

        //Main Corners
        translate([_key1_25uLength*(1)+riserInwardsLengthAdjustment,_key1_25uWidth*(1)+riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 0])
                housingCornerSupport(supportDepth);
        translate([_key1_25uLength*(1)+_key1uLength*(3)+riserInwardsLengthAdjustment,_key1_25uWidth*(1)+riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 180])
                housingCornerSupport(supportDepth);
        translate([_key1_25uLength*(1)+_key1uLength*(5)-riserInwardsLengthAdjustment,_key1_25uWidth*(1)+_key1uWidth*(3)-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 180])
                housingCornerSupport(supportDepth);
        translate([_key1_25uLength*(1)+_key1uLength*(5)-riserInwardsLengthAdjustment,_key1_25uWidth*(1)-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 90])
                housingCornerSupport(supportDepth);

        //Thumb Corners
        translate([_key1_25uLength*(1)+_key1uLength*(3)+riserInwardsLengthAdjustment,riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 0])
                housingCornerSupport(supportDepth);
        translate([_key1_25uLength*(4)+_key1uLength*(3)-riserInwardsLengthAdjustment,riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, 90])
                housingCornerSupport(supportDepth);

        //Non-corner backplate supports.
        //Top edge
        translate([_key1_25uLength*(1)+_key1uLength*(1)-_housingStraightSupportLength,_key1uWidth*(3)+_pinkyBackplateWidth-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);
        translate([_key1_25uLength*(1)+_key1uLength*(3)-_housingStraightSupportLength,_key1uWidth*(3)+_pinkyBackplateWidth-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);

        //Main bottom
        translate([_key1_25uLength*(1)+_key1uLength*(1.5)-_housingStraightSupportLength,_key1_25uWidth*(1)+riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);

        //Main arduino side
        translate([_key1_25uLength*(3)+_key1uLength*(3)-riserInwardsLengthAdjustment,_key1_25uWidth*(1)+_key1uWidth*(1.5)-(_housingStraightSupportLength*(3/4)),_housingBaseThickness])
            rotate([0, 0, 0])
                housingStraightSupport(supportDepth);

        //Thumb bottom
        translate([_key1_25uLength*(3)+_key1uLength*(2.5)-_housingStraightSupportLength,riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);

        //Thumb top arduino side
        translate([_key1_25uLength*(3)+_key1uLength*(3.5)-_housingStraightSupportLength+_housingStraightSupportLength/2,_key1_25uWidth*(1)-riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);
    }
}

module housingCornerSupport(depth)
{
    union()
    {
        // "core"
        translate([-_housingCornerSupportLegWidth/2, -_housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegWidth, _housingCornerSupportLegWidth, depth]);

        // "legs"
        translate([_housingCornerSupportLegWidth/2, -_housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegLength, _housingCornerSupportLegWidth, depth]);

        translate([-_housingCornerSupportLegWidth/2, _housingCornerSupportLegWidth/2, 0])
            cube([_housingCornerSupportLegWidth, _housingCornerSupportLegLength, depth]);
    }
}

module housingStraightSupport(depth)
{
    union()
    {
        translate([-_housingStraightSupportLength/2,-_housingStraightSupportLength/2,0])
           cube([_housingStraightSupportLength, _housingStraightSupportWidth, depth]);
    }
}

module backplate(backplateDepth)
{
    difference()
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

        backplateBoltCountersinkDepth = 1.5;
        translate([0,0,-backplateBoltCountersinkDepth])
            riserBackplateBoltPunchSet(backplateDepth);
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

module backplateMountingRiserSet(riserHeight)
{
    translate([(_key1uLength*1)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight);

    translate([(_key1uLength*2)+(_key1_25uLength*1), (_key1uWidth*1)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*0)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight);
}

module backplateMountingRiser(riserHeight)
{
    difference()
    {
        cylinder(r2=_riserTopRadius, r1=_riserBottomRadius, h=riserHeight, $fn=100);
        translate([0,0,riserHeight-_riserCutoutDepth])
            cylinder(r=_riserCutoutRadius, h=_riserCutoutDepth+1, $fn=100);
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
            difference()
            {
                arbitraryDepth = 10;
                housingSubModule(_arduinoHousingBaseLength-(_housingBodyRoundingRadius*2), _arduinoHousingBaseWidth-(_housingBodyRoundingRadius*2), arbitraryDepth);
                translate([0,0,_arduinoHousingBaseDepth])
                    cube([_arduinoHousingBaseLength, _arduinoHousingBaseWidth, arbitraryDepth]);
            }

            nutSetOffsetAdjustment = -0.5;
            arduinoInsetNutSetLengthOffset = ((_arduinoHousingBaseLength-_arduinoNutInsertLengthCenterToCenter)/2)+nutSetOffsetAdjustment;
            arduinoInsetNutSetWidthOffset = ((_arduinoHousingBaseWidth-_arduinoNutInsertWidthCenterToCenter)/2)+nutSetOffsetAdjustment;
            translate([arduinoInsetNutSetLengthOffset,arduinoInsetNutSetWidthOffset,_arduinoHousingBaseDepth-_arduinoInsetNutCutoutDepth])
                arduinoInsetNutPunchSet();
        }

        paddingOffsetAdjustment = 0.25;
        translate([_arduinoHousingLengthEdgePadding-paddingOffsetAdjustment, _arduinoHousingWidthEdgePadding-paddingOffsetAdjustment, 0])
            arduinoMicroPunch();
    }
}

module kailhKeyCapTop(length, width, depth)
{
    capInterfaceShankCenterToCenter = 5.70;
    capInterfaceShankWidth = 3.3;
    capInterfaceShankDepth = 2;
    capInterfaceShankLength = 1.9;
    totalCapInterfaceLength = capInterfaceShankCenterToCenter+capInterfaceShankLength;

    difference()
    {
        difference()
        {
            baseCapDepth = 20;
            // form the base cap
            roundedCube(size=[length, width, baseCapDepth], radius = _keyCapRoundingRadius, apply_to="zmin");
            //cut to the desired depth
            translate([-1,-1,depth])
                cube([length+2,width+2,baseCapDepth]);
        }

        translate([(length-totalCapInterfaceLength)/2,(width-capInterfaceShankWidth)/2,1])
            union()
            {
                cube([capInterfaceShankLength,capInterfaceShankWidth,capInterfaceShankDepth+1]);
                translate([capInterfaceShankCenterToCenter,0,0])
                    cube([capInterfaceShankLength,capInterfaceShankWidth,capInterfaceShankDepth+1]);
            }
    }
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

module arduinoInsetNutPunchSet()
{
    translate([0,0,0])
        arduinoInsetNutPunch();
    translate([_arduinoNutInsertLengthCenterToCenter,0,0])
        arduinoInsetNutPunch();
    translate([0,_arduinoNutInsertWidthCenterToCenter,0])
        arduinoInsetNutPunch();
    translate([_arduinoNutInsertLengthCenterToCenter,_arduinoNutInsertWidthCenterToCenter,0])
        arduinoInsetNutPunch();
}

module arduinoInsetNutPunch()
{
    union()
    {
        cylinder(r=_insetNutCutoutRadius,h=_arduinoInsetNutCutoutDepth+1,$fn=100);
    }
}

module riserBackplateBoltPunchSet(backplateDepth)
{
    translate([(_key1uLength*1)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), _riserBoltHeadCutoutDepth])
        riserBackplateBoltPunch(backplateDepth);

    translate([(_key1uLength*2)+(_key1_25uLength*1), (_key1uWidth*1)+(_key1_25uWidth*1), _riserBoltHeadCutoutDepth])
        riserBackplateBoltPunch(backplateDepth);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), _riserBoltHeadCutoutDepth])
        riserBackplateBoltPunch(backplateDepth);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*0)+(_key1_25uWidth*1), _riserBoltHeadCutoutDepth])
        riserBackplateBoltPunch(backplateDepth);
}

module riserBackplateBoltPunch(backplateDepth)
{
    union()
    {
        //Traditional bolt punch
        boltHeadCutoutRadius = 2.1;
        boltHeadCutoutDepth = 3;

        cylinder(r=boltHeadCutoutRadius, h=boltHeadCutoutDepth+1, $fn=100);

        boltPunchDepth = backplateDepth+1;
        translate([0,0,-boltPunchDepth])
               cylinder(r=_m2BoltHoleRadius, h=boltPunchDepth+2, $fn=100);
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
