#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
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
  if(L == R) segMentTree[p] = Array[L];
  else {

    build(left(p),L, (L + R) /2);
    build(right(p),(L + R) /2 + 1, R);
    int p1 = segMentTree[left(p)];
    int p2 = segMentTree[right(p)];
    segMentTree[p] = p1 + p2;


  }
}

int range_min_query_util(int p, int L, int R,int i,int j){
  if(i > R || j < L) return -1;
  if(L >= i &&  R <= j){
    return segMentTree[p];
    // std::cout << "p: " << p << " "<<segMentTree[p]<< '\n';

  }
  // std::cout << "p: " << p << " "<<segMentTree[p]<< '\n';

  int p1 = range_min_query_util(left(p),L,(L+R)/2,i,j);
  int p2 = range_min_query_util(right(p),(L+R)/2 + 1,R,i,j);

  if(p1 == -1)return p2;
  if(p2 == -1)return p1;
  return  p1+p2;
}
int range_min_query(int i, int j,int n){
  // std::cout << i<<j << '\n';
  return range_min_query_util(1,0,n-1,i,j);
}
void printST(){
	int i = 0;
	std::cout << "[i]\t"<<"[sum]" << '\n';
	for(auto it: segMentTree){
		std::cout<<'['<<i<<']'<<": \t"<< it<< '\n';
		++i;
	}
}
int modify_util(int p, int L, int R,int i,int j,int value, int dif){
  if(i > R || j < L) return -1;
  segMentTree[p] += dif;
  if(L == i &&  R == j){
    segMentTree[p] = value;
    return 0;
  }

  int p1 = modify_util(left(p),L,(L+R)/2,i,j,value,dif);
  int p2 = modify_util(right(p),(L+R)/2 + 1,R,i,j,value,dif);
  return  0;
}
void modify(int i,int j,int n, int value,int dif){
  modify_util(1,0,n-1,i,j,value,dif);
}
int main(int argc, char const *argv[]) {
  int n,i,j;
  int var;
  int counter = 0;
  while(std::cin >> n && n){
    int var;
    counter++;
    for(int i = 0; i < n; ++i){
      scanf("%d",&var);
      Array.push_back(var);
    }
    if(counter > 1)std::cout  << '\n';
    std::cout << "Case "<<counter << '\n';
    segMentTree.assign(4 * Array.size(),0);
    build(1,0,Array.size()-1);
    // printST();
    std::string action;
    while(std::cin >> action, action[0] != 'E'){
      scanf("%d %d",&i,&j);
      if(action[0] == 'M') << range_min_query(i-1,j-1,Array.size()) << '\n';
      else{
        int dif = j - Array[i-1];
        if(j >= Array[i-1])modify(i-1,i-1,Array.size(),j,dif);
        else modify(i-1,i-1,Array.size(),j,dif);
        Array[i-1] = j;
      }
    }
    segMentTree.clear();
    Array.clear();
  }

  return 0;
}
