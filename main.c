#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_CITY 30
#define MAX_DELIVERY 50
#define MAX_NAME 50
#define FUEL_PRICE 310.0

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
int distances[MAX_CITY][MAX_CITY];
vehicle vehicles[3];
int cityCount = 0;
int deliveryCount = 0;
Delivery deliveries[MAX_DELIVERY];


//phototyoes
void initializeSystem();
void mainMenu();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequest();
void findLeastCostRoute();
void reports();
void operations();
void saveData();
void loadData();


void addCity ();
void removeCity();
void renameCity();
void displayCity();
void updateDistance();
void displayDistanceMatrix();
int findCityIndex(char cityName[]);
void calculateDeliveries(int source, int destination, float weight, int vehicleType);
void displayDeliveries(int deliveryIndex);
void bruteForceRoute(int start, int end, float weight, int vehicleType);




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
            distances[i][j] = (i == j) ? 0 : -1;
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
    int distance;

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
    scanf("%d", &distance);

    if(distance < 0) {
        printf("Distance cannot be negative!\n");
        return;
    }

    distances[index1][index2] = distance;
    distances[index2][index1] = distance;
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
            if(distances[i][j] == -1) {
                printf("%-15s", "N/A");
            } else {
                printf("%-15d", distances[i][j]);
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

void deliveryRequest()
{
    if(cityCount < 2) {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    if(deliveryCount >= MAX_DELIVERY) {
        printf("Maximum delivery limit reached!\n");
        return;
    }

    displayCity();
    char source[MAX_NAME], destination[MAX_NAME];
    float weight;
    int vehicleChoice;

    printf("Enter source city: ");
    scanf("%s", source);
    printf("Enter destination city: ");
    scanf("%s", destination);

    int sourceIndex = findCityIndex(source);
    int destIndex = findCityIndex(destination);

    if(sourceIndex == -1 || destIndex == -1) {
        printf("One or both cities not found!\n");
        return;
    }

    if(sourceIndex == destIndex) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("Enter package weight (kg): ");
    scanf("%f", &weight);

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }

    vehicleManagement();
    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleChoice);

    if(vehicleChoice < 1 || vehicleChoice > 3) {
        printf("Invalid vehicle choice!\n");
        return;
    }

    // Check weight capacity
    if(weight > vehicles[vehicleChoice - 1].capacity) {
        printf("Weight exceeds vehicle capacity! Maximum: %d kg\n", vehicles[vehicleChoice - 1].capacity);
        return;
    }

    // Check if direct route exists
    if(distances[sourceIndex][destIndex] == -1) {
        printf("No direct route exists between these cities!\n");
        return;
    }

    calculateDeliveries(sourceIndex, destIndex, weight, vehicleChoice - 1);

}
void calculateDeliveries(int source, int destination, float weight, int vehicle_type) {
    Delivery *delivery = &deliveries[deliveryCount];

    delivery->id = deliveryCount + 1;
    strcpy(delivery->source, city[source]);
    strcpy(delivery->destination, city[destination]);
    delivery->weight = weight;
    strcpy(delivery->vehicleType, vehicles[vehicle_type].type);
    delivery->distance = distances[source][destination];

    // Calculate costs
    float D = delivery->distance;
    float R = vehicles[vehicle_type].ratePerKm;
    float W = weight;
    float S = vehicles[vehicle_type].avgSpeed;
    float E = vehicles[vehicle_type].fuelEfficiency;

    // Base delivery cost
    delivery->baseCost = D * R * (1 + W / 10000.0);

    // Fuel calculations
    delivery->fuelUsed = D / E;
    delivery->fuelCost = delivery->fuelUsed * FUEL_PRICE;

    // Operational cost
    delivery->operationalCost = delivery->baseCost + delivery->fuelCost;

    // Profit and customer charge
    delivery->profit = delivery->baseCost * 0.25;
    delivery->customerCharge = delivery->operationalCost + delivery->profit;

    // Delivery time
    delivery->deliveryTime = D / S;

    delivery->completed = 1;

    displayDeliveries(deliveryCount);
    deliveryCount++;
}




