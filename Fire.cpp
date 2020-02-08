#include <iostream>
#include <vector>
using namespace std;

void espalhaF(int lF,int cF,char carac, vector<vector<char> > &m,int rows,int cols,vector<pair<int,int> > &firesAux) {
	if (lF<0 || cF<0 || cF>=cols || lF>=rows || m[lF][cF]!=carac ) 
		return;
	
    firesAux.resize(firesAux.size()+1);
    firesAux[firesAux.size()-1].first = lF;
    firesAux[firesAux.size()-1].second = cF;

    m[lF][cF] = 'F';
	
}

void espalhaJ(int l,int c,char carac, vector<vector<char> > &m,int rows,int cols,bool &saiu,vector<pair<int,int> > &JoeAux) {
	if (l<0 || c<0 || c>=cols || l>=rows || m[l][c]!=carac ) 
		return;

    JoeAux.resize(JoeAux.size()+1);
    JoeAux[JoeAux.size()-1].first = l;
    JoeAux[JoeAux.size()-1].second = c;
	 
    m[l][c] = 'J';
	
    if(l==0 || c==0 || l == (rows-1) || c == (cols -1))
        saiu = true;
}


int main(){
    int t;
    cin >> t;

    while(t>0){
        int rows,cols;
        cin >> rows >> cols;

        vector<vector<char> > labirinto(rows,vector<char>(cols));

        vector<pair<int,int> > fires;
        vector<pair<int,int> > firesAux;
        vector<pair<int,int> > Joe;
        vector<pair<int,int> > JoeAux;
        
        int tam = 0;
        int tam2 = 0;

        bool JoeSaida = false;

        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                cin >> labirinto[i][j];
                if(labirinto[i][j] == 'F'){
                    fires.resize(tam+1);
                    fires[tam].first = i;
                    fires[tam].second = j;
                    tam++;
                }

                else if(labirinto[i][j] == 'J'){
                    if(i == 0 || j == 0 || i == (rows-1) || j == (cols-1) ){
                        cout << 1 << endl;
                        JoeSaida = true;
                    }


                    Joe.resize(tam2+1);
                    Joe[tam2].first = i;
                    Joe[tam2].second = j;
                    tam2++;
                }
            }
        }

        if(JoeSaida == false){
           
            bool saiu = false;
            bool vezJoe = false;
            int distancia = 1;


            for(int i=0;i<rows;i++){
                for(int j=0;j<cols;j++){
                    if(vezJoe == false){
                        for(int k=0;k<fires.size();k++){
                            espalhaF(fires[k].first,fires[k].second,'.',labirinto,rows,cols,firesAux);
                            espalhaF(fires[k].first-1,fires[k].second,'.',labirinto,rows,cols,firesAux);
                            espalhaF(fires[k].first+1,fires[k].second,'.',labirinto,rows,cols,firesAux);
                            espalhaF(fires[k].first,fires[k].second-1,'.',labirinto,rows,cols,firesAux);
                            espalhaF(fires[k].first,fires[k].second+1,'.',labirinto,rows,cols,firesAux);

                        }


                        fires = firesAux;
                        firesAux.resize(0);
                        vezJoe = true;
                    }

                    for(int k=0;k<Joe.size();k++){

                        espalhaJ(Joe[k].first,Joe[k].second,'.',labirinto,rows,cols,saiu,JoeAux);
                        espalhaJ(Joe[k].first-1,Joe[k].second,'.',labirinto,rows,cols,saiu,JoeAux);
                        espalhaJ(Joe[k].first+1,Joe[k].second,'.',labirinto,rows,cols,saiu,JoeAux);
                        espalhaJ(Joe[k].first,Joe[k].second-1,'.',labirinto,rows,cols,saiu,JoeAux);
                        espalhaJ(Joe[k].first,Joe[k].second+1,'.',labirinto,rows,cols,saiu,JoeAux);

                        

                        if(saiu){
                            distancia++;
                            cout << distancia << endl;
                            break;
                        }
                    }

                    distancia++;

                    vezJoe = false;
                    Joe = JoeAux;
                    JoeAux.resize(0);

                    if(saiu)
                        break;


                }
                if(saiu)
                    break;
            }
         
            if(saiu == false)
                cout << "IMPOSSIBLE" << endl;

        }

        t--;
    }

    return 0;
}