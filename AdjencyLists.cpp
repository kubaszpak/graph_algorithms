#include "AdjencyLists.h"

int AdjencyLists::max_int = std::numeric_limits<int>::max();

AdjencyLists::AdjencyLists()
{
}

AdjencyLists::~AdjencyLists()
{
    delete_vector();
}

AdjencyLists::AdjencyLists(std::string file_name, bool is_directed)
{

    std::ifstream file(file_name);

    int starting_vertex, final_vertex, edge_weight;

    if (file.is_open())
    {
        file >> this->number_of_edges;
        file >> this->number_of_vertices;
        file >> this->starting_vertex;
        file >> this->final_vertex;

        // adjency_lists.fill_with_inifinites(adjency_lists.number_of_vertices);
        resize_vector(number_of_vertices);

        if (file.fail())
        {
            std::cout << "File error - READ SIZE" << std::endl;
        }
        else
        {
            for (int i = 0; i < number_of_edges; i++)
            {
                file >> starting_vertex;
                file >> final_vertex;
                file >> edge_weight;

                if (file.fail())
                {
                    std::cout << "File error - READ DATA" << std::endl;
                    return;
                }
                else
                {
                    adjency_lists[starting_vertex].push_back(std::make_pair(final_vertex, edge_weight));
                    if (!is_directed)
                    {
                        adjency_lists[final_vertex].push_back(std::make_pair(starting_vertex, edge_weight));
                    }
                }
            }
        }
        file.close();
    }
    else
    {
        std::cout << "File error - OPEN" << std::endl;
        return;
    }
}

void AdjencyLists::resize_vector(int number_of_vertices)
{
    adjency_lists.resize(number_of_vertices);
}

void AdjencyLists::delete_vector()
{
    adjency_lists.clear();
}

bool AdjencyLists::is_empty()
{
    return adjency_lists.empty();
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

bool AdjencyLists::edge_exists(int from, int to)
{
    for (int i = 0; i < this->adjency_lists[from].size(); i++)
    {
        // std::cout << this->adjency_lists[from][i].first << " " << this->adjency_lists[from][i].second << std::endl;
        if (this->adjency_lists[from][i].first == to)
        {
            return true;
        }
    }
    return false;
}

void AdjencyLists::prim()
{
    std::vector<bool> visited(number_of_vertices, false);

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priority_queue;

    int vertex = this->starting_vertex;
    visited[vertex] = true;

    std::vector<Edge> result_edge_list;

    Edge edge;

    for (int i = 0; i < number_of_vertices - 1; i++)
    {

        for (int j = 0; j < this->adjency_lists[vertex].size(); j++)
        {
            // matrix[vertex][j] != AdjencyLists::max_int &&
            // std::cout << "DEBUG " << adjency_lists[vertex][j].first << " " << adjency_lists[vertex][j].second << std::endl;
            if (visited[adjency_lists[vertex][j].first] == false)
            {
                priority_queue.push(Edge(vertex, adjency_lists[vertex][j].first, adjency_lists[vertex][j].second));
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

        visited[vertex] = true;

        // if(priority_queue.empty()) break;
    }

    // for (int k = 0; k < visited.size(); k++)
    // {
    //     std::cout << visited[k] << " ";
    // }
    // std::cout << std::endl
    //           << priority_queue.empty() << std::endl;

    int result = 0;
    for (int i = 0; i < result_edge_list.size(); i++)
    {
        std::cout << result_edge_list[i] << std::endl;
        result += result_edge_list[i].weight;
    }
    std::cout << "Result: " << result << std::endl;

    if (std::find(visited.begin(), visited.end(), false) != visited.end())
    {
        std::cout << "Dla podanego grafu nie znaleziono najmniejszego drzewa rozpinajacego, nie do kazdego wierzcholka mozna znalezc droge!" << std::endl;
    }
}

void AdjencyLists::dijkstra()
{
    std::priority_queue<DijkstraVertex, std::vector<DijkstraVertex>, std::greater<DijkstraVertex>> vertex_queue;
    std::vector<int> vertex_costs(number_of_vertices, AdjencyLists::max_int);
    std::vector<int> vertex_ancestors(number_of_vertices, -1);
    std::vector<bool> visited(number_of_vertices, false);

    vertex_costs[starting_vertex] = 0;
    vertex_queue.push(DijkstraVertex(starting_vertex, 0));

    DijkstraVertex dijkstraVertex;
    int new_cost, current_cost;
    int number_of_iterations = 0;
    bool negative_edge_found = false;

    while (!vertex_queue.empty() && number_of_iterations < number_of_vertices - 1)
    {
        do
        {
            dijkstraVertex = vertex_queue.top();
            vertex_queue.pop();
        } while ((dijkstraVertex.cost != vertex_costs[dijkstraVertex.vertex_number] || visited[dijkstraVertex.vertex_number] == true) && !vertex_queue.empty());

        if (dijkstraVertex.cost != vertex_costs[dijkstraVertex.vertex_number])
        {
            break;
        }

        visited[dijkstraVertex.vertex_number] = true;

        // TODO: Potential performance improvement don't check the edge the algorithm came from
        for (int i = 0; i < this->adjency_lists[dijkstraVertex.vertex_number].size(); i++)
        {
            // matrix[dijkstraVertex.vertex_number][i]
            int vertex_number = this->adjency_lists[dijkstraVertex.vertex_number][i].first;
            if (adjency_lists[dijkstraVertex.vertex_number][i].second < 0)
                negative_edge_found = true;
            new_cost = dijkstraVertex.cost + adjency_lists[dijkstraVertex.vertex_number][i].second;
            current_cost = vertex_costs[vertex_number];
            // std::cout << "Debating in " << dijkstraVertex << " is " << new_cost << " or " << current_cost << std::endl;
            if (new_cost < current_cost)
            {
                // std::cout << "Updating " << dijkstraVertex << " FROM " << current_cost << " TO " << new_cost << std::endl;
                vertex_ancestors[vertex_number] = dijkstraVertex.vertex_number;
                vertex_costs[vertex_number] = new_cost;
                vertex_queue.push(DijkstraVertex(vertex_number, new_cost));
            }
        }
        number_of_iterations++;
    }

    if (negative_edge_found)
        std::cout << "UWAGA! Znaleziono krawedz o ujemnej wadze, w grafie moze znajdowac sie ujemny cykl!" << std::endl;

    std::cout << "Start = " << starting_vertex << std::endl;
    std::cout << "End   Dist    Path" << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::string path = "";
        std::cout << std::setw(4) << i << " ";
        if (vertex_costs[i] == AdjencyLists::max_int)
        {
            std::cout << "INF ";
        }
        else
        {
            std::cout << std::setw(4) << vertex_costs[i];
        }
        std::cout << "  |  ";
        int parent = i;
        std::vector<bool> visited_vertices(number_of_vertices, false);
        do
        {
            visited_vertices[parent] = true;
            // std::cout << "Rodzic " << parent << "Rodzic rodzica " << vertex_ancestors[parent] << std::endl;
            path = std::to_string(parent) + " " + path;
            parent = vertex_ancestors[parent];
        } while (parent != -1 && visited_vertices[parent] == false);

        std::cout
            << path << std::endl;
    }

    if (vertex_queue.empty() && std::find(visited.begin(), visited.end(), false) != visited.end())
    {
        std::cout << "UWAGA! Nie do wszystkich wierzcholkow mozna dotrzec z wierzcholka poczatkowego!" << std::endl;
    }
}