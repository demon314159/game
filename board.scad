include_body = true;
include_pitch_flap = false;
include_bumper = true;
$fa = 1;
$fs = 0.01;
mag = 1;
thickness = mag * 0.05;
width = mag * 6.235;
length = mag * 9.4;
porch_length = mag * 0.45;
porch_width = width/3.05 + porch_length;
bumper_radius = thickness;
bumper_length = length + porch_length;
f = 0.98; // Pitch flap tolerance
p0 = [-width/2,-length];
p1 = [-width/2, porch_length];
p2 = [-width/2 + porch_width, porch_length];
p3 = [-width/2 + porch_width, 0];
p4 = [width/2 - porch_width, 0];
p5 = [width/2 - porch_width, porch_length];
p6 = [width/2, porch_length];
p7 = [width/2, -length];
points = [p0, p1, p2, p3, p4, p5, p6, p7];

translate([0,0,2])
  rotate([90,0,0]) {
    if (include_body) {      
      difference() {
        linear_extrude(height = thickness) {
          polygon(points);
        }
        translate([0,-5,thickness/2])
          cube([0.5,2,thickness], center=true);
        linear_extrude(height = thickness) {
          translate([width/2 - porch_width,porch_length,0])
            circle(porch_length);
          translate([-width/2 + porch_width,porch_length,0])
            circle(porch_length);
        }    
      }
    }
    if (include_pitch_flap) {
      translate([0,-2+1,thickness/2])
      cube([0.5*f,2*f,thickness], center=true);
    }
  }
if (include_bumper) {  
  scale([1,2,1])    
  translate([-width/2,bumper_radius,2-bumper_length+porch_length]) {
    cylinder(bumper_length,bumper_radius, bumper_radius);
    sphere(bumper_radius);  
    translate([0,0,bumper_length])  
      sphere(bumper_radius);  
  }
  scale([1,2,1])    
  translate([width/2,bumper_radius,2-bumper_length+porch_length]) {
    sphere(bumper_radius);  
    translate([0,0,bumper_length])  
      sphere(bumper_radius);  
    cylinder(bumper_length,bumper_radius, bumper_radius);
  }    
}    




