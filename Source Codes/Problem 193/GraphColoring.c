#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WHITE 0
#define BLACK 1

int nodeCnt;              /*number of nodes*/
int nodes[100];			  /*array of nodes*/
int connected[100][100];  /*grid of the pairs of nodes*/

int best_nodes[100];      /*complete list of the colored nodes*/
int maxBlack = 0;         /*number of black colored nodes*/

/*
  sets the color of each node
  numNode  - index of a node
  numBlack - index of a black colored node
*/
void setColor(int numNode, int numBlack){
	int i;        /*counter variable*/
	int end = 0;  /*determines if all nodes have been marked*/

	nodes[numNode] = BLACK;  /*colors the node at index numNode black*/
	numBlack++;              /*increments the number of black colored nodes*/
	
	/*if the current number of black colored nodes
	  exceed the maximum number of black colored nodes*/
	if(numBlack > maxBlack){
		/*set the current number of black nodes as the max number*/
		maxBlack = numBlack;
		
		/*all of the nodes have been marked*/
		end = 1;
	}
	
	/*for every node*/
	for(i = 0; i < nodeCnt; i++)
		/*if its pair has not yet been marked and
		  the node itself has not yet been colored*/
		if(connected[numNode][i] && nodes[i] == WHITE)
			/*marks the node as uncolored*/
			nodes[i] = 10 + numNode;
	
	/*for every node that is colored white*/
	for(i = 0; i < nodeCnt; i++)
		if(nodes[i] == WHITE){
			/*sets the colors of the remaining nodes at index i*/
			setColor(i, numBlack);
			
			/*not all of the nodes have been marked yet*/
			end = 0;
			break;
		}
	
	/*if all of the nodes have been marked*/
	if(end)
		/*copies the elements of the array nodes to best_nodes*/
		memcpy(best_nodes, nodes, sizeof(nodes));
	
	/*for every node that has been marked as uncolored*/
	for(i = 0; i < nodeCnt; i++)
		if(nodes[i] == 10 + numNode){
			/*colors the node white*/
			nodes[i] = WHITE;
		}
	
	/*unmarks the last node*/
	nodes[numNode] = 10 + numNode;
	
	/*decrements the number of black nodes*/
	numBlack--;
	
	/*for every whte colored node*/
	for(i = 0; i < nodeCnt; i++)
		if (nodes[i] == WHITE) {
			/*sets the colors of the last remaining nodes starting at index i*/
			setColor(i, numBlack);
			
			/*exits the for-loop once condition is met*/
			break;
		}
	
	/*colors the last node white*/
	nodes[numNode] = WHITE;
}

int main(void){
	int i,j,k;     /*counter variables*/
	int graphCnt,  /*number of graphs*/
	    edgeCnt;   /*number of edges*/
	int n1, n2;    /*pair of nodes*/
	
	/*scans the first line, gets the number of graphs*/
	scanf("%d", &graphCnt);
	
	/*scans the rest of the lines depending on graphCnt*/
	for(i = 0; i < graphCnt; i++){
		/*scans the second line, gets the number of nodes & edges*/
		scanf(" %d %d", &nodeCnt, &edgeCnt);
		
		/*sets the initial number of black colored nodes to 0*/
		maxBlack = 0;
		
		/*initializes each node to 0 (initial color)*/
		for(j = 0; j < nodeCnt; j++){
			nodes[j] = 0;
			
			/*initializes a grid of nodes to 0 (undirected edges)*/
			for(k = 0; k < nodeCnt; k++)
				connected[j][k] = 0;
		}
		
		/*connects a pair of nodes by marking their coordinates in the grid by 1*/
		for(j = 0; j < edgeCnt; j++){
			/*scans the two nodes*/
			scanf(" %d %d", &n1, &n2);  
			
			/*directs the two nodes to each other*/
			connected[n1-1][n2-1] = 1; 
			connected[n2-1][n1-1] = 1;  
		}
		
		/*sets the colors of the nodes such that
		  no two connected nodes may be black*/
		setColor(0,0);
		
		/*displays the maximum number of nodes that can be/is colored black*/
		printf("%d\n", maxBlack);
		n1 = 0;
		
		/*dislays the index of the black colored nodes*/
		for(j = 0; j < nodeCnt; j++)
			if(best_nodes[j] == BLACK){
				printf("%s%d", (n1 ? " " : ""), j + 1);
				n1 = 1;
			}
		
		printf("\n");
	}
	exit(0);
}
