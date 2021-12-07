#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct words{     //decleration of linked list to store the word count

	char word[100];     //word
	long  unsigned int count;  //word count
	long unsigned int wOrder;  //word appearence order
	float wPer;   //word percentage
	struct words*next;    //pointer
}words_t;

words_t *head=NULL;   //define some poiters to the LL
words_t *last=NULL;
words_t *current=NULL;

typedef struct cha{    //decleration of struct type data
	char ch;         //ch- character
	long unsigned int count;   //count-number of occurences
	int order;    //order- order of the letter when it is read from the file
	float per;  //character percentage
}cha_t;

cha_t carray[37];   //decleration of struct type array to store characters in the files

void insert(char w[],int wor);       //prototype function declerations     
int countWords(char array1[], int wor);  
void sortw();
void percentage_w();
unsigned long int total_w();
unsigned long int maxlen(int rows);
void wgraph(int scaled,unsigned long int rows);


int countCharacters(char array1[],int or);  
void sortc(cha_t cgarray[]);    
void percentage(cha_t carray[]);  
void cgraph(int scaled,int rows,cha_t carray[]); 
int clen(cha_t carray[]);

int cor=1;  //global variable declerations to find word and character appearance order
int wor=1;  //cor-character order, wor-word order

int main(int argc, char *argv[]){
	
	int lIndex;   //store the index of -l
	int rows=10;    // store number of rows in the  chart
	int w=0;   
	int c=0;    //variable declerations ; c=1 when -c is given,w=1 when -w is given
	int scaled=0;
	int fileIndex[50];  //array to store the indexes of the filenames in argv array
	int f=0;   //counter variable
	
	//handling command line arguments of the programm
	
	if(argc==1){   //check whether only the program name was given or not
		printf("No input files were given\n");                          //prompt msg
		printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
		exit(-1);   //terminate the program when input files were not given
	}

	    
	for(int c1=0;argv[c1]!=0;c1++){    //loop through the command line argument array

		if(!strcmp("-l",argv[c1])){  //check whether the -l option is given or not
			lIndex=c1;     //assign the index of the -l
	
			if(lIndex==(argc-1)){  //check whether -l option is given at last or not
				printf("Not enough options for [-l]\n");
				printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
				exit(-1);
			}

			if(!strcmp("0",argv[lIndex+1])){ //check whether the argument after -l is 0 or not
               			return 0;
       			}else{
               			 if(atoi(argv[lIndex+1])>0){  //check whether the argument after -l is positive  or not

                       			rows=atoi(argv[lIndex+1]); //assign number of rows to the rows variable
					c1++;
			
               			 }else{
                       			if(atoi(argv[lIndex+1])<0){   //check whether the argument after -l is negative  or not


                               			printf("Invalid option(negative) for [-l]\n");  //prompt a message  
                               			printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
						return 0;
                       			}else{
                              			 printf("Invalid options for [-l]\n");   //prompt a message when the argument after the -l is not an integer
                               			 printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
						 return 0;
                       			}

        			 }
	

       			}



		}else if(!strcmp("-w",argv[c1])){    //check whether the option -w is given or not
			
			w=1;

		}else if(!strcmp("-c",argv[c1])){  //check whether the -c option is given or not
			
			c=1;

		}else  if(!(strcmp("--scaled",argv[c1]))){ //check whether the --scaled option is given or not
                         scaled=1;

		}else if(argv[c1][0]=='-'){  //check whether the filename option is correctly given or not
			printf("Invalid option [%s]\n",argv[c1]);
			printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);

			return 0;

		}else if(c1!=0){   //check whether the c1==0 or not
			fileIndex[f]=c1;   //if c1==0 and argv[c1][0]!='-' then it is considered as a file name. Find the index of the file names and append them to the array fileIndex
			f++;              //increment the index of fileIndex array by 1
		}


	}

	if(w==1 && c==1){   //check whether -c and -w were given together
		                                                 
		printf("[-c] and [-w] cannot use together\n"); //promt a msg

		printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
		exit(-1);   //terminate the program
	}
	
		

	if(f==0){         //check whether input files are given or not
		printf("No input files were given\n");                          //prompt msg
		printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
		return 0;   //terminate the program when input files were not given
	}

	

	if(c==1){   //check whether the -c argument is given or not

		for(int c1=0;c1<f;c1++){    //loop to read multiple files in order to find character occurences

			char readf[256]={};  //create an empty char array to store the file name
			strcpy(readf,argv[fileIndex[c1]]);   //copy the file name to the array
			cor=countCharacters(readf,cor);  //invoke the function to count characters
               
                }

		if(cor==1){   //check whether the given file is empty or not ,cor -character apearence order
			printf("No data to process\n");  //prompt msg
               		exit(-1);  //terminate the program
		}else{
		
			sortc(carray);  //invoke function sortc to sort the arrayc which contains character count
			percentage(carray);   // invoke function percentage to evaluate the percentage
			printf("\n");       //print new line
			cgraph(scaled,rows,carray);  //invoke the function cgraph to print the graph of the character count
			printf("\n");
		}

	}else{
		for(int c1=0;c1<f;c1++){    //loop to read multiple files in order to find word occurences

			char readf[256]={};   //create an empty char array to store the file name

                        strcpy(readf,argv[fileIndex[c1]]);  //copy the file name to the array
			wor=countWords(readf,wor);   //invoke the function to count words
		}
		
		if(wor==1){  //check whether the given file is empty or not ,wor-word appearence order
			printf("No data to process\n");  //prompt msg
               		exit(-1);  //terminate the program
		}else{
			
			sortw();  //invoke the function to sort the LL
			percentage_w();  //invoke the function which calculates the percentage value
			printf("\n");
			wgraph(scaled,rows);  //invoke the function to print the graph
			printf("\n");
		}
	}


	return 0;
}


