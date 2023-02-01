#!/usr/bin/python

import os
import subprocess

import signal
import sys

def signal_handler(signal, frame):
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

bad = []


choice = sys.argv[1]

if choice == "1":
    print("invalid :")

    path = 'tester_parse_cub3d/invalid'

    files = os.listdir(path)
    cmd = 'ls -l'
    for file in files:
        cmd = './cub3D ' + path + '/' + file
        output = subprocess.check_output(cmd, shell=True)
        try:
            l = output.split(" ")
            if len(l) > 0:
                num = int(output.split(" ")[1])
                if(num == 0):
                    print(file + "\033[92m " + str(num) + " leaks \033[0m")
                    continue
                else:
                    print(file + "\033[91m " + str(num) + " leaks \033[0m")
                    bad.append(file)
        except:
            print ("Undefined behavior")
            bad.append(file)
else :
    print("Valid :")

    path = 'tester_parse_cub3d/valid'

    files = os.listdir(path)
    cmd = 'ls -l'
    for file in files:
        cmd = './cub3D ' + path + '/' + file
        output = subprocess.check_output(cmd, shell=True)
        num = int(output.split(" ")[1])
        if(num == 0):
            print(file + "\033[92m " + str(num) + " leaks \033[0m")
            #continue
        else:
            print(file + "\033[91m " + str(num) + " leaks \033[0m")
            #bad.append(file)


print(bad)


