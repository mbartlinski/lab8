#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void heap(int arr[], int n ,int i)
{
	int large = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[large])
	large = left;

	if (right < n && arr[right] > arr[large])
	large = right;

	if (large != i){
		int tmp = arr[i];
		arr[i] = arr[large];
		arr[large] = tmp;
		heap(arr, n, large);
	}
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{ extraMemoryAllocated = 0;

for (int i = n / 2 - 1; i >= 0; i--)
heap(arr, n, i );

for (int i = n-1; i > 0; i--){
	int tmp = arr[0];
	arr[0] = arr[i];
	arr[i] = tmp;

	heap(arr, i, 0);
}
}


// implement merge sort
void merge( int pData[], int l int m, int r){
	int i, j , k;
	int num1 = m-l+1;
	int num2 = r-m;

	int* L = (int*)malloc(num1 * sizeof(int));
	int* R = (int*)malloc(num2 * sizeof(int));

	for (i = 0; i < num1; i++)
	L[i] = pData[l + i];
	for (j = 0; j < num2; j++)
	R[i] = pData[m+1+j];
	
	i = 0;
	j = 0;
	k = 0;
	while( i < num1 &&  j < num2){
		if (L[i] <= R[j]){
			pData [k] = L[i];
			i++;
		}
		else{
			pData[k] = R[j];
			j++;
		}
		k++;
	}
	while ( i < num1){
		pData[k] = L[i];
		i++;
		k++;

	}
	while ( j < num2){
		pData[k] = R[j];
		j++;
		k++;
	}
	extraMemoryAllocated += num1 * sizeof(int) + num2 * sizeof(int);

	free(L);
	free(R);

}
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int m, int r)
{
	if (l < r){
		int m = l + (r - l) / 2;
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		merge(pData, l, m, r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	int memcpy();
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}