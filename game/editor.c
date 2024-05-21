#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;

ncEditorData_t ncEditorData;

Vector2 anchor01 = { 800, 24 };
Vector2 anchor02 = { 820, 72 };
Vector2 anchor03 = { 820, 336 };
Texture2D cursorTexture;

bool WindowBox000Active = true;

void InitEditor() {
    GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

    Image i = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(i);
    UnloadImage(i);
    HideCursor();

    ncEditorData.anchor01 = (Vector2){ 808, 24 };
    ncEditorData.anchor02 = (Vector2){ 816, 72 };
    ncEditorData.anchor03 = (Vector2){ 816, 264 };
    editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 304, 616 };


    //body
    ncEditorData.EditorBoxActive = true;
    ncEditorData.BodyTypeEditMode = false;
    ncEditorData.BodyTypeActive = 0;
    ncEditorData.MassValue = 5.0f;
    ncEditorData.DampingValue = 0.0f;
    ncEditorData.GravityScaleValue = 100.0f;
    ncEditorData.RestitutionValue = 0.0f;
    ncEditorData.StiffnessValue = 0.0f;


    //world
    ncEditorData.GravityValue = 0.0f;
    ncEditorData.GravitationValue = 0.0f;
    ncEditorData.TimestepValue = 1.0f;
}

void UpdateEditor(Vector2 position) {
    //
}

void DrawEditor(Vector2 position) {
    if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (ncEditorData.EditorBoxActive) {
        ncEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + -16, ncEditorData.anchor01.y + 0, 288, 656 }, "Editor");
        GuiGroupBox((Rectangle) { anchor02.x + -10, anchor02.y + 0, 250, 240 }, "Body");
        if (GuiDropdownBox((Rectangle) { anchor02.x + 40, anchor02.y + 24, 160, 24 }, "DYNAMIC;STATIC;KINEMATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 56, 120, 16 }, "Mass", NULL, & ncEditorData.MassValue, 0.5, 10);
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 80, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 104, 120, 16}, "Gravity Scale", NULL, & ncEditorData.GravityScaleValue, 0, 20);
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 128, 120, 16 }, "Stiffness", NULL, & ncEditorData.StiffnessValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 152, 120, 16 }, "Restitution", NULL, & ncEditorData.RestitutionValue, 0, 10);

        GuiGroupBox((Rectangle) { anchor03.x + -10, anchor03.y + 0, 250, 288 }, "World");
        GuiSlider((Rectangle) { anchor03.x + 80, anchor03.y + 32, 120, 16 }, "Gravity", NULL, & ncEditorData.GravityValue, -1, 1);
        GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 56, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, -10, 10);
        GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 80, 120, 16 }, "Timestep", NULL, & ncEditorData.TimestepValue, 0, 2);
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, GREEN);

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