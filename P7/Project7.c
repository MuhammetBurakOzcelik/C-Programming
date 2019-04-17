#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct input{
	char inputName[10];
	int val;
};

struct gate{
	char gateName[10];
	char inputName1[10];
	char inputName2[10];
	int type;
	int output;
	int input1;
	int input2;
};
void gate_list(struct gate *liste,struct input *inputs, int inputSize,int gate);
void eval(struct gate* liste,struct input* inputs,int inputSize, int gateNum,int opSize);
int row_Size(int *opSize,int numSize);


void main(){

	FILE *fp1;
	FILE *fp2;
	
	int i=0; 	
	char chr;
	char circ[10];
	int andCount=0,orCount=0,notCount=0,flipCount=0;
	int inputSize = 1;
	int gateNum=0;
	int  opSize=0;
	struct gate* liste;
	struct input* inputs;
	
	fp2 = fopen("circuit.txt","r");


//Ka� tane gate oldugunu buldugum dongu	
	while( (chr = fgetc(fp2)) != EOF){
	
		 if(chr == '\n' || chr == ' '){
		 	circ[i] = '\0';
		 	i =0;
		 	
		 	if(strcmp(circ,"AND") == 0){
		 		++andCount;
		 		gateNum++;
		 	}
		 	else if(strcmp(circ,"OR") == 0){
		 		orCount++;
		 		gateNum++;
		 	}
		 	else if(strcmp(circ,"FLIPFLOP")==0){
		 		flipCount++;
		 		gateNum++;
		 	}
		 	else if(strcmp(circ,"NOT")==0){
		 		notCount++;
		 		gateNum++;
		 	}
		 }
		 else{
		 	circ[i] = chr;
		 	++i;
		 }
	}
	fclose(fp2);
		
	fp2 = fopen("circuit.txt","r");

//Ka� tane input oldugunu bulmaya yarayan dongu.
	i=0;
	while( (chr = fgetc(fp2)) != EOF){
		if(chr == ' '){	
			circ[i] = '\0';
		 	i =0;
		}
		else{
		 	circ[i] = chr;
		 	++i;
		 }
		if(strcmp(circ,"INPUT") == 0){	
			while( (chr = fgetc(fp2)) != '\n'){
				if(chr == ' '){
					++inputSize;
				}
			}
		break;		
		}
	}
	fclose(fp2);

	liste  = calloc(gateNum,sizeof(struct gate));								//Dinamik hafiza ayirmak icin.GateNum kadar yer actim.
	inputs = calloc(inputSize,sizeof(struct input));							//Dinamik hafiza ayirmak icin.input sayisi kadar yer acilmasi gerekli.

	gate_list(liste,inputs,inputSize,(gateNum));
	row_Size(&opSize,inputSize);
	eval(liste,inputs,inputSize,(gateNum),opSize);
	

	free(liste);																//Bellekte isimiz bittiginde gereksiz yer tutmamasi icin alan� free ettim.
	free(inputs);
}
																				/*Bu fonksiyonda kap�lar�n girdi ve ciktilarini bulup kopyalad�m. Ve bu kapi tiplerini 
																				numaralandirdim. Bu fonksiyon da kapi sayisi kadar olacagi icin gateNum gonderdim.*/
void gate_list(struct gate *liste,struct input *inputs, int inputSize,int gate){

	FILE * fp1;
	fp1 = fopen("circuit.txt","r");
	char temp[10];
	char temp1[10];
	int i = 0, j =0;
	
	while(i<(gate) ){
		fscanf(fp1,"%s",temp);
		
		if( strcmp(temp,"AND") == 0){
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].gateName,temp1);
			liste[i].type = 1;

			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName1,temp1);
	
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName2,temp1);
			++i;
		}
		else if( strcmp(temp,"OR") == 0){
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].gateName,temp1);
			liste[i].type = 2;

			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName1,temp1);

			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName2,temp1);
			++i;
		}
		else if( strcmp(temp,"NOT") == 0){
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].gateName,temp1);
			liste[i].type = 3;

			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName1,temp1);
			++i;
		}
		else if( strcmp(temp,"FLIPFLOP") == 0){
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].gateName,temp1);
			liste[i].type = 4;
			liste[i].output = 0;
			fscanf(fp1,"%s",temp1);
			strcpy(liste[i].inputName1,temp1);
			++i;	
		}
	}
	
	fclose(fp1);
	
}	
																				//Satir sayisini sayarak ana dongunun kac kere donmesi gerektigini bulmus oldum.
int row_Size(int *opSize,int numSize){

	FILE *fp1;
	fp1 = fopen("input.txt","r");
	int row,i=0;
	while( (fscanf(fp1,"%d",&row)) != EOF){
		if(i%numSize == 0){														// kac input oldugunu bildigim icin eof durumu sikinti olmasin diye bu sekilde saydim.
			++(*opSize);
		}
		++i;
	}
	
	fclose(fp1);
	return(*opSize);
}
																				/*Eval fonksiyonu kapilari type numarasini kiyaslayacak,kapilarin input isimlerini k�yaslayacak ve eger son satirsa 
																				ekrana basma islevini yapacak olan fonksiyon.*/
