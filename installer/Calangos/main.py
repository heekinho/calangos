import sys,os
#print sys.path
#print sys.path[0]
bindir=os.path.abspath(sys.path[8])
#print bindir
gameenv=os.environ
#print gameenv['PATH']
gameenv['PATH'] += os.pathsep + bindir
os.execle('calangos.exe',gameenv)