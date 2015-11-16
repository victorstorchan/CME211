
#pragma once
#include <string>

#include <vector>



std::vector<double> computeprod_matrix_vect(std::vector<int> &row_ptr,
							 std::vector<int> &col_idx,
							 std::vector<double> &val,
							 std::vector<double> &b);

std::vector<double> soustract_vect(std::vector<double> v1, std::vector<double> v2);

double L2norm(std::vector<double> &v1);

double prod_vector_vector(std::vector<double> &v1,std::vector<double> &v2);

std::vector<double> add_vect(std::vector<double> v1, std::vector<double> v2);

<<<<<<< HEAD
std::vector<double>  prod_vector_scalar(double a,std::vector<double> &v1);
=======
std::vector<double>  prod_vector_scalar(double a,std::vector<double> &v1);
>>>>>>> bd2aeded7070b02a4aba4d4c9186d7855930e53a
