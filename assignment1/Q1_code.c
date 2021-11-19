#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
	// predefined set of programs
	char* programs[]={"firefox","ls","ps","libreoffice"};
	int cont=1;  
	char *args[]={"./EXEC",NULL}; 
	while(cont){
		printf("Enter an option from below :\n");
		printf("1. Firefox\n");
		printf("2. List all files\n");
	        printf("3. List processes running\n");
		printf("4. LibreOffice\n");
		int option; 
		printf("Your choice :");
		scanf("%d",&option);
		
		//check whether our option is valid or not
		if(option>=5 || option<=0){
			printf("ERROR - INVALID INPUT\n");
		}
		// if valis run program
		else{
			int proc_id=fork(); 
			if(proc_id==0){ 
				execvp(programs[option-1],args);
			}
			sleep(2); // wait for 2 seconds
		}
		printf("Do you want to continue? Press any number for Yes and 0 for No\n");
		 // asking the user if they want to continue or not
		scanf("%d",&cont);
	}
}
