.PHONY: install test debug

default: install test

install:
	sudo -H pip3 install -r requirements.txt

test:
	ESP_PORT=/dev/ttyUSB0 ESP_CONFIG_PATH=testconfig ESP_CONFIG_FILE=testconfig.json pytest tests -v --log-cli-level=INFO

debug:
	ESP_PORT=/dev/ttyUSB0 ESP_CONFIG_PATH=testconfig ESP_CONFIG_FILE=testconfig.json pytest tests -v --capture=tee-sys --log-cli-level=DEBUG