void eval(struct gate* liste,struct input* inputs,int inputSize, int gateNum,int opSize){

	FILE * fp1;
	FILE * fp2;
	fp1 = fopen("circuit.txt","r"); 
	fp2 = fopen("input.txt","r");
	int i =0;
	int k = 0;
	int j=0;
	char temp[10];
	char temp1[10];
	int control = 1;
	
																				//Bu dongude inputlarin isimlerini inputs structinin icine kopyaladim.
	while(control == 1){
		fscanf(fp1,"%s",temp);
		if( strcmp(temp,"INPUT") == 0){
				for(j=0; j<inputSize; ++j){
					fscanf(fp1,"%s",temp1);
					strcpy(inputs[j].inputName,temp1);
				}	
		}
		else{
			control = 0;}
	}
																				/*Satir sayisi kadar(opSize) donecek bu dongu kap�lar�n isimlerini karsilastirarak eger 
																				son satirsa cikan sonucu bastiracak.*/
	while(i<opSize){
		for(j=0; j<inputSize; ++j){												//inputlarin icine gerekli degerleri input.txt'den alip attim.
			fscanf(fp2,"%d",&inputs[j].val);
		}
		for(j = 0; j<gateNum; ++j){
			if(liste[j].type == 1){
				for(k = 0; k< inputSize; ++k){
					
					if( strcmp(liste[j].inputName1,inputs[k].inputName) == 0){		/*input ismi a-b de olabilir.*/
						liste[j].input1 = inputs[k].val;
					}
					if(	strcmp(liste[j].inputName2,inputs[k].inputName) == 0){
						liste[j].input2 = inputs[k].val;
					}
				}
				for(k = 0; k<j; ++k){
					if(strcmp(liste[j].inputName1,liste[k].gateName) == 0){			/*ya da bir input baska bir kapinin ismi olabilir.*/
						liste[j].input1 = liste[k].output;
					}
					if(strcmp(liste[j].inputName2,liste[k].gateName) == 0){
						liste[j].input2 = liste[k].output;
					}
				}
				liste[j].output = ((liste[j].input1) * (liste[j].input2));			/*and operatorunun sonucu*/
				if(j == gateNum-1){													//Eger son satirsa ekrana basmali.
					printf("%d\n",liste[j].output);
				}
			}
			
			else if(liste[j].type == 2){
				for(k = 0; k< inputSize; ++k){
					if( strcmp(liste[j].inputName1,inputs[k].inputName) == 0){
						liste[j].input1 = inputs[k].val;
					}
					if(	strcmp(liste[j].inputName2,inputs[k].inputName) == 0){
						liste[j].input2 = inputs[k].val;
					}
				}
				for(k = 0; k<j; ++k){
					if(strcmp(liste[j].inputName1,liste[k].gateName) == 0){
						liste[j].input1 = liste[k].output;
					}
					if(strcmp(liste[j].inputName2,liste[k].gateName) == 0){
						liste[j].input2 = liste[k].output;
					}
				}
				if((liste[j].input1 == 1) || (liste[j].input2) == 1){
					liste[j].output = 1;
				}
				else{
					liste[j].output = 0;}
				if(j == gateNum-1){
					printf("%d\n",liste[j].output);
				}
			}
			
			else if(liste[j].type == 3){
				for(k = 0; k< inputSize; ++k){
					if( strcmp(liste[j].inputName1,inputs[k].inputName) == 0){
						liste[j].input1 = inputs[k].val;
					}
				}
				for(k = 0; k<j; ++k){
					if(strcmp(liste[j].inputName1,liste[k].gateName) == 0){
						liste[j].input1 = liste[k].output;
					}
				}
				if(liste[j].input1 == 0){
					liste[j].output = 1;}
				else{
					liste[j].output = 0;}
				if(j == gateNum-1){
					printf("%d\n",liste[j].output);
				}
			}
			
			else if(liste[j].type == 4){
				for(k = 0; k< inputSize; ++k){
					if( strcmp(liste[j].inputName1,inputs[k].inputName) == 0){
						liste[j].input1 = inputs[k].val;
					}
				}
				for(k = 0; k<j; ++k){
					if(strcmp(liste[j].inputName1,liste[k].gateName) == 0){
						liste[j].input1 = liste[k].output;
					}
				}
				if(liste[j].input1 == liste[j].output ){
					liste[j].output = 0;}
				else{
					liste[j].output = 1;}
				if(j == gateNum-1){
					printf("%d\n",liste[j].output);
				}
			}
		}
	++i;
	}
	
	fclose(fp2);
	fclose(fp1);
}
