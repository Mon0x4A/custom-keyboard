_edgeCutCorrectionOffset=-2.5;
_caseWallDepth=20;
_backplateCountersink=5;
_caseWallThickness=3.5;
_baseThickness=5;
_backplateThickness=5;
_backplateSupportDepth=9;
_backplateSupportThickness=2;
_mountingPointThickness=4;

_controlBoardMountWidthOffset = 37;
_controlBoardMountLengthOffset = 82.5;
_switchBoardMountWidthOffset = 81;
_switchBoardMountLengthOffset = -6;
_mouseBoardMountWidthOffset = 55;
_mouseBoardMountLengthOffset = 34;

_mountingPuckLengthOffset = 80;
_mountingPuckWidthOffset = 40;
_mountingPuckPunchRadius = 1.95;

_usbcCutoutLength = 0;
_usbcCutoutWidth = 0;
_usbcCutoutDepth = 0;

_ethernetCutoutLength = 0;
_ethernetCutoutWidth = 0;
_ethernetCutoutDepth = 0;

_microUsbWallCutoutLength = 0;
_microUsbWallCutoutWidth = 2;
_microUsbWallCutoutDepth = 0;

//Top rim
//translate([_edgeCutCorrectionOffset,0,_caseWallDepth-(_caseWallThickness/2)])
//linear_extrude(height=_caseWallThickness)
//import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill_backplate_hole.svg");

//Backplate
//translate([_edgeCutCorrectionOffset, 1, _caseWallDepth-(_caseWallThickness*2)])
//difference()
//{
//    linear_extrude(height=_backplateThickness)
//    import("lpk20_mx_keypad_L_Mk1_rev0-Edge_Cuts_fill.svg");
//
//    translate([0, 0, -1])
//    linear_extrude(height=_backplateThickness+2)
//    import("lpk20_mx_keypad_L_Mk1_rev0-User_1.svg");
//}

//Case bottom
union()
{
    difference()
    //union()
    {
        linear_extrude(height=_baseThickness)
        import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");

        translate([_mountingPuckLengthOffset, _mountingPuckWidthOffset, -1])
        rotate([0, 0, 45])
        mountingPuckPunch(_baseThickness+2, _mountingPuckPunchRadius);
    }
    //TODO difference out the top attachment

    //Keypad mounts
    translate([_edgeCutCorrectionOffset, 0, _baseThickness])
    difference()
    {
        linear_extrude(height=_mountingPointThickness)
        import("lpk20_mx_keypad_L_Mk1_rev0-User_6.svg");
        translate([0, 0, -1])
        linear_extrude(height=_mountingPointThickness+2)
        import("lpk20_mx_keypad_L_Mk1_rev0-User_7.svg");
    }

    //Control board mounts
    translate([_controlBoardMountLengthOffset, _controlBoardMountWidthOffset, _baseThickness])
    {
        difference()
        {
            linear_extrude(height=_mountingPointThickness)
            import("pico_ctrl_board_primary_Mk2_rev0-User_4.svg");
            translate([0, 0, -1])
            linear_extrude(height=_mountingPointThickness+2)
            import("pico_ctrl_board_primary_Mk2_rev0-User_2.svg");
        }
        //linear_extrude(height=_mountingPointThickness+15)
        //import("pico_ctrl_board_primary_Mk2_rev0-Edge_Cuts.svg");
    }

    //Switch board mounts
    translate([_switchBoardMountLengthOffset, _switchBoardMountWidthOffset, _baseThickness])
    {
        difference()
        {
            linear_extrude(height=_mountingPointThickness)
            import("usbc_switch_board_Mk1_rev0-User_4.svg");
            translate([0, 0, -1])
            linear_extrude(height=_mountingPointThickness+2)
            import("usbc_switch_board_Mk1_rev0-User_3.svg");
        }
        //linear_extrude(height=_mountingPointThickness+15)
        //import("usbc_switch_board_Mk1_rev0-Edge_Cuts.svg");
    }

    //Mouse board mounts
    translate([_mouseBoardMountLengthOffset, _mouseBoardMountWidthOffset, _baseThickness])
    {
        difference()
        {
            linear_extrude(height=_mountingPointThickness)
            import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_5.svg");
            translate([0, 0, -1])
            linear_extrude(height=_mountingPointThickness+2)
            import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_4.svg");
        }
    }

    //Backplate supports
    difference()
    {
        translate([_edgeCutCorrectionOffset, 0, _baseThickness])
        {
            difference()
            {
                linear_extrude(height=_backplateSupportDepth)
                minkowski()
                {
                    circle(r=_backplateSupportThickness/2,$fn=100);
                    import("lpk20_mx_keypad_L_Mk1_rev0-Edge_Cuts.svg");
                }
                linear_extrude(height=_backplateSupportDepth+2)
                import("lpk20_mx_keypad_L_Mk1_rev0-User_6.svg");
            }
        }

        translate([_controlBoardMountLengthOffset-1, _controlBoardMountWidthOffset, _baseThickness])
        {
            linear_extrude(height=_backplateSupportDepth+2)
            import("pico_ctrl_board_primary_Mk2_rev0-Edge_Cuts_fill.svg");
        }

        switchBoardScaleOffset = -1;
        translate([_switchBoardMountLengthOffset+switchBoardScaleOffset, _switchBoardMountWidthOffset+switchBoardScaleOffset, _baseThickness])
        {
            linear_extrude(height=_backplateSupportDepth+2)
            scale([1.05, 1.05, 1])
            import("usbc_switch_board_Mk1_rev0-Edge_Cuts_fill.svg");
        }

        mouseBoardScaleOffset = -0.8;
        translate([_mouseBoardMountLengthOffset+mouseBoardScaleOffset, _mouseBoardMountWidthOffset+mouseBoardScaleOffset, _baseThickness])
        {
            linear_extrude(height=_backplateSupportDepth+2)
            scale([1.05, 1.05, 1])
            import("dual_axis_i2c_analog_mouse_Mk1_rev0-Edge_Cuts_fill.svg");
        }
    }
}

//Case top
//translate([0, 0, _caseWallDepth-(_caseWallThickness)])
//difference()
//{
//    linear_extrude(height=_caseWallThickness)
//    import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");
//
//    translate([_edgeCutCorrectionOffset, 0, -1])
//    linear_extrude(height=_caseWallThickness+2)
//    import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill.svg");
//}

//Case walls
//translate([_edgeCutCorrectionOffset, 0, 0])
//difference()
//{
//    linear_extrude(height=_caseWallDepth)
//    minkowski()
//    {
//        circle(r=_caseWallThickness/2,$fn=100);
//        import("lpk20_mx_keypad_L_Mk1_rev0-User_2.svg");
//    }
//}

module mountingPuckPunch(depth, rad)
{
    _puckCenterToCenterDist = 45;
    cylinder(r=rad, h=depth, $fn=100);
    translate([0, _puckCenterToCenterDist, 0])
    cylinder(r=rad, h=depth, $fn=100);
    translate([_puckCenterToCenterDist, 0, 0])
    cylinder(r=rad, h=depth, $fn=100);
    translate([_puckCenterToCenterDist, _puckCenterToCenterDist, 0])
    cylinder(r=rad, h=depth, $fn=100);
}