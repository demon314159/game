$fa = 1;
$fs = 0.04;
mag = 1;
thickness = mag * 0.05;
width = mag * 6.235;
length = mag * 9.4;
porch_width = width/3.05;
porch_length = mag * 0.45;

f = 0.98;
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
difference()
{
 linear_extrude(height = thickness) {
  polygon(points);
}
translate([0,-5,thickness/2])
cube([0.5,2,thickness], center=true);
}
//translate([0,-2+1,thickness/2])
//cube([0.5*f,2*f,thickness], center=true);
}



