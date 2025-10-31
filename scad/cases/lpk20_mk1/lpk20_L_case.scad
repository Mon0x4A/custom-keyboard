_edgeCutCorrectionOffset=-2.5;
_caseWallDepth=27;
_backplateCountersink=5;
_caseWallThickness=3.5;
_topRimThickness=2;
_baseThickness=4;
_backplateThickness=5;
_backplateSupportDepth=18;
_backplateSupportThickness=2;
_mountingPointThickness=4;
_pcbThickness = 2;

_controlBoardMountWidthOffset = 37;
_controlBoardMountLengthOffset = 82.5;
_switchBoardMountWidthOffset = 81;
_switchBoardMountLengthOffset = -6;
_mouseBoardMountWidthOffset = 55;
_mouseBoardMountLengthOffset = 34;

_mountingPuckLengthOffset = 80;
_mountingPuckWidthOffset = 40;
_mountingPuckPunchRadius = 1.95;

_ethernetCutoutLength = 15;
_ethernetCutoutWidth = 17;
_ethernetCutoutDepth = 13.5;

_usbPlugCutoutLength = 8;
_usbPlugCutoutWidth = _caseWallThickness+4;
_usbPlugCutoutDepth = 15;
_usbPlugCutoutLengthOffset = 112;
_usbPlugCutoutWidthOffset = 113;
_usbPlugCutoutDepthOffset = (_caseWallDepth-_usbPlugCutoutDepth-_baseThickness)/2;

_lowerLeftLidPunchLenghtOffset = 5;
_lowerLeftLidPunchWidthOffset = 40;

_lidMountingStudCutoutRadius = 1.6;
_lidMountingStudCutoutDepth = 4;
_lidMountingStudWallThickness = 2;
_lidMountingStudDepth = 20;

//Top
difference()
{
    union()
    {
        //Top rim
        translate([_edgeCutCorrectionOffset,0,_caseWallDepth])
        linear_extrude(height=_caseWallThickness+_topRimThickness)
        import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill_backplate_hole.svg");

        //Key border
        translate([0, 0, _caseWallDepth])//-(_caseWallThickness)])
        difference()
        {
            linear_extrude(height=_caseWallThickness)
            import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");

            translate([_edgeCutCorrectionOffset, 0, -1])
            linear_extrude(height=_caseWallThickness+2)
            import("lpk20_mx_keypad_L_Mk1_rev0-User_4_fill.svg");

        }

        translate([_edgeCutCorrectionOffset, 0, _caseWallDepth-1.5])
        linear_extrude(height=2)
        minkowski()
        {
            import("lpk20_mx_keypad_L_Mk1_rev0-User_2.svg");
            circle(r=0.5);
        }
    }

    translate([_lowerLeftLidPunchLenghtOffset, _lowerLeftLidPunchWidthOffset, _caseWallDepth-1])
    {
        lidAttachmentPunch(_caseWallThickness*3, 1.2);
    }
}

