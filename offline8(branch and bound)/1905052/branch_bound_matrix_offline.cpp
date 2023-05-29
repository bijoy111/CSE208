#include<bits/stdc++.h>
using namespace std;

class node
{
    int ba;//bandwidth
    int le;//level
    int orde;//order
    int co;//fixed column
    int ro;//fixed row
    vector<vector<char>> ma;//to store the matrix
public:
    node(int o,int a,int b,int c,int d,vector<vector<char>> v)
    {
        ba=o;
        le=a;
        orde=b;
        co=c;
        ro=d;
        ma=v;
    }
    int bandwidth()
    {
        return ba;
    }
    int level()
    {
        return le;
    }
    int order()
    {
        return orde;
    }
    int column()
    {
        return co;
    }
    int row()
    {
        return ro;
    }
    vector<vector<char>> matrix()
    {
        return ma;
    }
};
class compare : public std::binary_function<node, node, bool>
{
public:
    bool operator()(node l, node r)
    {
        if(l.bandwidth()==r.bandwidth())
        {
            if (l.level() == r.level())
            {
                return l.order() < r.order();
            }
            else
            {
                return l.level() < r.level();
            }
        }
        else
        {
            return l.bandwidth() > r.bandwidth();
        }
    }
};
int main()
{
    int n;
    cin>>n;
    vector<vector<char>>mati;
    for(int i=1; i<=n; i++)
    {
        vector<char>vec;
        for(int j=1; j<=n; j++)
        {
            char x;
            cin>>x;
            vec.push_back(x);
        }
        mati.push_back(vec);
    }
    int band=0;
    for(int i=1; i<=n; i++)
    {
        int tmp=0;
        for(int j=1; j<=n; j++)
        {
            if(mati[j-1][i-1]=='X')
            {
                tmp++;
            }
        }
        band=max(band,tmp);
    }
    for(int i=1; i<=n; i++)
    {
        int tmp=0;
        for(int j=1; j<=n; j++)
        {
            if(mati[i-1][j-1]=='X')
            {
                tmp++;
            }
        }
        band=max(band,tmp);
    }
    band=(band+1)/2;
    priority_queue<node,vector<node>,compare>pq;
    node nod(band,0,0,0,0,mati);
    pq.push(nod);
    while(1)
    {
        node ob=pq.top();
        /*
        cout<<"bandwidth: "<<ob.bandwidth()<<endl;
        cout<<"level: "<<ob.level()<<endl;
        cout<<"order: "<<ob.order()<<endl;
        cout<<"fixed column: "<<ob.column()<<endl;
        cout<<"fixed row: "<<ob.row()<<endl;
        vector<vector<char>>vect=ob.matrix();
        for(int ii=0; ii<n; ii++)
        {
            for(int jj=0; jj<n; jj++)
            {
                cout<<vect[ii][jj]<<" ";
            }
            cout<<endl;
        }
        */
        pq.pop();
        int b=ob.bandwidth();
        int c=ob.column()+1;
        int r=ob.row()+1;
        int lev=ob.level();
        int ord=0;
        vector<vector<char>>matri=ob.matrix();
        if(c==n&&r==n)
        {
            //cout<<"Final Matrix"<<endl;
            cout<<b<<endl;
            for(int i=1; i<=n; i++)
            {
                for(int j=1; j<=n; j++)
                {
                    cout<<matri[i-1][j-1]<<" ";
                }
                cout<<endl;
            }
            break;
        }

//column operation

        if(c==r)
        {
            char mat[100][100];
            char tmp[100][100];
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    mat[i+1][j+1]=matri[i][j];
                    tmp[i+1][j+1]=matri[i][j];
                }
            }
            for (int j = c; j <= n; j++)
            {
                for(int k=1; k<=n; k++)
                {
                    tmp[k][c]=mat[k][j];
                }
                for(int k=c; k<j; k++)
                {
                    for(int kk=1; kk<=n; kk++)
                    {
                        tmp[kk][k+1]=mat[kk][k];
                    }
                }
                int ban1=0;
                for(int i=1; i<=c; i++)
                {
                    int tm1=0;
                    for(int jj=i; jj<r; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm1++;
                        }
                    }
                    int tm2=0;
                    for(int jj=r; jj<=n; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm2++;
                        }
                    }
                    int rr=max(0,r-i);
                    if(tm2!=0)
                    {
                        tm2=tm2+rr;
                    }
                    ban1=max(ban1,tm1);
                    ban1=max(ban1,tm2);
                }


                for(int i=1; i<r; i++)
                {
                    int tm1=0;
                    for(int jj=i; jj<=c; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm1++;
                        }
                    }
                    int tm2=0;
                    for(int jj=c+1; jj<=n; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm2++;
                        }
                    }
                    int rr=max(0,c-i+1);
                    if(tm2!=0)
                    {
                        tm2=tm2+rr;
                    }
                    ban1=max(ban1,tm1);
                    ban1=max(ban1,tm2);
                }



                int ban=0;
                for(int i=c+1; i<=n; i++)
                {
                    int tm=0;
                    for(int jj=r; jj<=n; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm++;
                        }
                    }
                    ban=max(ban,tm);
                }
                for(int i=r; i<=n; i++)
                {
                    int tm=0;
                    for(int jj=c+1; jj<=n; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm++;
                        }
                    }
                    ban=max(ban,tm);
                }
                ban=(ban+1)/2;
                int bandwidth=max(ban,ban1);
                ord++;
                /*
                cout<<"bandwidth: "<<bandwidth<<endl;
                cout<<"level: "<<lev+1<<endl;
                cout<<"order: "<<ord<<endl;
                cout<<"fixed column: "<<c<<endl;
                cout<<"fixed row: "<<r-1<<endl;
                 */
                vector<vector<char>>vect;
                for(int ii=1; ii<=n; ii++)
                {
                    vector<char>vecto;
                    for(int jj=1; jj<=n; jj++)
                    {
                        //cout<<tmp[ii][jj]<<" ";
                        vecto.push_back(tmp[ii][jj]);
                    }
                    //cout<<endl;
                    vect.push_back(vecto);
                }
                node tmpo(bandwidth, lev + 1, ord, c, r - 1,vect);
                pq.push(tmpo);
            }
        }

