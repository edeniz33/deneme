/*Eylul Deniz Yildiz 2385748 CNG 315 Assignment 2 Solution*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Student{
	char Student_ID[4];
	char Name[41];
	char Letter_Department_Code[4];
};
void SearchStudent(struct Student* studentlist,char id[],int size,int preference);
int next_prime(int doubled);
int convert (char idnum);
int check_uniqueness(struct Student* studentlist,char id[],int size);
void insert_student(struct Student* studentlist,char id[],char name[],char dept[],int table_size,int technique);
struct Student* rehashing(struct Student* studentlist,int *size,int technique);


int main(){
	int technique,j;
	int total_students=0;
	struct Student* studentlist;
	int table_size=11;//at the beginning, we need to initialize table size as 11
	studentlist=(struct Student* )malloc(table_size*sizeof(struct Student));
    
	printf("\n Enter open addressing technique to be used");
	printf("\n (1):double hashing \n(2):quadratic probing:  ");
	scanf("%d",&technique);//open addressing chosen
	float load_factor=(float)total_students/(float)table_size;//first declaring load factor with 0 students and 11 sized table

	for(j=0;j<table_size;j++){//default initializing 
		strcpy(studentlist[j].Letter_Department_Code,"nul");
		strcpy(studentlist[j].Name,"null");
		strcpy(studentlist[j].Student_ID,"nul");}

	char temp_ID[4],temp_Name[41],temp_dept_code[4];//these values will be used for getting data from user
    int menu=0,key1,key2,i=0,hash1,hash2,doubled,new_size,rehash_control=0;
   
    while(menu!=4){//functionalities menu providing
    printf("\n*************** MENU ********************* ");
    printf("\n (1) Add");
    printf("\n (2) Search");
    printf("\n (3) Print");
    printf("\n (4) Exit");
    printf("\n Please enter your choice: ");
    scanf("%d",&menu);
   insert_student(studentlist,"C12","Salley Batess","CHM",table_size,1);
    insert_student(studentlist,"A56","AShley Norman","MEC",table_size,1);
   insert_student(studentlist,"A69","Peter Holland","CNG",table_size,1);
    insert_student(studentlist,"A00","George Martin","ASE",table_size,1);
    insert_student(studentlist,"U11","Molly Eleanor","PSY",table_size,1);
    total_students=5;
    	if(menu==1){//add a student case
			printf("\nEnter unique identifier: ");
   			scanf("%s",&temp_ID);
   			if(check_uniqueness(studentlist,temp_ID,table_size)==0){//if id is unique, continue
   				printf("\n The id you entered is not unique! BYE");
				return 0;}
   			fflush(stdin);
			printf("\nEnter name: ");
			scanf("%[^\n]s",&temp_Name);
			printf("\nEnter department: ");
			scanf("%s",&temp_dept_code);
			printf("\n%s has been registered.",temp_Name);
			
			insert_student(studentlist,temp_ID,temp_Name,temp_dept_code,table_size,technique);
		    total_students=total_students+1;//after adding number of student increased 
		    printf("\n total student %d  table size %d",total_students,table_size);
		    load_factor=(float)total_students/(float)table_size;//updated load factor
		    printf("\n load %f ",load_factor);
			if(load_factor>=0.50){
				printf("\n debug");
		    	studentlist=rehashing(studentlist,&table_size,technique);
				printf("\n debug2");
				}
			}
					
        else if(menu==2){//SEARCHING A STUDENT CASE
            char identifier[4];
	    	printf("\nEnter unique identifier: ");
	    	scanf("%s",&identifier);
	    	SearchStudent(studentlist,identifier,table_size,technique);
		}
		
	    else if(menu==3){//PRINTING CASE
	        int g;
	        printf("\nIndex  ID     	Name     	Department");
	        
		    for(g=0;g<table_size;g++){
	        	if(strcmp(studentlist[g].Student_ID,"nul")==0)
	        		printf("\n%d ",g);
	        	else 
	        		printf("\n %d 	%s    %s	%s",g,studentlist[g].Student_ID,studentlist[g].Name,studentlist[g].Letter_Department_Code);
			}
			
		}
		else if(menu==4){
			printf("\n You chose exit ! GOODBYE!");
			return 0;
		}
   		else//INVALID CHOSEN ENTERED CASE
   		printf("\n You entered invalid chose goodbye!");
}
   	
	return 0;
}
void SearchStudent(struct Student* studentlist,char id[],int size,int preference){//this function is searching the student with given ID by user inside hash table created
	//null olduðu an durcak 
	int temp_id_one,temp_id_two,i,j,key1,key2,hash1,hash2,size2=size,available,found;
	if(preference==1){//searching for double hashing case used table
		temp_id_one=convert(id[1]);
		temp_id_two=convert(id[2]);
		key1=(id[0]-65)+(temp_id_one)+(temp_id_two);
		hash1=(2 * key1)%size;//first computation for index finding	
		int available=0;
		if(strcmp(studentlist[hash1].Student_ID,id)==0){
			printf("\nName: %s",studentlist[hash1].Name);
			printf("\nDepartment: %s",studentlist[hash1].Letter_Department_Code);
			available+=1;
			}
			
		if(available==0){//this means we couldnt find,while adding this one there was a collison
			for(i=0;i<size;i++){
				hash2=(hash1+i*(7-(key1%7)))%size;//collision resolution applied here
				if(strcmp(studentlist[hash2].Student_ID,id)==0){
					printf("\nName: %s",studentlist[hash2].Name);
					printf("\nDepartment: %s",studentlist[hash2].Letter_Department_Code);
					available+=1;}
				}}
	
		if(i==size && available==0)//after all the searches, this student is not there
			printf("\nStudent is not found!!");
    }
	else if(preference==2){//searching for quadratic hashing case used table
		temp_id_one=convert(id[1]);
		temp_id_two=convert(id[2]);
		key2=(id[0]-65)+(temp_id_one)+(temp_id_two);
		hash2=(2 * key2)%size;//first computation for index finding	
		int found=0;
		if(strcmp(studentlist[hash2].Student_ID,id)==0){
			printf("\nName: %s",studentlist[hash2].Name);
			printf("\nDepartment: %s",studentlist[hash2].Letter_Department_Code);
			found+=1;
			}
		if(found==0){//this means we couldnt find,while adding this one there was a collison
			for(j=0;j<size2;j++){
				hash2=(hash1+j*(7-(key1%7)))%size;
				if(strcmp(studentlist[hash2].Student_ID,id)==0){
					printf("\nName: %s",studentlist[hash2].Name);
					printf("\nDepartment: %s",studentlist[hash2].Letter_Department_Code);
					found+=1;}
			}}	
	
		if(j==size2 && found==0)
			printf("\nStudent is not found!!");
	}}
			
int convert (char idnum){
	if(idnum=='0')
		return 0;
	else if(idnum=='1')
		return 1;
	else if(idnum=='2')
		return 2;
	else if(idnum=='3')
		return 3;
	else if(idnum=='4')
		return 4;
	else if(idnum=='5')
		return 5;
	else if(idnum=='6')
		return 6;
	else if(idnum=='7')
		return 7;
	else if(idnum=='8')
		return 8;
	else if(idnum=='9')
		return 9;				
}
int next_prime(int doubled){//This algorithm finds the next prime number in realloc process
	int i,j;
	for(i=doubled+1;i>0;i++){
		int count=0;
		for(j=1;j<=i;j++){
			if(i%j==0)
			count++;}

			if(count==2){
				break;}
	}
    return i;}


int check_uniqueness(struct Student* studentlist,char id[],int size){//chechks the id if it is assigned to the list before
	int h;
	for(h=0;h<size;h++){
		if(strcmp(studentlist[h].Student_ID,id)==0){
			return 0;	
			}
	}	
			return 1;
}
void insert_student(struct Student* studentlist,char id[],char name[],char dept[],int table_size,int technique){
int temp_id_one,temp_id_two,index,hash1,hash2,key1,key2,doubled,i=0;

if(technique==1){//DOUBLE HASHING PART
	temp_id_one=convert(id[1]);
	temp_id_two=convert(id[2]);
	key1=(id[0]-65)+(temp_id_one)+(temp_id_two);
	hash1=(2 * key1)%table_size;//first computation for index finding
				
	if(strcmp(studentlist[hash1].Student_ID,"nul")==0 ){//if target location is empty,no collosion case
		strcpy(studentlist[hash1].Name,name);//location the calculated index of the hash table 
		strcpy(studentlist[hash1].Letter_Department_Code,dept);
		strcpy(studentlist[hash1].Student_ID,id);
		}
										
    else if(strcmp(studentlist[index].Student_ID,"nul")!=0){
	while(i<table_size){
		index=(hash1+i*(7-(key1%7)))%table_size;
		if((strcmp(studentlist[index].Student_ID,"nul")==0)){
			strcpy(studentlist[index].Name,name);//location the calculated index of the hash table 
			strcpy(studentlist[index].Letter_Department_Code,dept);
			strcpy(studentlist[index].Student_ID,id);
			break;}
		else 
			i++;
		}}					
}				
						
else if(technique==2){//QUADRATIC PART
	temp_id_one=convert(id[1]);
	temp_id_two=convert(id[2]);
	key2=(id[0]-65)+(temp_id_one)+(temp_id_two);
	hash2=(2 * key2)%table_size;
				
	if(strcmp(studentlist[index].Student_ID,"nul")==0){//if target location is empty,no collosion case
		strcpy(studentlist[index].Name,name);//location the calculated index of the hash table 
		strcpy(studentlist[index].Letter_Department_Code,dept);
		strcpy(studentlist[index].Student_ID,id);
		}
									
	else if(strcmp(studentlist[index].Student_ID,"nul")!=0 ){
	
		while(i<table_size){
			index=(hash2+i*i)%table_size;
			if((strcmp(studentlist[index].Student_ID,"nul")==0)){
				strcpy(studentlist[index].Name,name);//location the calculated index of the hash table 
				strcpy(studentlist[index].Letter_Department_Code,dept);
				strcpy(studentlist[index].Student_ID,id);
				break;}
			else 
				i++;}}}						
}

struct Student* rehashing(struct Student* studentlist,int *size,int technique){//reshashing process for double hashing option
	int oldsize=size;
	int doubled=*size*2;
	*size=next_prime(doubled);
	printf("\n next prime is %d",*size);
	int sending_size=size;
	
	struct Student* studentlist2=(struct Student*) malloc(*size*sizeof(struct Student));
	int j;
	for(j=0;j<size;j++){//default initializing
		strcpy(studentlist2[j].Letter_Department_Code,"nul");
		strcpy(studentlist2[j].Name,"null");
		strcpy(studentlist2[j].Student_ID,"nul");
	}
	printf("\n after malloc");
    int i;
    for(i=0;i<oldsize;i++){
    	if(strcmp(studentlist[i].Student_ID,"nul")!=0){
    		insert_student(studentlist2,studentlist[i].Student_ID,studentlist[i].Name,studentlist[i].Letter_Department_Code,sending_size,technique);
    		printf("\n inserting %d",i);
		}
	}
	free(studentlist);
	return studentlist2;}	
    	


