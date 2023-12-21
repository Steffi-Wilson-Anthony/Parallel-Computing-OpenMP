# Parallel-Computing-OpenMP
### Length of Longest Increasing Subsequence
### Input: single integer (length of the array)

- We initialize an array with random integers
- To find the length of the required subsequence we use a dynamic programming approach with slight modification.

#### Dynamic Programming Approach:
- We traverse the array in the forward direction starting from index 0.
- The idea is to store the length of longest increasing subsequence for every index i, i.e length of longest increasing subsequence till element at index i.
- The from this array containing the lengths, we find the largest number (longest length).

#### Parallel Programming Approach:
- We divide the array into two halves and operate on them parallelly.
- On the first half the same operation is performed as in dynamic approach.
- On the second half the same thing is done but in reverse direction. This is because the value of length(i) depends on the previous values so doing it in forward direction would lead to a wrong answer. Hence we perfrom the same method in reverse direction.
- The once the length array is calculated we update the second half using the first half. Updation for each index i can be done parallelly since the first half remains unchanged.
- Lastly we find the maximum of all elements in length array using reduction.

#### Efficiency Analysis
- This may not be efficient for small number of elements.
- This could be done done by dividing the array into three subarrays but that wouldn't be efficient since more time will be required for in the process of updation.
- Since this is a dynamic programming problem with dependencies there is limit to the parallizability of the problem. 
