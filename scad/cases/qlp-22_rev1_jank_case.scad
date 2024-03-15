linear_extrude(2.5)
minkowski()
{
import("qlp-22_Mk1_rev1-Edge_Cuts.svg");
circle(r=2);
}

translate([36.25, 34, 0])
linear_extrude(3.5)
import("qlp-22_Mk1_rev1-User_1.svg");

