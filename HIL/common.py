import subprocess
import logging

logger = logging.getLogger(__name__)


def runProcess(cmd):
    logger.debug(f"run process: \"{cmd}\"")
    subprocess.run(cmd, shell=True).check_returncode()
