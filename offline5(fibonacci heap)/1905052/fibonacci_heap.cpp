#include<bits/stdc++.h>
#include<chrono>
using namespace std;
vector<pair<int,int>>vec[1000001];
class Heap
{
    pair<int,int>* heap;
    int maxsize;
    int currsize;
public:
    Heap()
    {
        maxsize=1000001;
        heap=new pair<int,int>[maxsize+1];
        currsize=1;
    }
    void build_heap(int s)
    {
        int j=s;
        while(j>1)
        {
            int p=j/2;
            if(heap[p].first>heap[j].first)
            {
                pair<int,int> tmp=heap[p];
                heap[p]=heap[j];
                heap[j]=tmp;
                j=p;
            }
            else
            {
                break;
            }
        }
    }
    void min_heapify(int i)
    {
        int l=2*i;
        int r=(2*i)+1;
        int smallest=i;
        if(l<currsize&&heap[l]<heap[smallest])
        {
            smallest=l;
        }
        if(r<currsize&&heap[r].first<heap[smallest].first)
        {
            smallest=r;
        }
        if(smallest!=i)
        {
            pair<int,int> tmp=heap[smallest];
            heap[smallest]=heap[i];
            heap[i]=tmp;
            min_heapify(smallest);
        }
    }
    void insert(int number,int v)
    {
        heap[currsize].first=number;
        heap[currsize].second=v;
        currsize++;
        build_heap(currsize-1);
    }
    int size()
    {
        return currsize-1;
    }
    pair<int,int> getMin()
    {
        return heap[1];
    }
    void deleteKey()
    {
        heap[1]=heap[currsize-1];
        currsize--;
        min_heapify(1);
    }
};

// crate a vertex
struct vertex
{
    int cost;
    int v;
    int deg;
    vertex *parent;
    vertex *child;
    vertex *left;
    vertex *right;
    //char mark;
};
vertex * minimum_vertex;

class FibonacciHeap
{
private:
    int nodes;//number of vertex in the heap

public:

    FibonacciHeap()
    {
        minimum_vertex = makeHeap();
    }
    vertex *make_vertex(int,int);
    vertex *makeHeap();
    void insert(vertex *);
    vertex *extract_Min();
    void help_extractmin();
    void solve_sameDegreeProblem(vertex *, vertex *);
};

// make a  node
vertex *FibonacciHeap::make_vertex(int cos,int ver)
{
    vertex *vert = new vertex;
    vert->cost = cos;
    vert->v=ver;
    return vert;
}

// make heap
vertex *FibonacciHeap::makeHeap()
{
    vertex *nod=NULL;
    return nod;
}

// push
void FibonacciHeap::insert(vertex *node)
{
    node->deg = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    //node->mark = 'F';
    if (minimum_vertex != NULL)
    {
        (minimum_vertex->left)->right = node;
        node->right = minimum_vertex;
        node->left = minimum_vertex->left;
        minimum_vertex->left = node;
        if (node->cost < minimum_vertex->cost)
            minimum_vertex = node;
    }
    else
    {
        minimum_vertex = node;
    }
    nodes++;
}

// extract min
vertex *FibonacciHeap::extract_Min()
{
    if (minimum_vertex == NULL)
    {
        return minimum_vertex;
    }
    vertex *minimum=minimum_vertex;//to get the minimum element
    vertex *del = minimum_vertex;//it is used to delete the minimum vertex
    vertex *x;
    vertex *tmp1;
    vertex *tmp2;
    x = NULL;
    if (del->child != NULL)
    {
        x = del->child;
    }
    if (x != NULL)
    {
        tmp1 = x;
        do
        {
            tmp2 = x->right;
            (minimum_vertex->left)->right = x;
            x->right = minimum_vertex;
            x->left = minimum_vertex->left;
            minimum_vertex->left = x;
            if (x->cost < minimum_vertex->cost)
                minimum_vertex = x;

            x->parent = NULL;
            x = tmp2;
        } while (tmp2 != tmp1);
    }

    (del->left)->right = del->right;
    (del->right)->left = del->left;
    if (del == del->right && del->child == NULL)
    {
        minimum_vertex = NULL;
    }
    else
    {
        minimum_vertex = del->right;
        help_extractmin();
    }
    nodes--;
    return minimum;
}


