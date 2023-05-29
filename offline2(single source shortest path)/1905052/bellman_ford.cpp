#include<bits/stdc++.h>
using namespace std;
vector<pair<int,pair<int,int>>>edge;
#define int long long
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,edg;
        cin>>u>>v>>edg;
        edge.push_back({edg,{u,v}});
    }
    int s,d;
    cin>>s>>d;
    int * cost=new int[n+1];
    int * parent=new int[n+1];
    for(int i=0;i<n;i++)
    {
        cost[i]=9223372036854775807;
    }
    cost[s]=0;
    parent[s]=0;
    for(int i=1;i<n;i++)//n times
    {
        for(int j=0;j<edge.size();j++)//m times
        {
            int ed=edge[j].first;
            int x=edge[j].second.first;
            int y=edge[j].second.second;
            if(cost[x]!=9223372036854775807&&cost[y]>(cost[x]+ed))
            {
                cost[y]=cost[x]+ed;
                parent[y]=x;
            }
        }
    }
    for(int j=0;j<edge.size();j++)
    {
        int ed=edge[j].first;
        int x=edge[j].second.first;
        int y=edge[j].second.second;
        if(cost[x]!=9223372036854775807&&cost[y]>(cost[x]+ed))
        {
            cout<<"The graph contains a negative cycle"<<endl;
            return 0;
        }
    }
    cout<<"The graph does not contain a negative cycle"<<endl;
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
/*total time complexity is O(mn)
                                        =O(edge *vertex)
*/
