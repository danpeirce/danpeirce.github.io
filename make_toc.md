title:Using Markdown Extensions

[TOC]
# Using Markdown
The PHP web-host I have been using is not always very reliable. 
I thought I might want to try something different.
I had looked at Markdown before and thought it was somewhat limited compared
to dokuwiki markup but I decided to give it another look because I see Markdown
showing up in various places. I am also now seeing that it has extensions that
expand it's capabilities.

## Auto-Generating HTML5 with a Table of Contents
One of the things I like about dokuwiki is that it automatically generates a table of contents.
When I saw the extensions for Markdown at [pythonhosted.org](http://pythonhosted.org/Markdown/extensions/index.html)
it occurred to me that Markdown might actually provide what I need. The 
Python file that was used to convert the markdown file [make_toc.md](make_toc.md) to
an HTML5 file is [make_toc.py](make_toc.py). The Python file is short enough to show here.

This is a combination of actual Python with multi-line string objects that 
contain some pre-written HTML.


    :::python
    import markdown
    import os, sys

    mkin = open(sys.argv[1])
    md = markdown.Markdown(extensions = ['toc(title=Table of Contents)', 'codehilite','meta'])
    gen_html = md.convert(mkin.read())
    md_meta =  md.Meta
    doc_title = md_meta.get('title')[0][0:] # [0] -> first converts one element list to string
                                            # [0:] -> removes u' from start of string
                                            #           and ' from end of string

    output = [ """<!DOCTYPE html>
    <html>
      <head>
        <meta charset="utf-8">
        <link href="white.css" type="text/css" rel="stylesheet" />
        <link href="default.css" type="text/css" rel="stylesheet" />
        <title>%(title)s</title>
      </head>

    <body>
    """ % { 'title' : doc_title } 
    ]


    output.append( gen_html )

    output.append( """

    </body>

    </html>
    """ )

    outfile = open(sys.argv[2], 'w')
    outfile.write(''.join(output))
    outfile.close()

    # end


The line that converts the Markdown text to html is

    :::python
    output.append( markdown.markdown(mkin.read(), extensions=['toc(title=Table of Contents)', 'codehilite']) )

Markdown does not include code for opening the top of the HTML file or closing 
at the end so literal multi-line strings are used to add those and the HTML
converted from Markdown is inserted in the middle.

The Python file was invoked as follows:

    :::bash
    python make_toc.py make_toc.md make_toc.html


### The CSS Style Sheets Used
I copied the CSS style Sheets used here from the web since they were available
and shared freely. 

* white.css was modified from [avenir-white.css](https://github.com/jasonm23/markdown-css-themes)
* default.css was taken from [default.css](https://github.com/richleland/pygments-css) -- used with Pygments for syntax highlighting.

## Syntax Highlighting Using Pygments

### Installing Pygments
On my Debian system Pygments was not pre-installed but it is a standard Debian 
Package.

    :::bash
    sudo apt-get install python-pygments

For a MS Windows computer that is not going to work. 
See [installing-python-pygments-on-windows](http://zduck.com/2009/installing-python-pygments-on-windows/)

### Example of C with Syntax Highlighting

    :::c
    #include <stdio.h>

    void main(void)
    {
        printf("Hello World");
    }

## Meta Extension to Read Title from Markdown File

The Markdown file requires the following on the first line:

    :::markdown
    title:{page title goes here}

For this to be seen as meta data it must occur on the first line. The first blank line in the
file indicates the end of the meta data.

Code as been added to the **make_toc.py** file to read the title and add it between *title*
tags in the generated HTML5 file. 
