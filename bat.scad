include </home/andy/repos/game.git/bat_boot.scad>
$fa = 1;
$fs = 0.01;
mag = 0.088235 * 2 / 0.3;

rsleeve = mag * 0.3 / 2;
rshaft = 0.69 * rsleeve;
rhang = 0.8 * rshaft;
rpost = (rsleeve + rshaft) / 2;

lsleeve = mag * 1.2;
lshaft = mag * 0.8;
lhang = mag * 0.25;
lpost = mag * 0.5;

rotate([-90,0,0])
rotate([0,0,-45])
translate([0,0,0.15]) {
  translate([0, 0, -lpost + rsleeve])
  bat_boot(lpost, rpost, 0.3);
//  rotate([0,90,0]) {
//    translate([0,0,-lhang])
//      bat_boot(lhang, rhang, 0.3);
//    cylinder(lshaft, rhang, rshaft);
//    translate([0,0,lshaft])
//      bat_boot(lsleeve, rsleeve, 0.3);
//  }
}



