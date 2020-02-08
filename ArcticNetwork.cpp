#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <iomanip>


using namespace std;

//Struct para salvar a aresta que liga v a w e seu peso

struct Aresta {
	int v, w;
	double peso;
	Aresta(int v = -1, int w = -1,double peso = 0) : v(v), w(w), peso(peso) { }
};

//operador para comparar pesos de duas arestas
bool operator <(const Aresta &i,const Aresta &j) {
	return i.peso<j.peso;
}

//classe para armazenar conjuntos
class UnionFind {
	private:
		vector<int> raiz;
	public:
        //cria um conjunto(1 elemento para cada conjunto)
        //e faz esse elemento ser o representante do seu conjunto
		void criaConjunto(int nVertices) {
			raiz.resize(nVertices);
			for(int i=0;i<nVertices;i++)
				raiz[i] = i;
		}
		
        //procura quem é o representante do elemento, com isso saberemos 
        //a qual conjunto ele pertence
		int EncontraConjunto(int elemento) {
			if (raiz[elemento]==elemento) 
				return elemento;
			
            raiz[elemento] = EncontraConjunto(raiz[elemento]);
			
            return raiz[elemento];
		}
        //faz o representante do conjunto i ser o representante
        //do conjunto j, com isso junta os conjuntos
		void JuntaConjunto(int i,int j) {
			raiz[ EncontraConjunto(i) ] = EncontraConjunto(j);
		}
		
        //verifica se i e j tem o mesmo representante
        //se sim, estão no mesmo conjunto
        bool VerificaConjunto(int i,int j) {
			return (EncontraConjunto(i)==EncontraConjunto(j));
		}

};


int Prim(vector<Aresta> &arestas, vector<bool> &arestasUtilizadas,int numVerticesGrafo) {
    //inicialmente não usu nenuma aresta, logo todas as posições sao false
	arestasUtilizadas = vector<bool>(arestas.size(),false); 
    //ordena Aresta com base no peso
	sort(arestas.begin(),arestas.end());

    //cria um conjunto para cada vertice
	UnionFind conjuntos;
	conjuntos.criaConjunto(numVerticesGrafo);

    //Como o algoritimo de prim só podemos adicionar arestas que ligam vétices descobetos,
    //cria um vetor para cada vertice e faz ser true os vértices pa primeira posição de Aresta,
    //já que a primeira posição contém a areta de menor peso.
    // A partir daí, o algoritimo olha as arestas dos vértices já descobertos e adiciona a de 
    //menor peso
    vector<bool> VertcicesUtilizados(arestas.size(),false);
    VertcicesUtilizados[arestas[0].v] = true;
    VertcicesUtilizados[arestas[0].w] = true;
	
	int tamArvore = numVerticesGrafo-1;
	int qtdArestas = 0;
	for(int i=0;i<arestas.size();i++) {
        //so adiciona aresta se ela não estiver no conjunto e se algum vértice dessa aresta já foi descoberto
        if (!conjuntos.VerificaConjunto( arestas[i].v, arestas[i].w ) && (VertcicesUtilizados[arestas[i].v]
                                                                      || VertcicesUtilizados[arestas[i].w])) {
        
			arestasUtilizadas[i] = true;
            qtdArestas++;

            //como adicionou, os vértices foram descobertos
            VertcicesUtilizados[arestas[i].v] = true;
            VertcicesUtilizados[arestas[i].w] = true;

            if (qtdArestas==tamArvore)
                return qtdArestas;
        

            conjuntos.JuntaConjunto(arestas[i].v, arestas[i].w );

            //temos q voltar com i toda vez porque podemos deixar algum vértice sem ser adicionado,
            //quando todos forem adicionados o prgrama acaba pois não entra no if
            i = 0;
        }
    }
	return qtdArestas;
}

//distancia de dois pontos
double distancia(pair<double,double> &c1 , pair<double,double> &c2){
    return sqrt((pow((c2.first-c1.first),2) + pow((c2.second-c1.second),2)));
}

int main(){
    int t;
    cin >>t;

    while(t >0){
        int s,p;
        cin >> s >> p;

        //incialmente, adiciona cada cordenada em um vector de pair
        //cada posição de pair será o vértice, e a distancia de cada pair a cada pair
        //será o peso
        vector<Aresta> arestas;
        vector<pair<double,double> > coordenadas(p);

        for(int i=0;i<p;i++){
            cin >> coordenadas[i].first >> coordenadas[i].second;
        }

        for(int i=0;i<p;i++){
            for(int j=0;j<p;j++){
                //impede de adcionar dois vértices iguais
                if((i!=j)){
                    arestas.push_back(Aresta(i,j,distancia(coordenadas[i],coordenadas[j])));
                }
            
            }   
        }

        //chama o algorítimo de prim para achar AGM
        vector<bool> arestasUtilizadas;
		Prim(arestas, arestasUtilizadas,arestas.size());

        //se tiver um satélite, não poderemos reduzir o número de arestas,
        //mais se tiver mais de um satélite a quantidade de arestas será 
        //(postos - 1) - (satélites- 1). A cada par de satélites, reduz 
        //uma aresta

        int qtdA = 0;
		if (s <= 1)
			qtdA = (p-1);
		else
			qtdA = (p-1) - (s-1);
        
        double distancia = 0;
        int c = 0;

        //como o vetor aresta está ordenado, a maior aresta está no fim
        //enquanto c for menor que qtdA podemos procurar, pois qtdA é máximo de arestas 
        //que serão utiliazdas. Pegamos o maior pois precisamos do maior valor de D

        for(int i=0;i<arestas.size();i++) {
            if(c < qtdA){
                if (arestasUtilizadas[i] == true) {
                    c++;				
                    distancia = max(distancia,arestas[i].peso);
                }
            }
		}

        cout << fixed << setprecision(2) << distancia << endl;

        t--;
    }

    return 0;
}