import os
import subprocess

if not os.path.exists('./build'):
    os.makedirs('./build')

os.chdir('./build')

subprocess.call(['cmake', '../src'])
subprocess.call(['cmake', '--build', '.'])