#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct Definings
struct table{
    int tableNumber;
    int status;
    int capacity;
    char waiterName[50];
    double bill;

    struct table *nextPtr;
};

struct order{
    int orderID;
    int quantity;
    int menuItemID;
    int isCompleted;

    struct order *nextPtr;
};

//Global front and rear defining
struct table *tableFront = NULL;
struct table *tableRear = NULL;

struct order *orderFront = NULL;
struct order *orderRear = NULL;

//Global Table Count Veriable
int countTable=0;

//Functions 
void displayMenu(FILE *menuFile){
    //Veriable Declerations
    char sentence[100];
    
    printf("----------MENU----------\n");
    
    
    while (fgets(sentence,100,menuFile)!=NULL){
        printf("%s\n",sentence);
    }
}

void createOneDesk(int tableNumber,int capacity,char waiterName[]){
    
    if(tableFront==NULL&&tableRear==NULL){
        struct table *newNode = (struct table *)malloc(sizeof(struct table));
        newNode->capacity = capacity;
        if(newNode->capacity>0)
            newNode->status = 0;
        else
            newNode->status = 1;
        newNode->tableNumber = tableNumber;
        strcpy(newNode->waiterName,waiterName);
        newNode->bill = 0;

        newNode->nextPtr = NULL;
        tableFront=tableRear=newNode;
    }else {
        struct table* newNode = (struct table*)malloc(sizeof(struct table));
        newNode->capacity = capacity;
        if(newNode->capacity>0)
            newNode->status = 0;
        else
            newNode->status = 1;
        newNode->tableNumber = tableNumber;
        strcpy(newNode->waiterName, waiterName);
        newNode->bill = 0;

        newNode->nextPtr = NULL;
        tableRear->nextPtr = newNode;
        tableRear = newNode;
    }
}

void createTable(int size){

    //Veriable Declerations
    int i;
    int capacity;
    char waiterName[50];

    for(i=0;i<size;i++){
        countTable++;
        printf("Please enter %d. table's capacity: ",countTable);
        scanf("%d",&capacity);

        printf("Please enter %d. table's waiter's: ",countTable);
        scanf("%s",waiterName);
        createOneDesk(countTable,capacity,waiterName);
    }
}

void displayTableInfo(){
    //Veriable Decleration
    struct table *index = (struct table *)malloc(sizeof(struct table));
    char isAvailable[20];
    int countAvailable=0;
    int countNotAvailable=0;

    index=tableFront;
    while (index!=NULL){
        if(index->status==1){
            strcpy(isAvailable,"Desk is empty.");
            countAvailable++;
        }else{
            strcpy(isAvailable,"Desk is full.");
            countNotAvailable++;
        }

        printf("%d. Desk -> %s\tWaiter: %s\tCapacity: %d\tBill: %.2lf\n",index->tableNumber,isAvailable,index->waiterName,index->capacity,index->bill);

        index = index->nextPtr;
    }

    printf("Total Available Table: %d\nTotal Not Available Table: %d\n",countAvailable,countNotAvailable);
}

void changeTableStatue(int tableNumber,int tableStatue){
    struct table *index = (struct table *)malloc(sizeof(struct table));
    index=tableFront;

    while(index->tableNumber!=tableNumber){
        index = index->nextPtr;
    }
    index->status = tableStatue;

    printf("The table statue has been changed successfully.\n");
}

double calculateBill(int tableNumber){
    
    struct table *index = (struct table *)malloc(sizeof(struct table));
    index=tableFront;

    while(index->tableNumber!=tableNumber){
        index = index->nextPtr;
    }

    return index->bill;
}

void takeOrder(int tableNumber, int menuItemID, int quantity, double *totalEarned, FILE* menuFile) {
    
    // Variable Declaration
    struct table* index = tableFront;  
    int id;
    char name[20],sentence[100];
    double price;

    while (index != NULL && index->tableNumber != tableNumber) {
        index = index->nextPtr;
    }

    if (index == NULL) {
        printf("Table Number %d does not exist.\n", tableNumber);
        return;
    }

    rewind(menuFile);  

    while (fgets(sentence,100,menuFile)!=NULL) {
        sscanf(sentence,"%d%s%lf",&id,name,&price);
        if(id == menuItemID){
            break;
        }
        
    }

    if (id != menuItemID) {
        printf("Menu Item ID %d does not exist.\n", menuItemID);
        return;
    }

    struct order* newOrder = (struct order*)malloc(sizeof(struct order));
    newOrder->menuItemID = menuItemID;
    newOrder->isCompleted = 0;
    newOrder->quantity = quantity;

    *totalEarned += price * quantity;

    if (orderFront == NULL && orderRear == NULL) {
        newOrder->orderID = 1;
        newOrder->nextPtr = NULL;
        orderFront = orderRear = newOrder;
    } else {
        newOrder->orderID = orderRear->orderID + 1;
        newOrder->nextPtr = NULL;
        orderRear->nextPtr = newOrder;
        orderRear = newOrder;
    }

    index->bill += price * quantity;

    printf("Order taken successfully.\n");
}

void displayOrders(){
    //Veriable Decleration
    struct order *index = orderFront;
    char isCompleted[20];

    if(index==NULL){
        printf("There is no order.\n");
        return;
    }else
        while (index!=NULL){
            if(index->isCompleted==0)
                strcpy(isCompleted,"Not Completed");
            else
                strcpy(isCompleted,"Completed");
            printf("%d. order\tQuantity: %d\tItem ID: %d\tStatue: %s\n",index->orderID,index->quantity,index->menuItemID,isCompleted);
            index = index->nextPtr;
        }
    
}

void markOrderAsCompleted(int orderID){
    struct order *index = orderFront;

    if(index==NULL){
        printf("The order list is empty.\n");
        return;
    }

    while (index->orderID!=orderID){
        index = index->nextPtr;
    }

    index->isCompleted = 1;

    printf("%d. order(Item ID %d) has been completed.\n",orderID,index->menuItemID);
}

void tableCheque(int numTable){

    struct table *index = tableFront;
    struct table *prev = NULL;

    if(index==NULL){
        printf("The restaurant is empty.\n");
        return;
    }

    while (index!=NULL){
        if(index->tableNumber==numTable)
            break;
        prev = index;
        index = index->nextPtr;
    }

    prev->nextPtr = NULL;
    prev->nextPtr = index->nextPtr;
    index->nextPtr = NULL;
    free(index);

    printf("Table cheque successfully taken.\n");
}








