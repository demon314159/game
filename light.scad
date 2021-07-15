include_base = false;
include_top = true;
$fa = 1;
$fs = 0.01;
mag = 1;
thickness = mag * 0.05;
base_radius = mag * 0.2;
top_radius = mag * 0.15;
rotate([90,0,0]) {
  if (include_top) {
//    sphere(top_radius);  
    translate([0,0,-thickness/4])
    linear_extrude(thickness)
    circle(top_radius);
  }
  if (include_base) {
    translate([0,0,-thickness/8])
    linear_extrude(thickness)
    circle(base_radius);
  }
}