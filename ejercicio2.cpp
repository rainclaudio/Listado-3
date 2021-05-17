#include <iostream>
#include <vector>
typedef std::vector<int> v;
/*
PROBLEM ID: 793	"Network Connections"
Solved by: Claudio Rain
*/

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
void unionSet(int i , int j){
      if(!isSameSet(i,j)){

        int x = findSet(i), y = findSet(j);
        if(rank[i] > rank[j]) p[y] = x;
        else {
          p[x] = y;
          if(rank[x] == rank[y]) rank[y]++;
        }
      }

  }


int main(int argc, char const *argv[]) {
  int n;
  scanf("%d\n",&n);
  std::string s;
    char qorc;
  int var1,var2, successCases = 0,unsuccessCases = 0;
  int n2;
  while(n--){
    scanf("%d\n",&n2);
    UnionFind(n2);

    while(1){
      if(!getline(std::cin,s) || s.empty()) break;
        sscanf(s.c_str(),"%c %d %d",&qorc,&var1,&var2);

      if(qorc == 'c'){
        unionSet(var1,var2);
      } else {
        if(isSameSet(var1,var2))successCases++;
        else unsuccessCases++;
      }

    }
    printf("%d,%d\n",successCases,unsuccessCases);
    if(n!=0)printf("\n");
    successCases = unsuccessCases = 0;
    p.clear();
    rank.clear();
  }
  return 0;
}
