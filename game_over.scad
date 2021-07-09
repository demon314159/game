$fa = 1;
$fs = 0.1;
mag = 1 / 15;
thickness = mag * 1;
height = mag * 15;
width = mag * 10;
border = mag * 1;
translate([2.1 - width, 0.0, -4.0])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("GAME OVER", size = 0.4, halign = "center");