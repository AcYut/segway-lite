all: haar_oldcamera surf_oldcamera

haar_oldcamera: 
	g++ -o haar_oldcamera haar_oldcamera.cpp `pkg-config --libs opencv cvblob` -lflycapture

surf_oldcamera: 
	g++ -o surf_oldcamera surf_oldcamera.cpp `pkg-config --libs opencv cvblob` -lflycapture

clean:
	rm -f haar_oldcamera surf_oldcamera
