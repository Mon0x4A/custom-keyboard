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

_keySwitchCutoutLength = 13.86;
_keySwitchCutoutWidth = 13.86;

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

_insetNutCutoutDiameter = 3.2;
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

//Pico Variables
_picoBodySizePadding = 0.4;
_picoBodyLength = 21 + _picoBodySizePadding;
_picoBodyWidth = 51 + _picoBodySizePadding;
_picoBodyDepth = 1;

_picoHousingLengthEdgePadding = 7;
_picoHousingWidthEdgePadding = 3.5;
_picoHousingBaseLength = _picoBodyLength + (_picoHousingLengthEdgePadding*2);
_picoHousingBaseWidth = _picoBodyWidth + (_picoHousingWidthEdgePadding*2);
_picoHousingBaseDepth = 6.5;
_picoHousingLidHeight = 10;
_picoHousingLidBoltCounterSink = 0;
_picoHousingLidBaseThickness = 2;
_picoHousingCableCutoutWidth = _picoHousingBaseWidth*(3/5);
_picoHousingCableCutoutOffset = _picoHousingBaseWidth*(1/5);
_picoHousingPaddingOffsetAdjustment = 0.25;

_picoIntraHousingLengthOffset = _picoHousingLengthEdgePadding-_picoHousingPaddingOffsetAdjustment;
_picoIntraHousingWidthOffset = _picoHousingWidthEdgePadding-_picoHousingPaddingOffsetAdjustment;
_picoInsetIntoHousing = 0.9;

_picoMountingHolesLengthCenterToCenter = 11.4;
_picoMountingHolesWidthCenterToCenter = 47;
_picoMountingStudWallThickess = 1.5;
_picoMountingStudHeight = 3;
_picoMountingStudInsetDepth = 3;

_picoCutoutDepth = 2;
_picoCenterSupportBeamLength = 8;
_picoCenterSupportBeamOffsetFromBottom = 2;
_picoCenterSupportBeamOffsetFromTop = 1.1;

_picoInsetNutCutoutDepth = 3;
_picoNutInsertLengthCenterToCenter = 27;
_picoNutInsertWidthCenterToCenter = 47;
_picoNutSetOffsetAdjustment = -0.25;
_picoInsetNutSetLengthOffset = ((_picoHousingBaseLength-_picoNutInsertLengthCenterToCenter)/2)+_picoNutSetOffsetAdjustment;
_picoInsetNutSetWidthOffset = ((_picoHousingBaseWidth-_picoNutInsertWidthCenterToCenter)/2)+_picoNutSetOffsetAdjustment;

_picoLengthPlacment = _key1uWidth*(6)+1.3;
_picoWidthPlacment = 24.5;

/// MAIN START ///

// Comment in this mirror statement to make any right-hand parts.
//mirror([1,0,0])

