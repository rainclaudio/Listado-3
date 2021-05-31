#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
const int z=100000;
const int maxn=2e6+6;
/*
option=com_onlinejudge&Itemid=8&page=show_problem&problem=2176

Title: In a sequence of length n and not strictly increasing, given q queries,
each query of the number that appears most frequently in a certain interval,
output the number of occurrences of that number in the interval.

answer: Use the line segment tree to maintain the maximum length of the continuous segment of the interval.
The first thing to note is thatSequence is not strictly increasing, This is a very important premise.

When merging intervals, consider whether the rightmost digit of the left interval
and the leftmost digit of the right interval are the same:

If they are not the same, the maximum length of the continuous segment of the
merged interval can be taken as max from the longest length of the continuous
segment of the two subintervals;

When the same, you also need to consider the length of the continuous segment
of the number in the middle of the interval.
*/
struct Node{
	int representante,frequency,leftMostDigit,rightMostDigit,l,r;
}SegmentTree[4*maxn];

int Array[maxn];
int LeftMostPosArray[maxn],rightMostPosArray[maxn];
Node mergy(Node node1,Node node2){

	Node ans=(Node){0,0,node1.leftMostDigit,node2.rightMostDigit,node1.l,node2.r};

	if(node1.frequency>node2.frequency)ans.frequency=node1.frequency,ans.representante=node1.representante;
	else ans.frequency=node2.frequency,ans.representante=node2.representante;
/*
When merging intervals, consider whether the rightmost digit of the left interval
and the leftmost digit of the right interval are the same:
*/
	/*
	If they are not the same, the maximum length of the continuous segment of the
	merged interval can be taken as max from the longest length of the continuous
	segment of the two subintervals;
	*/
	if(node1.rightMostDigit!=node2.leftMostDigit)return ans;
	/*
	When the same, you also need to consider the length of the continuous segment
	of the number in the middle of the interval.
	*/
	int currentMidElement=node1.rightMostDigit;
	int tmp=min(node2.r,rightMostPosArray[currentMidElement+z])-max(node1.l,LeftMostPosArray[currentMidElement+z])+1;
	// int tmp=rightMostPosArray[currentMidElement+z]-LeftMostPosArray[currentMidElement+z]+1;

	if(ans.frequency<tmp){
		ans.frequency=tmp;
		ans.representante=currentMidElement;
	}

	return ans;
}
void build(int l,int r,int x){
	if(l==r){
		SegmentTree[x]=(Node){Array[l],1,Array[l],Array[l],l,l};
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,2*x);
	build(mid+1,r,2*x+1);
	SegmentTree[x]=mergy(SegmentTree[2*x],SegmentTree[2*x+1]);
}
Node query(int i,int j,int L,int R,int x){
	if(i <= L && R <= j )return SegmentTree[x]; // complete overlap

	int mid=(L+R)>>1;

	Node x1,x2;

	x1=x2=(Node){0,0,0,0,0,0};

	if(i<=mid)x1=query(i,j,L,mid,2*x);

	if(j>mid)x2=query(i,j,mid+1,R,2*x+1);

	if(x1.frequency&&x2.frequency)return mergy(x1,x2);

	if(x1.frequency)return x1;

	if(x2.frequency)return x2;

}
int main(){
	int n,q;
	while(cin>>n&&n){
		cin>>q;
		// z = 100.000
		for(int i=1;i<=n;i++){

			scanf("%d",&Array[i]);

			if(Array[i]!=Array[i-1]||i==1)LeftMostPosArray[Array[i]+z]=i;

			if(i!=1&&Array[i]!=Array[i-1])rightMostPosArray[Array[i-1]+z]=i-1;

		}
		rightMostPosArray[Array[n]+z]=n;
		build(1,n,1);
		int l,r;
		for(int i=1;i<=q;i++){
			scanf("%d%d",&l,&r);
			Node ans=query(l,r,1,n,1);
			printf("%d\n",ans.frequency);
		}
	}
}
