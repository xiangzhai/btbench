# -*- coding: utf-8 -*-

import sys
import os
import time

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ./btbench.py /your/path/translator\n"
              "for example:\n"
              "./btbench.py /usr/local/bin/box64\n"
              "or\n"
              "./btbench.py /usr/bin/latx-x86_64")
        sys.exit(-1)

    tr = sys.argv[1]
    print("btbench %s start" % (tr))

    os.environ['BOX64_LOG'] = "0"
    os.environ['BOX64_NOBANNER'] = "1"

    ''' 7z '''
    cwd = os.getcwd()
    os.system("%s %s/benchmarks/p7zip/7z b" % (tr, cwd))
    os.system("%s %s/benchmarks/p7zip/7z b -mm=* -mmt=*" % (tr, cwd))

    ''' dav1d '''
    ivf_path = "%s/benchmarks/dav1d/Chimera-AV1-8bit-480x270-552kbps.ivf" % (cwd)
    if not os.path.exists(ivf_path):
        os.system("wget http://dgql.org/~unlord/Netflix/Chimera/Chimera-AV1-8bit-480x270-552kbps.ivf -O %s" % (ivf_path))
    if os.path.exists(ivf_path):
        os.environ['LD_LIBRARY_PATH'] = "$LD_LIBRARY_PATH:%s/benchmarks/dav1d" % (cwd)
        start_time = time.time()
        os.system("%s %s/benchmarks/dav1d/dav1d -i %s --muxer null" % (tr, cwd, ivf_path))
        print("%s seconds" % (time.time() - start_time))

    ''' scimark4_c '''
    os.system("%s %s/benchmarks/scimark4_c/scimark4" % (tr, cwd))
    os.system("%s %s/benchmarks/scimark4_c/scimark4 -large" % (tr, cwd))

    ''' glmark2 '''
    glmark2_path = "%s/benchmarks/glmark2" % (cwd)
    os.environ['LD_LIBRARY_PATH'] = "$LD_LIBRARY_PATH:%s" % (glmark2_path)
    os.system("%s %s/bin/glmark2 --data-path %s/share/glmark2" % (tr, glmark2_path, glmark2_path))

    print("btbench %s end" % (tr))