void insert(char w[],int wor){  //function to insert a new node to a linked list
	words_t *newnode;  //pointer to new node
	newnode=(words_t*)malloc(sizeof(words_t));   //creating a memory block in size of student_t data type
	
	strcpy(newnode->word,w);    //assign data values to a particular node
	newnode->count=1;
	newnode->wOrder=wor;
	newnode->next=head;
       	head=newnode;
}

	
int countWords(char array1[], int wor){   //function to read a word from a file and return the appearence position of the last word of the file

	char word[100];    //array to store a word

	FILE *fp;     //pointer to file
	fp=fopen(array1,"r");        //open a file to read

	if(fp==NULL){
		printf("Cannot open one or more given files\n");  //prompt msg
		exit(-1);  //terminate the program

	}else{
		
		while(fscanf(fp,"%s",word)!=EOF){      //read words from a file
			
			char reword[100]={};    //create an empty array
			
			int reIndex=0;  //variable to access array index
			int check=0;   //variable to check the spaces

			for(int c2=0;word[c2]!='\0';c2++){   //loop through the word read from the file

				if((isalpha(word[c2])!=0) || (isdigit(word[c2])!=0)){ //check whether a charater is in alphabet or it is a digit
					reword[reIndex]=tolower(word[c2]);  //preprossesing 
					check=1;                           //check==1 if it is not a space
					reIndex++;  
				}
			}

			if(check==1){   //check whether the word read from the file is a space or not

				if(head==NULL){
					insert(reword,wor);   //insert word to the ll
					wor++;    //increment word order by1
				}else{
					int in=0;    
					words_t* current=head;
					while((current!=NULL) && (in==0)){         //code part to check whether the word is already in the list
						if(strcmp(current->word,reword)==0){
							
							in=1;
							current->count=(current->count)+1;
						}
						current=current->next;
					}

					if(in==0){    //if the word is not in the list ,the following code part executes
						insert(reword,wor); 
						wor++;  //increment word appearence order by 1

					}
				}
			}

		}
		
		fclose(fp);  //close file
	}

	return wor;   //return the appearence position of the last word of the file
}


