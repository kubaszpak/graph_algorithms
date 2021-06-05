#include "AdjencyLists.h"

int AdjencyLists::max_int = std::numeric_limits<int>::max();

AdjencyLists::AdjencyLists()
{
}

AdjencyLists::~AdjencyLists()
{
    adjency_lists.clear();
}

void AdjencyLists::resize_vector(int number_of_vertices)
{
    adjency_lists.resize(number_of_vertices);
}

AdjencyLists &AdjencyLists::init_from_file(bool is_directed)
{
    std::string file_name;

    std::cout << "Enter a path to the text file with the graph representation: (Enter to try: graph.txt)" << std::endl;
    getline(std::cin, file_name);
    if (file_name.empty())
    {
        file_name = "graph.txt";
    }

    std::ifstream file(file_name);

    static AdjencyLists adjency_lists;

    int starting_vertex, final_vertex, edge_weight;

    if (file.is_open())
    {
        file >> adjency_lists.number_of_edges;
        file >> adjency_lists.number_of_vertices;
        file >> adjency_lists.starting_vertex;
        file >> adjency_lists.final_vertex;

        // adjency_lists.fill_with_inifinites(adjency_lists.number_of_vertices);
        adjency_lists.resize_vector(adjency_lists.number_of_vertices);

        if (file.fail())
        {
            std::cout << "File error - READ SIZE" << std::endl;
        }
        else
        {
            for (int i = 0; i < adjency_lists.number_of_edges; i++)
            {
                file >> starting_vertex;
                file >> final_vertex;
                file >> edge_weight;

                if (file.fail())
                {
                    std::cout << "File error - READ DATA" << std::endl;
                    return adjency_lists;
                }
                else
                {
                    adjency_lists.adjency_lists[starting_vertex].push_back(std::make_pair(final_vertex, edge_weight));
                    if (!is_directed)
                    {
                        adjency_lists.adjency_lists[final_vertex].push_back(std::make_pair(starting_vertex, edge_weight));
                    }
                }
            }
        }
        file.close();
    }
    else
    {
        std::cout << "File error - OPEN" << std::endl;
        return adjency_lists;
    }

    return adjency_lists;
}

void AdjencyLists::print()
{
    std::cout << std::endl
              << "--- AdjencyLists ---" << std::endl
              << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << i << "    ";
        for (int j = 0; j < this->adjency_lists[i].size(); j++)
        {
            std::cout << std::left << std::setw(2) << this->adjency_lists[i][j].first << " " << std::left << std::setw(2) << this->adjency_lists[i][j].second << "    ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}