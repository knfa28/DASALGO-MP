#include <stdio.h>

int determineComplete (int values [][255]){
	int i;
	
	for (i = 0; i< 255; i++){
		if (values[1][i] > 1 || (values[1][i] && !(values[2][i]))) /*if a node has been given a value*/
																   /*more than once (specs say "exactly once") */
			return 0;											   /*or if it has no parent, return 0*/
	}
	
	return 1; /*if none of the nodes satisfy the conditions that make the tree incomplete, return 1*/
	
}

void display (int values [][255]){
	int i;
	
	for (i=0; i<255; i++){
		if (values[1][i] > 0) /*if the node has been given a value*/
			printf("%d ", values [0][i]); /*print*/
	}
	
	printf("\n");
}

int giveOutput (int values[][255]){ /*give the output*/
	if (determineComplete (values))
		display(values);
	else
		printf("not complete\n");
}

void initialize(int a [][255]){
	int i;
	
    for ( i=0; i<255; i++){
		a [1][i] = 0;
		a [2][i] = 0;
	}
	
	a [2][0] = 1; /*root node technically has no parent*/
}

int main (){
	int values [3][255]; 
	/*[0] contains the actual value
	 *[1] contains the number of times it has been given a value
	 *[2] is a boolean stating whether or not it has a parent
	 */
	 
	int tempval;
	char ch;
	int index, check=0, i;
	
	initialize (values); 
	
	do{ 
	
		scanf("%c", &ch);
		
		if (ch == '('){ 
			
			if (scanf("%d", &tempval)==1){/*store value of the node*/
				index = 0;
				check = 1;
				
				while (check){
			
					scanf("%c", &ch);
					switch (ch){
						case 'R': index = index * 2 + 2; break; /*calculate the index*/
						case 'L': index = index * 2 + 1; break;
						case ')': 
								  	values[0][index] = tempval;
								  	
								  	/*for all nodes that could possibly be parent nodes*/
								  	if (index < 127){
								  		values [2][index*2 + 2] = 1;
								  		values [2][index*2 + 1] = 1;
								  	}
								  	
								  values[1][index]++;
								  check = 0;
								  break;
					
					}				
				}
				
			}
			
			else{
				
				scanf("%c", &ch);
		
				if (ch == ')'){
					giveOutput (values);
					initialize (values);
				}	
			}
		
		}

	} while (ch != EOF);
}
