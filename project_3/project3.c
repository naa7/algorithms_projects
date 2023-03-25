/*Testcode for  220 Homework 3 Spring 2020: Exploration of a grid graph */
/* compiles with command line  gcc test.c -lX11 -lm */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 30
#define OPEN_SPACE_COUNT 30
#define FREE 1
#define BLOCKED 0

typedef struct {
	int x, y, z;
} vertice;

typedef struct {
	vertice one, two;
} Edge;

typedef struct {
	int front, end, size;
	unsigned length;
	Edge* array;
} Queue;

int stepx, stepy, startx, starty, offsetx, offsety;
Queue* newQueue(unsigned length);
int check_if_not_empty(Queue* queue);
int check_if_empty(Queue* queue);
void enQueue(Queue* queue, Edge element);
Edge* deQueue(Queue* queue);
Edge* front(Queue* queue);
Edge* end(Queue* queue);
void insert(int* g, Queue* queue, int* Visited, int x, int y, int z);
void explored_edge(int sx, int sy, int sz, int tx, int ty, int tz);
void path_edge(int sx, int sy, int sz, int tx, int ty, int tz);
void find_path(int *g, int sx, int sy, int sz, int tx, int ty, int tz);


Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
unsigned int display_width, display_height;

Window win;
int border_width;
unsigned int win_width, win_height;
int win_x, win_y;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = "Example Window";
char *icon_name_string = "Icon for Example Window";

XEvent report;

GC gc, gc_yellow, gc_green, gc_red, gc_grey;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values, gc_green_values,
gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;


