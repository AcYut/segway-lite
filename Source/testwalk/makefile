all: ../Build/testwalk.a

main: main.cpp ../Build/testwalk.a
	g++ main.cpp ../Build/testwalk.a -o main -lftdi -lm -lrt -lpthread `pkg-config --libs opencv`

../Build/testwalk.a: ../Build/walk_thread.o ../Build/walk.o ../Build/testBot.o ../Build/communication.o ../Build/commondefswalk.o
	@echo $@
	@ar rc $@ ../Build/walk_thread.o ../Build/walk.o ../Build/testBot.o ../Build/communication.o ../Build/commondefswalk.o
	@echo $@
	@ranlib $@


../Build/walk_thread.o: walk_thread.cpp walk_thread.h 
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c walk_thread.cpp -fpermissive -o $@

../Build/walk.o: walk.cpp walk.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c walk.cpp -fpermissive -o $@	

../Build/testBot.o: testBot.cpp testBot.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c testBot.cpp -o $@

../Build/communication.o: communication.cpp communication.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c communication.cpp -o $@

../Build/commondefswalk.o: commondefswalk.cpp commondefswalk.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c commondefswalk.cpp -o $@


  
