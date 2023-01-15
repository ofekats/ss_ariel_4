#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIST 999999

typedef struct vert_ vert;
typedef struct edge_ edge;

void new_vert(vert * arr_vert1);
void delete_vert (vert ** arr);
void delete (vert ** arr, int input);

typedef struct edge_
{
    int weight;
    vert * dest_vert;
    edge * next;
} edge;

typedef struct vert_
{
    int value;
    edge * next_edge;
    vert * nextV;  
    int dist;
} vert;

void check(vert * arr){
    vert * head = arr;
    int i = 0;
    while(arr != NULL)
    {
        printf ("arr[%d]:%d\n",i,arr->value);
        edge** print_edge = NULL;
        print_edge = &(arr->next_edge);
            while (*print_edge != NULL)
            {
                printf("weight = %d, dest = %d\n", (*print_edge)->weight, ((*print_edge)->dest_vert)->value);
                print_edge = &(*print_edge)->next;
                
            } 
            i++;
        arr = arr->nextV;
    }
    arr = head;

}

void free_all(vert * head_of_vert) {
    vert * current_vert = head_of_vert;
    while (current_vert != NULL) {
        edge * current_edge = current_vert->next_edge;
        while (current_edge != NULL) {
            edge * next_edge = current_edge->next;
            free(current_edge);
            current_edge = next_edge;
        }
        vert * next_vert = current_vert->nextV;
        free(current_vert);
        current_vert = next_vert;
    }
}


char new_graph (vert ** head_of_vert){
    if (*head_of_vert != NULL)
    {
        free_all (*head_of_vert);
    }
    
    int num_of_vert = 0;
    scanf("%d", &num_of_vert);
    vert ** last_vert = NULL;
    vert * array_of_vert = *head_of_vert;
    for (int i = 0; i< num_of_vert; i++){
        if((array_of_vert = (vert*) malloc(sizeof (vert))) == NULL){
        printf ("Not enough memory1, exit program\n");
        if (*head_of_vert != NULL)
        {
            free_all (*head_of_vert);
        }
        exit(-1);
        }
        if (i == 0)
        {
            *head_of_vert = array_of_vert;
            last_vert = &array_of_vert; 
        }
        array_of_vert->next_edge = NULL;
        array_of_vert->value = i;
        array_of_vert->nextV = NULL;
        *last_vert = array_of_vert;
        last_vert = &array_of_vert->nextV;
    }
    array_of_vert = *head_of_vert;
   
    int input_from_user = 0;
    int num_from_user = 0;
    int vert_from_user = 0;
    char n = '0';

    while (scanf("%d" ,&input_from_user) != EOF){
        scanf("%c", &n);
        if (n!= 'n'){
            return (n);
        }

        scanf ("%d", &vert_from_user);
        edge** last_edge = NULL;
        while(array_of_vert != NULL){
            
            if(array_of_vert->value  == vert_from_user){
                break;
            }
            else{
                array_of_vert = array_of_vert->nextV;
            }
        }
        last_edge = &(array_of_vert->next_edge); 
        num_from_user = scanf("%d", &input_from_user);
        
        while (num_from_user != EOF  && num_from_user != 0){
            
            edge * new_edge = NULL;
            if((new_edge = (edge*) malloc (sizeof(edge) )) == NULL)
            {
                printf ("Not enough memory2, exit program\n");
                if (*head_of_vert != NULL)
                {
                    free_all (*head_of_vert);
                }
                exit(-1);
            }

            *last_edge = new_edge;
            (*last_edge)->dest_vert = NULL;
            (*last_edge)->next = NULL;
            (*last_edge)->weight = 0;
            vert * search_dest = *head_of_vert;

            while (search_dest != NULL){
                
                if (search_dest->value == input_from_user){
                    break;
                }
                else{
                    search_dest = search_dest->nextV;
                }
            }
            (*last_edge)->dest_vert = (search_dest);
            scanf("%d", &input_from_user);
            (*last_edge)->weight = input_from_user;
            last_edge = &((*last_edge)->next);
            num_from_user = scanf("%d", &input_from_user);
        }
        array_of_vert = *head_of_vert;
        

    } 
    return (n);   

}



