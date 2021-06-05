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
    std::cout << std::endl;
}

void AdjencyMatrix::prim()
{
    std::vector<bool> visited(number_of_vertices, false);

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priority_queue;

    int vertex = this->starting_vertex;

    std::vector<Edge> result_edge_list;

    Edge edge;

    // while (priority_queue.empty() == false)
    // {
    //     std::cout << priority_queue.top() << std::endl;
    //     priority_queue.pop();
    // }

    for (int i = 0; i < number_of_vertices - 1; i++)
    {

        visited[vertex] = true;

        for (int j = 0; j < number_of_vertices; j++)
        {

            if (matrix[vertex][j] != max_int && visited[j] == false)
            {
                priority_queue.push(Edge(vertex, j, matrix[vertex][j]));
            }
        }

        edge = priority_queue.top();
        priority_queue.pop();

        while (visited[edge.final_vertex] == true && !priority_queue.empty())
        {
            edge = priority_queue.top();
            // std::cout << edge << std::endl;
            priority_queue.pop();
        }

        vertex = edge.final_vertex;

        result_edge_list.push_back(edge);

        // if(priority_queue.empty()) break;
    }

    if (priority_queue.empty() && std::find(visited.begin(), visited.end(), false) != visited.end())
    {
        std::cout << "Dla podanego grafu nie znaleziono najmniejszego drzewa rozpinającego!" << std::endl;
        return;
    }

    int result = 0;
    for (int i = 0; i < result_edge_list.size(); i++)
    {
        std::cout << result_edge_list[i] << std::endl;
        result += result_edge_list[i].weight;
    }
    std::cout << "Result: " << result << std::endl;
}

void AdjencyMatrix::dijkstra()
{
    std::priority_queue<DijkstraVertex, std::vector<DijkstraVertex>, std::greater<DijkstraVertex>> vertex_queue;
    std::vector<int> vertex_costs(number_of_vertices, max_int);
    std::vector<int> vertex_ancestors(number_of_vertices, -1);
    std::vector<bool> visited(number_of_vertices, false);

    // vertex_costs[starting_vertex] = 0;
    // visited[starting_vertex] = true;
    // int vertex = starting_vertex;

    vertex_costs[starting_vertex] = 0;
    vertex_queue.push(DijkstraVertex(starting_vertex, 0));

    DijkstraVertex dijkstraVertex;
    int new_cost, current_cost;

    while (!vertex_queue.empty())
    {
        do
        {
            dijkstraVertex = vertex_queue.top();
            vertex_queue.pop();
            std::cout << dijkstraVertex << std::endl;
        } while ((dijkstraVertex.cost != vertex_costs[dijkstraVertex.vertex_number] || visited[dijkstraVertex.vertex_number] == true) && !vertex_queue.empty());

        visited[dijkstraVertex.vertex_number] = true;

        for (int i = 0; i < number_of_vertices; i++)
        {

            if (matrix[dijkstraVertex.vertex_number][i] != max_int)
            {
                std::cout << "TUTAJ" << std::endl;
                // auto it = std::find_if(vertex_queue.begin(), vertex_queue.end(), [&i](const DijkstraVertex &vertex)
                //                        { return vertex.vertex_number == i; });
                //  priority_queue.push(DijkstraVertex{});
                // std::cout << it << std::endl;
                new_cost = dijkstraVertex.cost + matrix[dijkstraVertex.vertex_number][i];
                current_cost = vertex_costs[i];
                if (new_cost < current_cost)
                {
                    vertex_ancestors[i] = dijkstraVertex.vertex_number;
                    vertex_costs[i] = new_cost;
                    vertex_queue.push(DijkstraVertex(i, new_cost));
                }
            }
        }
    }

    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << i << " " << vertex_costs[i] << " " << vertex_ancestors[i] << std::endl;
    }
}