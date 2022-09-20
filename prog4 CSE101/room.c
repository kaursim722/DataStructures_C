// room.c
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "Wall.h"
#include "List.h"
#include "BSP.h"


// Two line segments are equal if they start and end at the same point
// Returns 0 if segments are equal, -1 otherwise
int SegmentsEqual(void* segment1, void* segment2){				// function to check if 2 line segments are equal 
	segment *seg1 = (segment*) segment1;
	segment *seg2 = (segment*) segment2;						// check startxy and endxy
	if((seg1 -> start -> x == seg2 -> start -> x) && (seg1 -> end -> x == seg2 -> end -> x) && (seg1 -> start -> y == seg2 -> start -> y) && (seg1 -> end -> y == seg2 -> end -> y)) {
		return 0;
	}
	else {
		return -1;
	}
}

//print out the coordinates of the segment, remember to use %d for integers
void PrintSegment(void* segment1){								// PrintSegment in correct format
	segment *seg1 = (segment*) segment1;
	if (seg1 == NULL) {
		printf("NULL\n");
	} 
	else {
		printf("%d %d %d %d\n", seg1 -> start -> x, seg1 -> start -> y, seg1 -> end -> x, seg1 -> end -> y);
	}
}

// remember to free the start and end points of the segment
void DestroySegment(segment* seg){								// DestroySegment by freeing the start and end 
	free(seg -> start);
	free(seg -> end);
	free(seg);
	seg == NULL;
}

/**
* @brief Takes a parent node and generates a list containing all elements that form the left subtree of parent
* Note: The original list should be modified so that it contains only elements that form the right subtree of parent
* Assumes that parent is not in original
*
* @param parent The parent node which elements in the list argument will be compared with to determine left/right relationship
* @param original A pointer to a list containing all children of the parent. Original is modified to contain all right children
*
* @return ListPtr pointing to a list which holds all elements which will form the left subtree of parent. Returns NULL if parent or orignal
* are null
*/
ListPtr GetPartitions(void* parent, ListPtr remaining){									
	int i = 0;
	int counter = 0;
	int elem_find;
	//printf("inside getpartition\n");
	ListPtr leftPoint = list_create(SegmentsEqual, PrintSegment, DestroySegment);						// create a list of leftPoints
	segment *initial = (segment*) parent;																// create a parent segment
	for(i; i < list_length(remaining); i++) {															// for loop until the end of the remaining list
		segment *seg = list_get_index(remaining, i);
		if(ClassifySegment(*initial, *seg) == SEGMENT_WALL_SIDE_STRADDLING) {							// if straddling, create segments, call splitSegment
			segment *seg1 = (segment*)malloc(sizeof(segment));
			segment *seg2 = (segment*)malloc(sizeof(segment));
			SplitWallSegment(*initial, *seg, seg1, seg2);
			int find_element = list_find_element(remaining, seg);										// store element after finding and delete that index
			list_del_index(remaining,find_element);
			if(ClassifySegment(*initial, *seg1) == SEGMENT_WALL_SIDE_FRONT) {							// if FRONT, append left seg to leftPoint and right seg to remaining 
				list_append(leftPoint, seg1);
				list_insert(remaining, i, seg2);
			}
			else if(ClassifySegment(*initial, *seg1) == SEGMENT_WALL_SIDE_BEHIND) {						// if BEHIND, append left seg to leftPoint list and right seg to remaining
				list_insert(remaining, i, seg1);
				list_append(leftPoint, seg2);
			}	
		}
		else if(ClassifySegment(*initial, *seg) == SEGMENT_WALL_SIDE_FRONT) {							// else if FRONT, append remaining index to leftPoint list
			list_append(leftPoint, list_get_index(remaining, i));
		}
		else if(ClassifySegment(*initial, *seg) == SEGMENT_WALL_SIDE_BEHIND) {							// else if BEHIND, do nothing
			printf("");
		}
	}
	for(counter; counter < list_length(leftPoint); counter ++) {										// delete index from list 
		elem_find = list_find_element(remaining, list_get_index(leftPoint, counter));
		list_del_index(remaining, elem_find);
	}
	return leftPoint;
}
/**
 * @brief used to select the data which will form the root of a new subtree
 *
 * @param remaining A listpointer containing all the remaining data, after execution it should not contain the removed value
 *
 * @return void* A pointer to the extracted data
 */ 
