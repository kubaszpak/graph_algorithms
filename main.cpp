#include "AdjencyMatrix.h"
#include "AdjencyLists.h"

int main()
{
    // AdjencyMatrix adjency_matrix = AdjencyMatrix::init_from_file(true);
    // adjency_matrix.print();
    // adjency_matrix.prim();
    // adjency_matrix.dijkstra();
    AdjencyLists adjency_lists = AdjencyLists::init_from_file();
    adjency_lists.print();
}

//     std::vector<DijkstraVertex> vertices;
//     vertices.push_back(DijkstraVertex{1, 2});
//     vertices.push_back(DijkstraVertex{2, 3});
//     vertices.push_back(DijkstraVertex{3, 1});
//     vertices.push_back(DijkstraVertex{4, 6});
//     for (int i = 0; i < vertices.size(); i++)
//     {
//         std::cout << vertices[i] << std::endl;
//     }
//     std::cout << std::endl;
//     std::make_heap(vertices.begin(), vertices.end(), std::greater<DijkstraVertex>());
//     for (int i = 0; i < vertices.size(); i++)
//     {
//         std::cout << vertices.front() << std::endl;
//         std::pop_heap(vertices.begin(), vertices.end(), std::greater<DijkstraVertex>());
//         long min = vertices.back();
//         vertices.pop_back();
//         std::cout << min << std::endl;
//     }