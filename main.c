#include <stdio.h>
#include <stdlib.h>


#define MAX_CITY 30
#define MAX_DELIVERY 50
#define MAX_NAME 50



typedef struct{
char type[10];
int capacity;
float avgSpeed;
float ratePerKm;
float fuelEfficiency;
}vehicle;




char city[MAX_CITY][MAX_NAME];
int distances[MAX_CITY][MAX_CITY];
vehicle vehicles[3];
int cityCount = 0;
int deliveryCount = 0;

void mainMenu();
void cityManagement();


void addCity ();


int main()
{

}
void mainMenu()
{
    printf("\n=======================================\n");
    printf("     LOGISTICS MANAGEMENT SYSTEM\n");
    printf("\n=======================================\n");
    printf("1. City Management\n");



}

void cityManagement()
{
    int choice;

    do {
        printf("\n--- CITY MANAGMENT---");
        printf("1. Add City\n");
        printf("2. Remove City\n");
        printf("3. Rename City\n");
        printf("4. Display City\n");
        printf("5. back to main \n");
        printf("Enter your choice : ");
        scanf("%d",&choice );

        switch(choice)
    case 1 :
                break ;

    case 2 :
                break ;

    case 3 :
                break ;

    case 4 :
                break ;

    case 5 :
                break ;

    default :
        printf("Invalid choice!\n");


    }
    while (choice !=5);
}


void addCity ()
{
    if (cityCount >= MAX_CITY)
    {
        printf("you can't added city\n");
        return;
    }
    char cityName[MAX_NAME];
    printf("Enter the city name : \n");
    scanf("%s", cityName);

    //check if city already exists

    for (int i = 0; i < cityCount ; i++)
    {
        if(strcmp(city[i], cityName)==0)
        {
            printf("City already added");
        }
    }

    strcpy (city[cityCount],cityName);
    cityCount++;
    printf("City '%s' added successfully!\n", cityName);
}