void FibonacciHeap::help_extractmin()
{
    int degree;
    int siz=(log(nodes)) / (log(2));
    vertex *arr[siz];
    for (int i = 0; i <= siz; i++)
        arr[i] = NULL;
    vertex *x = minimum_vertex;
    vertex *y;
    vertex *tmp;
    do {
        degree = x->deg;
        while (arr[degree] != NULL)
        {
            y = arr[degree];
            if (x->cost > y->cost)
            {
                tmp = x;
                x = y;
                y = tmp;
            }
            if (y == minimum_vertex)
                minimum_vertex = x;
            solve_sameDegreeProblem(y, x);
            if (x->right == x)
                minimum_vertex = x;
            arr[degree] = NULL;
            degree = degree + 1;
        }
        arr[degree] = x;
        x = x->right;
    }while (x != minimum_vertex);
    minimum_vertex = NULL;
    for (int j = 0; j <= siz; j++)
    {
        if (arr[j] != NULL)
        {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (minimum_vertex != NULL)
            {
                (minimum_vertex->left)->right = arr[j];
                arr[j]->right = minimum_vertex;
                arr[j]->left = minimum_vertex->left;
                minimum_vertex->left = arr[j];
                if (arr[j]->cost < minimum_vertex->cost)
                {
                    minimum_vertex = arr[j];
                }
            }
            else
            {
                minimum_vertex = arr[j];
            }
            if (minimum_vertex == NULL)
            {
                minimum_vertex = arr[j];
            }
            else if (arr[j]->cost < minimum_vertex->cost)
            {
                minimum_vertex = arr[j];
            }
        }
    }
}


void FibonacciHeap::solve_sameDegreeProblem(vertex *y, vertex *x)
{
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if (x->right == x)
        minimum_vertex = x;
    y->left = y;
    y->right = y;
    y->parent = x;

    if (x->child == NULL)
        x->child = y;

    y->right = x->child;
    y->left = (x->child)->left;
    ((x->child)->left)->right = y;
    (x->child)->left = y;

    if (y->cost < (x->child)->cost)
        x->child = y;
    x->deg++;
}


