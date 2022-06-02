#include <iostream>
#include <utility>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>
#include <set>

int number_of_nodes = 1;
std::vector< std::vector<int> > adj(1);
std::vector< std::vector<int> > weight(1,std::vector<int> (1,-1));

bool is_delimiter(char charachter);
std::vector<std::string> split (std::string str);

void extend_nodes(int new_number_of_nodes);
void create_edge(std::vector<std::string> command);

void show_topology();

void update_edge(std::vector<std::string> command);

void remove_edge(std::vector<std::string> command);

// Link State
void link_state(std::vector<std::string> command);
void print_lsrp_by_source(int source_node);
void dijkstra(int source, long int* dist, int* parent);
void print_iteration(int &iter, long int* dist);
void print_lsrp_table(int source, long int* dist, int* parent);
void print_path_lsrp(int source, int i, int* parent);

// Distance Vector
void distance_vector(std::vector<std::string> command);
void print_dvrp_by_source(int source);
void belman_ford(int source,long int* dist,int* parent);
int find_next_hop(int source, int i,int* parent);
void print_path_dvrp(int source, int i, int* parent);


int main() {
	std::string command;
	
	while (getline(std::cin,command)) {
		std::vector<std::string> splited_command = split(command);

		if (splited_command.size() > 0) {
			if (splited_command[0] == "topology") {
				create_edge(splited_command);
			}
			else if (splited_command[0] == "show") {
				show_topology();
			}
			else if (splited_command[0] == "lsrp") {
				link_state(splited_command);
			}
			else if (splited_command[0] == "dvrp") {
				distance_vector(splited_command);
			}
			else if (splited_command[0] == "modify") {
				update_edge(splited_command);
			}
			else if (splited_command[0] == "remove") {
				remove_edge(splited_command);
			}
			else {
				std::cout << "Bad input. Try again\n";
			}
		}
	}
	return 0;
}

bool is_delimiter(char charachter) {
	return charachter == ' ' || charachter == '-';
}

std::vector<std::string> split(std::string str) {  
	std::string word = "";
	std::vector<std::string> splited_string;
	for (char letter: str) {
		if (is_delimiter(letter)) {
			if (word != "") {
				splited_string.push_back(word);
			}
			word = "";
		}
		else{
			word += letter;
		}
	}
	if (word != "")
		splited_string.push_back(word);
	
	return splited_string;
} 

void extend_nodes(int new_number_of_nodes) {
	if (new_number_of_nodes >= number_of_nodes) {
		int prev_number_of_nodes = number_of_nodes;
		while(new_number_of_nodes >= number_of_nodes) {
			adj.push_back(std::vector<int>());
			weight.push_back(std::vector<int> (prev_number_of_nodes, -1));
			number_of_nodes++;
		}
		for (int i = 0; i < number_of_nodes; i++) {
			for (int j = prev_number_of_nodes; j < number_of_nodes; j++)
				weight[i].push_back(-1);
		}
	}
}

void create_edge(std::vector<std::string> command) {
	for (int i = 1; i < command.size(); i += 3) {
		int source_node = std::stoi(command[i]) - 1;
		int destination_node = std::stoi(command[i + 1]) - 1;
		int cost_of_edge = std::stoi(command[i + 2]);
		if (source_node == destination_node) {
			std::cout<< "Source and Destibation are same! node: "+ 
				std::to_string(source_node + 1) + '\n';
			continue;
		}
		if (source_node >= number_of_nodes) {
			extend_nodes(source_node);
		}
		if (destination_node >= number_of_nodes) {
			extend_nodes(destination_node);
		}

		adj[source_node].push_back(destination_node);
		weight[source_node][destination_node]= cost_of_edge;
		adj[destination_node].push_back(source_node);
		weight[destination_node][source_node]= cost_of_edge;

		for (int i = 0; i < number_of_nodes; i++) {
			weight[i][i]= 0;
		}
	}
}

