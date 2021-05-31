#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <utility>
/*
Problem ID: 11350 "Stern-Brocot Tree"
Made By Claudio Rain
*/
typedef std::pair<long long,long long> LongPair;

LongPair get_answer(LongPair lb, LongPair mid, LongPair up, std::queue<int>& input){
  if(input.empty()) return mid;
  else if(input.front() == 0){
    LongPair answer = std::make_pair(lb.first + mid.first, lb.second + mid.second);
    input.pop();
    return get_answer(lb,answer,mid,input);
  } else {
    LongPair answer = std::make_pair(up.first + mid.first, up.second + mid.second);
    input.pop();
    return get_answer(mid,answer,up,input);
  }
}


int main(int argc, char const *argv[]) {
  int n1;
  std::cin >> n1;
  while(n1--){
    std::string input;
    std::cin >> input;
    std::queue<int> queue1;
    for(int i = 0; i < input.size(); ++i){
      if(input[i] == 'L' ){
        queue1.push(0);
      } else queue1.push(1);
    }
    LongPair lp = get_answer(std::make_pair(0,1),std::make_pair(1,1),std::make_pair(1,0),queue1);
    printf("%lld/%lld\n",lp.first,lp.second);
  }

  return 0;
}
