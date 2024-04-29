#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INF 99999

void printPath(int src, int dest, int n, int pred[][n])
{
	// base case for recursive function
	if (src==dest) // checks if control has reached the source after starting from the destination
	{
		printf("%d",src); // prints the source vertex
		return;
		
	}
	// checks for predecessor for destination vertex from source vertex
	if(pred[src][dest]==-1) // if it is true, it indicates there's no path between source and destination
	{
		printf("No path from %d to %d",src,dest);
		return;
	}
	printPath(src,pred[src][dest],n,pred); // recursive call executes if there is a path from source to destination
	// backtracks through the entire predecessor matrix and prints the entire path
	printf("-> %d",dest); // prints destination
	
}
void printDistance(int n,int cost[][n]) // prints the final distance matrix
{
	printf("\nThe distance matrix is:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if (cost[i][j]==INF) // if the distance between 2 vertices is infinite or undefined
				printf("INF");
			else
				printf("%d\t",cost[i][j]); // otherwise prints the shortest distance between any 2 vertices 
		}
		printf("\n");
	}
}
void floyd(int n, int cost[][n]) 
{
	// n = no. of vertices
	// cost[n] = adjacency matrix representing the graph
	
	int pred[n][n]; // predecessor matrix - stores predecessor of each vertex on shortest path
	
	for(int i=0;i<n;i++) // iterates over all the vertices
	{
		for(int j=0;j<n;j++)
		{
			// if it is a diagonal vertex, then it's predecessor is set to -1
			// otherwise it assigns each vertex to be its own predecessor, i.e. i
			pred[i][j]= (i==j)?-1:i;
		}
	}
	for(int k=0;k<n;k++) // iterates over all vertices to find the intermediate vertices for finding shorter paths between other pair of vertices
	{
		for(int i=0;i<n;i++) // iterates over all possible source vertices
		{
			for(int j=0;j<n;j++) // iterates over all possible destination vertices
			{
				// checks if the path through vertex k is shorter than the current shortest path between vertices i and j
				if((cost[i][k]+cost[k][j])<cost[i][j])
				{
					// updates both the distance matrix cost and the predecessor matrix pred
					cost[i][j]=cost[i][k]+cost[k][j];
					pred[i][j]=pred[k][j];
				}
			}
		}
	}
	printDistance(n,cost); // call to print distance matrix
	printf("\nThe shortest path between:\nSource\tDestination\tPath\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i!=j) // shortest path from i to i or j to j is 0
			{
			  	printf("%d\t%d\t\t",i,j);
				printPath(i,j,n,pred); // call to print the shortest path from i to j
				printf("\n");
			}
		}
	}
}

int main()
{
	int vertices;	
	printf("\nEnter the number of vertices:");
	scanf("%d",&vertices);
	int cost[vertices][vertices];
	printf("\nEnter the adjacency matrix:\n");
	for(int i=0;i<vertices;i++) // inputs the graph in the form of adjacency matrix
	{
		for(int j=0;j<vertices;j++)			
			scanf("%d",&cost[i][j]);
	}
	floyd(vertices,cost);
	return 0;
}
