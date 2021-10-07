#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

class Vertex{
    public:
    int colour = -1;
    int parent = -1;
    vector<Vertex * > adjacencies;
    int vertexNumber;

    Vertex(int val){
        vertexNumber = val;
    }

    void addAdjacency(Vertex * v){
        adjacencies.push_back(v);
    }

    bool isAdjacent(Vertex v){
        int a = v.vertexNumber;

        for(Vertex * i : adjacencies){
            int b = i->vertexNumber;
            if(a == b){
                return true;
            }
        }
        return false;
    }

    int getDegree(){
        return adjacencies.size();
    }
    // In the vertex class, we must create a setColor method.
    // • This method takes in an integer representing the degree of the vertex and returns nothing.
    // • It must create an array called used, whose size is equal to the degree of the graph. Initially,
    // all items in the used array are equal to 0.
    // • Then, for every Vertex in the adjacency list, it must get the colour c. It must set used[c] =
    // 1 in order to mark colour c as used.
    // • It must then find the first index in the used array that has a value of 0. This will give us
    // the smallest unused colour.
    // • It must then set the colour property to be equal to this smallest unused colour.
    // degree is the degree of the vertex
    void setColour(int degree){
        // Each index represents a colour value
        int used [degree + 1] = {0};

        for (Vertex * v : adjacencies){
            int c = v->colour;
            if(c != -1){
                used[c] = 1;
            }

            for(int i = 0; i < degree+1; i++){
                if(used[i] == 0){
                    colour = i;
                    break;
                }
            }
        }
    }

};

class Graph{
    public:
    vector< Vertex * > vertices;
    map< Vertex * ,bool> Visited;
    //Create the new vertex and add it to the list of vertices
    void addVertex(int value){
        Vertex * newVertex = new Vertex(value);
        vertices.push_back(newVertex);
    }

    Vertex * getVertex (int value){
        vector <Vertex *> :: iterator i;
        for(i = vertices.begin(); i != vertices.end(); i++){
            if((*i)->vertexNumber == value){
                return *i;
            }
            
        }
        return nullptr;
    }
    //Adding an edge between two vertices 
    // We basically need to add each vertex to the adjaceny list of the other one 
    void addEdge(int v1, int v2){
        Vertex * one = getVertex(v1);
        Vertex * two = getVertex(v2);
        one->addAdjacency(two);
        two->addAdjacency(one);

    }

    // Method to return the Vertex with the largest degree 
    // This method takes in no arguments. It looks through the list of Vertices, returning the vertex number of the uncoloured
    // Vertex with the highest degree. If there is a tie, it must return the Vertex with the lowest vertex
    // number. (eg. If Vertex 2 and Vertex 7 both have the highest degree, as they both have degree 9
    // and have colour -1, the method will pick Vertex 2 as it has the lowest Vertex number). If there
    // is no uncoloured Vertex, it should return -1.
    int getBiggestVertex(){
        Vertex * largest ;
        vector<Vertex *> Uncoloured;

        for(Vertex * v : vertices){
            if(v->colour == -1){
                Uncoloured.push_back(v);
            }
        }
        if(Uncoloured.size() == 0){
            return -1;
        }
        vector< int > degree;
        vector< int > vertexNumber;

        for (Vertex * v: Uncoloured){
            degree.push_back(v->getDegree());
            vertexNumber.push_back(v->vertexNumber);
        }
        int maxDegree = *max_element(degree.begin(),degree.end());

        vector < int > :: iterator it;
        it = find(degree.begin(),degree.end(),maxDegree);
        int index;
        if(it!=degree.end()){
            index = it - degree.begin();
        }
        return vertexNumber[index];
    }

    // Function that will perform a depth first search on the graph
    void DFS(int startNode) {
        Vertex * node = getVertex(startNode);
        Visited[node] = true;
       // cout<< node->vertexNumber<<endl;

        vector <Vertex *> :: iterator it;

        for(it = node->adjacencies.begin(); it!= node->adjacencies.end();it++){

            if( ! Visited[*it] ){
                (*it)->parent = node->vertexNumber;
                DFS((*it)->vertexNumber);
            }
        }
    }
    
    // Function to perform a breadth first search on the graph
    void BFS (int startNode){
        vector< Vertex *> :: iterator it;
        Vertex * node = getVertex(startNode);
        queue <Vertex *> NotVisited;

        NotVisited.push(node);

        while( !NotVisited.empty()){
            Vertex * top = NotVisited.front();
            NotVisited.pop();
            Visited[top] = true;
            cout<< top->vertexNumber<<endl;
            for( it = top->adjacencies.begin();it != top->adjacencies.end(); it++){
                if(!Visited[*it]){
                    Visited[*it] = true;
                    NotVisited.push(*it);
                }
            }
        }

    }
    //Print all the vertices in the graph
    void PrintVertices(){
        vector <Vertex *> :: iterator i;
        for(i = vertices.begin(); i != vertices.end(); i++){
            cout<<(*i)->vertexNumber<<endl;
            
        }
    }

    //Print each vertex and the degree of each vertex as well 
    void PrintDegrees(){
        vector <Vertex *> :: iterator i;

        for (i = vertices.begin(); i != vertices.end(); i++){
            cout<<(*i)->vertexNumber;
            cout<<" : ";
            cout<< (*i)->getDegree()<<endl;
        }
    }

    // Color the graph
    // In order to colour the vertices, you have to continuously use getBiggestVertex to find the Vertex
    // to colour, and then call setColor to colour that Vertex. When getBiggestVertex returns -1, you
    // are done colouring.
    void ColourGraph(int numberOfVertices){
        for(int i=0;i<numberOfVertices;i++){
            int ans = getBiggestVertex();
            if(ans == -1){
                break;
            }
            Vertex * v = getVertex(ans);
            v->setColour(v->getDegree());
        }
    }

    //Print each vertex and the colour of each vertex as well 
    void PrintColours(){
        vector <Vertex *> :: iterator i;

        for (i = vertices.begin(); i != vertices.end(); i++){
            cout<<(*i)->vertexNumber;
            cout<<" : ";
            cout<< (*i)->colour<<endl;
        }
    }

    //Print each vertex and it's parent as well
    void PrintParent(){
         vector <Vertex *> :: iterator i;

        for (i = vertices.begin(); i != vertices.end(); i++){
            cout<<(*i)->vertexNumber;
            cout<<" : ";
            cout<< (*i)->parent<<endl;
        }
    }
};

int main (){

    Graph g = Graph();
    vector<int> vals;
    string cut = "-1";
    string vertices,v;
    int numberOfVertices ;
    cin >> numberOfVertices;
    for(int i =0;i<numberOfVertices;i++){
        g.addVertex(i);
    }
    while(vertices != cut){
        getline(cin,vertices);
        stringstream X(vertices);
        while(getline(X,v,',')){
            if(v == cut){
                continue;
            }
            vals.push_back(stoi(v));
            
        }
        if(vals.size() != 0){
            g.addEdge(vals[0],vals[1]);
        }
        vals.clear();
    }
    // g.ColourGraph(numberOfVertices);
    // g.PrintColours();
    // g.DFS(0);
    // g.PrintParent();
    g.BFS(2);
   
    return 0;
}