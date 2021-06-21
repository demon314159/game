
$fa = 1;
$fs = 0.01;
mag = 0.416/2.6;
thickness = mag * 0.15;

a = mag * 1.4 / 2.0;
b = mag * 2.6 / 2.0;
c = mag * 2.2 / 2.0;
d = mag * 2.4;
e = mag * 1.8;
f = mag * 0.6;
g = mag * 0.6;
vcenter = mag * -5.4;

p0 = [-a, vcenter + d + e + f];
p1 = [-a, vcenter + d + e];
p2 = [-b, vcenter + d];
p3 = [-c, vcenter + 0.0];
p4 = [c, vcenter + 0.0];
p5 = [b, vcenter + d];
p6 = [a, vcenter + d + e];
p7 = [a, vcenter + d + e + f];
points = [p0, p1, p2, p3, p4, p5, p6, p7];
rotate([-20,0,0])
linear_extrude(height = thickness) {
  translate([0, -g/2, 0])
    square([a/2, g],center = true);   
  polygon(points);  
}  


