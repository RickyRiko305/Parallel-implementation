#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
#define ll long long int
int b[100];
int mainval[100];
vector <int> v[100];
void elu(int x, int &i){
  b[x] = 1;
  mainval[i++] = x;
  for (auto h = v[x].begin(); h != v[x].end(); h++) {
    // cout << *it << endl;
    if(!b[*h]){
      elu(*h, i);
      mainval[i++] = x;
    }
}
}
int main(){
  int n,x,y;
  cin>>n;


  memset(b,0,100);

  for(int i= 0; i<n; i++){
    cin>>x>>y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  int g=0;
  vector<pair<int, int> >eular_pair;//[2*n];
  elu(1,g);
  int r,last;
  for(int i=0; i<(2*n+1); i++){
    cout<<mainval[i]<<" ";
   r = mainval[i];
    if(i>0){
      eular_pair.push_back(make_pair(last,r));
    }
    last = mainval[i];
  }
  cout<<"\n";
  for (int h = 0; h < (2*n); h++){
    cout<<eular_pair[h].first <<" "<<eular_pair[h].second<<"\n";
  }
  cout<<"\nhfsjhhs\n";
  int root = 2;
  for (auto h = v[x].begin(); h != v[x].end(); h++) {
    last = *h;
  }
  //last = v[2][sizeof(v[2])];
  int next[2*n];
  for(int h = 0; h<(2*n-1); h++){
    next[h] = h+1;
  }
  next[2*n-1] = 0;
  int temp;
  for (int h = 0; h < (2*n); h++){
    if((eular_pair[h].first == 2) && (eular_pair[h].second==last)){
      temp = h;
    }
  //  cout<<eular_pair[h].first <<" "<<eular_pair[h].second<<"\n";
  }
  int h;
  h=next[temp];
  //h = next[temp];
  while(1/*h!=temp*/){
    cout<<eular_pair[next[h]].first <<" "<<eular_pair[next[h]].second<<"\n";
    h = next[h];
    if(h==next[temp]){
      break;
    }
  }
  return 0;
}
