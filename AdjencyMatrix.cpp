#include "AdjencyMatrix.h"

int AdjencyMatrix::max_int = std::numeric_limits<int>::max();

AdjencyMatrix::AdjencyMatrix()
{
}

AdjencyMatrix::~AdjencyMatrix()
{
    delete_vector();
}

void AdjencyMatrix::fill_with_inifinites(int number_of_vertices)
{
    matrix.resize(number_of_vertices, std::vector<int>(number_of_vertices, AdjencyMatrix::max_int));
}

void AdjencyMatrix::delete_vector()
{
    matrix.clear();
}

bool AdjencyMatrix::is_empty()
{
    return matrix.empty();
}

void AdjencyMatrix::swap_vector_for_empty()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        matrix[i].clear();
        matrix[i].resize(0);
    }
    matrix.clear();
    matrix.resize(0);
}

AdjencyMatrix &AdjencyMatrix::init_from_file(std::string file_name, bool is_directed)
{
    std::cout << is_directed << std::endl;
    std::ifstream file(file_name);

    static AdjencyMatrix adjency_matrix;

    adjency_matrix.matrix.swap(std::vector<std::vector<int>>(0));

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
                {
                    adjency_matrix.matrix[starting_vertex][final_vertex] = edge_weight;
                    if (!is_directed)
                    {
                        adjency_matrix.matrix[final_vertex][starting_vertex] = edge_weight;
                    }
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
    std::cout << std::endl
              << "--- AdjencyMatrix ---" << std::endl;
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
            if (matrix[i][j] != AdjencyMatrix::max_int)
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

            if (matrix[vertex][j] != AdjencyMatrix::max_int && visited[j] == false)
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
        std::cout << "Dla podanego grafu nie znaleziono najmniejszego drzewa rozpinajacego, nie do kazdego wierzcholka mozna znalezc droge!" << std::endl;
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
    std::vector<int> vertex_costs(number_of_vertices, AdjencyMatrix::max_int);
    std::vector<int> vertex_ancestors(number_of_vertices, -1);
    std::vector<bool> visited(number_of_vertices, false);

    // vertex_costs[starting_vertex] = 0;
    // visited[starting_vertex] = true;
    // int vertex = starting_vertex;

    vertex_costs[starting_vertex] = 0;
    vertex_queue.push(DijkstraVertex(starting_vertex, 0));

    DijkstraVertex dijkstraVertex;
    int new_cost, current_cost;
    // int prev_vertex_number = -1;
    bool negative_edge_found = false;
    int number_of_iterations = 0;

    while (!vertex_queue.empty() && number_of_iterations < number_of_vertices - 1)
    {
        do
        {
            dijkstraVertex = vertex_queue.top();
            vertex_queue.pop();
            // std::cout << dijkstraVertex << std::endl;
        } while ((dijkstraVertex.cost != vertex_costs[dijkstraVertex.vertex_number] || visited[dijkstraVertex.vertex_number] == true) && !vertex_queue.empty());

        if (dijkstraVertex.cost != vertex_costs[dijkstraVertex.vertex_number])
        {
            // std::cout << "BREAK LAST" << std::endl;
            break;
        }

        visited[dijkstraVertex.vertex_number] = true;

        // TODO: Potential performance improvement don't check the edge the algorithm came from
        for (int i = 0; i < number_of_vertices; i++)
        {

            if (matrix[dijkstraVertex.vertex_number][i] != AdjencyMatrix::max_int) // && i != prev_vertex_number maybe
            {
                // auto it = std::find_if(vertex_queue.begin(), vertex_queue.end(), [&i](const DijkstraVertex &vertex)
                //                        { return vertex.vertex_number == i; });
                //  priority_queue.push(DijkstraVertex{});
                // std::cout << it << std::endl;
                if (matrix[dijkstraVertex.vertex_number][i] < 0)
                    negative_edge_found = true;
                new_cost = dijkstraVertex.cost + matrix[dijkstraVertex.vertex_number][i];
                current_cost = vertex_costs[i];
                if (new_cost < current_cost)
                {
                    // std::cout << "Updating " << dijkstraVertex << " FROM " << current_cost << " TO " << new_cost << std::endl;
                    vertex_ancestors[i] = dijkstraVertex.vertex_number;
                    vertex_costs[i] = new_cost;
                    vertex_queue.push(DijkstraVertex(i, new_cost));
                }
            }
        }
        number_of_iterations++;
        // prev_vertex_number = dijkstraVertex.vertex_number;
    }

    if (negative_edge_found)
        std::cout << "UWAGA! Znaleziono krawedz o ujemnej wadze, jesli program nie zatrzymuje sie, w grafie znajduje sie ujemny cykl, zatrzymaj dzialanie programu CTRL C" << std::endl;

    std::cout << "Start = " << starting_vertex << std::endl;
    std::cout << "End   Dist    Path" << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::string path = "";
        std::cout << std::setw(4) << i << " ";
        if (vertex_costs[i] == AdjencyMatrix::max_int)
        {
            std::cout << "INF ";
        }
        else
        {
            std::cout << std::setw(4) << vertex_costs[i];
        }
        std::cout << "  |  ";
        int parent = i;
        do
        {
            path = std::to_string(parent) + " " + path;
            parent = vertex_ancestors[parent];
        } while (parent != -1);

        std::cout
            << path << std::endl;
    }

    if (vertex_queue.empty() && std::find(visited.begin(), visited.end(), false) != visited.end())
    {
        std::cout << "UWAGA! Nie do wszystkich wierzcholkow mozna dotrzec z wierzcholka poczatkowego!" << std::endl;
    }
}