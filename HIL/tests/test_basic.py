from HIL.esp_dut import ESP
from HIL.aprs_con import APRSIS, AprsIs


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


def test_aprs_msg(APRSIS):
    aprs = AprsIs("OE5BPA-2", passwd="22948",
                  host="localhost", port=10152)
    aprs.connect()
    aprs.send_line("OE5BPA-2>APLG01:=4819.82NL01418.68E&Testing")
    for i in range(2):
        line = APRSIS.get_line()
        for l in line:
            if l == "OE5BPA-2>APLG01,TCPIP*,qAC,OE5BPA:=4819.82NL01418.68E&Testing":
                return
    raise
