$fa = 1;
$fs = 0.1;
mag = 1 / 15;
thickness = mag * 1;
height = mag * 15;
width = mag * 10;
border = mag * 1;
translate([0,0,height/3.5])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("9", size = 0.6, halign = "center");
