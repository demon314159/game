$fa = 1;
$fs = 0.3;
wing_span = 20;
wing_width = 4;
thickness = 0.3;
wing_pitch = 5;
main_length = 5;
main_radius = 2;
tail_length = 10;
tail_radius = 0.7;
tail_wing_span = 8;
tail_wing_width = 3;
rudder_length = tail_wing_width;
rudder_height = rudder_length;
strut_radius = 0.3;
strut_angle = 30;
cockpit_radius = main_radius * 0.8;

//
// lower wing
//
translate([0,-wing_span/2,0])
  cube([wing_width, wing_span,thickness]);
//
// upper wing
//
translate([0,-wing_span/2,wing_pitch])
  cube([wing_width, wing_span,thickness]);

difference() {  
translate([0,0,main_radius])  
  rotate([0,90,0])  
    cylinder(main_length, main_radius, main_radius);
translate([main_length*.75,0,main_radius + cockpit_radius])
sphere(cockpit_radius);  
}    
    
    
translate([main_length,0,main_radius])  
  rotate([0,90,0])   
    cylinder(tail_length, main_radius, tail_radius);
translate([main_length + tail_length,0,main_radius])
  sphere(tail_radius);
translate([0,0,main_radius])
  sphere(main_radius);
 

  



translate([main_length + tail_length-tail_wing_width,-tail_wing_span/2,main_radius])
  cube([tail_wing_width, tail_wing_span, thickness]);

intersection() {
translate([main_length + tail_length - rudder_length,0,main_radius])
cube([rudder_length*1.2,thickness,rudder_height]);
translate([main_length+tail_length-rudder_length,0,main_radius])
rotate([0,45,0])
cube([rudder_length * 2, thickness, rudder_height * 2]);
}
translate([wing_width/2,wing_span*3/8,0])
cylinder(wing_pitch, strut_radius, strut_radius);
translate([wing_width/2,-wing_span*3/8,0])
cylinder(wing_pitch, strut_radius, strut_radius);
translate([wing_width/2,0,wing_pitch - wing_pitch * cos(strut_angle)+thickness / 2])
rotate([strut_angle,0,0])
cylinder(wing_pitch, strut_radius, strut_radius);
translate([wing_width/2,0,wing_pitch - wing_pitch * cos(strut_angle)+thickness / 2])
rotate([-strut_angle,0,0])
cylinder(wing_pitch, strut_radius, strut_radius);

