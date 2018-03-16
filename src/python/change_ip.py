#!/usr/bin/python

import fileinput
import re
import sys

if len(sys.argv) < 3:
    print("Usae: python update_ip.py config-file ip [port]")
elif len(sys.argv) == 3:
    f = fileinput.input(files=sys.argv[1], inplace=True, backup='.bak')
    for line in f:
        line = re.sub('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', sys.argv[2], line)
        line = line.rstrip();
        print(line)
    f.close()
elif len(sys.argv) == 4:
    f = fileinput.input(files=sys.argv[1], inplace=True, backup='.bak')
    for line in f:
        line = re.sub('\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', sys.argv[2], line)
        line = re.sub('TCP=\d*', "TCP="+sys.argv[3], line)
        line = line.rstrip();
        print(line)
    f.close()
