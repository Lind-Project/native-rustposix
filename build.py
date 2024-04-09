import subprocess
import sys

def build(target):
    subprocess.run(f"export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH && gcc -c {target}.c -o {target}.o && gcc -c lind_platform.c -o lind_platform.o && gcc {target}.o lind_platform.o -L. -lrustposix -o {target}", shell=True)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("need a target!")
    else:
        build(sys.argv[1]);