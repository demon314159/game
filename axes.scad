length = 6;
dummy = 0.01;
cube([length,dummy, dummy], center=true);
cube([dummy, length, dummy], center=true);
cube([dummy, dummy, length], center=true);