int main()
{
    int n,m;
    ifstream input("input1.txt");
    string str;
    getline(input,str);
    stringstream line(str);
    line>>n>>m;
    while(getline(input,str))
    {
        int u,v,edg;
        stringstream line(str);
        line>>u>>v>>edg;
        vec[u].push_back({edg,v});
        vec[v].push_back({edg,u});
    }
    int k;
    ifstream input2("input2.txt");
    string str2;
    getline(input2,str2);
    stringstream line2(str2);
    line2>>k;
    ofstream output;
    output.open("output1.txt");
    while(getline(input2,str2))
    {
        int s,d;
        stringstream line2(str2);
        line2>>s>>d;
        //int s1 = s;
        //int d1 = d;
        int s3=s;
        int d3=d;
        int des=d;
        //fibonacci heap implementation
        auto st1=std::chrono::high_resolution_clock::now();
        int *cost = new int[n + 1];
        int *visited = new int[n + 1];
        int *parent = new int[n + 1];
        for (int i = 0; i < n; i++)
        {
            cost[i] = INT_MAX;
            visited[i] = 0;
        }
        cost[s] = 0;
        parent[s] = s;
        FibonacciHeap pq;
        vertex *p;
        p = pq.make_vertex(cost[s], s);
        pq.insert(p);
        while (minimum_vertex != NULL)
        {
            p = pq.extract_Min();
            int vertex = p->v;
            visited[vertex] = 1;
            for (int i = 0; i < vec[vertex].size(); i++)
            {
                int adj = vec[vertex][i].second;
                if (visited[adj] == 0 && (cost[vertex] + vec[vertex][i].first) < cost[adj]) {
                    cost[adj] = cost[vertex] + vec[vertex][i].first;
                    parent[adj] = vertex;
                    p = pq.make_vertex(cost[adj], adj);
                    pq.insert(p);
                }
            }
        }
        //cout << "Shortest path cost: " << cost[d] << endl;
        vector<int> ans;
        while (parent[d] != d)
        {
            ans.push_back(d);
            d = parent[d];
        }
        ans.push_back(s);
        /*for (int i = ans.size() - 1; i > 0; i--) {
            cout << ans[i] << "->";
        }
        cout << ans[0] << endl;*/
        auto t1=std::chrono::high_resolution_clock::now();
        double ti1=std::chrono::duration<double,std::nano>(t1-st1).count();
        /*
        //built in priority queue implementation
        auto st2=std::chrono::high_resolution_clock::now();
        int *cost1 = new int[n + 1];
        int *visited1 = new int[n + 1];
        int *parent1 = new int[n + 1];
        for (int i = 0; i < n; i++) {
            cost1[i] = INT_MAX;
            visited1[i] = 0;
        }
        cost1[s1] = 0;
        parent1[s1] = s1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> prq;
        prq.push({cost1[s1], s1});
        while (!prq.empty())//n times
        {
            pair<int, int> p1 = prq.top();
            prq.pop();//O(log n)
            int vertex = p1.second;
            visited1[vertex] = 1;
            for (int i = 0; i < vec[vertex].size(); i++)// m/n times
            {
                int adj = vec[vertex][i].second;
                if (visited1[adj] == 0 && (cost1[vertex] + vec[vertex][i].first) < cost1[adj]) {
                    cost1[adj] = cost1[vertex] + vec[vertex][i].first;
                    parent1[adj] = vertex;
                    prq.push({cost1[adj], adj});
                }
            }
        }
        //cout << "Shortest path cost: " << cost1[d1] << endl;
        vector<int> ans1;
        while (parent1[d1] != d1) {
            ans1.push_back(d1);
            d1 = parent1[d1];
        }
        ans1.push_back(s1);
        for (int i = ans1.size() - 1; i > 0; i--) {
            cout << ans1[i] << "->";
        }
        cout << ans1[0] << endl;
        auto t2=std::chrono::high_resolution_clock::now();
        double ti2=std::chrono::duration<double,std::nano>(t2-st2).count();
    */
        //binary heap implementation
        auto st3=std::chrono::high_resolution_clock::now();
        int *cost3 = new int[n + 1];
        int *visited3 = new int[n + 1];
        int *parent3 = new int[n + 1];
        for (int i = 0; i < n; i++)
        {
            cost3[i] = INT_MAX;
            visited3[i] = 0;
        }
        cost3[s3] = 0;
        parent3[s3] = s3;
        Heap he;
        pair<int,int> p1={cost3[s3],s3};

        while (he.size()>0)
        {
            p1 = he.getMin();
            he.deleteKey();
            int vertex = p1.second;
            visited3[vertex] = 1;
            for (int i = 0; i < vec[vertex].size(); i++)
            {
                int adj = vec[vertex][i].second;
                if (visited3[adj] == 0 && (cost3[vertex] + vec[vertex][i].first) < cost3[adj]) {
                    cost3[adj] = cost3[vertex] + vec[vertex][i].first;
                    parent3[adj] = vertex;
                    he.insert(cost3[adj],adj);
                }
            }
        }
        //cout << "Shortest path cost: " << cost[d] << endl;
        vector<int> ans3;
        while (parent3[d3] != d3) {
            ans3.push_back(d3);
            d3= parent3[d3];
        }
        ans3.push_back(s3);
        /*for (int i = ans.size() - 1; i > 0; i--) {
            cout << ans[i] << "->";
        }
        cout << ans[0] << endl;*/
        auto t3=std::chrono::high_resolution_clock::now();
        double ti3=std::chrono::duration<double,std::milli>(t3-st3).count();
        cout<<ans.size()-1<<" "<<cost[des]<<" "<<ti1<<" "<<ti3<<endl;
        output<<ans.size()-1<<" "<<cost[des]<<" "<<ti1<<" "<<ti3<<endl;
    }
    output.close();
}
