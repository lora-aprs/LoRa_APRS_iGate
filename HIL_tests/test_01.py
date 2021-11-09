
import logging
import sys
from pathlib import Path
from HIL.esp_dut import ESP
from HIL.aprs_con import APRSIS

logger = logging.getLogger(__name__)
logger.error(sys.path)


def test_01(ESP, APRSIS):
    pass
