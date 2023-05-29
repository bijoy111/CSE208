#include<bits/stdc++.h>
using namespace std;
int ans[1000005];
int con=0;
struct node
{
    int value;
    int color;//0 for black and 1 for red
    node *parent;
    node *left;
    node *right;
};
class RB
{
    node * root;//for the root of the tree
    node* tmp;//for external node mainly
public:
    RB()
    {
        tmp=new node;
        tmp->color=0;//as color of external node is black
        tmp->left=NULL;
        tmp->right=NULL;
        root=tmp;
        root->parent=NULL;
    }
    node* get_root()
    {
        return root;
    }
    void left_rotate(node* x)
    {
        node* y;
        y=x->right;
        x->right=y->left;
        if(y->left!=tmp)
        {
            y->left->parent = x;
        }
        y->parent=x->parent;
        if(x->parent==NULL)
        {
            root=y;
        }
        else if(x==x->parent->left)
        {
            x->parent->left=y;
        }
        else
        {
            x->parent->right=y;
        }
        y->left=x;
        x->parent=y;
    }
    void right_rotate(node* x)
    {
        node* y;
        y=x->left;
        x->left=y->right;
        if(y->right!=tmp)
        {
            y->right->parent=x;
        }
        y->parent=x->parent;
        if(x->parent==NULL)
        {
            root=y;
        }
        else if(x==x->parent->right)
        {
            x->parent->right=y;
        }
        else
        {
            x->parent->left=y;
        }
        y->right=x;
        x->parent=y;
    }
    node* minimum(node* vertex)
    {
        while(vertex->left!=tmp)
        {
            vertex=vertex->left;
        }
        return vertex;
    }
    node* maximum(node* vertex)
    {
        while(vertex->right!=tmp)
        {
            vertex=vertex->right;
        }
        return vertex;
    }
    node* searching(node* r,int key)
    {
        if(r==tmp)
        {
            return NULL;
        }
        else if(r->value==key)
        {
            return r;
        }
        else if(r->value > key)
        {
            return searching(r->left,key);
        }
        else
        {
            return searching(r->right,key);
        }
    }
    void insert_help(node* z)
    {
        while(z->parent->color == 1)
        {
            if(z->parent == z->parent->parent->left)
            {
                node* y=z->parent->parent->right;
                if(y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color=0;
                    z->parent->parent->color=1;
                    right_rotate(z->parent->parent);
                }
            }
            else
            {
                node* y=z->parent->parent->left;
                if(y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color=1;
                    z=z->parent->parent;
                }
                else
                {
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color=1;
                    left_rotate(z->parent->parent);
                }
            }
            if(z==root)
            {
                break;
            }
        }
        root->color=0;
    }

    void delete_help(node* x)
    {
        while(x->color == 0 && x != root)
        {
            if(x == x->parent->left)
            {
                node* w=x->parent->right;
                if(w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    left_rotate(x->parent);
                    w=x->parent->right;
                }
                if(w->left->color == 0 && w->right->color == 0)
                {
                    w->color=1;
                    x=x->parent;
                }
                else
                {
                    if(w->right->color == 0)
                    {
                        w->left->color=0;
                        w->color=1;
                        right_rotate(w);
                        w=x->parent->right;
                    }
                    w->color=x->parent->color;
                    x->parent->color=0;
                    w->right->color=0;
                    left_rotate(x->parent);
                    x=root;
                }
            }
            else
            {
                node* w=x->parent->left;
                if(w->color==1)
                {
                    w->color=0;
                    x->parent->color=1;
                    right_rotate(x->parent);
                    w=x->parent->left;
                }
                if(w->left->color==0&&w->right->color==0)
                {
                    w->color=1;
                    x=x->parent;
                }
                else
                {
                    if(w->left->color==0)
                    {
                        w->right->color=0;
                        w->color=1;
                        left_rotate(w);
                        w=x->parent->left;
                    }
                    w->color=x->parent->color;
                    x->parent->color=0;
                    w->left->color=0;
                    right_rotate(x->parent);
                    x=root;
                }
            }
        }
        x->color=0;
    }
    int deleteing(int key)
    {
        if(ans[key]==0)
        {
            return 0;
        }
        else
        {
            ans[key]=0;
        }
        node* r=root;
        node* z;
        node* x;
        node* y;
        z=searching(r,key);
        if(z==NULL)
        {
            return 0;
        }
        y = z;
        int oc = z->color;
        if (z->left == tmp)
        {
            x = z->right;
            if(z->parent==NULL)
            {
                root=x;
            }
            else if(z==z->parent->left)
            {
                z->parent->left=x;
            }
            else
            {
                z->parent->right=x;
            }
            x->parent=z->parent;
        }
        else if (z->right == tmp)
        {
            x = z->left;
            if(z->parent==NULL)
            {
                root=x;
            }
            else if(z==z->parent->left)
            {
                z->parent->left=x;
            }
            else
            {
                z->parent->right=x;
            }
            x->parent=z->parent;
        }
        else
        {
            y = minimum(z->right);
            oc = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                if(y->parent==NULL)
                {
                    root=y->right;
                }
                else if(y==y->parent->left)
                {
                    y->parent->left=y->right;
                }
                else
                {
                    y->parent->right=y->right;
                }
                y->right->parent=y->parent;
                y->right = z->right;
                y->right->parent = y;
            }
            if(z->parent==NULL)
            {
                root=y;
            }
            else if(z->parent->left==z)
            {
                z->parent->left=y;
            }
            else
            {
                z->parent->right=y;
            }
            y->parent=z->parent;
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (oc == 0)
        {
            delete_help(x);
        }
        return 1;
    }

