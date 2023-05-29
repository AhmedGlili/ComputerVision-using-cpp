#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/////////// Importing Images  ////////// 
void getcontours(Mat imgdil,Mat img){

	vector<vector<Point>> contours;
	vector<Vec4i> heirarchy;
	findContours(imgdil, contours, heirarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img,contours,-1,Scalar(0,0,255),2);
	vector < Rect > BoundRect(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		vector<vector<Point>>conPoly(contours.size());
		string objectType;
		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(0, 0, 255), 2);
			cout<<conPoly[i].size()<<endl;
			BoundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, BoundRect[i].tl(), BoundRect[i].br(), Scalar(0, 255, 0), 5);
			int objcor = (int)conPoly[i].size();

			if (objcor == 3) {
				objectType = "Triangle";
			}
			if (objcor == 4) {
				float aspRatio =(float) BoundRect[i].width /(float) BoundRect[i].height;
				if ((aspRatio > 0.9) && (aspRatio < 1.1)) {
					objectType = "square";
				}
				else{
					objectType = "rectangle";
				}
			}
			if (objcor >4) {
				objectType = "Circle";
			}
			putText(img, objectType, {BoundRect[i].x+15,BoundRect[i].y-5} , FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1);
		}
	}

}

int main()
{
	string path = "shapes.png";
	Mat img = imread(path);
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny, imgDil, imgErode;


	/// /////preprocess ////////

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernel);
	getcontours(imgDil,img);

	imshow("Image", img);
	//imshow("Imagec", imgCanny);
	//imshow("")
	waitKey(0);

	return(0);
}