#include <iostream>
#include <vector>
#include <utility>
#include <map>
/*
PROBLEM ID: 11235 "Frequent values"
Solved by: Claudio Rain
*/
typedef std::vector<int> v;
typedef std::pair<int,int> Intpair;
typedef std::vector<Intpair> SegmentTree;
v Array;
SegmentTree segMentTree;
std::map<int,int> mymap;
int left(int p){
  return p<<1;
}
int right(int p){
  return (p<<1) + 1;
}
void printSegmentTree(){
  int i = 0;
  std::cout << "printing: " << '\n';
  for(auto it: segMentTree){
    std::cout<<i<<": " << it.first<<'\t'<<it.second << '\n';
    i++;
  }
}
void build(int p, int L, int R){
  std::cout << "BUILD: [p] = "<<p <<" [L] = "<<L <<" [R] = "<<R << '\n';
  if(L == R){
      // frecuencia relativa
      segMentTree[p] = std::make_pair(L,1);
      // frecuencia absoluta
      mymap[Array[L]]++;
  }else {

    build(left(p),L, (L + R) /2);
    build(right(p),(L + R) /2 + 1, R);
    std::cout << "[EVALUATING]: "<<p << '\n';
    // Índice
    Intpair p1 = segMentTree[left(p)];
    Intpair p2 = segMentTree[right(p)];
    // si son iguales, nos sirve cualquier índice para verificar si más adelante nos aparecen
    // nuevas coincidencias
    if(Array[p1.first] == Array[p2.first]){
      segMentTree[p] = std::make_pair(p2.first,p1.second + p2.second);
    }else{
      // si no:
      if(p1.second == p2.second){
        //caso1: las frec son iguales, tomamos el índice mayor para comparar más adelante
        if(p1.second == 1){
          segMentTree[p] = p2;
        } else {
          if(mymap[Array[p1.first]] > mymap[Array[p2.first]]){
            segMentTree[p] = std::make_pair(p1.first,mymap[Array[p1.second]]);
          } else {
            segMentTree[p] = std::make_pair(p2.first,mymap[Array[p2.second]]);
          }
        }
      } else if(p1.second > p2.second) segMentTree[p] = p1;
      else segMentTree[p] = p2;

    }
  }
}

Intpair range_min_query_util(int p, int L, int R,int i,int j){
  if(i > R || j < L) return std::make_pair(-1,-1); //no overlap
  if(L >= i &&  R <= j) return segMentTree[p];//complete overlap

  //check both parts
  Intpair p1 = range_min_query_util(left(p),L,(L+R)/2,i,j);
  Intpair p2 = range_min_query_util(right(p),(L+R)/2 + 1,R,i,j);

  //si estamos fuera del rango
  if(p1.first == -1)return p2;
  if(p2.first == -1)return p1;

  if(p1.second <= p2.second) return p2;
  else return p1;

}
int range_min_query(int i, int j,int n){
  Intpair p1 = range_min_query_util(1,0,n-1,i,j);
  return p1.second;
}
int main(int argc, char const *argv[]) {
  int querys,n,i,j;
  while(true){
    scanf("%d %d",&n,&querys);
    if(n == 0) break;
    int var;
    int last;
    std::cin >> var;
    last = var;
    n--;
    mymap[var] = 0;
    Array.push_back(var);
    while(n--){
      std::cin >> var;
      if(last != var){
        last = var;
        mymap[var] = 0;
      }
      Array.push_back(var);
    }

    segMentTree.assign(4 * Array.size(),{0,0});
    build(1,0,Array.size()-1);
    printSegmentTree();
    while(querys--){
      std::cin >> i >> j;
      std::cout <<range_min_query(i-1,j-1,Array.size())<<'\n';
    }
    segMentTree.clear();
    Array.clear();
  }

  return 0;
}
