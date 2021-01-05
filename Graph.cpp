#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<deque>
#include<stack>

#define INT_MAX 999999

using namespace std;

struct node{
	int recur;
	int index;
	int visited;
	int dist;//DISTANCIA MINIMA ENTRE A ORIGEM ATE OS PONTOS
	int prev;//ANTERIOR
	vector<int> *custo;
	vector<struct node*> *adj;
};
typedef struct node Node;

struct grafo{
		int m;
		vector<Node*> vertices;
};

typedef struct grafo Grafo;


Grafo* criaGrafo(){

	Grafo *g = (Grafo*) malloc (sizeof(Grafo));
	g->m = 0;

	return g; 

}

int existeNode(Grafo *g, int index){

	for(int i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) return 1;
	}

	return 0;

}

Node* addNode(Grafo *g, int index){

	if(!existeNode(g, index)){
		Node *n = (Node*) malloc(sizeof(Node));
		n->index = index;
		n->recur = 0;
		n->dist = -1;
		n->prev = -1;
		n->visited = 0;
		n->custo = new vector<int>;
		n->adj = new vector<Node*>;
		g->vertices.push_back(n);
		return n;
	}

	return NULL;
	
}



Node* buscaNode(Grafo* g, int index){

	int i = 0;

	for(i = 0; i < g->vertices.size(); i++){
		if(g->vertices[i]->index == index) {
			return g->vertices[i];
		}
	}

	return NULL;

}


void removeNode(Grafo *g, int index){

	int i = 0;

	vector<Node*>::iterator it;

	for(it = g->vertices.begin(); it != g->vertices.end(); it++){
		if((*it)->index == index) {
			g->vertices.erase(it);
			break;
		}
	}
}

void addArcoPonderado(Grafo *g, int i, int j, int custo){
	
	Node *node_i = buscaNode(g, i);
	Node *node_j = buscaNode(g, j);

	if(node_i == NULL){
		node_i = addNode(g, i);
	}
	if(node_j == NULL){
		node_j = addNode(g, j);
	}

	node_i->adj->push_back(node_j);
	node_i->custo->push_back(custo);

	g->m += 1;

}

int getCusto(Grafo *g, int i, int j){
	int k;
	Node *node_i = buscaNode(g,i);
	
	for(k=0; k < node_i->adj->size(); k++){
		if(node_i->adj->at(k)->index == j){
			return node_i->custo->at(k);
		}
	}
	return -1;
}



void addArco(Grafo *g, int i, int j){
	
	Node *node_i = buscaNode(g, i);
	Node *node_j = buscaNode(g, j);

	if(node_i == NULL){
		node_i = addNode(g, i);
	}
	if(node_j == NULL){
		node_j = addNode(g, j);
	}

	node_i->adj->push_back(node_j);

	g->m += 1;

}

void addAresta(Grafo *g, int i, int j){
	
	addArco(g, i, j);
	addArco(g, j, i);

}

vector<Node*>* verticesAdj(Grafo *g, int i){
	
	Node* node = buscaNode(g, i);
	if (node != NULL){
		return node->adj;
	}else{
		return NULL;
	}

}

void imprimirLista(vector<Node*> *lista){

	for(int i = 0; i < lista->size(); i++){
		printf("%d ", lista->at(i)->index);
	}

	printf("\n");

}

void imprimirGrafo(Grafo *g){


	for(int i = 0; i < g->vertices.size(); i++){
		printf("Node %d: ", g->vertices.at(i)->index);
		printf("\n   Adj: ");
		imprimirLista(g->vertices.at(i)->adj);
	}

}

void removeArco(Grafo *g, int i, int j){
	
	Node *node_i = buscaNode(g, i);
	
	vector<Node*>::iterator it;

	for(it = node_i->adj->begin(); it != node_i->adj->end(); it++){

		if((*it)->index == j) {
			node_i->adj->erase(it);
			break;
		}

	}

	g->m -= 1;

}

void removeAresta(Grafo* g, int i, int j){

	removeArco(g, i, j);
	removeArco(g, j, i);

}



int bsf(Grafo *g, int s, int t){ //ONDE S EH O NO INICIAL
	
	deque<Node*> fila;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return -1;
	fila.push_back(aux);//PEGA O ULTIMO ELEMENTO DA FILA
	
	while(!fila.empty()){
		aux = fila.front();//PEGA O PRIMEIRO ELEMENTO DA FILA
		fila.pop_front();
		aux->visited = 1;

		if (aux->index == t)return 1;
		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				fila.push_back(aux->adj->at(i));
			}		
		}		
				
				
			
	}
	return 0;
}

