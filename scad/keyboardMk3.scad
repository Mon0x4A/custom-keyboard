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

_oledBodyLength = 27.8;
_oledBodyWidth = 27.8;
_oledBodyDepth = 3.8;
_oledAttachmentHolesCentertoCenter = 23.5;
_oledScreenLength = 23.75;
_oledScreenWidth = 12.9;
_oledScreenLengthOffsetFromTop = 3.9;
_oledScreenWidthOffsetFromLeft = 2;
_oledBoltAttachmentLengthOffset = 2;
_oledBoltAttachmentWidthOffset = 2;

_trrsBodyLength = 12.1;
_trrsBodyWidth = 6.1;
_trrsBodyDepth = 5.1;
_trrsWallThickness = 2;

_trrsWedgeLength = _trrsBodyWidth;
_trrsWedgeWidth = _trrsBodyDepth;
_trrsWedgeDepth = 2;
_trrsWedgeAngle = 8;

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
_kailhBackplateRiserHeight = 2;
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
_arduinoMicroBodyLength = 18.5;
_arduinoMicroBodyWidth = 36.45;

_arduinoHousingLengthEdgePadding = 8;
_arduinoHousingWidthEdgePadding = 9;
_arduinoHousingBaseLength = _arduinoMicroBodyLength + (_arduinoHousingLengthEdgePadding*2);
_arduinoHousingBaseWidth = _arduinoMicroBodyWidth + (_arduinoHousingWidthEdgePadding*2);
_arduinoHousingBaseDepth = 5;
_arduinoHousingLidHeight = 12;
_arduinoHousingLidBoltCounterSink = 0;
_arduinoHousingLidBaseThickness = 2;
_arduinoHousingCableCutoutWidth = _arduinoHousingBaseWidth*(3/5);
_arduinoHousingCableCutoutOffset = _arduinoHousingBaseWidth*(1/5);
_arduinoHousingPaddingOffsetAdjustment = 0.25;

_arduinoInsetNutCutoutDepth = 3;
_arduinoNutInsertLengthCenterToCenter = 25;
_arduinoNutInsertWidthCenterToCenter = 45;
_arduinoNutSetOffsetAdjustment = -0.5;
_arduinoInsetNutSetLengthOffset = ((_arduinoHousingBaseLength-_arduinoNutInsertLengthCenterToCenter)/2)+_arduinoNutSetOffsetAdjustment;
_arduinoInsetNutSetWidthOffset = ((_arduinoHousingBaseWidth-_arduinoNutInsertWidthCenterToCenter)/2)+_arduinoNutSetOffsetAdjustment;

_arduinoLengthPlacment = _key1uWidth*(6)+1.3;
_arduinoWidthPlacment = 24.5;

/// MAIN START ///

