#include<stdio.h>
#include<string.h>

void recursion(char array[100], int level, int index);
void printChar(int level);

void main(){

	FILE* fp;
	char array[100];

	fp = fopen("input.txt","r");

	fscanf(fp,"%s",array);
	recursion(array, 0, 0);
	
	fclose(fp);
}
//level degiskeni parantez say�s�n� vererek bu hiyerarsinin olusmasini sagliyor.
void recursion(char array[100], int level, int index){

	if(index >= strlen(array));		//Arrayin sonuna gelene kadar fonksiyon cagrilacak. 
	else if(array[index] == '(')	// Parantez sayisini artirip tekrar cagiriyorum.
		recursion(array, level+1, index+1);
	else if(array[index] == ')')	// Parantez sayisini azaltip tekrar cagiriyorum.
		recursion(array, level-1, index+1);
	else if(array[index] == ',')	// Virgul geldiginde bi sey yapmamasi gerekiyor. indice artirip tekrar cagiriyorum.
		recursion(array, level, index+1);
	else{		//Diger tum durumlarda karakter olacagi icin yazma fonksiyonunu cagiriyorum. Ve sonra fonksiyonu tekrar cagiriyorum.
		printChar(level);
		printf("%c\n", array[index]);
		recursion(array, level, index+1);
	}
}
//'-' karakterini basabilmek icin kulland�g�m fonksiyon.
void printChar(int level){
	if(level == 0);		// Hic parantez acilmadiysa bir sey yapmamali.
	else{				// Diger tum durumlar icin parantez sayisi kadar '-' ifadesi basmal�.
		printf("-");
		printChar(level-1);
	}
}
