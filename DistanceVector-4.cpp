// #include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
	int src, dest, weight;
};

struct Graph {
	int V, E;
	struct Edge* edge;
};

struct Graph* create_graph(int V, int E) {
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

void print_arr(int dist[], int n) {
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

void Bellman_Ford(struct Graph* graph, int src) {
	int V = graph->V;
	int E = graph->E;
	int* dist = new int [V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX
				&& dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return;
		}
	}
	print_arr(dist, V);
	return;
}

void add_edge(struct Graph* graph, int edge_number, int src, int dest, int weight) {
	graph->edge[edge_number].src = src;
	graph->edge[edge_number].dest = dest;
	graph->edge[edge_number].weight = weight;	
}

int find_node_numbers(vector<string> topology_edges) {
	int E = topology_edges.size();
	bool is_duplicate;
	vector<int> nodes;
	for (size_t i = 0; i < E; i++) {
		vector <string> tokens;
		stringstream check1(topology_edges[i]);
		string intermediate;
		while(getline(check1, intermediate, '-')) {
        tokens.push_back(intermediate);
    	}

		for (size_t i = 0; i < 2; i++){
			is_duplicate = false;
			for (size_t j = 0; j < nodes.size(); j++)
				if (stoi(tokens[i]) == nodes[j])
					is_duplicate = true;
			if (is_duplicate == false)
				nodes.push_back(stoi(tokens[i]));
		}	
	}
	return nodes.size();
}

void run_topology_command(struct Graph* graph, vector<string> topology_edges, int & V, int & E) {
	E = topology_edges.size();
	V = find_node_numbers(topology_edges);
	graph = create_graph(V, E);
	int src, dst, weight;
	for (size_t i = 0; i < E; i++) {
		vector <string> tokens;
		stringstream check1(topology_edges[i]);
		string intermediate;
		while(getline(check1, intermediate, '-')) {
        tokens.push_back(intermediate);
    	}
		src = stoi(tokens[0]);
		dst = stoi(tokens[1]);
		weight = stoi(tokens[2]);
		if (src != dst)
			add_edge(graph, i, src, dst, weight);
		else	
			cout << "Source and destination nodes can not be the same : node ["<< src << "]" << endl;
	}
	

}

void run_show_command(struct Graph* graph) {
	cout << "u\v |";
	vector<vector<int>> adj_list;
	vector<int> row_list;
	for (size_t i = 1; i < graph->V + 1; i++) {
		for (size_t j = 1; j < graph->V + 1; j++) {
			for (size_t k = 0; k < graph->E; k++) {
				if (graph->edge[k].src == i) {
					
				}
			}
			
		}
		
	}
	

}

void parse_command(struct Graph* graph, string input_command, int & V, int & E) {
	stringstream check1(input_command);
	string intermediate;
	vector<string> tokens;

    while(getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }
    
	// E = tokens.size() - 1;

    if (tokens[0] == "topology") {
		vector<string> edges(tokens.begin() + 1, tokens.end());
		run_topology_command(graph, edges, V, E);
	}
	else if (tokens[0] == "show") {
		run_show_command(graph);
	}
	else if (tokens[0] == "lsrp") {

	}
	else if (tokens[0] == "dvrp") {

	}
	else if (tokens[0] == "modify") {

	}
	else if (tokens[0] == "remove") {

	}
	else {
		cout << "Bad input. Try again\n";
	}

}

int main() {
	int V, E;
	struct Graph* graph; 
	int edge_counter = 0;
	string input;

	while (1) {
		getline(cin, input);
		parse_command(graph, input, V, E);

	}



	// add edge 0-1 (or A-B in above figure)
	// graph->edge[0].src = 0;
	// graph->edge[0].dest = 1;
	// graph->edge[0].weight = -1;

	// Bellman_Ford(graph, 0);

	return 0;
}
