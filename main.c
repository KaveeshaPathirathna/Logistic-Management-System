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
void removeCity();
void renameCity();


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
void removeCity()
{
if (cityCount==0)
{
    printf("No cities available ! \n");
    return ;

}
displayCity();
char cityName [MAX_NAME];
printf("Enter city name to remove : ");
scanf("%s" , cityName);

int index = findCityIndex (cityName);
if (index == -1)
{
    printf("City not found ! \n");
    return ;
}
//remove city and shift array

for (int i = index; i < cityCount - 1 ; i++)
{
    strcpy (city[i], city[i+1]);
    //shift distance matrix

    for (int j = 0 ; j < cityCount ; j++)
    {
        distances[i][j] = distances[i +1][j];
        distances[j][i] = distances [j][i + 1];
    }
}

cityCount--;
printf("City '%s' removed successfully!\n " , cityName);

}

void renameCity()
{
    if (cityCount == 0)
    {
        printf("No cities available ! \n");
        return ;
    }

    displayCity();
    char oldName[MAX_NAME], newName[MAX_NAME];
    printf("Enter current city name : ");
    scanf("%s", oldName);

    int index = findCityIndex(oldName);
    if(index == -1)
    {
        printf("City not found !\n");
        return ;
    }
      printf("Enter new city name : ");
      scanf("%s", newName);


        for (int i = 0 ; i < cityCount ; i++)
        {
            if(i != index && strcmp (city[i], newName)== 0 )
            {
                printf("City name already exists!\n");
                return ;
            }
        }
    strcpy(city[index], newName);
    printf("City renamed successfully!\n");
    }
