#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// void floyd_warshall(vector<vector<long int> > &dist,int n) {
//     for (int k = 0; k < n; k++)
//         for (int i = 0; i < n; i++)
//             for (int j = 0; j < n; j++) 
//                 if ( dist[i][k] + dist[k][j] < dist[i][j] )
//                     dist[i][j] = dist[i][k] + dist[k][j];
// }

struct Aresta {
	long int v, w;
	double peso;
	Aresta(long int v = -1, long int w = -1,double peso = 0) : v(v), w(w), peso(peso) { }
};

bool BellmanFord(vector<Aresta> &arestas,int inicial,int n){
    vector<long int> custo(n,4294967295);
    custo[inicial] = 0;

    for(int i=0;i<(n-1);i++){
        for(int j=0;j<arestas.size();j++){
            if((custo[arestas[j].v] + arestas[j].peso) < custo[arestas[j].w])
                custo[arestas[j].w] = custo[arestas[j].v] + arestas[j].peso;
        }
    }

    for(int j=0;j<arestas.size();j++){
        if((custo[arestas[j].v] + arestas[j].peso) < custo[arestas[j].w])
            return false;
    }
    
    return true;
}

int main( ) {
    int t;
    cin >> t;

    while (t>0){
        int n,m;
        cin >>n >> m;
        vector<Aresta> arestas(m);

        if(m == 0 || n == 1 ){
            cout << "not possible" << endl;
            t--;
            continue;
        }

        for(int i=0;i<arestas.size();i++){
            cin >> arestas[i].v >> arestas[i].w >> arestas[i].peso;
        }
        
        
        bool possible = BellmanFord(arestas,0,n);
        
        if(!possible){
            cout << "possible" << endl;
        }

        if(possible){
            cout << "not possible" << endl;
        }

        t--;
    }
                    
    return 0;
}