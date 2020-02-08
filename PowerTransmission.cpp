#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>

//algoritimo fordFulkerson retirado do site abaixo
//http://shygypsy.com/tools/flow.cpp

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, prev[NN];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof( prev ) );
        qf = qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prev[q[qb++] = v] = u;

        // see if we're done
        if( prev[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            bot = std::min(bot,(cap[u][v] - fnet[u][v] + fnet[v][u]));

        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    //a <? = B;" para "a = min (a, b);". O mesmo para>? = E max ().

    return flow;
}

//existem n+2 vertices, como não funciona fazer vertice cap[i][i] = peso
//temos q duplicar a quantidade de vértices

int main(){
    int n;

    while(std::cin >> n){

        if(n == EOF)
            break;

        memset (cap, 0, sizeof (cap));
        
        int n2 = n+2;

        cap[0][n2] = 4000000; //liga os dois barisal
        cap[n2-1][(2*n2)-1] = 4000000; //liga as duas dhaka
    
        for(int i=1;i<=n;i++){
            std::cin >> cap[i][i+n2]; //rede 1, liga rede 2
        }

        int m;
        std::cin >> m;

        int x,y,peso;
        for(int i=0;i<m;i++){
            std::cin >> x >> y >> peso;
            cap[x+n2][y] += peso;  //rede 2, liga rede 1
        }

        int b,d;
        std::cin >> b >> d;

        int c;
        for(int i=0;i<b;i++){
            std::cin >> c;
            cap[n2][c] = 4000000; //brarisal 2, liga rede 1
        }
        
        int dhaka = 2*n2-1;
    
        for(int i=0;i<d;i++){
            std::cin >> c;
            cap[c+n2][n2-1] = 4000000; //rede 2, liga dhaka 1
        }

        std::cout << fordFulkerson(2*n2, 0, dhaka) << "\n";
    }

    return 0;
}