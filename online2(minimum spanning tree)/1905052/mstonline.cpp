#include<bits/stdc++.h>
using namespace std;
int n,m;//vertex and edge
vector<pair<double,pair<int,int>>>vec;
vector<pair<double,pair<int,int>>>vect;
multiset<pair<int,int>>mul;
multiset<pair<int,int>>mult;
int * parent;
int find_set(int vertex)
{
    if(parent[vertex]==vertex)
    {
        return vertex;
    }
    else
    {
        return find_set(parent[vertex]);
    }
}
int root(int v)
{
    while(parent[v]!=v)
    {
        v=parent[v];
    }
    return v;
}
void union_set(int u,int v)
{
    int l=root(u);
    int r=root(v);
    parent[l]=parent[r];
}
int main()
{
    cin>>n>>m;
    parent=new int[n+1];
    double cos=0.0;
    for(int i=0;i<m;i++)
    {
        int u,v;
        double edg;
        cin>>u>>v>>edg;
        vec.push_back({edg,{u,v}});
        vect.push_back({edg,{u,v}});
        mul.insert({u,v});
        mult.insert({u,v});
        cos+=edg;
    }
    sort(vect.begin(),vect.end(),greater<pair<double,pair<int,int>>>());
    sort(vec.begin(),vec.end());//O(m log m)
    for(int j=0;j<vect.size();j++)
    {
        for(int i=0;i<n;i++)
        {
            parent[i]=i;
        }
        int vertex=0;
        for(int i=0;i<vec.size();i++)//m times
        {
            if(vec[i]==vect[j]||mult.count({vec[i].second.first,vec[i].second.second})==0)
            {
                continue;
            }
            int u=vec[i].second.first;
            int v=vec[i].second.second;
            if(find_set(u)!=find_set(v))//O(log n)
            {
                //cost+=vec[i].first;
                //ans.push_back(vec[i]);
                union_set(u,v);//O(log n)
                vertex++;
            }
        }
        if(vertex==n-1)
        {
            cos-=vect[j].first;
            mul.erase(*mul.find({vect[j].second.first,vect[j].second.second}));
            mult.erase(*mult.find({vect[j].second.first,vect[j].second.second}));
        }
    }
    for(auto x:mult)
    {
        cout<<"("<<x.first<<","<<x.second<<")"<<endl;
    }
    cout<<"Total weight of MST is "<<cos<<endl;
    return 0;
}


