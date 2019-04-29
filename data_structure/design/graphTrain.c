#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAX 41
#define INF 0x3f3f3f3f
#define MAXSTATION 500

typedef struct Edge
{
	int adj;
	int weight;
	int line;
	struct Edge *next;
} edge;

typedef struct Station
{
	char name[MAX];
	int trans;
	int line;
	int station;
	edge *link;
} station;

typedef struct Line
{
	int size;
	int seq;
	int isLoop;
	struct Station *list;
} line;

typedef struct Railway
{
	int size;
	struct Station list[MAXSTATION];
} railway;

void addEdge(station *head, int end, int line);
void addStation(railway *railway, line line, int inLine, int inRail);
void updateStation(railway *railway, line line, int inLine, int inRail);
void addLine(railway *railway, line line);
void updateLine(railway *railway, line *line);
int inRail(railway railway, char name[]);
void Dijkstra(railway *railway, char startname[], char destname[], int path[]);
int getLine(railway railway, int stat1, int stat2);
void getPath(railway *railway, int start, int dest, int path[]);

int main()
{
	int linenum, lineseq, statnum, trans;
	int i, j;
	char statname[MAX], startname[MAX], destname[MAX];
	FILE *fi = fopen("bgstations.txt", "r");

	if (fi == NULL) 
		exit(1);

	railway *beijing = (railway *)malloc(sizeof(railway));
	beijing->size = 0;

	line *new_line = (line *)malloc(sizeof(line));
	fscanf(fi, "%d\n", &linenum);

	for (i = 1; i <= linenum; i++)
	{
		fscanf(fi, "%d %d\n", &lineseq, &statnum);
		new_line->seq = lineseq;
		new_line->size = statnum;
		new_line->isLoop = 0;
		new_line->list = (station *)malloc(statnum * sizeof(station));

		for (j = 0; j < statnum; j++)
		{
			fscanf(fi, "%s %d\n", statname, &trans);
			new_line->list[j].line = i;
			strcpy(new_line->list[j].name, statname);
			new_line->list[j].trans = trans;
		}

		if (strcmp(new_line->list[0].name, statname) == 0)
			new_line->isLoop = 1;

		updateLine(beijing, new_line);
		addLine(beijing, *new_line);
		free(new_line->list);
		fscanf(fi, "\n");
	}

	scanf("%s", startname);
	scanf("%s", destname);

	int *path = (int *)malloc(beijing->size * sizeof(int));
	Dijkstra(beijing, startname, destname, path);

	getPath(beijing, inRail(*beijing, startname), inRail(*beijing, destname), path);

	free(new_line);
	free(path);
	fclose(fi);

	return 0;
}

void addEdge(station *head, int end, int line)
{
	edge *rear = head->link;
	edge *new_edge = (edge *)malloc(sizeof(edge));

	if (new_edge == NULL)
	{
		printf("ERROR");
		exit(1);
	}

	new_edge->weight = 1;
	new_edge->line = line;
	new_edge->adj = end;
	new_edge->next = NULL;

	if (rear == NULL)
		head->link = new_edge;
	else
	{
		while (rear->next != NULL)
			rear = rear->next;
		rear->next = new_edge;
	}
}

void addStation(railway *railway, line line, int inLine, int inRail)
{
	strcpy(railway->list[inRail].name, line.list[inLine].name);

	railway->list[inRail].trans = line.list[inLine].trans;
	railway->list[inRail].line = line.seq;
	railway->list[inRail].station = inRail;
	railway->list[inRail].link = NULL;
	railway->size++;

	if (inLine == 0)
	{
		if (line.isLoop)
		{
			addEdge(&(railway->list[inRail]), line.list[1].station, line.seq);
			addEdge(&(railway->list[inRail]), line.list[line.size - 2].station, line.seq);
		}
		else
			addEdge(&(railway->list[inRail]), line.list[1].station, line.seq);
	}

	else if (inLine == line.size - 1 - line.isLoop)
	{
		if (line.isLoop)
		{
			addEdge(&(railway->list[inRail]), line.list[0].station, line.seq);
			addEdge(&(railway->list[inRail]), line.list[line.size - 3].station, line.seq);
		}
		else
			addEdge(&(railway->list[inRail]), line.list[line.size - 2].station, line.seq);
	}
	else
	{
		addEdge(&(railway->list[inRail]), line.list[inLine + 1].station, line.seq);
		addEdge(&(railway->list[inRail]), line.list[inLine - 1].station, line.seq);
	}
}