void displayDeliveries(int deliveryIndex) {
    Delivery *delivery = &deliveries[deliveryIndex];

    printf("\n==============================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("==============================================================\n");
    printf("From: %s\n", delivery->source);
    printf("To: %s\n", delivery->destination);
    printf("Distance: %.2f km\n", delivery->distance);
    printf("Vehicle: %s\n", delivery->vehicleType);
    printf("Weight: %.2f kg\n", delivery->weight);
    printf("==============================================================\n");
    printf("Base Cost: %.2f � %.2f � (1 + %.2f/10000) = %.2f LKR\n",
           delivery->distance, vehicles[findCityIndex(delivery->source) == 0 ? 0 : 1].ratePerKm,
           delivery->weight, delivery->baseCost);
    printf("Fuel Used: %.2f L\n", delivery->fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", delivery->fuelCost);
    printf("Operational Cost: %.2f LKR\n", delivery->operationalCost);
    printf("Profit: %.2f LKR\n", delivery->profit);
    printf("Customer Charge: %.2f LKR\n", delivery->customerCharge);
    printf("Estimated Time: %.2f hours\n", delivery->deliveryTime);
    printf("==============================================================\n");
}

void findLeastCostRoute() {
    if(cityCount < 2) {
        printf("Need at least 2 cities!\n");
        return;
    }

    displayCity();
    char source[MAX_NAME], destination[MAX_NAME];
    float weight;
    int vehicle_choice;

    printf("Enter source city: ");
    scanf("%s", source);
    printf("Enter destination city: ");
    scanf("%s", destination);

    int source_index = findCityIndex(source);
    int dest_index = findCityIndex(destination);

    if(source_index == -1 || dest_index == -1) {
        printf("One or both cities not found!\n");
        return;
    }

    if(source_index == dest_index) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("Enter package weight (kg): ");
    scanf("%f", &weight);

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }

    vehicleManagement();
    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicle_choice);

    if(vehicle_choice < 1 || vehicle_choice > 3) {
        printf("Invalid vehicle choice!\n");
        return;
    }

    bruteForceRoute(source_index, dest_index, weight, vehicle_choice - 1);
}
void bruteForceRoute(int start, int end, float weight, int vehicle_type) {


    printf("\n--- Route Optimization ---\n");
    printf("Finding best route from %s to %s...\n", city[start], city[end]);

    // Check direct route first
    if(distances[start][end] != -1) {
        printf("\nDirect Route:\n");
        printf("%s -> %s: %d km\n", city[start], city[end], distances[start][end]);

        // Calculate cost for direct route
        float D = distances[start][end];
        float R = vehicles[vehicle_type].ratePerKm;
        float cost = D * R * (1 + weight / 10000.0);
        printf("Estimated Cost: %.2f LKR\n", cost);
    }

    // Check for one intermediate city
    printf("\nChecking routes with one intermediate city...\n");
    float min_cost = -1;
    int bes_inter = -1;

    for(int i = 0; i < cityCount; i++) {
        if(i != start && i != end && distances[start][i] != -1 && distances[i][end] != -1) {
            float total_dist = distances[start][i] + distances[i][end];
            float cost = total_dist * vehicles[vehicle_type].ratePerKm * (1 + weight / 10000.0);

            printf("%s -> %s -> %s: %.2f km, Cost: %.2f LKR\n",
                   city[start], city[i], city[end], total_dist, cost);

            if(min_cost == -1 || cost < min_cost) {
                min_cost = cost;
                bes_inter = i;
            }
        }
    }

    if(bes_inter != -1) {
        printf("\nBest route with one intermediate city:\n");
        printf("%s -> %s -> %s\n", city[start], city[bes_inter], city[end]);
        printf("Total Distance: %.2f km\n", distances[start][bes_inter] + distances[bes_inter][end]);
        printf("Estimated Cost: %.2f LKR\n", min_cost);
    }
}

void reports() {
    if(deliveryCount == 0) {
        printf("No deliveries completed yet!\n");
        return;
    }

    printf("\n--- PERFORMANCE REPORTS ---\n");

    // Total deliveries
    printf("Total Deliveries Completed: %d\n", deliveryCount);

    // Total distance covered
    float tot_distance = 0;
    float tot_revenue = 0;
    float tot_profit = 0;
    float tot_time = 0;
    float max_distance = 0;
    float min_distance = -1;

    for(int i = 0; i < deliveryCount; i++) {
        tot_distance += deliveries[i].distance;
        tot_revenue += deliveries[i].customerCharge;
        tot_profit += deliveries[i].profit;
        tot_time += deliveries[i].deliveryTime;

        if(deliveries[i].distance > max_distance) {
            max_distance = deliveries[i].distance;
        }

        if(min_distance == -1 || deliveries[i].distance < min_distance) {
            min_distance = deliveries[i].distance;
        }
    }

    printf("Total Distance Covered: %.2f km\n", tot_distance);
    printf("Average Delivery Time: %.2f hours\n", tot_time / deliveryCount);
    printf("Total Revenue: %.2f LKR\n", tot_revenue);
    printf("Total Profit: %.2f LKR\n", tot_profit);
    printf("Longest Route: %.2f km\n", max_distance);
    printf("Shortest Route: %.2f km\n", min_distance);
}


void operations() {
    int choice;
    do {
        printf("\n--- File Operations ---\n");
        printf("1. Save Data to Files\n");
        printf("2. Load Data from Files\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: saveData(); break;
            case 2: loadData(); break;
            case 3: break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 3);
}





















