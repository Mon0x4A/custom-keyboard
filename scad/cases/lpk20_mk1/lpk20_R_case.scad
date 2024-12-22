
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
_controlBoardMountLengthOffset = -3;
_mouseBoardMountWidthOffset = 58;
_mouseBoardMountLengthOffset = 47;

_mountingPuckLengthOffset = 65;
_mountingPuckWidthOffset = 40;
_mountingPuckPunchRadius = 1.95;

_joystickPunchLengthOffset = 97;
_joystickPunchWidthOffset = 91.75;
_joystickPunchRadius = 1.75;
_joystickCenterToCenterDist = 13;

//Top rim
//translate([_edgeCutCorrectionOffset,0,_caseWallDepth-(_caseWallThickness/2)])
//linear_extrude(height=_caseWallThickness)
//import("lpk20_mx_keypad_R_Mk1_rev0-User_3_fill_backplate_hole.svg");

//Backplate
translate([_edgeCutCorrectionOffset, 1, _caseWallDepth-(_caseWallThickness*2)])
difference()
{
    linear_extrude(height=_backplateThickness)
    import("lpk20_mx_keypad_R_Mk1_rev0-Edge_Cuts_fill.svg");

    translate([0, 0, -1])
    linear_extrude(height=_backplateThickness+2)
    import("lpk20_mx_keypad_R_Mk1_rev0-User_1.svg");
}

//Case bottom
//union()
//{
//    difference()
//    //union()
//    {
//        linear_extrude(height=_baseThickness)
//        import("lpk20_mx_keypad_R_Mk1_rev0-User_2_fill.svg");
//
//        translate([_mountingPuckLengthOffset, _mountingPuckWidthOffset, -1])
//        rotate([0, 0, 45])
//        mountingPuckPunch(_baseThickness+2, _mountingPuckPunchRadius);
//
//        translate([_joystickPunchLengthOffset, _joystickPunchWidthOffset, -1])
//        joystickPunch(_baseThickness+2, _joystickPunchRadius);
//    }
//
//    //Keypad mounts
//    translate([0, 0, _baseThickness])
//    difference()
//    {
//        linear_extrude(height=_mountingPointThickness)
//        import("lpk20_mx_keypad_R_Mk1_rev0-User_5.svg");
//        translate([0, 0, -1])
//        linear_extrude(height=_mountingPointThickness+2)
//        import("lpk20_mx_keypad_R_Mk1_rev0-User_4.svg");
//    }
//
//    //Control board mounts
//    translate([_controlBoardMountLengthOffset, _controlBoardMountWidthOffset, _baseThickness])
//    {
//        difference()
//        {
//            linear_extrude(height=_mountingPointThickness)
//            import("io_ctrl_board_secondary_Mk2_rev0-User_3.svg");
//            translate([0, 0, -1])
//            linear_extrude(height=_mountingPointThickness+2)
//            import("io_ctrl_board_secondary_Mk2_rev0-User_2.svg");
//        }
//        //linear_extrude(height=_mountingPointThickness+15)
//        //import("io_ctrl_board_secondary_Mk2_rev0-Edge_Cuts.svg");
//    }
//
//    translate([_mouseBoardMountLengthOffset, _mouseBoardMountWidthOffset, _baseThickness])
//    {
//        difference()
//        {
//            linear_extrude(height=_mountingPointThickness)
//            import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_5.svg");
//            translate([0, 0, -1])
//            linear_extrude(height=_mountingPointThickness+2)
//            import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_4.svg");
//        }
//    }
//
//    //Backplate supports
//    difference()
//    {
//        translate([0, 0, _baseThickness])
//        {
//            difference()
//            {
//                linear_extrude(height=_backplateSupportDepth)
//                minkowski()
//                {
//                    circle(r=_backplateSupportThickness/2,$fn=100);
//                    import("lpk20_mx_keypad_R_Mk1_rev0-Edge_Cuts.svg");
//                }
//                linear_extrude(height=_backplateSupportDepth+2)
//                import("lpk20_mx_keypad_R_Mk1_rev0-User_5.svg");
//            }
//        }
//
//        translate([_controlBoardMountLengthOffset+12, _controlBoardMountWidthOffset-1, _baseThickness])
//        {
//            linear_extrude(height=_backplateSupportDepth+2)
//            scale([1.05, 1.05, 1])
//            import("io_ctrl_board_secondary_Mk2_rev0-Edge_Cuts_fill.svg");
//        }
//
//        mouseBoardScaleOffset = -0.8;
//        translate([_mouseBoardMountLengthOffset+mouseBoardScaleOffset, _mouseBoardMountWidthOffset+mouseBoardScaleOffset, _baseThickness])
//        {
//            linear_extrude(height=_backplateSupportDepth+2)
//            scale([1.05, 1.05, 1])
//            import("dual_axis_i2c_analog_mouse_Mk1_rev0-Edge_Cuts_fill.svg");
//        }
//
//        translate([_joystickPunchLengthOffset-(_joystickPunchRadius*3), _joystickPunchWidthOffset-(_joystickPunchRadius*3), _baseThickness])
//        cube([_joystickCenterToCenterDist+10, _joystickPunchRadius+16, _backplateSupportDepth+2]);
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

module joystickPunch(depth, rad)
{
    cylinder(r=rad, h=depth, $fn=100);
    translate([_joystickCenterToCenterDist, 0, 0])
    cylinder(r=rad, h=depth, $fn=100);
}
