#include <vector>
#include <string>
#include "sparse.hpp"
#include "CGSolver.hpp"
#include "COO2CSR.hpp"
void SparseMatrix::Resize(int nrows, int ncols){
  this->nrows = nrows;
  this->ncols = ncols;

}
void SparseMatrix::AddEntry(int i, int j, double val){
   //std::vector<double> copy_a=this->a;
  //std::vector<int> copy_i_idx=this->i_idx;
  //std::vector<int> copy_j_idx=this->j_idx;
   this->i_idx.push_back(i);
   this->j_idx.push_back(j);
   this->a.push_back(val);
   //this->i_idx=copy_i_idx;
  //this->a=copy_a;
  //this->j_idx=copy_j_idx;

}
void SparseMatrix::ConvertToCSR(){
  std::vector<double> copy_a=this->a;
  std::vector<int> copy_i_idx=this->i_idx;
  std::vector<int> copy_j_idx=this->j_idx;
  
  COO2CSR(copy_a,copy_i_idx,copy_j_idx);
 
  this->i_idx=copy_i_idx;
  
  this->a=copy_a;
  this->j_idx=copy_j_idx;
}
std::vector<double> SparseMatrix::MulVec(std::vector<double> &vec){

      int n1;
      n1=int(this->i_idx.size()-1);
      std::vector<double> y;
          for(int i=0;i<n1;i++){y.push_back(0);}
      for(int i=0;i<n1;i++){
               for(int j= this->i_idx[i];j<this->i_idx[i+1];j++){
                    y[i]=y[i]+this->a[j]*vec[this->j_idx[j]];
               }
          }

return y;


}
std::vector<int> SparseMatrix::get_j_idx(){return this->j_idx;}
std::vector<int> SparseMatrix::get_i_idx(){return this->i_idx;}
std::vector<double> SparseMatrix::get_a(){return this->a;}
int SparseMatrix::get_ncols(){return this->ncols;}
int SparseMatrix::get_nrows(){return this->nrows;}