//row operation

        else
        {
            c--;
            char mat[100][100];
            char tmp[100][100];
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    mat[i+1][j+1]=matri[i][j];
                    tmp[i+1][j+1]=matri[i][j];
                }
            }
            for (int j = r; j <= n; j++)
            {

                for(int k=1; k<=n; k++)
                {
                    tmp[r][k]=mat[j][k];
                }
                for(int k=r; k<j; k++)
                {
                    for(int kk=1; kk<=n; kk++)
                    {
                        tmp[k+1][kk]=mat[k][kk];
                    }
                }

                int ban1=0;
                for(int i=1; i<=c; i++)
                {
                    int tm1=0;
                    for(int jj=i; jj<=r; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm1++;
                        }
                    }
                    int tm2=0;
                    for(int jj=r+1; jj<=n; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm2++;
                        }
                    }
                    int rr=max(0,r-i+1);
                    if(tm2!=0)
                    {
                        tm2=tm2+rr;
                    }
                    ban1=max(ban1,tm1);
                    ban1=max(ban1,tm2);
                }


                for(int i=1; i<=r; i++)
                {
                    int tm1=0;
                    for(int jj=i; jj<=c; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm1++;
                        }
                    }
                    int tm2=0;
                    for(int jj=c+1; jj<=n; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm2++;
                        }
                    }
                    int rr=max(0,c-i+1);
                    if(tm2!=0)
                    {
                        tm2=tm2+rr;
                    }
                    ban1=max(ban1,tm1);
                    ban1=max(ban1,tm2);
                }



                int ban=0;
                for(int i=c+1; i<=n; i++)
                {
                    int tm=0;
                    for(int jj=r+1; jj<=n; jj++)
                    {
                        if(tmp[jj][i]=='X')
                        {
                            tm++;
                        }
                    }
                    ban=max(ban,tm);
                }
                for(int i=r+1; i<=n; i++)
                {
                    int tm=0;
                    for(int jj=c+1; jj<=n; jj++)
                    {
                        if(tmp[i][jj]=='X')
                        {
                            tm++;
                        }
                    }
                    ban=max(ban,tm);
                }
                ban=(ban+1)/2;
                int bandwidth=max(ban,ban1);
                ord++;
                /*
                cout<<"bandwidth: "<<bandwidth<<endl;
                cout<<"level: "<<lev+1<<endl;
                cout<<"order: "<<ord<<endl;
                cout<<"fixed column: "<<c<<endl;
                cout<<"fixed row: "<<r<<endl;
                */
                vector<vector<char>>vect;
                for(int ii=1; ii<=n; ii++)
                {
                    vector<char>vecto;
                    for(int jj=1; jj<=n; jj++)
                    {
                        //cout<<tmp[ii][jj]<<" ";
                        vecto.push_back(tmp[ii][jj]);
                    }
                    //cout<<endl;
                    vect.push_back(vecto);
                }
                node tmpo(bandwidth, lev + 1, ord, c, r,vect);
                pq.push(tmpo);
            }
        }
    }
    return 0;
}

