// C++ program to perform TimSort. 
#include<bits/stdc++.h> 
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <time.h>
using namespace std; 
const int RUN = 50; 
const int numThreads = 32;

// this function sorts array from left index to 
// to right index which is of size atmost RUN 
void insertionSort(int arr[], int left, int right) 
{ 
	for (int i = left + 1; i <= right; i++) 
	{ 
		int temp = arr[i]; 
		int j = i - 1; 
		while (arr[j] > temp && j >= left) 
		{ 
			arr[j+1] = arr[j]; 
			j--; 
		} 
		arr[j+1] = temp; 
	} 
} 

// merge function merges the sorted runs 
void merge(int arr[], int l, int m, int r) 
{ 
	// original array is broken in two parts 
	// left and right array 
	int len1 = m - l + 1, len2 = r - m; 
	int left[len1], right[len2]; 
	for (int i = 0; i < len1; i++) 
		left[i] = arr[l + i]; 
	for (int i = 0; i < len2; i++) 
		right[i] = arr[m + 1 + i]; 

	int i = 0; 
	int j = 0; 
	int k = l; 

	// after comparing, we merge those two array 
	// in larger sub array 
	while (i < len1 && j < len2) 
	{ 
		if (left[i] <= right[j]) 
		{ 
			arr[k] = left[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = right[j]; 
			j++; 
		} 
		k++; 
	} 

	// copy remaining elements of left, if any 
	while (i < len1) 
	{ 
		arr[k] = left[i]; 
		k++; 
		i++; 
	} 

	// copy remaining element of right, if any 
	while (j < len2) 
	{ 
		arr[k] = right[j]; 
		k++; 
		j++; 
	} 
} 

// iterative Timsort function to sort the 
// array[0...n-1] (similar to merge sort) 
void timSort(int arr[], int n) 
{ 
	// Sort individual subarrays of size RUN  
	omp_set_num_threads(numThreads);
	#pragma omp parallel
	{	
		#pragma omp for
		for (int i = 0; i < n; i+=RUN) 
			insertionSort(arr, i, min((i+(RUN - 1)), (n-1))); 

		// start merging from size RUN (or 32). It will merge 
		// to form size 64, then 128, 256 and so on .... 
		for (int size = RUN; size < n; size = 2*size) 
		{ 
			// pick starting point of left sub array. We 
			// are going to merge arr[left..left+size-1] 
			// and arr[left+size, left+2*size-1] 
			// After every merge, we increase left by 2*size
			#pragma omp for
			for (int left = 0; left < n; left += 2*size) 
			{ 
				// find ending point of left sub array 
				// mid+1 is starting point of right sub array 
				int mid = left + size - 1; 
				int right = min((left + 2*size - 1), (n-1)); 
				//printf('');
				// merge sub array arr[left.....mid] & 
				// arr[mid+1....right]
				merge(arr, left, mid, right); 					
			} 
		} 
	}
} 

// utility function to print the Array 
void printArray(int arr[], int n) 
{ 
	for (int i = 0; i < n; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

void retornaVetorContrario(int *a, int tam){
	int aux=tam-1;
	for(int i=0;i<tam;i++){
		a[i]=aux;
		aux=aux-1;
	}
}

void retornaAleatorio(int *a, int tam){
	int auxvet[tam]={629,486,29,610,80,247,100,493,497,590,657,307,611,77,823,532,615,727,675,407,748,111,
	825,443,760,678,895,549,681,71,921,952,176,66,185,926,50,546,605,215,459,36,400,408,166,404,775,627,
	877,591,689,855,604,686,290,575,226,238,8,708,374,959,419,971,44,600,659,393,105,112,4,283,606,613,445,
	6,192,48,985,874,992,19,846,988,869,626,909,205,946,133,630,260,640,897,866,284,410,132,470,200,187,520,
	152,907,352,10,770,150,843,249,949,584,70,494,157,59,201,12,829,828,142,645,43,30,495,86,702,740,777,561,
	210,799,121,824,559,197,514,538,485,839,160,562,598,685,526,469,104,994,311,650,826,57,798,593,417,961,322,
	51,525,46,632,444,542,489,439,148,586,502,463,882,455,318,891,535,804,620,636,976,487,870,211,665,700,0,848,
	420,153,117,298,261,115,243,38,938,145,566,884,370,60,524,924,536,541,989,385,392,776,320,707,755,297,670,345,
	570,127,21,805,281,709,136,540,138,815,126,648,580,623,98,426,380,336,467,900,637,78,116,108,556,177,423,892,481,
	596,594,774,706,58,987,139,844,271,507,545,37,842,440,96,395,381,68,7,434,367,741,358,204,879,792,448,608,306,56,
	930,356,256,739,696,172,353,114,25,106,418,906,880,329,252,227,674,432,296,773,818,180,369,498,915,780,134,386,671,
	223,178,64,73,717,564,782,849,209,174,758,34,653,716,519,841,194,847,458,958,836,62,53,438,683,24,310,513,362,321,790,
	482,565,966,995,529,669,161,625,788,628,781,903,960,819,93,923,699,330,92,682,743,123,797,315,151,587,237,751,231,768,
	347,257,103,63,582,13,515,119,624,430,317,646,99,795,973,39,704,451,970,742,935,692,22,794,899,861,668,552,437,266,913,
	779,377,999,449,239,303,476,471,251,323,188,522,216,97,198,416,982,91,441,856,860,738,896,655,835,592,510,265,33,190,383,
	355,551,101,361,156,601,341,295,868,725,986,339,17,262,128,422,644,346,852,676,567,756,932,875,983,908,697,918,778,997,881,
	537,936,278,23,503,229,737,810,581,767,344,220,67,478,391,162,955,766,948,288,454,505,851,695,141,401,679,389,769,944,579,450,
	199,730,759,523,5,820,754,508,732,714,789,763,76,402,622,384,862,814,991,332,761,335,399,375,617,928,939,394,490,635,558,649,409,
	639,509,984,548,378,956,642,512,728,517,878,521,722,809,749,904,893,301,488,242,125,175,360,715,14,931,528,589,951,518,993,480,666,
	543,397,250,858,916,184,720,929,585,980,662,428,414,750,285,325,816,2,289,396,415,690,466,269,179,163,859,660,573,511,757,998,808,912,
	736,403,853,72,270,813,667,181,186,947,28,333,572,854,460,941,831,975,248,977,807,864,527,802,373,762,603,890,81,922,506,694,191,170,
	784,272,274,129,291,245,442,857,553,279,462,83,698,718,734,26,713,801,236,61,840,850,427,597,158,811,412,654,863,222,342,616,168,94,
	232,969,224,189,687,576,118,724,838,496,254,431,544,664,406,304,940,316,371,349,195,691,817,452,783,661,90,475,338,365,950,275,350,
	803,219,54,638,159,154,711,47,491,107,472,867,723,705,203,299,483,547,474,539,75,925,343,354,473,588,914,516,49,435,633,964,337,
	554,786,207,981,979,583,771,641,571,765,499,887,382,398,710,334,651,569,822,957,212,193,85,680,684,595,124,468,171,719,120,15,
	656,55,721,791,996,555,894,164,82,233,568,429,693,477,110,331,963,830,182,729,368,388,793,953,122,990,501,155,833,574,563,910,
	745,27,436,812,255,277,911,424,313,618,934,213,45,658,883,764,461,457,1,965,557,221,144,20,968,52,88,492,11,465,413,208,865,
	827,902,228,919,834,35,945,218,772,293,196,712,258,726,217,484,109,183,328,530,785,264,533,319,832,137,837,359,230,147,479,
	294,74,3,433,500,967,731,240,974,263,898,927,84,885,962,796,259,954,800,787,169,327,292,143,379,747,267,173,390,943,464,
	405,348,31,560,872,206,753,733,302,65,421,324,599,309,280,387,234,602,453,672,364,351,901,40,372,282,376,531,357,363,
	917,688,871,621,619,845,202,241,446,214,942,889,504,32,703,326,95,577,920,308,411,614,9,165,16,225,905,578,550,888,
	113,673,631,79,312,149,886,167,140,652,135,41,456,752,253,663,268,735,89,340,821,425,366,18,287,876,643,273,42,607,
	978,244,246,305,746,937,806,235,276,102,612,701,744,314,87,131,972,69,146,130,933,873,647,300,609,634,534,677,447,286};	
	for(int i=0;i<tam;i++){
		a[i]=auxvet[i];
	}
}

// Driver program to test above function 
int main(int numargs, char *arg[]) 
{ 
	double start, end, tempo;
	double segundosTotal;
	
	int TAM = 1000;
	int arr[TAM];

	int escolha=atoi (arg[1]);
	if(escolha==0){
		retornaAleatorio(arr, TAM);
		printf("Aleatório\n");
	}else{
		retornaVetorContrario(arr, TAM);
		printf("Inverso\n");
	}
 
	int n = sizeof(arr)/sizeof(arr[0]);
	//printf("Given Array is\n"); 
	//printArray(arr, n);
	
	//clock_t startTime = clock();
	start = omp_get_wtime();
	{
	timSort(arr, n); 
	}
	end = omp_get_wtime();
	//segundosTotal = (clock() - startTime)/(double)(CLOCKS_PER_SEC);
	
	tempo = end-start;
	//printf("%f s lib ctime\n", segundosTotal);
	printf("%f s lib openmp\n", tempo);
	//printf("After Sorting Array is\n"); 
	//printArray(arr, n);
	return 0; 
} 

