all: ../Build/walk.a 

main: main.cpp ../Build/walk.a ../Build/imu.a
	g++ main.cpp ../Build/walk.a ../Build/imu.a -o main -lftdi -lm -lrt -lpthread

../Build/walk.a: ../Build/commondefswalk.o ../Build/hand.o ../Build/leg.o ../Build/walk_thread.o ../Build/walk.o ../Build/AcYut.o ../Build/communication.o ../Build/motor.o
	@echo $@
	@ar rc $@ ../Build/commondefswalk.o ../Build/hand.o ../Build/leg.o ../Build/walk_thread.o ../Build/walk.o ../Build/AcYut.o ../Build/communication.o ../Build/motor.o
	@echo $@
	@ranlib $@

../Build/commondefswalk.o: commondefswalk.cpp commondefswalk.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c commondefswalk.cpp -o $@

../Build/hand.o: hand.cpp hand.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c hand.cpp -o $@

../Build/leg.o: leg.cpp leg.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c leg.cpp -o $@

../Build/walk_thread.o: walk_thread.cpp walk_thread.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c walk_thread.cpp -fpermissive -o $@

../Build/walk.o: walk.cpp walk.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c walk.cpp -fpermissive -o $@	

../Build/AcYut.o: AcYut.cpp AcYut.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c AcYut.cpp -o $@

../Build/communication.o: communication.cpp communication.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c communication.cpp -o $@


../Build/motor.o: motor.cpp motor.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c motor.cpp -o $@
