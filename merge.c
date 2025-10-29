#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void merge(int arr[], int left, int mid, int right){
    int i ,j, k;
    int n1=mid-left+1;
    int n2=right-mid;
    int*L=(int*)malloc(n1*sizeof(int));
    int*R=(int*)malloc(n2*sizeof(int));
    for (int i = 0; i <n1; i++)
    {
        L[i]=arr[left+1];
    }
    for (int j = 0; j< n2; j++)
    {
        R[j]=arr[mid+1+j];
    }
    i=0,j=0,k=left;
while(i<n1 && j<n2){
    if (L[i]<=R[j]){
        arr[k]=L[i];
        i++;
    }

    else{
        arr[k]=R[j];
        j++;
    }
    k++;
    
}  
while(i<n1){
    arr[k]=L[i];
    i++;
    k++;
}
while(j<n2){
    arr[k]=R[j];
    j++;
    k++;
}
free(L);
free(R);
}
void mergesort(int arr[], int left, int right){
    if (left<right)
    {
        int mid= left+(right-left)/2;
        mergesort(arr,left,mid);
         mergesort(arr,mid+1,right);
         merge(arr, left, mid ,right);

    }
    
}
void generateRandomArray(int arr[], int n){
    for (int i = 0; i < n; i++)
    {
    
    arr[i]=rand() % 100000;
    }
}

int main(){
int n;
printf("Enter the number of elements:");
scanf("%d",&n);;
if (n<5000)
{
   printf("Please enter a value greater than 5000\n");
   return 1;
}
int*arr=(int*)malloc(n*sizeof(int));
if (arr == NULL)
{
    printf("Memory allocation failed\n");
    return 1;
}
generateRandomArray(arr,n);
clock_t start=clock();
for (int i = 0; i < 1000; i++) //1 using for loop 2. random inside3rd without for loop
{
    mergesort(arr,0,n-1);

}
clock_t end =clock();
double time_taken=((double)(end-start))/CLOCKS_PER_SEC/1000.0;
printf("TIME TAKEN TO SORT %d ELEMENTS:%f seconds\n",n,time_taken);
free(arr);
return 0;
}