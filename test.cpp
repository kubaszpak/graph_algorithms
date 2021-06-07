#include "AdjencyMatrix.h"
#include "AdjencyLists.h"
#include "AdditionalDataStructures.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

int main()
{

    std::string file_name = "example_graphs/test_cases/graph_s_3000_50.txt";
    // 3 4 1 5 2                                               ^
    bool choice = false;
    int counter = 100;

    // AdjencyMatrix adjency_matrix = AdjencyMatrix(file_name, choice);
    AdjencyLists adjency_lists = AdjencyLists(file_name, choice);

    clock_t start, elapsed;

    double sum = 0;

    for (int i = 0; i < counter; i++)
    {

        start = clock();

        // adjency_matrix.prim();
        adjency_lists.prim();
        // adjency_matrix.dijkstra();
        // adjency_lists.dijkstra();

        elapsed = clock() - start;
        cout << "Time [ms] = " << (1000 * elapsed) / CLOCKS_PER_SEC << endl;
        sum += (1000 * elapsed) / CLOCKS_PER_SEC;
    }
    cout << "Final time " << sum / counter << endl;

    return 0;
}