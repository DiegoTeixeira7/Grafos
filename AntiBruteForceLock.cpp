#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

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

//Função para calcular a menor distância de rolagem de uma chave i, para chegar o uma chave j

int distancias(string i,string j){
	int vetori[4];
	char a[1];
	
	//inicialmente converte cada uma das chaves em int e salva num vetor

	a[0] = i[3];
	vetori[3] = atoi(a);
	a[0] = i[2];
	vetori[2] = atoi(a);
	a[0] = i[1];
	vetori[1] = atoi(a);
	a[0] = i[0];
	vetori[0] = atoi(a);

	int vetorj[4];
	a[0] = j[3];
	vetorj[3] = atoi(a);
	a[0] = j[2];
	vetorj[2] = atoi(a);
	a[0] = j[1];
	vetorj[1] = atoi(a);
	a[0] = j[0];
	vetorj[0] = atoi(a);

	int m1=0,m2=0;
	int dis = 0;

	//temos dois casos para fazer esse calculo, pois do 9 o numero pode ir para o 0 e vice versa
	//logo temos q contar a distancia de dois numeros roalndo em sentido horario e setntido anti-horario.
	//a menr distancia é que vamos usar

	for(int k=0;k<4;k++){
		m1 = m2 = 0;
		
		//sentido horario
		m1 = abs(vetori[k] - vetorj[k]);

		//sentido anti-horario
		//para esse caso, transformo todos numeros para 0 e somo a qtd de rolagem
		//o unicos casos q isso vale a pena é para 9,8,7,6

		if(vetori[k] == 9){
			vetori[k] = 0;
			m2++;
		}

		else if(vetori[k] == 8){
			vetori[k] = 0;
			m2+=2;
		}

		else if(vetori[k] == 7){
			vetori[k] = 0;
			m2+=3;
		}

		else if(vetori[k] == 6){
			vetori[k] = 0;
			m2+=4;
		}

		if(vetorj[k] == 9){
			vetorj[k] = 0;
			m2++;
		}

		else if(vetorj[k] == 8){
			vetorj[k] = 0;
			m2+=2;
		}

		else if(vetorj[k] == 7){
			vetorj[k] = 0;
			m2+=3;
		}

		else if(vetorj[k] == 6){
			vetorj[k] = 0;
			m2+=4;
		}

		//descubro a distancia do sentido anti-horario
		m2 = m2 + abs(vetori[k] - vetorj[k]);

		//distancia vira a distancia atual mais o min das duas distancias calculadas,
		//já que queremos a menor
		dis = dis +  min(m1,m2);
	}


	return dis;
}


int main(){

	int t;
	cin >> t;

	while(t > 0){
		int n;
		cin >>n;

		//caso tenha 0 chaves, não tem distancia
		if(n==0){
			t--;
			cout << 0 << endl;
			continue;
		}

		//variavel para verificar se 0 é uma chave
		bool zero = false;

		vector<string> vertices(n);

		for(int i=0;i<n;i++){
			cin >> vertices[i];
			if(vertices[i] == "0000"){
				zero = true;
			}
		}

		//se 0 não for cahave , vamos adcioná-lo temporiamente 
		if(zero == false)
			vertices.push_back("0000");


		vector<Aresta> arestas;
		
		//como os vértices tem q ser de 0 a nVertices - 1, criaemos um map
		//para podermos fazer isso
		map<int,int> myMap;

		char *a1 = new char[4];
		char *a2 = new char[4];

		int num,num2;

		//se o numeros de chaves for 1, verificamos a distancia da chave a 0000 
		//e retornamos a distancia apenas

		if(n == 1){

			string z = "0000";

			int d = distancias(vertices[0],z);
			cout << d << endl;
			
			t--;
			
			continue;
		}
		
		vector<int> pesos;

		//nesse momento adicionaremos as Arestas do grafo
		//Se 0 for uma chave, adcionaremos ele normalmente,
		//se 0 não for chave , só vamos começar da aresta de meor peso 
		//que liga 0 e excluiremos o vértice 0

		for(int i=0;i<vertices.size();i++){
			for(int j=0;j<vertices.size();j++){
				a1[0] = vertices[i][0];
				a1[1] = vertices[i][1];
				a1[2] = vertices[i][2];
				a1[3] = vertices[i][3];
				
				a2[0] = vertices[j][0];
				a2[1] = vertices[j][1];
				a2[2] = vertices[j][2];
				a2[3] = vertices[j][3];

				num = atoi(a1);
				num2 = atoi(a2);
				
				//00000 não é chave, logo so pegamos os pesos das arestas q o liga
				if((i!=j) && (zero == false ) && ((num == 0) || (num2 == 0))){
					pesos.push_back(distancias(vertices[i],vertices[j]));
				}

				else if((i!=j)){
					arestas.push_back(Aresta(num,num2,distancias(vertices[i],vertices[j])));
				}
			}
			//fazemos  o map para cada vértice
			myMap[num] = i;
			
			
		}

		delete []a1;
		delete []a2;

	
		//pegamos o peso da aresta com o menor ccusto de 0000. Caso 0000 for chave,
		//d é 0

		int d = 0;
		if(zero == false)
			d = pesos[0];

		
		for(int i=1;i<pesos.size();i++)
			d = min(d,pesos[i]);
			
		//trocamos o nome de cada vértice pelo seu código no map
		//Ex: vértce 1155 tem código 1 no map, logo aresta[1].v = 1
		for(int i=0;i<arestas.size();i++){
			arestas[i].v = myMap[arestas[i].v];
			arestas[i].w = myMap[arestas[i].w];
		}

		//chama o algoritimo de prim para achar a AGM
		vector<bool> arestasUtilizadas;
		Prim(arestas, arestasUtilizadas,vertices.size());
		
		//soma o custo de todas as arestas utiliadas ns AGM
		for(int i=0;i<arestasUtilizadas.size();i++){
			if(arestasUtilizadas[i]){
				d = d + arestas[i].peso;
			}
		}
		
		cout << d << endl;
		
		t--;
	}
	
    return 0;
}