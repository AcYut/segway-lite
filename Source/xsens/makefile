all: ../Build/imu.a ../../imu-calibrator

../Build/imu.a: ../Build/cmt1.o ../Build/cmt2.o ../Build/cmt3.o ../Build/cmtmessage.o ../Build/cmtscan.o ../Build/cmtpacket.o ../Build/xsens_time.o ../Build/xsens_std.o ../Build/imu.o
	@echo $@
	@ar rc $@ ../Build/cmt1.o ../Build/cmt2.o ../Build/cmt3.o ../Build/cmtmessage.o ../Build/cmtscan.o ../Build/cmtpacket.o ../Build/xsens_time.o ../Build/xsens_std.o ../Build/imu.o
	@echo $@
	@ranlib $@

../Build/cmt1.o: cmt1.cpp cmt1.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmt1.cpp -o $@

../Build/cmt2.o: cmt2.cpp cmt2.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmt2.cpp -o $@

../Build/cmt3.o: cmt3.cpp cmt3.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmt3.cpp -o $@

../Build/cmtmessage.o: cmtmessage.cpp cmtmessage.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmtmessage.cpp -o $@

../Build/cmtpacket.o: cmtpacket.cpp cmtpacket.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmtpacket.cpp -o $@

../Build/cmtscan.o: cmtscan.cpp cmtscan.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c cmtscan.cpp -o $@

../Build/xsens_time.o: xsens_time.cpp xsens_time.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c xsens_time.cpp -o $@

../Build/xsens_std.o: xsens_std.cpp xsens_std.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c xsens_std.cpp -o $@

../Build/imu.o: imu.cpp imu.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c imu.cpp -o $@

../../imu-calibrator: ../Build/imu.a main.cpp 
	@echo $@
	g++ main.cpp ../Build/imu.a -o $@ -lpthread -lrt