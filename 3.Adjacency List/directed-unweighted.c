#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct node** graph_init(struct node**);
struct node** graph_construct(struct node**);
struct node** graph_linking(struct node**,int,int);
struct node** linker(struct node**,int,int);
bool duplicate(struct node*,int,int);
void display(struct node**);

struct node{
    int vertex;
    struct node *next;
};
int v_num = 0;

int main(){
    struct node **graph;
    graph = graph_init(graph);
    graph = graph_construct(graph);
    display(graph);
    return 0;
}

void display(struct node **graph){
    int i = 0;
    struct node* temp;
    printf("\n\n..........Your Output..........\n");
    for(i = 0 ; i < v_num;i++){
            temp = graph[i];
           while (temp != NULL)
            {
                printf("%d=>",temp->vertex);
                temp = temp->next;
            }
            printf("Null\n\n");
            
        
    }
}

bool duplicate(struct node* temp,int src,int dest){
   while(temp!= NULL){
    if(temp->vertex == dest + 1){
        return true;
    }
    temp = temp->next;
   }
   return false; 
}

struct node** graph_linking(struct node** graph , int src , int dest){
   if (duplicate(graph[src]->next,src,dest))
   {
      return graph;
   }
        graph = linker(graph,src,dest);
    return graph;
}

struct node** linker(struct node** graph,int src , int dest){
    struct node *temp , *new;
    new = (struct node*)malloc(sizeof(struct node));
    new->vertex = dest + 1;
    new->next = NULL;
    temp = graph[src];
    if(temp->next == NULL){
        temp->next = new;
    } 
    else{
     while (temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    return graph;
}

struct node** graph_construct(struct node** graph){
    int i = 0 , terminate = 0 , count = 0 , target = 0;
    for(i = 0 ; i < v_num ; i++){
        printf("\nPlease enter the connected vertices with vertex %d:\n",i+1);
        terminate = 0;
        count = 0;
        while (terminate == 0 && count < v_num)
        {
            printf("\nFor vertex %d,\nPress 0 to continue\nPress 1 to exit\n",i+1);
            scanf("%d",&terminate);
            if(terminate == 1){
                break;
            }
            printf("\nEnter the connected vertex(range 1 to %d):\n",v_num);
            scanf("%d",&target);
            graph = graph_linking(graph,i,target-1);
            count++;
        }
        
    }
    return graph;
}

struct node** graph_init(struct node **graph){
    int i = 0;
    printf("\nEnter the number of vertices:\n");
    scanf("%d",&v_num);
    graph = (struct node**)malloc(v_num*sizeof(struct node*));
    for(i = 0 ; i < v_num ; i++){
        graph[i] = (struct node*)malloc(sizeof(struct node));
        graph[i]->vertex = i+1;
        graph[i]->next = NULL;
    }
    return graph;
}

