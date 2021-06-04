#include "AdjencyMatrix.h"

int main()
{
    AdjencyMatrix adjency_matrix = AdjencyMatrix::init_from_file();
    adjency_matrix.print();
    adjency_matrix.primMST();
}