#ifndef ADJENCY_MATRIX_H
#define ADJENCY_MATRIX_H

#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <queue>
#include <algorithm>
#include "AdditionalDataStructures.h"

class AdjencyMatrix
{
public:
    AdjencyMatrix();
    ~AdjencyMatrix();
    AdjencyMatrix(std::string file_name, bool is_directed = false);
    void fill_with_inifinites(int number_of_vertices);
    void print();
    void delete_vector();
    bool is_empty();

    void prim();
    void dijkstra();

private:
    std::vector<std::vector<int>> matrix;
    int number_of_edges;
    int number_of_vertices;
    int starting_vertex;
    int final_vertex;
    static int max_int;
};

#endif /* ADJENCY_MATRIX_H */