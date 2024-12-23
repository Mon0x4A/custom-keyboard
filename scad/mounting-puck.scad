//NOTE: This is the diagonal center to center distance.
_puckCenterToCenterDist = 63;

_armWidth = 10;
_armLength = _puckCenterToCenterDist;
_armDepth = 6;

_armPassthroughCutoutRadius = 1.75;

_centerRadius = 12;
_centerDepth = 11;
_centerNutCutoutRadius = 3.95;

///MAIN
puck();

module puck()
{
    union()
    {
        difference()
        {
            translate([-_armLength/2, -_armWidth/2, 0])
                union()
                {
                    arm();
                    translate([(_armLength/2)+(_armWidth/2), (-_armLength/2)+_armWidth/2, 0])
                    rotate([0, 0, 90])
                    arm();
                }

            translate([0, 0, -1])
                cylinder(r=_centerRadius, h=_centerDepth, $fn=100);
        }

        center();
    }
}

module arm()
{

difference()
{
    union()
    {
        translate([0, _armWidth/2, 0])
        cylinder(r=_armWidth/2, h=_armDepth, $fn=100);
        cube([_armLength, _armWidth, _armDepth]);
        translate([_armLength, _armWidth/2, 0])
        cylinder(r=_armWidth/2, h=_armDepth, $fn=100);
    }
    translate([0, _armWidth/2, -1])
    cylinder(r=_armPassthroughCutoutRadius, h=_armDepth+2, $fn=100);
    translate([_armLength, _armWidth/2, -1])
    cylinder(r=_armPassthroughCutoutRadius, h=_armDepth+2, $fn=100);
}


}

module center()
{
    difference()
    {
        cylinder(r=_centerRadius, h=_centerDepth, $fn=100);
        translate([0, 0, -1])
            cylinder(r=_centerNutCutoutRadius, h=_centerDepth+2, $fn=100);
    }
}
