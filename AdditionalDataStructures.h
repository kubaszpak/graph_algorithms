#ifndef ADDITIONAL_DATA_STRUCTURES_H
#define ADDITIONAL_DATA_STRUCTURES_H

class Edge
{

public:
    int starting_vertex;
    int final_vertex;
    int weight;

    Edge() {}

    Edge(int _starting_vertex, int _final_vertex, int _weight)
    {
        starting_vertex = _starting_vertex;
        final_vertex = _final_vertex;
        weight = _weight;
    }

    operator>(const Edge &edge) const
    {
        return weight > edge.weight;
    }

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge)
    {
        os << "S: " << edge.starting_vertex << ", E: " << edge.final_vertex << ", W: " << edge.weight;
        return os;
    }
};

class DijkstraVertex
{
public:
    int vertex_number;
    int cost;

    DijkstraVertex() {}

    DijkstraVertex(int _vertex_number, int _cost)
    {
        vertex_number = _vertex_number;
        cost = _cost;
    }

    operator>(const DijkstraVertex &dv) const
    {
        return cost > dv.cost;
    }

    friend std::ostream &operator<<(std::ostream &os, const DijkstraVertex &vertex)
    {
        os << "V: " << vertex.vertex_number << ", Cost: " << vertex.cost;
        return os;
    }
};

#endif /* ADDITIONAL_DATA_STRUCTURES_H */