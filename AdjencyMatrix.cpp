#include "AdjencyMatrix.h"

AdjencyMatrix::AdjencyMatrix()
{
    max_int = std::numeric_limits<int>::max();
}

AdjencyMatrix::~AdjencyMatrix()
{
    matrix.clear();
}

void AdjencyMatrix::fill_with_inifinites(int number_of_vertices)
{
    matrix.resize(number_of_vertices, std::vector<int>(number_of_vertices, max_int));
}

AdjencyMatrix &AdjencyMatrix::init_from_file(bool is_directed)
{

    std::string file_name;

    std::cout << "Enter a path to the text file with the graph representation: (Enter to try: graph.txt)" << std::endl;
    getline(std::cin, file_name);
    if (file_name.empty())
    {
        file_name = "graph.txt";
    }

    std::ifstream file(file_name);

    static AdjencyMatrix adjency_matrix;

    int starting_vertex, final_vertex, edge_weight;

    if (file.is_open())
    {
        file >> adjency_matrix.number_of_edges;
        file >> adjency_matrix.number_of_vertices;
        file >> adjency_matrix.starting_vertex;
        file >> adjency_matrix.final_vertex;

        adjency_matrix.fill_with_inifinites(adjency_matrix.number_of_vertices);

        if (file.fail())
        {
            std::cout << "File error - READ SIZE" << std::endl;
        }
        else
        {
            for (int i = 0; i < adjency_matrix.number_of_edges; i++)
            {
                file >> starting_vertex;
                file >> final_vertex;
                file >> edge_weight;

                if (file.fail())
                {
                    std::cout << "File error - READ DATA" << std::endl;
                    return adjency_matrix;
                }
                else
                    adjency_matrix.matrix[starting_vertex][final_vertex] = edge_weight;
                if (!is_directed)
                {
                    adjency_matrix.matrix[final_vertex][starting_vertex] = edge_weight;
                }
            }
        }
        file.close();
    }
    else
    {
        std::cout << "File error - OPEN" << std::endl;
        return adjency_matrix;
    }

    return adjency_matrix;
}

void AdjencyMatrix::print()
{
    std::cout << "      ";
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << std::setw(3) << i << "   ";
        for (int j = 0; j < number_of_vertices; j++)
        {
            if (matrix[i][j] != max_int)
            {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            else
            {
                std::cout << "Inf"
                          << " ";
            }
        }
        std::cout << std::endl;
    }
}

void AdjencyMatrix::primMST()
{
    std::vector<bool> visited(number_of_vertices, false);

    std::priority_queue<PrimEdge, std::vector<PrimEdge>, std::greater<PrimEdge>> priority_queue;

    priority_queue.push(PrimEdge(3, 3, 3));
    priority_queue.push(PrimEdge(3, 3, 4));
    priority_queue.push(PrimEdge(3, 3, 6));
    priority_queue.push(PrimEdge(3, 3, 2));
    priority_queue.push(PrimEdge(3, 3, 9));

    while (priority_queue.empty() == false)
    {
        std::cout << priority_queue.top() << std::endl;
        priority_queue.pop();
    }
}