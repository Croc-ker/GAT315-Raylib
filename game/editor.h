#pragma once
#include "raylib.h"

typedef struct ncEditorData {
	Vector2 anchor01;
	Vector2 anchor02;
	Vector2 anchor03;

	//editor
	bool EditorBoxActive;
	bool MouseOnEditor;

	//body
	bool BodyTypeEditMode;
	int BodyTypeActive;
	float MassValue;
	float DampingValue;
	float GravityScaleValue;
	float RestitutionValue;
	float StiffnessValue;

	//world
	float GravityValue;
	float GravitationValue;
	float TimestepValue;

	//display
	bool ResetPressed;
	bool MassDisplayEditMode;
	int MassDisplayValue;
	bool DampingDisplayEditMode;
	int DampingDisplayValue;
	bool GravityScaleDisplayEditMode;
	int GravityScaleDisplayValue;
	bool StiffnessDisplayEditMode;
	int StiffnessDisplayValue;
	bool RestitutionDisplayEditMode;
	int RestitutionDisplayValue;
	bool GravityDisplayEditMode;
	int GravityDisplayValue;
	bool GravitationDisplayEditMode;
	int GravitationDisplayValue;
	bool TimestepDisplayEditMode;
	int TimestepDisplayValue;
	bool SimulateChecked;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();

struct ncBody* GetBodyIntersect(struct ncBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct ncBody* body, Vector2 position);