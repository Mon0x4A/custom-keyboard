_edgeCutCorrectionOffset=-2.5;
_caseWallDepth=20;
_backplateCountersink=5;
_caseWallThickness=4;
_backplateThickness=5;

translate([_edgeCutCorrectionOffset,0,_caseWallDepth-(_caseWallThickness/2)])
linear_extrude(height=_caseWallThickness)
import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill_backplate_hole.svg");


translate([_edgeCutCorrectionOffset, 0, _caseWallDepth-(_caseWallThickness*2)])
difference()
{
    linear_extrude(height=_backplateThickness)
    import("lpk20_mx_keypad_L_Mk1_rev0-Edge_Cuts_fill.svg");

    translate([0, 0, -1])
    linear_extrude(height=_backplateThickness+2)
    import("lpk20_mx_keypad_L_Mk1_rev0-User_1.svg");
}

//Case bottom
//linear_extrude(height=_caseWallThickness)
//import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");

//Case top
translate([0, 0, _caseWallDepth-(_caseWallThickness)])
difference()
{
    linear_extrude(height=_caseWallThickness)
    import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");

    translate([_edgeCutCorrectionOffset, 0, -1])
    linear_extrude(height=_caseWallThickness+2)
    import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill.svg");
}

translate([_edgeCutCorrectionOffset, 0, 0])
linear_extrude(height=_caseWallDepth)
minkowski()
{
    circle(r=_caseWallThickness/2,$fn=100);
    import("lpk20_mx_keypad_L_Mk1_rev0-User_2.svg");
}