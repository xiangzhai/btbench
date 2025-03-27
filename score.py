# -*- coding: utf-8 -*-

import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python3 score.py /your/path/bench.log")
        sys.exit(-1)

    _7z_score = ""
    dav1d_score = ""
    scimark4_c_score = None
    scimark4_c_large_score = None
    glmark2_score = ""
    with open(sys.argv[1], 'r') as file:
        for line in file:
            if line.find("Tot") != -1:
                arr = line.split(" ")
                _7z_score = arr[-1][0:-1]
            elif line.find("Decoded") != -1 and line.find("frames") != -1 and line.find("100.0%") != -1:
                arr = line.split(" ")
                arr1 = arr[5].split("/")
                dav1d_score = arr1[0]
            elif line.find("Composite Score") != -1:
                arr = line.split(" ")
                if scimark4_c_score == None:
                    scimark4_c_score = arr[-1][0:-1]
                elif scimark4_c_large_score == None:
                    scimark4_c_large_score = arr[-1][0:-1]
            elif line.find("glmark2 Score") != -1:
                arr = line.split(" ")
                glmark2_score = arr[-2]

    print("|benchmark       |score bigger is better |")
    print("|----------------|-----------------------|")
    print("|7z              |%s                   |" % (_7z_score))
    print("|dav1d           |%s                 |" % (dav1d_score))
    print("|scimark4_c      |%s                 |" % (scimark4_c_score))
    print("|scimark4_c large|%s                 |" % (scimark4_c_large_score))
    print("|glmark2         |%s                   |" % (glmark2_score))
