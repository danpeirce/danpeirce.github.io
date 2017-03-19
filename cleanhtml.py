# -*- coding: utf-8 -*-

import os, sys

replacedic = {
        '/var/www/danp/dokuwiki/bin/doku.php?id='             : '' ,
        '/var/www/danp/dokuwiki/bin/lib/exe/detail.php?id='   : '' , 
        '/var/www/danp/dokuwiki/bin/lib/exe/fetch.php?media=' : '' ,
        '/var/www/danp/dokuwiki/bin/lib/exe/fetch.php?'       : '' ,
        '&amp;media='                                         : '' ,
        '“'                                                   : '"',
        '”'                                                   : '"',
        '–'                                                   : '--' ,
        '…'                                                   : '...',
        '→'                                                   : '->' ,
        'υ'                                                   : 'u'  ,
        '×'                                                   : 'by' ,
        'Ω'                                                   : 'ohm' ,
        '×'                                                   : 'by'  ,
        }
 
oldfile = open(sys.argv[1])

text = oldfile.read()
oldfile.close()

for i, j in replacedic.iteritems():
    text = text.replace(i, j)

print text
    

