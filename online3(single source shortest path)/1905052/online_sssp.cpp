#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>vec[1001];
//int *paren=new int[1001];
int * cost=new int[1001];
int mat[1001][1001];
int n,m;
int *ans=new int[1001];
class graph
{
    int ver;
    map<int,list<int>>edge;
public:
    graph(int ver)
    {
        this->ver=ver;
    }
    void addedge(int u,int v)
    {
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    void bfs(int v)
    {
        int *color=new int[n+1];
        for(int i=0;i<n;i++)
        {
            ans[i]=0;
            color[i]=0;
        }
        int *cos=new int[n+1];
        queue<int>q;
        q.push(v);
        color[v]=1;
        //paren[v]=0;
        cos[v]=0;
        while(!q.empty())
        {
            int vtx=q.front();
            list<int>nbd=edge[vtx];
            q.pop();

            list<int>::iterator i;
            for (i = nbd.begin(); i != nbd.end(); i++) {
                if (color[*i] == 0 && cost[*i]==(cost[vtx]+mat[vtx][*i])) {
                    //paren[*i] = vtx;
                    color[*i] = 1;
                    q.push(*i);
                    ans[*i]=ans[vtx]+1;
                }
            }
        }
    }
};
int main()
{

    cin>>n>>m;
    graph g(n+1);
    for(int i=0;i<m;i++)
    {
        int u,v,edg;
        cin>>u>>v>>edg;
        vec[u].push_back({edg,v});
        vec[v].push_back({edg,u});
        g.addedge(u,v);
        mat[u][v]=edg;
        mat[v][u]=edg;
    }
    int s;
    cin>>s;
    int * visited=new int[n+1];
    int * parent=new int[n+1];
    for(int i=0;i<n;i++)
    {
        cost[i]=INT_MAX;
        visited[i]=0;
    }
    cost[s]=0;
    parent[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({cost[s],s});
    while(!pq.empty())
    {
        pair<int,int>p=pq.top();
        pq.pop();
        int vertex=p.second;
        visited[vertex]=1;
        for(int i=0;i<vec[vertex].size();i++)
        {
            int adj=vec[vertex][i].second;
            if(visited[adj]==0&&(cost[vertex]+vec[vertex][i].first)<cost[adj])
            {
                cost[adj]=cost[vertex]+vec[vertex][i].first;
                parent[adj]=vertex;
                pq.push({cost[adj],adj});
            }
        }
    }
    g.bfs(0);
    cout<<"output are:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<ans[i]<<endl;
    }
}