//Backplate
//translate([_edgeCutCorrectionOffset, 1, _baseThickness+_backplateSupportDepth])
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
//union()
//{
//    difference()
//    //union()
//    {
//        linear_extrude(height=_baseThickness)
//        import("lpk20_mx_keypad_L_Mk1_rev0-User_2_fill.svg");
//
//        translate([_mountingPuckLengthOffset, _mountingPuckWidthOffset, -1])
//        rotate([0, 0, 45])
//        mountingPuckPunch(_baseThickness+2, _mountingPuckPunchRadius);
//    }
//    //TODO difference out the top attachment
//
//    //Keypad mounts
//    translate([_edgeCutCorrectionOffset, 0, _baseThickness])
//    difference()
//    {
//        linear_extrude(height=_mountingPointThickness)
//        import("lpk20_mx_keypad_L_Mk1_rev0-User_6.svg");
//        translate([0, 0, -1])
//        linear_extrude(height=_mountingPointThickness+2)
//        import("lpk20_mx_keypad_L_Mk1_rev0-User_7.svg");
//    }
//
//    //Control board mounts
//    translate([_controlBoardMountLengthOffset, _controlBoardMountWidthOffset, _baseThickness])
//    {
//        difference()
//        {
//            linear_extrude(height=_mountingPointThickness)
//            import("pico_ctrl_board_primary_Mk2_rev0-User_4.svg");
//            translate([0, 0, -1])
//            linear_extrude(height=_mountingPointThickness+2)
//            import("pico_ctrl_board_primary_Mk2_rev0-User_2.svg");
//        }
//        //translate([0, 0, _mountingPointThickness])
//        //linear_extrude(height=_pcbThickness)
//        //import("pico_ctrl_board_primary_Mk2_rev0-Edge_Cuts.svg");
//    }
//
//    //Top Mounts
//    translate([_lowerLeftLidPunchLenghtOffset, _lowerLeftLidPunchWidthOffset, 0])
//    {
//        difference()
//        {
//            difference()
//            {
//                lidAttachmentPunch(_lidMountingStudDepth,_lidMountingStudCutoutRadius+_lidMountingStudWallThickness);
//                translate([0, 0, _lidMountingStudDepth-_lidMountingStudCutoutDepth])
//                #lidAttachmentPunch(8,_lidMountingStudCutoutRadius);
//            }
//            controlPcbCutoutLengthOffset = 125;
//            controlPcbCutoutWidthOffset = 60;
//            controlPcbCutoutSideLength = 10;
//            translate([controlPcbCutoutLengthOffset, controlPcbCutoutWidthOffset, _baseThickness+_mountingPointThickness])
//            #cube([controlPcbCutoutSideLength, controlPcbCutoutSideLength, _pcbThickness]);
//        }
//    }
//
//    //Switch board mounts
//    //translate([_switchBoardMountLengthOffset, _switchBoardMountWidthOffset, _baseThickness])
//    //{
//    //    difference()
//    //    {
//    //        linear_extrude(height=_mountingPointThickness)
//    //        import("usbc_switch_board_Mk1_rev0-User_4.svg");
//    //        translate([0, 0, -1])
//    //        linear_extrude(height=_mountingPointThickness+2)
//    //        import("usbc_switch_board_Mk1_rev0-User_3.svg");
//    //    }
//    //    //linear_extrude(height=_mountingPointThickness+15)
//    //    //import("usbc_switch_board_Mk1_rev0-Edge_Cuts.svg");
//    //}
//
//    //Mouse board mounts
//    //translate([_mouseBoardMountLengthOffset, _mouseBoardMountWidthOffset, _baseThickness])
//    //{
//    //    difference()
//    //    {
//    //        linear_extrude(height=_mountingPointThickness)
//    //        import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_5.svg");
//    //        translate([0, 0, -1])
//    //        linear_extrude(height=_mountingPointThickness+2)
//    //        import("dual_axis_i2c_analog_mouse_Mk1_rev0-User_4.svg");
//    //    }
//    //}
//
//    //Backplate supports
//    difference()
//    {
//        translate([_edgeCutCorrectionOffset, 0, _baseThickness])
//        {
//            difference()
//            {
//                linear_extrude(height=_backplateSupportDepth)
//                minkowski()
//                {
//                    circle(r=_backplateSupportThickness/2,$fn=100);
//                    import("lpk20_mx_keypad_L_Mk1_rev0-Edge_Cuts.svg");
//                }
//                linear_extrude(height=_backplateSupportDepth+2)
//                import("lpk20_mx_keypad_L_Mk1_rev0-User_6.svg");
//            }
//        }
//
//        translate([_controlBoardMountLengthOffset-1, _controlBoardMountWidthOffset, _baseThickness])
//        {
//            linear_extrude(height=_backplateSupportDepth+2)
//            import("pico_ctrl_board_primary_Mk2_rev0-Edge_Cuts_fill.svg");
//        }
//
//        switchBoardScaleOffset = -1;
//        translate([_switchBoardMountLengthOffset+switchBoardScaleOffset, _switchBoardMountWidthOffset+switchBoardScaleOffset, _baseThickness])
//        {
//            linear_extrude(height=_backplateSupportDepth+2)
//            scale([1.05, 1.05, 1])
//            import("usbc_switch_board_Mk1_rev0-Edge_Cuts_fill.svg");
//        }
//
//        mouseBoardScaleOffset = -0.8;
//        translate([_mouseBoardMountLengthOffset+mouseBoardScaleOffset, _mouseBoardMountWidthOffset+mouseBoardScaleOffset, _baseThickness])
//        {
//            linear_extrude(height=_backplateSupportDepth+2)
//            scale([1.05, 1.05, 1])
//            import("dual_axis_i2c_analog_mouse_Mk1_rev0-Edge_Cuts_fill.svg");
//        }
//    }
//}
//
//
////Case walls
//translate([_edgeCutCorrectionOffset, 0, _baseThickness])
//difference()
//{
//    linear_extrude(height=_caseWallDepth-_baseThickness)
//    minkowski()
//    {
//        circle(r=_caseWallThickness/2,$fn=100);
//        import("lpk20_mx_keypad_L_Mk1_rev0-User_2.svg");
//    }
//    translate([_controlBoardMountLengthOffset, _controlBoardMountWidthOffset, _baseThickness])
//    {
//        _ethernetCutoutLengthOffset = 52;
//        _ethernetCutoutWidthOffset = 3;
//        _ethernetCutoutDepthOffset = _pcbThickness;
//        translate([_ethernetCutoutLengthOffset, _ethernetCutoutWidthOffset, _ethernetCutoutDepthOffset])
//        #cube([_ethernetCutoutLength, _ethernetCutoutWidth, _ethernetCutoutDepth]);
//    }
//    translate([_controlBoardMountLengthOffset+3.5, _controlBoardMountWidthOffset,0])
//    {
//        translate([0, 0, _mountingPointThickness])
//        #linear_extrude(height=_pcbThickness)
//        import("pico_ctrl_board_primary_Mk2_rev0-Edge_Cuts_fill.svg");
//    }
//    translate([_usbPlugCutoutLengthOffset, _usbPlugCutoutWidthOffset, _usbPlugCutoutDepthOffset])
//    {
//        #cube([_usbPlugCutoutLength, _usbPlugCutoutWidth, _usbPlugCutoutDepth]);
//    }
//}

//Punches
module mountingPuckPunch(depth, rad)
{
    //NOTE: This is the side distance of the square, not the diagonal distance.
    _puckCenterToCenterDist = 45;
    cylinder(r=rad, h=depth, $fn=100);
    translate([0, _puckCenterToCenterDist, 0])
    cylinder(r=rad, h=depth, $fn=100);
    translate([_puckCenterToCenterDist, 0, 0])
    cylinder(r=rad, h=depth, $fn=100);
    translate([_puckCenterToCenterDist, _puckCenterToCenterDist, 0])
    cylinder(r=rad, h=depth, $fn=100);
}

module lidAttachmentPunch(depth, rad)
{
    //Lower Left
    cylinder(r=rad, h=depth, $fn=100);

    //Upper Left
    translate([0, 72.5, 0])
    cylinder(r=rad, h=depth, $fn=100);

    //Upper Right
    translate([132, 72.5, 0])
    cylinder(r=rad, h=depth, $fn=100);

    translate([132, -35, 0])
    cylinder(r=rad, h=depth, $fn=100);
}