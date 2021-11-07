.PHONY: install test debug

default: install test

install:
	pip3 install -r requirements.txt

test:
	ESP_PORT=/dev/ttyUSB0 pytest tests -v --log-cli-level=INFO

debug:
	ESP_PORT=/dev/ttyUSB0 pytest tests -v --capture=tee-sys --log-cli-level=DEBUG
