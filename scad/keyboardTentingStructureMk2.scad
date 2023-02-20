
_m3BoltHoleDiameter = 3.2 + 0.2; // plus padding
_m3BoltHoleRadius = _m3BoltHoleDiameter/2;

_mk2HousingLength = 127;
_mk2HousingWidth = 88;
_mk2HousingDepth = 18;

_carraigeThickness = 4.1;
_carraigeLengthSidePadding = 0.2;
_carraigeWidthSidePadding = _carraigeLengthSidePadding;
_carraigeLength = _mk2HousingLength + ((_carraigeThickness + _carraigeLengthSidePadding)*2);
_carraigeWidth = _mk2HousingWidth + ((_carraigeThickness + _carraigeWidthSidePadding)*2);
_carraigeDepth = _carraigeThickness + 14;

_carraigeBeamWidth = 20;
_carraigeRoundingRadius = 1;
_carraigeBeamBoltChannelWidth = _m3BoltHoleDiameter + 0.2; //plus padding
_carraigeBeamBoltChannelCountersinkWidth = _carraigeBeamBoltChannelWidth  + 2;
_carraigeBeamBoltChannelCountersinkDepth = 3;
_carraigeBeamCutoutRadius = 5;

_tentBeamThickness = 4.5;
_tentBeamWidth = 20;
_tentRoundingRadius = 1;

_tentHeight = 121;
_tentMountingBeamLength = 140;
_tentAngle = 60;

_tentBaseThickness = 5.5;
_tentBaseLength = 130;
_tentBaseWidth = 90;
_frameBaseBeamCutoutOffset = 10;
/// MAIN START ///
//tentingAssembly();
tentingStructure();
//boltChannelPunch(50, _tentBeamThickness+1, _carraigeBeamBoltChannelWidth/2, _carraigeBeamBoltChannelCountersinkWidth/2, _carraigeBeamBoltChannelCountersinkDepth);
//carraigeBeam(50);
//carraige();
/// MAIN END ///

module tentingAssembly()
{
    difference()
    union()
    {
        //possibly break this out into another method
        difference()
        {
            tentingStructure();
            //bolt channel
            //"triangulation"
        }

       translate([7.5,(_tentBaseWidth-_carraigeWidth)/2,1])
            rotate([0,-_tentAngle,0])
                carraige();
    }
}

module tentingStructure()
{
    difference()
    //union()
    {
        union()
        {
            // Parallel to keyboard beam.
            translate([0, (_tentBaseWidth-_tentBeamWidth)/2, 0])
                baseConnectingBeam();

            translate([0, 0, 0])
                baseBeam();
            translate([_tentBaseLength-_tentBeamWidth, 0, 0])
                baseBeam();

            translate([0,0, _tentBaseThickness])
                mountingFrame();
        }

        //Cutout for carraige
        carraigeCutoutSidePadding = 1;
        carraigeCutoutWidth = _carraigeBeamWidth + (carraigeCutoutSidePadding*2);
        translate([7.4, (_tentBaseWidth-carraigeCutoutWidth)/2, 1])
            rotate([0,-_tentAngle,0])
                cube([50, carraigeCutoutWidth, 10]);
    }
}

module baseBeam()
{
    roundedCube(size=[_tentBeamWidth, _tentBaseWidth, _tentBaseThickness], radius=_tentRoundingRadius, apply_to="zmax");
}

module baseConnectingBeam()
{
    roundedCube(size=[_tentBaseLength, _tentBeamWidth, _tentBaseThickness], radius=_tentRoundingRadius, apply_to="zmax");
}

module mountingFrame()
{
    union()
    {
        translate([80,(_tentBaseWidth-_tentBeamWidth)/2,0])
            decorativeFrameBeam(_tentHeight);

        // Carraige attachment beam
        translate([10,(_tentBaseWidth-_tentBeamWidth)/2,0])
            rotate([0,90-_tentAngle,0])
                attachmentFrameBeam(_tentMountingBeamLength, _frameBaseBeamCutoutOffset);
        // Secondary angled support beam
        translate([120,(_tentBaseWidth-_tentBeamWidth)/2,-_tentBaseThickness])
            rotate([0,-90+_tentAngle,0])
                decorativeFrameBeam(_tentMountingBeamLength*(2.85/5));
    }
}

module attachmentFrameBeam(length, cutoutSideOffset)
{
    difference()
    //union()
    {
        roundedCube(size=[_tentBeamThickness, _tentBeamWidth, length], radius=_tentRoundingRadius, apply_to="zmax");
        cutoutLength = length-(cutoutSideOffset*2);
        translate([-1,_tentBeamWidth/2,cutoutSideOffset+_carraigeBeamBoltChannelWidth/2])
            rotate([90,0,0])
                rotate([0,90,0])
                    boltChannel(cutoutLength, _tentBeamThickness+2, _carraigeBeamBoltChannelWidth/2);
    }
}

module decorativeFrameBeam(length)
{
    roundedCube(size=[_tentBeamThickness, _tentBeamWidth, length], radius=_tentRoundingRadius, apply_to="zmax");
}

module carraige()
{
    union()
    {
        carraigeBody();
    }
}

module carraigeBody()
{
    union()
    {
        //// Keyboard stand-in
        //translate([_carraigeLengthSidePadding + _carraigeThickness, _carraigeWidthSidePadding + _carraigeThickness, _carraigeThickness])
        //    translate([0,0,12]) // Center at Z=0
        //        import("../resources/stl/keyboardMk2.stl");

