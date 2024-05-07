#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum ncBodyType {
	STATIC,
	KINEMATIC,
	DYNAMIC
} ncBodyType;

typedef enum {
	FORCE,
	IMPULSE,
	VELOCITY
} ncForceMode;

typedef struct ncBody
{
	ncBodyType type;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass;
	float gravityScale;
	float damping;

	Color color;

	struct ncBody* next;
	struct ncBody* prev;
} ncBody;



inline void ApplyForce(ncBody* body, Vector2 force, ncForceMode mode)
{
	if (body->type != DYNAMIC) return;

	switch (mode) {
	case FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case IMPULSE:
		body->velocity = Vector2Scale(force, body->inverseMass);
		break;
	case VELOCITY:
		body->velocity = force;
		break;
	}
}

inline void ClearForce(ncBody* body)
{
	body->force = Vector2Zero();
}

void Step(ncBody* body, float timestep);