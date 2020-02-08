#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void adj(int l,int c,char carac,vector<vector<char> > &m,int rows,int cols) {
	if (l<0 || c<0 || c>=cols || l>=rows || m[l][c]!=carac ) 
		return;
	
	m[l][c] = '#';
    
	adj(l-1,c,carac,m,rows,cols);
	adj(l+1,c,carac,m,rows,cols);
	adj(l,c-1,carac,m,rows,cols);
	adj(l,c+1,carac,m,rows,cols);
}

int main(){
    int n;
    cin>>n;
    int world = 0;

    for(int i=0;i<n;i++){
        int linhas,colunas;
        cin>>linhas>>colunas;
       
        vector<vector<char> > letras(linhas,vector<char>(colunas));

        for(int j=0;j<linhas;j++){
            for(int k=0;k<colunas;k++){
                cin >> letras[j][k];
            }
        }


        char letra;
        vector<pair<char,int> > pares;
        bool tem = false;

        for(int j=0;j<linhas;j++){
            for(int k=0;k<colunas;k++){
                if(letras[j][k]!='#'){
                    letra = letras[j][k];
                    
                    adj(j,k,letra,letras,linhas,colunas);
                    for(int m=0;m<pares.size();m++){
                        if(letra == pares[m].first){
                            pares[m].second += 1;
                            tem = true;
                        }
                    }
                    
                    if(tem == false)
                        pares.push_back(make_pair(letra,1));
                    tem = false;
                }
            }
        }

        int maior = 0;
        char l;
        int pos;
        
        world++;
        cout << "World #" << world << endl;
       
        while(pares.size()>0){
            maior = 0;
            for(int k=0;k<pares.size();k++){
                if(pares[k].second>maior){
                    maior = pares[k].second;
                    l = pares[k].first;
                    pos = k;
                }

                else if((pares[k].second == maior) && (pares[k].first < l)){
                    maior = pares[k].second;
                    l = pares[k].first;
                    pos = k;
                }
            }
            
            
            cout << l << ": " <<  maior << endl;
            
            swap(pares[pos],pares[pares.size()-1]);
            pares.pop_back();
        }
    }

    return 0;
}