void new_vert(vert * arr_vert1){
    int input_from_user = 0;
    int flag1 = 1;
    int flag2 = 1;
    
    scanf ("%d", &input_from_user);
    vert * arr_vert = arr_vert1;
    vert * prev = arr_vert;
    while(arr_vert != NULL){
        if (arr_vert->value == input_from_user){
            flag1 = 0;
            edge * delet_next_edge1 = arr_vert->next_edge;
            edge * delet_next_edge2 = NULL; 
            while (delet_next_edge1 !=NULL)
            {
                delet_next_edge2 = delet_next_edge1->next;
                free (delet_next_edge1);
                delet_next_edge1 = delet_next_edge2;
                if (delet_next_edge1 !=NULL){   
                    delet_next_edge2 = delet_next_edge2->next;
                }
            }
            arr_vert->next_edge = NULL;
            break;
        }
        else{
            arr_vert = arr_vert->nextV;
        }
        if (!flag2 && prev != NULL){

            prev = prev->nextV;    
        }
        flag2 = 0;
    }
    
    if (flag1){
        arr_vert = prev;
        vert * new_vert = NULL;
        
        if((new_vert = (vert*) malloc (sizeof(vert) )) == NULL)
        {
            printf ("Not enough memory3, exit program\n");
            if (arr_vert1 != NULL)
            {
                free_all (arr_vert1);
            }
            exit(-1);
        }

        new_vert->value = input_from_user ;
        new_vert->next_edge = NULL;
        new_vert->nextV = NULL;
        arr_vert->nextV = new_vert;
        arr_vert = arr_vert->nextV;
    }

    edge** last_edge = NULL;
    last_edge = &(arr_vert->next_edge); 


    //we got from user the dest of edge
    int num_from_user = scanf("%d", &input_from_user);
    
    while (num_from_user != EOF  && num_from_user != 0){  
        edge * new_edge = NULL;
        if((new_edge = (edge*) malloc (sizeof(edge) )) == NULL)
        {
            printf ("Not enough memory4, exit program\n");
            if (arr_vert1 != NULL)
            {
                free_all (arr_vert1);
            }
            exit(-1);
        }
        *last_edge = new_edge;
        (*last_edge)->dest_vert = NULL;
        (*last_edge)->next = NULL;
        (*last_edge)->weight = 0;

        vert * search_dest = arr_vert1;
        while (search_dest != NULL){
            
            if (search_dest->value == input_from_user){
                break;
            }
            else{
                search_dest = search_dest->nextV;
            }
        }
        (*last_edge)->dest_vert = search_dest;

        //the weight of the edge
        scanf("%d", &input_from_user);
        (*last_edge)->weight = input_from_user;
        last_edge = &((*last_edge)->next);

        //input could be 'n' or int anyaway it goes to the while loop
        num_from_user = scanf("%d", &input_from_user);

    }
    arr_vert = arr_vert1;
}

//what we want to delete
void delete_vert (vert ** arr){
    int input = 0;
    scanf ("%d", &input);
    delete (arr, input);
}

void delete (vert ** arr, int input){

    //3 pointers to the verts
    vert * vert1 = *arr;
    vert * vert2 = *arr;
    vert * vert3 = *arr;

    //2 pointers to the edges
    edge ** edge1 = &((*arr)->next_edge);
    edge * edge2 = (*arr)->next_edge;

    //flags
    int flag_edge = 1;
    int flag_vert = 1;
    int flag_found = 1;
    int flag_first = 0;
    
    //if the delete is for the first vert
    if (vert2->value == input){
        flag_first = 1;
    }
    
    while (vert3 != NULL){
        if (vert3->value != input){
            while (edge2 != NULL)
            {
                if (!flag_edge){
                    edge1 = &((*edge1)->next); 
                       
                }
                flag_edge = 0;
                
                if (edge2->dest_vert->value == input){
                    edge2 = edge2->next;
                    free((*edge1));
                    (*edge1) = (edge2);
                    
                }
                else{
                    edge2 = edge2->next;
                }
            }

            //if we found the prev time the vert so increase only vert 3. also, in the first time increase only vert2 & vert3
            if(flag_found){
                if(!flag_vert){
                    vert1 = vert1->nextV;
                }
                vert2 = vert2->nextV;
            }
            vert3 = vert3->nextV;
            flag_vert = 0;
            if (vert3 != NULL){
                edge1 = &(vert3->next_edge);
                edge2 = vert3->next_edge;
            }
            flag_edge = 1;   
        }

        //if we found this time the vert
        else{
            flag_found = 0;
            vert3 = vert3->nextV;
            flag_vert = 0;
            if (vert3 != NULL){
                edge1 = &(vert3->next_edge);
                edge2 = vert3->next_edge;
            }
            flag_edge = 1;
        }
    }

    //if the delete is for the first vert
    if(flag_first) {
        *arr = (*arr)->nextV;
    }
    edge1 = &(vert2->next_edge);
    edge2 = NULL; 
    while ((*edge1) !=NULL)
    {
        edge2 = (*edge1)->next;
        free ((*edge1));
        (*edge1) = edge2;
        if ((*edge1) !=NULL){   
            edge2 = edge2->next;
        }
    }
    vert2->next_edge = NULL;

    vert3 = vert2->nextV;
    vert2->nextV = NULL;
    free(vert2);
    vert1->nextV = vert3;

}

