$fa = 1;
$fs = 0.1;

rotate([0,0,30])
translate([0,0,0.75])
rotate([0,0,0]) {

translate([-0.2,0,-0.1]) {
// right leg    
//cylinder(1.2,0.2, 0.1);

// right shoe    
//translate([0,0.2, 1.2])
//scale([0.2,0.4,0.1])
//sphere(1);
}

translate([0.2,0,-0.1]) {
// left leg    
//cylinder(1.2,0.2, 0.1);

// left shoe    
//translate([0,0.2, 1.2 ])
//scale([0.2,0.4,0.1])
//sphere(1);
}

// torso
//translate([0,0,-0.8])
//scale([0.6,0.4,1])
//sphere(1);

// neck
//translate([0,0,-2])
//cylinder(0.3,0.2,0.2);

// head
//translate([0,0,-2.3])
//sphere(0.4);

// right arm
//translate([-0.6,0,-1.4])
//rotate([0,-10,0])
//cylinder(1,0.2,0.1);

// left arm
//translate([0.6,0,-1.4])
//rotate([0,10,0])
//cylinder(1,0.2,0.1);

// shoulders
//translate([0,0,-1.45])
//scale([0.8,0.3,0.3])
//sphere(1);

// right hand
//translate([-0.8,0,-0.3])
//scale([1,0.5,1])
//sphere(0.2);

// left hand
//translate([0.8,0,-0.3])
//scale([1,0.5,1])
//sphere(0.2);

// nose
//translate([0,0.35,-2.2])
//scale([0.5,1,0.5])
//  sphere(0.2);

// left eye
translate([0.21,0.35,-2.4])
  sphere(0.08);
  
// right eye  
translate([-0.21,0.35,-2.4])
  sphere(0.08);
}