keyboard(KAILH_SWITCH_TYPE, isLeftSide=true);
wristRest();
//housing(_kailhHousingBodyDepth);
//backplate(_kailhBackplateDepth);
//oledScreenPunch(_arduinoHousingLidBaseThickness+2);
//trrsBodyPunch();
//trrsWedgeBlock();
//arduinoHousing(renderLid=true);
//arduinoHousingBase();
//arduinoHousingTop();
//arduinoMicroPunch();
//kailhKeyCapTop(_key1uLength, _key1uWidth, _kailhKeyCapDepth);
//kailhKeyCapTop(_key1_25uWidth, _key1uWidth, _kailhKeyCapDepth);
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
    backplateSupportHeight = backplateOffsetFromHousing-_housingBaseThickness;
    union()
    {
        difference()
        {
            union()
            {
                difference()
                {
                    housing(housingDepth);
                    //Trim off the top edge of the housing to avoid sharper corners
                    housingTopTrimBlockLength = _mainBackplateLength+_pinkyBackplateLength+_thumbBackplateLength;
                    housingTopTrimBlockWidth = _mainBackplateWidth+_pinkyBackplateWidth+_thumbBackplateWidth;
                    housingTopTrimAmount = 1.0;
                    translate([-_housingWallThickness*3, -_housingWallThickness*3, housingDepth-housingTopTrimAmount])
                        cube([housingTopTrimBlockLength, housingTopTrimBlockWidth, housingDepth]);
                }
                translate([0,0,backplateOffsetFromHousing])
                    backplate(backplateDepth);
                //Arduino enclosure
                translate([_arduinoLengthPlacment,_arduinoWidthPlacment,0])
                    union()
                    {
                        arduinoHousing(renderLid=true);
                        arduinoHousingBodyJointWidth = 60.45;
                        arduinoHousingBodyJointLength = 28.70;
                        arduinoHousingBodyJointDepth = 2;
                        jointLengthOffset = -7;
                        jointWidthOffset = -7;
                        translate([jointLengthOffset, jointWidthOffset, 0])
                            difference()
                            {
                                roundedCube(size=[arduinoHousingBodyJointLength, arduinoHousingBodyJointWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="all");
                                cutoutEdgePadding = 5;
                                translate([-cutoutEdgePadding,-cutoutEdgePadding, arduinoHousingBodyJointDepth])
                                    cube([arduinoHousingBodyJointLength+(cutoutEdgePadding*2), arduinoHousingBodyJointWidth+(cutoutEdgePadding*2), housingDepth]);
                            }

                    }
            }
            if (backplateSupportHeight < _riserCutoutDepth)
            {
                riserCounterSinkAmount = _riserCutoutDepth - backplateSupportHeight;
                translate([0, 0, riserCounterSinkAmount])
                    backplateMountingRiserSet(backplateSupportHeight, renderNutHoles=false);
            }
        }
        //Backplate mounting risers
        translate([0,0,_housingBaseThickness - (_riserCutoutDepth-backplateSupportHeight)])
            backplateMountingRiserSet(max(_riserCutoutDepth, backplateSupportHeight), renderNutHoles=true);
        //Housing backplate supports
        housingBackplateEdgeSupportSet(backplateSupportHeight);
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
                additionPinkyHousingLengthToHideRearSeam = 1;
                translate([0,_key1uWidth*(3),0])
                    translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                        housingSubModule(_pinkyBackplateLength+additionPinkyHousingLengthToHideRearSeam, _pinkyBackplateWidth, housingDepth, _housingBaseThickness);
                translate([_key1_25uLength*(1),_key1_25uWidth*(1),0])
                    translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                        housingSubModule(_mainBackplateLength, _mainBackplateWidth, housingDepth, _housingBaseThickness);
                translate([_key1uLength*(4),0,0])
                    translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                        housingSubModule(_thumbBackplateLength, _thumbBackplateWidth, housingDepth, _housingBaseThickness);
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
            // reduce the width here so we can get the round joint at the top
            arduinoHousingCutoutDifferenceFromRoundedMeasure = -3.1;
            arduinoHousingCutoutExtraLength = 2;
            translate([_arduinoLengthPlacment+arduinoHousingCutoutLengthOffset,_arduinoWidthPlacment+arduinoHousingCutoutWidthOffset,_housingBaseThickness])
            {
                cube([_arduinoHousingBaseLength, _arduinoHousingBaseWidth+arduinoHousingCutoutDifferenceFromRoundedMeasure, housingDepth*2]);
                //include the housing lid shape itself for scuplted top cutout
                housingSubModule(_arduinoHousingBaseLength-(_housingBodyRoundingRadius*2), _arduinoHousingBaseWidth-(_housingBodyRoundingRadius*2), housingDepth*2, _arduinoHousingLidBaseThickness, apply_to="z");
            }
        }

        //Arduino/Thumb Wall corner patch
        arduinoCornerWallPatchLength = 1.5;
        arduinoCornerWallPatchWidth = 3;
        arduinoCornerWallPatchDepth = 3;
        arduinoCornerWallPatchLengthPlacement = _arduinoLengthPlacment + arduinoCornerWallPatchLength + 18.1;
        arduinoCornerWallPatchWidthPlacement = _arduinoWidthPlacment - 2;
        arduinoCornerWallPatchDepthPlacement = 2;
        translate([arduinoCornerWallPatchLengthPlacement, arduinoCornerWallPatchWidthPlacement , arduinoCornerWallPatchDepthPlacement])
            cube([arduinoCornerWallPatchLength, arduinoCornerWallPatchWidth, arduinoCornerWallPatchDepth]);

    }
}

