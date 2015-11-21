#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <string>
#include <boost/multi_array.hpp>




void Convolution(boost::multi_array<unsigned char,2> &input,
                       boost::multi_array<unsigned char,2> &output,
                       boost::multi_array<float,2>         &kernel);

class image {
  public:
  std::string filename;
  boost::multi_array<unsigned char,2> img;
  image(std::string filename); 
  void save(fint argc, char *argv[] );
  void BoxBlur(int k);
  unsigned int sharpness();
};

#endif /* IMAGE_HPP */
