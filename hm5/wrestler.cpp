#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;

//Source: https://www.cprogramming.com/tutorial/lesson14.html
//Source: https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
//Source: https://www.geeksforgeeks.org/bipartite-graph/
//Source: https://www.geeksforgeeks.org/check-if-a-given-graph-is-bipartite-using-dfs/

//Graph class represents the graph using adjacency list representation
class Graph {
    int V;      //variable holds the number of vertices
    int **adj; //pointer to an array containing adjacency list

public:
    Graph(int V);                                       //Constructor
    void addEdge (int v, int w);                        //function to add edge to a graph
    bool isBipartite(int **Graph, int wrestlers[]);     //function returns true if the graph is bipartite
    bool BFS(int **Graph, int s, int wrestlers[]);      //modified BFS algorithm
    int **adjList();                                    //returns private adjacency list variable
};

//Class Graph function creates adjacency list
Graph::Graph(int V) {
    this->V = V;

    //creates 2D array
    adj = new int*[V];
    for(int i = 0; i < V; i++) {
        adj[i] = new int[V];
    }

    //fills the 2D array
    for(int j = 0; j < V; j++) {
        for(int k = 0; k < V; k++) {
            adj[j][k] = 0;
        }
    }
}

//void addEdge function adds edges to the graph
void Graph::addEdge(int v, int w) {
    adj[v][w] = 1;
}

//bool function returns true if the graph is bipartite
bool Graph::isBipartite(int **Graph, int *wrestlers) {
    //for loop finds all adjacent vertices
    for(int i = 0; i < V; ++i) {
        wrestlers[i] = -1;
    }

    //for loop returns false if the graph is not bipartite
    for(int j = 0; j < V; j++) {
        if(wrestlers[j] == -1 && BFS(Graph, j, wrestlers) == false) {
            return false;
        }
    }
    return true;
}

//bool function is a modified BFS algorithm with bipartite function
//This function returns true is Graph[i][j] is bipartite, else false
bool Graph::BFS(int **Graph, int s, int wrestlers[]) {
    wrestlers[s] = 1;
    list <int> queue;
    queue.push_back(s);

    //run while there are vertices in queue
    while(!queue.empty()) {
        int u = queue.front();
        queue.pop_front();

        //return false if there is a self-loop
        if(Graph[u][u] == 1) {
            return false;
        }

        //for loop gets all non-colored adjacent vertices
        for(int v = 0; v < V; ++v) {

            //if an edge from u to v exists and destination v is not colored
            if(Graph[u][v] && wrestlers[v] == -1) {
                wrestlers[v] = 1 - wrestlers[u];
                queue.push_back(v);
            }

            //An edge from u to v exists and destination v is colored with same color as u
            else if(Graph[u][v] && wrestlers[v] == wrestlers[u]) {
                return false;
            }
        }

    }
    return true;
}

//Function returns the adjacent list from the private Graph class
int** Graph::adjList() {
    return adj;
}

//main function with two arguments
int main (int argc, char* argv[]) {

    //checks the number of arguements in the command line entered by the user
    if(argc != 2) {
        cout << "Enter two arguments: exectuable file, text file." << endl;
    }

    //reads the file on the command line
    ifstream readFile(argv[1]);

        int n = 0;  //variable represents number of wrestlers
        int r = 0;  //variable represents number of rivalries

        //string variables represent two wrestlers in a rivarly
        string w1;
        string w2;

        vector<string> babyfaces;       //creates vector of babyface wrestlers
        vector<string> heels;           //creates vector of heel wrestlers

        //reads the number of wrestlers from the input file
        readFile >> n;

        int wrestlers[n];       //creates team array for wrestlers
        string names[n];    //creates name array for wrestlers

        //for loop reads the names of each wrestler
        for(int i = 0; i < n; i++) {
            readFile >> names[i];
        }

        //Creates graph oject to hold all the names of the wrestlers
        Graph graph(n);

        //reads number of rivalries
        readFile >> r;

        int a = 0;
        int b = 0;

        //for loop reads the number of rivarlies
        for(int j = 0; j < r; j++) {
            readFile >> w1 >> w2;     //reads the first and second wrestler in the rivarly from the file

            //for loop traverses through the wrestler names in the names[] array
            for(int k = 0; k < n; k++) {
                //assigns vertex to the adjacency list
                if(w1 == names[k]) {
                    a = k;
                }

                //assigns vertex to the adjacency list
                else if(w2 == names[k]) {
                    b = k;
                }
            }

            //adds both newly created edges to the graph
            graph.addEdge(a,b);
            graph.addEdge(b,a);
        }

        //Determines whether or not the graph is bipartite
        if(graph.isBipartite(graph.adjList(), wrestlers)) {
            for(int x = 0; x < n; x++) {

                //if the index at x is equal to 1, pushes babyface wrestler
                if(wrestlers[x] == 1) {
                    babyfaces.push_back(names[x]);
                }

                //else if the index at x is equal to 0, pushes heel wrestler
                else if(wrestlers[x] == 0) {
                    heels.push_back(names[x]);
                }
            }

            //prints Yes if the graph is bipartite
            cout << "Yes" << endl;

            //for loop prints the list of babyfaces
            cout << "Babyfaces: ";
            for(int y = 0; y < babyfaces.size(); y++) {
                cout << babyfaces[y] << " ";
            }
            cout << endl;

            //for loop prints the list of heels
            cout << "Heels: ";
            for(int z = 0; z < heels.size(); z++) {
                cout << heels[z] << " ";
            }
            cout << endl;
        }

        //Else, if the graph is not bipartite - prints No
        else {
            cout << "No" << endl;
        }

    //close the file stream
    readFile.close();
    return 0;
}
