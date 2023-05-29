#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int **mat;
const int N=9223372036854775807;
signed main()
{
    cin>>n>>m;
    mat=new int*[n+1];
    for(int i=1;i<=n;i++)
    {
        mat[i]=new int[n+1];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
            {
                mat[i][j]=0;
            }
            else
            {
                mat[i][j]=N;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        int u,v,edg;
        cin>>u>>v>>edg;
        if(mat[u][v]>edg)
        {
            mat[u][v] = edg;
        }
    }
    for(int k=1;k<=n;k++)//n times
    {
        for(int i=1;i<=n;i++)//n times
        {
            for(int j=1;j<=n;j++)//n times
            {
                if(mat[i][k]!=N&&mat[k][j]!=N&&mat[i][j]>(mat[i][k] + mat[k][j]))
                {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
    //time complexity is : O(n^3)
    cout<<"Shortest distance matrix "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(mat[i][j]==N)
            {
                cout<<"INF"<<" ";
            }
            else
            {
                cout << mat[i][j] << " ";
            }
        }
        cout<<endl;
    }
    return 0;
}
