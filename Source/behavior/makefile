XABSLFILES=$(shell echo `ls ../../Xabsl/XabslEngine/ -c1 | grep .cpp` | sed "s%Xabsl%../Build/Xabsl%g" | sed "s%\.cpp%.o%g")

all: ../Build/behavior.a

../Build/behavior.a: ../Build/WorldState.o ../Build/MyBasicBehaviors.o ../Build/main.o $(XABSLFILES) ../common/common.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@ar rc $@ $(XABSLFILES) ../Build/WorldState.o ../Build/MyBasicBehaviors.o ../Build/main.o
	@ranlib $@

intermediate: xabsl-src/*.xabsl xabsl-src/options/*.xabsl
	@echo compiling XABSL source files and generating the intermediate code
	@make -s -C ../../Xabsl/compiler
	@make -s -C ./xabsl-src


../Build/Xabsl%.o: ../../Xabsl/XabslEngine/Xabsl%.cpp ../../Xabsl/XabslEngine/Xabsl%.h 
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c $< -o $@

../Build/WorldState.o: WorldState.cpp WorldState.h ../common/common.h ../imgProc/camcapture.h ../imgProc/camcontrol.h ../imgProc/featuredetection.h ../imgProc/headmotor.h ../imgProc/localize.h ../path/path.hpp ../common/common.h ../common/commondefs.h ../testwalk/commondefswalk.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c WorldState.cpp -o $@
	
../Build/MyBasicBehaviors.o: MyBasicBehaviors.cpp MyBasicBehaviors.h ../common/common.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c MyBasicBehaviors.cpp -o $@

../Build/main.o: main.cpp WorldState.h MyBasicBehaviors.h Tools.h intermediate ../common/common.h
	@echo $@
	@if !(test -d ../Build); then mkdir ../Build; fi
	@g++ -c main.cpp -o $@
 