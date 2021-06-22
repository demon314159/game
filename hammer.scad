include </snap/openscad/current/usr/share/openscad/libraries/MCAD/boxes.scad>
$fa = 1;
$fs = 0.01;
mag = 1.0 / 1.1 / 2.6;

lax = mag * 1.0;
lay = mag * 2.0;
lbx = lax * 1.1;
lby = lay * 0.9;
lshaft = mag * 2.0;
rotate([-90,0,0]) {
//  roundedBox([lax,lay,lax], lax/5,     sidesonly=false);
// roundedBox([lbx,lby,lbx], lax/5 ,sidesonly=false);
  rotate([180,0,0])
    cylinder(lshaft, lax /4, lax / 5);
}