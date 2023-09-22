#define CLOSE_DISTANCE_THRESHOLD 1.5
struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest)
{
	struct Route result = { {0,0}, 0, DIVERSION };
	struct Route emptyRoute = { {0,0}, 0, DIVERSION };
	struct Point last = { -1, -1 };
	struct Point current = start;
	struct Route possible = { {0,0},0,0 };
	int close = 0;
	int iterations = 0;
	while (distance(&current, &dest) > CLOSE_DISTANCE_THRESHOLD)
	{
		possible = getPossibleMoves(map, current, last);
		close = getClosestPoint(&possible, dest);
		if (close >= 0)
		{
			last = current;
			current = possible.points[close];
			addPtToRoute(&result, current);
			if (result.numPoints == MAX_ROUTE)
				return emptyRoute;
		}
	}
	return result;
}