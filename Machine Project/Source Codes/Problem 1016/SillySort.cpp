#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

int orig[100000];    /*original array*/
int sorted[100000];  /*sorted array*/
bool vis[100000];    /*stores the bool value whether original array is sorted or not*/
                     /*ex. orig[0] = sorted[0], vis[0] = true*/

int main (void) {
    int nInput;  /*number of elements*/
    int t = 0;   /*number of times cases happens*/
    
	/*gets the nInput, if nInput is 0 does not proceed*/
	while (scanf("%d", &nInput) && nInput) {
        t++;  /*increments number of cases*/
        
        /*scans a number nInput times*/
        for(int i = 0; i < nInput; ++i){
            scanf("%d", &orig[i]); /*stores scanned number into an array*/
            sorted[i] = orig[i];   /*contents of original are copied into an array to be sorted*/
            vis[i] = false;        /*initializes the boolean values of each element to false*/
        }
        
        /*sorts the array 'sorted'*/
        sort(sorted, sorted + nInput);

        /*maps the numbers to their desired place after sort*/
        map<int, int> place;
        
        /*stores the index to the index of the value
		  of each sorted number to their mapped place*/
        for (int i = 0; i < nInput; ++i)
            place[sorted[i]] = i;
    
        int res = 0;  /*initial value of the result*/
        
        /*traverses the original list*/
        for (int i = 0; i < nInput; ++i) {
        	/*if the value at the index is unsorted*/
            if (vis[i] == false) {
            	/*if the place of the original element is the same with corresponding sorted list element*/
                if (place[orig[i]] == i) {
                    vis[i] = true;  /*sets the bool value to true*/
                    continue;       /*starts the loop again and immediately iterates at the for loop*/
                }
                
                /*
				  index passes through here if bool value is false
                  we're in new cycle
				*/
                
                int min_val = orig[i];  /*assigns the current value of orig value to be minimum*/
                int num = 0;            /*number of non-sorted elements*/
                int sum = 0;            /*sum of the values to be added*/
                int j = i;              /*j to traverse the list with respect to i so that excluded i's wont be checked*/
				
				/*while the boolean of the original array is false*/
                while (vis[j] == false) {
                    sum += orig[j];  /*adds all the unsorted elements in the list*/
                    num++;           /*iterates number of unsorted elements*/
                    
					/*finds the minimum value of the original list*/
					if (orig[j] < min_val)
                        min_val = orig[j];
    
                    vis[j] = true;       /*sets every element passed to true*/
                    j = place[orig[j]];  /*get the place of the one that was added(because cycle)*/
                }
                
                sum -= min_val;  /*subtract sum with the min val*/
                
                /*adds the current sum and the min val multiplied by the number of times it will get switched*/
                res += sum + min_val * (num - 1);
                
                /*
				  Let's try to borrow the minimum value.
                  If it's less costly then update our result.
                */
                
                /*checks if the lowest value replaced with the min value gives a better sum*/
                if(2 * (sorted[0] + min_val) < (min_val - sorted[0]) * (num - 1))
                	/*if so, subtract the higher sum then add the lower sum*/
                    res -= (min_val - sorted[0]) * (num - 1) - 2 * (sorted[0] + min_val);      
            }
        }
        /*displays Case t: res*/
        printf("Case %d: %d\n\n", t, res);
    }
    return 0;
}