void* SelectPartitionRoot(ListPtr remaining){									// if length of remaining list is less than or equal to 1, delete index and return it
	//printf("inside select partition\n");
	if(list_length(remaining) <= 1) {
		return list_del_index(remaining, 0);
	}
	else {																		// floor(number of walls/2)
		int index = floor(list_length(remaining)/2);
		segment* del_index = list_del_index(remaining, index-1);
		return del_index;
	}
}

/**
 * BONUS POINT CASE.
 * Determines which wall the Fancy Door is located on using bsp tree
 * The fancy door is a segment with given endpoints
 *
 * @param tree The BSP tree you built with the provided rooms
 * @param door A segment to be found
 * @param Wall It will store the wall contains the door here.
 *
 * @return int Returns -1 if the door outside the room (as long as part of the door is outside the room), 
 *						0 if the door inside the room (including the door touch the walls), 
 *						1 if the door on the walls
*/ 
int FindFancyDoor(BSPTree* tree, segment fancydoor, segment* Wall);

/**
 * Determines which wall the door is located on using bsp tree
 * The door is a point with given coordinates
 *
 * @param tree The BSP tree that you built with the provided rooms
 * @param door A coordinate point to be found
 * @param Wall It will store the wall contains the door here.
 *
 * @return int Returns -1 if the door outside the room, 0 if the door inside the room, 1 if the door on the walls
 */
int FindDoor(BSPTree* tree, point door, segment* Wall) {					
	ListPtr wall_tree = BSP_GetTraversal(tree); 
	int i = 0;
	int j = 0;
	int intersect = 0;
	for(i; i < list_length(wall_tree); i++) {						// this loop checks for whether the door is on a vertical or horizontal segment
		segment *wall_segment = list_get_index(wall_tree, i);
		if(((((door.y <= wall_segment -> start -> y) && (door.y >= wall_segment -> end -> y)) || ((door.y >= wall_segment -> start -> y) && (door.y <= wall_segment -> end -> y))) && ((door.x == wall_segment -> start -> x) && (door.x == wall_segment -> end -> x))) && (GetOrientation(wall_segment) == VERTICAL)) {
			*Wall = *wall_segment;
			return 1;
		}
		else if (((((door.x >= wall_segment -> start -> x) && (door.x <= wall_segment -> end -> x)) || ((door.x <= wall_segment -> start -> x) && (door.x >= wall_segment -> end -> x))) && ((door.y == wall_segment -> start -> y) && (door.y == wall_segment -> end -> y))) && (GetOrientation(wall_segment) == HORIZONTAL)) {
			*Wall = *wall_segment;	
			return 1;
		}
	}
	for(j; j < list_length(wall_tree); j++) {						// this loop checks for whether the door is outside or inside the room by comparing the vertical lines 
		segment *wall_seg2 = list_get_index(wall_tree, j);
		if(GetOrientation(wall_seg2) == VERTICAL) {
			if(wall_seg2 -> start -> x > door.x && wall_seg2 -> end -> x > door.x) {
				if((door.y <= wall_seg2 -> start -> y && door.y >= wall_seg2 -> end -> y) || (door.y >= wall_seg2 -> start -> y && door.y <= wall_seg2 -> end -> y)) {
					intersect ++;
				}
			}
			else {
				//do nothing
			}	
		}
	}
	if(intersect % 2 == 0) {		
		return -1;
	}
	else{
		return 0;
	}
}

/**
 * @brief Used to draw out our BSP (room)
 *
 * @param tree A pointer to the tree containing the room
 * @param filename The name of the outputfile, DrawBSP concatenates with ".png"
 * @param doors A list of doors (points) that will be drawn to the cairo canvas in red
 * @param fancyDoors A list of fancyDoors (segments) that will be drawn to the cairo canvas in yellow
 *
 */