keyboard(KAILH_SWITCH_TYPE, isLeftSide=true);
//wristRest();
//housing(_kailhHousingBodyDepth);
//backplate(_kailhBackplateDepth);
//oledScreenPunch(_picoHousingLidBaseThickness+2);
//oledScreenPlateCover(depth=1.5);
//oledScreenFrame();
//picoModel();
//trrsBodyPunch();
//trrsWedgeBlock();
//picoMountingStudSet(_picoMountingStudHeight,_picoMountingStudInsetDepth);
//picoMountingStud(_picoMountingStudHeight,_picoMountingStudInsetDepth);
//picoMountingNutPunchSet();
//picoHousing(renderLid=true, renderBase=false, renderPico=false);
//picoHousingBase();
//picoHousingTop();
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
                //pico enclosure
                translate([_picoLengthPlacment,_picoWidthPlacment,0])
                    union()
                    {
                        picoHousing(renderLid=true, renderBase=true, renderPico=false);
                        picoHousingBodyJointWidth = 64.40;
                        picoHousingBodyJointLength = 28.70;
                        picoHousingBodyJointDepth = 2;
                        jointLengthOffset = -7;
                        jointWidthOffset = -7;
                        // Smoothing for joint seam.
                        translate([jointLengthOffset, jointWidthOffset, 0])
                            difference()
                            {
                                roundedCube(size=[picoHousingBodyJointLength, picoHousingBodyJointWidth, housingDepth], radius=_housingBodyRoundingRadius, apply_to="all");
                                cutoutEdgePadding = 5;
                                translate([-cutoutEdgePadding,-cutoutEdgePadding, picoHousingBodyJointDepth])
                                    cube([picoHousingBodyJointLength+(cutoutEdgePadding*2), picoHousingBodyJointWidth+(cutoutEdgePadding*2), housingDepth]);
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
                // Hide the joint between the pink and main bodies
                additionPinkyHousingLengthToHideRearSeam = 1;

                // Pink housing body
                translate([0,_key1uWidth*(3),0])
                    translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                        housingSubModule(_pinkyBackplateLength+additionPinkyHousingLengthToHideRearSeam, _pinkyBackplateWidth, housingDepth, _housingBaseThickness);
                // Main housing body.
                translate([_key1_25uLength*(1),_key1_25uWidth*(1),0])
                    translate([-_housingWallThickness,-_housingWallThickness,0]) // Zero on origin
                        housingSubModule(_mainBackplateLength, _mainBackplateWidth, housingDepth, _housingBaseThickness);
                // Thumb housing body.
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

            // pico-adjacent wall cutouts
            picoHousingCutoutWidthOffset = -0.1;
            picoHousingCutoutLengthOffset = -0.6;
            // reduce the width here so we can get the round joint at the top
            picoHousingCutoutDifferenceFromRoundedMeasure = -3.1;
            picoHousingCutoutExtraLength = 2;
            translate([_picoLengthPlacment+picoHousingCutoutLengthOffset,_picoWidthPlacment+picoHousingCutoutWidthOffset,_housingBaseThickness])
            {
                cube([_picoHousingBaseLength, _picoHousingBaseWidth+picoHousingCutoutDifferenceFromRoundedMeasure, housingDepth*2]);
                //include the housing lid shape itself for scuplted top cutout
                housingSubModule(_picoHousingBaseLength-(_housingBodyRoundingRadius*2), _picoHousingBaseWidth-(_housingBodyRoundingRadius*2), housingDepth*2, _picoHousingLidBaseThickness, apply_to="z");
            }
        }

        //pico/Thumb Wall corner patch
        picoCornerWallPatchLength = 1.5;
        picoCornerWallPatchWidth = 3;
        picoCornerWallPatchDepth = 3;
        picoCornerWallPatchLengthPlacement = _picoLengthPlacment + picoCornerWallPatchLength + 18.1;
        picoCornerWallPatchWidthPlacement = _picoWidthPlacment - 2;
        picoCornerWallPatchDepthPlacement = 2;
        translate([picoCornerWallPatchLengthPlacement, picoCornerWallPatchWidthPlacement , picoCornerWallPatchDepthPlacement])
            cube([picoCornerWallPatchLength, picoCornerWallPatchWidth, picoCornerWallPatchDepth]);

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
        riserInwardsLengthAdjustment = _picoHousingPaddingOffsetAdjustment;
        riserInwardsWidthAdjustment = _picoHousingPaddingOffsetAdjustment;
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

        //Main pico side
        translate([_key1_25uLength*(3)+_key1uLength*(3)-riserInwardsLengthAdjustment,_key1_25uWidth*(1)+_key1uWidth*(1.5)-(_housingStraightSupportLength*(3/4)),_housingBaseThickness])
            rotate([0, 0, 0])
                housingStraightSupport(supportDepth);

        //Thumb bottom
        translate([_key1_25uLength*(3)+_key1uLength*(2.5)-_housingStraightSupportLength,riserInwardsWidthAdjustment,_housingBaseThickness])
            rotate([0, 0, -90])
                housingStraightSupport(supportDepth);

        //Thumb top pico side
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

module picoHousing(renderLid, renderBase, renderPico)
{
    union()
    {
        difference()
        {
            union()
            {
                if (renderBase)
                    picoHousingBase();
                if (renderLid)
                    translate([0, 0, _picoHousingBaseDepth])
                        picoHousingTop();
            }
            usbcCutoutLength = 12;
            usbcCutoutWidth = 20;
            usbcCutoutHeight = 7.25;
            usbcCutoutHeightOffset = 3.0;
            usbcCutoutDepth = 3.76;
            //Cutout for usb connection
            translate([((_picoHousingBaseLength-usbcCutoutLength)/2)-_picoHousingPaddingOffsetAdjustment, _picoHousingBaseWidth-usbcCutoutDepth, usbcCutoutHeightOffset])
                cube([usbcCutoutLength, usbcCutoutWidth, usbcCutoutHeight]);

            translate([((_picoHousingBaseLength-_picoMountingHolesLengthCenterToCenter)/2)-_picoHousingPaddingOffsetAdjustment, ((_picoHousingBaseWidth-_picoMountingHolesWidthCenterToCenter)/2)-_picoHousingPaddingOffsetAdjustment, _picoHousingBaseDepth-_picoMountingStudHeight-_picoCenterSupportBeamOffsetFromTop])
                picoMountingStudSet(_picoMountingStudHeight,0);
        }

        if(renderPico)
            translate([_picoIntraHousingLengthOffset, _picoIntraHousingWidthOffset, _picoHousingBaseDepth-_picoInsetIntoHousing])
                picoModel();

        if (renderBase)
            translate([((_picoHousingBaseLength-_picoMountingHolesLengthCenterToCenter)/2)-_picoHousingPaddingOffsetAdjustment, ((_picoHousingBaseWidth-_picoMountingHolesWidthCenterToCenter)/2)-_picoHousingPaddingOffsetAdjustment, _picoHousingBaseDepth-_picoMountingStudHeight-_picoCenterSupportBeamOffsetFromTop])
                picoMountingStudSet(_picoMountingStudHeight,_picoMountingStudInsetDepth);
    }
}

module picoHousingBase()
{
    union()
    {
        difference()
        {
            difference()
            {
                arbitraryDepth = 10;
                housingSubModule(_picoHousingBaseLength-(_housingBodyRoundingRadius*2), _picoHousingBaseWidth-(_housingBodyRoundingRadius*2), arbitraryDepth, _picoHousingBaseDepth);
                translate([0,0,_picoHousingBaseDepth])
                    cube([_picoHousingBaseLength, _picoHousingBaseWidth, arbitraryDepth]);
            }

            // Lid attachement nut set
            translate([_picoInsetNutSetLengthOffset,_picoInsetNutSetWidthOffset,_picoHousingBaseDepth-_picoInsetNutCutoutDepth])
                lidAttachmentNutPunchSet();
            // Pico cutout
            translate([_picoIntraHousingLengthOffset, _picoIntraHousingWidthOffset, _picoHousingBaseDepth-_picoCutoutDepth])
                picoPunch(_picoCutoutDepth+1);
            // Cable ramp cutout
            picoCableRampAngle = 42;
            translate([-_picoHousingBaseDepth*1.5, _picoHousingCableCutoutOffset, 0])
                rotate([0, picoCableRampAngle, 0])
                    cube([_picoHousingBaseDepth, _picoHousingCableCutoutWidth, _picoHousingBaseDepth*3]);
        }

        translate([((_picoHousingBaseLength-_picoCenterSupportBeamLength)/2)-_picoHousingPaddingOffsetAdjustment, _picoIntraHousingWidthOffset-1, _picoCenterSupportBeamOffsetFromBottom])
            cube([_picoCenterSupportBeamLength, _picoBodyWidth+2, _picoHousingBaseDepth-_picoCenterSupportBeamOffsetFromTop-_picoCenterSupportBeamOffsetFromBottom]);
    }
}

module picoMountingStudSet(height, insertDepth)
{
    translate([0,0,0])
        picoMountingStud(height, insertDepth);
    translate([_picoMountingHolesLengthCenterToCenter,0,0])
        picoMountingStud(height, insertDepth);
    translate([0,_picoMountingHolesWidthCenterToCenter,0])
        picoMountingStud(height, insertDepth);
    translate([_picoMountingHolesLengthCenterToCenter,_picoMountingHolesWidthCenterToCenter,0])
        picoMountingStud(height, insertDepth);
}

module picoMountingStud(height, insertDepth)
{
    difference()
    {
        cylinder(r=_insetNutCutoutRadius+_picoMountingStudWallThickess, h=height, $fn=100);
        translate([0, 0, height-insertDepth])
            picoMountNutPunch();
    }
}

module picoHousingTop()
{
    trrsPortOffsetFromBottom = 7.5;
    trrsPortOffsetFromRight = _housingWallThickness-_picoHousingPaddingOffsetAdjustment;
    trrsPortTotalLengthOffset = _picoHousingBaseLength-(_trrsBodyLength)-trrsPortOffsetFromRight;
    trrsPortTotalWidthOffset = trrsPortOffsetFromBottom;

    difference()
    {
        union()
        {
            difference()
            {
                translate([_picoHousingBaseLength-1, 0, _picoHousingLidHeight])
                    rotate([0, 180, 0])
                        housingSubModule(_picoHousingBaseLength-(_housingBodyRoundingRadius*2), _picoHousingBaseWidth-(_housingBodyRoundingRadius*2), _picoHousingLidHeight, _picoHousingLidBaseThickness, apply_to="z");

                // bolt attachements from the top into the housing bottom
                translate([_picoInsetNutSetLengthOffset-_picoHousingPaddingOffsetAdjustment, _picoInsetNutSetWidthOffset, _picoHousingLidHeight-_picoHousingLidBoltCounterSink])
                {
                    translate([0, 0, 0])
                        riserBackplateBoltPunch(_picoHousingLidBaseThickness);
                    translate([_picoNutInsertLengthCenterToCenter, 0, 0])
                        riserBackplateBoltPunch(_picoHousingLidBaseThickness);
                    translate([0, _picoNutInsertWidthCenterToCenter, 0])
                        riserBackplateBoltPunch(_picoHousingLidBaseThickness);
                    translate([_picoNutInsertLengthCenterToCenter, _picoNutInsertWidthCenterToCenter, 0])
                        riserBackplateBoltPunch(_picoHousingLidBaseThickness);
                }

                // cutout to bring in matrix row/col wires
                picoCableCutoutDepth = 1.5;
                translate([-1, _picoHousingCableCutoutOffset, -1])
                    cube([_housingWallThickness+2, _picoHousingCableCutoutWidth, picoCableCutoutDepth+1]);

                //Screen cutout
                oledWidthOffsetFromTop = _oledBodyWidth + 10;
                oledLengthOffset = ((_picoHousingBaseLength - _oledBodyLength)/2)-_picoHousingPaddingOffsetAdjustment;
                translate([oledLengthOffset, _picoHousingBaseWidth-oledWidthOffsetFromTop, _picoHousingLidHeight-_picoHousingLidBaseThickness-1])
                    oledScreenPunch(_picoHousingLidBaseThickness+2);
            }

            //TRRS port holder
            union()
            {
                trrsPortWallHeight = _trrsBodyDepth;
                trrsCutoutTolerance = 0.1;
                trrsShimThickness = _trrsWedgeDepth;
                translate([trrsPortTotalLengthOffset-_trrsWallThickness-trrsShimThickness, trrsPortTotalWidthOffset, _picoHousingLidHeight-_picoHousingLidBaseThickness-trrsPortWallHeight])
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
        translate([trrsPortTotalLengthOffset-0.1, trrsPortTotalWidthOffset+_trrsWallThickness, _picoHousingLidHeight-_picoHousingLidBaseThickness-_trrsBodyDepth])
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
    pinkyRestWidth = (_key1_25uWidth*1)+(_key1uWidth*2)+(_housingWallThickness*2);
    mainRestLength = (_key1_25uLength*1)+(_key1uLength*3);
    mainRestWidth = (_key1_25uWidth*1)+(_key1uWidth*0)+(_housingWallThickness*1);
    thumbRestLength = (_key1_25uLength*4)+(_key1uLength*3)+(_housingWallThickness*2);
    thumbRestWidth = (_key1_25uWidth*3)+(_key1uWidth*1);

    difference()
    {
        union()
        {
            translate([-_housingWallThickness, -_housingWallThickness*4, 0])
                roundedCube(size=[pinkyRestLength, pinkyRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
            translate([-_housingWallThickness, -_housingWallThickness*2, 0])
                roundedCube(size=[mainRestLength, mainRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
            translate([-_housingWallThickness, -thumbRestWidth-_housingWallThickness, 0])
                roundedCube(size=[thumbRestLength, thumbRestWidth, wristRestDepth], radius=_housingBodyRoundingRadius, apply_to="zall");
        }

        // Cutout idea, but it won't work on the outside of the rest because it interferes
        // with the palm placement and stability.
        //squareCutoutSideLength = _key1uLength;
        //restCutoutPadding = _housingWallThickness;
        //translate([0, -(_key1_25uWidth*3)-(_key1uWidth*1), -1])
        //    roundedCube(size=[squareCutoutSideLength, squareCutoutSideLength, wristRestDepth+2], radius=_housingBodyRoundingRadius, apply_to="zall");
        //translate([0, -(_key1_25uWidth*3)+restCutoutPadding, -1])
        //    roundedCube(size=[squareCutoutSideLength/2, squareCutoutSideLength/2, wristRestDepth+2], radius=_housingBodyRoundingRadius/1.5, apply_to="zall");
        //translate([(_key1uLength*1)+restCutoutPadding, -(_key1_25uWidth*3)-(_key1uWidth*1), -1])
        //    roundedCube(size=[squareCutoutSideLength/2, squareCutoutSideLength/2, wristRestDepth+2], radius=_housingBodyRoundingRadius/1.5, apply_to="zall");
    }
}

module oledScreenPlateCover(depth, includeScreenCutout=false)
{
    difference()
    {
        cube([_oledBodyLength, _oledBodyWidth, depth]);
        translate([_picoHousingPaddingOffsetAdjustment, 0, -1])
            oledScreenPunch(depth+2, includeScreenCutout);
    }
}

module oledScreenFrame()
{
    union()
    {
        frameDepth = 1.5;
        oledScreenPlateCover(frameDepth, includeScreenCutout=true);
        difference()
        {
            extraPadding = 1.5;
            translate([-extraPadding, -extraPadding, 0])
                roundedCube(size = [_oledBodyLength+(extraPadding*2), _oledBodyWidth+(extraPadding*2), frameDepth], radius=0.75, apply_to="zall");
            translate([0, 0, -1])
                cube([_oledBodyLength, _oledBodyWidth, frameDepth+2]);
        }
    }
}

module picoModel()
{
    translate([_picoBodyLength/2, _picoBodyWidth/2, _picoBodyDepth/2])
        rotate([90, 0, 0])
            import("../resources/stl/Raspberry-Pi-Pico-R3.stl");
}

//Punches
module picoPunch(depth)
{
    union()
    {
        cube([_picoBodyLength, _picoBodyWidth, depth]);
    }
}

module lidAttachmentNutPunchSet()
{
    translate([0,0,0])
        lidAttachmentNutPunch();
    translate([_picoNutInsertLengthCenterToCenter,0,0])
        lidAttachmentNutPunch();
    translate([0,_picoNutInsertWidthCenterToCenter,0])
        lidAttachmentNutPunch();
    translate([_picoNutInsertLengthCenterToCenter,_picoNutInsertWidthCenterToCenter,0])
        lidAttachmentNutPunch();
}

module lidAttachmentNutPunch()
{
    union()
    {
        cylinder(r=_insetNutCutoutRadius,h=_picoInsetNutCutoutDepth+1,$fn=100);
    }
}

module picoMountingNutPunchSet()
{
    translate([0,0,0])
        picoMountNutPunch();
    translate([_picoMountingHolesLengthCenterToCenter,0,0])
        picoMountNutPunch();
    translate([0,_picoMountingHolesWidthCenterToCenter,0])
        picoMountNutPunch();
    translate([_picoMountingHolesLengthCenterToCenter,_picoMountingHolesWidthCenterToCenter,0])
        picoMountNutPunch();
}

module picoMountNutPunch()
{
    union()
    {
        cylinder(r=_insetNutCutoutRadius,h=_picoInsetNutCutoutDepth+1,$fn=100);
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

module oledScreenPunch(depth, includeScreenCutout=true)
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
        if (includeScreenCutout)
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
