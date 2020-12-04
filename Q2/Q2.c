#include<stdio.h>
int main()
{
    int n, m; 
    printf("No. of processes and resources: \n"); 
    scanf("%d %d", &n, &m); 
    printf("\nEnter allocation matrix: \n"); 
    int alloc[n][m]; 
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]); 
        }
    }
    printf("\nEnter max resource matrix: \n"); 
    int max[n][m]; 
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < m; j++)
        {
            scanf("%d", &max[i][j]); 
        }
    }
    int avail[m]; 
    printf("\nEnter available resources: \n"); 
    for(int i=0; i < m; i++)
    {
        scanf("%d", &avail[i]); 
    }
    int complete[n]; 
    for(int i=0; i < n; i++)
    {
        complete[i]=0; 
    }
    int need[n][m]; 
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < m; j++)
        {
            need[i][j]=max[i][j]-alloc[i][j]; 
        }
    }
    int seq[n]; 
    int process, count=0; 
    do
    {
        process=-1; 
        for(int i=0; i < n; i++)
        {
            if(complete[i]==0)
            {
                process=i; 
                for(int j=0; j < m; j++)
                {
                    if(avail[j]  <  need[i][j])
                    {
                        process=-1; 
                        break; 
                    }
                }
            }
            if(process!=-1)
                break; 
        }
        if(process!=-1)
        {
            printf("Completed PID : %d\n", process); 
            seq[count]=process; 
            count ++ ; 
            for(int j=0; j < m; j++)
            {
                avail[j]+=alloc[process][j]; 
                // alloc[process][j]=0; 
                // max[process][j]=0; 
            }
            complete[process]=1; 
        }
    }while(count !=n && process !=-1); 
    if(count == n)
    {
        printf("SAFE_STATE Sequence : "); 
        for(int i = 0;  i  <  n;  i++)
			printf("%d : ",  seq[i]); 
        printf("\nInput request (in the order Process No, ResNo, Count): ");
        int resNo, count, pno;
        scanf("%d %d %d", &pno, &resNo, &count);
        if(pno > n){
            printf("Invalid Process No\n");
        }
        else if(resNo > m){
            printf("Invalid Resource No\n");
        }
        else if(count > avail[resNo]){
            printf("Cannot allocate - Not enough resources\n");
        }
        else if(count + need[pno][resNo] > max[pno][resNo]){
            printf("Excess resource requested\n");
        }
        else{
            printf("Allocation possible\n");
           
        }
    }
    else
    {
        printf("Unsafe State\n"); 
    }
}
