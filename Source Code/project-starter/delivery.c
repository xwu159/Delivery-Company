#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "delivery.h"
#include "mapping.h"

// Define constant integer values for error codes
#define NO_ERROR 0
#define INVALID_SIZE 1
#define INVALID_WEIGHT 2
#define INVALID_DESTINATION 3
#define INVALID_DESTINATION_MAP 4

// Define error messages array
char* error_messages[] = {
    "Thank you for shipping with Seneca!\n",
    "Invalid size\n",
    "Invalid weight (must be 1-1000 Kg.)\n",
    "Invalid destination\n",
    "Invalid destination\n"
};

int isValidPoint(const struct Point des) {
    int ret = 0;    // flag for invalid point
    if ((des.row >= 0 && des.row < MAP_ROWS) && (des.col >= 0 && des.col < MAP_COLS)) {
        ret = 1;    // change return value to 'true' when point is valid
    }
    return ret;
}

int isValidWeight(int weight) {
    int ret = 0;    // flag for invalid weight
    if (weight > 0 && weight <= MAX_WEIGHT) {
        ret = 1;    // change return value to 'true' when weight is valid
    }
    return ret;
}

int isValidSize(double size) {
    int ret = 0;    // flag for invalid size
    if (size == 0.25 || size == 0.5 || size == 1) {
        ret = 1;    // change return value to 'true' when size is valid
    }
    return ret;
}


int validate(double size, int weight, struct Point des)
{
    struct Map map = populateMap();
    struct Map* tempMap = &map;
    int ret = 1;
    int min = 0; int max = 26;

    if (weight == 0 && size == 0 && des.row == 'x')
    {
        printf("%s", error_messages[NO_ERROR]);
        ret = 0;
    }
    else if (des.row == NULL || des.col == NULL || des.row > max || des.col > max)
        des.row = des.col = -1;

    if (ret != 0)
    {
        if (isValidWeight(weight)==0)
        {
            ret = -2;
            printf("%s", error_messages[INVALID_WEIGHT]);
        }
        else if (isValidSize(size) == 0)
        {
            ret = -1;
            printf("%s", error_messages[INVALID_SIZE]);
        }
        else if (isValidPoint(des) == 0)
        {
            ret = -3;
            printf("%s", error_messages[INVALID_DESTINATION]);

        }
        else if (tempMap->squares[(int)des.row][(int)des.col] == 0)
        {
            ret = -3;
            printf("%s", error_messages[INVALID_DESTINATION_MAP]);
        }
    }
    return ret;
}

char findTruckForShipment(struct Shipment shipment)
{
    int size = 0;
    int result = -1;
    struct Route routes[MAX_ROUTES] = { 0 };
    struct Route blueRoute = getBlueRoute();
    struct Route greenRoute = getGreenRoute();
    struct Route yellowRoute = getYellowRoute();
    trucks[0].route = &blueRoute;
    trucks[1].route = &greenRoute;
    trucks[2].route = &yellowRoute;

    if ((trucks[0].totalWeight + shipment.weight <= MAX_WEIGHT) && (trucks[0].totalBoxSize + shipment.vol <= MAX_SIZE)) {
        allPossibleRoute(shipment, trucks[0], baseMap, &routes, &size);
    }
    if ((trucks[1].totalWeight + shipment.weight <= MAX_WEIGHT) && (trucks[1].totalBoxSize + shipment.vol <= MAX_SIZE)) {
        allPossibleRoute(shipment, trucks[1], baseMap, &routes, &size);
    }
    if ((trucks[2].totalWeight + shipment.weight <= MAX_WEIGHT) && (trucks[2].totalBoxSize + shipment.vol <= MAX_SIZE)) {
        allPossibleRoute(shipment, trucks[2], baseMap, &routes, &size);
    }


        

    int bestRoute = findBestRoute(routes, size, shipment);
    printResult(routes[bestRoute], shipment);

    if (routes[bestRoute].routeSymbol == 2)
    {
        trucks[0].totalBoxSize += shipment.vol;
        trucks[0].totalWeight += shipment.weight;
        result = 2;
    }
    else if (routes[bestRoute].routeSymbol == 4)
    {
        trucks[1].totalBoxSize += shipment.vol;
        trucks[1].totalWeight += shipment.weight;
        result = 4;
    }
    else if (routes[bestRoute].routeSymbol == 8)
    {
        trucks[2].totalBoxSize += shipment.vol;
        trucks[2].totalWeight += shipment.weight;
        result = 8;
    }
    return result;
}


