$fa = 1;
$fs = 0.01;
mag = 2.5;
thickness = mag * 0.15;
l1 = mag * 0.7;
l2 = mag * 0.3 / 2.0;
l3 = mag * 0.1 / 2.0;
ldif = l2 - l3;
hyp = sqrt(l1 * l1 + ldif * ldif);
sinth = ldif / hyp;
costh = l1 / hyp;
lax = l2 * sinth;
lay = l2 * costh;
lbx = l3 * sinth;
lby = l3 * costh;
p0 = [lax, -lay];
p1 = [l1+lbx, -lby];
p2 = [l1+lbx, lby];
p3 = [lax, lay];
points = [p0, p1, p2, p3];
linear_extrude(height = thickness) {
  polygon(points);
  translate([0, 0, 0]) circle(l2);
  translate([l1, 0, 0]) circle(l3);
}




