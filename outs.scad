$fa = 1;
$fs = 0.1;
mag = 1 / 15;
thickness = mag * 1;
height = mag * 15;
width = mag * 10;
border = mag * 1;
difference() {
cube([3 * width,thickness,height], center = true);
{    
cube([width - 2 * border, thickness, height - 2 * border], center = true);
translate([-width, 0, 0])
    cube([width - 2 * border, thickness, height - 2 * border], center = true);
translate([width, 0, 0])    
    cube([width - 2 * border, thickness, height - 2 * border], center = true);
}
}
translate([width,0,height/3.5])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("3", size = 0.6, halign = "center");
translate([0,0,height/3.5])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("2", size = 0.6, halign = "center");
translate([-width,0,height/3.5])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("1", size = 0.6, halign = "center");
translate([0,0,-height*0.6])
rotate([-90,0,0])
  linear_extrude(height = thickness)
  text("OUTS", size = 0.4, halign = "center");