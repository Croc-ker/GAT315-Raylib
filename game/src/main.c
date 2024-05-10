#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"
#include "force.h"
#include "editor.h"
#include "render.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void) {
	InitWindow(1280, 720, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		ncGravity = createVector2(0, -1);


		Vector2 position = GetMousePosition();
		ncScreenZoom -= GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10.0f);
		UpdateEditor(position);
		if (IsMouseButtonPressed(0)) {
			Color color = ColorFromHSV(GetRandomFloatValue(0, 360), 1, 1);
			for (int i = 0; i < 10; i++) {
				float angle = GetRandomFloatValue(0, 360);
				Vector2 force = Vector2Scale(GetVector2FromAngle((angle + GetRandomFloatValue(-60, 60)) * DEG2RAD), GetRandomFloatValue(150, 300));
				ncBody* body = CreateBody();
				body->color = color;
				body->position = ConvertScreenToWorld(position);
				body->mass = GetRandomFloatValue(ncEditorData.MassMinSliderValue, ncEditorData.MassMaxSliderValue);
				body->inverseMass = 1 / body->mass;
				body->type = ncEditorData.BodyTypeSelected;
				body->damping = ncEditorData.BodyDampingValue;
				body->gravityScale = ncEditorData.GravitySliderValue;
				ApplyForce(body, force, VELOCITY);
			}
		}

		//apply force
		ApplyGravitation(ncBodies, ncEditorData.GravitationSliderValue);
		

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
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), body->color);
		}

		DrawEditor();
		EndDrawing();
	}

	CloseWindow();
	free(ncBodies);
	return 0;
}