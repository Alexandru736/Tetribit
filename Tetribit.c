//Nume si prenume: Ionita Alexandru
//Grupa: 312CB

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
 
int numar_linii = 0;

void print_harta(uint64_t n); //printeaza harta
uint64_t transf(uint64_t m, int n); // realizeaza transformarea piesei
int coliziune(uint64_t n, uint64_t m);// verifica coliziunea cu o alta entitate
float calcul_scor(uint64_t n, double numar_linii);// calculeaza scorul final
uint64_t eliminare_linii(uint64_t piesa, uint64_t harta, int i);
int verificare_finala(uint64_t piesa, uint64_t harta, int i);//game-over
uint64_t mutare(uint64_t n, uint64_t m, int x,int i);//harta in care s-a facut 
//mutarea
uint64_t mutarepiesa(uint64_t piesa, int transf,int j);//mutarea piesei in  
//paralel cand harta are valoarea 0 urmand ca rezulatul sa fie implicat in 
//conditia de coliziune 
int margini(uint64_t piesa, int transf, int j);//coliziunea cu marginile hartii

int main(){
	uint64_t harta;// codificarea hartii initiale in decimal
	uint64_t harta1;// harta care se va actualiza pe parcurs
	int mutari; //numarul de mutari
	int i,j; // contori ai matricei matrice_mutari[][]
	
	scanf("%lu%d", &harta, &mutari);
	
	harta1 = harta;
	
	int matrice_mutari[mutari][8]; // matricea care memoreaza piesele si
	//transformarile
	uint64_t vector_piese[mutari];
	
	for(i = 0; i < mutari; i++){
		scanf("%lu", &vector_piese[i]);
		for(j = 0; j < 8; j++)
		    scanf("%d", &matrice_mutari[i][j]); 
		}
	if(mutari == 0){
		print_harta(harta);
		
		calcul_scor(harta, 0);
	}
	else{
	print_harta(harta);
	for(i = 0; i < mutari; i++){
		harta = harta1;
		short ok = 1;
		for(j = 1; j <= 8 && ok == 1; j++){
		uint64_t x = mutarepiesa(vector_piese[i], matrice_mutari[i][j-1], j);
		uint64_t y = mutare(vector_piese[i],harta, matrice_mutari[i][j-1], j);
		uint64_t z = transf(vector_piese[i], matrice_mutari[i][j-1]);
		uint64_t t = margini(vector_piese[i], matrice_mutari[i][j-1], j);
	 	 	if(coliziune(harta, x) == 0){
				if(t == 0){	
			 		print_harta(y);
					if(matrice_mutari[i][j-1] != 0)
			    		vector_piese[i] = z;
					harta1 = y;
							
				}
				else{
					if(matrice_mutari[i][j-1] < 0){
						matrice_mutari[i][j-1] = t;						
						print_harta(mutare(vector_piese[i], harta, t, j));
						if(matrice_mutari[i][j-1] != 0)
			    			vector_piese[i] = transf(vector_piese[i], t);
						harta1 = mutare(vector_piese[i], harta, t, j);
					}
					else if(matrice_mutari[i][j-1] > 0){
						matrice_mutari[i][j-1] = t;
						print_harta(mutare(vector_piese[i], harta, t-1, j));
						if(matrice_mutari[i][j-1] != 0)
			    			vector_piese[i] = transf(vector_piese[i], t-1);
						harta1 = mutare(vector_piese[i], harta, t-1, j);
					}
				}
			}
			else if((coliziune(harta, x) != 0) && (coliziune(harta,
mutarepiesa(vector_piese[i], 0, j) ) == 0)){
				harta1 =  mutare(vector_piese[i], harta, 0	, j);
				print_harta(harta1);
			}
		}
		}
	calcul_scor(harta1, 0);
	}
	return 0;
}

void print_harta(uint64_t harta){
	int i; //i - contor
	for(i = 63; i >= 0; i--){
		if((i+1) % 8 == 0)
			printf("\n");
		if(((harta >> i) & 1) != 0)
			printf("#");
		else 
			{
				printf(".");
			}   
	}
	printf("\n");

}

uint64_t transf(uint64_t piesa, int transf){
	if(transf < 0){
	    transf *= -1;
	    piesa <<= transf;
	}
	else if(transf > 0)
	    piesa >>= transf; 
	
	return piesa;
}

int coliziune(uint64_t harta, uint64_t piesa){
	return harta & piesa;
}

float calcul_scor(uint64_t harta, double numar_linii){
	int i; //i - contor 
	int numar_zerouri = 0;		

	for(i = 63; i >= 0; i--)
		if(!(((harta >> i) & 1) != 0))
			numar_zerouri++; //algoritm numarare zerouri
	printf("\n");

	float rezultat = 0;

	rezultat = sqrt (numar_zerouri) + powf (1.25, numar_linii);
	printf("GAME OVER!\nScore:%.2f\n", rezultat);
	
	return 0;
}

uint64_t eliminare_linii(uint64_t piesa, uint64_t harta, int i){
	      
	return 0;
} 
uint64_t mutarepiesa(uint64_t piesa, int transf,int j){
	uint64_t harta = 0;
		if(transf < 0){
	  	        transf *= -1;
			piesa = ((piesa << (64 - j * 8)) << transf) | harta;
			}
	    else if(transf > 0){
		        piesa = ((piesa << (64 - j * 8)) >> transf) | harta;
			}
		else 
			piesa = (piesa << (64 - j * 8)) | harta;
		return piesa;
}

uint64_t mutare(uint64_t piesa, uint64_t harta, int transf,int j){
		       	
  	if(transf < 0){
  	        transf *= -1;
	harta = ((piesa << (64 - j * 8)) << transf) | harta;
			}
		else if(transf > 0){
		        harta = ((piesa << (64 - j * 8)) >> transf) | harta;
			}
		else 
			harta = (piesa << (64 - j * 8)) | harta; 
		return harta;
}			
int margini(uint64_t piesa, int transf, int j){
	
	int i = 0;
	uint64_t pseudo_harta = (1 << 7) + 1;
	for(i = 0; i <= 7; i++){
		pseudo_harta <<= 8;
		pseudo_harta += (1 << 7) + 1;
	}
	if(transf > 0){ //coliziune cu marginea dreapta
		i = 0;
		while(i < transf){
			++i;
			if(coliziune(mutarepiesa(piesa, i, j), pseudo_harta) != 0){				
				return i;
			}
		}
	}
	else if(transf < 0){ // coliziune cu marginea stanga
		i = 0;
		while(i > transf){
			--i;
			if(coliziune(mutarepiesa(piesa, i, j), pseudo_harta) != 0){

				return i;
			}
		}
	}		
	return 0;
}
