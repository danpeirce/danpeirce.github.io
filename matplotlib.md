title: Matplotlib

[TOC]

# matplotlib

     Notes by Dan Peirce (reformated from my pages at 
               danpeirce.net46.net/dokuwiki/

## Introduction

This Python language extension was created to combine plotting capabilities
similar to Matlab (similar syntax) with the Python programming language. There
is a introduction to matplotlib at
<http://matplotlib.sourceforge.net/users/intro.html> . matplotlib requires
another language extension called [ NumPy](http://www.numpy.org/) which
processes large arrays efficiently. NumPy is pre-installed on the [ Raspberry
Pi](raspberry_pi.html) Rasbian image.

From that link one can also find a tutorial on how to make plots from data. As
a simple python example that generated the plot shown down below:

    
    :::python
    import numpy as np
    import matplotlib.pyplot as plt
     
    # evenly sampled time at 200ms intervals
    t = np.arange(0., 5., 0.2)
     
    # red dashes, blue squares and green triangles
    plt.plot(t, t, 'r--', t, t**2, 'bs', t, t**3, 'g^')
    plt.show()

This little Python script generated this plot (was run on the [ Raspberry
Pi](raspberry_pi.html) ) ![](matplotlib/plot03.png)

The image shown above was saved as a *.png file. A screen shot of how it looks
on the Raspberry Pi remote desktop is shown below. This is the screenshot with
the remote Raspberry Pi desktop sitting on a windows XP desktop using the
tightvnc viewer. This can also be viewed on an Android tablet using [ android-
vnc-viewer](http://code.google.com/p/android-vnc-viewer/)

![](matplotlib/matplotlib_plot03.png)

## Installation

The Raspbian image has Python already installed. numpy is also installed. To
get matplotlib running on also needs **python-matplotlib** . To install just
run the following:

    
    :::sh
    sudo apt-get install python-matplotlib

You may also want to install the documentation

    
    :::sh
    sudo apt-get install python-matplotlib-doc

After the documentation install the manual will be available at

  * **/usr/share/doc/python-matplotlib-doc/html/index.html**

These packages can also be installed on windows PC's.

  * <http://www.scipy.org/Download>
  * <http://sourceforge.net/projects/matplotlib/files/>
  * <http://www.python.org/download/releases/2.7/>

## Advantages over Using Tkinter for Plotting

Matplotlab is a library that allows one to create a graphical plot without
worrying about the details of creating a GUI since matplotlab creates the
graphical window transparently in the background. It also creates good quality
plots with scales on the axis. For an alternative using Tkinter see

  * [example_using_python_and_tkinter](ultrasonic_ranger#example_using_python_and_tkinter)

## Related Python Language Extension SciPy

  * <http://www.scipy.org/>
  * <http://docs.scipy.org/doc/scipy/reference/tutorial/general.html>
  * <http://scipy.org/Getting_Started> \--I have started to work through some examples on the Raspberry Pi

    1. see [scipy](scipy.html)


    :::sh
    sudo apt-get install python-scipy

## Related IPython For Scientific Computing

Python has an interactive shell. IPython was developed to provide a more
feature rich interactive shell (by a physicist). Can install debian package
python-ipython and python-ipython-doc.

  * <https://www.pythonanywhere.com/try-ipython/>
  * <http://www.youtube.com/watch?v=3Fp1zn5ao2M> \-- introduction to NumPy and Matplotlib (examples are done in IPython) -- IPython notes [ipython_notes](ipython_notes.html)

