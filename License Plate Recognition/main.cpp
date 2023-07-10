#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/* Takes image as input, detects all license plates in the image, and saves the cropped license plate */

int main() {

	string path = "Resources/test3.jpg";
	Mat img = imread(path);

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml"); // model trained for Russian plates
	if (plateCascade.empty())
		cout << "XML not loaded" << endl;

	vector<Rect> plates;

	plateCascade.detectMultiScale(img, plates, 1.1, 10);

	int id = 0;
	for (int i = 0; i < plates.size(); i++) {
		Mat imgCrop = img(plates[i]);
		imwrite("Resources/Plates/" + to_string(id++) + ".png", imgCrop);
		rectangle(img, plates[i], Scalar(255, 0, 255), 3);
	}

	imshow("Image", img);
	waitKey(0);

	return 0;
}