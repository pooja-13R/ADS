// C++ program to find number of islands
// using Disjoint Set data structure.
#include <bits/stdc++.h>
using namespace std;


class DisjointUnionSets
{
	
	vector<int> rank, parent;
	int n;
	
	public:
	DisjointUnionSets(int n)
	{
		rank.resize(n);
		parent.resize(n);
		this->n = n;
		makeSet();
	}

	void makeSet()
	{
		
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	
	int find(int x)
	{
		if (parent[x] != x)
		{
		
			parent[x]=find(parent[x]);
		}

		return parent[x];
	}

	
	void Union(int x, int y)
	{
	
		int xRoot = find(x);
		int yRoot = find(y);

		
		if (xRoot == yRoot)
			return;

		if (rank[xRoot] < rank[yRoot])
			parent[xRoot] = yRoot;

		
		else if (rank[yRoot] < rank[xRoot])
			parent[yRoot] = xRoot;

		else 
		{
			
			parent[yRoot] = xRoot;

			
			rank[xRoot] = rank[xRoot] + 1;
		}
	}
};


int countIslands(vector<vector<int>>a)
{
	int n = a.size();
	int m = a[0].size();

	DisjointUnionSets *dus = new DisjointUnionSets(n * m);
	int dirx[8]={0,1,0,-1,1,1,-1,-1};
	int diry[8]={1,0,-1,0,1,-1,1,-1};

	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < m; k++)
		{
		
			if (a[j][k] == 0)
				continue;
            for(int i=0;i<8;i++){
                int newx=dirx[i]+j;
                int newy=diry[i]+k;
                	if (newx >= 0 && newy >= 0 && newx <n && newy <m &&	a[newx][newy] == 1)
				dus->Union(j * m + k,
						newx * m + newy);
            }
		
		
		}
	}

	
	int *c = new int[n * m];
	int numberOfIslands = 0;
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < m; k++)
		{
			if (a[j][k] == 1)
			{
				int x = dus->find(j * m + k);

				
				if (c[x] == 0)
				{
					numberOfIslands++;
					c[x]++;
				}

				else
					c[x]++;
			}
		}
	}
	return numberOfIslands;
}


int main(void)
{
	vector<vector<int>>a = {{1, 1, 0, 0, 0},
				{0, 1, 0, 0, 1},
				{1, 0, 0, 1, 1},
				{0, 0, 0, 0, 0},
				{1, 0, 1, 0, 1}};
	cout << "Number of Islands is: "
		<< countIslands(a) << endl;
}
