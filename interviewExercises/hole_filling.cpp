#include <opencv2/opencv.hpp>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;
using namespace cv;

#define HOLE_THRESHOLD (5)
#define IS_HOLE(i,j) (hole.at<uchar>((i), (j)) < HOLE_THRESHOLD)													\

typedef pair<int, int> Pixel;

#define X first
#define _X first.first
#define Y first
#define _Y first.second
#define VAL second
#define COOR first


// hash function for pair in order to use unorered map (hash table)
struct pair_hash {
	template<class c1, class c2>
	size_t operator()(const pair<c1, c2> &pair)const {
		return hash<c1>()(pair.first) ^ hash<c2>()(pair.second);
	}
};


//euclidean distance calcuator
static float dist(int x1, int y1, int x2, int y2) {
	float x = ((float)x1 - (float)x2)*((float)x1 - (float)x2);
	float y = ((float)y1 - (float)y2)*((float)y1 - (float)y2);
	return sqrt(x + y);
}


class HoleFiller
{
public:
	HoleFiller(const Mat& src, const Mat& hole, const int connenctivty, const float power, const float eps);
	void exactInterpolation();
	void approximateInterpolation(const int iterations);
	void resetHole();
	void showImage();
	void saveImage(string name);
	~HoleFiller();
	void setPower(float p);
	void setEpsilon(float e);
	void setConnectivity();
private:
	void get_boundary_pixel(const Mat& hole, const int i, const int j);
	float weight(const Pixel u, const Pixel v);
	Mat image;
	unordered_map<Pixel,float, pair_hash> boundary;
	unordered_map<Pixel,float, pair_hash> holes;
	int connectivity;
	float power;
	float eps;
};

HoleFiller::HoleFiller(const Mat& src, const Mat& hole, const int connenctivty, const float power, const float eps):
	connectivity(connenctivty), power(power), eps(eps)
{
	src.convertTo(image, CV_32FC1); //converting the image to float values, as requested.
	image /= 255; //normallizing values
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++) {
			if (IS_HOLE(i, j)) {
				holes.insert({{ i, j }, -1}); 
				image.at<float>(i, j) = -1;
				get_boundary_pixel(hole, i, j); // find boundary pixels.
			}
		}
	}
}

void HoleFiller::exactInterpolation()
{
	//exactly the same as the forumal of the excersise
	for (auto u : holes) {
		float up = 0.0;
		float down = 0.0;
		for (auto v : boundary) {
			float aa = weight(u.COOR, v.COOR);
			up += weight(u.COOR, v.COOR)*v.VAL;
			down += weight(u.COOR, v.COOR);
		}
		image.at<float>(u._X, u._Y) = up / down;
	}
}

void HoleFiller::approximateInterpolation(const int iterations=1)
{
	// iterating the hole pixels calculaitng each one by his known neighbors.
	for (int i = 0; i < iterations; i++)
	{
		for (auto u : holes) {
			float up = 0.0, down = 0.0;
			// iteratinf neighbors
			for (int r = -1; r <= 1; r++) {
				for (int c = -1; c <= 1; c++)
				{
					if (r == 0 && c == 0)
						continue;
					if (connectivity == 4 && (r != 0 && c != 0))
						continue;
					if (image.at<float>(u._X+r, u._X+c) >= 0) {
						up += weight({ 0,0 }, { r,c })*image.at<float>(u._X + r, u._X + c);
						down += weight({ 0 ,0}, { r,c });
					}
				}
			}
			image.at<float>(u._X, u._Y) = (down) ? up / down : 0;
		}
	}
}

void HoleFiller::resetHole()
{
	for (auto u : holes) {
		image.at<float>(u._X, u._Y) = -1;
	}
}

