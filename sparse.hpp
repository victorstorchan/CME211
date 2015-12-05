#ifndef SPARSE_HPP
#define SPARSE_HPP
#include <iostream>
#include <vector>
#include "COO2CSR.hpp"

class SparseMatrix
{
  private:
    std::vector<int> i_idx;
    std::vector<int> j_idx;
    std::vector<double> a;
    int ncols;
    int nrows;



  public:
    /* Method to modify sparse matrix dimensions */
    void Resize(int nrows, int ncols);

    /* Method to add entry to matrix in COO format */
    void AddEntry(int i, int j, double val);

    /* Method to convert COO matrix to CSR format using provided function */
    void ConvertToCSR();

    /* Method to perform sparse matrix vector multiplication using CSR formatted matrix */
    std::vector<double> MulVec(std::vector<double> &vec);

    /* TODO: Add any additional public methods you need */
    std::vector<int> get_j_idx();
    std::vector<int> get_i_idx();
    std::vector<double> get_a();
    int get_ncols();
    int get_nrows();



};

#endif /* SPARSE_HPP */
