#ifndef _GETDEVICE__H
#define _GETDEVICE__H
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
typedef struct _electronComponent{
	cv::Point center;
	int radius;
	vector<Point> contours;
	Vec4i LinkLineOne;
	Vec4i LinkLineTwo;
}electronComponent;

void SortLocation(vector<double> T,vector<int> &label);

void EnhanceEdge(Mat &img,Mat &EnhancedImage);

void GetHist(Mat &img,Mat &mask, MatND &hist);

void calcProject(Mat &img,MatND hist,Mat&backproj);

void ExtractColor(Mat img,MatND &hist);

void findDeviceLinkLine(Mat backProjectImg,Point &centre,Vec4i &LinkLineOne,Vec4i &LinkLineTwo,vector<Point> &DeviceContours);

void ExtractDeviceComponentInfo(Mat img,Vec3i centre,electronComponent &DeviceInfo);

void getDevice(Mat img,vector<electronComponent> &DeviceSet);

#endif