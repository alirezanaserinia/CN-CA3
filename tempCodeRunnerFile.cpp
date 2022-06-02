for (int i = 0; i < adj[source].size(); i++) {
		dist[adj[source][i]] = weight[source][adj[source][i]];
		parent[adj[source][i]] = source;
	}