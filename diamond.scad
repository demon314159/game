$fa = 1;
$fs = 0.04;
mag = 1;
thickness = mag * 0.05;
wback = mag * 6.235;
//wfront = mag * 5.529;
wfront = wback;
length = mag * 9.4;
f = 0.98;
base_length = 4.4;
mat_length = 0.5;
angle = 50;
pthick = 0.2;
plate_length = 0.25;


translate([0,0.01,2])
rotate([90,0,0]) 
linear_extrude(thickness) {
    
translate([0,-1-mat_length/3,0]) {
square([plate_length,plate_length/2],center=true);
translate([0,plate_length/4,0])
rotate([0,0,45])
square(plate_length*cos(45),center=true);
}
translate([-pthick/2+base_length*cos(angle), -1-base_length*sin(angle),0])
square(plate_length, center=true);
translate([pthick/2-base_length*cos(angle), -1-base_length*sin(angle),0])
square(plate_length, center=true);
translate([0, pthick/2-1-2*base_length*sin(angle),0])
square(plate_length, center=true);

translate([0,-1-pthick/2,-thickness])
//rotate([0,0,45])
square([mat_length,mat_length],center=true);

translate([pthick/2-cos(angle)*base_length,-1-sin(angle)*base_length,-thickness])
//rotate([0,0,45])
square([mat_length,mat_length],center=true);

translate([-pthick/2+cos(angle)*base_length,-1-sin(angle)*base_length,-thickness])
//rotate([0,0,45])
square([mat_length,mat_length],center=true);

translate([0,-1+pthick/2-2*sin(angle)*base_length,-thickness])
//rotate([0,0,45])
square([mat_length,mat_length],center=true);

translate([0,-1,-2*thickness])    
rotate([0,0,-angle])
//linear_extrude(thickness, center = true)
translate([base_length/2,0,0])
square([base_length,pthick], center=true);    

translate([0,-1,-2*thickness])    
rotate([0,0,angle])
translate([-base_length/2,0,0])
square([base_length,pthick], center=true);    

translate([cos(angle)*base_length,-1 -sin(angle)*base_length,-2*thickness])    
rotate([0,0,angle])
translate([-base_length/2,0,0])
square([base_length,pthick], center=true);    

translate([-cos(angle)*base_length,-1 -sin(angle)*base_length,-2*thickness])    
rotate([0,0,-angle-180])
translate([-base_length/2,0,0])
square([base_length,pthick], center=true);    
}