int shortest_path (vert * head, int src, int des){
    vert * value = head;
    vert * inf = head;
    vert * dest = head;
    edge * src_edge = NULL;
    edge * path = NULL;
    int find_src = 0;
    int find_des = 0;

    while (inf != NULL){
        if (inf->value == src){
            find_src = 1;
            inf->dist =0;
        }
        else{
            inf->dist = MAX_DIST;
        }
        if (inf->value == des){
            find_des = 1;
        }
        if (!find_des){
            dest = dest->nextV;
        }
        if (!find_src){
            value = value->nextV;
        }
        inf = inf->nextV;
    }

    src_edge = value->next_edge;
    path = value->next_edge;

    inf = value;
    while (path != NULL){
        if (value->dist + path->weight < path->dest_vert->dist){
            path->dest_vert->dist = value->dist + path->weight;
        }
        path = path->next;
    }

    while (src_edge != NULL){
        path = src_edge->dest_vert->next_edge;
        inf = src_edge->dest_vert;
        while (path != NULL){
            if (inf->dist + path->weight < path->dest_vert->dist){
                path->dest_vert->dist = inf->dist + path->weight;
            }
            path = path->next;
        }
        src_edge = src_edge->next;
    }
    if (dest->dist == MAX_DIST){
        return -1;
    }
    return (dest->dist);

}

void swap (int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr [j];
    arr[j] = temp;
}

int find_d (int * min_d, int * arr_of_k, int k, vert * head){
    int sum = 0;
    int there_is_path = 0;

    for (int i = 0; i < k-1; i++){
        there_is_path = 0;
        there_is_path = shortest_path (head, arr_of_k[i], arr_of_k[i+1]);
        if (there_is_path == -1)
        {
            return *min_d;
        }
        sum += there_is_path;        
    }
    if (sum < *min_d){
        *min_d = sum;
    }
    return *min_d;
}

void permutation(int * arr_of_k, int k, int place, int * min_d, vert *head){
    if (place == k-1){
        *min_d = find_d (min_d, arr_of_k, k, head);
        return;
    }

    for(int i = place; i < k; i++){
        swap (arr_of_k, i, place);
        permutation (arr_of_k, k, place+1, min_d, head);
        swap (arr_of_k, i, place);
    }

}


int main(){
    vert * head = NULL;
    char n = '0';
    int scan = scanf("%c", &n);
    int flag = 1;
    int flag_break = 1;
    while (scan != 0 && flag_break){
        switch(n){
            case 'A':
                n = new_graph(&head);
                // printf("A:\n");
                // check (head);
                // printf ("\n");
                flag = 0;
                break;
            case 'B':
                new_vert(head);
                // printf("B:\n");
                // check (head);
                // printf ("\n");
                scan = 0;
                break;
            case 'D':
                delete_vert(&head);
                // printf("D:\n");
                // check (head);
                // printf ("\n");
                break;
            case 'S':
                int src = 0;
                int des = 0;
                scanf ("%d", &src);
                scanf ("%d", &des);
                int Dijsktra = shortest_path (head, src, des);
                printf ("Dijsktra shortest path: %d \n", Dijsktra);
            case ' ':
                break;
            case 'T':
                int k = 0;
                int max = MAX_DIST;
                scanf ("%d", &k);
                int * arr_of_k = NULL;
                if ((arr_of_k = (int*) malloc (sizeof(int) * k)) == NULL){
                    printf ("Not enough memory5, exit program\n");
                    if (head != NULL)
                    {
                        free_all (head);
                    }
                    exit(-1);
                }
                for (int i= 0; i<k; i++){
                    scanf("%d",&(arr_of_k[i]));
                }
                permutation (arr_of_k, k, 0, &max, head);
                if (max == MAX_DIST){
                    max = -1;
                }
                printf ("TSP shortest path: %d \n", max);
                free(arr_of_k);
                break;
            default:
                flag_break = 0;
        }
        if (flag){
            scan = scanf("%c", &n);
        }
        flag = 1;
    }
    if (head != NULL)
    {
        free_all (head);
    }
    
    return 0;
}