#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include <mathf.h>

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;

ncEditorData_t ncEditorData;

Vector2 anchor01 = { 792, 24 };
Vector2 anchor02 = { 816, 72 };
Vector2 anchor03 = { 816, 336 };
Texture2D cursorTexture;

bool WindowBox000Active = true;

void InitEditor() {
	GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

	Image i = LoadImage("resources/reticle.png");
	cursorTexture = LoadTextureFromImage(i);
	UnloadImage(i);
	HideCursor();

	//editor
	ncEditorData.anchor01 = (Vector2){ 808, 24 };
	ncEditorData.anchor02 = (Vector2){ 816, 72 };
	ncEditorData.anchor03 = (Vector2){ 816, 264 };
	editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 312, 688 };
	ncEditorData.EditorBoxActive = true;
	ncEditorData.MouseOnEditor = false;


	//body
	ncEditorData.BodyTypeEditMode = false;
	ncEditorData.BodyTypeActive = 0;
	ncEditorData.MassValue = 5.0f;
	ncEditorData.DampingValue = 0.0f;
	ncEditorData.GravityScaleValue = 0.0f;
	ncEditorData.RestitutionValue = 0.0f;
	ncEditorData.StiffnessValue = 0.0f;

	//world
	ncEditorData.GravityValue = 0.0f;
	ncEditorData.GravitationValue = 0.0f;
	ncEditorData.TimestepValue = 60.0f;

	//display
	ncEditorData.MassDisplayValue = ncEditorData.MassValue;
	ncEditorData.DampingDisplayValue = ncEditorData.DampingValue;
	ncEditorData.GravityScaleDisplayValue = ncEditorData.GravityScaleValue;
	ncEditorData.StiffnessDisplayValue = ncEditorData.StiffnessValue;
	ncEditorData.RestitutionDisplayValue = ncEditorData.RestitutionValue;
	ncEditorData.GravityDisplayValue = ncEditorData.GravityValue;
	ncEditorData.GravitationDisplayValue = ncEditorData.GravitationValue;
	ncEditorData.TimestepDisplayValue = ncEditorData.TimestepValue;
	ncEditorData.ResetPressed = false;
	ncEditorData.MassDisplayEditMode = false;
	ncEditorData.DampingDisplayEditMode = false;
	ncEditorData.GravityScaleDisplayEditMode = false;
	ncEditorData.StiffnessDisplayEditMode = false;
	ncEditorData.RestitutionDisplayEditMode = false;
	ncEditorData.GravityDisplayEditMode = false;
	ncEditorData.GravitationDisplayEditMode = false;
	ncEditorData.TimestepDisplayEditMode = false;
	ncEditorData.SimulateChecked = true;
}

void UpdateEditor(Vector2 position) {
	//ncEditorData.MassDisplayValue =			EDITOR_DATA(ncEditorData.MassValue);
	//ncEditorData.DampingDisplayValue =		EDITOR_DATA(ncEditorData.DampingValue);
	//ncEditorData.GravityScaleDisplayValue = EDITOR_DATA(ncEditorData.GravityScaleValue);
	//ncEditorData.StiffnessDisplayValue =	EDITOR_DATA(ncEditorData.StiffnessValue);
	//ncEditorData.RestitutionDisplayValue =	EDITOR_DATA(ncEditorData.RestitutionValue);
	//ncEditorData.GravityDisplayValue =		EDITOR_DATA(ncEditorData.GravityValue);
	//ncEditorData.GravitationDisplayValue =	EDITOR_DATA(ncEditorData.GravitationValue);
	//ncEditorData.TimestepDisplayValue =		EDITOR_DATA(ncEditorData.TimestepValue);
}

void DrawEditor(Vector2 position) {
	if (ncEditorData.BodyTypeEditMode) GuiLock();

	if (ncEditorData.EditorBoxActive) {
		ncEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + -16, ncEditorData.anchor01.y + 0, 312, 688 }, "Editor");
		GuiGroupBox((Rectangle) { anchor02.x + 0, anchor02.y + 0, 264, 232 }, "Body");
		if (GuiDropdownBox((Rectangle) { anchor02.x + 40, anchor02.y + 24, 160, 24 }, "DYNAMIC;STATIC;KINEMATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
		GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 56, 120, 16 }, "Mass", NULL, & ncEditorData.MassValue, 0.5, 20);
		GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 80, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 10);
		GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 104, 120, 16 }, "Gravity Scale", NULL, & ncEditorData.GravityScaleValue, 0, 20);
		GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 128, 120, 16 }, "Stiffness", NULL, & ncEditorData.StiffnessValue, 0, 10);
		GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 152, 120, 16 }, "Restitution", NULL, & ncEditorData.RestitutionValue, 0, 2);

		GuiGroupBox((Rectangle) { anchor03.x + 0, anchor03.y + 0, 264, 288 }, "World");
		GuiSlider((Rectangle) { anchor03.x + 80, anchor03.y + 32, 120, 16 }, "Gravity", NULL, & ncEditorData.GravityValue, -1, 1);
		GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 56, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, -10, 10);
		GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 80, 120, 16 }, "Timestep", NULL, & ncEditorData.TimestepValue, 0, 120);

		//display
		//if (GuiDropdownBox((Rectangle) { anchor02.x + 40, anchor02.y + 24, 160, 24 }, "DYNAMIC;STATIC;KINEMATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
		GuiLabel((Rectangle) { anchor02.x + 208, anchor02.y + 56, 48, 16 },		EDITOR_DATA(ncEditorData.MassValue));
		GuiLabel((Rectangle) { anchor02.x + 208, anchor02.y + 80, 48, 16 },		EDITOR_DATA(ncEditorData.DampingValue));
		GuiLabel((Rectangle) { anchor01.x + 232, anchor01.y + 152, 48, 16 },		EDITOR_DATA(ncEditorData.GravityScaleValue));
		GuiLabel((Rectangle) { anchor01.x + 232, anchor01.y + 176, 48, 16 },		EDITOR_DATA(ncEditorData.StiffnessValue));
		GuiLabel((Rectangle) { anchor01.x + 232, anchor01.y + 200, 48, 16 },		EDITOR_DATA(ncEditorData.RestitutionValue));
		GuiLabel((Rectangle) { anchor03.x + 208, anchor03.y + 32, 48, 16 },		EDITOR_DATA(ncEditorData.GravityValue));
		GuiLabel((Rectangle) { anchor03.x + 208, anchor03.y + 56, 48, 16 },		EDITOR_DATA(ncEditorData.GravitationValue));
		GuiLabel((Rectangle) { anchor03.x + 208, anchor03.y + 80, 48, 16 },		EDITOR_DATA(ncEditorData.TimestepValue));

		ncEditorData.ResetPressed = GuiButton((Rectangle) { anchor01.x + 24, anchor01.y + 648, 120, 24 }, "Reset");
		GuiCheckBox((Rectangle) { anchor01.x + 168, anchor01.y + 648, 24, 24 }, "Simulate", & ncEditorData.SimulateChecked);
	}

	DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, GREEN);
	ncEditorData.MouseOnEditor = CheckCollisionPointRec(position, editorRect);

	GuiUnlock();
}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position) {
	for (ncBody* body = bodies; body; body = body->next) {
		Vector2 screen = ConvertWorldToScreen(body->position);
		if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f))) {
			return body;
		}
	}
	return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position) {
	Vector2 screen = ConvertWorldToScreen(body->position);
	DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}