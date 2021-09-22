import pytest
import socket


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

        self.socket = socket.create_connection(self.server)
        peer = self.socket.getpeername()
        print(f"Connected to {str(peer)}")
        self.socket.setblocking(1)
        self.socket.settimeout(1)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
        banner = list(self._get_line())
        print(f"Banner: {banner[0].rstrip()}")

        self.send_line(
            f"user {self.callsign} pass {self.passwd} vers testlib 0.1\r\n")

        login = list(self._get_line())
        print(f"login line: {login[0]}")
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


@pytest.fixture
def APRSIS():
    aprs = AprsIs("OE5BPA-1", passwd="22948",
                  host="localhost", port=10152)
    aprs.connect()
    return aprs
