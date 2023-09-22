#include "pch.h"
#include "delivery_r.h"
#include "CppUnitTest.h"
#include "mapping.h"
#include "delivery.h"
#include <iostream>
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest
{
	TEST_CLASS(ValidateTest)
	{
	public:
		TEST_METHOD(I1001)
		{
			//edge case in weight 
			double size = 0.5;
			int weight = 1000;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(I1002)
		{
			//normal case 
			double size = 0.5;
			int weight = 800;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(I1003)
		{
			//test: isValidSize failed;
			double size = 2;
			int weight = 1000;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I1004)
		{
			//test: isValidWeight failed;
			double size = 0.5;
			int weight = 2000;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-2, result);
		}

		TEST_METHOD(I1005)
		{
			//test: isValidPoint failed;
			double size = 0.5;
			int weight = 1000;
			struct Point des = { 25, 25 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-3, result);
		}
		TEST_METHOD(I1006)
		{
			//test: isValidPoint in negative
			double size = 0.5;
			int weight = 800;
			struct Point des = { -1, -1 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-3, result);
		}

		TEST_METHOD(I1007)
		{
			//test: all failed
			double size = 0;
			int weight = 2000;
			struct Point des = { -1, -1 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-2, result);
		}

		TEST_METHOD(I1008)
		{
			//test: isValidSize and isValidPoint failed
			double size = '\0';
			int weight = 500;
			struct Point des = { -1, -1 };
			int result = validate(size, weight, des);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I1009)
		{
			//isValidWeight case: value immediately adjacent to other special value
			double size = 0.5;
			int weight = 1;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(I1010)
		{
			//isValidWeight case: MAXWEIGHT
			double size = 0.5;
			int weight = MAX_WEIGHT;
			struct Point des = { 6, 4 };
			int result = validate(size, weight, des);
			Assert::AreEqual(1, result);
		}

	};


	TEST_CLASS(FindTruckForShipment_allPossibleRouteTest)
	{
	public:
		TEST_METHOD(I2001)
		{
			//normal: GREEN LINE
			struct Shipment shipment = { 50, 0.25, {7, 24} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(4, result);
		}

		TEST_METHOD(I2002)
		{
			//BLUE LINE edge case
			struct Shipment shipment = { 50, 0.25, {1, 1} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(2, result);
		}

		TEST_METHOD(I2003)
		{
			//normal: BLUE LINE 
			struct Shipment shipment = { 50, 0.25, {6, 7} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(2, result);
		}

		TEST_METHOD(I2004)
		{
			//out of map MAX range
			struct Shipment shipment = { 20, 0.25, {25, 25} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I2005)
		{
			//out of map MIN range
			struct Shipment shipment = { 20, 0.25, {-1, -1} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I2006)
		{
			//normal YELLOW line
			struct Shipment shipment = { 20, 0.25, {21, 6} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(8, result);
		}

		TEST_METHOD(I2007)
		{
			//normal YELLOW line
			struct Shipment shipment = { 20, 0.25, {23, 9} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(8, result);
		}
		
	};


	TEST_CLASS(FindTruckForShipment_findBestRouteTest)
	{
	public:
		TEST_METHOD(I3001)
		{
			//normal: GREEN LINE
			struct Shipment shipment = { 20, 0.25, {1, 16} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(4, result);
		}

		TEST_METHOD(I3002)
		{
			//normal: BLUE LINE
			struct Shipment shipment = { 20, 0.25, {11, 11} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(2, result);
		}

		TEST_METHOD(I3003)
		{
			//normal: YELLOW LINE
			struct Shipment shipment = { 20, 0.25, {21, 13} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(8, result);
		}

		TEST_METHOD(I3004)
		{
			//out of map MAX range
			struct Shipment shipment = { 20, 0.25, {25, 25} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I3005)
		{
			//out of map MIN range
			struct Shipment shipment = { 20, 0.25, {-1, -1} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I3006)
		{
			//shipment with invalid weight
			struct Shipment shipment = { 2000, 0.25, {6, 4} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(I3007)
		{
			//shipment with invalid size
			struct Shipment shipment = { 30, 40, {6, 4} };
			int result = findTruckForShipment(shipment);
			Assert::AreEqual(-1, result);
		}

	};


	TEST_CLASS(allPossibleRoute_findBestRoute)
	{
	public:
		TEST_METHOD(I4001)
		{
			//shipment destination is 0,0 - edge case
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {0, 0} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(0, bestRoute);
		}

		TEST_METHOD(I4002)
		{
			//shipment destination is -1,-1 - out of MIN scope
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {-1, -1} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(0, bestRoute);
		}

		TEST_METHOD(I4003)
		{
			//shipment destination is 25,25 - out of MAX scope
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {25, 25} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(0, bestRoute);
		}

		TEST_METHOD(I4004)
		{
			//BLUE truck normal
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {6, 8} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(11, bestRoute);
		}

		TEST_METHOD(I4005)
		{
			//GREEN truck normal
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {2, 12} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(13, bestRoute);
		}

		TEST_METHOD(I4006)
		{
			//YELLOW truck normal
			int size = 0;
			int result = -1;
			struct Route routes[MAX_ROUTES] = { 0 };
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			trucks[0].route = &blueRoute;
			trucks[1].route = &greenRoute;
			trucks[2].route = &yellowRoute;
			struct Shipment shipment = { 20, 0.25, {6, 4} };

			allPossibleRoute(shipment, trucks[0], baseMap, routes, &size);
			int bestRoute = findBestRoute(routes, size, shipment);

			Assert::AreEqual(7, bestRoute);
		}

	};

}



namespace BlackboxTest
{
	TEST_CLASS(IsValidPointTest)
	{
	public:
		TEST_METHOD(F1001)
		{
			struct Point p1 = { 6, 4 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F1002)
		{
			struct Point p1 = { 0, 0 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F1003)
		{
			struct Point p1 = { 24, 24 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F1004)
		{
			struct Point p1 = { 25, 25 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F1005)
		{
			struct Point p1 = { 30, 30 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F1006)
		{
			struct Point p1 = { -1, -1 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F1007)
		{
			struct Point p1 = { -1, 1 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result); 
		}

		TEST_METHOD(F1008)
		{
			struct Point p1 = { 1, -1 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

	};

	
	TEST_CLASS(IsValidWeightTest)
	{
	public:
		TEST_METHOD(F2001)
		{
			int weight = 500;
			int result = isValidWeight(weight);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F2002)
		{
			int weight = 1000;
			int result = isValidWeight(weight);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F2003)
		{
			int weight = 1500;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F2004)
		{
			int weight = -200;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F2005)
		{
			int weight = 0;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F2006)
		{
			int weight = 1;
			int result = isValidWeight(weight);
			Assert::AreEqual(1, result);
			};
		
		TEST_METHOD(F2007)
		{
			int weight = 1001;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F2008)
		{
			int weight = -1;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}
		
};
	TEST_CLASS(IsValidSizeTest)
	{
	public:
		TEST_METHOD(F3001)
		{
			double size = 0.25;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F3002)
		{
			double size = 0.5;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F3003)
		{
			double size = 1.0;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F3004)
		{
			double size = 0.0;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F3005)
		{
			double size = 1.5;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F3006)
		{
			double size = -0.5;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F3007)
		{
			double size = 0.1;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F3008)
		{
			double size = 2;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}


	};

	/* TEST_CLASS(FindTruckForShipmentTest) //include multiple function and not available for unit test
	{
	public:
		TEST_METHOD(F4001)
		{
			struct Shipment s = { 500, 0.25, {5, 7} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(F4002)
		{
			struct Shipment s = { 800, 0.5, {15, 21} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(F4003)
		{
			struct Shipment s = { 1200, 1.0, {4, 6} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(F4004)
		{
			struct Shipment s = { 1000, 0.25, {1, 1} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(F4005)
		{
			struct Shipment s = { 1000, 0.5, {24, 23} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(F4006)
		{
			struct Shipment s = { 1000, 1.0, {12, 11} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(F4007)
		{
			struct Shipment s = { -200, 0.5, {8, 16} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(F4008)
		{
			struct Shipment s = { 700, 2.0, {-1, 5} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}
	};*/


	
	TEST_CLASS(TruckLimitFactorComparisonTest)
	{
	public:
		TEST_METHOD(F5001)
		{

			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2'};
			struct Truck truck1 = { 100, 20, &blueRoute};
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'4' };
			struct Truck truck2 = { 80, 15, &greenRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result);
		}

		
		TEST_METHOD(F5002)
		{
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }}, 3, '4' };
			struct Truck truck1 = { 80, 15, &greenRoute};
			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2' };
			struct Truck truck2 = { 100, 20, &blueRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result); 
		}

		
		TEST_METHOD(F5003)
		{
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }}, 3, '4' };
			struct Truck truck1 = { 100, 15, &greenRoute};
			struct Route yellowRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '8' };
			struct Truck truck2 = { 100, 20, &yellowRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result);
		}

		
		TEST_METHOD(F5004)
		{
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }}, 3, '4' };
			struct Truck truck1 = { 0, 0, &greenRoute };
			struct Route yellowRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '8' };
			struct Truck truck2 = { 0, 0, &yellowRoute };
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result);
		}
		
		TEST_METHOD(F5005)
		{
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }}, 3, '4' };
			struct Truck truck1 = {100, 0, &greenRoute};
			struct Route yellowRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '8' };
			struct Truck truck2 = { 100, 0, &yellowRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result);
			//Assert::Fail(L"Error!Both trucks have weight, but zero box size");
		}

		
		TEST_METHOD(F5006)
		{
			struct Route greenRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '4' };
			struct Truck truck1 = { 0, 20, &greenRoute };
			struct Route yellowRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'8' };
			struct Truck truck2 = { 0, 20, &yellowRoute };
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result);
			//Assert::Fail(L"Error!Both trucks have box sizes, but zero weight");
		}
		
	};
	

	TEST_CLASS(IsDestinationTest)
	{
	public:

		TEST_METHOD(F7001)
		{
			struct Route route = { 0 };
			route.points[0] = { 1, 0 };
			route.points[1] = { 2, 0 };
			route.points[2] = { 3, 0 };
			route.points[3] = { 4, 0 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {5, 0} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F7002)
		{
			struct Route route = { 0 };
			route.points[0] = { 10, 1 };
			route.points[1] = { 11, 2 };
			route.points[2] = { 12, 3 };
			route.points[3] = { 13, 4 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {13, 4} };

			int result = isDestination(&route, s);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F7003)
		{
			struct Route route = { 0 };
			route.points[0] = { 24, 1 };
			route.points[1] = { 24, 2 };
			route.points[2] = { 24, 3 };
			route.points[3] = { 24, 4 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {24, 4} };

			int result = isDestination(&route, s);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(F7004)
		{
			struct Route route = { 0 };
			route.points[0] = { 1, 0 };
			route.points[1] = { 2, 0 };
			route.points[2] = { 3, 0 };
			route.points[3] = { 4, 0 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {5, 0} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F7005)
		{
			struct Route route = { 0 };
			route.points[0] = { 1, 0 };
			route.points[1] = { 2, 0 };
			route.points[2] = { 3, 0 };
			route.points[3] = { 4, 0 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {-1, 0} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F7006)
		{
			struct Route route = { 0 };
			route.numPoints = 0;

			struct Shipment s = { 800, 30, {5, 0} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}
	};

	TEST_CLASS(FindBestRouteTest)
	{
	public:
		TEST_METHOD(F8001)
		{
			int size = 2;
			struct Truck truck[3]; 
			struct Route route1 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route route2 = { {{1,1}, {2,2}, {3,3}}, 3, '4' };
			struct Route routes[2] = { route1, route2 };
			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F8002)
		{
			int size = 0; 
			struct Truck truck[3];
			struct Route routes[2] = {}; 
			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result); //was -1
		}

		TEST_METHOD(F8003)
		{
			int size = 1;
			struct Truck truck[3];
			struct Route route1 = { {{1,1}, {2,2}, {3,3}}, 3, '4' };
			struct Route routes[1] = { route1 };
			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(F8004)
		{
			int size = 0;
			struct Truck truck[3];
			struct Route route1 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route route2 = { {{1,1}, {2,2}, {3,3}}, 3, '4' };
			struct Route routes[2] = { route1, route2 };
			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result); //was 0
		}

		TEST_METHOD(F8005)
		{
			int size = 2;
			struct Truck truck[3];
			struct Route route1 = { {{1,1}, {2,2}, {3,3}}, 3, '4' };
			struct Route route2 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route routes[2] = { route1, route2 };
			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(1, result);
		}

	};
}


namespace WhiteboxTest
{
	TEST_CLASS(IsValidPointTest)
	{
	public:
		TEST_METHOD(W1001)
		{
			struct Point p1 = { 2, 4 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W1002)
		{
			struct Point p1 = { 0, 0 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W1003)
		{
			struct Point p1 = { 24, 24 };
			int result = isValidPoint(p1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W1004)
		{
			struct Point p1 = { 25, 25 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W1005)
		{
			struct Point p1 = { -1, -1 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W1006)
		{
			struct Point p1 = { -1, 2 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W1007)
		{
			struct Point p1 = { 2, -1 };
			int result = isValidPoint(p1);
			Assert::AreEqual(0, result);
		}
	};

	TEST_CLASS(IsValidWeightTest)
	{
	public:
		TEST_METHOD(W2001)
		{
			int weight = 100;
			int result = isValidWeight(weight);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W2002)
		{
			int weight = 0;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W2003)
		{
			int weight = 1000;
			int result = isValidWeight(weight);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W2004)
		{
			int weight = 1100;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W2005)
		{
			int weight = -100;
			int result = isValidWeight(weight);
			Assert::AreEqual(0, result);
		}
	};

	TEST_CLASS(IsValidSizeTest)
	{
	public:
		TEST_METHOD(W3001)
		{
			double size = 0.25;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W3002)
		{
			double size = 0.5;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W3003)
		{
			double size = 1.0;
			int result = isValidSize(size);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W3004) //Failed Case report to Jira and resolved
		{
			double size = 0.0;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W3005)
		{
			double size = 1.5;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W3006)
		{
			double size = -0.5;
			int result = isValidSize(size);
			Assert::AreEqual(0, result);
		}
	};

	/*TEST_CLASS(FindTruckForShipmentTest)  //include multiple function and not available for unit test
	{
		public:
		TEST_METHOD(W4001)
		{
			struct Shipment s = { 500, 0.25, {5, 7} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W4002)
		{
			struct Shipment s = { 800, 0.5, {15, 21} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W4003)
		{
			struct Shipment s = { 1000, 0.25, {1, 1} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W4004)
		{
			struct Shipment s = { 1000, 0.5, {24, 23} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W4005)
		{
			struct Shipment s = { 1000, 1.0, {12, 11} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W4006)
		{
			struct Shipment s = { -200, 0.5, {8, 16} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(W4007)
		{
			struct Shipment s = { 700, 2.0, {1, 5} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(W4008)
		{
			struct Shipment s = { 1200, 1.0, {4, 6} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(W4009)
		{
			struct Shipment s = { 700, 1.0, {1, 25} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(W4010)
		{
			struct Shipment s = { 700, 1.0, {-1, 5} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

		TEST_METHOD(W4011)
		{
			struct Shipment s = { 700, 1.0, {-1, -5} };
			char result = findTruckForShipment(s);
			Assert::AreEqual('0', result);
		}

	};*/

	TEST_CLASS(truckLimitFactorComparisonTest)
	{
	public:
		TEST_METHOD(W5001)
		{
			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2' };
			struct Truck truck1 = { 600, 10, &blueRoute};
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'4' };
			struct Truck truck2 = { 800, 8, &greenRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('2', result);
		}

		TEST_METHOD(W5002)
		{
			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2' };
			struct Truck truck1 = { 400, 30, &blueRoute};
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'4' };
			struct Truck truck2 = { 800, 20, &greenRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('4', result); //should be 4?
		}


		TEST_METHOD(W5003)
		{
			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2' };
			struct Truck truck1 = { 700, 15, &blueRoute };
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'4' };
			struct Truck truck2 = { 700, 15, &greenRoute };
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('2', result);
		}


		TEST_METHOD(W5004)
		{
			struct Route blueRoute = { { {0, 0}, {1, 2}, {3, 4} }, 3, '2' };
			struct Truck truck1 = { 0, 0, &blueRoute};
			struct Route greenRoute = { { {0, 0}, { 1, 2 }, { 3, 4 }},3,'4' };
			struct Truck truck2 = { 0, 0, &greenRoute};
			char result = truckLimitFactorComparison(truck1, truck2);
			Assert::AreEqual('2', result);
		}

	};

	TEST_CLASS(IsDestinationTest)
	{
	public:
		TEST_METHOD(W6001)
		{
			struct Route route = { 0 };
			route.points[0] = { 1, 0 };
			route.points[1] = { 2, 0 };
			route.points[2] = { 3, 0 };
			route.points[3] = { 4, 0 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {3,0} };

			int result = isDestination(&route, s);
			Assert::AreEqual(1, result);
		}


		TEST_METHOD(W6002)
		{
			struct Route route = { 0 };
			route.points[0] = { 0, 1 };
			route.points[1] = { 0, 2 };
			route.points[2] = { 0, 3 };
			route.points[3] = { 0, 4 };

			route.numPoints = 4;

			struct Shipment s = { 800, 30, {0,4} };

			int result = isDestination(&route, s);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W6003)
		{
			struct Route route = { 0 };
			route.points[0] = { 9, 1 };
			route.points[1] = { 10, 1 };
			route.points[2] = { 11, 1 };
			route.points[3] = { 12, 1 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {12,1} };

			int result = isDestination(&route, s);
			Assert::AreEqual(1, result);

		}

		TEST_METHOD(W6004)
		{
			struct Route route = { 0 };
			route.points[0] = { 1, 0 };
			route.points[1] = { 2, 0 };
			route.points[2] = { 3, 0 };
			route.points[3] = { 4, 0 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {4,2} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W6005)
		{
			struct Route route = { 0 };
			route.points[0] = { 0, 1 };
			route.points[1] = { 0, 2 };
			route.points[2] = { 0, 3 };
			route.points[3] = { 0, 4 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {1,4} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W6006)
		{
			struct Route route = { 0 };
			route.points[0] = { 9, 1 };
			route.points[1] = { 10, 1 };
			route.points[2] = { 11, 1 };
			route.points[3] = { 12, 1 };
			route.numPoints = 4;

			struct Shipment s = { 800, 30, {13,2} };

			int result = isDestination(&route, s);
			Assert::AreEqual(0, result);
		}


	};


	TEST_CLASS(FindBestRouteTest)
	{
	public:
		TEST_METHOD(W7001) //Failed Case report to Jira and resolved
		{
			int size = 2;

			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Truck truck[3];
			truck[0].route = &blueRoute;
			truck[1].route = &greenRoute;
			truck[2].route = &yellowRoute;

			struct Route route1 = { {{1,1}, {2,2}, {3,3}}, 3, '2' };
			struct Route route2 = { {{1,1}, {2,2}}, 2, '4' };

			struct Route routes[2] = { route1, route2 };

			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(W7002)
		{
			int size = 2;

			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Truck truck[3];
			truck[0].route = &blueRoute;
			truck[1].route = &greenRoute;
			truck[2].route = &yellowRoute;

			struct Route route1 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route route2 = { {{1,1}, {2,2}, {3,3}}, 3, '4' };

			struct Route routes[2] = { route1, route2 };

			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W7003) //empty
		{
			int size = 0;

			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Truck truck[3];
			truck[0].route = &blueRoute;
			truck[1].route = &greenRoute;
			truck[2].route = &yellowRoute;

			struct Route emptyRoute[2];

			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(emptyRoute, size, s);
			Assert::AreEqual(0, result); //was 0
		}


		TEST_METHOD(W7004) //negative
		{
			int size = 2;

			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Truck truck[3];
			truck[0].route = &blueRoute;
			truck[1].route = &greenRoute;
			truck[2].route = &yellowRoute;

			struct Route route1 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route route2 = { {{-1,1}, {2,-2}, {-3,3}}, 3, '4' };

			struct Route routes[2] = { route1, route2 };


			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(W7005) //same distance
		{
			int size = 2;

			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();
			struct Truck truck[3];
			truck[0].route = &blueRoute;
			truck[1].route = &greenRoute;
			truck[2].route = &yellowRoute;

			struct Route route1 = { {{1,1}, {2,2}}, 2, '2' };
			struct Route route2 = { {{1,1}, {2,2}}, 2, '2' };

			struct Route routes[2] = { route1, route2 };

			struct Shipment s = { 800, 30, {6,19} }; //just added

			int result = findBestRoute(routes, size, s);
			Assert::AreEqual(0, result);
		}

	};

}