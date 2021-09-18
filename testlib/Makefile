.PHONY: install test

default: install test

install:
	pip3 install -r requirements.txt

test:
	ESP_PORT=/dev/ttyUSB0 pytest tests -v
