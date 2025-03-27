# -*- coding: utf-8 -*-

import sys
import os
import subprocess
from datetime import datetime

def run(cmd, log_file):
    with open(log_file, 'a') as out:
        return_code = subprocess.call(cmd, stdout=out, shell=True)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python3 btbench.py /your/path/translator\n"
              "for example:\n"
              "./btbench.py /usr/local/bin/box64\n"
              "or\n"
              "./btbench.py /usr/bin/latx-x86_64")
        sys.exit(-1)

    tr = sys.argv[1]
    if not os.path.exists(tr):
        print("%s not exists" % (tr))
        sys.exit(-1)

    print("btbench %s start" % (tr))

    os.environ['BOX64_LOG'] = "0"
    os.environ['BOX64_NOBANNER'] = "1"

    cur_dt = datetime.today().strftime('%Y%m%d%H%M%S')
    cwd = os.getcwd()
    log_path = "%s/logs" % (cwd)
    if not os.path.exists(log_path):
        os.makedirs(log_path)
    log_file = "%s/%s-%s.log" % (log_path, os.path.basename(tr), cur_dt)

    ''' dav1d '''
    ivf_path = "%s/benchmarks/dav1d/Chimera-AV1-8bit-480x270-552kbps.ivf" % (cwd)
    if not os.path.exists(ivf_path):
        os.system("wget http://dgql.org/~unlord/Netflix/Chimera/Chimera-AV1-8bit-480x270-552kbps.ivf -O %s" % (ivf_path))
    if os.path.exists(ivf_path):
        os.environ['LD_LIBRARY_PATH'] = "$LD_LIBRARY_PATH:%s/benchmarks/dav1d" % (cwd)
        print("dav1d %s" % (datetime.today().strftime('%Y-%m-%d %H:%M:%S')))
        run("%s %s/benchmarks/dav1d/dav1d -i %s --muxer null 2>&1|tee %s" % (tr, cwd, ivf_path, log_file), log_file)

    ''' 7z '''
    print("7z %s" % (datetime.today().strftime('%Y-%m-%d %H:%M:%S')))
    run("%s %s/benchmarks/p7zip/7z b" % (tr, cwd), log_file)

    ''' scimark4_c '''
    print("scimark4_c %s" % (datetime.today().strftime('%Y-%m-%d %H:%M:%S')))
    run("%s %s/benchmarks/scimark4_c/scimark4" % (tr, cwd), log_file)
    run("%s %s/benchmarks/scimark4_c/scimark4 -large" % (tr, cwd), log_file)

    ''' glmark2 '''
    glmark2_path = "%s/benchmarks/glmark2" % (cwd)
    os.environ['LD_LIBRARY_PATH'] = "$LD_LIBRARY_PATH:%s" % (glmark2_path)
    print("glmark2 %s" % (datetime.today().strftime('%Y-%m-%d %H:%M:%S')))
    run("%s %s/bin/glmark2 --data-path %s/share/glmark2" % (tr, glmark2_path, glmark2_path), log_file)

    print("btbench %s end" % (tr))

    os.system("%s --version" % (tr))
    os.system("/usr/bin/python3 score.py %s" % (log_file))
