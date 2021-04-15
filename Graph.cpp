#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct edge{            //pomocnicza struktura danych do przechowywania listy krawędzi (i ich wag)
    int s;              //węzeł początkowy krawędzi (s,t)
    int t;              //węzeł końcowy krawędzi (s,t)
    double w;            //waga krawędzi (s,t)
};

class Graph{
    private:
        double** adjMatrix;
        int n;                       //liczba węzłów
        bool directed;                //true jeśli graf jest skierowany
        bool weighted;                //true jeśli jest to graf ważony
    public:
        Graph(int n, int m, edge edges[], bool directed, bool weighted);    //tworzy graf na podstawie listy krawędzi
        void insertEdge(int i, int j, double w);                   //wstawia krawędź (i, j)(i (j,i) dla grafu nieskierowanego)
        bool check(int i, int j);                                           //sprwdza czy krawędź (i, j) istnieje
        void bfs(int s);
        void Dijkstra(int s, int*& parent, int*& distance);                //distance - tablica odlegości, parent- tablica poprzedników
        void Dijkstra2(int s, int*& parent, int*& distance);
        friend ostream& operator<<(ostream& out, Graph& g){        //wyświetla graf w postaci "listy sąsiedztwa" (z wagami dla grafów ważonych)
        	if(g.weighted==true){
        		for (int i = 0; i < g.n; i++){
        		       	out << "Adj v(" << i << "): " ;
        		       	for (int j = 0; j < g.n ; j++){
        		       	if(g.adjMatrix[i][j] != 1000 && i != j) out << j << "("<< g.adjMatrix[i][j]<<") ";
        		       	}
        		    	out << endl;
        		}
        	}

        	else{
        	for (int i = 0; i < g.n; i++){
        		out << "Adj v(" << i << "): " ;
        		for (int j = 0; j < g.n ; j++){
        			if(g.adjMatrix[i][j] != 0 || g.adjMatrix[i][j] != 0) out << j <<" ";
        		}
        		out << endl;
        	}
        	}
        	return out;
        }
};

