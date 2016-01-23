#include<opencv2/opencv.hpp>
#include"_getdevice.h"
#include"findLine.h"
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}

int main(int argc, char** argv)
{
    /*const char* filename = argc >= 2 ? argv[1] : "../data/board.jpg";*/

    Mat cimg = imread("/Users/sanwan/Downloads/unconnected/game2.jpg");
	Mat img;
	resize(cimg,cimg,Size(cimg.cols/5,cimg.rows/5));

	vector<electronComponent> DeviceSet;
	getDevice(cimg,DeviceSet);
	Mat Wirelines;
    Mat SrcCopy=cimg.clone();
    Mat srcB = cimg.clone();

	for(int i = 0;i <DeviceSet.size();i++){
		electronComponent DeviceInfo = DeviceSet[i];
        vector<vector<Point>> tmp;
        tmp.push_back(DeviceSet[i].contours);
       // drawContours(SrcCopy,tmp,0,Scalar(255),CV_FILLED);
        drawContours(srcB, tmp, 0, Scalar(0),CV_FILLED);
	    circle(SrcCopy,Point(DeviceInfo.LinkLineOne[0],DeviceInfo.LinkLineOne[1]),5,Scalar(0,0,255),CV_FILLED);
		circle(SrcCopy,Point(DeviceInfo.LinkLineOne[2],DeviceInfo.LinkLineOne[3]),5,Scalar(0,0,255),CV_FILLED);
		circle(SrcCopy,Point(DeviceInfo.LinkLineTwo[0],DeviceInfo.LinkLineTwo[1]),5,Scalar(0,0,255),CV_FILLED);
		circle(SrcCopy,Point(DeviceInfo.LinkLineTwo[2],DeviceInfo.LinkLineTwo[3]),5,Scalar(0,0,255),CV_FILLED);
		circle(SrcCopy,DeviceInfo.center,DeviceInfo.radius,Scalar(0,0,255),3);
	}

    vector<Cline> circuitLines;
    getEndPointOfLine(cimg, srcB, circuitLines);
    for(int i = 0;i < circuitLines.size() ;i++){
        for(int j = 0;j < circuitLines[i].endPoint.size();j++){
            circle(SrcCopy,circuitLines[i].endPoint[j],5,Scalar(0,255,0),CV_FILLED);
        }
        
    }
    imshow("srcCopy", SrcCopy);
    waitKey();
    return 0;
}
