#include<stdio.h>

void pairs(char alphabet[27], char array[729][2]);
void editFile( char allPairs[][2], int pairCounter1[],int pairCounter2[],int pairCounter3[],int pairCounter4[],int pairCounter5[],int pairCounterX[], 
				   double frequences1[729],double frequences2[729],double frequences3[729],double frequences4[729],double frequences5[729],double frequencesx[729]);

void dissimilarity(	double frequences1[729], double frequences2[729], double frequences3[729], double frequences4[729], double frequences5[729], double frequencesx[729],double dissVal[5]);

void main(){

	

	char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
	char allPair[729][2];
	
	int pairCounter1[728];			//pair sayilarini tuttugum diziler.
	int pairCounter2[728];
	int pairCounter3[728];
	int pairCounter4[728];
	int pairCounter5[728];
	int pairCounterx[728];

	double frequences1[728];		//frekanslari tuttugum diziler.
	double frequences2[728];
	double frequences3[728];
	double frequences4[728];
	double frequences5[728];
	double frequencesx[728];
	
	double dissVal[5];				//Dissimilarity degerlerini tuttugum array.

	pairs (alphabet, allPair); //ikili kombinasyonlarÄ± hazırladıgım fonksiyon
	editFile(allPair, pairCounter1, pairCounter2, pairCounter3, pairCounter4, pairCounter5, pairCounterx, 
				    frequences1, frequences2, frequences3, frequences4, frequences5, frequencesx);
	
	dissimilarity(frequences1,frequences2,frequences3,frequences4,frequences5,frequencesx,dissVal);
	printf("%f\n",dissVal[0]);
	printf("%f\n",dissVal[1]);
	printf("%f\n",dissVal[2]);
	printf("%f\n",dissVal[3]);
	printf("%f\n",dissVal[4]);
}
//Alfabeyi ikili ikili kombinasyonlarına ceviren fonksiyon.
void pairs(char alphabet[27], char array[729][2]){

	int i,j;
	int k = 0;
	for(i = 0; i<27 ; ++i){
		for(j = 0; j<27; ++j){
			array[k][0] = alphabet[i];
			array[k][1] = alphabet[j];
			++k;
		}
	}	
	
}
//Dosyadan okuyarak pair sayısını sayan ve frekanslarını hesaplayan fonksiyon.
void editFile( char allPairs[][2], int pairCounter1[],int pairCounter2[],int pairCounter3[],int pairCounter4[],int pairCounter5[],int pairCounterX[], 
				   double frequences1[729],double frequences2[729],double frequences3[729],double frequences4[729],double frequences5[729],double frequencesx[729]){

	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;
	FILE *fp5;
	FILE *fp6;	

	int i,j;
	int k;
	int sum = 0;
	char first,second;

	fp1 = fopen("language_1.txt","r");
	fp2 = fopen("language_2.txt","r");
	fp3 = fopen("language_3.txt","r");
	fp4 = fopen("language_4.txt","r");
	fp5 = fopen("language_5.txt","r");
	fp6 = fopen("language_x.txt","r");

/*----------------------1.Dosya icin islemler------------------------*/
	for(k = 0; k<729; ++k){		//Counter arrayini sıfırladım.
		pairCounter1[k] = 0;
	}
	
	fscanf(fp1,"%c",&first);	//Swap edebilmek icin aldıgım ilk degisken
	if(first == '\n' ){
			first = ' ';
	}

	do{
		if(first == EOF ){ 		//Eger dosya bos ise donguden cıkmalı.
			break;
		}		
		second = fgetc(fp1);		
		if(second == EOF ){ 	//Eger dosya sonuna gelirse donguden cıkmalı.
			break;
		}			
		if(second == '\n'){		/*Eger karakter \n ise bosluk ile degistir*/
			second = ' ';
		}
		/*Eger bosluk karakterse veya karakter bosluksa veya karakter karakter ise pair arrayi icinde bul ve counter artır.*/
		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounter1[i] += 1;		// Pairin hangi indiste ise onun degerini 1 artır.
				}
			}
		}
		first = second;
	}while(1);

	for(k = 0; k<729; ++k){			/*toplam kaç pair var ise frekans hesaplamak icin sum degiskeninde topluyorum.*/
		sum += pairCounter1[k];
	}

	for(k = 0; k<728; ++k){			// Her pairin frekans degerini topladıgım toplam pair sayisina bolerek buluyorum.
		frequences1[k] = pairCounter1[k] / ((double)sum);
	}
	printf("%d\n",sum);
	fclose(fp1);
	sum = 0; 						// Dosyayi kapatip sum degerini sifirliyorum. Ve bu olayı tum dosyalar icin tekrarlıyorum...
	
/*---------------------2.Dosya icin islemler----------------------*/
	for(k = 0; k<729; ++k){
		pairCounter2[k] = 0;
	}

	
	first = fgetc(fp2);
	if(first == '\n'){
		first = ' ';
	}
	do{
		if(first == EOF ){ 
			break;
		}	
		second = fgetc(fp2);		
		
		if(second == '\n'){
			second = ' ';  
		}
		if(second == EOF){ 
			break;
		}

		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounter2[i] += 1;
				}
			}
		}
		first = second;
	}while(1);
		
	for(k = 0; k<729; ++k){
		sum += pairCounter2[k];
	}

	for(k = 0; k<729; ++k){
		frequences2[k] = pairCounter2[k] / ((double)sum);
	}

	fclose(fp2);
	sum =0;

