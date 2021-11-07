import pytest
import socket
import logging

logger = logging.getLogger(__name__)


class AprsIs:
    def __init__(self, callsign, passwd="-1", host="localhost", port=10152) -> None:
        self.callsign = callsign
        self.passwd = passwd
        self.server = (host, port)
        self.socket = None
        self.buffer = ""

    def connect(self):
        if self.socket:
            return False

        logger.debug(f"trying to connect to {self.server}")
        self.socket = socket.create_connection(self.server)
        peer = self.socket.getpeername()
        logger.info(f"Connected to {str(peer)}")
        self.socket.setblocking(1)
        self.socket.settimeout(1)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
        banner = list(self._get_line())
        logger.info(f"Banner: {banner[0].rstrip()}")

        login_line = f"user {self.callsign} pass {self.passwd} vers testlib 0.1\r\n"
        logger.debug(login_line)
        self.send_line(login_line)

        login = list(self._get_line())
        logger.info(f"login line: {login[0]}")
        _, _, _, status, _ = login[0].split(' ', 4)
        if status == "verified":
            return True
        self.close()
        return False

    def close(self):
        if not self.socket:
            self.socket.close()
            self.socket = None

    def send_line(self, line):
        if self.socket:
            self.socket.sendall(bytearray(f"{line}\r\n", encoding='utf8'))

    def get_line(self):
        line_list = list(self._get_line())
        new_list = []
        if line_list:
            for line in line_list:
                if not line.startswith("#"):
                    new_list.append(line)
        return new_list

    def _get_line(self):
        if self.socket:
            try:
                buf = self.socket.recv(4096)
                self.buffer = self.buffer + buf.decode('latin-1')
            except:
                pass
            while "\r\n" in self.buffer:
                line, self.buffer = self.buffer.split("\r\n", 1)
                yield line
        return None

    def wait_for(self, towait):
        for i in range(2, 10):
            line = self.get_line()
            for l in line:
                if l == towait:
                    return
        raise


@pytest.fixture
def APRSIS():
    aprs = AprsIs("OE5BPA-1", passwd="22948",
                  host="localhost", port=10152)
    aprs.connect()
    return aprs
