#include <stdio.h>

#define MAX 1000

int adj[MAX][MAX];
int visited[MAX];
int n, m;

// -------- DFS --------
void dfs(int v)
{
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++)
    {
        if (adj[v][i] == 1 && visited[i] == 0)
        {
            dfs(i);
        }
    }
}

// -------- BFS --------
void bfs(int src)
{
    int queue[MAX];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[src] = 1;
    queue[rear++] = src;

    while (front < rear)
    {
        int v = queue[front++];
        printf("%d ", v);

        for (int i = 0; i < n; i++)
        {
            if (adj[v][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    // initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    int u, v;

    // read edges (directed)
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    int src;
    scanf("%d", &src);

    // ---- BFS ----
    bfs(src);
    printf("\n");

    // ---- DFS ----
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    dfs(src);
    printf("\n");

    return 0;
}