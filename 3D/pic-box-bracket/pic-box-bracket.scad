inch = 25.4;

// distance between centers of mounting  holes
mnt_width = 1.966 * inch; 
mnt_length = 4.326 * inch;
// distance between centers box holes
box_hole_width = 2.390 * inch;
box_hole_length = 4.730 * inch;

// Lid board supports
sup_rad = 0.106 * inch;
hole_rad = 0.048 * inch;
sup_hight = 0.196 * inch;

hole_boss_rad = 0.108 * inch;

// outside box dim
box_length = 5.308 * inch;
box_width = 2.942 *inch;

// lid thickness
lid_thickness = 0.123 * inch;

mnt_hole_dis = 0.488 * inch - lid_thickness;
box_hole_disx = 0.286 *inch - lid_thickness;
box_hole_disy = 0.276* inch - lid_thickness;

ttl_usb_x = 35.7;
ttl_usb_y = 16.03;

pic_x = 76.0;
pic_y = 30;

//

module plate()
{
        cube([box_length-2*lid_thickness, box_width-2*lid_thickness, lid_thickness]);
}

module hole(x_dis, y_dis, rad)
{
     translate([x_dis, y_dis, -1]) 
        cylinder(h= lid_thickness*2+2, r = rad, center=false,$fn=100);
}

module boss(x_dis, y_dis, rad)
{
     translate([x_dis, y_dis, lid_thickness-0.2]) 
        cylinder(h= 0.2*inch-lid_thickness+0.2, r = rad, center=false,$fn=100);    
}

module ttl_usb_platform()
{   difference()
    {
        translate([0.1, (box_width-2*lid_thickness)/2-(ttl_usb_y+2.54*2)/2, +0.1])
            cube([ttl_usb_x+2.54, ttl_usb_y+2.54*2, 1.6+4.42+0.1]);
        translate([-0.1, (box_width-2*lid_thickness)/2-(ttl_usb_y+0.3*2)/2, 4.42])
            cube([ttl_usb_x+0.3, ttl_usb_y+0.3*2, 4.42+0.1]);
        translate([-0.1, (box_width-2*lid_thickness)/2-(ttl_usb_y-0.5*2)/2, -0.2])
            cube([ttl_usb_x-0.5, ttl_usb_y-0.5*2, 8+0.1]);
    }
}

module pic_platform_hole()
{
     translate([ttl_usb_x+2+lid_thickness, 2*lid_thickness+6,-0.1 ])
         cube([pic_x, pic_y, 2*lid_thickness]);
}

module tab(x_dis, y_dis)
{
    translate( [x_dis, y_dis, 0.1] )
      cylinder(h=lid_thickness-.2, r =4 , center=false, $fn=16);
}

module pic_platform()
{
     translate([ttl_usb_x+2-2+lid_thickness, 2*lid_thickness+6-2-0.5,lid_thickness-0.1])
          cube([pic_x+2*2-1.2, 2, 1.6+0.1]);
     translate([ttl_usb_x+2-2+lid_thickness, 2*lid_thickness+6-2+0.5+2+pic_y,lid_thickness-0.1])
          cube([pic_x+2*2-1, 2, 1.6+0.1]);
     translate([ttl_usb_x+2-2+lid_thickness-0.6, 2*lid_thickness+6-2-0.5,lid_thickness-0.1])
          cube([2, pic_y+2*2+1,  1.6+0.15]);
     translate([ttl_usb_x+2-2+lid_thickness+0.6+pic_x+2, 2*lid_thickness+6-0.5,lid_thickness-0.1])
          cube([2, pic_y+2*2+1,  1.6+0.15]);
      tab(ttl_usb_x+2+lid_thickness, 2*lid_thickness+6);
      tab(ttl_usb_x+2+lid_thickness + pic_x-3.5, 2*lid_thickness+6);
      tab(ttl_usb_x+2+lid_thickness, 2*lid_thickness+6 + pic_y);
      tab(ttl_usb_x+2+lid_thickness + pic_x, 2*lid_thickness+6 + pic_y);
}

module trim(x_dis, y_dis, x_size, y_size)
{
    translate([x_dis, y_dis, -0.1])
        cube([x_size, y_size,lid_thickness+0.2]);
}

difference()
{
    union()
    {
        plate();
        boss(mnt_hole_dis, mnt_hole_dis, sup_rad+0.2);
        boss(mnt_hole_dis + mnt_length, mnt_hole_dis, sup_rad+0.2);
        boss(mnt_hole_dis, mnt_hole_dis+mnt_width, sup_rad+0.2);
        boss(mnt_hole_dis+mnt_length, mnt_hole_dis+mnt_width, sup_rad+0.2);
        
    }
    hole(mnt_hole_dis, mnt_hole_dis, hole_rad+0.3);
    hole(mnt_hole_dis + mnt_length, mnt_hole_dis, hole_rad+0.3);
    hole(mnt_hole_dis, mnt_hole_dis+mnt_width, hole_rad+0.3);
    hole(mnt_hole_dis+mnt_length, mnt_hole_dis+mnt_width, hole_rad+0.3);
    hole(box_hole_disx, box_hole_disy, hole_boss_rad+0.5);
    hole(box_hole_disx+box_hole_length, box_hole_disy, hole_boss_rad+0.5);
    hole(box_hole_disx, box_hole_disy+box_hole_width, hole_boss_rad+0.5);
    hole(box_hole_disx+box_hole_length, box_hole_disy+box_hole_width, hole_boss_rad+0.5);
    translate([-0.1, (box_width-2*lid_thickness)/2-(ttl_usb_y-0.5*2)/2, -0.2])
            cube([ttl_usb_x-0.5, ttl_usb_y-0.5*2, 8+0.1]);
    pic_platform_hole();
    trim(-0.1, -0.1, box_length, 5);
    trim(-0.1, box_width-10, box_length, 5);
    trim(-0.1, -0.1, 5, box_width/2-ttl_usb_y/2-8);
    trim(-0.1, box_width-box_width/2+ttl_usb_y/2+3, 5, box_width/2-ttl_usb_y/2-8);
    trim(-0.1+box_length-12, -0.1, 6, box_width);
    trim(17, box_width-25, 92, 20);
}
ttl_usb_platform();
pic_platform();


