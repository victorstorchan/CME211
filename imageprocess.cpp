#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <boost/multi_array.hpp>
#include <jpeglib.h>
//#include <conio.h>
#include "hw6.hpp"
#include "image.hpp"

//pb with convolution: regarder les pixels à l'intérieurs de la matrice. Affichage ligne 36. Travailler sur a qui semble etre nul trop souvent.
void Convolution(boost::multi_array<unsigned char,2> &input,
                       boost::multi_array<unsigned char,2> &output,
                       boost::multi_array<float,2>         &kernel){
	if (input.shape()[0]==output.shape()[0] and input.shape()[1]==output.shape()[1] 
		and kernel.shape()[0]== kernel.shape()[1] and kernel.shape()[0]%2==1
		and kernel.shape()[0]>=3 ){
		int k0 =int(kernel.shape()[0]);
	   
		int k1 = int(kernel.shape()[1]);
		int k = int(floor(double(kernel.shape()[0]/2)));
		int row_size = int(output.shape()[0]);
		int column_size = int(output.shape()[1]);
		
		boost::multi_array<float,2> a(boost::extents[2*k+row_size][2*k+column_size]);
		
		for(int j=0;j<k+1;j++){for(int i=0;i<k+1;i++){a[i][j]=float(input[0][0]);}}
		for(int j=0;j<k+1;j++){for(int i=row_size+k-1;i<row_size+2*k;i++){a[i][j]=float(input[row_size-1][0]);}}
		for(int j=column_size+k-1;j<column_size+2*k;j++){for(int i=0;i<k+1;i++){a[i][j]=float(input[0][column_size-1]);}}
		for(int j=column_size+k-1;j<column_size+2*k;j++){for(int i=row_size+k-1;i<row_size+2*k;i++){a[i][j]=float(input[row_size-1][column_size-1]);}}
			
		for(int j =0;j<k;j++){for(int i=k+1;i<k+row_size-1;i++){a[i][j]=float(input[i-k][k]);}}
		for(int j =k+column_size;j<2*k+column_size;j++){for(int i=k+1;i<row_size-1;i++){a[i][j]=float(input[i][column_size-1]);}}//pb
		for(int j =k+1;j<k+column_size-1;j++){for(int i=0;i<k;i++){a[i][j]=float(input[k][j-k]);}}
		for(int j =k+1;j<k+column_size-1;j++){for(int i=k+row_size;i<2*k+row_size;i++){a[i][j]=float(input[row_size-1][j-k]);}}
		for(int j = k+1;j<k+column_size-1;j++){for(int i=k+1;i<k+row_size-1;i++){a[i][j]=float(input[i-k][j-k]);}}
		
		for(int j=k;j<k+column_size;j++){for(int i=k;i<k+row_size;i++){
			float p=0;
		boost::multi_array<float,2> b(boost::extents[k0][k1]);
		
		for(int r=0;r<k0;r++){for(int s=0; s<k1;s++){
			b[r][s]=a[i-k+r][j-k+s];
		}}
		
		for(int r=0;r<k0;r++){for(int s=0; s<k1;s++){p=p+b[r][s]*float(kernel[r][s]);}}
			if(p<0){p=0;}
			if(p>=255){p=255;}
		
         output[i-k][j-k]= static_cast<unsigned char>(lround(p));
			
		}
		
	}
    }
   else{
    std::cout << "Error from the data:" << std::endl;
    std::cout <<  " See the usage of the function convolution" << std::endl;
    

   }


}




image::image(std::string filename){
  //boost::multi_array<unsigned char,2> img;
  this->filename = filename; 
  	ReadGrayscaleJPEG(this->filename, this->img);
  	//this->img = img;
}

 void image::save(std::string filename0 ){ //in this line the pb is: how to make an argument not mandatory?
 	//boost::multi_array<unsigned char,2> img;
 	
 		WriteGrayscaleJPEG(filename0, this->img);
 		
}
void image::save(void){
	WriteGrayscaleJPEG(this->filename, this->img);
	
}
 void image::BoxBlur(int k){
 	boost::multi_array<float,2> kernel(boost::extents[k][k]);
 	for(int j=0;j<k;j++){for(int i= 0;i<k;i++){
 		kernel[i][j]= float(1/(float(k)*float(k)));
 		 	}}
 	boost::multi_array<unsigned char,2> output(boost::extents[this->img.shape()[0]][this->img.shape()[1]]);	 	
 	Convolution(this->img,output,kernel);
 	this->img = output;
 	
 	
   }


 unsigned int image::sharpness(void){
 	boost::multi_array<float,2> kernel(boost::extents[3][3]);
 	kernel[0][0]=0;kernel[1][0]=1;kernel[2][0]=0;
 	kernel[0][1]=1;kernel[1][1]=-4;kernel[2][1]=1;
 	kernel[0][2]=0;kernel[1][2]=1;kernel[2][2]=0;
 	boost::multi_array<unsigned char,2> output(boost::extents[this->img.shape()[0]][this->img.shape()[1]]);
 	Convolution(this->img,output, kernel);
 	unsigned int max = 0;
    for(int x=3; x<int(output.shape()[0])-2; ++x)
    for(int y=3; y<int(output.shape()[1])-2; ++y)
    max = std::max(static_cast<unsigned int>(output[x][y]), max);
	unsigned int max_return = max;
    return max_return;
 	}
 

