#include <iostream>
using namespace std;

class Graph
{
    int adjMatrix[20][20];
    int Nodes;
    int Edges;

    void addEdge(int source, int destination, int weight)
    {
        adjMatrix[source][destination] = weight;
    }

public:
    Graph(int Nodes, int Edges)
    {
        this->Nodes = Nodes;
        this->Edges = Edges;
        for (int i = 0; i < Nodes; i++)
        {
            for (int j = 0; j < Nodes; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }
    void Display()
    {
        for (int i = 0; i < Nodes; i++)
        {
            for (int j = 0; j < Nodes; j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    cout << i << "-" << j << " W: " << adjMatrix[i][j] << endl;
                }
            }
        }
    }
    void Create()
    {
        int source;
        int destination;
        int weight;
        for (int i = 0; i < Edges; i++)
        {
            cout << "Enter Source: ";
            cin >> source;
            cout << "Enter Destination: ";
            cin >> destination;
            cout << "Enter Weight: ";
            cin >> weight;
            addEdge(source, destination, weight);
        }
    }
};

int main()
{
    Graph g1(5, 6);
    g1.Create();
    g1.Display();
    return 0;
}