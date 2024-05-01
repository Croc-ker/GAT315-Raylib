#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"

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
			Body* body = CreateBody();
			body->position = position;
			body->velocity = createVector2(GetRandomFloatValue(-1, 1), GetRandomFloatValue(-1, 1));
			body->force = createVector2(0, 0);
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, PINK);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, PURPLE);
		DrawCircle((int)position.x, (int)position.y, 10, DARKPURPLE);

		// update / draw bodies
		Body* body = bodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			body->velocity = Vector2Add(body->velocity, body->force, dt);
			body->position = Vector2Add(body->position, body->velocity, dt);
			// draw body
			DrawCircle((int)body->position.x, (int)body->position.y, 5, DARKBLUE);

			body = body->next; // get next body
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}