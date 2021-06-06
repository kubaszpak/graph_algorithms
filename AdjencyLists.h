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
    AdjencyLists(std::string file_name, bool is_directed = false);
    void resize_vector(int number_of_vertices);
    void print();
    bool edge_exists(int from, int to);
    void delete_vector();
    bool is_empty();

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