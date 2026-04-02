#include <stdio.h>

int main()
{
    int n;

    // Read number of vertices
    scanf("%d", &n);

    int adj[n][n];

    // Read adjacency matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    // Convert to adjacency list
    for (int i = 0; i < n; i++)
    {
        printf("%d", i);

        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] == 1)
            {
                printf(" %d", j);
            }
        }

        printf("\n");
    }

    return 0;
}