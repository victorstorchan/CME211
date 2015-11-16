#include "CGSolver.hpp"
#include <vector>
#include "matvecops.hpp"
#include <string>
#include <iostream>
int CGSolver(std::vector<double> &val,
             std::vector<int>    &row_ptr, 
             std::vector<int>    &col_idx,
             std::vector<double> &b, 
             std::vector<double> &x,
             double              tol){

		std::vector<double> u_0= x;
		std::vector<double> r0;
		std::vector<double>  temp;
		temp= computeprod_matrix_vect(row_ptr,col_idx,val,x);
		
		r0= soustract_vect(b,temp);
	
		double L2norm0;
		L2norm0=L2norm(r0);
		std::vector<double> p0;
		std::vector<double>  r=r0;
		p0=r0;
		int nitermax=int(b.size());
		int niter=0;

		while(niter<nitermax ){
			
	niter=niter+1;

	std::vector<double> A_p0;
	A_p0= computeprod_matrix_vect(row_ptr,col_idx,val,p0);
	double alpha = (L2norm(r)*L2norm(r))/(prod_vector_vector(p0,A_p0));
	std::vector<double> u0_temp;

	u0_temp=add_vect(u_0,prod_vector_scalar(alpha,p0));
	u_0=u0_temp;
	r0=soustract_vect(r,prod_vector_scalar(alpha,A_p0));
	double L2norm1;
	L2norm1= L2norm(r0);
	if(L2norm1/L2norm0<tol){x=u_0;break;}
	double beta;
	beta = prod_vector_vector(r0,r0)/(prod_vector_vector(r,r));

	r=r0;
	std::vector<double> p0_temp;
	p0_temp=add_vect(r0,prod_vector_scalar(beta,p0));
	p0=p0_temp;
	
	

		}
		if(niter==nitermax){return -1;}
		else{return niter;}


}
