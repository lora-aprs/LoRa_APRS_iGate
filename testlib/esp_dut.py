import os
import pytest
import serial
from testlib.common import runProcess


class EspFlash:
    def __init__(self, port):
        self.pio_package_path = "$HOME/.platformio/packages"
        self.port = port

    def runESPTool(self, cmd):
        runProcess(
            f"/usr/bin/python3 {self.pio_package_path}/tool-esptoolpy/esptool.py --chip esp32 --port {self.port} {cmd}")

    def erase(self):
        self.runESPTool("erase_flash")

    def write(self, addr, bin_file):
        self.runESPTool(
            f"--baud 460800 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_size detect {addr} {bin_file}")

    def verify(self, addr, bin_file):
        self.runESPTool(
            f"--baud 460800 --before default_reset --after hard_reset verify_flash --flash_mode dio --flash_size detect {addr} {bin_file}")

    def make_spiffs(self, fs_path, fs_bin):
        runProcess(
            f"{self.pio_package_path}/tool-mkspiffs/mkspiffs_espressif32_arduino -c {fs_path} -p 256 -b 4096 -s 1507328 {fs_bin}")


class EspDut:
    def __init__(self, port):
        self.port = port
        self.serial = None
        self.flash = EspFlash(self.port)

    def writeFlash(self, bin_dir):
        self.flash.erase()
        self.flash.write("0x1000",  f"{bin_dir}/bootloader_dio_40m.bin")
        self.flash.write("0x8000",  f"{bin_dir}/partitions.bin")
        self.flash.write("0xe000",  f"{bin_dir}/boot_app0.bin")
        self.flash.write("0x10000", f"{bin_dir}/firmware.bin")

    def writeConfig(self, fs_path):
        fs_bin = "spiffs.bin"
        self.flash.make_spiffs(fs_path, fs_bin)
        self.flash.write("0x290000", fs_bin)

    def openPort(self):
        self.serial = serial.Serial(self.port, 115200, timeout=0)

    def getLine(self):
        return self.serial.readline()

    def closePort(self):
        if self.serial:
            self.serial.close()
            self.serial = None


@pytest.fixture
def ESP():
    return EspDut(os.environ["ESP_PORT"])