void HoleFiller::showImage()
{
	Mat show;
	image.copyTo(show);
	for (int i = 0; i < show.rows; ++ i ) {
		for (int j = 0; j < show.cols; ++j) {
			show.at<float>(i,j) = show.at<float>(i, j)<0 ? 0 : show.at<float>(i, j)*255;
		}
	}
	show.convertTo(show, CV_8U);
	namedWindow("HoleFiller", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("HoleFiller", show); // Show our image inside it.
	waitKey();
	destroyWindow("HoleFiller");
}

void HoleFiller::saveImage(string name)
{
	Mat show = image;
	for (int i = 0; i < show.rows; ++i) {
		for (int j = 0; j < show.cols; ++j) {
			show.at<float>(i, j) = show.at<float>(i, j) < 0 ? 0 : show.at<float>(i, j) * 255;
		}
	}
	show.convertTo(show, CV_8U);
	imwrite(name, show);
}

HoleFiller::~HoleFiller()
{

}

void HoleFiller::setPower(float p)
{
	power = p;
}
void HoleFiller::setEpsilon(float e)
{
	eps = e;
}
void HoleFiller::setConnectivity() {
	connectivity = 12 - connectivity;
}

void HoleFiller::get_boundary_pixel(const Mat& hole, const int i, const int j)
{
	for (int r = -1; r <= 1; ++r) {
		for (int c = -1; c <= 1; ++c) {
			if (r == 0 && c == 0)
				continue;
			if (connectivity == 4 && r != 0 && c != 0)
				continue;
			if (!IS_HOLE(i + r, j+c))
				boundary.insert({ { i + r,j + c }, image.at<float>(i + r, j + c) });
		}
	}
}

float HoleFiller::weight(const Pixel u, const Pixel v)
{
	return 1.0 / (pow(dist(u.X ,u.Y,v.X,v.Y),power)+eps);
}

int main(int argc, char** argv){
	if (argc != 6)
	{
		cout << " Usage: holefilling <image> <hole_mask> <z_power> <epsilon> <connectivity> "<< endl;
		return -1;
	}
	Mat srcImage, hole, dst;
	srcImage = imread(argv[1], IMREAD_GRAYSCALE);   // Read the file
	hole = imread(argv[2], IMREAD_GRAYSCALE);   // Read the hole's mask
	
	if (!srcImage.data || !hole.data)                              // Check for invalid input
	{
		cout << "Error: Could not open or find the image or hole" << endl;
		return -1;
	}
	if (hole.rows != srcImage.rows || hole.cols != srcImage.cols) {
		cout << "Error: mask and image not in the same size" << endl;
		return -1;
	}
	float power;
	float epsilon;
	int connectivity;
	stringstream str;
	try {
		str << argv[3]; str >> power; str.clear();
		str << argv[4]; str >> epsilon; str.clear();
		str << argv[5]; str >> connectivity; str.clear();
	}
	catch(...){
		cout << "Error: invalid parameter" << endl;
		return -1;
	}
	if (connectivity != 4 && connectivity != 8) {
		cout << "Error: invalid connectivity-type" << endl;
		return -1;
	}
	cout << "Every thing is in order. Initializing Hole Filler class... " << endl;

	srcImage.copyTo(dst, hole);
	HoleFiller hf(dst, hole, connectivity, power, epsilon);

	int option = 0;
	while (true) {
		if (option == 0) {
			cout << "choose what you want to do: \n";
			cout << "0 - Exit\n";
			cout << "1 - view image, to continue after click on the picture and press Enter.\n";
			cout << "2 - Exact Interpolation in O(n^2)\n";
			cout << "3 - Approximate Interpolation in O(n)\n";
			cout << "4 - Save image  \n";
			cout << "5 - reset hole\n";
			cout << "6 - set z\n";
			cout << "7 - set epsilon\n";
			cout << "8 - change connectivity\n";
		}
		else
			cout << "[0, 1, 2, 3, 4, 5, 6, 7, 8]: ";
		cin >> option;
		switch (option) {
			case 0: {
				cout << "Goodbye" << endl; 
				return 0;
			}
			case 1: {
				hf.showImage(); 
				break; 
			}
			case 2: {
				cout << "intrapolating ... ";
				hf.exactInterpolation(); 
				cout << "success" << endl;
				break; 
			}
			case 3: {
				cout << "Choose number of iteration: ";
				int num;
				cin >> num;
				cout << "intrapolating ... ";
				hf.approximateInterpolation(num);
				cout << "success" << endl;
				break;
			}
			case 4: {
				cout << "Enter path and name of the image you wish to save: ";
				string name;
				cin >> name;
				hf.saveImage(name);
				
			}
			case 5: {
				hf.resetHole(); 
				break;
			}
			case 6: {
				cout << "Enter new value: ";
				float z;
				cin >> z;
				hf.setPower(z);
				break;
			}
			case 7: {
				cout << "Enter new value: ";
				float e;
				cin >> e;
				hf.setEpsilon(e);
			
			}
			case 8: {
				hf.setConnectivity();
			}
			
			default: option = 0;
		}
	}

	return 0;
}
