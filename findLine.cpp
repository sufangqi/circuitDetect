
#include "findLine.h"
#define  _SHOW_
//获取图像中线的端点坐标，端点可能大于2个
float  distancePoint(const Point & pt1,const Point & pt2){
    return sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
}
void imageThin(const Mat& src,Mat& dst, int intera){
    if(src.type()!=CV_8UC1){
        printf("only binary image\n");
        return;
    }
    //非原地操作时候，copy src到dst
    if(dst.data!=src.data){
        src.copyTo(dst);
    }
    
    int i, j, n;
    int width, height;
    width = src.cols -1;
    //之所以减1，是方便处理8邻域，防止越界
    height = src.rows -1;
    int step = (int)src.step;
    int  p2,p3,p4,p5,p6,p7,p8,p9;
    uchar* img;
    bool ifEnd;
    int A1;
    Mat tmpimg;
    //n表示迭代次数
    for(n = 0; n<intera; n++){
        dst.copyTo(tmpimg);
        ifEnd = false;
        img = tmpimg.data;
        for(i = 1; i < height; i++){
            img += step;
            for(j =1; j<width; j++){
                uchar* p = img + j;
                A1 = 0;
                if( p[0] > 0){
                    if(p[-step]==0&&p[-step+1]>0){ //p2,p3 01模式
                        A1++;
                    }
                    if(p[-step+1]==0&&p[1]>0) //p3,p4 01模式
                    {
                        A1++;
                    }
                    if(p[1]==0&&p[step+1]>0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if(p[step+1]==0&&p[step]>0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if(p[step]==0&&p[step-1]>0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if(p[step-1]==0&&p[-1]>0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if(p[-1]==0&&p[-step-1]>0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if(p[-step-1]==0&&p[-step]>0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    p2 = p[-step]>0?1:0;
                    p3 = p[-step+1]>0?1:0;
                    p4 = p[1]>0?1:0;
                    p5 = p[step+1]>0?1:0;
                    p6 = p[step]>0?1:0;
                    p7 = p[step-1]>0?1:0;
                    p8 = p[-1]>0?1:0;
                    p9 = p[-step-1]>0?1:0;
                    if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7  &&  A1==1){
                        if((p2==0||p4==0||p6==0)&&(p4==0||p6==0||p8==0)) //p2*p4*p6=0 && p4*p6*p8==0
                        {
                            dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }
        
        dst.copyTo(tmpimg);
        img = tmpimg.data;
        for(i = 1; i < height; i++)
        {
            img += step;
            for(j =1; j<width; j++)
            {
                A1 = 0;
                uchar* p = img + j;
                if( p[0] > 0)
                {
                    if(p[-step]==0&&p[-step+1]>0) //p2,p3 01模式
                    {
                        A1++;
                    }
                    if(p[-step+1]==0&&p[1]>0) //p3,p4 01模式
                    {
                        A1++;
                    }
                    if(p[1]==0&&p[step+1]>0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if(p[step+1]==0&&p[step]>0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if(p[step]==0&&p[step-1]>0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if(p[step-1]==0&&p[-1]>0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if(p[-1]==0&&p[-step-1]>0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if(p[-step-1]==0&&p[-step]>0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    p2 = p[-step]>0?1:0;
                    p3 = p[-step+1]>0?1:0;
                    p4 = p[1]>0?1:0;
                    p5 = p[step+1]>0?1:0;
                    p6 = p[step]>0?1:0;
                    p7 = p[step-1]>0?1:0;
                    p8 = p[-1]>0?1:0;
                    p9 = p[-step-1]>0?1:0;
                    if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7  &&  A1==1)
                    {
                        if((p2==0||p4==0||p8==0)&&(p2==0||p6==0||p8==0)) //p2*p4*p8=0 && p2*p6*p8==0
                        {
                            dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }
        
        //如果两个子迭代已经没有可以细化的像素了，则退出迭代
        if(!ifEnd) break;
    }
    
}

void findEndPoint(const Mat & src,const vector<Point> & points,vector<Point> & endPoint){
    //  8邻域法 求端点
    for (size_t i = 0; i < points.size();i++) {
        int row = points[i].y;
        int col = points[i].x;
        if(row < 1 || col < 1 || row > src.rows - 1 || col > src.cols - 1 ){
            continue;
        }
        int count = 0;
        if (src.at<uchar>(row - 1,col - 1) > 0) count++;
        if (src.at<uchar>(row - 1,col) > 0) count++;
        if (src.at<uchar>(row - 1,col + 1) > 0) count++;
        if (src.at<uchar>(row ,col - 1) > 0) count++;
        if (src.at<uchar>(row ,col + 1) > 0) count++;
        if (src.at<uchar>(row + 1,col -1) > 0) count++;
        if (src.at<uchar>(row + 1,col) > 0) count++;
        if (src.at<uchar>(row + 1,col + 1) > 0) count++;
        
        if (count == 1) {
            endPoint.push_back(points[i]);
        }
    }
}
void  getEndPointOfLine(const Mat & src,vector<Cline> & lines){
    
    //二值化
    Mat gray;
    cvtColor(src,gray,CV_BGR2GRAY);
    Mat binary;
    double thre = 10;
    double maxval = 255;
    threshold(gray, binary, thre, maxval,CV_THRESH_BINARY_INV);
    medianBlur(binary, binary, 3);
    //线的细化
    Mat bin;
    int intera = 8;
    imageThin(binary,bin,intera);
    //寻找曲线的端点
    vector<vector<Point> > contours;
    Mat copyBin;
    bin.copyTo(copyBin);
    findContours(copyBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (size_t i = 0; i < contours.size(); i++) {
        if (contours[i].size() < 10) {
            continue;
        }
        vector<Point> endPoint;
        findEndPoint(bin,contours[i], endPoint);
        if (endPoint.size() > 0) {
            Cline line;
            line.numPoint = (int)endPoint.size();
            for (size_t k = 0;k < endPoint.size();k++) {
                line.endPoint.push_back(endPoint[k]);
            }
            lines.push_back(line);
        }
    }
}
void getEndPointOfLine(const Mat &src,const Mat & srcB,vector<Cline> & lines){
    
    //binary
    Mat binary;
    double thre = 10;
    int mode = CV_THRESH_BINARY_INV;
    binaryImage(src, binary, thre, mode);
    
    //线的细化
    Mat bin;
    int intera = 8;
    imageThin(binary,bin,intera);
    //寻找曲线的端点
    vector<vector<Point> > contours;
    Mat copyBin;
    bin.copyTo(copyBin);
    findContours(copyBin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (size_t i = 0; i < contours.size(); i++) {
        if (contours[i].size() < 10) {
            continue;
        }
        vector<Point> endPoint;
        findEndPoint(bin,contours[i], endPoint);
        if (endPoint.size() > 0) {
            Cline line;
            line.numPoint = (int)endPoint.size();
            for (size_t k = 0;k < endPoint.size();k++) {
                line.endPoint.push_back(endPoint[k]);
            }
            lines.push_back(line);
        }
    }
    
    //找与线连接的半圆
    Mat binaryB = Mat::zeros(srcB.rows, srcB.cols, CV_8UC1);
    int value1 = 200;
    int value2 = 20;
    for (int i = 0; i < srcB.rows; i++) {
        for (int j = 0; j < srcB.cols; j++) {
            if (!(srcB.at<Vec3b>(i,j)[0] >= value1 && srcB.at<Vec3b>(i,j)[1] >= value1 &&srcB.at<Vec3b>(i,j)[2] >= value1 ) && !(srcB.at<Vec3b>(i,j)[0] <= value2 && srcB.at<Vec3b>(i,j)[1] <= value2 &&srcB.at<Vec3b>(i,j)[2] <= value2)) {
                binaryB.at<uchar>(i,j) = 255;
            }
        }
    }
    medianBlur(binaryB, binaryB, 5);
    vector<CSemicircle> semicircles;
    //求半圆的半径 圆心
    vector<vector<Point> > contoursb;
    Mat copyBinaryb = binaryB.clone();
    Mat binaryBrgb;
    cvtColor(binaryB,binaryBrgb, CV_GRAY2BGR);
    findContours(copyBinaryb, contoursb, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (int k = 0; k < contoursb.size(); k++) {
        CSemicircle semi;
        float radius;
        Point2f center;
        minEnclosingCircle(contoursb[k],center, radius);
        circle(binaryBrgb, center, radius, Scalar(0,0,255));
        semi.center = center;
        semi.radius = radius;
        semicircles.push_back(semi);
    }
#ifdef _SHOW_2
    imshow("binaryb", binaryB);
    imshow("rgb", binaryBrgb);
    waitKey();
#endif
    //连接曲线与半圆
    //1 首先将连接的直线连接起来
    vector<Cline> newLines;
    float threRadius = 1.5;
    for (int i = 0; i < lines.size(); i++) {
        Cline line;
        line.numPoint = lines[i].numPoint;
        for (int j = 0 ; j < lines[i].numPoint; j++ ) {
            for (int k = 0; k < semicircles.size(); k++) {
                if (distancePoint(lines[i].endPoint[j], semicircles[k].center) < threRadius * semicircles[k].radius) {
                    line.endPoint.push_back(semicircles[k].center);
                    break;
                }
            }
        }
        newLines.push_back(line);
    }
#ifdef _SHOW_2
    Mat rgb2 = src.clone();
    for (int i = 0; i < newLines.size(); i++) {
        for (int j = 0 ; j < newLines[i].numPoint; j++) {
            circle(rgb2,newLines[i].endPoint[j], 3, Scalar(0,0,255),CV_FILLED);
        }
    }
    imshow("rgb2", rgb2);
    waitKey();
    std::cout << "newLines: " << newLines.size() << std::endl;
#endif
    //合并
    vector<Cline> circuitLines;
    for (int i = 0; i < newLines.size() ; i++) {
        int flag = 0;
        for (int j = i+1; j < newLines.size(); j++) {
            for (int m = 0 ; m < newLines[i].numPoint; m++) {
                for (int n = 0; n < newLines[j].numPoint; n++) {
                    if (newLines[i].endPoint[m] == newLines[j].endPoint[n]) {
                        vector<Point> newEndPoint;
                        for (int km = 0; km < newLines[i].numPoint; km++) {
                            if (km == m) {
                                continue;
                            }
                            newEndPoint.push_back(newLines[i].endPoint[km]);
                        }
                        for (int kn = 0; kn < newLines[j].numPoint; kn++) {
                            if (kn == n) {
                                continue;
                            }
                            newEndPoint.push_back(newLines[j].endPoint[kn]);
                        }
                        newLines[i].endPoint.clear();
                        for (int k = 0; k < newEndPoint.size(); k++) {
                            newLines[i].endPoint.push_back(newEndPoint[k]);
                        }
                        newLines[i].numPoint = (int)newLines[i].endPoint.size();
                        newLines[j].numPoint = 0;
                        newLines[j].endPoint.clear();
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    break;
                }
            }
            flag = 0;
        }
    }
    for (int i = 0; i < newLines.size(); i++) {
        if (newLines[i].numPoint == 0) {
            continue;
        }
        circuitLines.push_back(newLines[i]);
    }
#ifdef _SHOW_
    Mat rgb3 = src.clone();
    for (int i = 0; i < circuitLines.size(); i++) {
        for (int j = 0 ; j < circuitLines[i].numPoint; j++) {
            circle(rgb3,circuitLines[i].endPoint[j], 3, Scalar(0,0,255),CV_FILLED);
        }
        imshow("rgb3", rgb3);
        waitKey();
    }
    
    std::cout << "circuitLines: " << circuitLines.size() << std::endl;
#endif
}
void  binaryImage(const Mat & src,Mat & binary,double thre,int mode){
    //二值化
    Mat gray;
    cvtColor(src,gray,CV_BGR2GRAY);
    double maxval = 255;
    threshold(gray, binary, thre, maxval,mode);
    medianBlur(binary, binary, 3);
}


