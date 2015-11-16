#include <vector>
#include <string>
#include <numeric>
#include <math.h>
#include "matvecops.hpp"
#include <iostream>

std::vector<double> computeprod_matrix_vect(std::vector<int> &row_ptr,
               std::vector<int> &col_idx,
               std::vector<double> &val,
               std::vector<double> &b){


      int n1;
      n1=int(row_ptr.size()-1);
      std::vector<double> y;
          for(int i=0;i<n1;i++){y.push_back(0);}
      for(int i=0;i<n1;i++){
               for(int j= row_ptr[i];j<row_ptr[i+1];j++){
                    y[i]=y[i]+val[j]*b[col_idx[j]];
               }
          }

return y;



}



std::vector<double> soustract_vect(std::vector<double> v1, std::vector<double> v2){
          int n1 = int(v1.size());
          int n2 =int(v2.size());
          std::vector<double> v3;
          if (n1==n2){
               for(int j=0; j<n2;j++){
                    v3.push_back(v1[j]-v2[j]);
               }
          }
          else{
               std::cerr << "DIMENSION ERROR" << std::endl;
  }
  return v3;

}
std::vector<double> add_vect(std::vector<double> v1, std::vector<double> v2){
          int n1 = int(v1.size());
          int n2 =int(v2.size());
          std::vector<double> v3;
          if (n1==n2){
               for(int j=0; j<n2;j++){
                    v3.push_back(v1[j]+v2[j]);
               }
          }
          else{
               std::cerr << "DIMENSION ERROR" << std::endl;
  }
  return v3;

}

double L2norm(std::vector<double> &v1){
          int n1 = int(v1.size());
          double k=0;
          for(int j=0;j<n1;j++){
               k=k+v1[j]*v1[j];

          }
          double k1 = sqrt(k);
          return k1;
}
double prod_vector_vector(std::vector<double> &v1,std::vector<double> &v2){
          int n1 = int(v1.size());
          int n2 =int(v2.size());
          double k=0;
          if (n1==n2){
               for(int j=0; j<n2;j++){
                    k=k+v1[j]*v2[j];
               }
          }
          else{
               std::cerr << "DIMENSION ERROR" << std::endl;
  }
return k;

}

std::vector<double>  prod_vector_scalar(double a,std::vector<double> &v1){
     int n1 = int(v1.size());
     std::vector<double> v2;
     for(int n=0;n<n1;n++){v2.push_back(0);}
     for(int j=0; j<n1;j++){
                    v2[j]=v1[j]*a;
               }
     return v2;

}
}