void sortw(){      //function to sort the word count

	words_t* current=head;  //pointer variables to the ll
	words_t* NEXT=NULL;

	char tword[100];
	long unsigned int tcount;  //variable declerations
	long unsigned int torder;

	if(head==NULL){  //check whether the ll is empty or not
		return;  //terninate the function when ll is empty
	}else{
		
		while(current!=NULL){    //loop through the linked list
			NEXT=current->next;        //code part to sort the ll by its word count (descending order)

			while(NEXT!=NULL){
				if((current->count)<(NEXT->count)){
					strcpy(tword,current->word);
					tcount=current->count;
					torder=current->wOrder;
									//swap elements
					strcpy(current->word,NEXT->word);
					current->count=NEXT->count;
					current->wOrder=NEXT->wOrder;
	
					strcpy(NEXT->word,tword);
					NEXT->count=tcount;
					NEXT->wOrder=torder;
				}
				
				NEXT=NEXT->next;
			}
			
			current=current->next;
		}
	
	}



	words_t* current1=head;   //pointer variables
        words_t* NEXT1=NULL;     

	while(current1!=NULL){  //loop through the linked list
        	NEXT1=current1->next;     //code part to sort the linked list by its appearence order, when different words have same occurence  

                while(NEXT1!=NULL){    
		       	if((current1->count)==(NEXT1->count)){
				if((current1->wOrder)>(NEXT1->wOrder)){

					strcpy(tword,NEXT1->word);
                                        tcount=NEXT1->count;
                                        torder=NEXT1->wOrder;
										//swap elements
                                        strcpy(NEXT1->word,current1->word);
                                        NEXT1->count=current1->count;
                                        NEXT1->wOrder=current1->wOrder;

                                        strcpy(current1->word,tword);
                                        current1->count=tcount;
                                        current1->wOrder=torder;
				}
			}
			NEXT1=NEXT1->next;
		}
		current1=current1->next;
	}
}

void percentage_w(){   //function to evaluate percentage value of word occurences

	unsigned long int sum=0;   
	words_t* current=head;
        while(current!=NULL){    //code part to calculate the total number of words in the given files
		sum=sum+(current->count);
		current=current->next;
        }


	words_t* current1=head;  
        while(current1!=NULL){   //code part to calculate the percentage value of a word occurence
                current1->wPer=((float)(current1->count)*100)/sum;
                current1=current1->next;
        }
}


unsigned long int total_w(){  //function to evaluate the total number of different words in the given files

	unsigned long int w_sum=0;
        words_t* current=head;
        while(current!=NULL){
                w_sum++;       //loop through the ll and calculate the total number of different words
                current=current->next;
        }
	return w_sum;
}

unsigned long int maxlen(int rows){   //function to calculate the maximum word length

	unsigned long int total_words=total_w();
	if(rows>total_words){
		rows=total_words; //check whether the rows are grater than the total different number of words
	}

	int max_len=0;  //initialize maximum length to 0

	words_t* current=head;   //pointer to the ll

	for(int i=0;i<rows;i++){
		int len=strlen(current->word);
		if(len>max_len){                    //code part to find the maximum word length in the given number of rows
			max_len=len;
		}
		current=current->next;
	}
	return max_len;
}


