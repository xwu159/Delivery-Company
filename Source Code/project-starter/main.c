#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mapping.h"
#include "delivery.h"


int main(void) {
	printf("=================\n");
	printf("Seneca Deliveries\n");
	printf("=================\n");

	double size;
	int weight, scanned, len, row, col, i, done = 0;
	char point[4], c;
	struct Point des;
	int loop = 1;
	int check;
	struct Shipment shipment = { 0 };

	struct Map map = populateMap();
	baseMap = &map;

	struct Route blue = getBlueRoute();
	struct Route green = getGreenRoute();
	struct Route yellow = getYellowRoute();

	struct Truck truck[3] = {
	{0, 0, &blue},
	{0, 0, &green},
	{0, 0, &yellow}
	};

	while (!done)
	{
		char p[4];
		struct Point des;
		int dataNum;
		int ret = 0;
		row = col = weight = dataNum = len = 0;
		size = -1;
		struct Shipment shipment;

		des.row = des.col = -1;

		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		dataNum = scanf("%d %lf %s", &weight, &size, p);
		len = strlen(p);

		if (dataNum != 3)
		{ 

			printf("Invalid input. Follow this format: 1 1 1A\n");

			char ch = 'x';
			while (ch != '\n')
			{
				ch = getchar();
			}
		}
		else
		{

			if (weight == 0 && size == 0 && strcmp(p, "x") == 0)
			{
				printf("Thank you for shipping with Seneca!\n");
				break;
			}

			for (int i = 0; i < len; i++)
			{

				c = p[i];

				if (c >= '0' && c <= '9')
				{
					row = row * 10 + (c - '0');
				}
				else if (c >= 'A' && c <= 'Z')
				{
					col = col * 26 + (c - 'A');
				}
			}

			// Assign the broken down row and col into the Point struct
			des.row = --row;
			des.col = col;

			check = validate(size, weight, des);
			if (check == 1)
			{
				shipment.weight = weight;
				shipment.vol = size;
				shipment.destination.row = des.row;
				shipment.destination.col = des.col;

				ret = findTruckForShipment(shipment);

				done = 0;
			}

		}
	}
	return 0;
}
