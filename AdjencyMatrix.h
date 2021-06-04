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

class Edge
{

public:
    int starting_vertex;
    int final_vertex;
    int weight;

    Edge() {}

    Edge(int _starting_vertex, int _final_vertex, int _weight)
    {
        starting_vertex = _starting_vertex;
        final_vertex = _final_vertex;
        weight = _weight;
    }

    operator>(const Edge &edge) const
    {
        return weight > edge.weight;
    }

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge)
    {
        os << "S: " << edge.starting_vertex << ", E: " << edge.final_vertex << ", W: " << edge.weight;
        return os;
    }
};

class AdjencyMatrix
{
public:
    AdjencyMatrix();
    ~AdjencyMatrix();
    void fill_with_inifinites(int number_of_vertices);
    static AdjencyMatrix &init_from_file(bool is_directed = false);
    void print();
    void prim();
    void dijkstra();

private:
    std::vector<std::vector<int>> matrix;
    int number_of_edges;
    int number_of_vertices;
    int starting_vertex;
    int final_vertex;
    int max_int;
};

#endif /* ADJENCY_MATRIX_H */