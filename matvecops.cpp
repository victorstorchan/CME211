#include <vector>
#include <string>
#include <numeric>
#include <math.h>
#include "matvecops.hpp"

std::vector<double> computeprod_matrix_vect(std::vector<int> &row_ptr,...
							 std::vector<int> &col_idx,...
							 std::vector<double> &val,...
							 std::vector<double> &b){


     	int n1;
     	n1=row_ptr.size()-1;
     	std::vector<int> y;
          for(int i=0;i<n1;i++){y.push_back(0);}
     	for(int i=0;i<n1;i++){
               for(int j= row_ptr[i];j<row_ptr[i+1];j++){
                    y[i]=y[i]+val[j]*b[col_idx[j]];
               }
          }

return y;



}


std::vector<double> soustract_vect(std::vector<double> &v1, std::vector<double> &v2){
          int n1 = v1.size();
          int n2 =v2.size();
          if (n1==n2){
               std::vector<double> &v3;
               for(int j=0; j<n2;j++){
                    v3.push_back(v1[j]-v2[j]);
               }
          }
          else{
               std::cerr << "DIMENSION ERROR" << std::endl;
  }
  return v3;

}
std::vector<double> add_vect(std::vector<double> &v1, std::vector<double> &v2){
          int n1 = v1.size();
          int n2 =v2.size();
          if (n1==n2){
               std::vector<double> &v3;
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
          int n1 = v1.size();
          double k=0;
          for(int j=0;j<n1;j++){
               k=k+v1[j]*v1[j];

          }
          double k1 = sqrt(k);
          return k1;
}
double prod_vector_vector(std::vector<double> &v1,std::vector<double> &v2){
          int n1 = v1.size();
          int n2 =v2.size();
          if (n1==n2){
               double k=0;
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
     int n1 = v1.size();
     for(int j=0; j<n1;j++){
                    v1[j]=v1[j]*a;
               }
     return v1;
}
