#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/////////// Colour Detection  ////////// 
Mat imghsv,mask;
int hmin = 125, smin = 172, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
int main()
{
	string path = "shapes.png";
	Mat img = imread(path);
	cvtColor(img, imghsv, COLOR_BGR2HSV);
	namedWindow("trackbars", (640, 200));
	createTrackbar("hue min ", "trackbars", &hmin, 179);
	createTrackbar("s min  ", "trackbars", &smin, 255);
	createTrackbar("v min ", "trackbars", &vmin, 255);
	createTrackbar("hue max ", "trackbars", &hmax, 179);
	createTrackbar("s max ", "trackbars", &smax, 255);
	createTrackbar("v max ", "trackbars", &vmax, 255);

	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imghsv, lower, upper, mask);



		imshow("Image", img);
		imshow("imagehsv", imghsv);
		imshow("mask", mask);
		waitKey(1);
	}
		return (0);
}