//prufundidade
int dfs(Grafo *g, int s, int t){ //ONDE S EH O NO INICIAL
	
	stack<Node*> stack;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return -1;
	stack.push(aux);
	
	while(!stack.empty()){
		aux = stack.top();
		stack.pop();
		aux->visited = 1;

		if (aux->index == t)return 1;
		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				stack.push(aux->adj->at(i));
			}		
		}		
				
				
			
	}
	return 0;
}
//PROFUNDIDADE - VERSÃO RECURSIVA 
void dfsRec(Grafo* g, int s, int t){
	int i;
	Node *aux = buscaNode(g,s);
	aux->visited = 1;
	if(aux->index != t){
		for(i=0; i < aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				dfsRec(g, aux->adj->at(i)->index, t);
			}
		}
	}
}

//PROFUNDIDADE - VERSÃO RECURSIVA - Aula 
int temCicloUtil(Grafo* g, Node *aux){
	int i;
	
	
	aux->recur = 1; //VERTICE AINDA NAO EXPLOROU TODOS OS FILHOS
	aux->visited = 1;

	for(i=0; i < aux->adj->size(); i++){
		if(aux->adj->at(i)->recur == 1){
			return 1;	
		}else{
			temCicloUtil(g, aux->adj->at(i));
		 }
	}
	aux->recur = 0; //VERTICE EXPLOROU TODOS OS FILHOS
	return 0;
}

int temCiclo(Grafo *g){
	int i;
	//ZERANDO A ESTRUTURA AUXILIAR (QUE VERIFICA SE O VÉRTICE ESTÁ OU NÃO NA RECURSÃO)
	for(i=0; i < g->vertices.size();i++){
		g->vertices.at(i)->recur = 0;
	}	
	//CHAMA A FUNÇÃO PARA VERIFICAR CICLIO A PARTIR DE CADA VÉRTICE DO GRAFO.
	for(i=0; i < g->vertices.size();i++){
		if(temCicloUtil(g, g->vertices.at(i))) return 1;
	}
	return 0;
		
}

void caminhoMinimo(Grafo *g, int s){ //ONDE S EH O NO INICIAL
	
	deque<Node*> fila;
	Node *aux;
	int i;
	
	for(i=0; i < g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
		g->vertices.at(i)->prev = -1;
		g->vertices.at(i)->dist = 0;
	}

	aux = buscaNode(g, s);
	
	if(aux == NULL) return;

	fila.push_back(aux);//PEGA O ULTIMO ELEMENTO DA FILA
	
	while(!fila.empty()){
		aux = fila.front();//PEGA O PRIMEIRO ELEMENTO DA FILA
		fila.pop_front();
		aux->visited = 1;

		//ITERANDO SOBRE OS ADJ E ADICIONANDO NA FILA		
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				aux->adj->at(i)->dist = aux->dist + 1;
				aux->adj->at(i)->prev = aux->prev;
				fila.push_back(aux->adj->at(i));
			}		
		}		
						
	}
}

void posOrdemGrafo(Grafo *g, int s, stack<int> *stack){
//VERTICE S = 0;
	int i;
	Node *aux = buscaNode(g, s);
	aux->visited = 1;
	
	for(i=0; i< aux->adj->size(); i++){
		if(aux->adj->at(i)->visited == 0){
			posOrdemGrafo(g, aux->adj->at(i)->index, stack);
		}
	}
	stack->push(s);	
}

Grafo* transporGrafo(Grafo *g){
	int i, j;
	Grafo *grafoTranposto = new Grafo;
	
	for(i=0; i < g->vertices.size(); i++){
		for(j=0; j < g->vertices.at(i)->adj->size(); j++){
			//CRIA OS VÉRTICES INVERTIDOS
			addArco(grafoTranposto, g->vertices.at(i)->adj->at(j)->index, g->vertices.at(i)->index);
		}
	}
	return grafoTranposto;	

}

void dfsRec2(Grafo* g, int s, vector<int> *vertices){
	int i;
	Node *aux = buscaNode(g,s);
	aux->visited = 1;
	vertices->push_back(s);
	
		for(i=0; i < aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				dfsRec2(g, aux->adj->at(i)->index, vertices);
			}
		}
}