    int inserting(int key)
    {
        if(ans[key])
        {
            return 0;
        }
        else
        {
            ans[key]=1;
        }
        node * z=new node;
        z->parent=NULL;
        z->value=key;
        z->left=tmp;
        z->right=tmp;
        z->color=1;
        node *y=NULL;
        node *x=root;
        while(x!=tmp)
        {
            y=x;
            if(z->value > x->value)
            {
                x=x->right;
            }
            else
            {
                x=x->left;
            }
        }
        z->parent=y;
        if(y==NULL)
        {
            root=z;
        }
        else if(z->value>y->value)
        {
            y->right=z;
        }
        else
        {
            y->left=z;
        }
        if(z->parent==NULL)
        {
            z->color=0;
            return 1;
        }
        if(z->parent->parent==NULL)
        {
            return 1;
        }
        insert_help(z);
        return 1;
    }
    void preorder(node* r,int key)
    {
        if(r!=tmp)
        {
            if(r->value<key)
            {
                con++;
            }
            preorder(r->left,key);
            preorder(r->right,key);
        }
    }
    int less_priority(node* r,int key)
    {
        con=0;
        preorder(r,key);
        return con;
    }
};
int main()
{
    for(int i=1;i<=1000000;i++)
    {
        ans[i]=0;
    }
    RB rb;
    ifstream input("inp.txt");
    string str;
    getline(input,str);
    stringstream line(str);
    int n;
    //cin>>n;
    line>>n;
    ofstream output;
    output.open("out.txt");
    output<<n<<endl;
    cout<<n<<endl;
    //for(int i=0;i<n;i++)
    int i=1;
    while(getline(input,str))
    {
        cout<<"test case: "<<i<<endl;
        i++;
        int e,x;
        stringstream line(str);
        line>>e>>x;
        //cin>>e>>x;
        if(e==0)
        {
            int res=rb.deleteing(x);
            if(res==0)
            {
                cout<<"No priority ("<<x<<") exists"<<endl;
                cout<<e<<" "<<x<<" "<<res<<endl;
                output<<e<<" "<<x<<" "<<res<<endl;
            }
            else
            {
                cout<<"Successful termination "<<x<<endl;
                cout<<e<<" "<<x<<" "<<res<<endl;
                output<<e<<" "<<x<<" "<<res<<endl;
            }
        }
        else if(e==1)
        {
            int res=rb.inserting(x);
            if(res==0)
            {
                cout<<"Same priority ("<<x<<") exists"<<endl;
                cout<<e<<" "<<x<<" "<<res<<endl;
                output<<e<<" "<<x<<" "<<res<<endl;
            }
            else
            {
                cout<<"Successful initiation "<<x<<endl;
                cout<<e<<" "<<x<<" "<<res<<endl;
                output<<e<<" "<<x<<" "<<res<<endl;
            }
        }
        else if(e==2)
        {
            node* roots=rb.get_root();
            node* r=rb.searching(roots,x);
            if(r==NULL)
            {
                cout<<"Priority "<<x<<" not found"<<endl;
                cout<<e<<" "<<x<<" "<<0<<endl;
                output<<e<<" "<<x<<" "<<0<<endl;
            }
            else
            {
                cout<<"Priority "<<x<<" found"<<endl;
                cout<<e<<" "<<x<<" "<<1<<endl;
                output<<e<<" "<<x<<" "<<1<<endl;
            }
        }
        else if(e==3)
        {
            node* roots=rb.get_root();
            int res=rb.less_priority(roots,x);
            cout<<res<<" programs having priority <"<<x<<endl;
            cout<<e<<" "<<x<<" "<<res<<endl;
            output<<e<<" "<<x<<" "<<res<<endl;
        }
    }
    output.close();
    return 0;
}
