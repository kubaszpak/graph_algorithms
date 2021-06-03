#ifndef ADJENCY_MATRIX_H
#define ADJENCY_MATRIX_H

#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

class AdjencyMatrix
{
public:
    AdjencyMatrix();
    ~AdjencyMatrix();
    void fill_with_inifinites(int number_of_vertices);
    static AdjencyMatrix &init_from_file(bool is_directed = false);
    void print();
    void primMST();

private:
    std::vector<std::vector<int>> matrix;
    int number_of_edges;
    int number_of_vertices;
    int starting_vertex;
    int final_vertex;
    int max_int;
};

#endif /* ADJENCY_MATRIX_H */