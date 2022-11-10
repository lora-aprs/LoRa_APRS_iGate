import os
import pytest
import serial
import logging
import json
import tempfile
import pigpio

from pathlib import Path
from HIL.common import runProcess

logger = logging.getLogger(__name__)


class EspFlash:
    def __init__(self, port):
        self._pio_package_path = Path('$HOME') / '.platformio' / 'packages'
        self._port = port
        logger.info(f"pio package path: {self._pio_package_path}")
        logger.info(f"port: {self._port}")

    def runESPTool(self, cmd):
        esp_tool = self._pio_package_path / 'tool-esptoolpy' / 'esptool.py'
        runProcess(
            f"/usr/bin/python3 {esp_tool} --chip esp32 --port {self._port} {cmd}")

    def erase(self):
        logger.info("erase flash")
        self.runESPTool("erase_flash")

    def write(self, addr, bin_file):
        logger.info(f"write flash on addr {addr} with file {bin_file}")
        self.runESPTool(
            f"--baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect {addr} {bin_file}")

    def verify(self, addr, bin_file):
        logger.info(f"verify flash on addr {addr} with file {bin_file}")
        self.runESPTool(
            f"--baud 460800 --before default_reset --after hard_reset verify_flash --flash_mode dio --flash_size detect {addr} {bin_file}")

    def make_spiffs(self, fs_path, fs_bin):
        logger.info(f"make spiffs, fs_path: {fs_path}, fs_bin: {fs_bin}")
        mkspiffs_espressif32_arduino = self._pio_package_path / \
            'tool-mkspiffs' / 'mkspiffs_espressif32_arduino'
        runProcess(
            f"{mkspiffs_espressif32_arduino} -c {fs_path} -p 256 -b 4096 -s 1507328 {fs_bin}")


class EspConfig:
    def __init__(self, path, filename):
        self.filename = filename
        logger.info(f"reading config from: {path}/{self.filename}")
        with open(path / self.filename) as json_file:
            self.data = json.load(json_file)
        logger.info(f"was reading this data: {self.data}")

    def writeFile(self):
        tmpdirname = tempfile.TemporaryDirectory()
        logger.info(f"writing this data: {self.data}")
        with open(Path(tmpdirname.name) / self.filename, 'w') as outfile:
            json.dump(self.data, outfile)
        return tmpdirname


class EspDut:
    def __init__(self, port, configPath, configFile, powerPin):
        self.port = port
        self.baudrate = 115200
        self.serial = None
        self.flash = EspFlash(self.port)
        self.config = EspConfig(configPath, configFile)
        self.pigpio = pigpio.pi()
        self.powerPin = powerPin
        self.pigpio.set_mode(self.powerPin, pigpio.OUTPUT)

    def begin(self):
        self.pigpio.pi.write(self.powerPin, 1)

    def stop(self):
        self.pigpio.pi.write(self.powerPin, 0)

    def writeFlash(self, bin_dir):
        logger.info("write flash")
        self.flash.erase()
        self.flash.write("0x1000",  bin_dir / 'bootloader_dio_40m.bin')
        self.flash.write("0x8000",  bin_dir / 'partitions.bin')
        self.flash.write("0xe000",  bin_dir / 'boot_app0.bin')
        self.flash.write("0x10000", bin_dir / 'firmware.bin')

    def writeConfig(self):
        logger.info("write config")
        fs_bin = "spiffs.bin"
        fs_path = self.config.writeFile()
        self.flash.make_spiffs(fs_path.name, fs_bin)
        self.flash.write("0x290000", fs_bin)

    def openPort(self):
        logger.info(f"open port: {self.port}, baudrate: {self.baudrate}")
        self.serial = serial.Serial(
            self.port, baudrate=self.baudrate, timeout=0)

    def getLine(self):
        return self.serial.readline()

    def closePort(self):
        if self.serial:
            self.serial.close()
            self.serial = None


@pytest.fixture
def ESP():
    return EspDut(os.environ["ESP_PORT"], Path(os.environ["ESP_CONFIG_PATH"]), Path(os.environ["ESP_CONFIG_FILE"]), 13)