/*
input 1:
4
X 0 0 X
0 0 X 0
X 0 0 X
0 X X X
output 1:
2
X 0 0 0
X X X 0
0 0 X X
0 0 X X

input 2:
6
0 X X 0 0 X
0 0 X 0 0 0
X X 0 0 0 X
X 0 0 X X 0
X 0 0 0 0 0
0 0 0 X 0 0
output 2:
2
0 X 0 0 0 0
X X X 0 0 0
0 0 X 0 0 0
0 0 X X X 0
0 0 0 X X X
0 0 0 0 0 X

input 3:
8
0 X 0 0 0 0 0 X
0 X 0 0 X 0 0 0
X 0 0 0 0 0 X 0
0 0 0 X 0 0 0 X
0 0 X 0 0 0 0 0
X 0 0 0 0 X 0 0
0 0 X 0 X 0 0 0
0 0 0 X 0 0 0 0
output 3:
2
0 X 0 0 0 0 0 0
X 0 X 0 0 0 0 0
0 X 0 X 0 0 0 0
0 0 X 0 X 0 0 0
0 0 0 X 0 X 0 0
0 0 0 0 0 0 X 0
0 0 0 0 0 X 0 X
0 0 0 0 0 0 X X

input 4:
6
X 0 0 X 0 X
X X 0 0 X 0
0 0 X 0 0 X
X X X X 0 0
X 0 0 X X X
0 X 0 0 0 X
output 4:
3
X 0 X 0 0 0
0 X X X 0 0
X X 0 X X 0
0 X X X 0 X
0 0 X 0 X 0
0 0 0 X X X

input 5:
7
X 0 0 X 0 X 0
X X 0 0 X 0 X
0 0 X 0 0 X 0
X X X X 0 0 0
X 0 0 X X X 0
0 X 0 0 0 X X
X 0 X 0 X 0 X
output 5:
4
X 0 0 X 0 0 0
X X X 0 X 0 0
0 X 0 X X X 0
X 0 0 0 X X X
0 X X 0 X 0 X
0 0 X X 0 0 X
0 0 0 X X X 0

input 6:
8
X 0 0 X 0 X 0 0
X X 0 0 X 0 X 0
0 0 X 0 0 X 0 0
X X X X 0 0 0 0
X 0 0 X X X 0 0
0 X 0 0 0 X X X
X 0 X 0 X 0 X 0
0 0 0 X 0 0 X 0
output 6:
4
0 X 0 X 0 0 0 0
0 X X 0 X 0 0 0
0 0 X 0 0 X 0 0
X X 0 0 0 X X 0
0 X X 0 X 0 0 X
0 0 X X X 0 X 0
0 0 0 X X X 0 X
0 0 0 0 X X X X

input 7:
9
X 0 0 X 0 X 0 0 0
X X 0 0 X 0 X 0 0
0 0 X 0 0 X 0 0 0
X X X X 0 0 0 0 0
X 0 0 X X X 0 0 X
0 X 0 0 0 X X X 0
X 0 X 0 X 0 X 0 X
0 0 0 X 0 0 X 0 X
0 X X 0 0 X X X 0
output 7:
5
0 0 X X 0 0 0 0 0
X X X X X 0 0 0 0
X X 0 X X 0 0 0 0
0 X X 0 0 X 0 X 0
0 X 0 0 X 0 0 X X
0 0 X 0 X 0 X X X
0 0 0 X 0 X X X X
0 0 0 X 0 X 0 X 0
0 0 0 0 X X X 0 0

input 8:
10
X 0 0 X 0 X 0 0 0 X
X X 0 0 X 0 X 0 0 X
0 0 X 0 0 X 0 0 0 X
X X X X 0 0 0 0 0 X
X 0 0 X X X 0 0 X 0
0 X 0 0 0 X X X 0 X
X 0 X 0 X 0 X 0 X 0
0 0 0 X 0 0 X 0 X X
0 X X 0 0 X X X 0 0
0 0 0 X 0 X 0 X 0 X
output 8:
6
X X X X X 0 0 0 0 0
X X 0 X X X 0 0 0 0
X 0 0 0 X X X 0 0 0
0 X X 0 0 X X X 0 0
0 0 X 0 X X 0 0 0 0
0 X 0 X 0 X 0 X 0 X
0 0 X X 0 0 0 X X X
0 0 0 X 0 X X 0 X 0
0 0 0 0 X 0 X X X X
0 0 0 0 X X X X 0 0
*/