void DrawBSP(BSPTree* tree, char* filename, ListPtr doors, ListPtr fancyDoors){
	// Get a list of our BSP data sorted by pre-order traversal
	ListPtr traversalList = BSP_GetTraversal(tree);
	cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 512, 512);
	cairo_t *cr = cairo_create (surface);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, 0, 0, 512, 512);
	cairo_fill(cr);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 5.0);
	cairo_set_font_size(cr, 32);
	char label[10];
	for(int i = 0; i < list_length(traversalList); i++){
		segment* seg = (segment*)list_get_index(traversalList, i);
		//draw the line
		cairo_move_to(cr, seg->start->x, seg->start->y);
		cairo_line_to(cr, seg->end->x, seg->end->y);
		cairo_stroke(cr);
		int midX = (seg->start->x + seg->end->x)/2;
		int midY = (seg->start->y + seg->end->y)/2;
		cairo_move_to(cr, midX, midY);
		sprintf(label, "%d", i);
		cairo_show_text(cr, label);
	}
	
	if(doors != NULL){
		cairo_close_path(cr);
		cairo_set_source_rgb(cr, 1, 0, 0);
		for(int i = 0; i < list_length(doors); i++){
			point* d = (point*)list_get_index(doors, i);
			cairo_rectangle(cr, (d->x) - 5, (d->y) - 5, 10, 10);
			cairo_stroke(cr);
		}
	}

	if(fancyDoors != NULL){
		cairo_set_source_rgb(cr, 1, 1, 0);
		for(int i = 0; i < list_length(fancyDoors); i++){
			segment* seg = (segment*)list_get_index(fancyDoors, i);
			//draw the line
			cairo_move_to(cr, seg->start->x, seg->start->y);
			cairo_line_to(cr, seg->end->x, seg->end->y);
			cairo_close_path(cr);
			cairo_stroke(cr);
		}
	}

	cairo_destroy(cr);
	char* outputName = strcat(filename, ".png");
	cairo_surface_write_to_png(surface, outputName);
	cairo_surface_destroy(surface);
}


int main (int argc, char **argv){
	char room_file[100];
	int coord_1x;						//initialize variables
	int coord_2x;
	int coord_1y;
	int coord_2y;
	int door_type;
	int door_x;
	int door_y;

	ListPtr list_points = list_create(SegmentsEqual, PrintSegment, DestroySegment);		// list of door points
	ListPtr list_name = list_create(SegmentsEqual, PrintSegment, DestroySegment);		// list of room points 

	FILE *roomfile = fopen(argv[1], "r");												// take input from two files
	fscanf(roomfile, "%s", &room_file);
	//printf("----------ROOM Output---------\n");
	while(!feof(roomfile)) {									
		fscanf(roomfile, "%d", &coord_1x);
		fscanf(roomfile, "%d", &coord_1y);
		fscanf(roomfile, "%d", &coord_2x);
		fscanf(roomfile, "%d", &coord_2y);
		//printf("%d %d %d %d\n", coord_1x, coord_1y, coord_2x, coord_2y);
		point* p1 = point_create(coord_1x, coord_1y);
		point* p2 = point_create(coord_2x, coord_2y);
		segment* seg = segment_create(p1, p2);
		list_append(list_name, seg);
	}
	//printf("----------DOOR Output---------\n");

	FILE *doorfile = fopen(argv[2], "r");
	fscanf(doorfile, "%d", &door_type);
	while(!feof(doorfile)) {
		fscanf(doorfile, "%d", &door_x);
		fscanf(doorfile, "%d", &door_y);
		//printf("%d %d\n", door_x, door_y);
		point* coords = point_create(door_x, door_y);
		list_append(list_points, coords);
	}
	fclose(roomfile);				// close files
	fclose(doorfile);
	BSPTree* tree = BSP_Create(list_name, SelectPartitionRoot, GetPartitions, SegmentsEqual, PrintSegment, DestroySegment);
	//BSP_print(tree);
	DrawBSP(tree, room_file, list_points, NULL);

	int counter = 0;
	for(counter; counter < list_length(list_points); counter++) {				// for loop to print the output in correct format that checks whether door is inside or outside
		point* door_points = list_get_index(list_points, counter);
		point* p1 = point_create(0,0);											
		point* p2 = point_create(0,0);
		segment* interseg = segment_create(p1, p2); 
		int fdoor = FindDoor(tree, *door_points, interseg);
		if (fdoor == 0) {
			printf("IN\n");
		}
		else if (fdoor == -1) {
			printf("OUT\n");
		}
		else if (fdoor == 1) {
			PrintSegment(interseg);
		}
	}
}