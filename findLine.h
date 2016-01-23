
#ifndef _findLine__
#define _findLine__

#include <opencv2/opencv.hpp>
using namespace cv;

struct Cline{
    int numPoint;
    vector<Point> endPoint;
};
struct CSemicircle{
    Point center;
    float radius;
};
void getEndPointOfLine(const Mat &src,vector<Cline> & lines);
void getEndPointOfLine(const Mat &src,const Mat & srcB,vector<Cline> & lines);
void imageThin(const Mat & src,Mat & dst, int intera);
void findEndPoint(const Mat & src,const vector<Point> & points,vector<Point> &endPoint);
void  binaryImage(const Mat & src,Mat & binary,double thre,int mode);
#endif 
