#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,m;
char v[N][N];
int vis[N][N];
void dfs(int i,int j)
{
    if(i-1>=0&&vis[i-1][j]==0)
    {
        vis[i-1][j]=1;
        dfs(i-1,j);
    }
    if(i+1<n&&vis[i+1][j]==0)
    {
        vis[i+1][j]=1;
        dfs(i+1,j);
    }
    if(j-1>=0&&vis[i][j-1]==0)
    {
        vis[i][j-1]=1;
        dfs(i,j-1);
    }
    if(j+1<m&&vis[i][j+1]==0)
    {
        vis[i][j+1]=1;
        dfs(i,j+1);
    }
}
int fun()
{
    n=3;
    int cros=0,zero=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>v[i][j];
            if(v[i][j]=='X')
            {
                cros++;
            }
            else if(v[i][j]=='O')
            {
                zero++;
            }
        }
    }
    if(abs(cros-zero)>=2)
    {
        return 3;
    }
    if(v[1][1]=='X'&&v[1][2]=='X'&&v[1][3]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[1][1]=='O'&&v[1][2]=='O'&&v[1][3]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[2][1]=='X'&&v[2][2]=='X'&&v[2][3]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[2][1]=='O'&&v[2][2]=='O'&&v[2][3]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[3][1]=='X'&&v[3][2]=='X'&&v[3][3]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[3][1]=='O'&&v[3][2]=='O'&&v[3][3]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }

    if(v[1][1]=='X'&&v[2][1]=='X'&&v[3][1]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][1]=='O'&&v[2][1]=='O'&&v[3][1]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][2]=='X'&&v[2][2]=='X'&&v[3][2]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][2]=='O'&&v[2][2]=='O'&&v[3][2]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][3]=='X'&&v[2][3]=='X'&&v[3][3]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][3]=='O'&&v[2][3]=='O'&&v[3][3]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][1]=='X'&&v[2][2]=='X'&&v[3][3]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][1]=='O'&&v[2][2]=='O'&&v[3][3]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][3]=='X'&&v[2][2]=='X'&&v[3][1]=='X'&&(cros+zero)!=9)
    {
        return 3;
    }
    if(v[1][3]=='O'&&v[2][2]=='O'&&v[3][1]=='O'&&(cros+zero)!=9)
    {
        return 3;
    }
    //check row wise
    for(int i=1;i<=3;i++)
    {
        int cr=0,ze=0;
        for(int j=1;j<=3;j++)
        {
            if(v[i][j]=='X')
            {
                cr++;
            }
            else if(v[i][j]=='O')
            {
                ze++;
            }
        }
        if(cr==0&&(4-zero)>=(3-ze))
        {
            return 1;
        }
        else if(ze==0&&(5-cros)>=(3-cr))
        {
            return 1;
        }
    }
//check column wise
    for(int i=1;i<=3;i++)
    {
        int cr=0,ze=0;
        for(int j=1;j<=3;j++)
        {
            if(v[j][i]=='X')
            {
                cr++;
            }
            else if(v[j][i]=='O')
            {
                ze++;
            }
        }
        if(cr==0&&(4-zero)>=(3-ze))
        {
            return 1;
        }
        else if(ze==0&&(5-cros)>=(3-cr))
        {
            return 1;
        }
    }
    //diagonal check
    int cr=0,ze=0;
    if(v[1][1]=='X')
    {
        cr++;
    }
    else if(v[1][1]=='O')
    {
        ze++;
    }
    if(v[2][2]=='X')
    {
cr++;
    }
    else if(v[2][2]=='O')
    {
ze++;
    }
    if(v[3][3]=='X')
    {
cr++;
    }
    else if(v[3][3]=='O')
    {
ze++;
    }
    if(cr==0&&(4-zero)>=(3-ze))
    {
        return 1;
    }
    else if(ze==0&&(5-cros)>=(3-cr))
    {
        return 1;
    }
    cr=0;
    ze=0;
    if(v[1][3]=='X')
    {
        cr++;
    }
    else if(v[1][3]=='O')
    {
        ze++;
    }
    if(v[2][2]=='X')
    {
        cr++;
    }
    else if(v[2][2]=='O')
    {
        ze++;
    }
    if(v[3][1]=='X')
    {
        cr++;
    }
    else if(v[3][1]=='O')
    {
        ze++;
    }
    if(cr==0&&(4-zero)>=(3-ze))
    {
        return 1;
    }
    else if(ze==0&&(5-cros)>=(3-cr))
    {
        return 1;
    }
    return 2;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int ans=fun();
        cout<<ans<<endl;
    }
    return 0;
}