        // Length-wise beam.
        translate([0, (_carraigeWidth-_carraigeBeamWidth)/2, 0])
            carraigeBeam(_carraigeLength);

        // Width-wise beams.
        translate([(_carraigeLength-_carraigeBeamWidth)*(1/4),0,0])
            translate([_carraigeBeamWidth, 0, 0]) //Center at X=0
                rotate([0,0,90])
                    carraigeBeam(_carraigeWidth);

        translate([(_carraigeLength-_carraigeBeamWidth)*(3/4),0,0])
            translate([_carraigeBeamWidth, 0, 0]) //Center at X=0
                rotate([0,0,90])
                    carraigeBeam(_carraigeWidth);
    }
}

module carraigeBeam(length)
{
    difference()
    //union()
    {
        union()
        {
            cube([length, _carraigeBeamWidth, _carraigeThickness]);

            translate([_carraigeThickness, 0, 0])
                rotate([0,-90,0])
                    roundedCube(size=[_carraigeDepth, _carraigeBeamWidth, _carraigeThickness], radius=_carraigeRoundingRadius, apply_to="z");
            translate([length, 0, 0])
                rotate([0,-90,0])
                    roundedCube(size=[_carraigeDepth, _carraigeBeamWidth, _carraigeThickness], radius=_carraigeRoundingRadius, apply_to="z");
        }

        //Bolt channel cutout
        boltChannelSidePadding = 13;
        totalLength = length + _carraigeThickness*2;
        boltChannelLength =  totalLength - (boltChannelSidePadding*2);
        radiusDifference = (_carraigeBeamBoltChannelCountersinkWidth - _carraigeBeamBoltChannelWidth);
        channelCounterSinkTotalLength = boltChannelLength + radiusDifference*2;
        translate([(totalLength-channelCounterSinkTotalLength)/2, _carraigeBeamWidth/2, -2])
            rotate([0,0,-90])
                boltChannelPunch(boltChannelLength+radiusDifference, _carraigeDepth+1, _carraigeBeamBoltChannelWidth/2, _carraigeBeamBoltChannelCountersinkWidth/2, _carraigeBeamBoltChannelCountersinkDepth);

        //Holding tab cutouts
        translate([-1,_carraigeBeamWidth/2,_carraigeDepth/2])
            rotate([0,90,0])
                cylinder(r=_carraigeBeamCutoutRadius, h=length+2, center=false, $fn=100);
    }
}

//Punches
module boltChannelPunch(length, depth, radius, countersinkRadius, countersinkDepth)
{
    union()
    {
        // Punch portion
        boltChannel(length, depth, radius);
        // Countersink portion
        translate([0,0,countersinkDepth])
            boltChannel(length+(countersinkRadius-radius)*2, depth, countersinkRadius);

    }
}

module boltChannel(length, depth, radius)
{
    union()
    {
        cylinder(r=radius, h=depth, $fn=100);

        translate([-radius,0,0])
            cube([radius*2, length-radius*2, depth]);

        translate([0,length-radius*2,0])
            cylinder(r=radius, h=depth, $fn=100);
    }
}

//Utility Methods
/// Builds a cube with rounded corners
/// size - dimension vector
/// center - centered on xyz planes?
/// radius - rounding radius
/// apply_to - which sides to round
module roundedCube(size = [1, 1, 1], center = false, radius = 0.5, apply_to = "all")
{
	// If single value, convert to [x, y, z] vector
	size = (size[0] == undef) ? [size, size, size] : size;

	translate_min = radius;
	translate_xmax = size[0] - radius;
	translate_ymax = size[1] - radius;
	translate_zmax = size[2] - radius;

	diameter = radius * 2;

	obj_translate = (center == false) ?
		[0, 0, 0] : [
			-(size[0] / 2),
			-(size[1] / 2),
			-(size[2] / 2)
		];

	translate(v = obj_translate) {
		hull() {
			for (translate_x = [translate_min, translate_xmax]) {
				x_at = (translate_x == translate_min) ? "min" : "max";
				for (translate_y = [translate_min, translate_ymax]) {
					y_at = (translate_y == translate_min) ? "min" : "max";
					for (translate_z = [translate_min, translate_zmax]) {
						z_at = (translate_z == translate_min) ? "min" : "max";

						translate(v = [translate_x, translate_y, translate_z])
						if (
							(apply_to == "all") ||
							(apply_to == "xmin" && x_at == "min") || (apply_to == "xmax" && x_at == "max") ||
							(apply_to == "ymin" && y_at == "min") || (apply_to == "ymax" && y_at == "max") ||
							(apply_to == "zmin" && z_at == "min") || (apply_to == "zmax" && z_at == "max")
						) {
							sphere(r = radius, $fn=20);
						} else {
							rotate =
								(apply_to == "xmin" || apply_to == "xmax" || apply_to == "x") ? [0, 90, 0] : (
								(apply_to == "ymin" || apply_to == "ymax" || apply_to == "y") ? [90, 90, 0] :
								[0, 0, 0]
							);
							rotate(a = rotate)
							cylinder(h = diameter, r = radius, center = true, $fn=20);
						}
					}
				}
			}
		}
	}
}


