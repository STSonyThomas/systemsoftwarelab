#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//fucntion decalrations
void createPage(int* remPage, int* noProcess,int* processPage);
void calcPhysical(int pageSize,int maxpage,int* noProcess, int* processPage,int** pagingTable);





int main(){
    int memSize,pageSize,noPage,noProcess,x,y,z,remPages;
    int* processPage;
    int** pagingTable;

    printf("Enter the size of memory: ");
    scanf("%d",&memSize);
    printf("Enter pageSize : ");
    scanf("%d",&pageSize);
    // no of pages = memory size/ pageSize
    noPage = memSize / pageSize;
    printf("The no of pages = %d",noPage);

    //preliminary preparation over

    //asking user to write the number of processes

    printf("Enter the number of processes: ");
    scanf("%d",&noProcess);

    //assigning in a dynamic fashion the no of rows for processPage(this contains the number of pages of each process)
    processPage =(int*)malloc(sizeof(int)*noProcess);
    //assigning size to 2 dimensional array for pagingTable
    pagingTable =(int**)malloc(sizeof(int)*noProcess);
    for(int i=0;i<noProcess;i++){
        pagingTable[i]=(int*)malloc(sizeof(int)*noPage);
        //because the maximum number of pages that a process can take
        //is the max available pages in logical memory that is noPage
    }


    //setting the remaining unassigned pages to total number of pages initially
    remPages = noPage;


    createPage(&remPages,&noProcess,processPage);
    calcPhysical(pageSize,noPage,&noProcess,processPage,pagingTable);

    free(processPage);
    free(pagingTable);
    return 0;

}






//fucntion definitions

void createPage(int* remPage, int* noProcess,int* processPage){
    int pages;

    for(int i=0;i<*noProcess;i++){
        printf("Enter the no of Pages required for process%d : ",i+1);
        scanf("%d",&pages);
        if(pages>*remPage){
            printf("Memory full,terminating now!");
            break;
        }
    *remPage-=pages;
    processPage[i]=pages;
    }
}

//for pagingTable and physical memory calculation

void calcPhysical(int pageSize,int maxpage,int* noProcess, int* processPage,int** pagingTable){
    int pno,pgno,x;
    for(int i=0;i<*noProcess;i++){
        printf("Enter the paging of process %d\n",i+1);
        for(int j=0;j<processPage[i];j++){
            printf("for page %d\n",j+1);
            scanf("%d",&pagingTable[i][j]);
        }
    }

    printf("Enter the process no,page no,offset : ");
    scanf("%d %d %d",&pno,&pgno,&x);

    if(pno<=*noProcess &&x<=maxpage){
        if(pgno<=processPage[pno-1]){
            printf("\nthe physical address is: %d\n",(pagingTable[pno-1][pgno-1]*pageSize+x));
        }
    }else{
        printf("Error in process no, page no or displacement\n");
    }
}