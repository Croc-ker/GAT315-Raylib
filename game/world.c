#include "world.h"
#include <stdlib.h>
#include <assert.h>

ncBody* ncBodies;
int ncBodyCount = 0;

ncBody* CreateBody() {
	ncBody* body = (ncBody*)malloc(sizeof(ncBody));
	assert(body);
	body->prev = NULL;
	body->next = ncBodies;
	if (ncBodies) ncBodies->prev = body;
	ncBodies = body;
	ncBodyCount++;
	return body;
}
void DestroyBody(ncBody* body) {
	assert(body);
	if (body->prev) body->prev->next = body->next;
	if (body->next) body->next->prev = body->prev;
	if (ncBodies == body) ncBodies = body->next;
	ncBodies--;
	free(body);
}
void DestroyAllBodies() { 
	return;
}