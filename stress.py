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
        if(output == "Error"):
            #print(file + "\033[92m OK\033[0m")
            continue
        else:
            #print(file + "\033[91m KO\033[0m")
            bad.append(file)
else :
    print("Valid :")

    path = 'tester_parse_cub3d/valid'

    files = os.listdir(path)
    cmd = 'ls -l'
    for file in files:
        cmd = './cub3D ' + path + '/' + file
        output = subprocess.check_output(cmd, shell=True)
        if(output == ""):
            print(file + "\033[92m OK\033[0m")
        else:
            print(file + "\033[91m KO\033[0m")


print(bad)