void wgraph(int scaled,unsigned long int rows){   //function to print the word percentage graph
	
	
	unsigned long int total_words=total_w();   //get the total number of different words in the given files
        if(rows>total_words){          //check whether the rows are grater than the total different number of words

                rows=total_words;
        }
	unsigned long int maxw_len=maxlen(rows);  //get the maximum word length
	
	words_t* current=head;  //pointer to the ll

	float initial=current->wPer;      //get the percentage of the first word in the sorted ll

        for(unsigned long int i=0;i<rows;i++){
		int numsq;   //number of squares to print

		if(scaled==0){   //check whether the scaled option is given or not
			if(total_words==1){    //check whether there is only one word in the file
				numsq=70-maxw_len;
			}else{
				numsq=((72-maxw_len)*(current->wPer))/100;  //calculate number of squares to print

			}
		}else{
			if(total_words==1){
				numsq=70-maxw_len;    //calculate number of squares to print

			}else{
				numsq=((72-maxw_len)*(current->wPer))/(initial);

			}
		}

		for(int j=0;j<(maxw_len+2);j++){     //code part to print the graph
			printf(" ");          //print spaces
		}
		printf("\u2502");    //print |

		for(int k=0;k<numsq;k++){
			printf("\u2591");   //print squares
		}
		printf("\n");

		printf(" %s",current->word);   //print a word in the graph
		for(int l=0;l<(maxw_len+1-(strlen(current->word)));l++){
			printf(" ");             //print spaces
		}
		printf("\u2502");  //print |

		for(int m=0;m<numsq;m++){
			printf("\u2591");      //print squares
		}

		printf("%.2f",current->wPer);  //print word percentage with 2 decimal places
		printf("%c",37);   //print % 
		printf("\n");
		
		for(int j=0;j<(maxw_len+2);j++){
                        printf(" ");               //print spaces
                }
                printf("\u2502");  //print |

                for(int k=0;k<numsq;k++){
                        printf("\u2591");   //print squares
                }
                printf("\n");

		for(int j=0;j<(maxw_len+2);j++){
                        printf(" ");           //print spaces
                }
                printf("\u2502");   //print |
		printf("\n");
		current=current->next;  //move to next node of the ll
        }

	for(int j=0;j<(maxw_len+2);j++){  //print spaces
		printf(" ");
	}

	printf("\u2514");   //print the bottom part of the graph

	int dash=80-(maxw_len+3);  //count number of - in the last line of the graph
	for(int c=1;c<=dash;c++){
		printf("\u2500");  //print -
	}

}

int countCharacters(char array1[],int cor){  //function to count the occurences of a character in the given files

	char c;    //c-store a character
	FILE *fp;    //pointer to file
        fp=fopen(array1,"r");   //oprn a file to read


	if(fp==NULL){

		printf("Cannot open one or more given files\n"); //prompt msg
                exit(-1);  //terminate progam
	

        }else{
	       while((c=getc(fp)) && (c!=EOF)){   //read a file character by character

			int check=0;  //check - used to check the validity of a character
			int in=0;  //in-used to check whether the character is already in the array

			if((isalpha(c)!=0) || (isdigit(c)!=0)){   //check whether the character is in the alphabet or digit
				c=tolower(c);  //convert a character to lowercase
				check=1;   //assign check to one
			}

			if(check==1){  //if the character is in alphabet or it is a digit,then following code part  executes

				int c1;  //counter variable

				for(c1=0;(carray[c1].ch!='\0') && (in==0);c1++){    //loop trough the carray
							
					if(carray[c1].ch==c){   //if the character is already in the array ,then following code part executes
						in=1;
						carray[c1].count=carray[c1].count+1;  //increment count by 1
					}
				}
					
				if(in==0){    //if the character is not in the carray then the following code executes

					carray[c1].ch=c;   //append character to carray
					carray[c1].count=1;  //assign 1 to count  
					carray[c1].order=cor; //assign character appearance order to the array
					cor++;   //increment character appearence order by 1
				}
			}
		}
		fclose(fp);   //close the file
	}

	return cor;  //return the character appearance order
}



