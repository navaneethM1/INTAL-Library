#include "intal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int max(int a, int b)
{
	return a > b ? a : b;
}

static int min(int a, unsigned int b)
{
	return a < b ? a : b;
}

static char* mod(char *intal1, char *intal2)
{
	char *temp1;
	char *temp2;
	while(intal_compare(intal1, intal2) != -1)
	{
		temp1 = intal_diff(intal1, intal2);
		temp2 = intal1;
		intal1 = temp1;
		free(temp2);
	}
	return intal1;
}

static char* gcd(char *intal1, char *intal2)
{
	if(intal_compare(intal2, "0") == 0)
	{
		char *res = (char *)malloc((strlen(intal1) + 1) * sizeof(char));
		strcpy(res, intal1);
		free(intal1);
		free(intal2);
		return res;
	}
	char *temp = intal_mod(intal1, intal2);
	free(intal1);
	return gcd(intal2, temp);
}

static void heapify(char **arr, int n, int index)
{
	int k = index;
	char *v = arr[k];
	int heap = 0;
	int cmp;
	while(heap == 0 && 2*k+1 < n)
	{
		int j = 2*k+1;
		if(j < n-1)
		{
			if(intal_compare(arr[j], arr[j+1]) == -1)
			{
				j = j + 1;
			}
		}
		cmp = intal_compare(v, arr[j]);
		if(cmp == 0 || cmp == 1)
		{
			heap = 1;
		}
		else
		{
			arr[k] = arr[j];
			k = j;
		}
	}
	arr[k] = v;
}

static void heap_sort(char **arr, int n)
{
	for(int i = n/2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for(int i = n-1; i > 0; i--)
	{
		char *temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);
	}
}

char* intal_add(const char* intal1, const char* intal2)
{
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);
	int size = max(l1, l2) + 2;
	int res_size = size;

	char sum[size];

	int carry = 0;
	l1--;
	l2--;
	sum[--size] = '\0';
	size--;

	while(l1 >= 0 && l2 >= 0)
	{
		int s = (intal1[l1] - '0') + (intal2[l2] - '0') + carry;
		char dig = (s % 10) + '0';
		carry = s / 10;
		sum[size] = dig;
		l1--;
		l2--;
		size--;
	}

	while(l1 >= 0)
	{
		int s = (intal1[l1] - '0') + carry;
		char dig = (s % 10) + '0';
		carry = s / 10;
		sum[size] = dig;
		l1--;
		size--;
	}

	while(l2 >= 0)
	{
		int s = (intal2[l2] - '0') + carry;
		char dig = (s % 10) + '0';
		carry = s / 10;
		sum[size] = dig;
		l2--;
		size--;
	}

	if(carry != 0)
	{
		char dig = carry + '0';
		sum[size] = dig;
		size--;
	}

	res_size = res_size - (size + 1);
	char *res = (char *)malloc(res_size * sizeof(char));
	strcpy(res, sum + size + 1);

	return res;
}

int intal_compare(const char* intal1, const char* intal2)
{
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);

	if(l1 > l2)
	{
		return 1;
	}

	if(l2 > l1)
	{
		return -1;
	}

	int i = 0;
	while(i < l1 && intal1[i] == intal2[i])
	{
		i++;
	}

	if(i == l1)
	{
		return 0;
	}

	return (intal1[i] - '0') > (intal2[i] - '0') ? 1 : -1;
}

