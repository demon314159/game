$fa = 1;
$fs = 0.01;
mag = 0.416/2.2;
thickness = mag * 0.4;

a = mag * 1.4 / 2.0;
b = mag * 2.6 / 2.0;
c = mag * 2.2 / 2.0;
d = mag * 2.4;
e = mag * 1.8;
f = mag * 0.6;
g = mag * 0.6;
vcenter = mag * 0;

p0 = [-a, vcenter + d + e + f];
p1 = [-a, vcenter + d + e];
p2 = [-b, vcenter + d];
p3 = [-c, vcenter + 0.0];
p4 = [c, vcenter + 0.0];
p5 = [b, vcenter + d];
p6 = [a, vcenter + d + e];
p7 = [a, vcenter + d + e + f];
points = [p0, p1, p2, p3, p4, p5, p6, p7];
rotate([-90,0,0]) {
//translate([0,-d - e - f,0])
//linear_extrude(height = thickness) {
//  polygon(points);
//}
//translate([-c,-d-e-f,thickness/2])
//rotate([0,90,0])
//cylinder(c*2, thickness / 3, thickness / 3);
translate([0,-f,0.01])
linear_extrude(height = thickness) 
  text("HOMER",size = 0.1,direction="ttb");
}