void show_topology() {
	std::cout<< "u\\v |";
	for (int i = 0; i < number_of_nodes; i++) {
		std::cout << '\t'<< i + 1;
	}
	std::cout <<'\n';
	for (int i = 0; i < 2 * number_of_nodes + 4; i++) {
		std::cout<< "---";
	}
	std::cout <<'\n';
	for (int i = 0; i < number_of_nodes; i++) {
		std::cout << " " << i + 1 << "  |";
		for (int j = 0; j < number_of_nodes; j++) {
			std::cout << '\t'<< weight[i][j];
		}
		std::cout << '\n';
	}	
}

void update_edge(std::vector<std::string> command) {
	int source_node = std::stoi(command[1]) - 1;
	int destination_node = std::stoi(command[2]) - 1;
	int new_weight = std::stoi(command[3]);
	if (source_node == destination_node)
		std::cout<< "Source and Destibation are same! node: " + 
				std::to_string(source_node + 1) + '\n';
	if (weight[source_node][destination_node] == -1) {
		adj[source_node].push_back(destination_node);
		adj[destination_node].push_back(source_node);
		
	}
	weight[source_node][destination_node] = new_weight;
	weight[destination_node][source_node] = new_weight;	
}

void remove_edge(std::vector<std::string> command) {
	int source_node = std::stoi(command[1]) - 1;
	int destination_node = std::stoi(command[2]) - 1;
	if (weight[source_node][destination_node] == -1)
		return;
	adj[source_node].erase(std::remove(adj[source_node].begin(),
	adj[source_node].end(), destination_node), adj[source_node].end());
	adj[destination_node].erase(std::remove(adj[destination_node].begin(),
	adj[destination_node].end(), source_node), adj[destination_node].end());
	weight[source_node][destination_node] = -1;
	weight[destination_node][source_node] = -1;
}

// Link State
void print_path_lsrp(int source, int i, int* parent) {
	std::vector<int> path_leaf_to_root;
	while(parent[i] != source) {
		path_leaf_to_root.push_back(i);
		i = parent[i];
	}
	path_leaf_to_root.push_back(i);
	std::cout << source + 1;
	for (int i = path_leaf_to_root.size() - 1; i >= 0; i--) {
		std::cout << " --> " + std::to_string(path_leaf_to_root[i] + 1);
	}
	std::cout << "\n";
}

void print_lsrp_table(int source, long int* dist, int* parent) {
	std::cout << "Path:\t[s] --> [d]\tMin-Cost\tShortest Path\n";
	std::cout << "\t---------\t---------\t-------------\n";
	for (int i = 0; i < number_of_nodes; i++) {
		if (i == source)
			continue;
		else {
		std::cout << "\t[" << source + 1 << "] --> [" << i + 1 << "]\t" << dist[i] << "\t\t";
		print_path_lsrp(source, i , parent); 
		}
	}
}

void print_iteration(int &iter, long int* dist) {
	std::cout << "\t\titer " << iter << ":" << std::endl;
	std::cout << "Dest\t\t| ";
	for (int i = 0; i < number_of_nodes; i++) {
		std::cout << i + 1 << "|\t";
	}
	std::cout << "\nCost\t\t| ";
	for (int i = 0; i < number_of_nodes; i++) {
		if (dist[i] == INT_MAX)
			std::cout << -1 << "|\t";
		else
			std::cout << dist[i] << "|\t";
	}
	std::cout << "\n";
	std::cout << "---------------------------------------------------\n";
}

void dijkstra(int source, long int* dist, int* parent) {
	for (int i = 0; i < number_of_nodes; i++){
		dist[i] = INT_MAX;
		parent[i] = -1;
	}
	dist[source] = 0;
	std::set<int> S, V, V_S;
	S.insert(source);

	for (int i = 0; i < number_of_nodes; i++) {
		if (i != source)
			V_S.insert(i);
		V.insert(i);
	}
	
	for (int i = 0; i < adj[source].size(); i++) {
		dist[adj[source][i]] = weight[source][adj[source][i]];
		parent[adj[source][i]] = source;
	}

	int arg_min, min, u, v, edge_weight, iter = 1 ;
	while (S != V)	{
		print_iteration(iter, dist); 
		iter++;
		arg_min = 0, min = INT_MAX;
		for (auto k = V_S.begin(); k != V_S.end(); k++) {
			if (dist[*k] < min) {
				min = dist[*k];
				arg_min = *k;
			}
		}
		u = arg_min;
		S.insert(u);
		V_S.erase(u);

		for (int i = 0; i < adj[u].size(); i++) {
			if (V_S.find(adj[u][i]) != V_S.end()) {
				v = adj[u][i];
				edge_weight = weight[u][v];
				
				if (weight[u][v] == -1)
					edge_weight = INT_MAX;
				if (dist[v] > dist[u] + edge_weight) {
					dist[v] = dist[u] + edge_weight;
					parent[v] = u;
					
				}
			}
		}
	}
}

