title: Python Markdown

# Python Markdown

* This page is a replacment for <http://danpeirce.net46.net/dokuwiki/doku.php?id=python_markdown>

New updates will be made here rather than there (at least that is what I am thinking now).

[TOC]

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
    md = markdown.Markdown(extensions = ['toc(title=Table of Contents)', 'codehilite','meta'], output_format="html5")
    gen_html = md.convert(mkin.read())
    md_meta =  md.Meta
    doc_title = md_meta.get('title')[0] # [0] -> converts one element list to string
        
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
    gen_html = md.convert(mkin.read())

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



## Converting from DokuWiki

I have worked out a method to convert my dokuwiki pages to static html using markdown as the new working file format.
The method was inspired by <http://donaldmerand.com/code/2012/07/20/how-i-actually-convert-dokuwiki-to-latex.html>. 
Despite the name given to that page this is relevant since he actually talks a lot about converting dokuwiki to markdown

The steps I am using are

1.    Convert the DokuWiki page to HTML. 
     This is done using **dokucli.php** which should be put in the dokuwiki/bin folder. On my Rasperry Pi it is at **/var/www/danp/dokuwiki/bin/dokucli.php**.  

     The command is 

         **php /var/www/danp/dokuwiki/bin/dokucli.php  < {dokuwiki_file.txt} > {newfile.html_}** 

     The file dokuwiki.php comes from <https://www.dokuwiki.org/tips:dokuwiki_parser_cli>

2.    The new HTML file may or may not require some cleanup as references to the path on the raspberry pi need to be removed and some non-Ascii characters may be pressent and need to be removed or converted to Ascii (Markdown will not work with non-Ascii in the file. 

         **python cleanhtml.py newfile.html_ > newfile.html__ **  

     (note that the input file ends in one underscore and the output file name ends in two underscores)

     I wrote cleanhtml.py myself and I am adding new non-ascii characters as I go. Notes on the webpage that gave me insight into this have be lost. [cleanhtml.py](cleanhtml.py)

3.    Now the file should be ready to be converted to Markdown markup language.
     ./html2text.py < newfile.html__ > newfile.md  -> {if cleanup was needed use the cleaned file}

     html2text.py is from [https://github.com/aaronsw/html2text](https://github.com/aaronsw/html2text)

4.    A few adjustments are edited into the markdown file. This generally easy to do in a text editor (I typically using vim).
     1.    I am using the meta extension and put 

               title:{pagetitle}

           at the top of each markdown page.

     2.    I put **TOC** in square brackets where I want the Table of Contents to go (using the TOC extension).

     3.    In dokuwiki the local links are just the name of the page without an extension. I add the html extension and tweek the path if needed.

     4.     Images that are in a subdirectory require the : be replaced with a / in the path.

5.    The markdown file is converted to an HTML file.

         python makehtml.py newfile.md newfile.html

      My [makehtml.py](makehtml.py) was modified from [make_toc.py](../markdown/make_toc.py). 
      See [make_toc.html](../markdown/make_toc.html). 

## BeatifulSoup for Extracting Section of Web Page

Sometimes one needs only part of an existing webpage for conversion to Markdown.BeatifulSoup can be used to extract some part of a bigger page. A simple example in which I wanted to backup only particular divisions of a page generated by a CMS before the site was to be migrated to a different CMS.

    #!/usr/bin/python
    
    import urllib2 
    from BeautifulSoup import BeautifulSoup
    
    soup = BeautifulSoup(urllib2.urlopen('http://www.kpu.ca/science/physics.html').read())
    
    idcontent = soup.find("div", {"id": "content"}) 
    print idcontent
    
    idsidebar = soup.find("div", {"id": "sidebar"}) 
    print idsidebar

This finds the div tag in which the **id** was set to "content" and the id for which the **id** was set to "sidebar"
    
