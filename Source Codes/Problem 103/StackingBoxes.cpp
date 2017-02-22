#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <set>
#include <math.h>

using namespace std;

/*node of a box*/
struct node{   
    int id;     /*stores the index of the box*/
    int d[12];  /*dimensions of the box*/
}a[32];         /*maximum number of boxes*/

int k;           /*number of boxes*/
int n;           /*number of dimensions for each box*/
int best[32];    /*determines the number of boxes that can be stacked*/
int parent[32];  /*the array of indexes to be pushed to the stack from boxes*/
vector <int> v;  /*contains the list of values acts as the stacker*/

/*compares the dimensions of two boxes*/ 
bool cmp(int x, int y){
	/*for every dimension of each box*/
    for(int i = 0; i < n; i++)
		/*determines which box has the larger dimensions*/ 
        if(a[x].d[i] <= a[y].d[i])
            return false;
    
    return true;
}

/*pushes all the values into the stack except for the last element*/
void print_path(int x){
	/*stops the recursion when a number is repeated ex.  x = 5 {0, 1, 1, 1, 4, 2, 5} returns values {1,4,2}*/
    if(x == parent[x])
        return ;
	
	/*recurses the function if there are repeating numbers*/
    print_path(parent[x]);
	
	/*uses the index to push the element to the stack*/
    v.push_back(a[parent[x]].id);
}

/*returns the max number of stackable boxes*/
int lis(){
    for(int i = 0; i < k; i++){
        best[i] = 1;    /*initializes  1 as the number of the times a box can be stacked*/
        parent[i] = i;  /*initializes the index to the stack of indices*/
    }
	
    for(int i = 1; i < k; i++) 
        for(int j = 0; j < i; j++)
			/*if i > j and the first values are not greater than the one beside*/
            if(cmp(i, j) && best[i] < best[j] + 1){
	            /*iterates whenever it finds an i > j meaning a box can be on it*/
                best[i] = best[j] + 1;
				/*stores the index of the stackable box*/
                parent[i] = j; 
            }
        
    int index;   /*index of the highest value*/
    int max = 0; /*initial value of the highest value*/
	
	/*for every box*/
    for(int i = 0; i < k; i++)
        if (max < best[i]){
            max = best[i];   /*finds the highest value in the array*/
            index = i;       /*on which index was it found meaning where the highest value was*/
        }
    
	/*pushes all of the values of the stack starting at index*/
    print_path(index);
	
	/*pushes the id of the last element of a[index]to the stack*/
    v.push_back(a[index].id);
	
    return max;
}


int main(){ 
	/*scans every line for the number of boxes k, and the number of its dimensions n*/
	while(scanf("%i %i", &k, &n) != EOF) {
        v.clear();  /*clears stack (list) v*/	
		
		/*for every box*/
        for(int i = 0; i < k; i++){
            a[i].id = i + 1;  /*initializes the index as the id of every box*/
            
			/*scans and stores the dimensions of every box*/
			for(int j = 0; j < n; j++)
                scanf("%d", &a [i].d[j]);
            
			/*sorts the dimension of evry box in ascending order for unifromity*/
			sort(a[i].d, a[i].d + n);
        }

        /*sorts the boxes into ascending order according to the size of their dimensions */
        for(int i = 0; i < k; i++) 
            for ( int j = i + 1; j < k; j++ )
				/*if the dimensions of the box at index i is greater than the dimensions of the box at index j*/
				if(cmp(i, j))          
					swap(a[i], a[j]);  /*swaps the boxes*/    
        
		/*prints the number of stackable boxes*/
        printf("%d\n", lis());
		
		/*prints the stack*/
        for(unsigned int i = 0; i < v.size (); i++){
            if(i != 0)
                printf(" ");
            printf("%d", v.at (i));
        }
    }
    return 0;
}
