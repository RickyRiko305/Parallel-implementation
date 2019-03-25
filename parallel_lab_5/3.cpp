#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using namespace chrono;
int n,root;
vector<int> eulertour,parent;
vector<vector<int> > adj;
void dfs(int loc, int par)
{
    parent[loc] = par;
    eulertour.push_back(loc);
    for(int i:adj[loc])
    {
        if(i!=par)
        {
            dfs(i,loc);
            eulertour.push_back(loc);
        }
    }
}
void makeeulertour()
{
    int x,y;
    cin>>n>>root;
    adj.resize(n+1);
    parent.resize(n+1);
    eulertour.reserve(2*n-1);
    for(int i=1;i<n;i++)
    {
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(root,-1); // root has no parent
}
void par_prefix(vector<int> &in)
{
    int n = in.size();
    vector<int> in2(n);
    int lgn = 0;
    while((1<<lgn)<n) lgn++; //calculates ceil(log2(n))
    vector<int> prev(n);
    for(int lg=0;lg<lgn;lg++)
    {
        #pragma omp parallel for
        for(int i=(1<<lg);i<n;i++)
        {
            in2[i] = in[i]+in[i-(1<<lg)];
        }
        #pragma omp parallel for
        for(int i=0;i<(1<<lg);i++)
        {
            in2[i] = in[i];
        }
        swap(in,in2); //O(1), only references are swapped
    }
}
void dfs2(int loc, int par, vector<int> &v, int &cnt)
{
    v[loc] = cnt++;
    for(int i:adj[loc])
        if(i!=par)
        {
            dfs2(i,loc,v,cnt);
        }
}
int32_t main() 
{
    makeeulertour();
    vector<int> v(n+1),v2(n+1);
    int ser_time, par_time;
    {
        //serial part
        auto st = high_resolution_clock::now();
        int cnt = 1;
        dfs2(root,-1,v,cnt);
        cout<<"Serial preorder numbering:";
        for(int i=1;i<=n;i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
        auto en = high_resolution_clock::now();
        ser_time = duration_cast<microseconds>(en-st).count();
        cout<<"Serial execution time:"<<ser_time<<"us"<<endl;
    }
    {
        //parallel part
        auto st = high_resolution_clock::now();
        vector<int> a(2*n-1,0);
        #pragma omp parallel for
        for(int i=1;i<2*n-1;i++)
        {
            if(parent[eulertour[i]]==eulertour[i-1])
                a[i] = 1;
        }
        a[0] = 1;
        par_prefix(a);
        #pragma omp parallel for
        for(int i=1;i<2*n-1;i++)
        {
            if(parent[eulertour[i]]==eulertour[i-1])
                v2[eulertour[i]] = a[i];
        }
        v2[root] = 1;
        cout<<"Parallel preorder numbering:";
        for(int i=1;i<=n;i++)
        {
            cout<<v2[i]<<" ";
        }
        cout<<endl;
        auto en = high_resolution_clock::now();
        par_time = duration_cast<microseconds>(en-st).count();
        cout<<"Size of truncated array:"<<v2.size()<<endl;
        cout<<"Parallel execution time:"<<par_time<<"us"<<endl;
    }
    cout<<"Speedup:"<<((double)ser_time/par_time)<<endl;
    return 0;
}