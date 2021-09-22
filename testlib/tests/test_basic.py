from testlib.esp_dut import ESP
from testlib.aprs_con import APRSIS


def test_basic_port(ESP):
    ESP.openPort()
    ESP.closePort()


def test_flash(ESP):
    bin_dir = "testbinary"
    ESP.writeFlash(bin_dir)
    ESP.flash.verify("0x1000",  f"{bin_dir}/bootloader_dio_40m.bin")
    ESP.flash.verify("0x8000",  f"{bin_dir}/partitions.bin")
    ESP.flash.verify("0xe000",  f"{bin_dir}/boot_app0.bin")
    ESP.flash.verify("0x10000", f"{bin_dir}/firmware.bin")


def test_flash_config(ESP):
    config_dir = "testconfig"
    ESP.writeConfig(config_dir)


def test_erase(ESP):
    ESP.flash.erase()


def test_aprs_login(APRSIS):
    pass
