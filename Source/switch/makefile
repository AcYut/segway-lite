all: ../Build/switch.a

../Build/switch.o: acyut_gpio.h acyut_gpio.cpp
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c acyut_gpio.cpp -o $@

../Build/switch.a: ../Build/switch.o
	@echo $@
	@ar rc $@ ../Build/switch.o
	@ranlib $@