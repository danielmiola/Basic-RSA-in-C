/**************************************************************
 * UFSCar - Universidade Federal de Sao Carlos. Campus Sorocaba
 **************************************************************
 *
 * Disciplina: Introdução à criptografia
 * Docente: Dra Yeda Regina Venturini
 *
 * Alunos: 
 * 438340 Daniel Ramos Miola
 * 438308 Matheus Casarin Paez
 *
 * Trabalho 2 de Introdução a Criptografia (peso 3)
 * Problema I da Maratona de Programação da SBC 2015
 * RSA
 *************************************************************/

#include <stdio.h>

#define MAX 1000000000

void extended_euclidean_algorithm( long long int a, long long int b, long long int  *gdc, long long int *sf, long long int *tf );

long long int square_and_multiply(long long int x, int buffer[], int tam, long long int n);

int itoa(long long int k, int buffer[]);

int main(){
	
	int primos[100000];
	long long int n, e, c, p, q, totiente, gdc, s, t, res;
	int num, i = 0, j, flag, tam, buffer[33];

	// entrada padrão
	scanf("%lld %lld %lld", &n, &e, &c);

	// gera vetor de numeros primos utilizando a propriedade da raiz
	num = 3;
	while(num*num < MAX){		
		
		int cont;
		if(num%2 == 0)
			num++;

		for(cont=2;cont<num;cont++){
			if(num%cont == 0){
				flag = 0;
				break;
			}else{
				flag = 1;
			}
		}

		if(flag){
			primos[i] = num;
			i++;
		}
		num++;
	}

	int final = i;

	// encontra um primo divisivel e calcula o outro
	for(i = 0; i < final; i++){
		if(n % primos[i] == 0){
			p = primos[i];
			q = n / p;
			break;
		}
	}

	//printf("p = %lld e q = %lld \n", p ,q );
	
	//calcula totiente de n
	totiente = (p-1)*(q-1);

	//calcula a gdc e a chave privada
	if (totiente > e){
		extended_euclidean_algorithm(totiente, e, &gdc, &s, &t);
		if (t < 0)
			t = t + totiente;
	}

	//printf("%lld. inverso multiplicativo (mais conhecido como \"d\"): %lld\n", gdc, t);
	//printf("totiente: %d\n", totiente);

	// transforma o expoente em binário e gera o resultado
	tam = itoa(t, buffer);
	res = square_and_multiply(c, buffer, tam, n);

	printf("%lld\n", res);
	
	return 0;
}


// função do algoritmo extendido de euclides para calcular o gdc e a chave privara(inverso de e)
void extended_euclidean_algorithm( long long int a, long long int b, long long int  *gdc, long long int *sf, long long int *tf ){

	long long int s, old_s, t, old_t, r, old_r, quotient, prov;
	s = 0; old_s = 1;
	t = 1; old_t = 0;
	r = b; old_r = a;

	while(r != 0){
		quotient = old_r / r;

		prov = r;
		r = old_r - prov * quotient;
		old_r = prov;

		prov = s;
		s = old_s - prov * quotient;
		old_s = prov;

		prov = t;
		t = old_t - prov * quotient;
		old_t = prov;		
	}

	*gdc = old_r;
	*sf = old_s;
	*tf = old_t;
}

// função que transforma expoente k em um vetor de bits
int itoa(long long int k, int buffer[]){

	int tam = 0;

	while(k > 0){
		buffer[tam] = k % 2;
		k = k / 2;
		tam++;
	}

	return tam;
}

// função quadrado e multiplica para exponenciacao rapida
long long int square_and_multiply(long long int x, int buffer[], int tam, long long int n){

	long long int result = x;
	int i;

	for(i = tam-2; i >=0; i--){
		result = (result * result) % n;

		if(buffer[i] == 1)
			result = (result * x) % n;
	}

	return result;
}