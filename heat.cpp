#include <string>
#include <vector>
#include "sparse.hpp"
#include "heat.hpp"
#include "CGSolver.hpp"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>

int HeatEquation2D::Setup(std::string inputfile){
    std::ifstream f;
    f.open(inputfile.c_str());
    if (f.is_open()) {
      float len,wi,h;
       f>>len>>wi>>h;
       double Tc,Th;
       f>>Tc>>Th;
       f.close();
       
       int nx, ny;
       nx=int(len/h)+1;
       ny=int(wi/h)+1;
       
    this->A.Resize((nx-1)*(ny-2), (nx-1)*(ny-2));
    for(int i=0;i<ny-2;i++){for(int j=0;j<nx-1;j++){
      if(i==0 and j==0){this->A.AddEntry(0,0,4);this->A.AddEntry(0,1,-1);//pb avec la deuxieme entré (colonne)
                          this->A.AddEntry(0,nx-1,-1);this->A.AddEntry(0,nx-2,-1);}
      if(i==0 and j!=0 and j!=nx-2){this->A.AddEntry(j,j-1,-1);this->A.AddEntry(j,j,4);
                          this->A.AddEntry(j,j+1,-1);this->A.AddEntry(j,nx+j-1,-1);}
      if(i==0 and j==nx-2){this->A.AddEntry(j,0,-1);this->A.AddEntry(j,j-1,-1);
                          this->A.AddEntry(j,j,4);this->A.AddEntry(j,nx+j-1,-1);}
      if(i>=1 and i<=ny-4){if(j!=0 and j!=nx-2){this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+j-1,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i+j+1,-1);this->A.AddEntry((nx-1)*i+j,(nx-1)*(i+1)+j,-1);}//error au 7
                           if(j==0){this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+nx-2,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i+j+1,-1);this->A.AddEntry((nx-1)*i+j,(nx-1)*(i+1)+j,-1);

                        }
                        if(j==nx-2){this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+j-1,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i,-1);this->A.AddEntry((nx-1)*i+j,(nx-1)*(i+1)+j,-1);}

                      }
      if(i==ny-3 ){if(j!=0 and j!=nx-2){this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+j-1,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i+j+1,-1);}

        else if(j==0){this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+nx-2,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i+j+1,-1);}

        else{this->A.AddEntry((nx-1)*i+j,(i-1)*(nx-1)+j,-1);this->A.AddEntry((nx-1)*i+j,i*(nx-1)+j-1,-1);
                          this->A.AddEntry((nx-1)*i+j,(i*(nx-1)+j),4);this->A.AddEntry((nx-1)*i+j,(nx-1)*i,-1);}
       }//celle du dernier if
     }
      }//celle du dernier for

      for(int j=0;j<nx-1;j++){this->b.push_back(Th);}
      for(int j=0;j<(nx-1)*(ny-2)-2*(nx-1);j++){this->b.push_back(0);}
      for(int i=0;i<nx-1;i++){this->b.push_back(-Tc*(exp(-10*(double(float(i)*h)-double(len/2))*(double(float(i)*h)-double(len/2)))-2));}
  std::cout<<b[(nx-1)*(ny-2)-2*(nx-1)+nx-1+int((nx-1)/2)-1]<<std::endl;
}
else {
    std::cout << "Failed to open file" << std::endl;
  }
 
  

    
return 0;

}

int HeatEquation2D::Solve(std::string soln_prefix){
//std::vector<double> var_a=this->A.get_a();
//std::vector<int> var_i = this->A.get_i_idx();
//std::vector<int> var_j = this->A.get_j_idx();


//COO2CSR(var_a,var_i,var_j);
this->A.ConvertToCSR();
std::vector<double> var_a=this->A.get_a();
std::vector<int> var_i = this->A.get_i_idx();
std::vector<int> var_j = this->A.get_j_idx();

std::vector<double> var_x=this->x;
for(int i=0;i<this->A.get_ncols();i++){var_x.push_back(1);}
int niter;

std::vector<double> var_b=this->b;

niter=CGSolver(var_a,var_i ,var_j,var_b,var_x,0.00001);

std::ofstream g;
g.open(soln_prefix.c_str());
if (g.is_open()) {
   std::cout.setf(std::ios::scientific, std::ios::floatfield);
   std::cout.precision(4);
  for(int n =0;n<this->A.get_ncols();n++){g<<std::setprecision(4)<<var_x[n]<<std::endl;}

g.close();
if(niter==-1){std::cout <<  " Fail to converge" << std::endl;}
else{std::cout <<  " SUCCESS: CG solver converged in" <<" "<< niter<<" "<<"iterations."<<std::endl;
}
}

  
  else {
    std::cout << "Failed to open file" << std::endl;
  }
return 0;




}
SparseMatrix HeatEquation2D::getA(){return this->A;};







