#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int **w;
int **mat;
const int N=9223372036854775807;
int** apsp()
{
    int** new_mat;
    new_mat=new int*[n+1];
    for(int i=1;i<=n;i++)
    {
        new_mat[i]=new int[n+1];
    }
    for(int i=1;i<=n;i++)//n times
    {
        for(int j=1;j<=n;j++)//n times
        {
            new_mat[i][j]=N;
            for(int k=1;k<=n;k++)//n times
            {
                if(mat[i][k]!=N&&mat[k][j]!=N&&new_mat[i][j]>(mat[i][k] + mat[k][j]))
                    new_mat[i][j] = mat[i][k]+mat[k][j];
            }

        }
    }
    return new_mat;
}
signed main()
{
    cin>>n>>m;
    w=new int*[n+1];
    mat=new int*[n+1];
    for(int i=1;i<=n;i++)
    {
        w[i]=new int[n+1];
        mat[i]=new int[n+1];
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
            {
                w[i][j]=0;
                mat[i][j]=0;
            }
            else
            {
                w[i][j] =N;
                mat[i][j]=N;
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        int u,v,edg;
        cin>>u>>v>>edg;
        if(w[u][v]>edg)
        {
            w[u][v] = edg;
        }
        if(mat[u][v]>edg)
        {
            mat[u][v] = edg;
        }
    }
    for(int d=1;d<n;d*=2)//log n times
    {
        mat=apsp();//O(n^3)
    }
    //time complexity is O(n^3 log n)
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
