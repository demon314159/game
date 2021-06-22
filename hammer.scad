include </home/andy/repos/game.git/bat_boot.scad>
$fa = 1;
$fs = 0.01;
//mag = 1.0 / 1.1 / 2.6;

//lax = mag * 1.0;
//lay = mag * 2.0;
//lbx = lax * 1.1;
//lby = lay * 0.9;
//lshaft = mag * 2.0;
//rotate([-90,0,0]) {
//  roundedBox([lax,lay,lax], lax/5,     sidesonly=false);
// roundedBox([lbx,lby,lbx], lax/5 ,sidesonly=false);
//  rotate([180,0,0])
//    cylinder(lshaft, lax /4, lax / 5);
//}



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
//rotate([-90,0,0])
translate([0,-d - e - f,0])
linear_extrude(height = thickness) {
  polygon(points);
}
translate([-c,-d-e-f,thickness/2])
rotate([0,90,0])
bat_boot(c*2, thickness / 3, 0.2);

