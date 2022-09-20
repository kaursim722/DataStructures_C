#include <stdio.h>
#include <math.h>
#include "Wall.h"

point* point_create(int x, int y){							// function to create points (malloc)
	point* p = (point*)malloc(sizeof(point));
	p->x = (double)x;
	p->y = (double)y;
	return p;
}

segment* segment_create(point* start, point* end){			// function to create a segment using points created
	segment* wall = (segment*)malloc(sizeof(segment));
	wall->start = start;
	wall->end = end;
	wall->orientation = GetOrientation(wall);
	return wall;
}

enum WallOrientation GetOrientation(segment* wall){			// function to check whether wall is vertical or horizontal
	if (wall->start->x == wall->end->x){
		return VERTICAL;
	} else {
		return HORIZONTAL;
	}
}

// determine a wall located on which side of the partition segment
enum ESegmentWallSide ClassifySegment(segment PartitionSeg, segment wall)										// ClassifySegment function to determine a wall located FRONT or BEHIND of segment
{
   if(GetOrientation(&PartitionSeg) == VERTICAL) {
		if((wall.start -> x <= PartitionSeg.start -> x) && (wall.end -> x <= PartitionSeg.end -> x)){			
		   return SEGMENT_WALL_SIDE_FRONT;
		} 
		else if ((wall.start -> x >= PartitionSeg.start -> x) && (wall.end -> x >= PartitionSeg.end -> x)){
			return SEGMENT_WALL_SIDE_BEHIND;
		}
		else {
			return SEGMENT_WALL_SIDE_STRADDLING;
		}
	}
	else if(GetOrientation(&PartitionSeg) == HORIZONTAL) {
		if((wall.start -> y <= PartitionSeg.start -> y) && (wall.end -> y <= PartitionSeg.end -> y)) {
			return SEGMENT_WALL_SIDE_FRONT;
		}
		else if ((wall.start -> y >= PartitionSeg.start -> y) && (wall.end -> y >= PartitionSeg.end -> y)) {
			return SEGMENT_WALL_SIDE_BEHIND;
		}
		else {
			return SEGMENT_WALL_SIDE_STRADDLING;
   		}
	}
}

// compute the intersection point on the wall divided by the PartitionSeg
int IntersectionWalls(segment PartitionSeg, segment wall, point* out){				// if Straddling and vertical, outx = startx of partition wall
	if(ClassifySegment(PartitionSeg, wall) == SEGMENT_WALL_SIDE_STRADDLING) {		// outy = starty of wall
		if(GetOrientation(&PartitionSeg) == VERTICAL){
			out -> x = PartitionSeg.start -> x;
			out -> y = wall.start -> y;
		}
		else if(GetOrientation(&PartitionSeg) == HORIZONTAL) {						// if straddling and horizontal, outx = startx of wall
			out -> x = wall.start -> x;												// outy = starty of partition segment
			out -> y = PartitionSeg.start -> y;
		}
		return 1;
	}
	return -1;
}


// Output the two segments of the original wall divided by the partition segment to frontSeg and backSeg
void SplitWallSegment(segment PartitionSeg, segment wall, segment *frontSeg, segment *backSeg)
{
    if(GetOrientation(&PartitionSeg) == HORIZONTAL) {					// if horizontal, split the start wall and end wall into front and back segments
		point *temp_point = (point*)malloc(sizeof(point));
		IntersectionWalls(PartitionSeg, wall, temp_point);
		*frontSeg = *segment_create(wall.start, temp_point);
		*backSeg = *segment_create(temp_point, wall.end);
	}
	else if (GetOrientation(&PartitionSeg) == VERTICAL) {				// if vertical, split the start wall and end wall into front and back segments
		point *temp_point = (point*)malloc(sizeof(point));
		IntersectionWalls(PartitionSeg, wall, temp_point);
		*frontSeg = *segment_create(wall.start, temp_point);
		*backSeg = *segment_create(temp_point, wall.end);
	}
}
