import subprocess


def runProcess(cmd):
    subprocess.run(cmd, shell=True).check_returncode()
