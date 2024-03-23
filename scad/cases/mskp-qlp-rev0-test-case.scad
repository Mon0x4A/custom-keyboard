_is_left_side = false;

_basePlateThickness = 4;
_basePlateWallThickness = 5.5;

if (_is_left_side)
{
    //Keypad
    linear_extrude(_basePlateThickness)
    minkowski()
    {
    import("qlp-22_mx_hs_keypad_L_Mk1_rev0-Edge_Cuts.svg");
    circle(r=2);
    }

    linear_extrude(_basePlateWallThickness)
    import("qlp-22_mx_hs_keypad_L_Mk1_rev0-User_1.svg");


    //Keypad/Control connection
    translate([120, 36, 0])
    cube([40, 35, _basePlateThickness]);

    //Control board
    translate([145, 28, 0])
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
}
else
{
    //Keypad
    linear_extrude(_basePlateThickness)
    minkowski()
    {
    import("qlp-22_mx_hs_keypad_R_Mk1_rev0-Edge_Cuts.svg");
    circle(r=2);
    }

    linear_extrude(_basePlateWallThickness)
    import("qlp-22_mx_hs_keypad_R_Mk1_rev0-User_1.svg");


    //Keypad/Control connection
    translate([-2, 36, 0])
    cube([40, 35, _basePlateThickness]);

    //Control board
    translate([-39, 34, 0])
    union()
    {
        linear_extrude(_basePlateThickness)
        minkowski()
        {
        import("io_ctrl_board_secondary_Mk1_rev0-Edge_Cuts.svg");
        circle(r=2);
        }

        linear_extrude(_basePlateWallThickness)
        import("io_ctrl_board_secondary_Mk1_rev0-User_1.svg");
    }
}

////Keypad/Palm connection
//translate([50, 37, 0])
//cube([20, 35, _basePlateThickness]);
//
////Palm rest
//translate([50, -10, 0])
//{
//    difference()
//    {
//        translate([0, 0, 10])
//            rotate([0, 0, 180])
//                import("datahand-palm-rest.stl");
//        //TODO cut out mounting holes and countersinks
//    }
//
//    translate([2, 0, 0])
//        linear_extrude(_basePlateThickness)
//        minkowski()
//        {
//            square([60, 90], center=true);
//            circle(r=2);
//        }
//}
