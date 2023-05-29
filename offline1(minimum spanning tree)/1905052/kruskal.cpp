#include<bits/stdc++.h>
using namespace std;
int n,m;//vertex and edge
vector<pair<double,pair<int,int>>>vec;//use for solving the problem
vector<pair<double,pair<int,int>>>ans;//use for taking the solution
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
        //parent[v]=parent[parent[v]];
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
    ifstream input("mstinput.txt");
    string str;
    getline(input,str);
    stringstream line(str);
    line>>n>>m;
    //cin>>n>>m;
    parent=new int[n+1];
    for(int i=0;i<n;i++)
    {
        parent[i]=i;
    }
    while(getline(input,str))
    {
        int u,v;
        double edg;
        stringstream line(str);
        line>>u>>v>>edg;
        vec.push_back({edg,{u,v}});
    }
    /*for(int i=0;i<m;i++)
    {
        int u,v;
        float edg;
        cin>>u>>v>>edg;
        vec.push_back({edg,{u,v}});
    }*/
    sort(vec.begin(),vec.end());//O(m log m)
    double cost=0.0;
    for(int i=0;i<vec.size();i++)//m times
    {
        int u=vec[i].second.first;
        int v=vec[i].second.second;
        if(find_set(u)!=find_set(v))//O(log n)
        {
            cost+=vec[i].first;
            ans.push_back(vec[i]);
            union_set(u,v);//O(log n)
        }
    }
    cout<<"Cost of the minimum spanning tree :"<<cost<<endl;
    cout<<"List of edges selected by Kruskal's:{("<<ans[0].second.first<<","<<ans[0].second.second<<")";
    for(int i=1;i<ans.size();i++)
    {
        cout<<",("<<ans[i].second.first<<","<<ans[i].second.second<<")";
        //cout<<ans[i].second.first<<" "<<ans[i].second.second<<" "<<ans[i].first<<endl;
    }
    cout<<"}"<<endl;
    /*total time complexity:O(m log m)+O(m log n)
                           =O(m log m)
                           =O(edge log edge)
    */
    return 0;
}