void componentesConexos(Grafo *g, int s){
	
	Grafo *grafoTransposto;
	int indiceNo, i, j;
	Node *nodeAtual;

	vector<vector<int>*> componentesConexos;
	//ORDEM EM QUE EH PRECISO APLICAR A BUSCA EM PROFUNDIDADE
	stack<int> *posOrdemPilha = new stack<int>;
	posOrdemGrafo (g, s, posOrdemPilha);
	
	//CRIA O GRAFO TRANSPOSTO
	grafoTransposto = transporGrafo(g);
	
	while(!posOrdemPilha->empty()){
		indiceNo = posOrdemPilha->top();
		posOrdemPilha->pop();
	
		nodeAtual = buscaNode(grafoTransposto, indiceNo);

		if(nodeAtual->visited == 0){
			vector<int> *vertices = new vector<int>;
			dfsRec2(grafoTransposto, indiceNo, vertices);	
			componentesConexos.push_back(vertices);
		}
	} 	
	for(i=0; i<componentesConexos.size(); i++){
		printf("Componente %d: \n", i);
		for(j=0; j<componentesConexos.at(i)->size(); j++){
			printf(" %d", componentesConexos.at(i)->at(j));
		}
		printf("\n");
	}
}

void ordenacaoTopologicaUtil(Grafo *g, Node *aux, stack<int> *pilha){

	int i;

	if(aux->visited == 0){
		aux->visited = 1;	
		for(i=0; i< aux->adj->size(); i++){
			if(aux->adj->at(i)->visited == 0){
				ordenacaoTopologicaUtil(g, aux->adj->at(i), pilha);
			}
		}
		pilha->push(aux->index);	
	}
}

void ordenacaoTopologica(Grafo *g){
	
	int i;
	stack<int> *pilha = new stack<int>;

	//ZERA A ESTRUTURA
	for(i=0; i<g->vertices.size(); i++){
		g->vertices.at(i)->visited = 0;
	}
	//CHAMA A FUNCAO PARA TODOS OS VERTICES DO GRAFO
	for(i=0; i< g->vertices.size(); i++){
		ordenacaoTopologicaUtil(g, g->vertices.at(i), pilha);
	}
	while(!pilha->empty()){
		printf("%d \n", pilha->top());
		pilha->pop();
	}
}

Node* obterMenorEstimativaDistancia(vector<Node*> *verticesNaoVisitados){

	int i;
	int menorDist = INT_MAX;
	Node *menorNode;
	vector<Node*>::iterator it;

	//OBTENHO A MENOR ESTIMATIVA DE DISTANCIA ENTRE OS NÓS NAO VISITADOS
	for(i=0; i < verticesNaoVisitados->size(); i++){
		if(verticesNaoVisitados->at(i)->dist < menorDist){	
			menorDist = verticesNaoVisitados->at(i)->dist;
			menorNode = verticesNaoVisitados->at(i);
		}
	}
	for(it = verticesNaoVisitados->begin(); it != verticesNaoVisitados->end(); it++){
		if((*it)->dist == menorDist){
			verticesNaoVisitados->erase(it);
			break;
		}
	}
	return menorNode;
}

void dijkstra(Grafo *g, int s){
	int i;
	Node *noAtual;
	Node *noAdj;
	//LISTA CONTENDO TODOS OS VERTICES DO GRAFO
	vector<Node*> *verticesNaoVisitados = new vector<Node*>;
	
	//INICIALIZAÇÃO DE ACORDO COM O ALGORITMO
	for(i=0; i < g->vertices.size(); i++){
		if(g->vertices.at(i)->index == s){
			g->vertices.at(i)->dist = 0;
		}else{
				g->vertices.at(i)->dist = INT_MAX;
		}
		g->vertices.at(i)->prev = -1;

		verticesNaoVisitados->push_back(g->vertices.at(i));
	}
	//ENQUANTO A LISTA DE VÉRTICES NAO VISITADOS NAO FOR VAZIA
	while(!verticesNaoVisitados->empty()){
		//OBTENHO O MENOR
		noAtual = obterMenorEstimativaDistancia(verticesNaoVisitados);
		noAtual->visited = 1;

		//ATUALIZA A ESTIMATIVA DE DISTANCIA PARA TODOS OS ADJ
		for (i=0; i < noAtual->adj->size(); i++){

			noAdj = noAtual->adj->at(i);
			
			if(noAdj->dist > noAtual->dist
											+ getCusto(g, noAtual->index, noAdj->index)){
				noAdj->dist = noAtual->dist
											+ getCusto(g, noAtual->index, noAdj->index);
				
				noAdj->prev = noAtual->index;
			}
		}
	}
}		

int main(){
	
	Grafo *g = new Grafo();
	addArcoPonderado(g, 0, 1, 1);
	addArcoPonderado(g, 1, 2, 1);
	addArcoPonderado(g, 2, 0, 1);
	addArcoPonderado(g, 2, 3, 1);
	addArcoPonderado(g, 3, 4, 1);

	dijkstra(g, 0);
	printf("%d \n", buscaNode(g,4)->dist);
	//ordenacaoTopologica(g);	
	
}
