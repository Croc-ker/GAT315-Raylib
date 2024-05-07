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

		ncGravity = createVector2(0, 2);

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0)) {
			/* standard
			Color color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			for (int i = 0; i < 30; i++) {
				float angle = GetRandomFloatValue(0, 360);
				Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(-30, 30)) * DEG2RAD), GetRandomFloatValue(150, 300));
				ncBody* body = CreateBody();
				body->color = color;
				body->position = position;
				body->mass = GetRandomFloatValue(1, 15);
				body->inverseMass = 1 / body->mass;
				body->type = DYNAMIC;
				body->damping = 1.5f;
				body->gravityScale = 5;
				ApplyForce(body, force, VELOCITY);
			}*/
			/* scatter, dome - shape
			Color color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			for (int i = 0; i < 100; i++) {
				float angle = GetRandomFloatValue(180, 360);
				Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(-30, 30)) * DEG2RAD), GetRandomFloatValue(10, 30) * i/2);
				ncBody* body = CreateBody();
				body->color = color;
				body->position = position;
				body->mass = GetRandomFloatValue(1, 10);
				body->inverseMass = 1 / body->mass;
				body->type = DYNAMIC;
				body->damping = 1.5f;
				body->gravityScale = 5;
				ApplyForce(body, force, VELOCITY);
			}*/

			//shower
			Color color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			for (int i = 0; i < 100; i++) {
				float angle = GetRandomFloatValue(0, 360);
				//Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(0, 180)) * DEG2RAD), GetRandomFloatValue(10, 30) * i / 2);
				//now fire horizontally

				ncBody* body = CreateBody();
				body->color = color;
				body->position = position;
				body->mass = GetRandomFloatValue(1, 10);
				body->inverseMass = 1 / body->mass;
				body->type = DYNAMIC;
				body->damping = 1.0f;
				body->gravityScale = 100;
				Vector2 force = createVector2(GetRandomFloatValue(0, 100) * (i % 2 == 0 ? -1 : 1) * i / 10, GetRandomFloatValue(-200, -50) - i);
				ApplyForce(body, force, VELOCITY);
			}

		}

		//apply force
		ncBody* body = ncBodies;
		while (body)
		{
			body = body->next;
		}

		//update bodies
		for (ncBody* body = ncBodies; body; body = body->next) {
			Step(body, dt);
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
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, body->color);

			//trail
			if (body->prev) {
				Vector2 min = Vector2Subtract(body->position, createVector2(30, 30));
				Vector2 max = Vector2Add(body->position, createVector2(30, 30));
				DrawLineV(body->position, Vector2Clamp(Vector2Subtract(body->position, body->velocity), min, max), Fade(body->color, 0.5f));
			}


			ClearForce(body);
			body = body->next;
		}

		EndDrawing();
	}

	CloseWindow();
	free(ncBodies);
	return 0;
}