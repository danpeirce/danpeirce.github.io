use <write.scad>

inch = 25.4;
h_hole = 1/2*inch;
h_length = 2*inch;
h_thick = h_hole+4;
v_length = 2*inch;
v_thick = h_thick;
radius = 1/2*inch/2;
radius2 = 1/4*inch/2+1/64*inch/2;
clearance440 = 0.1285*inch;

difference()
{

    union()
    {
         cube([h_thick, h_length, h_thick]);                // h block for sensor
         translate([h_thick/2, h_length/2, h_thick])
             write("KPU Physics", t=2, rotate=90, center=true);

         translate([-v_length,h_length/2-v_thick/2,0])
             cube([v_length, v_thick, v_thick]);            // v block for support rod
         translate([-radius2, h_length/2-v_thick/2-radius2, 0]) 
             cube([radius2, radius2, h_thick]);             // fillet one
         translate([-radius2, h_length/2+v_thick/2, 0]) 
             cube([radius2, radius2, h_thick]);             // fillet two
         
    }
    translate([h_thick/2, -1, h_thick/2])  rotate([-90,0,0])           // hole h part
        cylinder(h_length+2, radius+1/64*inch/2, radius+1/64*inch/2, $fn=100);                                                                       
    translate([-1, h_length/2, h_thick/2])  rotate([-90,0,90])
        cylinder(h_length+2, radius2, radius2, $fn=100);          // hole for support rod
    translate([-radius2, h_length/2-v_thick/2-radius2, -1])
         cylinder(h_thick+2, radius2, radius2, $fn=100);             // trim fillet one
    translate([-radius2, h_length/2+v_thick/2+radius2, -1])
         cylinder(h_thick+2, radius2, radius2, $fn=100);             // trim fillet two
    translate([-0.3*inch, h_length/2-0.22*inch, -1])
         cylinder(h=h_thick+2, r=clearance440/2,  $fn=100);             // support hole 1
    translate([-0.3*inch, h_length/2+0.22*inch, -1])
         cylinder(h=h_thick+2, r=clearance440/2,   $fn=100);             // support hole 2
    translate([-0.3*inch-1.5*inch, h_length/2-0.22*inch, -1])
         cylinder(h=h_thick+2, r=clearance440/2,  $fn=100);             // support hole 3
    translate([-0.3*inch-1.5*inch, h_length/2+0.22*inch, -1])
         cylinder(h=h_thick+2, r=clearance440/2, $fn=100);              // support hole 4
    
//    translate([-v_length-1, 0-1, h_thick/2])                            // slice object in half
//       cube([v_length+h_thick+2, h_length+2, h_thick+2]);

}