int main(int argc, char** argv) {
 int n, m;

//testy dla zadania 0
 cout <<"Graf skierowany: \n";
 edge directedGraph[]={{0,1, 1},{1,2, 1},{1,7, 1},{2,3,1},{2,8,1},{3,2,1},{3,9,1},{4,0,1},{5,3,1},{5,8,1},{6,0,1},{6,7,1},{7,1,1},{7,4,1},{7,6,1},{8,5,1},{8,7,1},{9,8,1} /* należy podać listę krawędzi, jako trzecią składową podając 1*/};
 //ustawienie n i m
 n = 10;
 m = 18;
 Graph g(n,m,directedGraph,true, false);
 cout<<g;


//... test dla grafu nieskierowanego (może być na podstawie wcześniejszego grafu skierowanego)
 cout <<"\n\n Graf nieskierowany: \n";

 Graph g2(n,m,directedGraph, false , false);
cout<<g2;
//... testy dla grafu ważonego
cout <<"\n\n Graf ważony skierowany: \n";
 edge weightedDirectedGraph[]={{0,1, 5},{1,2, 2},{1,7, 3},{2,3,7},{2,8,6},{3,2,7},{3,9,5},{4,0,2},{5,3,2},{5,8,5},{6,0,5},{6,7,5},{7,1,3},{7,4,1},{7,6,5},{8,5,5},{8,7,1},{9,8,4}};
 //ustawienie n i m
 Graph h(n,m,weightedDirectedGraph,true, true);
 cout<<h;

 //testy dla zadania 1 - dla grafu skierowanego z zadania 0
 g.bfs(0); cout<<endl;        //przykładowe wywołanie dla s=0
 //inne testy BFS

 //testy dla zadania 2 - dla grafu ważonego z zadania 0
 int* distance = new int[n];
 int* parent = new int[n];
 h.Dijkstra(0,parent,distance);        //przykładowe wywołanie dla s = 0
 //wyświetlenie wyników: tj. odległości i poprzedników na ścieżce
 cout << "\n\nDla wywołania od 3 elementu:\ndistance[]= ";
 for (int i = 0; i< n;i++){
	 cout << distance[i] << " ";
 }
 cout << "\nparent[]= ";
 for (int i = 0; i< n;i++){
 	 cout << parent[i] << " ";
  }
 //inne testy dla innych wartości s

 h.Dijkstra(3,parent,distance);
 cout << "\n\nDla wywołania od 3 elementu:\ndistance[]= ";
 for (int i = 0; i< n;i++){
	 cout << distance[i] << " ";
 }
 cout << "\nparent[]= ";
 for (int i = 0; i< n;i++){
 	 cout << parent[i] << " ";
  }

 h.Dijkstra(6,parent,distance);

 cout << "\n\nDla wywołania od 6 elementu:\ndistance[]= ";
 for (int i = 0; i< n;i++){
	 cout << distance[i] << " ";
 }
 cout << "\nparent[]= ";
 for (int i = 0; i< n;i++){
 	 cout << parent[i] << " ";
  }
 return 0;

}
void Graph::insertEdge(int i, int j, double w){
	adjMatrix[i][j]=w;
	if(directed == false) adjMatrix[j][i]=w;
}
Graph::Graph(int n, int m, edge edges[], bool directed, bool weighted){
	this->n = n;
	this->directed = directed;

	this->weighted = weighted;
	adjMatrix= new double*[n];

	for (int i = 0; i<n ; i++){
		adjMatrix[i]= new double[n];
		for(int j = 0; j < n ; j++){
			if(weighted == false) adjMatrix[i][j] = 0;
			else {
				adjMatrix[i][j] = 1000; // INF
				if(i==j) adjMatrix[i][j] = 0;
			}
		}


	}
	for (int i = 0; i < m ; i++) insertEdge(edges[i].s, edges[i].t , edges[i].w);
}
bool Graph::check(int i, int j){
	if(adjMatrix[i][j] != 0 && adjMatrix[i][j] != 1000)return true;
	return false;
}
void Graph::bfs(int s){
	bool visited[n]{false};
	int parent[n]{1000};
	queue <int> Q;

	visited[s] = true;
	Q.push(s);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for (int i = 0 ; i<n; i++){
			if(adjMatrix[u][i]  && !visited[i]){
				if(visited[i] == false ){
					visited[i] = true;
					parent[i] = u;
					Q.push(i);
				}
			}
		}

	}
	cout << "parent:  ";
	for (int i = 0 ; i<n; i++){
		if (parent[i]== 1000)cout << "brak ";

		else cout << parent[i]<< " ";

	}
	cout << "\nvisited:  ";
		for (int i = 0 ; i<n; i++){
			cout << visited[i] <<" ";


		}
}

void Graph::Dijkstra2(int s, int*& parent, int*& distance){
	priority_queue<int> q;

	for (int u=0; u < n; u++){
		distance[u] = 1000; //INF
		parent[u] = -1;
	}
	distance[s]=0;


}


int find(int distance[], bool S[], int n)
{
	int min=1000,index;
	for(int v=0;v<n;v++)
	{
		if(S[v]==false && distance[v]<=min)
		{
			min=distance[v];
			index=v;
		}
	}
	return index;
}

void Graph::Dijkstra(int s, int*& parent, int*& distance){
	bool S[n]{false};

	for (int i=0; i < n;i++){
		distance[i] = 1000; //INF
		parent[i] = -1;
	}

	distance[s]=0;


	for (int i=0; i<n;i++){	/*int u=1000,j;
		for(j = 0; S[j]; j++);
		for(u = j+1 ; j<n; j++){
			if(!S[j] && ( distance[j] < distance[u])) u = j;

		}*/
		int u = find(distance,S,n);
		S[u] = true;
		for (int v = 0 ; v < n; v ++){
			if((adjMatrix[u][v] != 1000) && (u != v) && !S[v] ){
				if( distance[v] > (distance[u] + adjMatrix[u][v]) ){
					distance[v] = distance[u] + adjMatrix[u][v];
					parent[v] = u;
 				}
			}
		}

	}
}


