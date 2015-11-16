#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "matvecops.hpp"
#include "CGSolver.hpp"
#include "COO2CSR.hpp"
#include <tuple>

int main(int argc, char *argv[]) {
    if (argc < 2) {
    std::cout << "Usage:" << std::endl;
    std::cout <<  " ./CGsolver <matrix file> " << std::endl;
    return 0;
    }
    std::string filename = argv[1];
    std::ifstream f;
    f.open(filename.c_str());
    if (f.is_open()) {
    	 std::vector<std::tuple<int,int,double>> data;
    	 int rows;
    	 int columns;
    	 double values;
         int n1,n2;
         f>>n1>>n2;
    	while (f >> rows >> columns >> values) {
      			data.emplace_back(rows, columns, values);
    }

    f.close();
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<double> val;
    for(unsigned int n = 0; n < data.size(); n++) {
    	row_ptr.push_back(std::get<0>(data[n]));
    	col_idx.push_back(std::get<1>(data[n]));
    	val.push_back(std::get<2>(data[n]));

}
  COO2CSR(val,row_ptr,col_idx);
std::vector<double> x;
std::vector<double> b;
for(int i;i<n1;i++){b.push_back(0);x.push_back(1);}
  int niter;
  niter=CGSolver(val,row_ptr,col_idx,b,x,0.00001);
//reste a faire: converts the matrix to CSR
//format, runs your CG solver function with a starting guess of ones for the
//solution and zeros for the right hand side
if(niter==-1){std::cout <<  " Fail to converge" << std::endl;}
else{std::cout <<  " SUCCESS: CG solver converged in" << niter<<"iterations."<<std::endl;
}


  }
  else {
    std::cout << "Failed to open file" << std::endl;
  }
return 0;



    }





