#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>

//algoritimo fordFulkerson retirado do site abaixo
//http://shygypsy.com/tools/flow.cpp

// the maximum number of vertices
#define NN 101

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
  
int main() { 
    int v;
    std::cin >> v;
    int network = 1;

    while(v!=0){
        
        memset (cap, 0, sizeof (cap)); 

        int origem,destino,arestas;
        std::cin >> origem >> destino >> arestas;

        

        for(int i=0;i<arestas;i++){
            int x,y,peso;
            std::cin >> x >> y >> peso;
            cap[x-1][y-1] += peso;
            cap[y-1][x-1] += peso;
        }

        origem--;
        destino--;

        std::cout << "Network " << network << "\n";
        std::cout << "The bandwidth is " << fordFulkerson(v, origem, destino) << "." << "\n" << "\n"; 

        network++;
        std::cin >> v;
    }

    return 0; 
}