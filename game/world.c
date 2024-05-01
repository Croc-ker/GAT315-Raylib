#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies;
int bodyCount = 0;

Body* CreateBody() {
	/*
	Allocate memory for a new Body using malloc.
	Assert that the allocation was successful.
	Set the new body’s prev pointer to NULL and its next pointer to the current head of the list(bodies).
	If the list is not empty, update the prev pointer of the current head.
	Set the bodies to the new Body
	Increment the bodyCount.
	Return the new Body.
	*/
	Body* body = (Body*)malloc(sizeof(Body));
	assert(body);
	body->prev = NULL;
	body->next = bodies;
	if (bodies) bodies->prev = body;
	bodies = body;
	bodyCount++;
	return body;
}
void DestroyBody(Body* body) {
	assert(body);
	if (body->prev) body->prev->next = body->next;
	if (body->next) body->next->prev = body->prev;
	if (bodies == body) bodies = body->next;
	bodies--;
	free(body);
}