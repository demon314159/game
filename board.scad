$fa = 1;
$fs = 0.04;
mag = 1;
thickness = mag * 0.05;
wback = mag * 6.235;
wfront = mag * 5.529;
length = mag * 9.4;
f = 0.98;
p0 = [-wback/2,-length];
p1 = [-wfront/2, 0];
p2 = [wfront/2, 0];
p3 = [wback/2, -length];
points = [p0, p1, p2, p3];

translate([0,0,2])
rotate([90,0,0]) {
difference()
{
 linear_extrude(height = thickness) {
  polygon(points);
}
translate([0,-3,thickness/2])
cube([0.5,2,thickness], center=true);
}
//translate([0,-2+1,thickness/2])
//cube([0.5*f,2*f,thickness], center=true);
}



