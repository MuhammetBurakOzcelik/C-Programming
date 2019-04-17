#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cube{
	int ** a;
};

int row(int row_size);
int left(int face);
int right(int face);
int up(int face, int opNum,int face2);
int down(int face,int opNum,int face2);

void main(){
	int a =0;
	int row_size = 0;
	int opNum = 0;
	int i,j,k,num = 0;
	int x = 0;
	int face,rowCol;
	int satir = 0;
	int control = 0;
	char way[10], rotate[10];
	int *temp;
	int * temp2;
	struct cube * p;
	FILE * fp3;
	p = malloc(sizeof(struct cube*)*7);
	
/*----------------------------------------------------------------------------*/	
	/*Commands.txt'nin ilk satirini okuyarak iki boyutlu arrayin icerisini renk kodlari ile doldurdum.*/
	FILE * fp1;
	fp1 = fopen("commands.txt","r");	
	
	fscanf(fp1,"%d",&num);
	while(x<6){
		p[x].a = malloc(sizeof(int*)*num);
		for(j=0; j<num; ++j){
			p[x].a[j] = malloc(sizeof(int)*num);
			for(i = 0; i<num; ++i){
				p[x].a[j][i] = x;
			}
		}
	++x;
	}
	temp = malloc(sizeof(int)*num);
	temp2 = malloc(sizeof(int)*num);
	
	row_size = row(row_size);			//Toplam kac tane rotate islemi oldugunu buldugum fonksiyon.
	i=0;
	j=0;
	FILE * fp2;
	fp2 = fopen("commands.txt","r");
	fscanf(fp2,"%d",&num);
	while(i<row_size){
		fscanf(fp2,"%s",rotate);		//rotate kelimesini aldi
		fscanf(fp2,"%d",&face);		//Sonraki numarayi aldi
		fscanf(fp2,"%s",way);			//Satir ya da sutun aldi
		fscanf(fp2,"%d",&rowCol);		//Ikinci numarayi aldi
		fscanf(fp2,"%s",rotate);		//Yonu aldi
		satir = rowCol;
		if(strcmp(rotate,"left") == 0){
			if(strcmp(way,"row") == 0){
				for(j=0; j<num; ++j){
					/*1.islem*/
					control = left(face);	
					if((control == 3) && ( face == 5  || face==4)){
						if(face == 4){	//4. y�z�n sola �evrilmesine bak
							rowCol = satir;
							temp[j] = p[control].a[j][rowCol];
							p[control].a[num-j-1][satir] = p[face].a[rowCol][j];						
						}
						else if(face == 5){
							rowCol = satir;
							temp[j] = p[control].a[j][num-rowCol-1];
							p[control].a[j][num-rowCol-1] = p[face].a[rowCol][j];
						}
					}
					else{
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = p[face].a[rowCol][j];
					}
					/*2.islem*/
					if(control == 3 && (face == 5 || face == 4)){
						if(face == 5) { control = 4;
										rowCol = (num-rowCol-1);
										
						}
						else{ control = 5;
							  rowCol = num- rowCol-1;
						}	
					}
					else{
						control = left(control);
					}
					
					if( (control == 5 || control == 4) && (face == 5 || face == 4)){
						if(face == 4 && control == 5){
							temp2[j] = p[control].a[rowCol][j];
							p[control].a[rowCol][j] = temp[j];
						}
						else if(face ==5  && control == 4){
							temp2[j] = p[control].a[rowCol][j];
							p[control].a[rowCol][num-j-1] = temp[j];
						}
					}
					else{
						temp2[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = temp[j];
					}
					/*3.islem*/
					if(control == 4 && (face == 5)){ control = 1;
						rowCol = (num - rowCol -1);
					}
					else if(control == 5 && (face == 4) ){ control = 1;}
					else {
						control = left(control);
					}
					if( (control == 3 || control == 1) && (face == 5 || face == 4)){
						if(control == 1 && face == 4){
							temp[j] = p[control].a[j][rowCol];
							p[control].a[num-j-1][rowCol] = temp2[j];
						}
						else if(control == 1 && face == 5){
							temp[j] = p[control].a[j][rowCol];
							p[control].a[j][rowCol] = temp2[j];
						}
					}
					else{
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = temp2[j];
					}
					/*Son islem*/
					if(control == 1 && (face == 4)){ 
						control = 4;
						rowCol = num-rowCol-1;
					}
					else if(control == 1 && face ==5){ control = 5;}
					else if(control == 3 && (face == 5)){control = 4;}
					else if(control == 3 && face ==4 ){ 
						control = 5;
						rowCol = num-rowCol-1;
					}
					else{ 
						control = left(control);
					}
					if((control == 5 || control == 4 )&& (face == 5 || face == 4)){
						if(control == 4 && face ==4 ){
							p[control].a[rowCol][j] = temp[j];
						}
						else if(control == 5 && face ==5){
							p[control].a[rowCol][num-j-1] = temp[j];
						}
					}
					else{
						p[control].a[rowCol][j] = temp[j];
					}
				}
				
			}
		}
		else if(strcmp(rotate,"right") == 0){
			for(j=0; j<num; ++j){
				control = right(face);
				/*1.islem*/
				if((control == 1) && ( face == 5  || face==4)){			
					if(control == 1 && (face == 4) ){
							rowCol = (num -rowCol -1);
					}
					if(control == 1 && (face == 5) ){
						temp[j] = p[control].a[j][rowCol];
						p[control].a[num-j-1][rowCol] = p[face].a[satir][j];						
					}
					else if( control == 1 && face ==4){
						temp[j] = p[control].a[j][rowCol];
						p[control].a[j][rowCol] = p[face].a[satir][j];
					}
				}
				else{
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = p[face].a[rowCol][j];
				}
				/*2.islem*/
				if(control == 1 && (face == 5 || face == 4)){
					if(face == 5) { 
						control = 4;
						rowCol = (num - rowCol -1);
					}
					else{ 
						control = 5;
					}	
				}
				else{
					control = right(control);
				}
				
				if( (control == 5 || control == 4) && (face == 5 || face == 4)){
					if(control == 4 && face == 5){
						temp2[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = temp[j];
					}
					else if(control == 5 && face ==4 ){
						temp2[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][num-j-1] = temp[j];
					}
				}
				else{
					temp2[j] = p[control].a[rowCol][j];
					p[control].a[rowCol][j] = temp[j];
				}
				
				/*3.islem*/
				if(control == 4 && (face == 5)){ 
					control = 3;
				}
				else if(control == 5 && (face == 4) ){
					control = 3;
					rowCol = num - rowCol -1;
				}
				else {
					control = right(control);
				}
				if((control == 3 ) && (face == 5 || face == 4)){
					if(control == 3 && face ==5){
						temp[j] = p[control].a[j][rowCol];
						p[control].a[num-j-1][rowCol] = temp2[j];
					}
					else if(control == 3 && face ==4 ){
						temp[j] = p[control].a[j][rowCol];
						p[control].a[j][rowCol] = temp2[j];
					}
				}
				else{
					temp[j] = p[control].a[rowCol][j];
					p[control].a[rowCol][j] = temp2[j];
				}
				/*Son islem*/
				if(control == 3 && (face == 4)){ 
						control = 4;
				}
				else if(control == 3 && face ==5){ 
					control = 5;
					rowCol = num-rowCol-1;
				}
				else if(control == 1 && (face == 5)){
					control = 4;
					rowCol = num -rowCol -1;
				}
				else if(control == 1 && face ==4 ){ 
					control = 5;
				}
				else{ 
					control = right(control);
				}
				if((control == 5 || control == 4 ) && (face == 5 || face == 4)){
					if(control == 5 && face == 5){
						p[control].a[rowCol][j] = temp[j];
					}
					else if(control == 4 && face == 4){
						p[control].a[rowCol][num-j-1] =temp[j]; 
					}
				}
				else{
					p[control].a[rowCol][j] = temp[j];
				}
			}
		}
		else if(strcmp(rotate,"up") == 0){
			for(j=0; j<num; j++){
				control = up(face,1,face);
				/*1. islem*/
				if (control == 4 && (face == 1 || face ==3) ){
					if(control == 4 && (face == 1) ){
							rowCol = (num -rowCol -1);
					}
					if(control == 4 && (face == 3) ){
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][num-j-1] = p[face].a[j][rowCol];						
					}
					else if(face == 1){	
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = p[face].a[j][rowCol];
					}
				}
				else if(control == 2 && face == 4){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = p[face].a[j][rowCol];			
				}
				else if(control == 4 && face ==2){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = p[face].a[j][rowCol];
				}
				else{
						temp[j] = p[control].a[j][rowCol];
						p[control].a[j][rowCol] = p[face].a[j][rowCol];
				}
				/*2.islem*/
				if(control == 4 && (face == 1 || face == 3)){
					if(face == 3) { 
						control = 1;
						rowCol = (num - rowCol -1);
					}
					else{ 
						control = 3;
					}	
				}
				else{
					control = up(control,2,face);
				}
				if((control == 1 || control == 3) && (face == 1 || face == 3)){
					temp2[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp[j];
				}
				else if(control == 0 && face == 2){
					temp2[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp[j];
				}
				else if(control == 2 && face ==0){
					temp2[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp[j];
				}
				else{
					temp2[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp[j];
				}
				/*3.islem*/
				if(control == 3 && (face == 1)){ 
					control = 5;
					rowCol = num - rowCol-1;
				}
				else if(control == 1 && (face == 3) ){
					control = 5;
				}
				else {
					control = up(control,3,face);
				}
								
				if((control == 5 || control == 4) && (face == 1 || face == 3)){
					temp[j] = p[control].a[rowCol][j];
					p[control].a[rowCol][j] = temp2[j];
				}
				else if(control == 5 && face == 2){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp2[j];
				}
				else if(control == 2 && face == 5){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp2[j];
				}
				else{
					temp[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp2[j];
				}
				/*Son islem*/
				if(control == 5 && (face == 1)){ 
						control = 1;
				}
				else if(control == 5 && face ==3){ 
					control = 3;
					rowCol = num-rowCol-1;
				}
				else if(control == 4 && (face == 1)){
					control = 3;
				}
				else if(control == 4 && face ==3 ){ 
					control = 1;
					rowCol = num - rowCol -1;
				}
				else if(control == 2 && face ==2){
					p[control].a[j][rowCol] = temp[j];
				}
				else{ 
					control = up(control,4,face);
				}

				if((control == 1 || control == 3 ) && (face == 1 || face == 3)){
					p[control].a[j][rowCol] = temp[j];
				}	
				else{
					p[control].a[j][rowCol] = temp[j];
				}
			}
		}
		else if(strcmp(rotate,"down") == 0){
			for(j=0; j<num; j++){
				control = down(face,1,face);
				/*1. islem*/
				if (control == 5 && (face == 1 || face ==3) ){
					if(control == 5 && (face == 3) ){
							rowCol = (num -rowCol -1);
					}
					if(control == 5 && (face == 1) ){
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][num-j-1] = p[face].a[j][rowCol];
					}
					else if(face ==3){	
						temp[j] = p[control].a[rowCol][j];
						p[control].a[rowCol][j] = p[face].a[j][rowCol];
					}
				}
				else if((control == 2) && (face ==5)){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = p[face].a[j][rowCol];	
				}
				else if(control == 5 && face == 2){   //2. columnun down edilmesi durumunu g�zden ge�ir
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = p[face].a[j][rowCol];
				}
				else{
						temp[j] = p[control].a[j][rowCol];
						p[control].a[j][rowCol] = p[face].a[j][rowCol];
				}
				/*2.islem*/
				if(control == 5 && (face == 1 || face == 3)){
					if(face == 1) { 
						control = 3;
						rowCol = (num - rowCol -1);
					}
					else{ 
						control = 1;
					}	
				}
				else{
					control = down(control,2,face);
				}
				if((control == 1 || control == 3) && (face == 1 || face == 3)){
					temp2[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp[j];
				}
				else if(control == 0 && face == 2){
					temp2[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp[j];
				}
				else if(control == 2 && face == 0){
					temp2[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp[j];
				}
				else{
					temp2[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp[j];
				}
				/*3.islem*/
				if(control == 1 && (face == 3)){ 
					control = 4;
					rowCol = num - rowCol-1;
				}
				else if(control == 3 && (face == 1) ){
					control = 4;
				}
				else {
					control = down(control,3,face);
				}
				
				if((control == 5 || control == 4) && (face == 1 || face == 3)){
					temp[j] = p[control].a[rowCol][j];
					p[control].a[rowCol][j] = temp2[j];
				}
				else if(control == 4 && face == 2){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp2[j];
				}
				else if(control == 4 && face == 0){
					temp[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp2[j];
				}
				else if(control == 2 && face == 4){
					temp[j] = p[control].a[num-j-1][num-rowCol-1];
					p[control].a[num-j-1][num-rowCol-1] = temp2[j];
				}
				else{
					temp[j] = p[control].a[j][rowCol];
					p[control].a[j][rowCol] = temp2[j];
				}
				/*Son islem*/
				if(control == 4 && (face == 1)){ 
						control = 1;
						rowCol = num - rowCol -1;
				}
				else if(control == 4 && face ==3){ 
					control = 3;
				}
				else if(control == 5 && (face == 1)){
					control = 3;
					rowCol = num - rowCol -1;
				}
				else if(control ==5 && face ==3 ){ 
					control = 1;
				}
				else{ 
					control = down(control,4,face);
				}

				if((control == 4 || control == 5 ) && (face == 1 || face == 3)){
					p[control].a[j][rowCol] = temp[j];
				}
				else if(control == 2 && face == 2){
					p[control].a[j][rowCol] = temp[j];
				}
				else if(control == 4 && face ==4){
					p[control].a[j][rowCol] = temp[j];
				}	
				else{
					p[control].a[j][rowCol] = temp[j];
				}
			
			}
		}
	++i;
	}
	fp3 = fopen("result.txt","w");
	x=0;
	while(x<6){
		for(a = 0; a<num; a++){
			for(k=0; k<num; k++){
				fprintf(fp3,"%d ",p[x].a[a][k]);
				if(k % num == num -1){ fprintf(fp3,"\n");
				}
			}
		}
	fprintf(fp3,"\n");
	++x;
	}
					
	fclose(fp2);
	fclose(fp1);
	
	while(x<6){
		for(j=0; j<num; ++j){
			free(p[x].a[j]);
		}
		free(p[x].a);
	++x;
	}
	free(p);
	free(temp);
	free(temp2);
}

int row(int row_size){
	FILE * fp2;
	char input[10];
	
	fp2 = fopen("commands.txt","r");
	
	while( (fscanf(fp2,"%s",input)) != EOF ){
		if(strcmp(input,"rotate") == 0){
			++row_size;
		}
	}
	
	fclose(fp2);
	return(row_size);
}

int left(int face){
	if(face == 0) { return 3;}
	else if(face == 1){ return 0;}
	else if(face == 2){ return 1;}
	else if(face == 3){ return 2;}
	else if(face == 4){ return 3;}
	else if(face == 5){ return 3;}
}

int right(int face){
	if(face == 0) { return 1;}
	else if(face == 1){ return 2;}
	else if(face == 2){ return 3;}
	else if(face == 3){ return 0;}
	else if(face == 4){ return 1;}
	else if(face == 5){ return 1;}
}

int up(int face,int opNum,int face2){
	if(face == 0) {
		if(opNum == 3){
			return 5;
		}
		else{
			return 4;}
	}
	else if(face == 1){ return 4;}

	else if(face == 2){ 
		if(opNum == 1){
			return 4;}
		else{
			return 5;}
	}
	else if(face == 3){ return 4;}
	else if(face == 4){
		if(opNum == 2 && face2 == 2){
			return 0;
		}
		else{
			return 2;}
	}
	else if(face == 5){ 
		if(opNum == 4 && face2 == 2){
			return 2;
		}
		else{
			return 0;}
	}
}

int down(int face,int opNum,int face2){
	if(face == 0) { 
		if(opNum == 3){
			return 4;
		}
		else{
			return 5;}
	}
	else if(face == 1){ return 5;}
	else if(face == 2){ 
		if(opNum == 1) {
			return 5;
		}
		else{
			return 4;}
	}
	else if(face == 3){ return 5;}
	else if(face == 4){ 
		if(opNum == 4 && face2 == 2){
			return 2;
		}
		else{
			return 0;}
	}
	else if(face == 5){ 
		if(opNum == 2 && face2 == 2){
			return 0;}
		else{	
			return 2;}
	}
}
