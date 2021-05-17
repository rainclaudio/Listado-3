#include <iostream>
#include <vector>
/*
PROBLEM ID: 11235
Solved by: Claudio Rain
*/
typedef std::vector<int> v;

v Array;
v segMentTree;
int n;
int left(int p){
  return p<<1;
}
int right(int p){
  return (p<<1) + 1;
}
void build(int p, int L, int R){
  if(L == R) segMentTree[p] = L;
  else {

    build(left(p),L, (L + R) /2);
    build(right(p),(L + R) /2 + 1, R);
    int p1 = segMentTree[left(p)];
    int p2 = segMentTree[right(p)];
    if(Array[p1] <= Array[p2]) segMentTree[p] = p1;
    else segMentTree[p] = p2;

  }
}

int range_min_query_util(int p, int L, int R,int i,int j){
  if(i > R || j < L) return -1;
  if(L >= i &&  R <= j) return segMentTree[p];

  int p1 = range_min_query_util(left(p),L,(L+R)/2,i,j);
  int p2 = range_min_query_util(right(p),(L+R)/2 + 1,R,i,j);

  if(p1 == -1)return p2;
  if(p2 == -1)return p1;

  if(Array[p1] <= Array[p2]) return  p1;
  else return p2;


}
int range_min_query(int i, int j){
  return range_min_query_util(1,0,n-1,i,j);
}
int main(int argc, char const *argv[]) {
  int querys,n,i,j;
  while(!std::cin.eof()){
    scanf("%d %d",&n,&querys);
    Array.push_back(0);
    int var;
    while(n--){
      std::cin >> var;
      Array.push_back(var);
    }
    segMentTree.assign(4 * Array.size(),0);
    build(1,0,Array.size()-1);
    while(querys--){
      std::cin >> i >> j;
      range_min_query(i,j);
    }
    Array.clear();
  }

  return 0;
}