void updateStation(railway *railway, line line, int inLine, int inRail)
{
	if (inLine == 0)
	{
		if (line.isLoop)
		{
			addEdge(&(railway->list[inRail]), line.list[1].station, line.seq);
			addEdge(&(railway->list[inRail]), line.list[line.size - 2].station, line.seq);
		}
		else
			addEdge(&(railway->list[inRail]), line.list[1].station, line.seq);
	}

	else if (inLine == line.size - 1 - line.isLoop)
	{
		if (line.isLoop)
		{
			addEdge(&(railway->list[inRail]), line.list[0].station, line.seq);
			addEdge(&(railway->list[inRail]), line.list[line.size - 3].station, line.seq);
		}
		else
			addEdge(&(railway->list[inRail]), line.list[line.size - 2].station, line.seq);
	}

	else
	{
		addEdge(&(railway->list[inRail]), line.list[inLine + 1].station, line.seq);
		addEdge(&(railway->list[inRail]), line.list[inLine - 1].station, line.seq);
	}
}

void addLine(railway *railway, line line)
{
	int inLine, inrail, seq_fromsize = railway->size;

	if (railway->size == 0)
	{
		for (inLine = 0; inLine < line.size; inLine++)
		{
			railway->list[inLine].link = NULL;
			addStation(railway, line, inLine, inLine);
		}
	}
	else
	{
		for (inLine = 0; inLine < line.size - line.isLoop; inLine++)
		{
			inrail = inRail(*railway, line.list[inLine].name);
			if (inrail != -1)
				updateStation(railway, line, inLine, inrail);
			else
			{
				addStation(railway, line, inLine, seq_fromsize);
				seq_fromsize++;
			}
		}
	}
}

void updateLine(railway *railway, line *line)
{
	int inLine, inrail, seq_fromsize = railway->size;

	if (railway->list == NULL)
	{
		for (inLine = 0; inLine < line->size; inLine++)
			line->list[inLine].station = inLine;
	}
	else
	{
		for (inLine = 0; inLine < line->size; inLine++)
		{
			inrail = inRail(*railway, line->list[inLine].name);

			if (inrail != -1)
				line->list[inLine].station = inrail;

			else
			{
				line->list[inLine].station = seq_fromsize;
				seq_fromsize++;
			}
		}
	}
}

int inRail(railway railway, char name[])
{
	int rail;

	for (rail = 0; rail < railway.size; rail++)
		if (strcmp(railway.list[rail].name, name) == 0)
			return rail;

	return -1;
}

void Dijkstra(railway *railway, char startname[], char destname[], int path[])
{
	int start = inRail(*railway, startname);
	int dest = inRail(*railway, destname);
	int *dist = (int *)malloc(railway->size * sizeof(int));
	memset(dist, INF, railway->size * sizeof(int));
	dist[start] = 0;

	edge *link = railway->list[start].link;
	while (link != NULL)
	{
		dist[link->adj] = link->weight;
		path[link->adj] = start;
		link = link->next;
	}

	while (dist[dest] == INF)
	{
		int min = INF, minstat = dest, iter;
		for (iter = 0; iter < railway->size; iter++)
		{
			if (dist[iter] != 0 && dist[iter] < min)
			{
				min = dist[iter];
				minstat = iter;
			}
		}
		link = railway->list[minstat].link;
		if (link == NULL) exit(1);
		while (link != NULL)
		{
			if (dist[minstat] + link->weight < dist[link->adj])
			{
				dist[link->adj] = dist[minstat] + link->weight;
				path[link->adj] = minstat;
			}
			link = link->next;
		}
		dist[minstat] = 0;
	}


	free(dist);
}

int getLine(railway railway, int stat1, int stat2)
{
	edge *link = railway.list[stat1].link;

	while (link != NULL)
	{
		if (link->adj == stat2)
			return link->line;
		link = link->next;
	}
	return -1;
}

void getPath(railway *railway, int start, int dest, int path[])
{
	int *track = (int *)malloc(railway->size * sizeof(int));
	int i = 0, k = 0, currstats = 1;
	memset(track, INF, railway->size * sizeof(int));
	while (dest != start)
	{
		track[k++] = dest;
		dest = path[dest];
	}
	track[k] = start;

	int j = k;
	while (i < j)
	{
		int tmp;
		tmp = track[j];
		track[j] = track[i];
		track[i] = tmp;
		i++, j--;
	}

	printf("%s-", railway->list[track[0]].name);

	for (i = 1; i < k; i++)
	{
		if (getLine(*railway, railway->list[track[i - 1]].station, railway->list[track[i]].station) != getLine(*railway, railway->list[track[i + 1]].station, railway->list[track[i]].station))
		{
			printf("%d(%d)-%s-", getLine(*railway, railway->list[track[i - 1]].station,
				railway->list[track[i]].station), currstats, railway->list[track[i]].name);
			currstats = 1;
		}
		else
			currstats++;
	}

	printf("%d(%d)-%s\n", getLine(*railway, railway->list[track[i - 1]].station, railway->list[track[i]].station), currstats, railway->list[track[k]].name);
}