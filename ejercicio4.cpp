#include <iostream>
#include <vector>
/*
PROBLEM ID: 10608 "Friends"
Solved by: Claudio Rain
*/
typedef std::vector<int> v;
v p,rank;

void UnionFind(int N){
    for (size_t i = 0; i <= N; i++) {
      p.push_back(i);
    }
    rank.assign(N+1,0);
}
int findSet(int i){
    return (p[i] == i)? i:(p[i] = findSet(p[i]));
}
bool isSameSet(int i , int j){
    return findSet(i) == findSet(j);
}
int unionSet(int i , int j){
  int x = findSet(i), y = findSet(j);

      if(!isSameSet(i,j)){

          p[y] = x;
          rank[x] += rank[y];

      }
    return rank[x];
}
void solve(){
  int Ncitizens;
  int dataSets;
  std::cin >> dataSets;
  while(dataSets--){
    int n,m;
    std::cin >>n>>m;
    UnionFind(n);
    int i,j,answer = 1;
    while(m--){
      std::cin >> i >> j;
      if(rank[i] == 0)rank[i] = 1;
      if(rank[j] == 0)rank[j] = 1;
      int var = unionSet(i,j);
      if(var > answer) answer = var;
    }
    std::cout << answer<< '\n';

    rank.clear();
    p.clear();
  }

}
int main(int argc, char const *argv[]) {
  solve();
  return 0;
}
