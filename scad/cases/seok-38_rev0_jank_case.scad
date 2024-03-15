linear_extrude(2.5)
minkowski()
{
import("seok-38_Mk1_rev0-Edge_Cuts.svg");
circle(r=2);
}

//translate([36.25, 34, 0])
linear_extrude(3.5)
import("seok-38_Mk1_rev0-User_1.svg");
