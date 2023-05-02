
_trackballDiameter = 40;
_trackballRadius = _trackballDiameter/2;

_trackballHousingInnerDiameter = 48;
_trackballHousingInnerRadius = _trackballHousingInnerDiameter/2;
_trackballHousingWallThickness = 5;
_trackballHousingOuterDiameter = _trackballHousingInnerDiameter+(_trackballHousingWallThickness*2);
_trackballHousingOuterRadius = _trackballHousingOuterDiameter/2;
_trackballHousingHeight = 15;
_trackballHousingCutoutOffsetFromBottom = 10;

_trackballBaseWallThickness = 7;
_trackballBaseSideLength = _trackballHousingOuterRadius + (_trackballBaseWallThickness*2);
_trackballBaseDepth = 5;
_trackballBaseCutoutSideLength = _trackballBaseSideLength - (_trackballBaseWallThickness*2);

_btuHousingDepth = 9 + 0.3 + _trackballHousingWallThickness; //plus padding for cutout
_btuHousingDiameter = 12.7 + 0.3; //plus padding for cutout
_btuHousingRadius = _btuHousingDiameter/2;
_btuFlangeDiameter = 14.8 + 0.3; //plus padding for cutout
_btuFlangeRadius = _btuFlangeDiameter/2;
_btuFlangeDepth = 3.8;
_btuBallBearingDiameter = 8;
_btuBallBearingRadius = _btuBallBearingDiameter/2;
_btuBallBearingExposure = 1.2;

_btuCutoutAngle = 58;
_btuCutoutOffset = _trackballHousingInnerRadius+_trackballHousingWallThickness;
_btuCutoutDepthOffset = 1;

/// MAIN START ///

macropad();
//btu();

/// MAIN END ///

//Bodies
module macropad()
{
    trackball();
}

module trackball()
{
    union()
    {
        trackballBallDepthOffset = 20;
        //translate([0, 0, trackballBallDepthOffset])
        //    ball();

        difference()
        //union()
        {
            trackballHousing();
            translate([0, _btuCutoutOffset, _btuCutoutDepthOffset])
                rotate([_btuCutoutAngle, 0, 0])
                    btu();
            rotate([0, 0, 120])
                translate([0, _btuCutoutOffset, _btuCutoutDepthOffset])
                    rotate([_btuCutoutAngle, 0, 0])
                        btu();
            rotate([0, 0, -120])
                translate([0, _btuCutoutOffset, _btuCutoutDepthOffset])
                    rotate([_btuCutoutAngle, 0, 0])
                        btu();
        }
    }
}

module trackballHousing()
{
    union()
    {
        translate([0, 0, _trackballHousingOuterRadius-_trackballHousingCutoutOffsetFromBottom])
            difference()
            //union()
            {
                translate([0, 0, 0])
                    sphere(r=_trackballHousingOuterRadius, $fn=100);
                // Cut out the center.
                translate([0, 0, 0])
                    sphere(r=_trackballHousingInnerRadius, $fn=100);
                // Cut out the bottom.
                translate([0, 0, _trackballHousingCutoutOffsetFromBottom])
                    translate([-_trackballHousingOuterDiameter/2, -_trackballHousingOuterDiameter/2, -_trackballHousingOuterDiameter-(_trackballHousingOuterDiameter/2)])
                        cube([_trackballHousingOuterDiameter+2, _trackballHousingOuterDiameter+2, _trackballHousingOuterDiameter]);
                // Cut out the bottom.
                translate([0, 0, -_trackballHousingOuterDiameter+_trackballHousingCutoutOffsetFromBottom+_trackballHousingHeight])
                    translate([-_trackballHousingOuterDiameter/2, -_trackballHousingOuterDiameter/2, _trackballHousingOuterDiameter/2])
                        cube([_trackballHousingOuterDiameter+2, _trackballHousingOuterDiameter+2, _trackballHousingOuterDiameter]);
            }

        //Trackball base
        translate([0, 0, -_trackballBaseDepth])
            difference()
            {
                baseRadius = 21.89;
                cylinder(r=baseRadius, h=_trackballBaseDepth, $fn=100);
                translate([0, 0, -1])
                    cylinder(r=baseRadius-_trackballBaseWallThickness, h=_trackballBaseDepth+2, $fn=100);
            }

        //translate([-_trackballBaseSideLength/2, -_trackballBaseSideLength/2, -_trackballBaseDepth])
        //    difference()
        //    {
        //        cube([_trackballBaseSideLength, _trackballBaseSideLength, _trackballBaseDepth]);
        //        translate([_trackballBaseWallThickness, _trackballBaseWallThickness, -1])
        //            cube([_trackballBaseCutoutSideLength, _trackballBaseCutoutSideLength, _trackballBaseDepth+2]);
        //    }
    }
}

module btu()
{
    union()
    {
        cylinder(r=_btuHousingRadius, h=_btuHousingDepth, $fn=100);
        translate([0, 0, _btuHousingDepth-_btuFlangeDepth])
            cylinder(r=_btuFlangeRadius, h=_btuFlangeDepth, $fn=100);
        translate([0, 0, _btuHousingDepth-_btuBallBearingRadius+_btuBallBearingExposure])
            sphere(r=_btuBallBearingRadius, $fn=100);
    }
}

module ball()
{
    union()
    {
        sphere(r=_trackballRadius, $fn=100);
    }
}
