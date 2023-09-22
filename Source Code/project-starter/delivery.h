#ifndef DELIVERY_H
#define DELIVERY_H

#include "mapping.h"

#define SMALL_BOX_VOL 0.25
#define MED_BOX_VOL 0.50
#define LARGE_BOX_VOL 1.0
#define MAX_WEIGHT 1000
#define MAX_SIZE 36
#define TRUCK_SIZE 3

struct Shipment
{
	int weight;
	double vol;
	struct Point destination;
};

struct Truck
{
	int totalWeight;
	double totalBoxSize;
	struct Route* route;
};

struct Map* baseMap;
struct Truck trucks[3];

/**
 * Validates parameters for shipment, and sends valid shipment to findTruckForShipments function.
 * @param size - size of shipment: SMALL_BOX_VOL, MED_BOX_VOL, or LARGE_BOX_VOL
 * @param weight - weight of shipment in kgs (1 - 1000)
 * @param des - shipment's deilvery destination from {0,0} to {25,25}
 * @returns  1 if valid,-1 if invalid size,-2 if invalid weight,-3 if invalid destination
 */
int validate(double size, int weight, struct Point des);

/**
 * Validate the given point is within the map boundaries.
 * @ param des - the point to be validate
 * @ returns - an integer, return 1 if the point is valid, and 0 otherwise
 */
int isValidPoint(const struct Point des);

/**
 *Validate the weight of a shipment is within the maximum weight that the truck can hold up to
 *@ param weight - the weight added to the truck
 *@ returns - an integer, return 1 if the point is valid, and 0 otherwise
 */
int isValidWeight(int weight);

/**
 *Validate the box size is a valid size for shipment and the size added to the shipment is within the maximum capacity of the truck
 *@ param size -  the box size to be validate
 *@ returns  - an integer, return 1 if the point is valid, and 0 otherwise
 */
int isValidSize(double size);


/**
 * Find the best truck for shipment with the consideration of shortest distance, availability and validation of size and weight.
 * @param shipment - shipment from user input, including weight, box size, and destination information
 * @returns - a character, returns route symbol of the assigned truck; 2 for blue truck, 4 for green truck, 8 for yellow truck and 0 if no truck is assigned
 */
char findTruckForShipment(struct Shipment shipment);


/**
 *Have all possible paths form the 3 route to a shipment destination, looping through all the points on these 3 routes, getting the shortest possible path from those point to the shipment destination point, and store the possible path in the route[maxNoRoute] array
 *@ param truck - the truck in the 3 routes
 *@ param shipment - the shipment form the user input
 *@ param route -  an array to store all the possible path
 *@ param size - the size of the route array for iteration
 */
void allPossibleRoute(struct Shipment shipment, struct Truck truck, const struct Map* map, struct Route routes[MAX_ROUTES], int* size);

/**
 * Find the best route by comparing possible routes from 3 different trucks that stored in routes, create a loop and compare.
 * The best route is determined by the shortest number of points in the route.
 *
 * @param routes - An array of Route structures representing possible routes from different trucks.
 * @param s - The number of routes in the 'routes' array.
 * @param shipment - The Shipment structure representing the shipment details.
 * @returns - An integer, representing the index of the best route in the 'routes' array. If 's' is 0 or negative, or 'routes' is NULL, or no valid route is found, the function returns -1.
 */
int findBestRoute(struct Route routes[MAX_ROUTES], int s, struct Shipment shipment);

/**
 * Check if destination point is included in the route. Iterating the route to find the destination.
 * @param route - the route to be checked if any of route points is a destination of shipment
 * @param shipment - shipment destination to be compared
 * @returns - an integer, return 1 when destination is found and included, return 0 when destination is not found
 */
int isDestination(struct Route* route, struct Shipment shipment);

/**
 * Print the result as output, including best truck, diversion, and proposed route
 * @param bestRoute - the best route to deliver will be printed
 * @param shipment - shipment data including destination to be printed
 *
 */
void printResult(struct Route bestRoute, struct Shipment shipment);


/**
* Calculate the limit factor percentage and comparison between two trucks to determine less full truck.
* @param truck1 - the first truck to be compared, including total weight, box size and route symbol information
* @param truck2 - the second truck to be compared, including total weight, box size and route symbol information
* @returns - a character, returns route symbol of the less full truck; 2 for blue truck, 4 for green truck, 8 for yellow truck and 0 if they have the same percentage.
*/

char truckLimitFactorComparison(struct Truck truck1, struct Truck truck2);

#endif
