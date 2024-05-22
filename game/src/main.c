#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "integrator.h"
#include "world.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include "spring.h"
#include "collision.h"
#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <mathf.h>

int main(void) {
	ncBody* selectedBody = NULL;
	ncBody* connectBody = NULL;

	InitWindow(1280, 720, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);
	float fixedTimestep = 1.0f / ncEditorData.TimestepValue;
	float timeAccumulator = 0.0f;

	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		fixedTimestep = 1.0f / ncEditorData.TimestepValue;

		//initialize world
		ncGravity = (Vector2){ 0, -ncEditorData.GravityValue };

		Vector2 position = GetMousePosition();
		ncScreenZoom -= GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(position);

		ncGravity = (Vector2){ 0, -ncEditorData.GravityValue };

		if (IsKeyPressed(KEY_E)) ncEditorData.EditorBoxActive = !ncEditorData.EditorBoxActive;
		if (ncEditorData.ResetPressed) {
			DestroyAllBodies();
			DestroyAllSprings();
			selectedBody = NULL;
			connectBody = NULL;
		}

		selectedBody = GetBodyIntersect(ncBodies, position);
		if (selectedBody) {
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, YELLOW);
		}
		if (!ncEditorData.MouseOnEditor) {
			//create body
			if ((IsMouseButtonPressed(0))) {
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassValue, ncEditorData.BodyTypeActive);
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->color = PURPLE;
				body->restitution = ncEditorData.RestitutionValue;
				AddBody(body);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody, position);
			if (IsKeyDown(KEY_SPACE) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) {

				Vector2 spring = Vector2Subtract(ConvertScreenToWorld(position), connectBody->position);
				Vector2 damping = Vector2Scale(connectBody->velocity, -ncEditorData.DampingValue);
				spring = Vector2Add(spring, damping);

				ApplyForce(connectBody, spring, FORCE);

			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
				if (selectedBody && selectedBody != connectBody) {
					ncSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), ncEditorData.StiffnessValue);
					AddSpring(spring);
				}
			}
		}


		ncContact_t* contacts = NULL;
		timeAccumulator += dt;
		while (timeAccumulator >= fixedTimestep) {
			timeAccumulator -= fixedTimestep;
			if (!ncEditorData.SimulateChecked) continue;

			//apply force
			ApplyGravitation(ncBodies, ncEditorData.GravitationValue);
			ApplySpringForce(ncSprings);

			//update bodies
			for (ncBody* body = ncBodies; body; body = body->next) {
				Step(body, fixedTimestep);
			}

			//collision
			CreateContacts(ncBodies, &contacts);
			SeparateContacts(contacts);
			ResolveContacts(contacts);
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);




		//draw springs
		for (ncSpring_t* spring = ncSprings; spring; spring = spring->next) {
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, SKYBLUE);
		}

		//draw bodies
		for (ncBody* body = ncBodies; body; body = body->next) {
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}

		//draw contacts
		for (ncContact_t* contact = contacts; contact; contact = contact->next) {
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), MAGENTA);
		}

		DrawEditor(position);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000 / fps), 10, 10, 20, PINK);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, PURPLE);
		EndDrawing();
	}
	CloseWindow();
	free(ncBodies);

	return 0;
}