// Created by Simranpreet Kaur
// CSE101 Fall 2021
// skaur52@ucsc.edu
// October 3, 2021

#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// sqRecur recursive function to draw successively smaller squares using fractions

void sqRecur(int width, int height, int depth, double fract, double point1x, double point1y, double point2x, double point2y, double point3x, double point3y, double point4x, double point4y, cairo_t *cr) {
	if (depth == 0) {
		return;
	}
	else {

		double store_1 = point1x;				// storing point1 to go back to the starting point to close the box
		double store_2 = point1y;			
		double W1 = point2x - point1x;			// P2.x - P1.x (prog0 document)
		double H1 = point2y - point1y;			// P2.y - P1.y (prog0 document)
		double W2 = point3x - point2x;
		double H2 = point3y - point2y;
		double W3 = point4x - point3x;
		double H3 = point4y - point3y;
		double W4 = store_1 - point4x;
		double H4 = store_2 - point4y;

		cairo_set_source_rgb (cr, 0, 0, 0);			// black pen

		point1x = point1x + fract * W1;						// P2, P.x = P1.x + 0.1*W and P.y = P1.y + 0.1*H (prog0 document)
		point1y = point1y + fract * H1;
		cairo_move_to (cr, point1x,  point1y);				// move cursor to origin to start making first square

		point2x = point2x + fract * W2;
		point2y = point2y + fract * H2;
		cairo_line_to (cr, point2x, point2y);				// draw line to next point
		
		point3x = point3x + fract * W3;
		point3y = point3y + fract * H3;
		cairo_line_to (cr, point3x, point3y);				// draw line to next point

		point4x = point4x + fract * W4;
		point4y = point4y + fract * H4;
		cairo_line_to (cr, point4x, point4y);				// draw line to next point

		cairo_line_to (cr, point1x, point1y);				// draw line to next point
		cairo_stroke (cr);

	}
		depth = depth - 1;									// goes down by one to recursively call
		sqRecur(width, height, depth, fract, point1x, point1y, point2x, point2y, point3x, point3y, point4x, point4y, cr);

	return;
}

// main function to create the canvas background, base square, and send user's output to file

int main () {

	char user_input[50];			//initializing variables
	int width;						
	int height;
	int depth;
	double fract;
	double origx;
	double origy;
	double lastx;
	double lasty;


	scanf("%s", user_input);		// scanning through text file for user input and storing addresses
	strcat(user_input, ".png");		// concatenate strings
	scanf("%d", &width);
	scanf("%d", &height);
	scanf("%d", &depth);
	scanf("%lf", &fract);
	scanf("%lf", &origx);
	scanf("%lf", &origy);
	scanf("%lf", &lastx);
	scanf("%lf", &lasty);	

	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height );  // create canvas background
	cairo_t *cr = cairo_create(surface);

	cairo_set_source_rgb (cr, 143.0/255.0, 247.0/255.0, 206.0/255.0);		// customized background color
	cairo_rectangle (cr, 0, 0, 512, 512);   								// set canvas size
	cairo_fill (cr);														// fill in background

	cairo_set_source_rgb (cr, 0, 0, 0);			// black pen
	cairo_move_to (cr, origx,  origy);			// move cursor to origin to start making first square
	cairo_line_to (cr, lastx, lasty);			// draw line to next point
	cairo_line_to (cr, lastx + (lasty - origy), lasty - (lastx - origx));	
	cairo_line_to (cr, (lastx + (lasty - origy)) - (lastx - origx), (lasty - (lastx - origx)) - (lasty - origy));
	cairo_line_to (cr, origx, origy);			// draw line back to origin
	cairo_stroke (cr);						
	
	sqRecur(width, height, depth, fract, origx, origy, lastx, lasty, lastx + (lasty - origy), lasty - (lastx - origx), (lastx + (lasty - origy)) - (lastx - origx), (lasty - (lastx - origx)) - (lasty - origy), cr);

	// sending output to the file
	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, user_input);
	cairo_surface_destroy(surface);
	return 0;
	
}

