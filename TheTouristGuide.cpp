#include <iostream>
#include <vector>

using namespace std;

void floyd_warshall(vector<vector<int> > &dist,int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = max(dist[i][j],min(dist[i][k],dist[k][j]));
}

int main(){
    int n,r;
    int cenario = 1;
    cin >> n >> r;

    while(n!=0 || r!=0){
        if(n < 2){
            cout << "Scenario #"<< cenario << "\n";
            cout << "Minimum Number of Trips = " << 0 << "\n" << "\n";
            cenario++;
            
            cin >> n >> r;
            continue;

        }

        vector<vector<int> >dist(n,vector<int>(n));

        int x,y;

        for(int i=0;i<r;i++){
            cin >> x >> y >> dist[x-1][y-1]; 
            dist[x-1][y-1]--;
            dist[y-1][x-1] = dist[x-1][y-1];
        }

        floyd_warshall(dist,dist.size());

        int origem,destino,qtdPessoas;
        cin >> origem >> destino >> qtdPessoas;

        int NumPessoas = dist[origem-1][destino-1];
        int passageiros = 0;
        int numViagem = 0;

        if(NumPessoas == 0){
            cout << "Scenario #"<< cenario << "\n";
            cout << "Minimum Number of Trips = " << 0 << "\n" << "\n";
            cenario++;
            
            cin >> n >> r;
            continue;
        }

        while(passageiros < qtdPessoas){
            numViagem++;
            passageiros += NumPessoas;
        }   

        cout << "Scenario #"<< cenario << "\n";
        cout << "Minimum Number of Trips = " << numViagem << "\n" << "\n";

        cenario++;
        
        cin >> n >> r;
    }

    return 0;
}