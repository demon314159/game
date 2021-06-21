// f is between 0 and 1, no chamfer to full chamfer
module bat_boot(h, r, f) {
  intersection() {
    cylinder(h, r, r);
    cylinder(h + (1-f)*r, h + (1-f)*r, 0);
    translate([0,0,-(1-f)*r])
      cylinder(h + (1-f)*r, 0, h + (1-f)*r);
  }
}