void sortc(cha_t carray[]){    //function to sort the carray in descending order
	
	int oval; //variable declerations
	int val;
	char chn;
	
	for(int c3=0;carray[c3].ch!='\0';c3++){   //loop through the carray

		for(int c4=c3+1;carray[c4].ch!='\0';c4++){

			if(carray[c3].count<carray[c4].count){     //code part to sort the carray in descending order
				oval=carray[c4].order;
				val=carray[c4].count;
				chn=carray[c4].ch;
								//swap elements
				carray[c4].count=carray[c3].count;
				carray[c4].ch=carray[c3].ch;
				carray[c4].order=carray[c3].order;

				carray[c3].count=val;
				carray[c3].ch=chn;
				carray[c3].order=oval;
			}

		}
	
	}

	for(int c5=0;carray[c5].ch!='\0';c5++){   //loop through the sorted carray

		for(int c6=c5+1;carray[c6].ch!='\0';c6++){
			if((carray[c5].count) == (carray[c6].count)){
				if((carray[c5].order) > (carray[c6].order)){   //code part to sort the carray accoding to the appearence order(when there are characters with similar count)
		        		val=carray[c6].count;
                                	chn=carray[c6].ch;
					oval=carray[c6].order;
									//swap elements
                               		carray[c6].count=carray[c5].count;
                               		carray[c6].ch=carray[c5].ch;
				        carray[c6].order=carray[c5].order; 

                               		carray[c5].count=val;
                               		carray[c5].ch=chn;
					carray[c5].order=oval;
				}
			
			}
		}
	}
}



void percentage(cha_t carray[]){   //function to count character percentages
	unsigned long int sum=0;    //sum - variable to store the sum of all characters in the gien files
	for(int c7=0;carray[c7].ch!='\0';c7++){  //code to find sum
		sum=sum+carray[c7].count;
	}
	
	for(int c8=0;carray[c8].ch!='\0';c8++){    //code to evaluate the percentages of each characters
		carray[c8].per=((float)(carray[c8].count)*100)/sum;
	}
}


int clen(cha_t carray[]){   //function to find the length of carray
	int clength=0;
	for(int i=0;carray[i].ch!='\0';i++){  //loop throuh the carray
		clength++;
	}

	return clength;  //return the length of the carray
}



void cgraph(int scaled,int rows,cha_t carray[]){   //function to print the character count of the given files
	
	if(rows>36){     //check whether the argument after -l is grater thhen 36 or not
		rows=36;
	}

	if(rows>clen(carray)){    //check whether the argument after -l is grater than the length of the carray or not
		rows=clen(carray);
	}

	for(int c9=0;c9<rows;c9++){   // code part to print the rows of the graph

		int numsq;  //variable to store the number of squares need to print

		if(scaled==0){   //check whether the --scaled argument is given or not

			if(clen(carray)==1){   //check whether the length of carray is 1 or not
			       	numsq=(69*carray[c9].per)/100;  //evaluate the number of squares 
			}else{
				numsq=(70*carray[c9].per)/100;
			}
		}else{      //when --scaled option is not given the following code part  execute
			if(clen(carray)==1){    
			       	numsq=(69*carray[c9].per)/(carray[0].per);
					
                        }else{
                                numsq=(70*carray[c9].per)/(carray[0].per);  //evaluate number of squares
                        }

		}
					
		
		
		printf("   \u2502");  //print (   |)
                for(int c10=0;c10<numsq;c10++){
                	 printf("\u2591");      //print a square
                }
	       	printf("\n");   //print new line

		printf(" %c \u2502",carray[c9].ch);  //print( character |)
		for(int c10=0;c10<numsq;c10++){
                	printf("\u2591");  //print a square
                }
		printf("%.2f",carray[c9].per);   //print percentage value of the character with 2 decimal places
		printf("%c",37);   //print %
                printf("\n");

		printf("   \u2502");  //print (   |)
                for(int c10=0;c10<numsq;c10++){
                	printf("\u2591");  //print a square
                }
                printf("\n");

		printf("   \u2502");  //print (   |)
		printf("\n");


	}
		
	printf("   \u2514");  //print (|_) 
	for(int c10=1;c10<=76;c10++){  //code part to print the bootom part of the graph
		printf("\u2500");
	}
	
}	