void print_lsrp_by_source(int source_node) {
	long int* dist = new long int [number_of_nodes];
	int* parent = new int [number_of_nodes];
	dijkstra(source_node, dist, parent);
	print_lsrp_table(source_node, dist, parent);	
}

void link_state(std::vector<std::string> command) {
	if (command.size() == 2) {
		int source_node = std::stoi(command[1]) - 1;
		print_lsrp_by_source(source_node);
	}
	else if (command.size() == 1) {
		for (int source_node = 0; source_node < number_of_nodes; source_node++) {
			print_lsrp_by_source(source_node);
		}
	}
	else {
		std::cout << "invalid input!\n";
	}
}

// Distance Vector
void print_path_dvrp(int source, int i, int* parent) {
	std::cout << '[';
	if (i == source) {
		std::cout << i + 1;
		std::cout <<']';
		return;
	}
	std::vector<int> path_leaf_to_root;
	while(parent[i] != source) {
		path_leaf_to_root.push_back(i);
		i = parent[i];
	}
	path_leaf_to_root.push_back(i);
	std::cout << source + 1;
	for (int i = path_leaf_to_root.size() - 1; i >= 0; i--) {
		std::cout << " --> " + std::to_string(path_leaf_to_root[i] + 1);
	}
	std::cout << ']';
}

int find_next_hop(int source, int i, int* parent) {
	if (i == source){
		return i;
	}
	while(parent[i] != source){
		i = parent[i];
	}
	return i;
}

void belman_ford(int source, long int* dist, int* parent){
	for (int i = 0; i < number_of_nodes; i++){
		dist[i] = INT_MAX;
		parent[i] = -1;
	}
	dist[source] = 0;
	for (int k = 0; k < number_of_nodes; k++){
		for (int i = 0; i < number_of_nodes; i++){
			for (int j = 0; j < adj[i].size(); j++){
				int u = i, v = adj[i][j], edge_weight = weight[u][v];
				if (weight[u][v] == -1)
					edge_weight = INT_MAX;
				if (dist[v] > dist[u] + edge_weight) {
					dist[v] = dist[u] + edge_weight;
					parent[v] = u;
				}
			}
		}
	}
}

void print_dvrp_by_source(int source_node) {
	long int* dist = new long int [number_of_nodes];
	int* parent = new int [number_of_nodes];
	// long int dist[number_of_nodes];
	// int parent[number_of_nodes];
	belman_ford(source_node, dist, parent);
	std::cout << '\n';
	std::cout << "Dest\tNext Hop\tDist\tShorterst path\n";
	std::cout << "---------------------------------------------------\n";
	for (int i = 0; i < number_of_nodes; i++){
		std::cout << i + 1 << '\t';
		int next_hop = find_next_hop(source_node, i, parent) + 1;
		std::cout << next_hop << "\t\t";
		std::cout << dist[i] << '\t';
		print_path_dvrp(source_node, i, parent);
		std::cout << '\n';
	}
}

void distance_vector(std::vector<std::string> command) {
	if (command.size() == 2){
		int source_node = std::stoi(command[1]) - 1;
		print_dvrp_by_source(source_node);
	}
	else if (command.size() == 1){
		for (int source_node = 0; source_node < number_of_nodes; source_node++) {
			print_dvrp_by_source(source_node);
		}
	}
	else {
		std::cout << "invalid input!\n";
	}
}


