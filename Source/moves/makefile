all: ../Build/fdwave.o
all1: move1 move2 move3 getup salute wave motor.o communication.o hand.o leg.o AcYut.o commondefswalk.o
move1: move1.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o move1 move1.cpp -lftdi -lm -lrt -lpthread
move2: move2.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o move2 move2.cpp -lftdi -lm -lrt -lpthread	
move3: move3.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o move3 move3.cpp -lftdi -lm -lrt -lpthread	
getup: getup-try.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o getup getup-try.cpp -lftdi -lm -lrt -lpthread
salute: salute.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o salute salute.cpp -lftdi -lm -lrt -lpthread
wave: wave.cpp communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o xsens/totalxsens.o commondefswalk.o
	g++ commondefswalk.o motor.o communication.o hand.o leg.o AcYut.o xsens/imu.o xsens/totalxsens.o -o wave wave.cpp -lftdi -lm -lrt -lpthread
motor.o: motor.cpp motor.h commondefswalk.o
	g++ -c motor.cpp 
communication.o: communication.cpp communication.h commondefswalk.o
	g++ -c communication.cpp
leg.o: leg.cpp leg.h commondefswalk.o communication.o motor.o
	g++ -c leg.cpp
AcYut.o : motor.o communication.o leg.o AcYut.cpp AcYut.h hand.o commondefswalk.o
	g++ -c AcYut.cpp
hand.o : hand.h hand.cpp motor.o communication.o commondefswalk.o
	g++ -c hand.cpp
commondefswalk.o : bot1.h commondefswalk.h commondefswalk.cpp
	g++ -c commondefswalk.cpp
../Build/fdwave.o: fdwave.cpp fdwave.h communication.o motor.o leg.o hand.o AcYut.o xsens/imu.o commondefswalk.o
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c fdwave.cpp -lftdi -lm -lrt -lpthread -o $@
clean: 
	rm motor.o 
	rm communication.o
	rm leg.o
	rm AcYut.o
	rm hand.o
	rm commondefswalk.o
	rm getup


