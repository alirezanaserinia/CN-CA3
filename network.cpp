#include <iostream>
#include <utility>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>

// struct edge_tuple
// {
// 	int u,v;
// 	edge_tuple(int _u, int _v){
// 		u= _u;
// 		v= _v;
// 	};
// 	bool operator==(const edge_tuple & e){
// 		return (e.u==u && e.v==v);
// 	}
// } typedef edge;

int number_of_nodes = 1;
std::vector< std::vector<int> > adj(1);
std::vector< std::vector<int> > weight(1,std::vector<int> (1,-1));

bool is_delimiter(char charachter);
std::vector<std::string> split (std::string str);

void remove_edge(std::vector<std::string> command);
void show_topology();
void distance_vector(std::vector<std::string> command);
void link_state(std::vector<std::string> command);
void update_edge(std::vector<std::string> command);
void create_edge(std::vector<std::string> command);
void extend_nodes(int new_number_of_nodes);

//bool is_in(std::vector<edge> path_edge,edge cur_edge);
//void belman_ford(int n,std::vector< std::vector<int> >& adj,
//					long int* dist,int* parent,std::vector< std::vector<int> >& weight);

int main() {
	std::string command;
	
	while (getline(std::cin,command)) {
		std::vector<std::string> splited_command = split(command);

		if (splited_command.size() > 0){
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
	/*
	int n,m;
	std::cin>> n>>m;
	std::vector< std::vector<int> > adj(n);
	std::vector< std::vector<int> > new_adj(n);
	std::vector< std::vector<int> > weight(n,std::vector<int> (n,INT_MAX));

	for (int i= 0; i< m; i++){
		int u,v;
		std::cin>> u>>v;
		adj[u-1].push_back(v-1);
		weight[u-1][v-1]= 2;
	}
	for (int i=0;i<n;i++)
		weight[i][i]=0;

	long int dist[n];
	int parent[n];
	belman_ford(n,adj,dist,parent,weight);

	int v= n-1;
	std::vector<edge> path_edge;
	while(parent[v]!= -1){
		path_edge.push_back({parent[v],v});
		v= parent[v];
	}
	// for (int i=0;i<path_edge.size();i++)
	// 	std::cout<< "Path:: U: "<< path_edge[i].u<< " V: "<<path_edge[i].v<<' ';
	// std::cout<<'\n';

	for (int i=0; i<n; i++){
		for (int j=0; j< adj[i].size();j++){
			int u= i, v= adj[i][j];
			edge cur_edge(i,adj[i][j]);
			if (!is_in(path_edge,cur_edge)){
				auto it= std::find(adj[u].begin(),adj[u].end(),v);
				//adj[u].erase(it);
				new_adj[v].push_back(u);
				//adj[v].push_back(u);
				weight[u][v]= INT_MAX;
				weight[v][u]= -1;
				//std::cout<<"("<<u<<" , "<<v<<") ";	
			}
			else
				new_adj[u].push_back(v);
		}
	}
	// std::cout<<'\n';

	// for (int i=0; i<n; i++){
	// 	for (int j=0; j< n;j++){
	// 		std::cout<< weight[i][j]<< ' ';
	// 	}
	// 	std::cout<<'\n';
	// }

	belman_ford(n,new_adj,dist,parent,weight);

	bool possibility= true;
	for (int i=0; i<n; i++){
		for (int j=0; j<new_adj[i].size();j++){
			int u=i, v= new_adj[i][j];
			if (dist[v]> dist[u]+weight[u][v]){
				possibility= false;
			}
		}
	}

	if (possibility)
		std::cout<<"Yes\n";
	else
		std::cout<<"No\n";
	*/
	return 0;
}
/*
bool is_in(std::vector<edge> path_edge,edge cur_edge){
	for (int i=0; i< path_edge.size();i++)
		if (path_edge[i]== cur_edge)
			return true;
	return false;
}

void belman_ford(int n,std::vector< std::vector<int> >& adj,
					long int* dist,int* parent,std::vector< std::vector<int> >& weight){

	for (int i=0; i<n; i++){
		dist[i]=INT_MAX;
		parent[i]= -1;
	}

	dist[0]=0;

	for (int k=0; k<n-2;k++){
		for (int i=0; i<n; i++){
			for (int j=0; j<adj[i].size();j++){
				int u=i, v= adj[i][j];
				if (dist[v]> dist[u]+weight[u][v]){
					dist[v]= dist[u]+weight[u][v];
					parent[v]= u;
				}
			}
		}
	}
}
*/
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

bool is_delimiter(char charachter) {
	return charachter == ' ' || charachter == '-';
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

void extend_nodes(int new_number_of_nodes) {
	if (new_number_of_nodes >= number_of_nodes){
		int prev_number_of_nodes = number_of_nodes;
		while(new_number_of_nodes >= number_of_nodes){
			adj.push_back(std::vector<int>());
			weight.push_back(std::vector<int> (prev_number_of_nodes, -1));
			number_of_nodes++;
		}
		for (int i = 0; i < number_of_nodes; i++){
			for (int j = prev_number_of_nodes; j < number_of_nodes; j++)
				weight[i].push_back(-1);
		}
	}
}

void remove_edge(std::vector<std::string> command) {
	int source_node= std::stoi(command[1]) - 1;
	int destination_node= std::stoi(command[2]) - 1;
	if (weight[source_node][destination_node] == -1)
		return;
	adj[source_node].erase(std::remove(adj[source_node].begin(),
	adj[source_node].end(), destination_node), adj[source_node].end());
	adj[destination_node].erase(std::remove(adj[destination_node].begin(),
	adj[destination_node].end(), source_node), adj[destination_node].end());
	weight[source_node][destination_node] = -1;
	weight[destination_node][source_node] = -1;
}

void distance_vector(std::vector<std::string> command) {}

void link_state(std::vector<std::string> command) {

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
