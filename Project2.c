#include <stdio.h>
#define MAX_SIZE 1000

int read_File (float myArray[],FILE *fp);
void chunk_Seperator(float chunk[],int result[],float myArray[],float average[],int arraySize,int chunk_elements[]);
void calculate_Average(float chunk[], int result[], float average[], int resultsize);
int sizeofResult(int result[]);
int sizeofAverage(float average[]);
void sort_average(float average[],int result[],int chunk_elements[],int avCount);
void write_File(int chunk_elements[], float chunk[],int result[],int averageSize);


int main()
{	
	float myArray[MAX_SIZE];
	float chunk[MAX_SIZE];
	int result[MAX_SIZE];
	float average[MAX_SIZE];
	int chunk_elements[MAX_SIZE];
	int arraySize;
	int resultSize;
	int averageSize;

	FILE *fp;
	fp = fopen("input.txt","r");
	
	arraySize = read_File(myArray,fp);
	
	chunk_Seperator(chunk, result, myArray, average, arraySize, chunk_elements);
	
	resultSize = sizeofResult(result);
	
	calculate_Average(chunk, result, average, resultSize); 

	averageSize = sizeofAverage(average);

	sort_average(average, result, chunk_elements, averageSize);

	write_File(chunk_elements, chunk, result, averageSize);

	fclose(fp);
	return(0);
}
//Dosyadan okuyup myArray'e yazan ve eleman sayısını bulmaya yarayan fonksiyon.
int read_File (float myArray[], FILE *fp)
{
	float k;
	int i = 0;
	while(!feof(fp))
	{
		fscanf(fp,"%f",&k);
		myArray[i] = k;
		++i;	
	}
	myArray[i-1] = 0;
	
  return (i-1);	
}
//Chunk array'ini dolduran fonksiyon.
void chunk_Seperator(float chunk[],int result[],float myArray[],float average[],int arraySize,int chunk_elements[])
{
	int i,j;
	int zeros = 0;
	int count = 0;
	float sum = 0;
	int avCount = 0; 
	int chSize = 0;
	int element = 0;
	
	//Bu döngüyle elemanının sıfır olup olmadığına ve ondan sonraki 2 elemanı kontrol ederek chunk arrayine atama işlemini gerçekleştirdim.
	for(i = 0; i < arraySize; ++i){
      		for(j=0;j<3;j++){
     			if(myArray[i+j] == 0.0) 
					zeros++;
     		}
			//Zeros değişkeni ile arka arkaya kaç tane 0.0 geldiğini kontrol ettim.
      		if(zeros<3){
    			chunk[chSize]=myArray[i];
				sum += myArray[i];	//Sum değişkeni ile chunkın eleman sayısını bularak average hesapladım
    			count++;	//chunk'ın kaç elemanlı olduğunu hesapladım.
				++chSize;	//chunk arrayini doldurmaya yarayan değişken.
				chunk_elements[element] = element;		
				++element;
		}	
		//Eğer 3 tane sıfır arka arkaya gelirse yapılacak işlemler.
		else if (zeros == 3)
		{
			result[avCount] = count;	//Daha sonra kullanabilmek için chunk'ın kaç elemanlı olduğunu bulduğum array.
			avCount++;
			i += 2;
			sum=0;
			count=0;
		}

		zeros=0;
	}
	//Son elemanları da chunk arrayine atabilmek için count değişkenini kontrol ettim.
	if (count != 0){
		result[avCount] = count;
		chunk_elements[element] = element;
		++element;
	}
	
}

//Kaç tane chunk oluştuğunu result arrayinin eleman sayısı ile bulduğum fonksiyon.
int sizeofResult(int result[])
{
	int i;

	for (i = 0; result[i]; ++i)
      ;
	
	return i;
}

//Average arrayini sıralayabilmek için kaç elemanlı olduğunu buldum.Aynı zamanda değişken isimleri karışmaması için.
int sizeofAverage(float average[])
{
	int i;

	for (i = 0; average[i]!= 0; ++i)
		;
	
	return i;
}

//Average hesapladığım fonksiyon.
void calculate_Average(float chunk[], int result[], float average[], int resultsize)
{
	int i, k, m = 0;
	float sum = 0;

	for (k = 0; k < resultsize; ++k)
	{
		for (i = 0; i < result[k]; ++i)
		{
			//printf("resultsize : %d, k : %d icin | chunk[%d] : %f, sum : %f\n", resultsize, k, m, chunk[m], sum);
			sum += chunk[m];
			++m;
		}
		//printf("\n\n");
		average[k] = sum / result[k];
		sum = 0;
		//printf("average[%d] : %f\n", k, average[k]);
	}

}

//Average arrayini küçükten büyüğü sıralama fonksiyonu.
void sort_average(float average[],int result[],int chunk_elements[],int avCount)
{

	int i,j;
	float swap;
	int swap2;
	for (i = 0 ; i < ( avCount - 1 ); i++)
	  {
		for (j = 0 ; j < avCount - i - 1; j++)
		{
		  if (average[j] > average[j+1]) /* For decreasing order use < */
		  {
		    swap       = average[j];
		    average[j]   = average[j+1];
		    average[j+1] = swap;
			
        swap2 = chunk_elements[j];
        chunk_elements[j] = chunk_elements[j+1];
        chunk_elements[j+1] = swap2;			
		  }
		}
	  }
}
//Dosyaya yazmaya yarayan fonksiyon.
void write_File(int chunk_elements[], float chunk[],int result[],int averageSize)
{

	FILE *p;
	int m = 0 ;
	int i= 0;
	int count = 0;
	float element = 0;
	int sort= 0, x = 0;
	int size= 0;
	
	p = fopen("output.txt","w");

	while(count < averageSize){
		
		sort = chunk_elements[count];

		while(m < sort){
			x += result[m];	
			++m;
		}
		
		while(sort >= 0){
			size += result[sort];
			sort--;
		}
		
		for(i = x; i<size; ++i){
			element = chunk[x];
			fprintf(p,"%f ",element);	
			x++;		
		}
		fprintf(p,"\n");	
		
		count++;
		size = 0;
		x = 0;	
		m=0;
	}
	fclose(p);
}



