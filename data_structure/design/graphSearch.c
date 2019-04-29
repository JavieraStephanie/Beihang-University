#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAX 100

struct Vertex {
	int label;
	bool visited;
};


int queue[MAX];
int rear = -1;
int front = 0;
int stack[MAX];
int top = -1;
int queueItemCount = 0;

struct Vertex* lstVertices[MAX];

int adjMatrix[MAX][MAX];

int vertexCount = 0;

void push(int item) {
	stack[++top] = item;
}

int pop() {
	return stack[top--];
}

int peek() {
	return stack[top];
}

bool isStackEmpty() {
	return top == -1;
}

void insert(int data) {
	queue[++rear] = data;
	queueItemCount++;
}

int removeData() {
	queueItemCount--;
	return queue[front++];
}

bool isQueueEmpty() {
	return queueItemCount == 0;
}

void addVertex(int label) 
{
	struct Vertex* vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
	vertex->label = label;
	vertex->visited = false;
	lstVertices[vertexCount++] = vertex;
}

void addEdge(int start, int end) 
{
	adjMatrix[start][end] = 1;
	adjMatrix[end][start] = 1;
}

void displayVertex(int vertexIndex) {
	printf("%d ", lstVertices[vertexIndex]->label);
}

int getAdjUnvisitedVertex(int vertexIndex) 
{
	int i;

	for (i = 0; i<vertexCount; i++) 
	{
		if (adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false)
			return i;
	}

	return -1;
}

void depthFirstSearch(int search, int x) 
{
	int i;

	lstVertices[0]->visited = true;
	displayVertex(0);
	push(0);

	while (!isStackEmpty()) 
	{
		int unvisitedVertex = getAdjUnvisitedVertex(peek());

		if (unvisitedVertex == -1) 
		{
			pop();
		}
		else 
		{
			lstVertices[unvisitedVertex]->visited = true;
			if (unvisitedVertex == x && search)
				continue;
			displayVertex(unvisitedVertex);
			push(unvisitedVertex);
		}
	}
        
	for (i = 0; i < vertexCount; i++) 
	{
		lstVertices[i]->visited = false;
	}
}

void breadthFirstSearch(int search, int x) 
{
	int i;

	lstVertices[0]->visited = true;
	displayVertex(0);
	insert(0);
	int unvisitedVertex;

	while (!isQueueEmpty()) {
		int tempVertex = removeData();

		while ((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1) 
		{
			lstVertices[unvisitedVertex]->visited = true;
			if (unvisitedVertex == x && search)
				continue;
			displayVertex(unvisitedVertex);
			insert(unvisitedVertex);
		}

	}
      
	for (i = 0; i<vertexCount; i++) {
		lstVertices[i]->visited = false;
	}
}

int main() 
{
	int i, j, num, edge, x, search=0;
	
	scanf("%d %d", &num, &edge);

	for (i = 0; i<num; i++)
		for (j = 0; j<num; j++)
			adjMatrix[i][j] = 0;

	for (i = 0; i < num; i++)
		addVertex(i);

	for (i = 0; i < edge; i++)
	{
		int src, dest;
		scanf("%d %d", &src, &dest);
		addEdge(src, dest);
	}

	scanf("%d", &x);

	depthFirstSearch(search, x);
	printf("\n");
	breadthFirstSearch(search, x);
	printf("\n");
	search = 1;
	depthFirstSearch(search, x);
	printf("\n");
	breadthFirstSearch(search, x);

	return 0;
}