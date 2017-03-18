import markdown
import os, sys

mkin = open(sys.argv[1])
md = markdown.Markdown(extensions = ['toc(title=Table of Contents)', 'codehilite','meta'] )
gen_html = md.convert(mkin.read())
md_meta =  md.Meta
doc_title = md_meta.get('title')[0] # [0] -> first converts one element list to string


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

