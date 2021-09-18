from testlib.esp_dut import ESP


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
    ESP.flash.erase()
