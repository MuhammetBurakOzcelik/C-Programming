#include<stdio.h>
#include<string.h>

#define SIZE 100
#define SIZE2 1000

int addBetween(char myArr[], int arrSize, char myChar,int index);
int multiple_evaluation (char array1[],int array1_size);
void evaluation_of_power(char array1[],char new[], int array1_size);
int partial_array(char last[SIZE2],char part[SIZE][SIZE],char islem[SIZE]);

void calculate(char newArray[SIZE][SIZE], double nums[], double result[],char islem[SIZE], int nums_size, int islem_size, int flag);
void writeFile(double result[], int nums_size);

int main()
{

    FILE *fp1;
    FILE *fp2;

    double nums[SIZE]; //Dosyadan numaraları aldıgım array.
    char plynm[SIZE2];	//Dosyadan polinomu aldıgım array
	  double result[SIZE];	//Output dosyasına yazmak icin olusturdugum array.
    char new[SIZE2];		//Polinomum bosluklarını duzenledigim array.
	  char part[SIZE][SIZE];	//5*x 23.5x*x*x*x x*x gibi ayrı ayrı islemsiz tuttugum array.
	  char islem[SIZE];		//islemleri alığ yerlestirdigim array.
	  int flag = 0;		//Polinomun ilk elemanının - olmasına gore kontrol ettigim degisken.
	
	
	  int islem_size = 0;
    int i = 0; 
    int j = 0; 

    double num;
    int new_size=0;

    fp1 = fopen("values.txt","r");
    fp2 = fopen("polynomial.txt","r");

    while(fscanf(fp1,"%lf",&nums[i]) != EOF){
        ++i;
    }

    while(fscanf(fp2,"%c",&plynm[j]) != EOF){
        ++j;
    }
    plynm[j] = 0;

	  if(plynm[0] == '-'){
		  flag = 1;
	  }


    new_size = multiple_evaluation(plynm,j);
	  evaluation_of_power(plynm,new,new_size);
	  islem_size = partial_array(new,part,islem);
	
	  calculate(part,nums,result,islem,i,islem_size,flag);
	  writeFile(result,i);

    fclose(fp1);
    fclose(fp2);


    return(0);
}
//	'*' islemini araya eklemek icin kullandıgım fonksiyon
int addBetween(char myArr[], int arrSize, char myChar,int index){
 
	  int i =0;

	  for(i=arrSize-1; i>=index; i--){
        myArr[i+1]=myArr[i];
    }
    myArr[index]=myChar;
    arrSize++;
    myArr[arrSize]='\0';

}


// arrayi matematiksel ifadeye çevirmek için kullanıdığımız fonksiyon
int multiple_evaluation (char array1[],int array1_size){
 
    int i=0;
    int pow=0;

    while(array1[i]!='\0'){
        if(array1[i]=='x'){
            if(i-1>-1 && array1[i-1]!='+' && array1[i-1]!='-' ){
                addBetween(array1,array1_size,'*',i);
                i++;
                array1_size++;
            }

        }
    	i++;
    }

	return(array1_size-1);
}
// '^' ifadesinin yerine *x koyabilmek icin kullandıgım fonksiyon.
void evaluation_of_power(char array1[],char new[], int array1_size){
	int i=0	,k;
	int j=0;
	int pow = 0;
	array1[array1_size] = '\0';
	
	while(array1[i] != '\0'){
		if(array1[i]!='^' && array1[i] != ' '){
		    new[j] = array1[i];
			++j;		
		}
        else{
			pow=array1[i+1];
			++i;
			pow = pow-48	;
			for(k=0;k<pow-1;k++){
				new[j] = '*';
				++j;
				new[j] = 'x';
				++j;
            }
		}
	++i;
	}
	new[j] = '\0';
}
//Polinomu islemlere gore parca parca alıp ayırdıgım iki boyutlu array icin kullandıgım fonksiyon.
int partial_array(char last[SIZE2],char part[SIZE][SIZE],char islem[SIZE]){
    
    int i=0, count = 0,k =0;
	int sayac = 0;
    while(last[i] != '\0'){
	
        if((last[i] != '+') && (last[i] != '-'))		
        {
            part[count][k] = last[i];
            k++;
        }
        else{
            part[count][k] = '\0';
            if(last[i] == '+'){
                islem[sayac] = '+';
            }
            else if( last[i] == '-'){
                islem[sayac] = '-';
            }
            k=0;
            count++;
			sayac++;
        }
        ++i;
    }
    part[count][k] = '\0';
	islem[sayac] = '\0';

	if(last[0] == '-' || last[0] == '+'){	/*Eger ilk elemanda - varsa fazladan bunu almamak ve islem sayısını artırmamak icin kullandıgım degisken*/
		sayac--;
	}
    count++;
	return sayac; //islem size icin kullandıgım degisken.
}	

//Hesaplamaları yapıp result arrayine atmak icin kullandıgm fonksiyon.
void calculate(char newArray[SIZE][SIZE], double nums[], double result[],char islem[SIZE], int nums_size,int islem_size, int flag){

	char temp[SIZE2];
	int newArraySize[SIZE];
	double num = 0;
	double sum;
	int count = 0;
	int i = 0,j = 0; 
	int k = 0;

	if(flag == 1){
		for(i=0; i<=islem_size;++i){
			strcpy(newArray[i],newArray[i+1]);
		}
	}

	for(i=0; i<nums_size; ++i){
		result[i] = 0;
	}

	for(i=0;i<islem_size+1;++i){
		newArraySize[i]=0;	
	}

	for(i=0;i<islem_size+1;++i){
		for(j=0;newArray[i][j]!='\0';++j){
			++newArraySize[i];
		}
	}

	i=0;
	j=0;

	while(i<nums_size)
	{
		if(newArray[k][j] != '*' && j<newArraySize[k]){
			if(newArray[k][0] != 'x'){
				temp[count] = newArray[k][j];
				count++;
				temp[count]= '\0';
				++j;
		
			}
			else{
				num=nums[i];
				++j;
			}
		}
		else if(k<=islem_size){
			if(num==0){
				sscanf(temp,"%lf",&num); }
			count = 0;
			
			while(j<newArraySize[k]){
				num*=nums[i];
				j+=2;
			}

			if(k == 0 && flag == 1){ //Eger ilk eleman '-' ise eksi ile çarpma islemi
				result[i] -= num;
			}
			else if(k == 0){		//degilse direk resultın elemanına toplama islemi
				result[i] += num;
			}
			else{		//ilk eleman haricindeki elemanları carpıp result arrayine atma islemi.Yine eksi ve artı durumuna gore
				if(flag == 1){
					if(islem[k] == '+')
						result[i]+=num;
					else if(islem[k] == '-')
						result[i]-=num;
				}
				else{		//operatorlerin sırasını kacırmamak icin kullandıgım statement
					if(islem[k - 1] == '+')
						result[i]+=num;
					else if(islem[k - 1] == '-')
						result[i]-=num;
				}
			}

			++k;
			j=0;
			count = 0;
			num = 0;
		}	
		//Values diger sayilara gecebilmek icin kontrol ettigim statement. 
		if(k > islem_size && j>=newArraySize[k]){
			k=0;
			j=0;
			i++;

		}
	}
}
//Dosyaya yazmak icin kullandıgım fonksiyon
void writeFile(double result[], int nums_size){

	FILE * fp;
	fp = fopen("evaluations.txt","w");
	int i;

	for(i = 0; i<nums_size; ++i){
		fprintf(fp,"%.2lf",result[i]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}
