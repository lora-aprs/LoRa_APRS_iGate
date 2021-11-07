.PHONY: install test debug

default: install test

install:
	pip3 install -r HIL/requirements.txt

test:
	ESP_PORT=/dev/ttyUSB0 ESP_CONFIG_PATH=data ESP_CONFIG_FILE=is-cfg.json PYTHONPATH=. pytest HIL_tests -v --log-cli-level=INFO

debug:
	ESP_PORT=/dev/ttyUSB0 ESP_CONFIG_PATH=data ESP_CONFIG_FILE=is-cfg.json PYTHONPATH=. pytest HIL_tests -v --capture=tee-sys --log-cli-level=DEBUG