module housingSubModule(backplateLength, backplateWidth, housingDepth, baseThickness, apply_to="all")
{
    difference()
    {
        housingLength = backplateLength + (_housingWallThickness*2);
        housingWidth = backplateWidth + (_housingWallThickness*2);
        roundedCube(size = [housingLength, housingWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to=apply_to);

        // Housing body cut out.
        wallThicknessLessToleranceGap = _housingWallThickness-(_housingBackplateCutoutPadding);
        translate([wallThicknessLessToleranceGap, wallThicknessLessToleranceGap, baseThickness])
        {
            roundedCube(size=[backplateLength+(_housingBackplateCutoutPadding*2), backplateWidth+(_housingBackplateCutoutPadding*2), housingDepth], radius=_backplateRoundingRadius, apply_to="zmax");
        }
    }
}

module housingBackplateEdgeSupportSet(supportDepth)
{
    union()
    {
        riserInwardsLengthAdjustment = _arduinoHousingPaddingOffsetAdjustment;
        riserInwardsWidthAdjustment = _arduinoHousingPaddingOffsetAdjustment;
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

module backplateMountingRiserSet(riserHeight, renderNutHoles)
{
    translate([(_key1uLength*1)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight, renderNutHoles);

    translate([(_key1uLength*2)+(_key1_25uLength*1), (_key1uWidth*1)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight, renderNutHoles);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*2)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight, renderNutHoles);

