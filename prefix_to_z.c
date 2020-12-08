#include <stdio.h>
#include <malloc.h>

extern inline int min (const int a, const int b)
{
    return a < b ? a : b;
}

int main()
{
	int n = 0;
	scanf("%d", &n);

	int* pref = malloc(n * sizeof(int));
	int* z = calloc(n, sizeof(int));

	for (int* i = pref; i != pref + n; i++)
		scanf("%d", i);

    for (int i = 1; i < n; i++) 
        if (pref[i])
            z[i - pref[i] + 1] = pref[i];

	*z = n;
	
    if (z[1]) 
        for (int i = 1; i < z[1]; i++)
            z[i + 1] = z[1] - i;

    int t = 0;
	
    for (int i = z[1] + 1; i < n - 1; i++) 
    {
        t = i;
    	
        if (z[i] && !z[i + 1])
        {
	        for (int j = 1; j < z[i] && z[i + j] <= z[j]; j++)
            {
                z[i + j] = min(z[j], z[i] - j);
                t = i + j;
            }
        }
            
        i = t;
    }

	for (int* i = z; i != z + n; i++)
		printf("%d ", *i);

	free(pref); free(z);
	return 0;
}
