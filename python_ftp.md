title: Python and FTP

[TOC]

# Python and FTP

  * <http://love-python.blogspot.ca/2008/02/ftp-file-upload.html>

That page gives a very short simple Python code to FTP a file. I tried adapting it to send a little text file to my Telus webspace. 

Note that {username} and {password} were replaced with my actual user name and password.


    :::python
    import ftplib

    ftp = ftplib.FTP('ftp.shaw.ca','{username}','{password}') # Connect
    fp = open('try.txt','rb') # file to send
    ftp.storbinary('STOR try.txt', fp) # Send the file

    fp.close() # Close file and FTP
    ftp.quit()


<iframe src="http://members.shaw.ca/danpeircenotes/try.txt" 
 style="float: right; 
 width: 260px; height: 130px; 
 margin-left: 12px; border: 1px solid black;" >Alternative Content</iframe>


It worked! The python code was put in a file called **ftp.py**. \\ 
I also created a little text file with a short message called **try.txt**.

The result in this inline window shown here at the far right. You could also look at it using this link 
<http://members.shaw.ca/danpeircenotes/try.txt>.
This would be more interesting if I the python code created some content generated on the fly. 
Perhaps temperature data. For a start I'd try just sending the time time of day.


## Sending Time of Day 

To send the time of day I changed the python file as follows


    :::python
    import ftplib
    from time import strftime


    def uploadfile():
        ftp = ftplib.FTP('ftp.shaw.ca','{username}','{password}') # Connect
        fp = open('time.txt','rb') # file to send
        ftp.storbinary('STOR time.txt', fp) # Send the file

        fp.close() # Close file and FTP
        ftp.quit()

    def buildfile():
        f = open('time.txt', 'w')
        f.write(strftime("%Y-%m-%d %H:%M:%S"))
        f.close()

    buildfile()
    uploadfile()

The result can be seen at <http://members.shaw.ca/danpeircenotes/time.txt>.
The date and time represent the last time the file was last updated. In addition to time sensor date could be included.


Rather than overwriting the file each time it is possible to append the file so that each update time is kept and a list 
of update times is created.


    :::python
    import ftplib
    from time import strftime


    def uploadfile():
        ftp = ftplib.FTP('ftp.shaw.ca','{username}','{password}') # Connect
        fp = open('time_a.txt','rb') # file to send
        ftp.storbinary('STOR time_a.txt', fp) # Send the file

        fp.close() # Close file and FTP
        ftp.quit()

    def buildfile():
        f = open('time_a.txt', 'a')
        f.write(strftime("%Y-%m-%d %H:%M:%S"))
        f.write('\n')
        f.close()

    buildfile()
    uploadfile()

The result can be seen at <http://members.shaw.ca/danpeircenotes/time_a.txt>.

## Dynamically Creating Static HTML 

Previous examples created simple text files. It is also possible to create HTML files. There are a variety of techniques for this. I decided to try the technique shown on the following website.

  * http://anh.cs.luc.edu/python/hands-on/3.1/handsonHtml/webtemplates.html


I also decided to change the template to a basic html5 template to be much like my index.html page on my www3.telus.net site. The intent is to have a page that is still friendly to mobile devices as well as bigger computers. The other modification of the webtemplates.html example is that I have included the ftp upload as given in my previous examples rather than opening a web browser to view the result.


    :::python
    import ftplib
    from time import strftime
    
    # this section is the template. It is a multi-line string assigned to the variable pageTemplate.  Inside
    #    the string is a placeholder {time} for the dynamic time string.
    pageTemplate = '''
    <!DOCTYPE html> 
    <html>
    <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, user-scalable=yes" />
    <link media="Screen" href="test.css" type="text/css" rel="stylesheet" />
    <link media="handheld, only screen and (max-width: 480px), only screen and (max-device-width: 480px)" href="mobile.css"
    
    type="text/css" rel="stylesheet" />
    
    <title>Dynamic Generation of Static HTML5 and Automatic FTP Upload</title>
    </head>
    <body>
      <div id="header"><hr />
        <h1>Dynamic Generation of Static HTML5 and Automatic FTP Upload</h1><hr />
      </div>
      <div id="container">
      <div id="content">
      <p>The date and time this file was last updated was {time}
      </p>
      </div>
      </div> <!-- container -->
      <div id="footer" ><hr /> <a href="#header">Back to top of page</a><hr />
      </div>
    </body>
    </html>'''  # NEW note '{time}' seven lines up
    
    
    def strToFile(text, filename='time.html'):
        """Write a file with the given name and the given text."""
        output = open(filename,"w")
        output.write(text)
        output.close()
    
    def uploadfile():
        ftp = ftplib.FTP('ftp.shaw.ca','{username}','{password}') # Connect
        fp = open('time.html','rb') # file to send
        ftp.storbinary('STOR time.html', fp) # Send the file
    
        fp.close() # Close file and FTP
        ftp.quit()
    
    def main():    # NEW
        time = strftime("%Y-%m-%d %H:%M:%S") 
        contents = pageTemplate.format(**locals())   # this puts the variable time into the {time} space holder in the string
        strToFile(contents) 
        uploadfile()
    
    main()
 



The uploaded page looks like this: **it can also be seen at** 
<http://members.shaw.ca/danpeircenotes/time.html>  

Also, the same folder on the server contains two css files that don't change 

  * <http://members.shaw.ca/danpeircenotes/test.css>
  * <http://members.shaw.ca/danpeircenotes/mobile.css>


<iframe src="http://members.shaw.ca/danpeircenotes/time.html"  
 width="100%" height="300" border: 1px solid black;" >iframe normally shows page at http://members.shaw.ca/danpeircenotes/time.html</iframe>


## Python Pickle
It is probably unnecessary to upload data to the web server too frequently. 
It would be more practical to store data locally 
on the Raspberry Pi and update the server just a few times a day. 
The data can be stored in data structures in ram but 
should be saved to files periodically to avoid loss  of data. 
Pickel can be used when saving a data structure.

* <http://python.about.com/od/pythonstandardlibrary/a/pickle_intro.htm>



## Data Exchange Formats 
Often it is not ideal to convert data directly to html. One may want 
to store the data in a database or data exchange format. 

Examples of data exchange formats are XML and JSON.

The advantages of a data exchange format are

* the data can be easly moved from one type of platform to another
* information can be easily extracted from the data file using scripts 
  of anyone of a number of languages including Python, 
  Perl, PHP, javascript, ... depending on preference and circumstance.


## other 

* [network_protocols](netork_protocols.html)
* <http://effbot.org/librarybook/ftplib.htm>


<http://www.broadbandreports.com/faq/10283>

