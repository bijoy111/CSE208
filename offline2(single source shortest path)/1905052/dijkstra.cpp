#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>vec[1001];
#define int long long
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,edg;
        cin>>u>>v>>edg;
        vec[u].push_back({edg,v});
    }
    int s,d;
    cin>>s>>d;
    int * cost=new int[n+1];
    int * visited=new int[n+1];
    int * parent=new int[n+1];
    for(int i=0;i<n;i++)
    {
        cost[i]=9223372036854775807;
        visited[i]=0;
    }
    cost[s]=0;
    parent[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({cost[s],s});
    while(!pq.empty())//n times
    {
        pair<int,int>p=pq.top();
        pq.pop();//O(log n)
        int vertex=p.second;
        visited[vertex]=1;
        for(int i=0;i<vec[vertex].size();i++)// m/n times
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
    cout<<"Shortest path cost: "<<cost[d]<<endl;
    vector<int>ans;
    while(parent[d]!=d)
    {
        ans.push_back(d);
        d=parent[d];
    }
    ans.push_back(s);
    for(int i=ans.size()-1;i>0;i--)
    {
        cout<<ans[i]<<"->";
    }
    cout<<ans[0]<<endl;
}
/*total time complexity is O(m log n)
                                        =O(edge log vertex)
*/


