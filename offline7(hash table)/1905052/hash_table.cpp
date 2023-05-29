#include<bits/stdc++.h>
#include<chrono>
#include <cstdlib>
#include "ADT.h"
#include "list.h"
using namespace std;
class Sep_chaining
{
    int siz;
    LList<int> *ob;
public:
    Sep_chaining(int sz)
    {
        siz=sz;
        ob=new LList<int>[siz+1];
    }
    void insert_value(string str,int value)
    {
        long long ind=hash_function1(str);
        int index=hash_function2(ind,siz);
        ob[index].insert(value);
    }
    void delete_value(string str,int value)
    {
        long long ind=hash_function1(str);
        int index=hash_function2(ind,siz);
        ob[index].moveToStart();
        int k=ob[index].length();
        for(int i=0; i<k; i++)
        {
            if(ob[index].getValue()==value)
            {
                ob[index].remove();
                return;
            }
            ob[index].next();
        }
    }
    int search_value(string str,int value)
    {
        long long ind=hash_function1(str);
        int index=hash_function2(ind,siz);
        ob[index].moveToStart();
        int k=ob[index].length();
        for(int i=0; i<k; i++)
        {
            if(ob[index].getValue()==value)
            {
                return 1;
            }
            ob[index].next();
        }
        return 0;
    }
    long long hash_function1(string str)
    {
        long long sum=str[0];
        //sum=sum%m;
        int siz=str.size();
        for(int i=1; i<siz; i++)
        {
            sum+=str[i]*pow(31,i);
            //sum=sum%m;
        }
        //return sum%m;
        return sum;
    }
    int hash_function2(long long number,int m)
    {
        return number%m;
    }
};
class Linear_Probing
{
    int siz;
    int *T;
    int probe;
public:
    Linear_Probing(int sz)
    {
        siz=sz;
        T=new int[siz+1];
        for(int i=0; i<siz; i++)
        {
            T[i]=-1;//-1 as a NIL
        }
    }
    void set_probe(int x)
    {
        probe=x;
    }
    int get_probe()
    {
        return probe;
    }
    void insert_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1||T[index]==-2)
            {
                T[index]=value;
                return;
            }
        }
    }
    void delete_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]==-2)
            {
                continue;
            }
            else if(T[index]==value)
            {
                T[index]=-2;
                return;
            }
        }
    }
    int search_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            probe++;
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]==-2)
            {
                continue;
            }
            else if(T[index]==value)
            {
                return 1;
            }
        }
        return 0;
    }
    long long hash_function1(string str)
    {
        long long sum=str[0];
        //sum=sum%m;
        int siz=str.size();
        for(int i=1; i<siz; i++)
        {
            sum+=str[i]*pow(31,i);
            //sum=sum%m;
        }
        //return sum%m;
        return sum;
    }
    int hash_function2(long long number,int m,int i)
    {
        return (number+i)%m;
    }
};
class Quadratic_Probing
{
    int siz;
    int *T;
    int probe;
public:
    Quadratic_Probing(int sz)
    {
        siz=sz;
        T=new int[siz+1];
        for(int i=0; i<siz; i++)
        {
            T[i]=-1;
        }
    }
    void set_probe(int x)
    {
        probe=x;
    }
    int get_probe()
    {
        return probe;
    }
    void insert_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1||T[index]==-2)
            {
                T[index]=value;
                return;
            }
        }
    }
    void delete_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]!=-2&&T[index]==value)
            {
                T[index]=-2;
                return;
            }
        }
    }
    int search_value(string str,int value)
    {
        long long ind=hash_function1(str);
        for(int i=0; i<siz; i++)
        {
            probe++;
            int index=hash_function2(ind,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]!=-2&&T[index]==value)
            {
                return 1;
            }
        }
        return 0;
    }
    long long hash_function1(string str)
    {
        long long sum=str[0];
        //sum=sum%m;
        int siz=str.size();
        for(int i=1; i<siz; i++)
        {
            sum+=str[i]*pow(31,i);
            //sum=sum%m;
        }
        //return sum%m;
        return sum;
    }
    int hash_function2(long long number,int m,int i)
    {
        int c1=1,c2=2;
        return (number+c1*i+c2*i*i)%m;
    }
};
class Double_Hashing
{
    int siz;
    int *T;
    int probe;
public:
    Double_Hashing(int sz)
    {
        siz=sz;
        T=new int[siz+1];
        for(int i=0; i<siz; i++)
        {
            T[i]=-1;
        }
    }
    void set_probe(int x)
    {
        probe=x;
    }
    int get_probe()
    {
        return probe;
    }
    void insert_value(string str,int value)
    {
        long long ind1=hash_function1(str);
        long long ind2=hash_function2(siz);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function3(ind1,ind2,siz,i);
            if(T[index]==-1||T[index]==-2)
            {
                T[index]=value;
                return;
            }
        }
    }
    void delete_value(string str,int value)
    {
        long long ind1=hash_function1(str);
        long long ind2=hash_function2(siz);
        for(int i=0; i<siz; i++)
        {
            int index=hash_function3(ind1,ind2,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]!=-2&&T[index]==value)
            {
                T[index]=-2;
                return;
            }
        }
    }
    int search_value(string str,int value)
    {
        long long ind1=hash_function1(str);
        long long ind2=hash_function2(siz);
        for(int i=0; i<siz; i++)
        {
            probe++;
            int index=hash_function3(ind1,ind2,siz,i);
            if(T[index]==-1)
            {
                break;
            }
            else if(T[index]!=-2&&T[index]==value)
            {
                return 1;
            }
        }
        return 0;
    }
    long long hash_function1(string str)
    {
        long long sum=str[0];
        //sum=sum%m;
        int siz=str.size();
        for(int i=1; i<siz; i++)
        {
            sum+=str[i]*pow(31,i);
            //sum=sum%m;
        }
        //return sum%m;
        return sum;
    }
    long long hash_function2(int m)
    {
        long long tmp=rand();
        return tmp%m;
    }
    int hash_function3(long long number1,long long number2,int m,int i)
    {
        return (number1+i*number2)%m;
    }
};
string randomly_generated_word()
{
    string str="";
    for(int i=1; i<=7; i++)
    {
        int rand_word=rand()%26;
        char ch='a'+rand_word;
        str+=ch;
    }
    return str;
}
int is_prime(int n)
{
    if (n == 1 || n == 0)
    {
        return 0;
    }
    for (int i = 2; i < (n / 2); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int find_prime(int n)
{
    if(n%2==0)
        n++;
    while(is_prime(n)==0)
    {
        n+=2;
    }
    return n;
}
long long hash_function1(string str)
{
    long long sum=str[0];
    int siz=str.size();
    for(int i=1; i<siz; i++)
    {
        sum+=str[i]*pow(31,i);
    }
    return sum;
}
int hash_function2(long long number,int m)
{
    return number%m;
}
void check_hash_func(int m)
{
    vector<string>vec;
    for(int i=1; i<=100;)
    {
        set<string>s;
        string word=randomly_generated_word();
        if(s.count(word)>0)
        {
            continue;
        }
        s.insert(word);
        vec.push_back(word);
        i++;
    }
    set<int>ans;
    for(int i=0; i<100; i++)
    {
        long long num=hash_function1(vec[i]);
        int nu=hash_function2(num,m);
        ans.insert(nu);
    }
    cout<<"The number of unique hash values produced by randomly generated 100 words:"<<ans.size()<<endl;
}
int main()
{
    check_hash_func(100);
    double sep_chaining[15][10];
    double lin_probing[15][10];
    double quad_probing[15][10];
    double double_hashing[15][10];
    int m;
    cin>>m;
    if(is_prime(m)==0)
    {
        m=find_prime(m);
    }
    cout<<"Separate Chaining"<<endl;
    for(double j=0.4; j<=0.9; j+=0.1)
    {
        vector<pair<string,int>>v;
        int siz=m*j;
        for(int i=1; i<=siz;)
        {
            set<string>s;
            string word=randomly_generated_word();
            if(s.count(word)>0)
            {
                continue;
            }
            s.insert(word);
            int value=s.size();
            v.push_back({word,i});
            i++;
            //cout<<randomly_generated_word()<<endl;
        }
        Sep_chaining sep(m);
        for(int i=0; i<v.size(); i++)
        {
            string wd=v[i].first;
            int val=v[i].second;
            sep.insert_value(wd,val);
        }
        int k=0.1*siz;
        auto s1=std::chrono::high_resolution_clock::now();
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            int srch=sep.search_value(wd,val);
        }
        auto t1=std::chrono::high_resolution_clock::now();
        double ti1=std::chrono::duration<double,std::milli>(t1-s1).count();
        ti1=ti1/k;
        set<pair<string,int>>mp;
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            sep.delete_value(wd,val);
            if(mp.size()<=k/2)
            {
                mp.insert({wd,val});
            }
        }
        for(int i=0; i<v.size(); i++)
        {
            if(mp.size()>=k)
            {
                break;
            }
            else if(mp.count({v[i].first,v[i].second})<=0)
            {
                mp.insert({v[i].first,v[i].second});
            }
        }
        auto s2=std::chrono::high_resolution_clock::now();
        for(auto i:mp)
        {
            string wd=i.first;
            int val=i.second;
            sep.search_value(wd,val);
        }
        auto t2=std::chrono::high_resolution_clock::now();
        double ti2=std::chrono::duration<double,std::milli>(t1-s1).count();
        ti2=ti2/k;
        cout<<"Load Factor"<<":"<<j<<" "<<"Avg_search_time_before_deletion:"<<ti1<<" "<<"Avg_search_time_After_deletion:"<<ti2<<endl;
        int jj=j*10;
        sep_chaining[jj][0]=ti1;
        sep_chaining[jj][1]=-1;
        sep_chaining[jj][2]=ti2;
        sep_chaining[jj][3]=-1;
    }
    cout<<"Linear Probing"<<endl;
    for(double j=0.4; j<=0.9; j+=0.1)
    {
        vector<pair<string,int>>v;
        int siz=m*j;
        for(int i=1; i<=siz;)
        {
            set<string>s;
            string word=randomly_generated_word();
            if(s.count(word)>0)
            {
                continue;
            }
            s.insert(word);
            int value=s.size();
            v.push_back({word,i});
            i++;
        }
        Linear_Probing Lin(m);
        for(int i=0; i<v.size(); i++)
        {
            string wd=v[i].first;
            int val=v[i].second;
            Lin.insert_value(wd,val);
        }
        int k=0.1*siz;
        auto s1=std::chrono::high_resolution_clock::now();
        Lin.set_probe(0);
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            int srch=Lin.search_value(wd,val);
        }
        double prob_before=(Lin.get_probe()*1.0)/(k);
        auto t1=std::chrono::high_resolution_clock::now();
        double ti1=std::chrono::duration<double,std::milli>(t1-s1).count();
        ti1=ti1/k;
        set<pair<string,int>>mp;
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            Lin.delete_value(wd,val);
            if(mp.size()<=k/2)
            {
                mp.insert({wd,val});
            }
        }
        for(int i=0; i<v.size(); i++)
        {
            if(mp.size()>=k)
            {
                break;
            }
            else if(mp.count({v[i].first,v[i].second})<=0)
            {
                mp.insert({v[i].first,v[i].second});
            }
        }
        auto s2=std::chrono::high_resolution_clock::now();
        Lin.set_probe(0);
        for(auto i:mp)
        {
            string wd=i.first;
            int val=i.second;
            Lin.search_value(wd,val);
        }
        double prob_after=(Lin.get_probe()*1.0)/(k);
        auto t2=std::chrono::high_resolution_clock::now();
        double ti2=std::chrono::duration<double,std::milli>(t2-s2).count();
        ti2=ti2/k;
        cout<<"Load Factor"<<":"<<j<<" "<<"Avg_search_time_before_deletion:"<<ti1<<" "<<"Avg_number_of_probes_before_deletion:"<<prob_before<<" "<<"Avg_search_time_After_deletion:"<<ti2<<" "<<"Avg_number_of_probes_after_deletion:"<<prob_after<<endl;
        int jj=j*10;
        lin_probing[jj][0]=ti1;
        lin_probing[jj][1]=prob_before;
        lin_probing[jj][2]=ti2;
        lin_probing[jj][3]=prob_after;
    }
    cout<<"Quadratic Probing"<<endl;
    for(double j=0.4; j<=0.9; j+=0.1)
    {
        vector<pair<string,int>>v;
        int siz=m*j;
        for(int i=1; i<=siz;)
        {
            set<string>s;
            string word=randomly_generated_word();
            if(s.count(word)>0)
            {
                continue;
            }
            s.insert(word);
            int value=s.size();
            v.push_back({word,i});
            i++;
            //cout<<randomly_generated_word()<<endl;
        }
        Quadratic_Probing Quad(m);
        for(int i=0; i<v.size(); i++)
        {
            string wd=v[i].first;
            int val=v[i].second;
            Quad.insert_value(wd,val);
        }
        int k=0.1*siz;
        auto s1=std::chrono::high_resolution_clock::now();
        Quad.set_probe(0);
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            int srch=Quad.search_value(wd,val);
        }
        double prob_before=(Quad.get_probe()*1.0)/(k);
        auto t1=std::chrono::high_resolution_clock::now();
        double ti1=std::chrono::duration<double,std::milli>(t1-s1).count();
        ti1=ti1/k;
        set<pair<string,int>>mp;
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            Quad.delete_value(wd,val);
            if(mp.size()<=k/2)
            {
                mp.insert({wd,val});
            }
        }
        for(int i=0; i<v.size(); i++)
        {
            if(mp.size()>=k)
            {
                break;
            }
            else if(mp.count({v[i].first,v[i].second})<=0)
            {
                mp.insert({v[i].first,v[i].second});
            }
        }
        auto s2=std::chrono::high_resolution_clock::now();
        Quad.set_probe(0);
        for(auto i:mp)
        {
            string wd=i.first;
            int val=i.second;
            Quad.search_value(wd,val);
        }
        double prob_after=(Quad.get_probe()*1.0)/(k);
        auto t2=std::chrono::high_resolution_clock::now();
        double ti2=std::chrono::duration<double,std::milli>(t2-s2).count();
        ti2=ti2/k;
        cout<<"Load Factor"<<":"<<j<<" "<<"Avg_search_time_before_deletion:"<<ti1<<" "<<"Avg_number_of_probes_before_deletion:"<<prob_before<<" "<<"Avg_search_time_After_deletion:"<<ti2<<" "<<"Avg_number_of_probes_after_deletion:"<<prob_after<<endl;
        int jj=j*10;
        quad_probing[jj][0]=ti1;
        quad_probing[jj][1]=prob_before;
        quad_probing[jj][2]=ti2;
        quad_probing[jj][3]=prob_after;
    }
    cout<<"Double Hashing"<<endl;
    for(double j=0.4; j<=0.9; j+=0.1)
    {
        vector<pair<string,int>>v;
        int siz=m*j;
        for(int i=1; i<=siz;)
        {
            set<string>s;
            string word=randomly_generated_word();
            if(s.count(word)>0)
            {
                continue;
            }
            s.insert(word);
            int value=s.size();
            v.push_back({word,i});
            i++;
        }
        Double_Hashing dbl(m);
        for(int i=0; i<v.size(); i++)
        {
            string wd=v[i].first;
            int val=v[i].second;
            dbl.insert_value(wd,val);
        }
        int k=0.1*siz;
        auto s1=std::chrono::high_resolution_clock::now();
        dbl.set_probe(0);
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            int srch=dbl.search_value(wd,val);
        }
        double prob_before=(dbl.get_probe()*1.0)/(k);
        auto t1=std::chrono::high_resolution_clock::now();
        double ti1=std::chrono::duration<double,std::milli>(t1-s1).count();
        ti1=ti1/k;
        set<pair<string,int>>mp;
        for(int i=1; i<=k; i++)
        {
            int j=rand()%siz;
            string wd=v[j].first;
            int val=v[j].second;
            dbl.delete_value(wd,val);
            if(mp.size()<=k/2)
            {
                mp.insert({wd,val});
            }
        }
        for(int i=0; i<v.size(); i++)
        {
            if(mp.size()>=k)
            {
                break;
            }
            else if(mp.count({v[i].first,v[i].second})<=0)
            {
                mp.insert({v[i].first,v[i].second});
            }
        }
        auto s2=std::chrono::high_resolution_clock::now();
        dbl.set_probe(0);
        for(auto i:mp)
        {
            string wd=i.first;
            int val=i.second;
            dbl.search_value(wd,val);
        }
        double prob_after=(dbl.get_probe()*1.0)/(k);
        auto t2=std::chrono::high_resolution_clock::now();
        double ti2=std::chrono::duration<double,std::milli>(t2-s2).count();
        ti2=ti2/k;
        cout<<"Load Factor"<<":"<<j<<" "<<"Avg_search_time_before_deletion:"<<ti1<<" "<<"Avg_number_of_probes_before_deletion:"<<prob_before<<" "<<"Avg_search_time_After_deletion:"<<ti2<<" "<<"Avg_number_of_probes_after_deletion:"<<prob_after<<endl;
        int jj=j*10;
        double_hashing[jj][0]=ti1;
        double_hashing[jj][1]=prob_before;
        double_hashing[jj][2]=ti2;
        double_hashing[jj][3]=prob_after;
    }
    for(double j=0.4; j<=0.9; j+=0.1)
    {
        cout<<"Performance of various collision resolution methods in load factor "<<j<<endl;
        int jj=j*10;
        for(int i=0; i<4; i++)
        {
            if(sep_chaining[jj][i]<0)
            {
                cout<<"N/A"<<" ";
            }
            else
            {
                cout<<sep_chaining[jj][i]<<" ";
            }
        }
        cout<<endl;
        for(int i=0; i<4; i++)
        {
            cout<<lin_probing[jj][i]<<" ";
        }
        cout<<endl;
        for(int i=0; i<4; i++)
        {
            cout<<quad_probing[jj][i]<<" ";
        }
        cout<<endl;
        for(int i=0; i<4; i++)
        {
            cout<<double_hashing[jj][i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
