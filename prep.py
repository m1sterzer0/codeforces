import re
import requests
import parsel
import sys
import os

dummyCppFile = '''#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}
'''

tasksJsonFile = '''{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [ "-g", "${file}" ],
            "group": { "kind": "build", "isDefault": true }
        }
    ]
}
'''

launchJsonFile = '''{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/a.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\\\mingw-w64\\\\mingw64\\\\bin\\\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
'''

cCppPropertiesJsonFile = '''{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}",
                "C:\\\\mingw-w64\\\\mingw64\\\\x86_64-w64-mingw32\\\\include",
                "C:\\\\mingw-w64\\\\mingw64\\\\lib\\\\gcc\\\\x86_64-w64-mingw32\\\\8.1.0\\\\include\\\\c++"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/mingw-w64/mingw64/bin/g++.exe",
            "intelliSenseMode": "clang-x64",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "browse": {
                "path": [
                    "${workspaceFolder}"
                ],
                "limitSymbolsToIncludedHeaders": true,
                "databaseFilename": ""
            }
        }
    ],
    "version": 4
}
'''

def vscodePrep():
    if os.path.isdir(".vscode") : return
    os.mkdir(".vscode")
    with open(".vscode/tasks.json",'w')  as fp : fp.write(tasksJsonFile)
    with open(".vscode/launch.json",'w') as fp : fp.write(launchJsonFile)
    with open(".vscode/c_cpp_properties.json","w") as fp : fp.write(cCppPropertiesJsonFile)

def cppStarter(fn) :
    if os.path.isfile(fn) : return
    with open(fn,"w") as fp : fp.write(dummyCppFile)  

vscodePrep()
alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
if len(sys.argv) != 2 :
    raise Exception ("USAGE: prep.py <contestnum>")
r = requests.get(f"https://codeforces.com/contest/{sys.argv[1]}")
doc = parsel.Selector(r.text)
problems = doc.xpath('//div[@class="datatable"]//table[@class="problems"]/tr/td[@class="id"]/a/@href').extract()
for i,p in enumerate(problems) :
    cppStarter(f"{sys.argv[1]}{alph[i]}.cpp")
    r2 = requests.get(f"https://codeforces.com{p}")
    doc2 = parsel.Selector(r2.text)
    infiles = doc2.xpath('//div[@class="sample-tests"]//div[@class="input"]//pre').extract()
    for j,infile in enumerate(infiles,1) :
        infile = re.sub(r'<pre>|</pre>','',infile)
        infile = re.sub(r'<br>',"\n",infile)
        fn = f"{sys.argv[1]}{alph[i]}.in{j}"
        with open(fn,"w") as fp : fp.write(infile)