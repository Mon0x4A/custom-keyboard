_basePlateThickness = 3.5;
linear_extrude(_basePlateThickness)
minkowski()
{
import("qlp-22_mx_hs_keypad_L_Mk1_rev0-Edge_Cuts.svg");
circle(r=2);
}

_basePlateWallThickness = 5.5;
linear_extrude(_basePlateWallThickness)
import("qlp-22_mx_hs_keypad_L_Mk1_rev0-User_1.svg");


translate([120, 38, 0])
union()
{
    linear_extrude(_basePlateThickness)
    minkowski()
    {
    import("pico_ctrl_board_primary_Mk1_rev0-Edge_Cuts.svg");
    circle(r=2);
    }

    linear_extrude(_basePlateWallThickness)
    import("pico_ctrl_board_primary_Mk1_rev0-User_1.svg");
}
