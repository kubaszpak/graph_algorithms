#include "AdjencyMatrix.h"
#include "AdjencyLists.h"

void main_menu()
{
    std::cout << "---Menu:---" << std::endl;
    std::cout << "0. Read a Graph from file" << std::endl;
    std::cout << "1. Output the graph" << std::endl;
    std::cout << "2. Prim's MST algorithm" << std::endl;
    std::cout << "3. Dijkstra's shortest path algorithm" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void graph_representation_menu()
{
    std::cout << "---Graph Representation:---" << std::endl;
    std::cout << "0. Adjency Matrix" << std::endl;
    std::cout << "1. Adjency Lists" << std::endl;
}

void edge_type_menu()
{
    std::cout << "---Edge type:---" << std::endl;
    std::cout << "0. Directed edges" << std::endl;
    std::cout << "1. Undirected edges" << std::endl;
}

void take_input(int &choice, int &output_check)
{
    char array[100];
    char buff[100];
    fgets(array, 100, stdin);
    output_check = sscanf(array, "%d %s", &choice, buff);
}

void wait_for_enter()
{
    std::cout << std::endl
              << "Press anything to continue....." << std::endl;
    getchar();
}

int take_int_input(int x)
{
    std::cout << "Pass an integer: " << std::endl;
    std::cin >> x;
    while (std::cin.fail())
    {
        std::cout << "Error, pass an integer" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    std::cin.clear();
    std::cin.ignore(256, '\n');
    return x;
}

int take_int_input(int x, int range)
{
    std::cout << "Pass an integer from range 0 to " << range << std::endl;
    std::cin >> x;
    while (std::cin.fail() || x < 0 || x > range)
    {
        std::cout << "Error, pass an integer from range 0 to " << range << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    std::cin.clear();
    std::cin.ignore(256, '\n');
    return x;
}

int main()
{
    AdjencyMatrix adjency_matrix;
    AdjencyLists adjency_lists;
    // bool inner_loop = true;
    std::string file_name;
    while (true)
    {
        system("cls");
        main_menu();
        int choice, output_check;
        take_input(choice, output_check);
        if (output_check == 1)
        {
            switch (choice)
            {
            case 0:
                system("cls");

                edge_type_menu();
                std::cout << std::endl
                          << "Choose an option from the menu: " << std::endl
                          << std::endl;
                choice = take_int_input(choice, 1);

                std::cout << "Enter a path to the text file with the graph representation: (Enter to try: graph.txt)" << std::endl;
                getline(std::cin, file_name);
                if (file_name.empty())
                {
                    file_name = "graph.txt";
                }
                // adjency_lists.swap_vector_for_empty();
                // adjency_matrix.swap_vector_for_empty();
                adjency_lists = AdjencyLists::init_from_file(file_name, choice);
                adjency_matrix = AdjencyMatrix::init_from_file(file_name, choice);
                wait_for_enter();
                break;
            case 1:
                system("cls");
                if (adjency_matrix.is_empty() || adjency_lists.is_empty())
                {
                    std::cout << "Firstly you need to read the graph from a file" << std::endl;
                    wait_for_enter();
                    break;
                }
                graph_representation_menu();
                std::cout << std::endl
                          << "Choose an option from the menu: " << std::endl
                          << std::endl;
                choice = take_int_input(choice, 1);
                if (choice == 0)
                {
                    adjency_matrix.print();
                }
                else
                {
                    adjency_lists.print();
                }
                wait_for_enter();
                break;
            case 2:
                system("cls");
                if (adjency_matrix.is_empty() || adjency_lists.is_empty())
                {
                    std::cout << "Firstly you need to read the graph from a file" << std::endl;
                    wait_for_enter();
                    break;
                }
                graph_representation_menu();
                std::cout << std::endl
                          << "Choose an option from the menu: " << std::endl
                          << std::endl;
                choice = take_int_input(choice, 1);
                if (choice == 0)
                {
                    adjency_matrix.prim();
                }
                else
                {
                    adjency_lists.prim();
                }
                wait_for_enter();
                break;
            case 3:
                system("cls");
                if (adjency_matrix.is_empty() || adjency_lists.is_empty())
                {
                    std::cout << "Firstly you need to read the graph from a file" << std::endl;
                    wait_for_enter();
                    break;
                }
                graph_representation_menu();
                std::cout << std::endl
                          << "Choose an option from the menu: " << std::endl
                          << std::endl;
                choice = take_int_input(choice, 1);
                std::cout << choice << std::endl;
                if (choice == 0)
                {
                    adjency_matrix.dijkstra();
                }
                else
                {
                    adjency_lists.dijkstra();
                }
                wait_for_enter();
                break;
            case 4:
                exit(0);
                break;
            default:
                std::cout << "Index out of bounds, try a different one \n";
                wait_for_enter();
                break;
            }
        }
        else
        {
            std::cout << "Wrong argument" << std::endl;
            wait_for_enter();
        }
    }
}