#include <iostream>
#include <stdio.h>

//OpenCV Headers
#include <opencv/cv.h>
#include <opencv/highgui.h>
//Input-Output
#include <stdio.h>
//Blob Library Headers
#include <cvblob.h>

#include <flycapture/FlyCapture2.h>

using namespace std;
using namespace cvb;
using namespace cv;

enum CamError {CAM_SUCCESS = 1, CAM_FAILURE = 0};

CvScalar cColor = CV_RGB(255, 255, 255);

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip );

// string cascadeName = "haarcascade_frontalface_alt.xml";
string cascadeName = "haarcascade_frontalface_alt.xml";
string nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";

int main()
{
    FlyCapture2::Error error;
    FlyCapture2::PGRGuid guid;
    FlyCapture2::BusManager busMgr;
    FlyCapture2::Camera cam;
    FlyCapture2::VideoMode vm;
    FlyCapture2::FrameRate fr;
    FlyCapture2::Image rawImage;

    //Initializing camera
        error = busMgr.GetCameraFromIndex(0, &guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        return CAM_FAILURE;
    }

          vm = FlyCapture2::VIDEOMODE_640x480Y8;
    fr = FlyCapture2::FRAMERATE_60;

    error = cam.Connect(&guid);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        return CAM_FAILURE;
    }

    cam.SetVideoModeAndFrameRate(vm, fr);
    //Starting the capture
    error = cam.StartCapture();
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
               return CAM_FAILURE;
    }

    bool tryflip = false;
    double scale = 1;

    CascadeClassifier cascade, nestedCascade;

    if( !nestedCascade.load( nestedCascadeName ) )
    {
        cerr << "ERROR: Could not load classifier nestedcascade" << endl;
        return -1;
    }

    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }
    // printf("3\n");
    while(1)
    {
        Mat img_scene = Mat(Size(640,480),CV_8UC1);
        Mat frame = Mat(Size(640,480),CV_8UC3);
        cam.RetrieveBuffer(&rawImage);
        memcpy(img_scene.data, rawImage.GetData(), rawImage.GetDataSize());
        cvtColor(img_scene,frame,CV_BayerBG2BGR);
        // Mat frame = imread("1.bmp",CV_LOAD_IMAGE_COLOR);
        // printf("4\n");
        // getFrame(hCam,frame);
        // printf("5\n");
        // printf("1\n");
        detectAndDraw(frame,cascade,nestedCascade,scale,tryflip);
        // printf("2\n");
        int c = cvWaitKey(10);
        if(c == 27)
            break;
    }
    return 0;
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip )
{
    int i = 0;
    double t = 0;
    vector<Rect> faces, faces2;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );

    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    t = (double)cvGetTickCount();
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30) );
    if( tryflip )
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale( smallImg, faces2,
                                 1.1, 2, 0
                                 //|CV_HAAR_FIND_BIGGEST_OBJECT
                                 //|CV_HAAR_DO_ROUGH_SEARCH
                                 |CV_HAAR_SCALE_IMAGE
                                 ,
                                 Size(30, 30) );
        for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++ )
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }
    t = (double)cvGetTickCount() - t;
    printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        // vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r->width/r->height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
			printf("FOUND\n");
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            circle( img, center, radius, color, 2, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
                       cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
                       color, 3, 8, 0);
        // if( nestedCascade.empty() )
        //     continue;
        // smallImgROI = smallImg(*r);
        // nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
        //     1.1, 2, 0
        //     //|CV_HAAR_FIND_BIGGEST_OBJECT
        //     //|CV_HAAR_DO_ROUGH_SEARCH
        //     //|CV_HAAR_DO_CANNY_PRUNING
        //     |CV_HAAR_SCALE_IMAGE
        //     ,
        //     Size(30, 30) );
        // for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
        // {
        //     center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
        //     center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
        //     radius = cvRound((nr->width + nr->height)*0.25*scale);
        //     circle( img, center, radius, color, 3, 8, 0 );
        // }
    }
    cv::imshow( "result", img );
}
