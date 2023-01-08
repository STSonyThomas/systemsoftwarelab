#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>

#define MAX_NAME_LEN 256

//fucniton definitions

//have to create a directory create a file in a directory and display contents

void createDirectory(void);
void displayDirectory (int level);
void createFile(void);

int main(){
    while(1){
        int choice;
        printf("Enter/ 1 to create Directory\nEnter / 2 to view the directory\nEnter / 3 to create file\nEnter / 4 to exit");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
                createDirectory();
                break;
            case 2:
                displayDirectory(0);
                break;
            case 3:
                createFile();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid entry! Try again!\n");
                break;
        }
    }
    
}


void createDirectory(void){
    char dir_name[MAX_NAME_LEN];
    printf("Enter directory name :");
    fgets(dir_name,MAX_NAME_LEN,stdin);
    //get rid of the trailing /n
    dir_name[strcspn(dir_name,"\n")]=0;

    if(strlen(dir_name)!=0){
        if(mkdir(dir_name,0700)!=0){
            perror("Error creating sub-directory");
            return ;
        }
    }

    printf("Directory name %s created successfully",dir_name);
}
void displayDirectory(int level){
    DIR *dir;
    struct dirent *entry;
    char path[MAX_NAME_LEN];

    dir =opendir(".");
    if(dir==NULL){
        perror("Error opening directory");
        return ;
    }
    // printf("List of directories:\n");
    while((entry=readdir(dir))!=NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        //print only directories here(not files)
        for(int i=0;i<level;i++){
            printf(" ");
        }
        printf("%s\n",entry->d_name);
        if(entry->d_type==DT_DIR){
            int j=snprintf(path,MAX_NAME_LEN,"%s/%s",".",entry->d_name);
            chdir(path);
            displayDirectory(level+1);
            chdir("..");
        }
    }
    closedir(dir);
}
void createFile(void){
    char path[MAX_NAME_LEN],user[60],file_name[MAX_NAME_LEN];
    printf("Enter the user into which file has to be inserted");
    scanf("%s",user);
    getchar();
    user[strcspn(user,"/n")]=0;
    //filename
    printf("Enter the file name");
    scanf("%s",file_name);
    getchar();
    user[strcspn(file_name,"/n")]=0;

    if(strlen(user)!=0){
        int j=snprintf(path,MAX_NAME_LEN,"%s/%s/%s",".",user,file_name);
        printf("%s",path);
        FILE *fp =fopen(path,"w");
        if(fp==NULL){
            perror("Error creating file");
            return;
        }
    }
    
}