#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>

//algoritimo fordFulkerson retirado do site abaixo
//http://shygypsy.com/tools/flow.cpp

// the maximum number of vertices
#define NN 40

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

int vertice(std::string &str){
    if(str == "L")   return 1;
    if(str == "M")   return 2;
    if(str == "S")   return 3;
    if(str == "XS")  return 4;
    if(str == "XL")  return 5;
    if(str == "XXL") return 6;
}

int main(){
    int t;
    std::cin >> t;

    while(t>0){

        int qtdCamisas,qtdPessoas;
        std::cin >> qtdCamisas >> qtdPessoas;

        memset (cap, 0, sizeof (cap));

        std::string tamanho1,tamanho2;
        int u,v;
        int j = 7;

        //S é o vértice 0, os vértices de 1 a 6 são as camisas
        //os proximos vertices são os voluntarios e o último vértice é T

        for(int i=0;i<qtdPessoas;i++){
            std::cin >> tamanho1 >> tamanho2;
            u = vertice(tamanho1);
            v = vertice(tamanho2);

            cap[j][u] = cap[u][j] = 1;
            cap[j][v] = cap[v][j] = 1;

            cap[0][j] = cap[j][0] = 1;

            j++;
        }

        for(int i=1;i<7;i++){
            cap[i][j] = cap[j][i] = (qtdCamisas/6);
        }

        int result = fordFulkerson(j+1, 0, j);

        if(result >= qtdPessoas)
            std::cout << "YES" << "\n";
        else
            std::cout << "NO" << "\n";
        
        t--;
    }

    return 0;
}