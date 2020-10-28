#include <stdio.h>
#include <malloc.h>

int main()
{
	int n = 0;
	scanf("%d", &n);

	int* pn = malloc(n * sizeof(int));
	int* ans = calloc(n, sizeof(int));
	*ans = 0;

	for (int* i = pn; i != pn + n; i++)
		scanf("%d", i);

	for (int i = 1; i < n; i++)
		if (pn[i])
			for (int j = pn[i] - 1; j >= 0 && !(ans[i + j]); j--)
				ans[i + j] = j + 1;

	for (int* i = ans; i != ans + n; i++)
		printf("%d ", *i);

	free(pn); free(ans);
	return 0;
}
