#!/usr/bin/python3.10
import os, sys

strs = {}
#strs['cmd'] = "gcc -Wall -Wextra -Wno-unused-value -g -fsanitize=address  -fcompare-debug-second -I ."
strs['cmd'] = "gcc -Wall -Wextra -Wno-unused-value -g  -fcompare-debug-second -I ."
strs['err'] = "Compilation error"
strs['compilation_script'] = "\033[94mCompilation Script\033[0m 📃"
strs['cpy'] = "🚀\033[32mCPY\033[0m"

files = {}
files['cpy'] = [ 'cpy-core.c', 'cpy-file.c', 'cpy-list.c', 'cpy-print.c', 'cpy-string.c']

dirs = {}
dirs['out'] = './out'
dirs['obj'] = dirs['out'] + '/objects'
dirs['so'] = dirs['out']


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

def check(rval, exit=False):
    # Rval from os.system.
    if (rval != 0):
        perror(strs['err'], exit)

def script(argList):
    global strs, dirs
    linkType = argList[0] if len(argList) >= 1 else 'shared'
    #scriptPath = argList[1]
    gccArgsList = " ".join(argList[1:])
    ret=0
    mkdirs()

    plog('Compiling script to binary executable.')
    if linkType == 'shared':
        if os.path.exists(dirs['so']+'/libcpy.so') == False:
            perror('CPY shared object not found', True)
        ret = os.system("{} -L {} -o {}/a.out {} -lcpy".format(strs['cmd'], dirs['so'], dirs['out'], gccArgsList))
        check(ret)
    elif linkType == 'static':
        if os.path.exists(dirs['so']+'/libcpy.a') == False:
            perror('CPY static archive not found', True)
        print("[advice] Use 'libtool' or 'pkg-config' to determine all libraries to link.")
        print("[advice] Then provide those as arguments: ./compile.py script main.c static -lfoo -lbar")
        ret = os.system("{} -static -L {} -o {}/a.out {} -lcpy".format(strs['cmd'], dirs['so'], dirs['out'], gccArgsList))
    else: perror('Unknown link type.', True)

def build(argList):
    global strs, files
    ret = 0
    cpyFiles = files['cpy']
    mkdirs()
    buildType = argList[0] if len(argList) >= 1 else 'shared'

    plog("Compiling with PIC to object")
    for i in range(len(cpyFiles)):
        filename = os.path.splitext(cpyFiles[i])[0]
        ret = os.system("{} -c -fpic -o {}/{}.o ./{}.c".format(strs['cmd'], dirs['obj'], filename, filename))
        check(ret, True)

    if (buildType == 'shared'):
        plog("Creating shared library")
        ret = os.system("{} -shared -o {}/libcpy.so {}/*".format(strs['cmd'], dirs['so'], dirs['obj']))
        check(ret, True)

    elif (buildType == 'static'):
        plog('Creating static library')
        ret = os.system("ar rcs {}/libcpy.a {}/*".format(dirs['so'], dirs['obj']))
        check(ret, True)
    else: perror('Unknown link type.', True)

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
            [positional args]\033[0m

build       Builds the CPY shared object.
script      Compiles your CPY script.
            [path to script]

Example:
compile.py build static/shared
compile.py script static/shared path-to-script.c -lcurl -lfoo -lbar
""")




startup()
cmdList = {'build': build, 'script': script, 'help': help}
args = sys.argv
if (len(args) < 2 or args[1] not in cmdList):
    help(None)
    sys.exit()
else:
    cmdList[args[1]](args[2:])