char* intal_diff(const char* intal1, const char* intal2)
{
	char *num1 = (char *)malloc((strlen(intal1) + 1) * sizeof(char));
	strcpy(num1, intal1);
	char *num2 = (char *)malloc((strlen(intal2) + 1) * sizeof(char));
	strcpy(num2, intal2);
	int cmp = intal_compare(num1, num2);

	if(cmp == 0)
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '0';
		res[1] = '\0';
		free(num1);
		free(num2);
		return res;
	}

	if(cmp == -1)
	{
		char *temp = num1;
		num1 = num2;
		num2 = temp;
	}

	int l1 = strlen(num1);
	int l2 = strlen(num2);
	int size = l1 + 1;
	int res_size = size;

	int carry = 0;
	char diff[size];
	l1--;
	l2--;
	diff[--size] = '\0';
	size--;

	while(l2 >= 0)
	{
		int s = (num1[l1] - '0') - (num2[l2] - '0') - carry;
		if(s < 0)
		{
			s = s + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		char dig = s + '0';
		diff[size] = dig;
		l1--;
		l2--;
		size--;
	}

	while(l1 >= 0)
	{
		int s = (num1[l1] - '0') - carry;
		if(s < 0)
		{
			s = s + 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		char dig = s + '0';
		diff[size] = dig;
		l1--;
		size--;
	}
	
	int i = 0;
	while(diff[i] == '0')
	{
		i++;
	}
	
	res_size = res_size - i;
	char *res = (char *)malloc(res_size * sizeof(char));
	strcpy(res, diff + i);
	free(num1);
	free(num2);
	return res;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
	int i, j;
	char* result;
	int l1,l2;
    
	if(0 == intal_compare(intal1, "0") || 0 == intal_compare(intal2,"0"))
	{
		char *res=(char*)malloc(2*sizeof(char));
		res[0]='0';
		res[1]='\0';
		return res; 
    }
	l1 = strlen(intal1);
	l2 = strlen(intal2);
	int len = l1+l2;
    
	int *arr = (int*)calloc(len,sizeof(int));
	for(i=l1-1;i>=0;i--)
	{
		for(j=l2-1;j>=0;j--)
		{
			arr[i+j+1] += (intal1[i]-'0')*(intal2[j]-'0');
		}
	}

	for(i=len-1;i>0;i--)
	{
		arr[i-1] += arr[i]/10;
		arr[i] %= 10;
	}

	if(arr[0]==0)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	result = (char*)malloc((len-i+1)*sizeof(char));
	int index = 0;
	for(;i<len;i++)
	{
		result[index++] = arr[i]+'0';
	}
	result[index] = '\0';
	free(arr);
	return result;
}

char* intal_mod(const char *intal1, const char *intal2)
{
	char *mod_res = (char *)malloc(2 * sizeof(char));
	mod_res[0] = '0';
	mod_res[1] = '\0';
	int n = strlen(intal1);
	char *num2 = (char *)malloc((strlen(intal2)+1) * sizeof(char));
	strcpy(num2, intal2);
	char digit[2];
	char *temp1;
	char *temp2;
	for(int i = 0; i < n; i++)
	{
		digit[0] = intal1[i];
		digit[1] = '\0';
		char *t1 = intal_multiply(mod_res,"10");
		char *t2 = intal_add(t1,digit);
		free(t1);
		temp1 = mod(t2,num2);
		temp2 = mod_res;
		mod_res = temp1;
		free(temp2);
	}
	free(num2);
	return mod_res;
}

char* intal_pow(const char* intal1, unsigned int n)
{
	if(intal_compare(intal1,"0") == 0)
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '0';
		res[1] = '\0';
		return res;
	}
	if(intal_compare(intal1,"1") == 0)
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '1';
		res[1] = '\0';
		return res;
	}
	if(n == 0)
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '1';
		res[1] = '\0';
		return res;
	}
	char *temp = intal_pow(intal1, n/2);
	char *res = intal_multiply(temp, temp);
	free(temp);
	if(n % 2 == 1)
	{
		char *temp1 = intal_multiply(res, intal1);
		char *temp2 = res;
		res = temp1;
		free(temp2);
	}
	return res;
}

char* intal_gcd(const char* intal1, const char* intal2)
{
	if(0 == intal_compare(intal1,"0") && 0 == intal_compare(intal2,"0"))
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '0';
		res[1] = '\0';
		return res;
	}
	if(0 == intal_compare(intal1,"1") || 0 == intal_compare(intal2,"1"))
	{
		char *res = (char *)malloc(2 * sizeof(char));
		res[0] = '1';
		res[1] = '\0';
		return res;
	}
	char *num1 = (char *)malloc((strlen(intal1)+1)*sizeof(char));
	strcpy(num1, intal1);
	char *num2 = (char *)malloc((strlen(intal2)+1)*sizeof(char));
	strcpy(num2, intal2);
	return gcd(num1, num2);
}

