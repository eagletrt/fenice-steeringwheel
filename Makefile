all: format

update:
	cd thirdparty/can && git pull origin build
	cd thirdparty/wiringpi && git pull origin master

format:
	bash ./tools/fmt

.PHONY: all update format

