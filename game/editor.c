#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;

ncEditorData_t ncEditorData;

Vector2 anchor01 = { 900, 10 };
bool WindowBox000Active = true;

void InitEditor() {
	GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

	ncEditorData.MassMinSliderValue = 0.1f;
	ncEditorData.MassMaxSliderValue = 1;
	ncEditorData.GravitySliderValue = 0;
	ncEditorData.GravitationSliderValue = 2;
	ncEditorData.BodyDampingValue = 5;
	ncEditorData.BodyTypeSelected = DYNAMIC;
}

void UpdateEditor(Vector2 position) {
	//
}

void DrawEditor() {
	if (ncEditorData.BodyTypeEditMode) GuiLock();
	if (WindowBox000Active) {
		WindowBox000Active = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 288, 696 }, "SAMPLE TEXT");
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 48, 120, 16 }, "Mass Min", NULL, & ncEditorData.MassMinSliderValue, 0, 10);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 72, 120, 16  }, "Mass Max", NULL, & ncEditorData.MassMaxSliderValue, 0, 10);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Gravity", NULL, & ncEditorData.GravitySliderValue, 0, 100);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 96, 120, 16  }, "Gravitation", NULL, & ncEditorData.GravitationSliderValue, 0, 1000);
		GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 144, 120, 16 }, "Body Damping", NULL, & ncEditorData.BodyDampingValue, 0, 100);
		if (GuiDropdownBox((Rectangle) { anchor01.x + 24, anchor01.y + 184, 176, 24 }, "STATIC;KINEMATIC;DYNAMIC", & ncEditorData.BodyTypeSelected, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
		GuiUnlock();
	}
}