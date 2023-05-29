#include<bits/stdc++.h>
using namespace std;
int **graph;//residual graph
int node;//total node
int **mat;//original graph
int bfs(int source, int sink, int p[])
{
    int *color=new int[node+1];
    for(int i=0;i<node;i++)
    {
        color[i]=0;
    }
    queue<int> q;
    q.push(source);
    color[source]=1;
    p[source]=-1;
    while (!q.empty())
    {
        int vtx = q.front();
        q.pop();
        for (int adj = 0; adj < node; adj++)
        {
            if (color[adj] == 0 && graph[vtx][adj] > 0)
            {
                q.push(adj);
                p[adj] = vtx;
                color[adj]=1;
            }
        }
    }
    if(color[sink]==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Edmonds_karp(int source, int sink)
{
    int *p=new int[node+1];
    int maximum_flow = 0;
    while (bfs(source, sink , p))
    {
        int flow = INT_MAX;
        for (int y = sink; y != source; y = p[y])
        {
            flow = min(flow, graph[p[y]][y]);
        }
        for (int y = sink; y != source; y = p[y])
        {
            graph[p[y]][y] -= flow;
            graph[y][p[y]] += flow;
        }
        maximum_flow += flow;
    }

    return maximum_flow;
}
int main()
{
    int t;
    cin>>t;
    for(int tmp=1;tmp<=t;tmp++)
    {
        int m, n;
        cin >> m >> n;//m = # of man and n = # of woman
        int **man;
        int **woman;
        man = new int *[m + 1];
        for (int i = 0; i < m; i++)
        {
            man[i] = new int[4];
        }
        woman = new int *[n + 1];
        for (int i = 0; i < n; i++)
        {
            woman[i] = new int[4];
        }
        for (int i = 0; i < m; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            man[i][0] = x;
            man[i][1] = y;
            man[i][2] = z;
        }
        for (int i = 0; i < n; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            woman[i][0] = x;
            woman[i][1] = y;
            woman[i][2] = z;
        }
        node = 2 + m + n;
        graph = new int *[node + 1];
        mat = new int *[node + 1];
        for (int i = 0; i <= node + 1; i++)
        {
            graph[i] = new int[node + 1];
            mat[i] = new int[node + 1];
        }
        for (int i = 0; i < node; i++)
        {
            for (int j = 0; j < node; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            graph[0][i] = 1;
        }
        for (int i = m + 1; i <= m + n; i++)
        {
            graph[i][node - 1] = 1;
        }
        for (int i = 0; i < m; i++)//h,age,di
        {
            for (int j = 0; j < n; j++) {
                int t1 = abs(man[i][0] - woman[j][0]);
                int t2 = abs(man[i][1] - woman[j][1]);
                if (t1 <= 12 && t2 <= 5 && man[i][2] == woman[i][2])
                {
                    graph[i + 1][m + 1 + j] = 1;
                }
            }
        }
        for (int i = 0; i < node; i++)
        {
            for (int j = 0; j < node; j++) {
                mat[i][j] = graph[i][j];
            }
        }
        cout <<"Case "<<tmp<<" : "<< Edmonds_karp(0, node - 1) << endl;
        int marriage=0;
        for(int i=1;i<=m;i++)
        {
            for(int j=m+1;j<=m+n;j++)
            {
                if(graph[j][i]>0)
                {
                    marriage++;
                    cout<<"Marriage number:"<<marriage<<" happens between "<<i-1<<" "<<j-(m+1)<<endl;
                }
            }
        }
    }
    return 0;
}
