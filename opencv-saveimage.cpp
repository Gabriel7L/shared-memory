#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Utils/road_time.h"
#include "Containers/nlmt_struct.h"

using namespace cv;
using namespace std;

int main(){
  VideoCapture cap(0, CAP_V4L2);
  if(!cap.isOpened()){
    cout << "Error opening video stream" << endl;
    return -1;
  }

  Mat frame;
  while (
    cap.read(frame)
  )
  {
		int64_t m_TEST_DATA;
    
		m_TEST_DATA = road_time();
			
    bool writedSuccessfully = imwrite("./images/" + to_string(m_TEST_DATA) + ".png", frame);
    if (writedSuccessfully){
      cout<< "Image saved" << endl;
    }else{
      cout <<"Error writing image" << endl;
    }
  }
  cout<< "Image capture finished" << endl;
}