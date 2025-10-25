#include <stdio.h>
#include <stdlib.h>

int main()
{
    
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