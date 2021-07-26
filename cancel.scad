label = "HIT ALL TARGETS TO CANCEL AN OUT";
$fa = 1;
$fs = 0.1;
mag = 1 / 15;
thickness = mag * 1;
translate([0, -(thickness *3)/ 4, -6.375])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text(label, size = 0.2, halign = "center");
