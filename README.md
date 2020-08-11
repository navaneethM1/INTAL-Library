# Introduction
Intal is an integer(zero or positive) of arbitrary number of digits. It is represented as a string of digits from '0' through '9' terminated with the null character. Intal is different from an integer(in general) because intal values are a representation of the value. It is not the value of the integer itself. It is different from integer data types supported by C in terms of the manner in which they are stored. C stores integers in 32bit word whereas intal is stored as a string of digits(in Big Endian manner) where each digit occupies 8bits. Also in the case of integer data types, bit wise logic is used directly by the ALU to perform operations like addition subtraction and others. But with intal being represented as string, the operations cannot be performed directly, instead they should be defined by us. Another difference is that the in-built integer data type cannot handle very large integers(ie integers greater than 2147483647) whereas the intal can handle integers having arbitrary number of digits(here restricted to 1000). 

The major application of intal is that it can be used to  represent very large numbers and carry out mathematical operations of addition, subtraction and others on very large numbers with very less chances of error which otherwise cannot be performed by the int data type provided by C.

# Comile and run
```
gcc intal_sampletest.c PES1201801597.c
./a.out
```

# Approach
1. intal_add:
Starting from the last digit of both the intals, the addition of digits is done and the mod is taken with 10 and stored in the result. The carry is propagated to the next digit as value of addition divided by 10.

2. intal_compare:
If string length of intal1 is lesser than intal2's, then intal1 is lesser than intal2. If string length of intal2 is lesser than intal1, then intal2 is lesser than intal1. If both the string lengths are same, then the digits are checked from left to right in each intal and whichever digit is greater, then that is the higher of the two. If every digit is found same, then the two intals are equal.

3. intal_diff:
Initially, if both the numbers are equal, then the difference is 0. Immediately after this, the arrangement is done such that num1 is larger value and num2 is the smaller value. num2 is then iterated from end along with num1, and subtraction of corresponding digits along with carry is done. 10 is added to represent borrow and carry set to 1 if the subtracted value is negative. The same process continues to happen till the beginning of num1.

4. intal_multiply:
The approach to this problem involves storing the intermediate products of each digit of intal1 being multiplied with intal2 in an integer array at the appropriate place. Each time a new product is calculated it is added to the previous value which was already present in the integer arrayAfter this, integer array is iterated from the end to propogate the carry and help store single digit in the product.

5. intal_mod:
The approach followed in this problem is long division. Initially, the mod_res variable is initialised to "0". After that, intal1 in iterated from left to right - each time the result (mod_res * 10 + intal[i])%intal2 is computed. This requires a call to static function named "mod" which repeatedly subtracts intal2 from (mod_res * 10 + intal[i]) until it is less than intal2. The time complexity of this algorithm is O(string length of intal1) or O(log10(intal1)).

6. intal_pow:
The decrease and conquer approach is used. pow(a, 0) is 1 and pow(a, n) is pow(a, n/2) multiplied by itself and optionally multiplied with a if n is odd.

7. intal_gcd:
Euclid's algorithm to find GCD of 2 numbers is used. GCD(a, 0) is a and GCD(a, b) is GCD(b, a MOD b).

8. intal_fibonacci:
The approach used here is based on the fact that the next fibonacci number is the sum of previous two fibonacci numbers. fibonacci(0) being 0 and fibonacci(1) being 1. A sliding window of 3 is thus maintained.

9. intal_factorial:
The factorial of a number is the product of all the numbers from 1 to the given number. factorial(0) being 1.

10. intal_bincoeff:
Since C(n,k) = C(n,n-k), k is reassigned to n-k if n-k is smaller than k for faster computation of the binomial coefficient. The approach uses the Pascal's Identity - C(n,k) = C(n-1,k) + C(n-1,k-1). DP is used as there is overlapping subproblems and optimal substructure. A window of size k is sufficient if the calculations of C(n,k) for a particular "n" is done from the end of the previous n's values(which is the DP's topological order). In order to not calculate unwanted(for the given input) values, the inner for loop is run only from min(i,k) to 1. After each iteration of the outer loop(from 1 to n), a row of the Pascal's triangle will be available.

11. intal_max:
Initially, the maximum element's index is assumed to be 0. Then an iteration through the elements starting from index 1 till the end of array is done and if a number greater than the present maximum is found, the index is updated to the present maximum's index.

12. intal_min:
Initially, the minimum element's index is assumed to be 0. Then an iteration through the elements starting from index 1 till the end of array is done and if a number lesser than the present minimum is found, the index is updated to the present minimum's index.

13. intal_search:
A linear search is done through the array elements. If the element is found, using the intal_compare method, then its index is returned. Else at the end, -1 is returned.

14. intal_binsearch:
Binary search expects the input array to be sorted. The element at the middle is checked. If it is equal to the key being searched, then the mid index is stored in the result variable and searching continues in the low to mid-1 range for finding first occurence. If middle element is greater than key, then high is made mid-1. If middle element is lesser than key, then low is made mid+1.

15. intal_sort:
As per the requirement mentioned, the sorting has to happen in nlogn time and in-place. For this, heap sort is used. There are 2 steps in this sort. One is max heap construction and the second step being repeated deletion of top element from heap and heapifying the root. Repeated deletion here means interchanging the last and top values of the heap. The heap is maintained as an array.

16. coin_row_problem:
The basic logic is that each element can either be a part of the final maximum amount of money or it is not. If it is a part, then the preceeding element should not be picked. If it is not a part, then the preceeding element can be picked. The recurrence relation for the maximum amount picked is amt(n) = max(amt(n-2)+C[n-1], amt(n-1)) where "n" is the number of coins and C is the array having coin values. This like the binomial coefficient problem has overlapping subproblems and optimal substructure. Hence DP is used and a sliding window of 2 is used. The third variable was not used as 2 variables were sufficient.

# Future work
The existing library created can be easily extended by including additional functionalities such as LCM, P(n, r), integer to roman conversion, TSP problem with large distances and probably list could go on endlessly. Such a complete library, when built without any errors, would prove to be very useful for performing mathematical operations involving large numbers. Coming to the question of handling integers of arbitrary length, I think that we can handle them if we use the temp1, temp2 method of freeing variables(mentioned in the doc file) instead of mallocing a fixed size of 1001 and strcpying to the same location. Further, in cases like addition, multiplication, subtraction where we know the maximum number of digits in the resulting answer, we can malloc those many bytes precisely. That is how I would approach the problem of handling integers of arbitrary lengths not restricted to a particular length.
