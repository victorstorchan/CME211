#include "CGSolver.hpp"
#include <vector>
#include "matvecops.hpp"

int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr, 
             std::vector<int>    &col_idx,
             std::vector<double> &b, 
             std::vector<double> &x,
             double              tol){


		std::vector<double> r0;
		std::vector<double>  temp;
		temp= computeprod_matrix_vect(row_ptr,col_idx,val,x);
		r0= soustract_vect(b,temp);
		double L2norm0;
		L2norm0=L2norm(r0);
		std::vector<double> p0;
		p0=r0;
		double r=r0;
		int nitermax=b.size();
		int niter=0;
		while(niter<nitermax){
	niter=niter+1;
	std::vector<double> A_p0;
	A_p0= computeprod_matrix_vect(row_ptr,col_idx,val,p0);
	double alpha = (L2norm(r)*L2norm(r))/(prod_vector_vector(p0,A_p0));
	u0=add_vect(u0,prod_vector_scalar(alpha,p0));
	r0=soustract_vect(r,prod_vector_scalar(alpha,A_p0));
	double L2norm1;
	L2norm1= L2norm(r0);
	if(L2norm1/L2norm0<tol){break}
	beta = prod_vector_vector(r0,r0)/(prod_vector_vector(r,r));
	r=r0;
	p0=add_vect(r0,prod_vector_scalar(beta,p0));

		}
		if(niter==nitermax){return -1;}
		else{return niter;}


}
