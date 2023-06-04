#ifndef TABLE_H
#define TABLE_H

void createTable(int size);
void createOneDesk(int tableNumber,int capacity,char waiterName[]);
void displayTableInfo();
void changeTableStatue(int tableNumber,int tableStatue);
double calculateBill(int tableNumber);
void takeOrder(int tableNumber, int menuItemID, int quantity,double *totalEarned,FILE *menuFile);
void displayMenu(FILE *menuFile);
void displayOrders();
void markOrderAsCompleted(int orderID);
void tableCheque(int numTable);

#endif 