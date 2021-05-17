#include <iostream>
#include <vector>
#include <string>
#include <map>
typedef std::vector<int> v;
/*
PROBLEM ID: 11503	"Virtual Friends"
Solved by: Claudio Rain
*/

v p,rank;
std::map<std::string,int> mymap;
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
long long unionSet(int i , int j){
  int x = findSet(i), y = findSet(j);

      if(!isSameSet(i,j)){

          p[y] = x;
          rank[x] += rank[y];

      }
    return rank[x];
}


int main(int argc, char const *argv[]) {
  int n;
  scanf("%d",&n);
  std::string s;
  int n2,fr_formed;
  std::string name1,name2;
  while(n--){
    scanf("%d",&fr_formed);
    UnionFind(2*fr_formed);
    int id = 0;
    while(fr_formed--){
        std::cin >> name1;
        std::cin >> name2;
        std::map<std::string,int>::iterator it1;
        it1 = mymap.find(name1);
        if(it1 == mymap.end()){
          mymap[name1] = id;
          rank[id] = 1;
          id++;
        }
        it1 = mymap.find(name2);
        if(it1 == mymap.end()){
          mymap[name2] = id;
          rank[id] = 1;
          id++;
        }
        printf("%d\n",unionSet(mymap[name1],mymap[name2]));
      // if(n!=0)printf("\n");
      // successCases = unsuccessCases = 0;
      name1 = name2 = "";
    }
    mymap.clear();
    p.clear();
    rank.clear();
  }
  return 0;
}
