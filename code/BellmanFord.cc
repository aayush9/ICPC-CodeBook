// Single source shortest paths with negative edge weights.
// Returns false if a negative weight cycle is detected.
// Running time: O(|V|^3)
//   INPUT:   start, w[i][j] = cost of edge from i to j
//   OUTPUT:  dist[i] = min weight path from start to i
//            dad[i] = prevector<int>ous node on the best path from the
//                      start node   
vector<int> dad;
vector<double> dist;
bool BellmanFord(int start, vector<vector<double>> &w){
  int n = w.size();
  dad = vector<int>(n, -1);
  dist = vector<double>(n, 1000000000);
  dist[start] = 0;
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[j] > dist[i] + w[i][j]){
          if (k == n-1) return false;
          else dist[j] = dist[i] + w[i][j], dad[j] = i;
        }
  
  return true;
}
int main(){}
