#include <iostream>
#include <queue>

using namespace std;

class Node
{
private:
    int vertexNumber;
    Node *next;

public:
    Node()
    {
        vertexNumber = 0;
        next = nullptr;
    }
    Node(int n)
    {
        vertexNumber = n;
        next = nullptr;
    }
    friend class Graph;
};

class Graph
{
private:
    Node **adjList;
    bool *visitedList;
    int totalV;
    int totalE;

    void addEdge(int source, int destination)
    {
        Node *newnode = new Node(destination);
        newnode->next = adjList[source];
        adjList[source] = newnode;
    }

    void clear()
    {
        for (int i = 0; i < totalV; i++)
        {
            visitedList[i] = false;
        }
    }

public:
    Graph(int vertices, int edges)
    {
        totalE = edges;
        totalV = vertices;
        adjList = new Node *[vertices];
        visitedList = new bool[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adjList[i] = nullptr;
            visitedList[i] = false;
        }
    }

    void createGraph()
    {
        int source, destination;
        for (int i = 0; i < totalE; i++)
        {
            cout << "Enter Source and Destination \n";
            cout << "Source: ";
            cin >> source;
            cout << "Destination: ";
            cin >> destination;
            addEdge(source, destination);
            addEdge(destination, source);
        }
    }

    void display()
    {
        cout << "Graph is --> \n";
        for (int i = 0; i < totalV; i++)
        {
            if (adjList[i] == NULL)
            {
                cout << "No connections for node " << i << " \n";
            }
            else
            {
                cout << "Node connected to " << i << " --> ";
                Node *temp = adjList[i];
                while (temp != NULL)
                {
                    cout << temp->vertexNumber << " ";
                    temp = temp->next;
                }
                cout << "\n";
            }
        }
    }

    void dfs(int vertexNo)
    {
        cout << "At node " << vertexNo << "\n";
        visitedList[vertexNo] = true;
        Node *temp = adjList[vertexNo];
        while (temp)
        {
            if (!visitedList[temp->vertexNumber])
            {
                dfs(temp->vertexNumber);
            }
            temp = temp->next;
        }
        return;
    }

    void bfs(int startnode)
    {
        clear();
        queue<int> que;
        cout << "Bfs --> ";
        que.push(startnode);
        visitedList[startnode] = true;
        while (!que.empty())
        {
            int temp = que.front();
            cout << temp << " ";
            que.pop();
            Node *current = adjList[temp];
            while (current != nullptr) //checking for nodes connected to current node
            {
                if (!visitedList[current->vertexNumber])
                {
                    visitedList[current->vertexNumber] = true;
                    que.push(current->vertexNumber);
                }
                current = current->next;
            }
        }
        cout << "\n";
        clear();
        return;
    }
};

int main()
{
    cout << "Enter number of nodes: ";
    int node = 0, edges = 0;
    cin >> node;
    cout << "Enter number of edges: ";
    cin >> edges;
    Graph G(node, edges);
    G.createGraph();

    int choice = 0, choice2 = 0;
    while (choice != 3)
    {
        cout << "1.Display graph\n";
        cout << "2.Traverse the graph\n";
        cout << "3.Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            G.display();
            break;
        case 2:
            cout << "1.DFS\n";
            cout << "2.BFS\n";
            cin >> choice2;
            if (choice2 == 1)
            {
                cout << "Dfs on graph \n";
                cout << "Enter the Start Node\n";
                int startNode;
                cin >> startNode;
                G.dfs(startNode);
                cout << "\n";
            }
            else
            {
                cout << "Bfs on graph \n";
                cout << "Enter the Start Node\n";
                int startNode;
                cin >> startNode;
                G.bfs(startNode);
            }
            break;
        default:
            break;
        }
    }

    return 0;
}