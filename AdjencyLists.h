#ifndef ADJENCY_LISTS_H
#define ADJENCY_LISTS_H

#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <queue>
#include <algorithm>
#include "AdditionalDataStructures.h"

class AdjencyLists
{
public:
    AdjencyLists();
    ~AdjencyLists();
    void resize_vector(int number_of_vertices);
    static AdjencyLists &init_from_file(bool is_directed = false);
    void print();

    void prim();
    void dijkstra();

private:
    std::vector<std::vector<std::pair<int, int>>> adjency_lists;
    int number_of_edges;
    int number_of_vertices;
    int starting_vertex;
    int final_vertex;
    static int max_int;
};

#endif /* ADJENCY_LISTS_H */