/* 
You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
Given M queries, your program must output the results of these queries.

Input
The first line of the input file contains the integer N.
In the second line, N numbers follow.
The third line contains the integer M.
M lines follow, where line i contains 2 numbers xi and yi.

Output
Your program should output the results of the M queries, one 
query per line.

Sample Input:
3 
-1 2 3 
1
1 2

Sample Output:
2
*/
#include <stdio.h>
#define ll long long

struct node
{
	int msum, lsum, rsum;
};

int arr[50010];
ll sumArr[50010];
struct node stree[200000];

int max(int a, int b)
{
	int max = a > b ? a : b;
	return max;
}

void createSegmentTree(int pos, int ss, int se)
{
	struct node left, right;
	if(ss == se)
		stree[pos].lsum = stree[pos].rsum = stree[pos].msum = arr[ss];
	else
	{
		createSegmentTree(pos * 2, ss, (ss + se) / 2);
		createSegmentTree(pos * 2 + 1, (ss + se) / 2 + 1, se);
		left = stree[pos * 2];
		right = stree[pos * 2 + 1];
		if(ss == 0)
			stree[pos].lsum = max(left.lsum, sumArr[(ss + se) / 2] + right.lsum);
		else
			stree[pos].lsum = max(left.lsum, sumArr[(ss + se) / 2] - sumArr[ss - 1] + right.lsum);
		stree[pos].rsum = max(right.rsum, sumArr[se] - sumArr[(ss + se) / 2] + left.rsum);
		stree[pos].msum = max(left.msum, max(right.msum , left.rsum + right.lsum));
	}
}

struct node query(int pos, int a, int b, int x, int y)
{
	struct node left, right, retVal;
	if(a == x && b == y)
		return stree[pos];
	if(y <= (a + b) / 2)
		return query(pos * 2, a, (a + b) / 2, x, y);
	if(x > (a + b) / 2)
		return query(pos * 2 + 1, (a + b) / 2 + 1, b, x , y);
	left = query(pos * 2, a, (a + b) / 2, x, (a + b) / 2);
	right = query(pos * 2 + 1, (a + b) / 2 + 1, b, (a + b) / 2 + 1, y);
	if(x == 0)
			retVal.lsum = max(left.lsum, sumArr[(a + b) / 2] + right.lsum);
		else
			retVal.lsum = max(left.lsum, sumArr[(a + b) / 2] - sumArr[x - 1] + right.lsum);
	retVal.rsum = max(right.rsum, sumArr[y] - sumArr[(a + b) / 2] + left.rsum);
	retVal.msum = max(left.msum, max(right.msum , left.rsum + right.lsum));

	return retVal;
}


int main()
{
	int n, i, m, x, y;

	scanf("%d", &n);

	scanf("%d", &arr[0]);
	sumArr[0] = arr[0];
	for(i = 1 ; i < n ; i++)
	{
		scanf("%d", &arr[i]);
		sumArr[i] = sumArr[i - 1] + arr[i];
	}

	createSegmentTree(1, 0, n - 1);	
	scanf("%d", &m);

	for(i = 0 ; i < m ; i++)
	{
		scanf("%d %d", &x, &y);
		x--; y--;
		printf("%d\n", query(1, 0, n - 1, x, y).msum);
	}

	return 0;
}
