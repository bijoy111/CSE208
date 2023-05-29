#include<bits/stdc++.h>
#include<chrono>
#include <cstdlib>
using namespace std;
class Double_Hashing
{
    int siz;
    vector<pair<string,int>>T;
    int probe;
    int value=0;
public:
    Double_Hashing(int sz)
    {
        siz=sz;
        if(is_prime(siz)==0)
        {
            siz=find_prime(siz);
        }
        for(int i=0; i<siz; i++)
        {
            T.push_back({"NULL",-1});
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
            if(T[index].second==-1||T[index].second==-2)
            {
                T[index].first=str;
                T[index].second=value;
                value++;
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
            if(T[index].second==-1)
            {
                break;
            }
            else if(T[index].second!=-2&&T[index].second==value)
            {
                T[index].second=-2;
                value--;
                //check is load factor below 0.4
                int load_fac=(value*10)/siz;
                if(load_fac<4)
                {
                    int m_new=siz/2;
                    if(is_prime(m_new)==0)
                    {
                        m_new=find_prime(m_new);
                    }
                    vector<pair<string,int>>Table;
                    for(int i=0; i<m_new; i++)
                    {
                        Table.push_back({"NULL",-1});
                    }
                    for(int i=0; i<siz; i++)
                    {
                        if(T[i].second!=-1&&T[i].second!=-2)
                        {
                            int j=ind1%m_new;
                            Table[j].first=T[i].first;
                            Table[j].second=T[i].second;
                        }
                    }
                    siz=m_new;
                    for(int i=0; i<siz; i++)
                    {
                        T[i].first=Table[i].first;
                        T[i].second=Table[i].second;
                    }
                }
                return;
            }
        }
    }
    void rehash()
    {
        int m_new=siz*2;
        if(is_prime(m_new)==0)
        {
            m_new=find_prime(m_new);
        }
        vector<pair<string,int>>Table;
        for(int i=0; i<m_new; i++)
        {
            Table.push_back({"NULL",-1});
        }
        for(int i=0; i<siz; i++)
        {
            if(T[i].second!=-1&&T[i].second!=-2)
            {
                string str=T[i].first;
                long long ind1=hash_function1(str);
                int j=ind1%m_new;
                Table[j].first=T[i].first;
                Table[j].second=T[i].second;
            }
        }
        siz=m_new;
        for(int i=0; i<siz; i++)
        {
            T[i].first=Table[i].first;
            T[i].second=Table[i].second;
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
            if(T[index].second==-1)
            {
                break;
            }
            else if(T[index].second!=-2&&T[index].second==value)
            {
                return 1;
            }
        }
        return 0;
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
    long long hash_function2(int m)
    {
        long long tmp=rand();
        return tmp%m;
    }
    int hash_function3(long long number1,long long number2,int m,int i)
    {
        return (number1+i*number2)%m;
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
int main()
{
    int m;
    cin>>m;
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
        int var=0;
        for(int i=0; i<v.size(); i++)
        {
            var++;
            string wd=v[i].first;
            int val=v[i].second;
            dbl.insert_value(wd,val);
            if(var>100)
            {
                var=0;
                int k=0.1*i;
                dbl.set_probe(0);
                for(int i=1; i<=k; i++)
                {
                    int j=rand()%siz;
                    string wd=v[j].first;
                    int val=v[j].second;
                    int srch=dbl.search_value(wd,val);
                }
                int prob=(dbl.get_probe())/(k);
                if(prob>2)
                {
                    dbl.rehash();
                }
            }
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
            dbl.delete_value(wd,val);   //delete
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
    }
    return 0;
}

