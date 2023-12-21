#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int longest_subsequence_length(int arr[], int n);

int main() {
    int s, i;

    // number of elements
    scanf("%d",&s);

    // initializing the array with random integers
    int arr[s];
    for(i=0;i<s;i++){
    	arr[i] = rand()%1000+1;
    }

    // printing the input array
    printf("Input Array:\n");
    for(i=0;i<s;i++){
    	printf("%d ",arr[i]);
    }
    printf("\n");

    int n = sizeof(arr) / sizeof(arr[0]);
    double start_time = omp_get_wtime();

    int l = longest_subsequence_length(arr, n);

    double end_time = omp_get_wtime();

    printf("Longest Increasing subsequence Length %d\n", l);
    printf("Execution time: %lf\n",end_time-start_time);
    return 0;
}

int longest_subsequence_length(int arr[], int n) {
    int len[n];
    int max_length = -1;
    int i, k, v;

    // Initialize the len array with 1
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        len[i] = 1;
    }

    // Compute the length of the longest subsequence for each element
    #pragma omp sections private(i, k)
    {
        // First half
        #pragma omp section
        for (i = 0; i < n/2; i++) {
            for (k = 0; k < i; k++) {
                if (arr[k] < arr[i]) {
                    // Use atomic operation to avoid race condition
                    // #pragma omp atomic write
                    len[i] = (len[i] > len[k] + 1) ? len[i] : (len[k] + 1);
                }
            }
        }

        // Second half
        #pragma omp section
        for (i = n-1; i >= n/2; i--) {
            for (k = n-1; k > i; k--) {
                if (arr[k] > arr[i]) {
                    // Use atomic operation to avoid race condition
                    // #pragma omp atomic write
                    len[i] = (len[i] > len[k] + 1) ? len[i] : (len[k] + 1);
                }
            }
        }
    }

    // Updating the second half of the array using the first half
    #pragma omp parallel for private(i, v, k)
    for(i=n/2;i<n;i++){
        v = len[i];
        for(k=0;k<n/2;k++){
            if(arr[i]>arr[k])
            {
                len[i] = (len[i] > len[k] + v) ? len[i] : (len[k] + v);
            }
        }
    }

    // Find the maximum length among all elements
    #pragma omp parallel for reduction(max: max_length)
    for (i = 0; i < n; i++) {
        if (len[i] > max_length)
            max_length = len[i];
    }

    return max_length;
}