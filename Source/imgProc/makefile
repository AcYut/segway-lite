all: ../Build/imgProc.a


../Build/imgProc.a: ../Build/camcapture.o ../Build/camcontrol.o ../Build/featuredetection.o ../Build/headmotor.o ../Build/imgproc.o ../Build/localize.o
	@echo $@
	@ar rc $@ ../Build/camcapture.o ../Build/camcontrol.o ../Build/featuredetection.o ../Build/headmotor.o ../Build/imgproc.o ../Build/localize.o
	@echo
	@ranlib $@

../Build/camcapture.o: camcapture.cpp camcapture.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c camcapture.cpp -lueye_api -o $@

../Build/camcontrol.o: camcontrol.cpp camcontrol.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c camcontrol.cpp -lueye_api  -o $@

../Build/featuredetection.o: featuredetection.cpp featuredetection.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c featuredetection.cpp -o $@

../Build/headmotor.o: headmotor.cpp headmotor.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c headmotor.cpp -lueye_api  -o $@

../Build/localize.o: localize.cpp localize.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c localize.cpp -lueye_api  -fpermissive -o $@

../Build/imgproc.o: imgproc.cpp imgproc.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c imgproc.cpp -o $@