#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_CITY 30
#define MAX_DELIVERY 50
#define MAX_NAME 50


// vehicle structure
typedef struct{
char type[10];
int capacity;
float avgSpeed;
float ratePerKm;
float fuelEfficiency;
}vehicle;

// delivery strucutre
typedef struct {
    int id;
    char source[MAX_NAME];
    char destination[MAX_NAME];
    float weight;
    char vehicleType[10];
    float distance;
    float baseCost;
    float fuelUsed;
    float fuelCost;
    float operationalCost;
    float profit;
    float customerCharge;
    float deliveryTime;
    int completed;
} Delivery;


//global variables
char city[MAX_CITY][MAX_NAME];
int distance[MAX_CITY][MAX_CITY];
vehicle vehicles[3];
int cityCount = 0;
int deliveryCount = 0;


//phototyoes
void initializeSystem();
void mainMenu();
void cityManagement();
void distanceManagement();
void vehicleManagement();


void addCity ();
void removeCity();
void renameCity();
void displayCity();
void updateDistance();
void displayDistanceMatrix();
int findCityIndex(char cityName[]);

int main()
{

}

void initializeSystem() {
    // Initialize vehicles
    strcpy(vehicles[0].type, "Van");
    vehicles[0].capacity = 1000;
    vehicles[0].ratePerKm = 30.0;
    vehicles[0].avgSpeed = 60.0;
    vehicles[0].fuelEfficiency = 12.0;

    strcpy(vehicles[1].type, "Truck");
    vehicles[1].capacity = 5000;
    vehicles[1].ratePerKm = 40.0;
    vehicles[1].avgSpeed = 50.0;
    vehicles[1].fuelEfficiency = 6.0;

    strcpy(vehicles[2].type, "Lorry");
    vehicles[2].capacity = 10000;
    vehicles[2].ratePerKm = 80.0;
    vehicles[2].avgSpeed = 45.0;
    vehicles[2].fuelEfficiency = 4.0;

    // Initialize distance matrix with -1 (unset distances)
    for(int i = 0; i < MAX_CITY; i++) {
        for(int j = 0; j < MAX_CITY; j++) {
            distance[i][j] = (i == j) ? 0 : -1;
        }
    }
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
        {
            case 1: addCity(); break;
            case 2: removeCity(); break;
            case 3: renameCity(); break;
            case 4: displayCity(); break;
            case 5: break;

            default :printf("Invalid choice!\n");
        }

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
        distance[i][j] = distance[i +1][j];
        distance[j][i] = distance [j][i + 1];
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
void displayCity()
 {
    if(cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n--- Available Cities ---\n");
    for(int i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i + 1, city[i]);
    }
}


int findCityIndex (char cityName[])
{
    for(int i = 0; i < cityCount; i++) {
        if(strcmp(city[i], cityName) == 0) {
            return i;
        }
    }
    return -1;
}


void distanceManagement() {
    int choice;
    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Update Distance\n");
        printf("2. Display Distance Matrix\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: updateDistance(); break;
            case 2: displayDistanceMatrix(); break;
            case 3: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 3);
}
void updateDistance() {
    if(cityCount < 2) {
        printf("Need at least 2 cities to set distances!\n");
        return;
    }

    displayCity();
    char city1[MAX_NAME], city2[MAX_NAME];
    int distances;

    printf("Enter first city: ");
    scanf("%s", city1);
    printf("Enter second city: ");
    scanf("%s", city2);

    int index1 = findCityIndex(city1);
    int index2 = findCityIndex(city2);

    if(index1 == -1 || index2 == -1) {
        printf("One or both cities not found!\n");
        return;
    }

    if(index1 == index2) {
        printf("Distance from city to itself is always 0!\n");
        return;
    }

    printf("Enter distance between %s and %s (km): ", city1, city2);
    scanf("%d", &distances);

    if(distances < 0) {
        printf("Distance cannot be negative!\n");
        return;
    }

    distance[index1][index2] = distances;
    distance[index2][index1] = distances;
    printf("Distance updated successfully!\n");
}

void displayDistanceMatrix() {
    if(cityCount == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n--- Distance Matrix (km) ---\n");
    printf("%-15s", "");
    for(int i = 0; i < cityCount; i++) {
        printf("%-15s", city[i]);
    }
    printf("\n");

    for(int i = 0; i < cityCount; i++) {
        printf("%-15s", city[i]);
        for(int j = 0; j < cityCount; j++) {
            if(distance[i][j] == -1) {
                printf("%-15s", "N/A");
            } else {
                printf("%-15d", distance[i][j]);
            }
        }
        printf("\n");
    }
}

void vehicleManagement()
{
    printf("\n--- Vehicle Information ---\n");
    printf("%-10s %-12s %-15s %-12s %-15s\n",
           "Type", "Capacity(kg)", "Rate/km(LKR)", "Speed(km/h)", "Efficiency(km/l)");
    printf("----------------------------------------------------------------\n");

    for(int i = 0; i < 3; i++) {
        printf("%-10s %-12d %-15.2f %-12.2f %-15.2f\n",
               vehicles[i].type, vehicles[i].capacity, vehicles[i].ratePerKm,
               vehicles[i].avgSpeed, vehicles[i].fuelEfficiency);
    }
}










