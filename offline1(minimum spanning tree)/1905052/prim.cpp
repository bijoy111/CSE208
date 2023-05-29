#include<bits/stdc++.h>
using namespace std;
vector<pair<double,pair<int,int>>>ans;//use for taking the solution
vector<pair<double,int>>vec[10001];//use for taking adjacency list of a vertex
int main()
{
    int n,m;//vertex and edge
    ifstream input("mstinput.txt");
    string str;
    getline(input,str);
    stringstream line(str);
    line>>n>>m;
    //cin>>n>>m;
    while(getline(input,str))
    {
        int u,v;
        double edg;
        stringstream line(str);
        line>>u>>v>>edg;
        vec[u].push_back({edg,v});

        vec[v].push_back({edg,u});
    }
    /*for(int i=0;i<m;i++)
    {
        int u,v;
        double edg;
        cin>>u>>v>>edg;
        if(value<edg)
            value=edg;
        vec[u].push_back({edg,v});

        vec[v].push_back({edg,u});
    }*/
    int *vis=new int[n+1];
    for(int i=0; i<n; i++)
    {
        vis[i]=0;
    }
    int edge=0;
    double cost=0.0;
    priority_queue<pair<double,pair<int,int>>,vector<pair<double,pair<int,int>>>,greater<pair<double,pair<int,int>>>>pq;
    pq.push({0.0,{0,0}});
    while(!pq.empty())//n times
    {
        pair<double,pair<int,int>>p=pq.top();
        pq.pop();//O(log n)
        if(vis[p.second.second]==0)
        {
            vis[p.second.second]=1;
            if(p.first!=0)
            {
                cost += p.first;
                ans.push_back({p.first,{p.second.first,p.second.second}});
            }
            for(int i=0;i<vec[p.second.second].size();i++)//O(m/n)
            {
                int tmp=vec[p.second.second][i].second;
                if(vis[tmp]==0)
                {
                    pq.push({vec[p.second.second][i].first,{p.second.second,vec[p.second.second][i].second}});//O(log n)
                }
            }
        }
    }
    cout<<"Cost of the minimum spanning tree :"<<cost<<endl;
    cout<<"List of edges selected by Prim's:{("<<ans[0].second.first<<","<<ans[0].second.second<<")";
    for(int i=1; i<ans.size(); i++)
    {
        cout<<",("<<ans[i].second.first<<","<<ans[i].second.second<<")";
    }
    cout<<"}"<<endl;
    /*
     total time complexity:O(n log n)+O(m log n)
                          =O(m log n)
                          =O(edge log|vertex|)
     */
    return 0;
}


