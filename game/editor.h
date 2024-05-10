#pragma once
#include "raylib.h"
#include "body.h"

typedef struct ncEditorData {
	float MassMinSliderValue;
	float MassMaxSliderValue;
	float GravitationSliderValue;
	float GravitySliderValue;
	float BodyDampingValue;


	bool BodyTypeEditMode;
	ncBodyType BodyTypeSelected;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;
extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();