#include <stdio.h>
#include <string.h>

#define MAX_LEN 250
#define MAX_ROW 100

void read_File(char array[MAX_ROW][MAX_LEN], FILE *f);

int vertical_search(char array[MAX_ROW][MAX_LEN], char word[MAX_LEN], int word_size,int i,int j);
int horizontal_search(char array[MAX_ROW][MAX_LEN], char word[MAX_LEN], int word_size,int i,int j);

void find_Word(char array[MAX_ROW][MAX_LEN],char word[MAX_LEN], int word_size);

int main(){

	FILE *f;
	f = fopen("input.txt","r");
	
	int word1_size, word2_size, word3_size, word4_size, word5_size;
	
	char array[MAX_ROW][MAX_LEN];	//Dosyadan okuduklarımızı topladımız array.
	
	//Kelimeleri ve uzunlukluklarını tuttuğumuz değişkenler.
	char word1[MAX_LEN] = "Xanthos";
	word1_size = strlen(word1);

	char word2[MAX_LEN] = "Patara";
	word2_size = strlen(word2);

	char word3[MAX_LEN] = "Myra";
	word3_size = strlen(word3);
	
	char word4[MAX_LEN] = "Arycanda";
	word4_size = strlen(word4);

	char word5[MAX_LEN] = "Phaselis";
	word5_size = strlen(word5);

	read_File(array,f);
	find_Word(array,word1,word1_size); 
	
	find_Word(array,word2,word2_size);

	find_Word(array,word3,word3_size);

	find_Word(array,word4,word4_size);

	find_Word(array,word5,word5_size);


	fclose(f);

return(0);
}

//Dosyadaki kelimeleri okuyarak bir array'in içine attım.
void read_File(char array[MAX_ROW][MAX_LEN],FILE *f){
	
	int i = 0;	
	while(fscanf(f,"%s",array[i]) != EOF){
		++i;
	}
}
 
//Kelimenin doğru olup olmadığıını ve doğruysa vertical olup olmadığını kontrol ettiğim fonksiyon.
int vertical_search(char array[MAX_ROW][MAX_LEN], char word[MAX_LEN], int word_size,int i,int j){

	int x;
	char control[word_size];	
	int size = 0;
	//Dikey arama yapabilmek için array[x][j] x artırıyoruz.
	for(x = i; x<i+word_size; ++x){
		control[size] = array[x][j]; //Aradığımız ya da değil baş harfi uyan bu kelimeyi bir arraye atarak altta strcmp ile aradığımız kelime mi diye kontrol ediyoruz.
		++size;
	}
	control[size] = 0; //Aradığımız kelimeyi bozmamak için son hanemize 0 atıyoruz.
	if(strcmp(control,word)==0){
		return 1;}
	else
		return 0;
}
//Kelimenin doğru olup olmadığıını ve doğruysa horizontal olup olmadığını kontrol ettiğim fonksiyon.
int horizontal_search(char array[MAX_ROW][MAX_LEN], char word[MAX_LEN], int word_size,int i,int j){

	int y;
	char control[word_size];	
	int size = 0;
	
	//Yatay arama yapabilmek için array[i][y] y artırıyoruz.
	for(y = j; y<j+word_size; ++y){
		control[size] = array[i][y]; //Aradığımız ya da değil baş harfi uyan bu kelimeyi bir arraye atarak altta strcmp ile aradığımız kelime mi diye kontrol ediyoruz.
		size++;
	}
	control[size] = 0;			//Aradığımız kelimeyi bozmamak için son hanemize 0 atıyoruz.
	if(strcmp(control,word)==0){ //Aradığımız kelime ile aynı olup olmadığını kontrol ediyoruz ve doğruysa 1 yanlışsa 0 return ediyoruz.
		return 1;}
	else
		return 0;
}

void find_Word(char array[MAX_ROW][MAX_LEN],char word[MAX_LEN], int word_size){

	int i = 0;
	int j = 0;
	
	for(j = 0; j<MAX_LEN; ++j){
		if(array[i][j] == 0){
			++i;
			j=-1; //Döngü bittiğinde tekrar artıracağından array[i][0] elemanından başlayabilmesi için j= -1 yaptım.
		}
		else{
			if(array[i][j] == word[0]){	//Eğer aradığımız kelime ile baş harfler uyuşuyorsa arama ve eşleşme işlemini yapacak olan fonksiyonların doğruluğu ile kontrol ediyoruz.		
				if((horizontal_search(array,word,word_size,i,j)) == 1){ //Eğer aradığımız kelime yataysa
					++i;	//Koordinatlarımızı arraylar sıfırdan başladığı için 1 artırıyoruz.
					++j;
					printf("%s (%d,%d) Horizontal\n",word, i, j); //Terminale basma işlemi.
					break;
				}
				else if(vertical_search(array,word,word_size,i,j) == 1){ //Eğer aradığımız kelime dikeyse
					++i;	//Koordinatlarımızı arraylar sıfırdan başladığı için 1 artırıyoruz.
					++j;
					printf("%s (%d,%d) Vertical\n",word,i,j); //Terminale basma işlemi.
					break;
				}
			}
		}
	}
}
