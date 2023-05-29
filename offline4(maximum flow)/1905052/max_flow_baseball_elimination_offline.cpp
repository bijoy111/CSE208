#include<bits/stdc++.h>
using namespace std;
int **graph;//it will create the required matrix for the ford-fulkerson algorithm
int node;//it will take the total nodes

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

int fac(int x)
{
    int multiply=1;
    while(x!=1)
    {
        multiply= multiply * x;
        x--;
    }
    return multiply;
}
int main()
{
    int n;//# of teams
    cin >> n;
    string *str = new string[n + 5];//it will take the team name
    int *win = new int[n + 5];
    int *loss = new int[n + 5];
    int *left = new int[n + 5];
    int **mat;//it will take the remaining game between two teams
    mat = new int *[n + 5];
    for (int i = 1; i <= n; i++)
    {
        mat[i] = new int[n + 5];
    }
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        int w, l, lef;
        cin >> w >> l >> lef;
        str[i] = s;
        win[i] = w;
        loss[i] = l;
        left[i] = lef;
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            mat[i][j] = x;
        }
    }
    int com = fac(n - 1) / (2 * fac(n-3));//# of node using combination with two teams from n teams or it will calculate (n-1)c2
    node = 2 + (n - 1) + com;//total nodes=source=1,destination=1,combination of n-1 teams to play each other is com, and n-1 teams
    graph = new int *[node + 1];
    for (int i = 0; i < node; i++)
    {
        graph[i] = new int[node + 1];
    }
    for(int k=1;k<=n;k++)//take all the team from 1 to n and check is this team will be eliminated
    {
        for (int i = 0; i < node; i++)
        {
            for (int j = 0; j < node; j++)
            {
                graph[i][j] = 0;//initially make flow from one node to another 0
            }
        }
        int l = 1;//it will use to calculate the flow from source to the node which we get from combination
        int a, b;//it will use to calculate the flow from the nodes (which indicate the match between two teams) to the node(which indicate the teams)
        a = 1;
        for (int i = 1; i <= n; i++)
        {
            if (i == k)
            {
                continue;
            }
            b = a + 1;
            for (int j = i + 1; j <= n; j++)
            {
                if (j == k)
                {
                    continue;
                }
                graph[0][l] = mat[i][j];
                graph[l][a + com] = INT_MAX;
                graph[l][b + com] = INT_MAX;
                l++;
                b++;
            }
            a++;
        }
        int var=0;//it is use to see if there is a team that has already winning match much than the given team can win
        set<int>te;
        a = 1;
        for (int i = 1; i <= n; i++)
        {
            if (i == k)
            {
                continue;
            }
            graph[a + com][node - 1] = win[k] + left[k] - win[i];
            if(graph[a + com][node - 1]<0)
            {
                te.insert(i);
                var=i;
            }
            a++;
        }
        int ans1=0;
        for(int i=0;i<node;i++)
        {
            ans1+=graph[0][i];
        }
        int ans2=Edmonds_karp(0, node-1);
        if(ans1!=ans2||var!=0)
        {
            cout<<str[k]<<" is eliminated"<<endl;
            cout<<"They can win at most "<<win[k]<<"+"<<left[k]<<" = "<<win[k]+left[k]<<" games."<<endl;
            int si=1;
            for(int i=1;i<=n;i++)
            {
                if(i==k)
                    continue;
                for(int j=i+1;j<=n;j++)
                {
                    if(j==k)
                        continue;
                    if(graph[0][si]!=0)
                    {
                        te.insert(i);
                        te.insert(j);
                    }
                    si++;
                }
                if(te.size()>0)
                {
                    break;
                }
            }
            a = 1;
            for (int i = 1; i <= n; i++)
            {
                if (i == k)
                {
                    continue;
                }
                if(graph[a + com][node - 1]==0)
                {
                    te.insert(i);
                }
                a++;
            }
            int ans[te.size()];
            int m=0;
            for(auto x:te)
            {
                ans[m++]=x;
            }
            int totalgames=0;
            int eachother=0;
            for(int i=0;i<m;i++)
            {
                totalgames+=win[ans[i]];
            }
            for(int i=0;i<m;i++)
            {
                for(int j=i+1;j<m;j++)
                {
                    eachother+=mat[ans[i]][ans[j]];
                }
            }
            if(var!=0)
            {
                cout<<str[var];
                cout<<" has won a total of "<<win[var]<<" games"<<endl;
                cout<<"They play each other "<<0<<" games"<<endl;
                cout<<"So on averge, each of the teams in this group  wins "<<win[var]<<"/"<<1<<" = "<<win[var]<<" games"<<endl;
                cout<<endl;
                cout<<endl;
            }
            else
            {
                int i;
                for(i=0;i<m-1;i++)
                {
                    cout<<str[ans[i]]<<",";
                }
                cout << str[ans[m - 1]];
                cout << " have won a total of " << totalgames << " games" << endl;
                cout << "They play each other " << eachother << " games" << endl;
                cout << "So on averge, each of the teams in this group  wins  "<<(totalgames + eachother)<<"/"<<te.size()<<" = "
                     << (1.0 * (totalgames + eachother)) / (1.0 * te.size()) << " games" << endl;
                cout << endl;
                cout << endl;
            }
        }

    }
}
