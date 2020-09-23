#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>

bool dfs (bool** matrix, const int x, const int y, const int sizeup, const int sizehor)
{
    bool check = false;
    
    if (x == sizeup - 1 && y == sizehor - 1)
        return true;
    
    if (y + 1 < sizehor && matrix[x][y + 1] != false)
        check = dfs(matrix, x, y + 1, sizeup, sizehor);
        
    if (check) 
        return true;
    
    else
    {
        if (x - 1 < sizehor && matrix[x - 1][y] != false)
            check = dfs(matrix, x - 1, y, sizeup, sizehor);
            
        if (check)
            return true;
            
        else
        {
            if (x + 1 < sizehor && matrix[x + 1][y] != false)
            check = dfs(matrix, x + 1, y, sizeup, sizehor);
            
            return check; 
        }
    }
}

int main() 
{
    int m = 0, n = 0, k = 0;
    scanf("%d%d%d", &m, &n, &k);
    
    bool** matrix = (bool**)malloc(n * sizeof(bool*));
    
    for (int i = 0; i < n; i++)
        matrix[i] = (bool*)malloc(m * sizeof(bool));
        
    for (int i = 0; i < n; i++)
        for (int q = 0; q < m; q++)
            matrix[i][q] = true;
    
    for (int i = 0; i < k; i++)
    {
        int x = 0, y = 0, d = 0;
        scanf("%d%d%d", &x, &y, &d), x--, y--;
        
        int left = 0;
        
        for (; left < d; left++)
            if (y - left - 1 < 0) 
                break;    
        
        int right = 0;
        
        for (; right < d; right++)
            if (y + right + 1 == m) 
                break;
                
        int up = 0;
        
        for (; up < d; up++)
            if (x - up - 1 < 0) 
                break;
                
        int down = 0;
        
        for (; down < d; down++)
            if (x + down + 1 == 0) 
                break;
                
        // puts("TEST");
                
        for (int q = x - up; q <= x + down; q++)
            for (int c = y - right; c <= y + left; c++)
                if (matrix[q][c] <= hypot(q - x, c - y))
                    matrix[q][c] = false;
    }
    
    bool ans = dfs(matrix, 0, 0, n, m);
    
    printf(ans ? "YES" : "NO");
    
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);    
    return 0;
}
