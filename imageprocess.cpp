// *****   work in progress    ******

#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <boost/multi_array.hpp>
#include <jpeglib.h>
#include <conio.h>
#include "hw6.hpp"




void Convolution(boost::multi_array<unsigned char,2> &input,
                       boost::multi_array<unsigned char,2> &output,
                       boost::multi_array<float,2>         &kernel){
	if (input.shape()[0]==output.shape()[0] and input.shape()[1]==output.shape()[1] 
		and kernel.shape()[0]== kernel.shape()[1] and kernel.shape()[0]%2==1
		and kernel.shape()[0]>=3 ){
		int k0 =kernel.shape()[0]];
		int k1 = kernel.shape()[]1];
		int k = floor(kernel.shape()[0]/2);
		int row_size = output.shape()[0];
		int column_size = output.shape()[1];
		boost::array<float,2> a(boost::extents[2*k+row_size][2*k+column_size]);
		for(int j=0;j<k+1;j++){for(int i=0;i<k+1;i++){a[i][j]=float(input[0][0]);}}
		for(int j=0;j<k+1;j++){for(int i=row_size+k-1;i<row_size+2*k;i++){a[i][j]=float(input[row_size-1][0]);}}
		for(int j=column_size+k-1;j<column_size+2*k;j++){for(int i=0;i<k+1;i++){a[i][j]=float(input[0][column_size-1]);}}
		for(int j=column_size+k-1;j<column_size+2*k;j++){for(int i=row_size+k-1;i<row_size+2*k;i++){a[i][j]=float(input[row_size-1][column_size-1]);}}
		for(int j =0;j<k;j++){for(int i=k+1;i<k+row_size-1;i++){a[i][j]=float(input[i][k]);}}
		for(int j =k+column_size;j<2*k+column_size;j++){for(int i=k+1;i<row_size-1;i++){a[i][j]=float(input[i][k+column_size-1]);}}
		for(int j =k+1;j<k+column_size-1;j++){for(int i=0;i<k;i++){a[i][j]=float(input[k][j]);}}
		for(int j =k+1;j<k+column_size-1;j++){for(int i=k+row_size;i<2*k+row_size;i++){a[i][j]=float(input[k+row_size-1][j]);}}
		for(j=k;j<k+column_size;j++){for(i=k;i<k+row_size;i++){
		boost::array<float,2> b(boost::extents[k0][k1);
		float s =0;
		for(int r=0;r<k0;r++){for(int s=0; s<){
			b[r][s]=a[i-k+r][j-k+s];
		}}
		for(int r=0;r<k0;r++){for(int s=0; s<){
			b[r][s]=a[i-k+r][j-k+s];
		}}
		for(int r=0;r<k0;r++){for(int s=0; s<){s=s+b[r][s]*kernel[r][s];}}
		output[i][j]= static_cast<unsigned char>(lround(s));

		}
	}
   else{
    std::cout << "Error from the data:" << std::endl;
    std::cout <<  " See the usage of the function convolution" << std::endl;
    return 0;

   }





}

class image {
	public:
  std::string filename;
  boost::multi_array<unsigned char,2> img;
  image(std::string filename) { this->filename = filename; 
  	boost::multi_array<unsigned char,2> img;
  	ReadGrayscaleJPEG(this->filename, img);
  	this->img = img;
}
 void save(fint argc, char *argv[] ){
 	boost::multi_array<unsigned char,2> img;
 	if (argc < 2){
 		WriteGrayscaleJPEG(this->filename, img);
 	}
 	else{
 		std::string filename2 = argv[1];
 		WriteGrayscaleJPEG(filename2, img);

 	}
 }
 void BoxBlur(k){
 	boost::array<float,2> kernel(boost::extents[k][k]);
 	for(int j=0;j<k;j++){for(int i= 0;i<k;i++){
 		kernel[i][j]= 1/(k*k);
 		 	}}
 	Convolution(img,
                img,
                kernel);



 }
};
