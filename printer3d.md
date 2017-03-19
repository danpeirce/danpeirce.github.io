title: 3D Printing

[TOC]

# 3D Printing Notes
    by Dan Peirce B.Sc.
    
## The tinkerines 3D Printer

The Ditto+ 

* <http://www.tinkerines.com/store/3d-printers/ditto-plus/> -- includes spec's
* [Ditto+ Assembly Manual](http://www.tinkerines.com/Ditto_Kit.pdf)
* [Calibration Manual](http://www.tinkerines.com/Calibration.pdf)
* [T.I.M (LCD/SD Interface) Manual](http://www.tinkerines.com/Manual_LCD.pdf)

It is pointed out in the Calibration Manual that there are settings for the 
software that control things like

1. The shell thickness
2. The amount of fill
3. the fill pattern

These settings can be adjusted. For example the default fill is only 10%. This 
conserves both material and the time it takes to print. It means there will be 
voids in an otherwise solid part and that one does not need to put these voids
in the 3D model.

It is also possible to turn on a feature that will automatically create 
supports for any parts with extreme overhang (more than 50 degrees). Presumably these
supports can be broken off after the part is complete. I would take this to mean that
parts can be quite arbitrary in design and easily include assembly tabs.
for places that have extreme overhang.

### Software For Controlling Ditto+

* [Coordia: Ditto Control Host -Beta-](http://www.tinkerines.com/coordia-ditto-control-host-beta/)
* [http://www.tinkerines.com/faq/](http://www.tinkerines.com/faq/)
* <http://slic3r.org/>
* <http://fabmetheus.crsndoo.com/>
* <https://github.com/kliment/Printrun>


## 3D Modeling Software

Creating 3D models to be printed requires software.

Both FOSS and Proprietary Packages are Available.

### Proprietary Software

1. Solidworks
2. others... (don't recall at the moment)

### Free Open Source Software

(The software that controls the Ditto+ is also open source)

1. Blender 
    * This software was development for modelling scenes, sets and animations. It can be used
      with 3D models for 3D printers but it was designed for use by artists.
    * The minimum hardware requirements mean that it can't install this on anything
      I have at home.

2. [OpenSCAD](openscad.html)
    * This software was developed for modelling parts to be printed on a 3D printer. It 
      is still at version 1. This will run on a netbook computer. One builds a model by 
      writting a script that defines cubes, cylinders and other basic shapes that can be 
      combined for the custom part.
    * on <http://www.openscad.org/> they say *"OpenSCAD The Programmers Solid 3D CAD Modeller"*

#### Using OpenSCAD to Make 3D Solid Models of Parts

There is a part we require for ASTR1100. I have put together our new photometers for Richmond. I still need a fitting to connect the sensor tube to the support rod. I decided try making a 3D solid model of the part as I envision it. Currently I have two versions.

![First Part](cylinders.png "First Part")

After reading more on 3D printers and thought I should change the design to make a stronger 
part. Keep in mind that in general that to keep costs down 3D parts are most often printed as 
a shell with less dense fill. The area interior to the shell is typically made much less dense by including voids. Also I have read that the parts tend to be weakest in the Z direction since the shell and fill are built up one layer at a time. The part essentially ends up as multiple layers laminated together. 

The new model looks as shown in these photos

![Fitting for Photometer](support_astr1100.png "Fitting for Photometer, ASTR1100")

Also, added some text to the object.

![Fitting with KPU Message](support_astr1100_kpu.png "Fitting with KPU Message", ASTR1100")

I also exported a cutaway view of the part which allow all the features to been seen together.
The extra new holes should help to provide support for the shell of the support rod hole.
These holes are sized to accept a #4-40 machine screw.

![Cutaway View](support_astr1100cut.png "Cutaway View of Fitting for Photometer")



## Old Promotional Video for Ditto

<http://www.youtube.com/watch?v=mwNpNNtUz8g&feature=youtu.be>
