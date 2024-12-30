#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student{
    char name[21];
    int grade;
    int group;
    int paid;
    struct student *next;
}Student;

Student *dp[6][2][2], *dpcurr[6][2][2];
int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        int n;
        scanf("%d",&n);
        Student *unsorted = malloc(sizeof(Student)*n);
        Student *sorted = malloc(sizeof(Student)*n);
        for(int i = 0; i < n; i++){
            scanf("%s %d %d %d",unsorted[i].name, &unsorted[i].grade, &unsorted[i].group, &unsorted[i].paid);
            unsorted[i].next = NULL;
        }
        for(int i = 0; i < n; i++){
            scanf("%s %d %d %d",sorted[i].name, &sorted[i].grade, &sorted[i].group, &sorted[i].paid);
            sorted[i].next = NULL;
        }
        memset(dp,0,sizeof(dp));
        memset(dpcurr,0,sizeof(dpcurr));
        for(int i = 0; i < n; i++){
            if(dp[sorted[i].grade][sorted[i].group][sorted[i].paid]){
                dpcurr[sorted[i].grade][sorted[i].group][sorted[i].paid]->next = &sorted[i];
                dpcurr[sorted[i].grade][sorted[i].group][sorted[i].paid] = &sorted[i];
            }
            else{
                dp[sorted[i].grade][sorted[i].group][sorted[i].paid] = dpcurr[sorted[i].grade][sorted[i].group][sorted[i].paid] = &sorted[i];
                dpcurr[sorted[i].grade][sorted[i].group][sorted[i].paid] = &sorted[i];
            }
        }
        int flag = 1;
        for(int i = 0; i < n; i++){
            if(dp[unsorted[i].grade][unsorted[i].group][unsorted[i].paid]==NULL || 
                strcmp(dp[unsorted[i].grade][unsorted[i].group][unsorted[i].paid]->name,unsorted[i].name)){
                printf("NO\n");
                flag = 0;
                break;
            }
            else{
                dp[unsorted[i].grade][unsorted[i].group][unsorted[i].paid] = dp[unsorted[i].grade][unsorted[i].group][unsorted[i].paid]->next;
            }
        }
        if(flag) printf("YES\n");
        free(unsorted);
        free(sorted);
    }
}