/*--------------------------3.Dosya icin islemler---------------------------*/
	for(k = 0; k<729; ++k){
		pairCounter3[k] = 0;
	}

	fscanf(fp3,"%c",&first);

	if(first == '\n'){
		first = ' ';	
	}
	do{
		if(first == EOF ){ 
			break;
		}	
		second = fgetc(fp3);
		
		if(second == '\n'){
			second = ' ';
		}
		if(second == EOF){ 
			break;
		}

		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounter3[i] += 1;
				}
			}
		}
		first = second;
	}while(1);
		
	for(k = 0; k<729; ++k){
		sum += pairCounter3[k];
	}

	for(k = 0; k<729; ++k){
		frequences3[k] = pairCounter3[k] / ((double)sum);
	}

	fclose(fp3);
	sum = 0;

/*---------------------4.Dosya icin islemler----------------------*/
	for(k = 0; k<729; ++k){
		pairCounter4[k] = 0;
	}

	
	fscanf(fp4,"%c",&first);
	if(first == '\n'){
		first = ' ';
	}
	do{
		if(first == EOF ){ 
			break;
		}	
		second = fgetc(fp4);
		
		if(second == '\n'){
			second = ' ';
		}
		if(second == EOF){ 
			break;
		}

		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounter4[i] += 1;
				}
			}
		}
		first = second;
	}while(1);

	for(k = 0; k<729; ++k){
		sum += pairCounter4[k];
	}

	for(k = 0; k<729; ++k){
		frequences4[k] = pairCounter4[k] / ((double)sum);
	}

	fclose(fp4);
	sum =0;

/*---------------------5.Dosya icin islemler----------------------*/
	for(k = 0; k<729; ++k){
		pairCounter5[k] = 0;
	}

	fscanf(fp5,"%c",&first);
	if(first == '\n'){
		first = ' ';
	}
	do{
		if(first == EOF ){ 
			break;
		}	
		second = fgetc(fp5);
		
		if(second == '\n'){
			second = ' ';
		}
		if(second == EOF){ 
			break;
		}

		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounter5[i] += 1;
				}
			}
		}
		first = second;
	}while(1);
		
	for(k = 0; k<729; ++k){
		sum += pairCounter5[k];
	}

	for(k = 0; k<729; ++k){
		frequences5[k] = pairCounter5[k] / ((double)sum);
	}

	fclose(fp5);
	sum =0;
/*---------------------6.Dosya icin islemler----------------------*/
	for(k = 0; k<729; ++k){
		pairCounterX[k] = 0;
	}

	
	fscanf(fp6,"%c",&first);
	if(first == '\n'){
		first = ' ';
	}
	do{
		if(first == EOF ){ 
			break;
		}	
		second = fgetc(fp6);		
		
		if(second == '\n'){
			second = ' ';
		}
		if(second == EOF){ 
			break;
		}

		if( ((first == ' ') && (second != ' ')) || ((first != ' ') && (second == ' ')) || ((first != ' ') && (second != ' ')) ) {
			for(i = 0; i<729; ++i){
				if( (allPairs[i][0]  == first) && (allPairs[i][1] == second) ){
					pairCounterX[i] += 1;
				}
			}
		}
		first = second;
	}while(1);

	for(k = 0; k<729; ++k){
		sum += pairCounterX[k];
	}

	for(k = 0; k<729; ++k){
		frequencesx[k] = pairCounterX[k] / ((double)sum);
	}

	fclose(fp6);
	sum =0;
}

//Tum dissimilarity degerlerini buldugum fonksiyon
void dissimilarity(	double frequences1[729], double frequences2[729], double frequences3[729], double frequences4[729], double frequences5[729], double frequencesx[729],double dissVal[5]){

	int i;
	double temp1 = 0, temp2 = 0, temp3= 0, temp4 = 0, temp5 = 0;

	for(i = 0; i<728; ++i){								//Her bir pairin frekansinin bulundugu indisler ayni oldugu icin birbirinden cıkariyorum.
		temp1 = frequencesx[i]-frequences1[i];
		
		if(temp1 < 0){									//Mutlak deger islemini gerceklestiriyorum.
			temp1 *= -1;
		}
		dissVal[0] += temp1;							//Buldugum sonucu dissimilarity arrayine atıyorum.
	}
	
	for(i = 0; i<728; ++i){
		temp2 = frequencesx[i]-frequences2[i];
		if(temp2 < 0){
			temp2 *= -1;
		}
		dissVal[1] += temp2;
	}
	
	for(i = 0; i<728; ++i){
		temp3 = frequencesx[i]-frequences3[i];
		if(temp3 < 0){
			temp3 *= -1;
		}
		dissVal[2] += temp3;
	}
	
	for(i = 0; i<728; ++i){
		temp4 = frequencesx[i]-frequences4[i];
		if(temp4 < 0){
			temp4 *= -1;
		}
		dissVal[3] += temp4;
	}

	for(i = 0; i<728; ++i){
		temp5 = frequencesx[i]-frequences5[i];
		if(temp5 < 0){
			temp5 *= -1;
		}
		dissVal[4] += temp5;
	}

}
