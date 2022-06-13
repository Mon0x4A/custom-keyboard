
_backplateRowCount = 6;
_backplateColumnCount = 8;

_switchLength = 15;
_switchWidth = 15;

_switchPaddingLength = 2.5;
_switchPaddingWidth = 2.5;

_key1uLength = _switchLength+(_switchPaddingLength*2);
_key1uWidth = _switchWidth+(_switchPaddingWidth*2);

_key2uLength = (_switchLength*2)+(_switchPaddingLength*4);
_key2uWidth = _switchWidth+(_switchPaddingWidth*2);

_backplateLength = (_key1uLength * _backplateColumnCount);
_backplateWidth = (_key1uWidth * _backplateRowCount);
_backplateDepth = 4;
_backplateRoundingRadius = 1.25;

/// MAIN START ///

echo(str("_key1uLength = ", _key1uLength));
echo(str("_key1uWidth = ", _key1uWidth));
echo(str("_key2uLength = ", _key2uLength));
echo(str("_key2uWidth = ", _key2uWidth));

//keyboard();
//backplate();
housing();

/// MAIN END ///

module keyboard()
{
    union()
    {
        backplate();

        translate([0, 0, 0])
        {
            housing();
        }
    }
}

module housing()
{

}

module backplate()
{
    difference()
    union()
    {
        plate();

        //todo bolt recesses
    }
}

module plate()
{
    union()
    {
        backplateGrooveDepth = 1;
        roundedCube(size=[_backplateLength, _backplateWidth, _backplateDepth - backplateGrooveDepth], radius=_backplateRoundingRadius, apply_to="zmax");

        //[0,0] is the upper left corner of the keyboard.
        translate([0, _key1uWidth*5, 0])
            row0();
        translate([0, _key1uWidth*4, 0])
            row1();
        translate([0, _key1uWidth*3, 0])
            row2();
        translate([0, _key1uWidth*2, 0])
            row3();
        translate([0, _key1uWidth*1, 0])
            row4();
        translate([0, 0, 0])
            row5();
    }
}

module row0()
{
    union()
    {
        key1u();
        translate([(_key1uLength*1), 0, 0])
            key1u();
        translate([(_key1uLength*2), 0, 0])
            key1u();
        translate([(_key1uLength*3), 0, 0])
            key1u();
        translate([(_key1uLength*4), 0, 0])
            key1u();
        translate([(_key1uLength*5), 0, 0])
            key1u();
        translate([(_key1uLength*6), 0, 0])
            key1u();
        translate([(_key1uLength*7), 0, 0])
            key1u();
    }
}

module row1()
{
    row0();
}

module row2()
{
    union()
    {
        key2u();
        translate([(_key2uLength), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*2), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*3), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*4), 0, 0])
            key1u();
        translate([(_key2uLength+_key1uLength*5), 0, 0])
            key1u();
    }
}

module row3()
{
    row0();
}

module row4()
{
    row2();
}

module row5()
{
    union()
    {
        key2u();
        translate([(_key2uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength*1+_key1uLength*1), 0, 0])
            key1u();
        translate([(_key2uLength*1+_key1uLength*2), 0, 0])
            key2u();
        translate([(_key2uLength*2+_key1uLength*2), 0, 0])
            key2u();
    }
}

module key1u()
{
    difference()
    union()
    {
        //cube([_key1uLength, _key1uWidth, _backplateDepth]);
        roundedCube(size = [_key1uLength, _key1uWidth, _backplateDepth], radius=1.25, apply_to="zmax");

        translate([_key1uLength/2, _key1uWidth/2, _backplateDepth])
        {
            switchPunch();
        }
    }
}

module key2u()
{
    difference()
    union()
    {
        //cube([_key2uLength, _key2uWidth, _backplateDepth]);
        roundedCube(size = [_key2uLength, _key2uWidth, _backplateDepth], radius=_backplateRoundingRadius, apply_to="zmax");

        translate([_key2uLength/2, _key2uWidth/2, _backplateDepth])
        {
            switchPunch();
        }
    }
}

module switchPunch()
{
    translate([0,0,13.15])
    {
        scale([1,1,1])
        {
            import("../resources/stl/switch_mx.stl");
        }
    }
}

/// Builds a cube with rounded corners
/// size - dimension vector
/// center - centered on xyz planes?
/// radius - rounding radius
/// apply_to - which sides to round
module roundedCube(size = [1, 1, 1], center = false, radius = 0.5, apply_to = "all") {
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
