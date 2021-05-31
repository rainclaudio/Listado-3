#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
/*
PROBLEM ID: 12532
Solved by: Claudio Rain
*/
typedef std::vector<int> v;


int LSOne(int n) {
	return n & (-n);
}
v ftNegative;
v ftZeroes;

void FenwickTree(v& ft,int n) {
		ft.assign(n + 1, 0);
}
int rsq(v& ft,int b) {
		int sum = 0;
		for (; b; b -= LSOne(b)){
      sum += ft[b];
    }
		return sum;
  }
	int rsq(v& ft, int a, int b) {
		return rsq(ft,b) - (a == 1 ? 0 : rsq(ft,a - 1));
	}
	void adjust(v& ft,int k, int v) {
		for (; k < (int) ft.size(); k += LSOne(k)){
      ft[k] += v;
    }
  }
int main(int argc, char const *argv[]) {
    int N,K;

    while(scanf("%d %d",&N,&K)!= EOF){
    v  Array(N+1);
    int var;
       FenwickTree(ftNegative,N + 1);
       FenwickTree(ftZeroes,N + 1);

      for(int i = 1; i <= N; ++i){
        scanf("%d",&var);

        if(var == 0)adjust(ftZeroes,i,1);
        else if(var < 0)adjust(ftNegative,i,1);
        Array[i] = var;
      }

      for (size_t i = 0; i < K; i++) {
          std::string action;
          int n1,n2;
          std::cin >> action >> n1 >> n2;
          if(action == "P"){
            // si existe un 0 en el intervalo

            if(rsq(ftZeroes,n1,n2)){
              printf("0");

            }
            // si tenemos un número impar de negativos
            else if((rsq(ftNegative,n1,n2)) % 2 == 1)printf("-");
            else printf("+");
          }else {
            // si cambiamos 0s por negativos y viceversa
            if(Array[n1] != 0 && n2 == 0)adjust(ftZeroes,n1,1);
            else if(Array[n1] == 0 && n2!=0)adjust(ftZeroes,n1,-1);
            // lo mismo para +'vos y -'vos
            if(Array[n1] < 0 && n2 >= 0)adjust(ftNegative,n1,-1);
            else if(Array[n1] >= 0 && n2 < 0)adjust(ftNegative,n1,1);
            Array[n1] = n2;
          }
      }
      printf("\n");
      Array.clear();
    }

  return 0;
}
