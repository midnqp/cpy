#!/usr/bin/python3.10
import os, sys

strs = {}
strs['cmd'] = "gcc -Wall -Wextra -Wno-unused-value -g -fsanitize=address  -fcompare-debug-second -I ."
strs['err'] = "Compilation error"
strs['compilation_script'] = "\033[94mCompilation Script\033[0m 📃"
strs['cpy'] = "🚀\033[32mCPY\033[0m"

files = {}
files['cpy'] = [ 'cpy-core.c', 'cpy-file.c', 'cpy-list.c', 'cpy-print.c', 'cpy-string.c']

dirs = {}
dirs['out'] = './out'
dirs['obj'] = dirs['out'] + '/objects'
dirs['so'] = dirs['out'] + '/so'


def mkdirs():
    global dirs
    for key in dirs:
        if (os.path.isdir(dirs[key]) == False):
            os.mkdir(dirs[key])
    

def perror(string, exit=False):
    print('\033[31m[error]\033[0m ' + string)
    if (exit == True):
        sys.exit()

def pokay(string):
    print('\033[32m[okay]\033[0m ' + string)

def plog(string):
    print('\033[32m[log]\033[0m ' + string)

def script(argList):
    global strs, dirs
    scriptPath = argList[1]
    ret=0
    mkdirs()

    if os.path.exists(dirs['so']+'/libcpy.so') == False:
        perror('CPY shared object not found')

    plog('Compiling script to binary executable.')
    ret = os.system("{} -L {} -o {}/a.out {} -lcpy".format(strs['cmd'], dirs['so'], dirs['out'], scriptPath))
    if (ret != 0):
        perror(strs['err'], True)

def build(argList):
    global strs, files
    ret = 0
    cpyFiles = files['cpy']
    mkdirs()

    plog("Compiling with PIC to object")
    for i in range(len(cpyFiles)):
        filename = os.path.splitext(cpyFiles[i])[0]
        ret = os.system("{} -c -fpic -o {}/{}.o ./{}.c".format(strs['cmd'], dirs['obj'], filename, filename))
        if (ret != 0):
            perror(strs['err'], True)

    plog("Creating shared library")
    ret = os.system("{} -shared -o {}/libcpy.so {}/*".format(strs['cmd'], dirs['so'], dirs['obj']))
    if (ret != 0):
        perror(strs['err'], True)

def startup():
    print("""
---------------------------
|                         |
|   {}                 |
------{}
""".format(strs['cpy'], strs['compilation_script']))

def help(argList):
    global strs
    print(
    """Usage:
\033[36m[commands]  [desc]
            [positional args]
\033[0m

build       Builds the CPY shared object.
script      Compiles your CPY script.
            [path to script]
""")




startup()
cmdList = {'build': build, 'script': script, 'help': help}
args = sys.argv
if (len(args) < 2 or args[1] not in cmdList):
    help(None)
    sys.exit()
else:
    cmdList[args[1]](args[1:])