char* intal_fibonacci(unsigned int n)
{
	char *a = (char *)malloc(2 * sizeof(char)); a[0] = '0'; a[1] = '\0';
	if(n == 0)
	{
		return a;
	}
	char *b = (char *)malloc(2 * sizeof(char)); b[0] = '1'; b[1] = '\0';
	char *c;
	for(int i = 2; i <= n; i++)
	{
		c = intal_add(a, b);
		free(a);
		a = b;
		b = c;
	}
	free(a);
	return b;
}

char* intal_factorial(unsigned int n)
{
	char *res = (char *)malloc(2 * sizeof(char)); res[0] = '1'; res[1] = '\0';
	if(n <= 1)
	{
		return res;
	}
	char *ith_no = (char *)malloc(2 * sizeof(char)); ith_no[0] = '2'; ith_no[1] = '\0';
	char *temp1;
	char *temp2;
	for(int i = 2; i <= n; i++)
	{
		temp1 = intal_multiply(res, ith_no);
		temp2 = res;
		res = temp1;
		free(temp2);

		temp1 = intal_add(ith_no, "1");
		temp2 = ith_no;
		ith_no = temp1;
		free(temp2);
	}
	free(ith_no);
	return res;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
	if(n-k < k)
	{
		k = n-k;
	}
	char *C[k+1];
	char *temp1;
	char *temp2;
	for(int i = 1; i <= k; i++)
	{
		char *s = (char *)malloc(2*sizeof(char));
		s[0] = '0'; s[1] = '\0';
		C[i] = s;
	}
	char *s = (char *)malloc(2*sizeof(char));
	s[0] = '1'; s[1] = '\0';
	C[0] = s;

	for(int i = 1; i <= n; i++)
	{
		for(int j = min(i, k); j > 0; j--)
		{
			temp1 = intal_add(C[j], C[j-1]);
			temp2 = C[j];
			C[j] = temp1;
			free(temp2);
		}
	}

	char *res = (char *)malloc((strlen(C[k])+1) * sizeof(char));
	strcpy(res, C[k]);
	for(int i = 0; i <= k; i++)
	{
		free(C[i]);
	}
	return res;
}

int intal_max(char **arr, int n)
{
	int ans = 0;
	for(int i = 1; i < n; i++)
	{
		if(intal_compare(arr[i], arr[ans]) == 1)
		{
			ans = i;
		}
	}
	return ans;
}

int intal_min(char **arr, int n)
{
	int ans = 0;
	for(int i = 1; i < n; i++)
	{
		if(intal_compare(arr[i], arr[ans]) == -1)
		{
			ans = i;
		}
	}
	return ans;
}

int intal_search(char **arr, int n, const char* key)
{
	for(int i = 0; i < n; i++)
	{
		if(intal_compare(arr[i], key) == 0)
		{
			return i;
		}
	}
	return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
	int l = 0;
	int h = n-1;
	int res = -1;
	int mid, cmp;
	while(l <= h)
	{
		mid = (l+h)/2;
		cmp = intal_compare(arr[mid], key);
		if(cmp == 0)
		{
			// for finding first occurence
			res = mid;
			h = mid - 1;
		}
		else if(cmp == 1)
		{
			h = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	return res;
}

void intal_sort(char **arr, int n)
{
	heap_sort(arr, n);
}

char* coin_row_problem(char **arr, int n)
{
	char *a = (char *)malloc(1001 * sizeof(char));
	a[0] = '0';
	a[1] = '\0';
	
	char *b = (char *)malloc(1001 * sizeof(char));
	strcpy(b, arr[0]);

	char *option1;
	char *option2;
	int cmp;

	for(int i = 2; i <= n; i++)
	{
		option1 = intal_add(arr[i-1], a);
		option2 = b;
		cmp = intal_compare(option1, option2);
		if(cmp == 1 || cmp == 0)
		{
			strcpy(a, b);
			strcpy(b, option1);
		}
		else
		{
			strcpy(a, b);
		}
		free(option1);
	}
	free(a);
	return b;
}