    translate([(_key1uLength*4)+(_key1_25uLength*1), (_key1uWidth*0)+(_key1_25uWidth*1), 0])
        backplateMountingRiser(riserHeight, renderNutHoles);
}

module backplateMountingRiser(riserHeight, renderNutHole)
{
    difference()
    {
        cylinder(r2=_riserTopRadius, r1=_riserBottomRadius, h=riserHeight, $fn=100);
        if (renderNutHole)
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

module arduinoHousing(renderLid)
{
    difference()
    {
        union()
        {
            //arduinoHousingBase();
            if (renderLid)
                translate([0, 0, _arduinoHousingBaseDepth])
                    arduinoHousingTop();
        }
        usbcCutoutLength = 12;
        usbcCutoutWidth = 20;
        usbcCutoutHeight = 7.25;
        usbcCutoutHeightOffset = 3.0;
        usbcCutoutDepth = 7;
        //Cutout for usbc connection
        translate([(_arduinoHousingBaseLength-usbcCutoutLength)/2, _arduinoHousingBaseWidth-usbcCutoutDepth, usbcCutoutHeightOffset])
            cube([usbcCutoutLength, usbcCutoutWidth, usbcCutoutHeight]);
    }
}

module arduinoHousingBase()
{
    union()
    {
        arduinoLengthOffset = _arduinoHousingLengthEdgePadding-_arduinoHousingPaddingOffsetAdjustment;
        arduinoWidthOffset = _arduinoHousingWidthEdgePadding-_arduinoHousingPaddingOffsetAdjustment;
        arduinoInsetIntoHousing = 2;
        difference()
        {
            difference()
            {
                arbitraryDepth = 10;
                housingSubModule(_arduinoHousingBaseLength-(_housingBodyRoundingRadius*2), _arduinoHousingBaseWidth-(_housingBodyRoundingRadius*2), arbitraryDepth, _arduinoHousingBaseDepth);
                translate([0,0,_arduinoHousingBaseDepth])
                    cube([_arduinoHousingBaseLength, _arduinoHousingBaseWidth, arbitraryDepth]);
            }

            // Lid attachement nut set
            translate([_arduinoInsetNutSetLengthOffset,_arduinoInsetNutSetWidthOffset,_arduinoHousingBaseDepth-_arduinoInsetNutCutoutDepth])
                arduinoInsetNutPunchSet();
            // Arduino cutout
            translate([arduinoLengthOffset, arduinoWidthOffset, _arduinoHousingBaseDepth-arduinoInsetIntoHousing])
                arduinoMicroPunch();
            // Cable ramp cutout
            arduinoCableRampAngle = 42;
            translate([-_arduinoHousingBaseDepth*1.5, _arduinoHousingCableCutoutOffset, 0])
                rotate([0, arduinoCableRampAngle, 0])
                    cube([_arduinoHousingBaseDepth, _arduinoHousingCableCutoutWidth, _arduinoHousingBaseDepth*3]);
            translate([_arduinoHousingBaseLength/2, _arduinoInsetNutSetWidthOffset, _arduinoHousingBaseDepth-_arduinoInsetNutCutoutDepth])
                arduinoInsetNutPunch();
        }

        arduinoCenterSupportBeamLength = 8;
        translate([((_arduinoHousingBaseLength-arduinoCenterSupportBeamLength)/2)-_arduinoHousingPaddingOffsetAdjustment, arduinoWidthOffset-1, 0.1])
            cube([arduinoCenterSupportBeamLength, _arduinoMicroBodyWidth+2, _arduinoHousingBaseDepth-1.6]);
        //translate([arduinoLengthOffset, arduinoWidthOffset, _arduinoHousingBaseDepth-arduinoInsetIntoHousing])
        //    arduinoMicroPunch();
    }
}

module arduinoHousingTop()
{
    trrsPortOffsetFromBottom = 6;
    trrsPortOffsetFromRight = _housingWallThickness-_arduinoHousingPaddingOffsetAdjustment;
    trrsPortTotalLengthOffset = _arduinoHousingBaseLength-(_trrsBodyLength)-trrsPortOffsetFromRight;
    trrsPortTotalWidthOffset = trrsPortOffsetFromBottom;

    difference()
    {
        union()
        {
            difference()
            {
                translate([_arduinoHousingBaseLength-1, 0, _arduinoHousingLidHeight])
                    rotate([0, 180, 0])
                        housingSubModule(_arduinoHousingBaseLength-(_housingBodyRoundingRadius*2), _arduinoHousingBaseWidth-(_housingBodyRoundingRadius*2), _arduinoHousingLidHeight, _arduinoHousingLidBaseThickness, apply_to="z");

                // bolt attachements from the top into the housing bottom
                translate([_arduinoInsetNutSetLengthOffset, _arduinoInsetNutSetWidthOffset, _arduinoHousingLidHeight-_arduinoHousingLidBoltCounterSink])
                {
                    translate([0, 0, 0])
                        riserBackplateBoltPunch(_arduinoHousingLidBaseThickness);
                    translate([_arduinoNutInsertLengthCenterToCenter, 0, 0])
                        riserBackplateBoltPunch(_arduinoHousingLidBaseThickness);
                    translate([0, _arduinoNutInsertWidthCenterToCenter, 0])
                        riserBackplateBoltPunch(_arduinoHousingLidBaseThickness);
                    translate([_arduinoNutInsertLengthCenterToCenter, _arduinoNutInsertWidthCenterToCenter, 0])
                        riserBackplateBoltPunch(_arduinoHousingLidBaseThickness);
                }

                // cutout to bring in matrix row/col wires
                arduinoCableCutoutDepth = 1.5;
                translate([-1, _arduinoHousingCableCutoutOffset, -1])
                    cube([_housingWallThickness+2, _arduinoHousingCableCutoutWidth, arduinoCableCutoutDepth+1]);

                //Screen cutout
                oledWidthOffsetFromTop = _oledBodyWidth + 10;
                oledLengthOffset = ((_arduinoHousingBaseLength - _oledBodyLength)/2)-_arduinoHousingPaddingOffsetAdjustment;
                translate([oledLengthOffset, _arduinoHousingBaseWidth-oledWidthOffsetFromTop, _arduinoHousingLidHeight-_arduinoHousingLidBaseThickness-1])
                    oledScreenPunch(_arduinoHousingLidBaseThickness+2);

                // cutout to leave room for the arudino tab connection
                tabCutoutLength = 6;
                tabCutoutWidth = _housingWallThickness + 2;
                tabCutoutDepth = 3;
                translate([(_arduinoHousingBaseLength-tabCutoutLength)/2-_arduinoHousingPaddingOffsetAdjustment, -1, -0.01])
                    cube([tabCutoutLength, tabCutoutWidth, tabCutoutDepth]);
            }

            //TRRS port holder
            union()
            {
                trrsPortWallHeight = _trrsBodyDepth;
                trrsCutoutTolerance = 0.1;
                trrsShimThickness = _trrsWedgeDepth;
                translate([trrsPortTotalLengthOffset-_trrsWallThickness-trrsShimThickness, trrsPortTotalWidthOffset, _arduinoHousingLidHeight-_arduinoHousingLidBaseThickness-trrsPortWallHeight])
                    difference()
                    {
                        cube([_trrsBodyLength+(_trrsWallThickness*2)+trrsShimThickness, _trrsBodyWidth+(_trrsWallThickness*2), trrsPortWallHeight]);
                        translate([_trrsWallThickness-trrsCutoutTolerance, _trrsWallThickness-trrsCutoutTolerance, -1])
                            cube([_trrsBodyLength+trrsCutoutTolerance+trrsShimThickness, _trrsBodyWidth+trrsCutoutTolerance, trrsPortWallHeight+2]);
                    }
            }
        }

        //TRRS port hole punch
        trrsPortCountsinkDepth = 1.5;
        translate([trrsPortTotalLengthOffset-0.1, trrsPortTotalWidthOffset+_trrsWallThickness, _arduinoHousingLidHeight-_arduinoHousingLidBaseThickness-_trrsBodyDepth])
        {
            trrsBodyPunch();
            //TRRS countersink punch
            translate([_trrsBodyLength+trrsPortCountsinkDepth, _trrsBodyWidth/2, _trrsBodyDepth/2])
                rotate([0, 90, 0])
                    cylinder(r=4, h=trrsPortCountsinkDepth+2, $fn=100);
        }
    }
}

module kailhKeyCapTop(length, width, depth)
{
    capInterfaceShankCenterToCenter = 6.25;
    capInterfaceShankWidth = 3.3;
    capInterfaceShankDepth = 1.5;
    capInterfaceShankLength = 1.9;
    totalCapInterfaceLength = capInterfaceShankCenterToCenter+capInterfaceShankLength;

    difference()
    {
        union()
        {
            difference()
            {
                baseCapDepth = 20;
                // form the base cap
                difference()
                {
                    roundedCube(size=[length, width, baseCapDepth], radius = _keyCapRoundingRadius, apply_to="zmin");
                    cutoutCubeSize = [length-(_keyCapWallThickness*2), width-(_keyCapWallThickness*2), baseCapDepth];
                    translate([_keyCapWallThickness, _keyCapWallThickness, _keyCapWallThickness])
                        roundedCube(size=cutoutCubeSize, radius = _keyCapRoundingRadius, apply_to="zmin");
                }
                //cut to the desired depth
                translate([-1,-1,depth])
                    cube([length+2,width+2, baseCapDepth]);
            }

            // bar to thicken shank interface area
            thickeningBarLengthPadding = 3;
            thickeningBarWidthPadding = 6;
            thickeningBarLength = length-thickeningBarLengthPadding*2;
            thickeningBarWidth = width-thickeningBarWidthPadding*2;
            translate([(length-thickeningBarLength)/2, (width-thickeningBarWidth)/2, 0])
                cube([thickeningBarLength, thickeningBarWidth, depth]);
        }

        //cut out the interface for the shank
        translate([(length-totalCapInterfaceLength)/2,(width-capInterfaceShankWidth)/2, depth-capInterfaceShankDepth])
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
    capInterfaceShankLength = 1.5;
    capInterfaceShankWidth = 1.5-printingTolerance;
    capInterfaceShankDepth = switchInterfaceShankDepth-printingTolerance;
    capInterfaceShankCenterToCenter = 6.25;
    shankInterfaceConnectorLength = 1.25;
    shankInterfaceConnectorWidth = 12;
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

module trrsWedgeBlock()
{
    difference()
    //union()
    {
        cube([_trrsWedgeLength, _trrsWedgeWidth, _trrsWedgeDepth]);
        translate([-1, -1, _trrsWedgeDepth/1.75])
            rotate([0, -_trrsWedgeAngle, 0])
                cube([_trrsWedgeLength+2, _trrsWedgeWidth+2, _trrsWedgeDepth+2]);
    }
}

module wristRest()
{
    wristRestDepth = 8;
    pinkyRestLength = (_key1_25uLength*1)+(_key1uLength*0);
    pinkyRestWidth = (_key1_25uWidth*1)+(_key1uWidth*2);
    mainRestLength = (_key1_25uLength*1)+(_key1uLength*3);
    mainRestWidth = (_key1_25uWidth*1)+(_key1uWidth*0)+(_housingWallThickness*1);
    thumbRestLength = (_key1_25uLength*4)+(_key1uLength*3)+(_housingWallThickness*2);
    thumbRestWidth = (_key1_25uWidth*3)+(_key1uWidth*0);

    difference()
    {
        union()
        {
            translate([-_housingWallThickness, -_housingWallThickness*2, 0])
                roundedCube(size=[pinkyRestLength, pinkyRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
            translate([-_housingWallThickness, -_housingWallThickness*2, 0])
                roundedCube(size=[mainRestLength, mainRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
            translate([-_housingWallThickness, -thumbRestWidth-_housingWallThickness, 0])
                roundedCube(size=[thumbRestLength, thumbRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
        }

        //squareCutoutSideLength = _key1uLength;
        //translate([0, -_key1_25uWidth*3, -1])
        //    roundedCube(size=[squareCutoutSideLength, squareCutoutSideLength, wristRestDepth+2], radius=_housingBodyRoundingRadius, apply_to="zall");
        //translate([(_key1_25uLength*4)+(_key1uLength*2), -_key1_25uWidth*3, -1])
        //    roundedCube(size=[squareCutoutSideLength, squareCutoutSideLength, wristRestDepth+2], radius=_housingBodyRoundingRadius, apply_to="zall");
    }
}

//Punches
module arduinoMicroPunch()
{
    arduinoMicroBodyLength = _arduinoMicroBodyLength;
    arduinoMicroBodyWidth = _arduinoMicroBodyWidth;
    arduinoMicroBodyDepth = 2.6;

    usbCPortLength = 9.1;
    usbCPortWidth = 7.5 + 10; //plus an extention for hole punching
    usbCPortDepth = 3.2;
    usbCDepthCutInToBody = 0.4;

    usbCOnBoardWidth = 5.5;
    usbCPortOverhang = 2;

    union()
    {
        cube([arduinoMicroBodyLength, arduinoMicroBodyWidth, arduinoMicroBodyDepth]);

        translate([(arduinoMicroBodyLength-usbCPortLength)/2, arduinoMicroBodyWidth-(usbCOnBoardWidth), arduinoMicroBodyDepth-usbCDepthCutInToBody])
        {
            cube([usbCPortLength, usbCPortWidth, usbCPortDepth]);
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

module oledScreenPunch(depth)
{
    union()
    {
        //bolt cutouts
        translate([_oledBoltAttachmentLengthOffset, _oledBoltAttachmentWidthOffset, 0])
        {
            translate([0, 0, 0])
                cylinder(r=_m2BoltHoleRadius, h=depth, $fn=100);
            translate([0, _oledAttachmentHolesCentertoCenter, 0])
                cylinder(r=_m2BoltHoleRadius, h=depth, $fn=100);
            translate([_oledAttachmentHolesCentertoCenter, 0, 0])
                cylinder(r=_m2BoltHoleRadius, h=depth, $fn=100);
            translate([_oledAttachmentHolesCentertoCenter, _oledAttachmentHolesCentertoCenter, 0])
                cylinder(r=_m2BoltHoleRadius, h=depth, $fn=100);
        }

        //screen cutout
        translate([_oledScreenWidthOffsetFromLeft, _oledScreenWidth-_oledScreenLengthOffsetFromTop, 0])
            cube([_oledScreenLength, _oledScreenWidth, depth]);
    }
}

module trrsBodyPunch()
{
    union()
    {
        trrsConnectorTolerance = 0.1;
        trrsConnectorDepth = 2 + 6; //plus punch length
        cube([_trrsBodyLength, _trrsBodyWidth, _trrsBodyDepth]);
        translate([_trrsBodyLength, _trrsBodyWidth/2, _trrsBodyDepth/2])
            rotate([0, 90, 0])
                cylinder(r=(_trrsBodyDepth/2)+trrsConnectorTolerance,h=trrsConnectorDepth, $fn=100);
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
