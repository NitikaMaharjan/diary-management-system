//diary management system
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//Global variable used for loop 
int i;

//Structure to hold each record
struct record{
	char date[15];
	char time[10];
	char location[25];
	char note[500];
};

//Function Prototypes

//function to add new record
void addRecord();
//function to display record
void viewRecord();
//function to update record
void updateRecord();
//function to delete record
void deleteRecord();
//function to display the header
void display();



void main(){
	
	int choice;
	char ch;
	
	do {
		
		display();
		
		//displaying the main menu options
		printf("\n\n\t\t\t\t\t\t      MAIN MENU\n");
		printf("\n\t\t\t\t PRESS[1]:Add Record");
    	printf("\n\t\t\t\t PRESS[2]:View Record");
    	printf("\n\t\t\t\t PRESS[3]:Update Record");
    	printf("\n\t\t\t\t PRESS[4]:Delete Record");
    	printf("\n\t\t\t\t PRESS[5]:Exit\n\n\t\t\t\t");
    
    	for (i=0; i<52; i++){
			printf("=");
		}
		printf("\n\n\t\t\t\t\t       PRESS KEY OF YOUR CHOICE : ");
		scanf("%d", &choice);
	
	switch(choice){
		case 1:
			addRecord();
			break;
		
		case 2:
			viewRecord();
			break;
		
		case 3:
			updateRecord();
			break;
			
		case 4:
			deleteRecord();
			break;
			
		case 5:
			printf("\n\t\t\t\tEXITING........\n");
			printf("\n\t\t\t\t\t   <<THANK YOU FOR USING THE PROGRAM>>\n");
			getch();
			exit(0);
			
		default:
            printf("\n\t\t\t\t\t\t    INVALID CHOICE\n");
            printf("\n\t\t\t\t\t       PRESS ANY KEY TO TRY AGAIN");
            getch();
			break;
	}
	fflush(stdin);
	printf("\n\n\t\t\t\tDo you want to choose again(Y/N)? : ");
	scanf("%c", &ch);
	
	}while(ch=='y' || ch=='Y');
	
	printf("\n\t\t\t\tEXITING........\n");
	printf("\n\t\t\t\t\t   <<THANK YOU FOR USING THE PROGRAM>>\n");
	getch();

}

void addRecord(){
	FILE *fp ;
	struct record r;
	char fileName[15];

	display();
	
	printf("\n\n\t\t\t\t\t\t WELCOME TO ADD RECORD");
	
	printf("\n\n\t\t\t\tEnter file name : ");
	scanf("%s", fileName);
	
	//opening file in write mode
	fp=fopen(fileName,"wb+");
	
	//checking if the file is opened successfully
	if(fp==NULL){
        printf("\n\t\t\t\t\t\tSYSTEM ERROR...");
		printf("\n\t\t\t\tPRESS ANY KEY TO EXIT");
		getch();
		return;
	}
	
    //clearing the input buffer
	getchar();
	
	//getting record details from the user
	printf("\t\t\t\tEnter Date(dd/mm/yyy) : ");
	fgets(r.date, sizeof(r.date), stdin);
	
	printf("\t\t\t\tEnter Time(hh:mm(am/pm)) : ");
    fgets(r.time, sizeof(r.time), stdin);
    
    printf("\t\t\t\tEnter Location : ");
    fgets(r.location, sizeof(r.location), stdin);
    
    printf("\n\t\t\t\tEnter note : \n\n\t\t\t\t");
    fgets(r.note, sizeof(r.note), stdin);
	
	//writing record to the file
	fwrite(&r, sizeof(r),1,fp);
	printf("\n\t\t\t\t\t\t  YOUR RECORD IS ADDED...\n");
	
	printf("\n\t\t\t\t");
	for (i=0; i<52; i++){
		printf("=");
	}
	
	//closing file
	fclose(fp);
}


