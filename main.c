/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: lenovo
 *
 * Created on November 21, 2016, 4:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


static void count();
static void timeT();
static void insertionSort();
static void selection();
static void ins(int* n, int count);
static void merge(int *A,int *L,int *R,int Lcount,int Rcount);
static void mergeSort(int *A,int n);

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    count();
    timeT();
    insertionSort();
    selection(); 
   int A[] = {6,2,3,1,9,10,15,13,12,17,89}; // creating an array of integers. 
	int i,n, B[200000],C[200000];
        for(i = 0; i < 200000; i++){
            B[i] = rand()%1000;
            C[i] = rand()%1000;
        }
	n = sizeof(B)/sizeof(B[0]);  
        clock_t begin = clock();
        mergeSort(B,n);
        clock_t end = clock();
        clock_t start_insert = clock();
        ins(C, n);
        clock_t end_insert = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        double time_spent_insert = (double)(end_insert - start_insert) / CLOCKS_PER_SEC;
        printf("\n\n\nMerge Sort\n\n");
	for(i = 0;i < n;i++) printf("%d ",C[i]);
        printf("\n\nAmount of CPU time merge sort took for %d elements"
                " = %f Seconds", n, time_spent);
        printf("\n\nAmount of CPU time insertion sort took for %d elements"
                " = %f Seconds", n, time_spent_insert);
    return (EXIT_SUCCESS);
}
            
static void count(){
             //1.2-2 Suppose we are comparing implementations of insertion sort and merge 
    //sort on the same machine. For inputs of size n, insertion sort runs in 
    //8n2 steps, while merge sort runs in 64n lgn steps. For which values 
    //of n does insertion sort beat merge sort?
        long n, i, insertion, merge;
        int counter = 0;
       
    for(n = 1; n <= 1000; n++){
        insertion = 8*pow(n,2);
        merge = 64*n*(log(n)/ log(2));
        if(insertion < merge){
            counter++;
        }
        if(n == 1000){
            printf("\nAmount of steps for insertion sorting 1000 elements = %ld", insertion);
            printf("\nAmount of steps for merge sorting 1000 elements = %ld", merge);
        }
    }
        printf("\nTotal Numbers in n array before merge sort becomes More efficient is %d ", counter);
}

static void timeT(){
    //1.2-3 What is the smallest value of n such that an algorithm whose running
    //time is 100n2 runs faster than an algorithm whose running time is 2n 
    //on the same machine?
    int n;
    for(n = 1; n < 1000; n++){
        if(100*pow(n,2) < pow(2,n)){
            printf("\n\nSmallest n value is %d", n);
            break;
        }
    }
}

void insertionSort(){
    int numbers[10] = {9,2,3,6,7,34,75,4,3,1};
    int key, i , j;
    for(j = 1; j < 10; j++){
        key = numbers[j];
        i = j - 1;
        while(i >= 0 && numbers[i] < key){//previous card > current card
            numbers[i+1] = numbers[i]; //shift across one
            i = i - 1; //go down the list
        }
        numbers[i+1] = key;//while loop breaks insert the card
    }
    printf("\n\nInsertion Sort 10 Int's\n");         
    for(int p = 0; p < 10; p++){
        printf(" %d ", numbers[p]);
    }
}

static  void selection(){
    int numbers[10] = {9,2,3,6,7,34,75,4,3,1};
    int j, i , key, smallest;
    int c = 1;
    for(i = 0; i < 10; i++){
        smallest = 0;
        key = numbers[i];
        for(j = c; j < 10; j++){
            if(key > numbers[j]){
                key = numbers[j];
                smallest = j;
            }
        }
        if(smallest == 0){
            key = numbers[i];
            smallest = i;
        }
            numbers[smallest] = numbers[i];
            numbers[c-1] = key;      
            c++; 
    }
    printf("\n\nMy attempt at selection algorithm\n\n");
    for(int a = 0; a < 10; a++){
        printf(" %d ", numbers[a]);
    }
}

static void ins(int* n, int count){
    int key, j, i;
    for(j = 1; j < count; j++){
        key = n[j];
        i = j - 1;
        while(i >= 0 && n[i] > key){
            n[i+1] = n[i];
            i = i - 1;
        }
        n[i+1] = key;
    }
    }

static void merge(int *M,int *L,int *R,int Lcount,int Rcount) {
	int i,j,k;//i = L subarr index, j = R subarr index, k = M subarr index
	i = 0; j = 0; k =0;
	while(i<Lcount && j< Rcount) {
            M[k++] = (L[i]<R[j]) ? L[i++] : R[j++];//if L < R, K++ = L++ else K++ = R++
        }
	while(i < Lcount) M[k++] = L[i++];
	while(j < Rcount) M[k++] = R[j++];
}

static void mergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; 
        
	mid = n/2; 
	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i]; 
	for(i = mid;i<n;i++) R[i-mid] = A[i]; 

	mergeSort(L,mid);  //sort left half
	mergeSort(R,n-mid);  //sort right half
	merge(A,L,R,mid,n-mid);  //merge the two halves
        free(L);//free allocated memory
        free(R);
}