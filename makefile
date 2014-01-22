all: run

run:Source/Build/path.a Source/Build/testwalk.a Source/Build/behavior.a Source/Build/imgProc.a Source/Build/imu.a run.cpp Source/Build/gameController.a Source/Build/switch.a
	@echo compiling and linking final code
	g++ -w run.cpp Source/Build/switch.a Source/Build/path.o Source/Build/testwalk.a Source/Build/behavior.a Source/Build/imgProc.a Source/Build/imu.a Source/Build/gameController.a -o run -lueye_api -lftdi -lopencv_highgui -lpthread -fpermissive -lopencv_core -lopencv_imgproc  -lcvblob -ltbb -O3 -fpermissive -lrt 

Source/Build/path.a: Source/path/*.cpp Source/path/*.hpp Source/common/*.h
	@make -s -C Source/path
Source/Build/imu.a: Source/xsens/*.cpp Source/xsens/*.h Source/common/*.h
	@make -s -C Source/xsens
# Source/Build/walk.a: Source/walk/*.cpp Source/walk/*.h Source/common/*.h
	# @make -s -C Source/walk
Source/Build/testwalk.a: Source/testwalk/*.cpp Source/testwalk/*.h Source/common/*.h
	@make -s -C Source/testwalk
Source/Build/behavior.a: Source/behavior/*.cpp Source/behavior/*.h Source/behavior/xabsl-src/*.xabsl Source/behavior/xabsl-src/options/*.xabsl Source/common/*.h
	@make -s -C Source/behavior
Source/Build/imgProc.a: Source/imgProc/*.cpp Source/imgProc/*.h Source/common/*.h
	@make -s -C Source/imgProc
Source/Build/gameController.a: Source/gameController/*.cpp Source/gameController/*.h
	@make -s -C Source/gameController
Source/Build/switch.a:
	@make -s -C Source/switch
# Source/Build/fdwave.o:
# 	@make -s -C Source/moves

DOC:
	@make -s -C Source/behavior/xabsl-src DOC
clean:
	@rm -f intermediate-code.dat
	@rm -f debug-symbols.dat 
	@rm -f run
	@make -s -C Source clean
	@make -s -C Xabsl/compiler clean
	@rm -f imu-calibrator
