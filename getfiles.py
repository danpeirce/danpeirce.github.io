import glob

print '''title: Site Map

# Site Map
'''
filelist = glob.glob('*.html')
filelist.sort()

filelist = [filename for filename in filelist if filename  != 'site_map.html']
filelist = [filename for filename in filelist if filename  != 'ModernPhysics.html']
filelist = [filename for filename in filelist if filename  != 'ModernTechnology.html']
filelist = [filename for filename in filelist if filename  != 'Physics_Major_Course_Grid.html']
filelist = [filename for filename in filelist if filename  != 'physics.html']

for filename in filelist:
    print '* [', filename, '](', filename, ')'
print ''

# [ ModernPhysics.html ]( ModernPhysics.html )
# [ ModernTechnology.html ]( ModernTechnology.html )
# [ Physics_Major_Course_Grid.html ]( Physics_Major_Course_Grid.html )

