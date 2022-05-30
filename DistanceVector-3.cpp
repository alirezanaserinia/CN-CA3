#include <iostream>
#include <limits>
#include <list>
using namespace std;

class Vertex{
public:
  //vertex label
  char name;
  //distance from the source vertex
  double distance; 
  //preceding vertex
  Vertex* prev = nullptr;

  Vertex(char name){
    this->name = name;
    this->distance = numeric_limits<double>::infinity();
  }
};

class Edge{
public:
  //from vertex
  Vertex* from;
  //to vertex
  Vertex* to;
  //edge weight or cost
  double cost;

  Edge(Vertex *from, Vertex* to, double cost){
    this->from = from;
    this->to = to;
    this->cost = cost;
  }
};

class BellmanFord{
public:
  /*
    *method implementing Bellman Ford algorithm
  */
  bool findPath(Vertex* source, list<Edge*> edges, int v){
    //distance of the source vertex to itself is 0
    source->distance = 0;

    //relax all the edges V-1 times
    for(int i=1; i<=(v-1); i++){
      for(Edge* edge: edges){
        if(edge->from->distance + edge->cost < edge->to->distance){
          edge->to->distance = edge->from->distance + edge->cost;
          /*
            *if edge is relaxed then also update
            *the preceding vertex of the target vertex
          */
          edge->to->prev = edge->from;
        }

      }
    }
    
    /*
      *If any more relaxation is possible
      *then, it means graph has a cycle
    */
    for(Edge* edge: edges){
      if(edge->from->distance + edge->cost < edge->to->distance){
        cout << "Graph has a negative cycle";
        return false;
      }
    }

    return true;
  }

  /*
    *function to trace path from destination to 
    *the source vertex using the preceding nodes
  */
  list<Vertex*> trace_path(Vertex* source, Vertex* destination){
    Vertex* vertex = destination;
    list<Vertex*> path;

    //iterate until we reach the source vertex
    while(vertex != source){
      //append vertex to the front of the list
      path.push_front(vertex);
      //update the iteration variable
      vertex = vertex->prev;
    }

    //also append the source vertex
    path.push_front(source);

    //return the path
    return path;
  }
};

int main() {
  //vertices of the graph
  Vertex* vertices[] = {new Vertex('A'), new Vertex('B'), new Vertex('C'), new Vertex('D'), new Vertex('E')};
  //edges of the graph
  list<Edge*> edges {new Edge(vertices[0], vertices[1], 10), 
                     new Edge(vertices[1], vertices[2], -15),
                     new Edge(vertices[0], vertices[2], 5),
                     new Edge(vertices[2], vertices[3], 20),
                     new Edge(vertices[3], vertices[4], 5),
                     new Edge(vertices[0], vertices[4], 30)};
  //driver code
  BellmanFord bellmanFord;
  /*
    *output the path only when the graph has no cycle,
    *call the findpath method with V=5
  */
  if(bellmanFord.findPath(vertices[0], edges, 5)){
    //get the path using the trace_path method
    list<Vertex*> path = bellmanFord.trace_path(vertices[0], vertices[4]);

    //output the destination vertex distance
    cout << "Distance: " << vertices[4]->distance << "\n";

    //output the path
    cout << "Path: ";
    for(Vertex* v: path){
      cout << v->name << " ";
    }
  }
}