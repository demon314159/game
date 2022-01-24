mag = 1.0 / 5.0;
dx = mag * 0.5;
dy = mag * 0.5;
dt = mag * 0.025;
db = mag * 0.05;

rotate([-90, 0, 0]) {
difference() {
cube([dx + 2 * db, dt, 4 * dy + 5 * db]);
translate([db, 0, db]) {
cube([dx, dt, dy]);
translate([0, 0, dy + db])
  cube([dx, dt, dy]);
translate([0, 0, 2 * (dy + db)])
  cube([dx, dt, dy]);
translate([0, 0, 3 * (dy + db)])
  cube([dx, dt, dy]);
}
}
}