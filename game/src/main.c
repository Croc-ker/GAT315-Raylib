#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void) {
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if ((IsMouseButtonDown(0))) {
			ncBody* body = CreateBody();
			body->position = position;
			body->velocity = createVector2(GetRandomFloatValue(-1, 1), GetRandomFloatValue(-1, 1));
		}

		//apply force
		ncBody* body = ncBodies;
		while (body)
		{
			ApplyForce(body, createVector2(0, -50));
			body = body->next;
		}

		//update bodies
		body = ncBodies;
		while (body)
		{
			ExplicitEuler(body, dt);
			ClearForce(body);
			body = body->next;
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, PINK);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, PURPLE);
		DrawCircle((int)position.x, (int)position.y, 10, DARKPURPLE);

		//draw bodies
		body = ncBodies;
		while (body)
		{
			DrawCircle((int)body->position.x, (int)body->position.y, 5, DARKBLUE);
			body = body->next;
		}

		EndDrawing();
	}

	CloseWindow();
	free(ncBodies);
	return 0;
}