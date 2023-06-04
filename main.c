#include <stdio.h>
//#include "menu.h"
#include "table.h"
#include <string.h>
#include <stdlib.h>

int main(){

    //Veriable Declerations
    int numTable,opOption,employeeOp,tableStatue,isZReported=0,itemID,quantity;
    char clearString[10];
    double bill,totalEarned=0,totalGain;
    
    //File openings
    FILE *menuFile = fopen("menu.txt","r+");

    //Controlling file
    if(menuFile==NULL){
        printf("There is an error while accessing the menu database.\n");
        return 1;
    }
    
    printf("What is your operating system type?\n1-Windows\n2-Unix Based(Linux,Mac)\n");
    scanf("%d",&opOption);
    if(opOption==1){
        strcpy(clearString,"cls");
    }else{
        strcpy(clearString,"clear");
    }
    system(clearString);

    printf("Please enter the number of desks: ");
    scanf("%d",&numTable);
    createTable(numTable);

    while (1){
        
        system(clearString);
        printf("Welcome to Restaurant's Waiter Control Center!\n"
        "1-Display Menu\n"
        "2-Take Order\n"
        "3-Mark Order as Completed\n"
        "4-Show All Orders\n"
        "5-Calculate Bill\n"
        "6-Table Cheque\n"
        "7-Add New Table\n"
        "8-Update Table Status\n"
        "9-Show Table Status\n"
        "10-Z Report\n"
        "11-Exit\n"
        "SELECT: ");
        scanf("%d",&employeeOp);

        switch (employeeOp){
            
            case 1:
                system(clearString);
                displayMenu(menuFile);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;
            
            case 2:
                system(clearString);
                printf("Please enter the number of the table: ");
                scanf("%d",&numTable);
                printf("Please enter the item ID: ");
                scanf("%d",&itemID);
                printf("Please enter the item quantity: ");
                scanf("%d",&quantity);
                takeOrder(numTable,itemID,quantity,&totalEarned,menuFile);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;
            
            case 3:
                system(clearString);
                printf("Please enter the order ID: ");
                scanf("%d",&itemID);
                markOrderAsCompleted(itemID);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;

            case 4:
                system(clearString);
                displayOrders();
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;


            case 5:
                system(clearString);
                printf("Please enter the number of the table: ");
                scanf("%d",&numTable);
                bill = calculateBill(numTable);
                printf("%d. Desk's Bill: %.2lf\n",numTable,bill);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;
            
            case 6:
                system(clearString);
                printf("Please enter the number of the table: ");
                scanf("%d",&numTable);
                tableCheque(numTable);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;

            case 7:
                system(clearString);
                printf("Please enter the number of desks: ");
                scanf("%d",&numTable);
                createTable(numTable);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;

            case 8:
                system(clearString);
                printf("Please enter the number of the table: ");
                scanf("%d",&numTable);
                
                printf("Please enter the statue of the table(1->Empty 2->Full): ");
                scanf("%d",&tableStatue);
                changeTableStatue(numTable,tableStatue);
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;
            
            case 9:
                system(clearString);
                displayTableInfo();
                printf("Do you want to continue?(Yes->1)\n"
                "SELECT: ");
                scanf("%d",&opOption);
                if(opOption!=1)
                    return 1;
                break;
            
            case 10:
                system(clearString);
                isZReported=1;
                printf("End of the day!\nTotal Earning %.2lf\n",totalEarned);

            case 11:
                system(clearString);
                if(isZReported!=1){
                    printf("Do you want to take Z Report?(Yes->1) ");
                    scanf("%d",&opOption);
                    if(opOption==1){
                        isZReported=1;
                        printf("End of the day!\nTotal Earning %.2lf\n",totalEarned);
                    }
                }
                printf("The program ends.\n");
                return 1;
            
            default:
                printf("Invalid operation.\n");
                break;
        }
    }
    
    //File closings
    fclose(menuFile);

    return 0;
}