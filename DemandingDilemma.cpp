#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){

    int t;
    cin >> t;

    int n,m;


    for(int i=0;i<t;i++){
        cin>>n>>m;
        vector<vector<bool> > g(n);
        for(int j=0;j<n;j++){
            g[j].resize(m);
            for(int k=0;k<m;k++){
                bool adj;
                cin >> adj;
                g[j][k] = adj;
            }
        }
        
        
        int contador = 0;
        bool nao = false;
        for(int j=0;j<m;j++){
            for(int k=0;k<n;k++){

                if(g[k][j] == true){
                    contador++;
                }

            }

            if (contador != 2){
                cout << "No" << endl;
                nao = true;
                break;
            }
            contador = 0;
        }

        vector<pair<int,int> > pares;
        int pos1 = -1;
        int pos2 = -1;
        bool recebeu = false;

        for(int j=0;j<m;j++){
            recebeu = false;
            pos1 = pos2 = -1;
            for(int k=0;k<n;k++){
                if(g[k][j] == true && recebeu == false){
                    pos1 = k;
                    recebeu = true;
                }
                if(g[k][j] == true && recebeu == true){
                    pos2 = k;
                }
            }
            
            pares.push_back(make_pair(pos1,pos2));
            
        }
        bool verifica = false;

        for(int j=0;j<pares.size();j++){
            for(int k=j+1;k<pares.size();k++){
                if(pares[j].first == pares[k].first && pares[j].second == pares[k].second){
                    verifica = true;
                    break;
                }
            }
            if(verifica)
                break;
        }

        if(nao == false && verifica == true){
            cout << "No" << endl;
            
        }
       
        if(nao == false && verifica == false)
            cout << "Yes" << endl;
        nao = false;
        verifica = false;
    }

    return 0;
}