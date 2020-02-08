#include <iostream>
#include <vector>
using namespace std;

const int vertice(const char letra){
    if(letra == 'A') return 0;
    if(letra == 'B') return 1;
    if(letra == 'C') return 2;
    if(letra == 'D') return 3;
    if(letra == 'E') return 4;
    if(letra == 'F') return 5;
    if(letra == 'G') return 6;
    if(letra == 'H') return 7;
    if(letra == 'I') return 8;
    if(letra == 'J') return 9;
    if(letra == 'K') return 10;
    if(letra == 'L') return 11;
    if(letra == 'M') return 12;
    if(letra == 'N') return 13;
    if(letra == 'O') return 14;
    if(letra == 'P') return 15;
    if(letra == 'Q') return 16;
    if(letra == 'R') return 17;
    if(letra == 'S') return 18;
    if(letra == 'T') return 19;
    if(letra == 'U') return 20;
    if(letra == 'V') return 21;
    if(letra == 'W') return 22;
    if(letra == 'X') return 23;
    if(letra == 'Y') return 24;
    if(letra == 'Z') return 25;
}

int main(){
    int n;
    cin >> n;
    bool passo = false;

    for(int i=0;i<n;i++){
       // cout << "Entrei 1" << endl;
        string c;
        char letra;
        vector<vector<int> > adj(26,vector<int>(26));
        
        int qtdArestas = 0;
        int pos1,pos2;

        vector<int> letras(26);
        if(passo == true){
            passo = false;
            c = '0';
        }

        while(c[0]!='*'){
            //cout << "Entrei 2" << endl;
            cin>>c;
            if(c[0]=='*'){
                break;
            }

            //cout << "Entrei 3" << endl;
        
            letra = c[1];
            pos1 = vertice(letra);
            if(letras[pos1] == 0 )
                letras[pos1]++;
            
            letra = c[3];
            pos2 = vertice(letra);
            if(letras[pos2] == 0 )
                letras[pos2]++;
            
            adj[pos1][pos2]++;
            adj[pos2][pos1]++;
            qtdArestas++;

        }

        string v;
        cin >> v;
        int qtdVertices = 0;
        vector<int> vertices(26);

        for(int j=0;j<v.length();j++){
            letra=v[2*j];
            vertices[vertice(letra)]++;
            qtdVertices++;
            if(2*j == (v.length() - 1 ))
                break;
            
        }

        // cout << "Vertices: " << endl;
        // for(int i=0;i<26;i++){
        //     cout<<vertices[i] << " ";
        // }
        // cout << endl;
        
        // cout << "letras: " << endl;
        // for(int i=0;i<26;i++){
        //     cout<<letras[i] << " ";
        // }
        //cout << endl;
        
        // cout << "adj " << endl;
        // for(int i=0;i<26;i++){
        //     for(int j=0;j<26;j++){
        //         cout<<adj[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        int componentes = qtdVertices - qtdArestas;
        //cout << componentes << endl;

        int trivial = 0;
        
        for(int i=0;i<26;i++){
            if(vertices[i] == 1 && letras[i] == 0)
                trivial++;
        }

        componentes = componentes - trivial;
        //cout << componentes << endl;
        //cout << trivial << endl;
        passo = true;

        cout << "There are " << componentes << " tree(s) and " << trivial << " acorn(s)." << endl;

    }

    return 0;
}