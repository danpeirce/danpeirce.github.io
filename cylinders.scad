inch = 25.4;
difference(){
    union() {
        translate([0, 0, inch/4+2])
        cylinder (h = 2*inch, r=inch/4+4);
        translate([-inch/2, 0, inch/4+2])
        rotate ([0,90,0]) cylinder (h = inch, r=inch/4+4);      
    }        
    union() {
        translate([0, 0, inch/4+2+inch/4+inch/8])
        cylinder (h = 2*inch+4, r=inch/8);
        translate([-inch/2-2, 0, inch/4+2])
        rotate ([0,90,0]) cylinder (h = inch+4, r=inch/4+.4);      
    }
}