void viewRecord(){
	FILE *fpn;
	struct record r2;
	char fileName[15];
	
	display();
	
	printf("\n\n\t\t\t\t\t\t WELCOME TO VIEW RECORD");
	
	printf("\n\n\t\t\t\tEnter file name that you want to view : ");
	scanf("%s", fileName);
	
	fpn=fopen( fileName,"rb");
	
	//checking if the file is opened successfully
	if(fpn==NULL){
		printf("\n\t\t\t\t\t\tTHE RECORD DOES NOT EXIST..." ) ;
		printf("\n\n\t\t\t\tPRESS ANY KEY TO EXIT");
		getch();
		return;
	}
	
	//displaying the contents of the file
	printf("\n\t\t\t\tThe contents of the file %s are : \n", fileName);
        while(fread(&r2,sizeof(r2),1,fpn) == 1 ){
			printf("\n\t\t\t\t\t\t\t\tDate : %s", r2.date);
            printf("\n\t\t\t\t\t\t\t\tTime : %s", r2.time);
            printf("\n\t\t\t\t\t\t\t\tLocation : %s", r2.location);
            printf("\n\t\t\t\tNote :\n\n\t\t\t\t%s\n", r2.note);
        }
    
	printf("\n\t\t\t\t");
	for (i=0; i<52; i++){
		printf("=");
	}
	
	//closing the file
	fclose(fpn);
	printf("\n\n\t\t\t\t\t   PRESS ANY KEY TO EXIT...");
	getch();
}

void updateRecord(){
    FILE *fp;
    FILE *ftemp;
    struct record r, temp;
    char fileName[15];

    display();

    printf("\n\n\t\t\t\t\t\t WELCOME TO UPDATE RECORD");

    printf("\n\n\t\t\t\tEnter file name to update : ");
    scanf("%s", fileName);
	
	//opening file in read mode
    fp = fopen(fileName,"rb");
    //checking if the file is opened successfully
    if(fp == NULL){
        printf("\n\t\t\t\t\t\tFILE DOES NOT EXIST...");
        printf("\n\n\t\t\t\tPRESS ANY KEY TO EXIT");
        getch();
        return;
    }
    
    //opening temporary file for writing
    ftemp = fopen("tempfile.bin", "wb+");
    //checking if the file is opened successfully
    if(ftemp == NULL){
        printf("\n\t\t\t\t\t\tSYSTEM ERROR...");
        fclose(fp);
        getch();
        return;
    }
    
	//clearing input buffer
	getchar();
    
	//getting record details from the user	
    printf("\t\t\t\tEnter New Date(dd/mm/yyyy) : ");
	fgets(r.date, sizeof(r.date), stdin);
            
    printf("\t\t\t\tEnter New Time(hh:mm(am/pm)) : ");
    fgets(r.time, sizeof(r.time), stdin);
            
    printf("\t\t\t\tEnter New Location : ");
    fgets(r.location, sizeof(r.location), stdin);
            
    printf("\n\t\t\t\tEnter New note : \n\n\t\t\t\t");
    fgets(r.note, sizeof(r.note), stdin);
            
    fwrite(&r, sizeof(r), 1, ftemp);
    
	printf("\n\t\t\t\t\t\t  RECORD UPDATED...\n");
    
    //closing original file
    fclose(fp);
    //closing temporary file
    fclose(ftemp);
	
	//removing original file 
    remove(fileName);
    //renaming the temporary file with the name of the file we just deleted
    rename("tempfile.bin", fileName);

    printf("\n\t\t\t\t");
    for (i=0; i<52; i++){
        printf("=");
    }

    printf("\n\n\t\t\t\t\t   PRESS ANY KEY TO EXIT...");
    getch();
}

void deleteRecord(){
	char fileName[15];
	
	display();
	
	printf("\n\n\t\t\t\t\t\t WELCOME TO DELETE RECORD");
	
	printf("\n\n\t\t\t\tEnter file name that you want to delete : ");
	scanf("%s", fileName);
	
	//deleting the file
    if (remove(fileName) == 0) {
        printf("\n\n\t\t\t\t     File %s has been deleted successfully...\n", fileName);
    } else {
        printf("\n\n\t\t\t\t        Failed to delete the file %s...\n", fileName);
    }
	
	printf("\n\t\t\t\t");
	for (i=0; i<52; i++){
		printf("=");
	}
	
	printf("\n\n\t\t\t\t\t   PRESS ANY KEY TO EXIT...");
	getch();  
}

void display(){
	system("cls");
		
	printf("\n\n\t\t\t\t");
	for (i=0; i<52; i++){
		printf("=");
	}
	printf("\n\t\t\t\t\t        DIARY MANAGEMENT SYSTEM\n\t\t\t\t");
	for (i=0; i<52; i++){
		printf("=");
	}

}