void printResult(struct Route bestRoute, struct Shipment shipment)
{
    switch (bestRoute.routeSymbol)
    {
    case 2:
        printf("Ship on BLUE LINE, ");
        break;
    case 4:
        printf("Ship on GREEN LINE, ");
        break;
    case 8:
        printf("Ship on YELLOW LINE, ");
        break;
    }

    if (bestRoute.numPoints >= 1)
    {
        if (bestRoute.numPoints == 1)
        {
            printf("no diversion.");
        }
        else
        {
            printf("divert: ");
            int i = 0;
            while (i < bestRoute.numPoints)
            {
                printf("%d%c", bestRoute.points[i].row + 1, 'A' + bestRoute.points[i].col);
                if (i != bestRoute.numPoints - 1)
                {
                    printf(", ");
                }
                i++;
            }
            if (bestRoute.points[bestRoute.numPoints - 1].col != shipment.destination.col ||
                bestRoute.points[bestRoute.numPoints - 1].row != shipment.destination.row)
            {
                printf(", %d%c", shipment.destination.row + 1, 'A' + shipment.destination.col);
            }
        }
    }
    else
    {
        printf("Ships tomorrow");
    }
    printf("\n");
}

void allPossibleRoute(struct Shipment shipment, struct Truck truck, const struct Map* map, struct Route routes[MAX_ROUTES], int* size)
{
    struct Map maps = populateMap();

    for (int i = 0; i < truck.route->numPoints; i++)
    {
        struct Route result = shortestPath(&maps, truck.route->points[i], shipment.destination);
        const struct Point resultDistance = result.points[result.numPoints - 1];

        if (isDestination(&result, shipment) == 1)
        {
            result.routeSymbol = truck.route->routeSymbol;
            routes[(*size)++] = result;

        }

        if (result.numPoints == 2)
        {
            for (int j = 0; j < truck.route->numPoints; j++)
            {
                // Check if the first point of the truck's route matches the first point of the result route
                if (result.points[0].row == truck.route->points[j].row &&
                    result.points[0].col == truck.route->points[j].col)
                {
                    // If the first point matches, update the first point of the result route to the shipment destination
                    result.points[0] = shipment.destination;
                    // Update the number of points in the result route to 1, effectively removing the original first point
                    result.numPoints = 1;
                }
            }
            // Set the route symbol of the modified result route to be the same as the truck's route symbol
            result.routeSymbol = truck.route->routeSymbol;
            // Add the modified result route to the "routes" array
            routes[(*size)++] = result;
        }

        else if (distance(&resultDistance, &shipment.destination) == 1 )
        {
            result.routeSymbol = truck.route->routeSymbol;
            routes[(*size)++] = result;
          
        }
    };
};

int findBestRoute(struct Route routes[MAX_ROUTES], int s, struct Shipment shipment)
{
    int ret = 0;
    int i = 0;

    for (i = 0; i < s; i++)
    {
        ret = (routes[i].numPoints < routes[ret].numPoints) ? i : ret;
    }
    return ret;
}

int isDestination(struct Route* route, struct Shipment shipment)
{
    int isDest = 0;
    int i = 0;
    while (i < route->numPoints && isDest == 0)
    {
        if (route->points[i].col == shipment.destination.col &&
            route->points[i].row == shipment.destination.row)
        {
            isDest = 1;
        }
        i++;
    }
    return isDest;
}

char truckLimitFactorComparison(const struct Truck Truck1, const struct Truck Truck2) {
    double tr1WeightPercent = (double)Truck1.totalWeight / MAX_WEIGHT;
    double tr2WeightPercent = (double)Truck2.totalWeight / MAX_WEIGHT;
    double tr1SizePercent = (double)Truck1.totalBoxSize / MAX_SIZE;
    double tr2SizePercent = (double)Truck2.totalBoxSize / MAX_SIZE;

    double tr1Percent = fmax(tr1WeightPercent, tr1SizePercent) * 100;
    double tr2Percent = fmax(tr2WeightPercent, tr2SizePercent) * 100;

    if (tr1Percent < tr2Percent) {
        return Truck1.route->routeSymbol; // Truck 1 has more space
    }
    else if (tr2Percent < tr1Percent) {
        return Truck2.route->routeSymbol; // Truck 2 has more space
    }
    else {
        return Truck1.route->routeSymbol; // Change******Both trucks have the same amount of space 
    }
}