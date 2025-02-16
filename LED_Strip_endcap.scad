$fn = 60;
rad = 16; // radius of the cover curvature and length of the sides
thick = 0.9; // thickeness of extrusion
tri = 6; // short sides of pin into extrusion
z_h = 10; // height of pin
z_d = 2; // depth of extrusion to sink into case
difference(){
	minkowski(){
		intersection(){
			cube([rad, rad, z_h]);
			cylinder(r=rad-(2*thick), h=z_h);
		}
		sphere(r=thick);
	}
	translate([-z_d, -z_d, 0]) cube([rad+z_d*2, z_d, z_h+z_d]);
	translate([-z_d, -z_d, 0]) cube([z_d, rad+z_d*2, z_h+z_d]);
	translate([tri, 0, 0]) cube([rad, thick, z_d]);
	translate([0, tri, 0]) cube([thick, rad, z_d]);
	difference(){
		cylinder(r=rad-(thick*5), h=z_h+z_d);
		cylinder(r=tri, h=z_h+z_d);
	}
	translate([0,tri,0]) rotate([0,0,-45]) cube([tri*1.5, tri, z_h+z_d]);
	difference(){
		union(){
			translate([0,0,z_d]) cylinder(r=rad, h=z_d+z_h);
			cylinder(r=rad-(1*thick), h=z_d);
		}
		cylinder(r=rad-(3*thick), h=z_d);
		cylinder(r=tri, h=z_d+z_h);
	}
}