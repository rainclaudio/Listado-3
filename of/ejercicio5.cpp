#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
/*
PROBLEM ID: 11235 "Frequent values"
Solved by: Claudio Rain
*/
typedef struct{
	int representante,frequency,leftMostDigit,rightMostDigit,leftNode,rightNode;
}Node;
typedef struct{
	int upperbound;
	int lowerbound;
}ValueInfo;
typedef std::vector<int> v;
typedef std::pair<int,int> Intpair;
typedef std::vector<Node> St;
v Array;
St st;
std::map<int,ValueInfo> utilMap;
int left(int p){
  return p<<1;
}
int right(int p){
  return (p<<1) + 1;
}

Node createNode(int representante, int frequency, int leftMostDigit, int rightMostDigit, int l, int r){
  Node newNode;
  newNode.representante = representante;
  newNode.frequency = frequency;
  newNode.leftMostDigit = leftMostDigit;
	newNode.rightMostDigit = rightMostDigit;
  newNode.leftNode = l;
  newNode.rightNode = r;
  return newNode;
}

Node getNode(Node n1, Node n2){
  Node answer;
  // if(n1.representante == n2.representante){
  //   answer = createNode(n1.representante,
  //            n1.frequency + n2.frequency,
  //            n1.leftMostDigit,
  //            n2.rightMostDigit,
  //            n1.leftNode,
  //            n2.rightNode);
	//
  // }else{
		if(n1.frequency > n2.frequency){
		 	answer = createNode(n1.representante,
													n1.frequency,
													n1.leftMostDigit,
													n2.rightMostDigit,
													n1.leftNode,
													n2.rightNode);
		} else{
			answer = createNode(n2.representante,
													n2.frequency,
													n1.leftMostDigit,
													n2.rightMostDigit,
													n1.leftNode,
													n2.rightNode);
		}
  // }

	if(n1.rightMostDigit == n2.leftMostDigit){
  	 ValueInfo valueInfo = utilMap[n1.rightMostDigit];
		 int frec = 1	+ std::min(valueInfo.upperbound, n2.rightNode)- std::max(valueInfo.lowerbound,n1.leftNode) ;
		 if(frec > answer.frequency){
			 answer.representante = n1.rightMostDigit;
			 answer.frequency = frec;
		 }
	}
  return answer;
}


void build(int p, int L, int R){
  if(L == R){
      Node newNode = createNode(Array[L],1,Array[L],Array[L],L,L);
	    st[p] = newNode;
			return;
  }else {

    build(left(p),L, (L + R) /2);
    build(right(p),(L + R) /2 + 1, R);

    Node p1 = st[left(p)];
    Node p2 = st[right(p)];
    st[p] = getNode(p1,p2);
  }
}
void printNode(int i, Node it){
	std::cout << "[i]\t"<<"[id]\t"<<"[frec]\t"<<"[LMD]\t"<<"[RMD]\t"<<"L\t"<<"R\t" << '\n';

	std::cout<<'['<<i<<']'<<": \t"
		<< it.representante<<'\t'
		<<it.frequency<<'\t'
		<<it.leftMostDigit<<'\t'
		<<it.rightMostDigit<<'\t'
		<<it.leftNode<<'\t'
		<<it.rightNode
		<< '\n';
}
void printST(){
	int i = 0;
	std::cout << "[i]\t"<<"[id]\t"<<"[frec]\t"<<"[LMD]\t"<<"[RMD]\t"<<"L\t"<<"R\t" << '\n';
	for(auto it: st){
		std::cout<<'['<<i<<']'<<": \t"
			<< it.representante<<'\t'
			<<it.frequency<<'\t'
			<<it.leftMostDigit<<'\t'
			<<it.rightMostDigit<<'\t'
			<<it.leftNode<<'\t'
			<<it.rightNode
			<< '\n';
		++i;
	}
}
void printMap(){
	int i = 1;
	std::cout << "UTILmap" << '\n';
	for(auto it: utilMap){
		std::cout << it.second.lowerbound << '\t';
		std::cout << it.second.upperbound << '\n';
	}
}

Node range_min_query_util(int p, int L, int R,int i,int j){
  if(j < L || i > R) return createNode(-1,-1,-1,-1,-1,-1);//no overlap
  if(i <= L &&  R <= j){
	 return st[p];//complete overlap

 }

  //check both parts
  Node p1 = range_min_query_util(left(p),L,(L+R)/2,i,j);
  Node p2 = range_min_query_util(right(p),(L+R)/2 + 1,R,i,j);

  //si estamos fuera del rango
  if(p1.frequency == -1)return p2;
  if(p2.frequency == -1)return p1;
	Node answer = getNode(p1,p2);
	return answer;
}
int range_min_query(int i, int j,int n){
  Node p1 = range_min_query_util(1,0,n-1,i,j);
  return p1.frequency;
}
int main(int argc, char const *argv[]) {
  int querys,n,i,j;
  while(true){
    scanf("%d",&n);
    if(n == 0) break;
    scanf("%d",&querys);
    int var;
    int last;
    std::cin >> var;
    last = var;
    n--;
    utilMap[var].lowerbound = 0;
    Array.push_back(var);
		int i = 1;
    while(n--){
      std::cin >> var;
      if(last != var){
				utilMap[last].upperbound = i-1;
        last = var;
        utilMap[last].lowerbound = i;
      }
      Array.push_back(var);
			i++;
    }

		utilMap[last].upperbound = i-1;

    st.assign(4 * Array.size(),{0,0,0,0,0,0});

    build(1,0,Array.size()-1);
	  while(querys--){
      std::cin >> i >> j;
      std::cout <<range_min_query(i-1,j-1,Array.size())<<'\n';
    }
    st.clear();
		utilMap.clear();
    Array.clear();
  }

  return 0;
}
