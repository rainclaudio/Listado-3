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

int LSOne(int n) {
	return n & (-n);
}

class FenwickTree {
private:
	v ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);
	}
	int rsq(int b) {
		int sum = 0;
		for (; b; b -= LSOne(b))sum += ft[b];
		return sum;}
	int rsq(int a, int b) {
		return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
	}
	void adjust(int k, int v) {
		for (; k < (int) ft.size(); k += LSOne(k))
			ft[k] += v;
	}
};

int main(int argc, char const *argv[]) {
  int n,i,j;
  int var;
  int counter = 0;
  while(std::cin >> n && n){
    FenwickTree ft(n);
    counter++;
    int var;
    Array.push_back(-1);
    for(int i = 1; i <= n; ++i){
      scanf("%d",&var);
      Array.push_back(var);
      ft.adjust(i, Array[i]);
    }
    if(counter > 1)printf("\n" );
    printf("Case %d:\n",counter);


    std::string action;
    while(std::cin >> action, action[0] != 'E'){
      scanf("%d %d",&i,&j);
      if(action[0] == 'M')printf("%d\n",ft.rsq(i,j));
      else{
        int dif = j - Array[i];
        ft.adjust(i,dif);
        Array[i] = j;
      }
    }
    Array.clear();
  }

  return 0;
}
