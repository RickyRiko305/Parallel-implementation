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
void dfs2(int loc, int par, vector<int> &v)
{
    v[loc] = 0;
    for(int i:adj[loc])
        if(i!=par)
        {
            dfs2(i,loc,v);
            v[loc]+=v[i]+1;
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
        dfs2(root,-1,v);
        cout<<"Serial no of descendants:";
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
        vector<int> a(n+1),b(n+1);
        #pragma omp parallel for
        for(int i=1;i<2*n-1;i++)
        {
            if(parent[eulertour[i]]==eulertour[i-1])
                a[eulertour[i]] = i;
        }
        #pragma omp parallel for
        for(int i=0;i<2*n-2;i++)
        {
            if(parent[eulertour[i]]==eulertour[i+1])
                b[eulertour[i]] = i;
        }
        #pragma omp parallel for
        for(int i=1;i<=n;i++)
        {
            v2[i] = (b[i]-a[i])/2;
        }
        v2[root] = n-1;
        cout<<"Parallel no of descendants:";
        for(int i=1;i<=n;i++)
        {
            cout<<v2[i]<<" ";
        }
        cout<<endl;
        auto en = high_resolution_clock::now();
        par_time = duration_cast<microseconds>(en-st).count();
        cout<<"Parallel execution time:"<<par_time<<"us"<<endl;
    }
    cout<<"Speedup:"<<((double)ser_time/par_time)<<endl;
    return 0;
}