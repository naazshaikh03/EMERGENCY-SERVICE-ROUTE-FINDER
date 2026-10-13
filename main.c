#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 999999

int graph[MAX][MAX];
char location[MAX][30];
int n;

void dijkstra(int source, int dist[], int parent[])
{
    int visited[MAX] = {0};
    int i, j, u, min;

    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (i = 0; i < n; i++)
    {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (graph[u][j] >= 0 &&
                graph[u][j] != INF &&
                !visited[j] &&
                dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }
}

void showPath(int parent[], int dest)
{
    if (parent[dest] == -1)
    {
        printf("%s", location[dest]);
        return;
    }

    showPath(parent, parent[dest]);
    printf(" -> %s", location[dest]);
}

int main()
{
    int i, j, choice;
    int source = 0, dest;
    int dist[MAX], parent[MAX];
    int weight;

    printf("=== EMERGENCY SERVICE ROUTE FINDER ===\n");

    printf("Enter number of locations (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of locations!\n");
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter location %d name (no spaces): ", i + 1);
        scanf("%29s", location[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    printf("\nEnter number of roads: ");
    scanf("%d", &weight);

    if (weight < 0 || weight > n * (n - 1))
    {
        printf("Invalid number of roads!\n");
        return 0;
    }

    for (i = 0; i < weight; i++)
    {
        int u, v;

        printf("Road %d (from to distance): ", i + 1);
        scanf("%d %d %d", &u, &v, &j);

        if (u < 1 || u > n || v < 1 || v > n || u == v || j < 0)
        {
            printf("Invalid road or negative distance! Try again.\n");
            i--;
            continue;
        }

        graph[u - 1][v - 1] = j;
        graph[v - 1][u - 1] = j;
    }

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Change source station\n");
        printf("2. Find route to destination\n");
        printf("3. Display distance table\n");
        printf("4. Display graph\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 5)
            break;

        if (choice == 1)
        {
            printf("Enter source location number (1-%d): ", n);
            scanf("%d", &source);

            if (source < 1 || source > n)
            {
                printf("Invalid source!\n");
                source = 1;
            }
            else
                source--;

        }
        else if (choice == 2)
        {
            printf("\nEnter destination number (1-%d): ", n);
            scanf("%d", &dest);

            if (dest < 1 || dest > n)
            {
                printf("Invalid destination!\n");
                continue;
            }

            dest--;
            dijkstra(source, dist, parent);

            if (dist[dest] == INF)
            {
                printf("No route available to %s.\n",
                       location[dest]);
            }
            else
            {
                printf("Shortest distance: %d\n", dist[dest]);
                printf("Best route: ");
                showPath(parent, dest);
                printf("\n");
            }
        }
        else if (choice == 3)
        {
            dijkstra(source, dist, parent);

            printf("\nSource: %s\n", location[source]);
            printf("%-20s %-15s\n", "Location", "Distance");

            for (i = 0; i < n; i++)
            {
                if (dist[i] == INF)
                    printf("%-20s %-15s\n",
                           location[i], "INF");
                else
                    printf("%-20s %-15d\n",
                           location[i], dist[i]);
            }
        }
        else if (choice == 4)
        {
            printf("\nAdjacency Matrix:\n");
            printf("%-12s", "");

            for (i = 0; i < n; i++)
                printf("%-12s", location[i]);

            printf("\n");

            for (i = 0; i < n; i++)
            {
                printf("%-12s", location[i]);

                for (j = 0; j < n; j++)
                {
                    if (graph[i][j] == INF)
                        printf("%-12s", "INF");
                    else
                        printf("%-12d", graph[i][j]);
                }

                printf("\n");
            }
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    printf("\nThank you for using the Route Finder!\n");
    return 0;
}
