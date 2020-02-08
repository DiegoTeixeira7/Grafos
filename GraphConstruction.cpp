#include <iostream>
#include <vector>

using namespace std;

void quick(int vet[], int esq, int dir){
    int pivo = esq, i,ch,j;         
    for(i=esq+1;i<=dir;i++){        
        j = i;                      
        if(vet[j] < vet[pivo]){     
            ch = vet[j];               
            while(j > pivo){           
                vet[j] = vet[j-1];      
                j--;                    
            }
            vet[j] = ch;               
            pivo++;                    
        }
    }
    if(pivo-1 >= esq){              
        quick(vet,esq,pivo-1);      
    }
    if(pivo+1 <= dir){              
        quick(vet,pivo+1,dir);      
    }
 }


int main(){
    int n;
    cin>>n;

    while(n != 0){
        int sequencia[n];
        int soma = 0;
        
        for(int i=0;i<n;i++){
            cin>>sequencia[i];
            soma += sequencia[i];
            sequencia[i] = sequencia[i] * (-1);
        }

        quick(sequencia,0,n);
        vector <int> sequencia2(n+1);

        for(int k=0;k<n;k++){
            sequencia[k] = sequencia[k] * (-1);
            sequencia2[k+1] = sequencia[k];
        }

        // for(int k=0;k<n;k++){
        //     cout <<  sequencia[k] <<  " ";
        // }
        // cout << endl;

        // for(int k=0;k<=n;k++){
        //     cout <<  sequencia2[k] <<  " ";
        // }
        // cout << endl;

        bool seq = false;
        int formula = 0;
        int s = 0;
        int d = 0;
        
        for(int k=1;k<=n;k++){
            formula = k * (k-1);
            s = d = 0;
            
            for(int j=k+1;j<=n;j++){
                s += min(sequencia2[j],k);
            }

            for(int i=1;i<=k;i++){
                d += sequencia2[i];
                //cout << "k: " << k << endl;
            }
            
           if(d > (formula + s)){
                seq = true;
                break;
           }
        }


        if(seq == true || soma % 2 != 0 ){
            cout << "Not possible" << endl;
        }
        else{
            cout << "Possible" << endl;
        }


        cin>> n;
    }

    return 0;
}