  
chan_description = 
chan_lastbuilddate = 'Fri, 12 Jul 2013 08:50:24 GMT'


def item1():
      print ''

def item2():
      print ''

def title( msg ):
      print '    <title>' + msg + '</title>'

def lastbuilddate( lbd ):
      print '    <lastbuilddate>' + lbd + '</lastbuilddate>'

def makechannel():
      TITLE = 'Python Markdown'
      LINK  = 'http://www3.telus.net/danpeirce/notes/python_markdown.html'
      DESCRIPTION = 'Notes on using Python Markdown to generate HTML5 webpages. ' +
                    'The python_markdown.html page was generated using Python Markdown.'
      BUILD_DATE =  'Fri, 12 Jul 2013 08:50:24 GMT'
      print '  <channel>'
      title( TITLE )
      link( LINK )
      description( DESCRIPTION )
      lastbuilddate( BUILD_DATE )
      item1()
      item2()
      print '  </channel>'


def makerss2():
      print '<rss version="2.0">'
      makechannel()
      print '</rss>'

print '<?xml version="1.0" encoding="iso-8859-1"?>'
makerss2()
