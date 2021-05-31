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
int range(int i, int j, int n){
  int counter = 1;
  int k = 0;
  int var = Array[i-1];
  int answer = 1;
  for(k = i; k < j; k++){
    if(Array[k] == var){
      answer++;
    }
    else break;
  }
  for(; k < j; ++k){
    if(Array[k] == var){
      counter++;
    } else {
      if(counter > answer){
        answer = counter;
      }
      counter = 1;
      var = Array[k];
    }
  }
  if(counter > answer)answer = counter;
  return answer;
}
int main(int argc, char const *argv[]) {
  int querys,n,i,j;
  while(true){
    scanf("%d",&n);
    if(n == 0) break;
    scanf("%d",&querys);
    int var;
    while(n--){
      std::cin >> var;
      Array.push_back(var);
    }

    while(querys--){
      std::cin >> i >> j;
      std::cout <<range(i,j,Array.size())<<'\n';
    }

    Array.clear();
  }

  return 0;
}