int main(int argc, char **argv)
{
	int graph[SIZE][SIZE][2]; int i, j, k;
	int sx, sy, sz, tx, ty, tz; /* start and target vertice */
	int rand_init_value;
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &rand_init_value);
		srand(rand_init_value);
	}
	for (i = 0; i< SIZE; i++)
		for (j = 0; j <SIZE; j++)
		{
			graph[i][j][0] = BLOCKED; graph[i][j][1] = BLOCKED;
		}
	/* cross of five open vertices in both directions */
	for (k = 0; k < (0.3*OPEN_SPACE_COUNT); k++)
	{
		i = rand() % (SIZE - 4); j = rand() % (SIZE - 4);
		graph[i][j + 2][0] = FREE;       graph[i + 1][j + 2][0] = FREE;
		graph[i + 2][j + 2][0] = FREE;     graph[i + 3][j + 2][0] = FREE;
		graph[i + 4][j + 2][0] = FREE;
		graph[i + 2][j][0] = FREE;       graph[i + 2][j + 1][0] = FREE;
		graph[i + 2][j + 3][0] = FREE;     graph[i + 2][j + 4][0] = FREE;
		i = rand() % (SIZE - 4); j = rand() % (SIZE - 4);
		graph[i][j + 2][1] = FREE;       graph[i + 1][j + 2][1] = FREE;
		graph[i + 2][j + 2][1] = FREE;     graph[i + 3][j + 2][1] = FREE;
		graph[i + 4][j + 2][1] = FREE;
		graph[i + 2][j][1] = FREE;       graph[i + 2][j + 1][1] = FREE;
		graph[i + 2][j + 3][1] = FREE;     graph[i + 2][j + 4][1] = FREE;

	}
	/* lines of six open vertices in x direction */
	for (k = 0; k < (0.3*OPEN_SPACE_COUNT); k++)
	{
		i = rand() % (SIZE - 5); j = rand() % SIZE;
		graph[i][j][0] = FREE;       graph[i + 1][j][0] = FREE;
		graph[i + 2][j][0] = FREE;     graph[i + 3][j][0] = FREE;
		graph[i + 4][j][0] = FREE;     graph[i + 5][j][0] = FREE;
		i = rand() % (SIZE - 5); j = rand() % SIZE;
		graph[i][j][1] = FREE;       graph[i + 1][j][1] = FREE;
		graph[i + 2][j][1] = FREE;     graph[i + 3][j][1] = FREE;
		graph[i + 4][j][1] = FREE;     graph[i + 5][j][1] = FREE;
	}
	/* lines of four open vertices in x direction */
	for (k = 0; k < OPEN_SPACE_COUNT; k++)
	{
		i = rand() % (SIZE - 3); j = rand() % SIZE;
		graph[i][j][0] = FREE;       graph[i + 1][j][0] = FREE;
		graph[i + 2][j][0] = FREE;     graph[i + 3][j][0] = FREE;
		i = rand() % (SIZE - 3); j = rand() % SIZE;
		graph[i][j][1] = FREE;       graph[i + 1][j][1] = FREE;
		graph[i + 2][j][1] = FREE;     graph[i + 3][j][1] = FREE;
	}
	/* lines of six open vertices in y direction */
	for (k = 0; k < (0.3*OPEN_SPACE_COUNT); k++)
	{
		i = rand() % SIZE; j = rand() % (SIZE - 5);
		graph[i][j][0] = FREE;       graph[i][j + 1][0] = FREE;
		graph[i][j + 2][0] = FREE;     graph[i][j + 3][0] = FREE;
		graph[i][j + 4][0] = FREE;     graph[i][j + 5][0] = FREE;
		i = rand() % SIZE; j = rand() % (SIZE - 5);
		graph[i][j][1] = FREE;       graph[i][j + 1][1] = FREE;
		graph[i][j + 2][1] = FREE;     graph[i][j + 3][1] = FREE;
		graph[i][j + 4][1] = FREE;     graph[i][j + 5][1] = FREE;
	}
	/* lines of four open vertices in y direction */
	for (k = 0; k < OPEN_SPACE_COUNT; k++)
	{
		i = rand() % SIZE; j = rand() % (SIZE - 3);
		graph[i][j][0] = FREE;       graph[i][j + 1][0] = FREE;
		graph[i][j + 2][0] = FREE;     graph[i][j + 3][0] = FREE;
		i = rand() % SIZE; j = rand() % (SIZE - 3);
		graph[i][j][1] = FREE;       graph[i][j + 1][1] = FREE;
		graph[i][j + 2][1] = FREE;     graph[i][j + 3][1] = FREE;
	}
	/* pair of vertices open in both layers */
	for (k = 0; k < OPEN_SPACE_COUNT; k++)
	{
		i = rand() % (SIZE - 1); j = rand() % SIZE;
		graph[i][j][0] = FREE;       graph[i + 1][j][0] = FREE;
		graph[i][j][1] = FREE;       graph[i + 1][j][1] = FREE;
		i = rand() % SIZE; j = rand() % (SIZE - 1);
		graph[i][j][0] = FREE;       graph[i][j + 1][0] = FREE;
		graph[i][j][1] = FREE;       graph[i][j + 1][1] = FREE;
	}

	/* now generate start and target vertice */
	/* and insure they are FREE, and connected to the graph*/
	sx = rand() % (SIZE - 4) + 1;
	sy = rand() % (SIZE - 4) + 1; sz = 0;
	graph[sx][sy][sz] = FREE;    graph[sx][sy + 1][sz] = FREE;
	graph[sx][sy + 2][sz] = FREE;   graph[sx][sy - 1][sz] = FREE;
	graph[sx - 1][sy][sz] = FREE;   graph[sx + 1][sy][sz] = FREE;
	graph[sx + 2][sy][sz] = FREE;
	tx = rand() % (SIZE - 4) + 1;
	ty = rand() % (SIZE - 4) + 1; tz = 1;
	graph[tx][ty][tz] = FREE;    graph[tx][ty + 1][tz] = FREE;
	graph[tx][ty + 2][tz] = FREE;   graph[tx][ty - 1][tz] = FREE;
	graph[tx - 1][ty][tz] = FREE;   graph[tx + 1][ty][tz] = FREE;
	graph[tx + 2][ty][tz] = FREE;


	/* opening display: basic connection to X Server */
	if ((display_ptr = XOpenDisplay(display_name)) == NULL)
	{
		printf("Could not open display. \n"); exit(-1);
	}
	printf("Connected to X server  %s\n", XDisplayName(display_name));
	screen_num = DefaultScreen(display_ptr);
	screen_ptr = DefaultScreenOfDisplay(display_ptr);
	color_map = XDefaultColormap(display_ptr, screen_num);
	display_width = DisplayWidth(display_ptr, screen_num);
	display_height = DisplayHeight(display_ptr, screen_num);

	printf("Width %d, Height %d, Screen Number %d\n",
		display_width, display_height, screen_num);
	/* creating the window */
	border_width = 10;
	win_x = 0; win_y = 0;
	win_height = (int)(display_height / 1.3);
	win_width = win_height; /*square window*/

	win = XCreateSimpleWindow(display_ptr, RootWindow(display_ptr, screen_num),
		win_x, win_y, win_width, win_height, border_width,
		BlackPixel(display_ptr, screen_num),
		WhitePixel(display_ptr, screen_num));
	/* now try to put it on screen, this needs cooperation of window manager */
	size_hints = XAllocSizeHints();
	wm_hints = XAllocWMHints();
	class_hints = XAllocClassHint();
	if (size_hints == NULL || wm_hints == NULL || class_hints == NULL)
	{
		printf("Error allocating memory for hints. \n"); exit(-1);
	}

	size_hints->flags = PPosition | PSize | PMinSize;
	size_hints->min_width = 60;
	size_hints->min_height = 60;

	XStringListToTextProperty(&win_name_string, 1, &win_name);
	XStringListToTextProperty(&icon_name_string, 1, &icon_name);

	wm_hints->flags = StateHint | InputHint;
	wm_hints->initial_state = NormalState;
	wm_hints->input = False;

	class_hints->res_name = "x_use_example";
	class_hints->res_class = "examples";

	XSetWMProperties(display_ptr, win, &win_name, &icon_name, argv, argc,
		size_hints, wm_hints, class_hints);

	/* what events do we want to receive */
	XSelectInput(display_ptr, win,
		ExposureMask | StructureNotifyMask | ButtonPressMask);

	/* finally: put window on screen */
	XMapWindow(display_ptr, win);

	XFlush(display_ptr);

	/* create graphics context, so that we may draw in this window */
	gc = XCreateGC(display_ptr, win, valuemask, &gc_values);
	XSetForeground(display_ptr, gc, BlackPixel(display_ptr, screen_num));
	XSetLineAttributes(display_ptr, gc, 2, LineSolid, CapRound, JoinRound);
	/* and some other graphics contexts, to draw in yellow and red and grey*/
	/* yellow*/
	gc_yellow = XCreateGC(display_ptr, win, valuemask, &gc_yellow_values);
	XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "yellow",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color yellow\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_yellow, tmp_color1.pixel);
	/* green */
	gc_green = XCreateGC(display_ptr, win, valuemask, &gc_green_values);
	XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "green",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color green\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_green, tmp_color1.pixel);
	/* red*/
	gc_red = XCreateGC(display_ptr, win, valuemask, &gc_red_values);
	XSetLineAttributes(display_ptr, gc_red, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "red",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color red\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_red, tmp_color1.pixel);
	/* grey */
	gc_grey = XCreateGC(display_ptr, win, valuemask, &gc_grey_values);
	XSetLineAttributes(display_ptr, gc_grey, 2, LineSolid, CapRound, JoinRound);
	if (XAllocNamedColor(display_ptr, color_map, "light grey",
		&tmp_color1, &tmp_color2) == 0)
	{
		printf("failed to get color grey\n"); exit(-1);
	}
	else
		XSetForeground(display_ptr, gc_grey, tmp_color1.pixel);

	/* and now it starts: the event loop */
	while (1)
	{
		XNextEvent(display_ptr, &report);
		switch (report.type)
		{
		case ConfigureNotify:
			/* This event happens when the user changes the size of the window*/
			win_width = report.xconfigure.width;
			win_height = report.xconfigure.height;
			/* break; this case continues into the next:after a resize,
			the figure gets redrawn */
		case Expose:
			/* (re-)draw the figure. This event happens
			each time some part of the window gets exposed (becomes visible) */
			XClearWindow(display_ptr, win);
			stepx = (int)(win_width / (SIZE + 4));
			stepy = (int)(win_height / (SIZE + 4));
			startx = 2 * stepx; offsetx = (int)(0.4*stepx);
			starty = 2 * stepy; offsety = (int)(0.4*stepy);
			/* Draw Grid vertices */
			for (i = 0; i < SIZE; i++)
				for (j = 0; j < SIZE; j++)
				{
					{ if (graph[i][j][0] == BLOCKED)
						XFillArc(display_ptr, win, gc_grey, /* grey */
							startx + i*stepx, starty + j*stepy, /*upper left corner */
							(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
					else
						XFillArc(display_ptr, win, gc, /*black*/
							startx + i*stepx, starty + j*stepy, /*upper left corner */
							(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
					}
					{
						if (graph[i][j][1] == BLOCKED)
							XFillArc(display_ptr, win, gc_grey, /* grey */
								startx + offsetx + i*stepx, starty + offsety + j*stepy,
								(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
						else
							XFillArc(display_ptr, win, gc, /*black*/
								startx + offsetx + i*stepx, starty + offsety + j*stepy,
								(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
					}

				}
			/* Draw edges in x direction */
			for (i = 0; i < (SIZE - 1); i++)
				for (j = 0; j < SIZE; j++)
				{
					if (graph[i][j][0] == FREE && graph[i + 1][j][0] == FREE)
						XDrawLine(display_ptr, win, gc,
							startx + i*stepx + (int)(0.15*stepx),
							starty + j*stepy + (int)(0.15*stepy),
							startx + (i + 1)*stepx + (int)(0.15*stepx),
							starty + j*stepy + (int)(0.15*stepy));
					if (graph[i][j][1] == FREE && graph[i + 1][j][1] == FREE)
						XDrawLine(display_ptr, win, gc,
							startx + offsetx + i*stepx + (int)(0.15*stepx),
							starty + offsety + j*stepy + (int)(0.15*stepy),
							startx + offsetx + (i + 1)*stepx + (int)(0.15*stepx),
							starty + offsety + j*stepy + (int)(0.15*stepy));
				}
			/* Draw edges in y direction */
			for (i = 0; i < SIZE; i++)
				for (j = 0; j < (SIZE - 1); j++)
				{
					if (graph[i][j][0] == FREE && graph[i][j + 1][0] == FREE)
						XDrawLine(display_ptr, win, gc,
							startx + i*stepx + (int)(0.15*stepx),
							starty + j*stepy + (int)(0.15*stepy),
							startx + i*stepx + (int)(0.15*stepx),
							starty + (j + 1)*stepy + (int)(0.15*stepy));
					if (graph[i][j][1] == FREE && graph[i][j + 1][1] == FREE)
						XDrawLine(display_ptr, win, gc,
							startx + offsetx + i*stepx + (int)(0.15*stepx),
							starty + offsety + j*stepy + (int)(0.15*stepy),
							startx + offsetx + i*stepx + (int)(0.15*stepx),
							starty + offsety + (j + 1)*stepy + (int)(0.15*stepy));
				}
			/* Draw edges in z direction */
			for (i = 0; i < SIZE; i++)
				for (j = 0; j < SIZE; j++)
				{
					if (graph[i][j][0] == FREE && graph[i][j][1] == FREE)
						XDrawLine(display_ptr, win, gc,
							startx + i*stepx + (int)(0.15*stepx),
							starty + j*stepy + (int)(0.15*stepy),
							startx + offsetx + i*stepx + (int)(0.15*stepx),
							starty + offsety + j*stepy + (int)(0.15*stepy));
				}
			/* Draw Start and Target vertice yellow: before call of function*/
			XFillArc(display_ptr, win, gc_red, /*red*/
				startx + sx*stepx, starty + sy*stepy,
				(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
			XFillArc(display_ptr, win, gc_red, /*red*/
				startx + offsetx + tx*stepx, starty + offsety + ty*stepy,
				(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);

			/* Now call function to draw shortest path */
			find_path(&(graph[0][0][0]), sx, sy, sz, tx, ty, tz);
			/* Draw Start and Target vertice red, after function did its work*/
			XFillArc(display_ptr, win, gc_red, /*red*/
				startx + sx*stepx, starty + sy*stepy,
				(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);
			XFillArc(display_ptr, win, gc_red, /*red*/
				startx + offsetx + tx*stepx, starty + offsety + ty*stepy,
				(int)(0.3*stepx), (int)(0.3*stepy), 0, 360 * 64);

			/*	  XDrawLine(display_ptr, win, gc, win_width /4, win_height/ 3,
			3*win_width/4, win_height/3 );
			XDrawArc( display_ptr, win, gc_yellow, win_width/4, win_height/3,
			win_height/6, win_height/3, 90*64, 180*64);*/

			break;
		default:
			/* this is a catch-all for other events; it does not do anything.
			One could look at the report type to see what the event was */
			break;
		}

	}
	exit(0);
}

Queue* newQueue(unsigned length) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->length = length;
	queue->front = queue->size = 0;
	queue->end = length - 1;
	queue->array = (Edge*)malloc(queue->length * sizeof(Edge));
	return queue;
}

int check_if_empty(Queue* queue) {

	return (queue->size == 0);
}

void enQueue(Queue* queue, Edge element)
{
	if (check_if_not_empty(queue))
		return;

	queue->end = (queue->end + 1) % queue->length;
	queue->array[queue->end] = element;
	queue->size = queue->size + 1;
}

Edge* deQueue(Queue* queue)
{
	if (check_if_empty(queue))
		return NULL;

	Edge* element = &queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->length;
	queue->size = queue->size - 1;
	return element;
}

Edge* front(Queue* queue)
{
	if (check_if_empty(queue))
		return NULL;

	return &queue->array[queue->front];
}

Edge* end(Queue* queue)
{
	if (check_if_empty(queue))
		return NULL;

	return &queue->array[queue->end];
}

int check_if_not_empty(Queue* queue) {

	return (queue->size == queue->length);
}

void insert(int* g, Queue* queue, int* Visited, int x, int y, int z) {

	vertice one, two;
	Edge edge;
	one.x = x; one.y = y; one.z = z;
	if (z == 1 && *(g + x * 2 * SIZE + y * 2 + z - 1) == FREE && *(Visited + x * 2 * SIZE + y * 2 + z - 1) == 0) {
		two.x = x; two.y = y; two.z = z - 1;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
	if (z == 0 && *(g + x * 2 * SIZE + y * 2 + z + 1) == FREE && *(Visited + x * 2 * SIZE + y * 2 + z + 1) == 0) {
		two.x = x; two.y = y; two.z = z + 1;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
	if (x >= 1 && *(g + (x - 1) * 2 * SIZE + y * 2 + z) == FREE && *(Visited + (x - 1) * 2 * SIZE + y * 2 + z) == 0) {
		two.x = x - 1; two.y = y; two.z = z;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
	if (x < SIZE - 1 && *(g + (x + 1) * 2 * SIZE + y * 2 + z) == FREE && *(Visited + (x + 1) * 2 * SIZE + y * 2 + z) == 0) {
		two.x = x + 1; two.y = y; two.z = z;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
	if (y >= 1 &&	*(g + x * 2 * SIZE + (y - 1) * 2 + z) == FREE && *(Visited + x * 2 * SIZE + (y - 1) * 2 + z) == 0) {
		two.x = x; two.y = y - 1; two.z = z;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
	if (y < SIZE - 1 && *(g + x * 2 * SIZE + (y + 1) * 2 + z) == FREE && *(Visited + x * 2 * SIZE + (y + 1) * 2 + z) == 0) {
		two.x = x; two.y = y + 1; two.z = z;
		edge.one = one; edge.two = two;
		enQueue(queue, edge);
	}
}

void explored_edge(int sx, int sy, int sz, int tx, int ty, int tz)
{
	if (abs(sx - tx) + abs(sy - ty) + abs(sz - tz) != 1)
		printf(" called explored_edge to connect non-neighbors (%d,%d,%d) and (%d,%d,%d)\n", sx, sy, sz, tx, ty, tz);
	else
		XDrawLine(display_ptr, win, gc_green,
			startx + sx*stepx + sz*offsetx + (int)(0.15*stepx),
			starty + sy*stepy + sz*offsety + (int)(0.15*stepy),
			startx + tx*stepx + tz*offsetx + (int)(0.15*stepx),
			starty + ty*stepy + tz*offsety + (int)(0.15*stepy));
}

void path_edge(int sx, int sy, int sz, int tx, int ty, int tz)
{
	if (abs(sx - tx) + abs(sy - ty) + abs(sz - tz) != 1)
		printf(" called path_edge to connect non-neighbors (%d,%d,%d) and (%d,%d,%d)\n", sx, sy, sz, tx, ty, tz);
	else
		XDrawLine(display_ptr, win, gc_red,
			startx + sx*stepx + sz*offsetx + (int)(0.15*stepx),
			starty + sy*stepy + sz*offsety + (int)(0.15*stepy),
			startx + tx*stepx + tz*offsetx + (int)(0.15*stepx),
			starty + ty*stepy + tz*offsety + (int)(0.15*stepy));
}

void find_path(int *g, int sx, int sy, int sz, int tx, int ty, int tz)
{
	int Visited[SIZE][SIZE][2] = { 0 };
	vertice Visited_from[SIZE][SIZE][2];
	Queue* queue = newQueue(5000);
	Visited[sx][sy][sz] = 1;
	insert(g, queue, &(Visited[0][0][0]), sx, sy, sz);

	while (check_if_empty(queue) == 0) {
		Edge edge = *deQueue(queue);
		vertice One = edge.one;
		vertice Two = edge.two;
		explored_edge(One.x, One.y, One.z, Two.x, Two.y, Two.z);

		if (Visited[tx][ty][tz] == 1) {
			vertice Three = Visited_from[tx][ty][tz];
			path_edge(tx, ty, tz, Three.x, Three.y, Three.z);
			while (abs(sx - Three.x) + abs(sy - Three.y) + abs(sz - Three.z) > 0) {
				vertice Four = Visited_from[Three.x][Three.y][Three.z];
				path_edge(Four.x, Four.y, Four.z, Three.x, Three.y, Three.z);
				Three = Four;
			}
		}

		if (Visited[Two.x][Two.y][Two.z] == 0) {
			Visited[Two.x][Two.y][Two.z] = 1;
			Visited_from[Two.x][Two.y][Two.z] = One;
			insert(g, queue, &(Visited[0][0][0]), Two.x, Two.y, Two.z);
		}
	}
}
