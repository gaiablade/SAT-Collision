#include <iostream>

#include <GaiaGL/Graphics.h>
#include <GaiaGL/System.h>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "Collider.hpp"

const float w = 800.0f;
const float h = 600.0f;

int main() {
    ga::Window window(w, h, "Collision");

    Rect2DOptions opt1 { ga::Color(1.0f, 0.0f, 0.0f, 1.0f), 250.0f, 250.0f };
    Rect2DOptions opt2 { ga::Color(0.0f, 0.0f, 1.0f, 1.0f), 250.0f, 250.0f };

    Collider pink = Collider(opt1);
    Collider blue = Collider(opt2);

    blue.setPosition(ga::Position2D<float>(w/2 + 500, h/2));
    blue.setRotation(ga::Rotation2D(10.0f));

    pink.setPosition(ga::Position2D<float>(w/2, h/2));

    pink.setRotation(ga::Rotation2D(30.0f));

    auto coll = pink.isColliding(blue);

    ga::Rect2D c1(ga::Color(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);
    ga::Rect2D c2(ga::Color(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);
    ga::Rect2D c3(ga::Color(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);
    ga::Rect2D c4(ga::Color(0.0f, 0.0f, 0.0f, 1.0f), 10.0f, 10.0f);

    float rotation1 = 0.0f;
    float rotation2 = 0.0f;
    float position1 = 100.0f;
    float position2 = 100.0f;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    while (window.isOpen()) {
        pink.setPosition(ga::Position2D<float>(position1, h/2));
        blue.setPosition(ga::Position2D<float>(position2, h/2));
        pink.setRotation(ga::Rotation2D(rotation1));
        blue.setRotation(ga::Rotation2D(rotation2));

        if (pink.isColliding(blue)) {
            pink.rect.setColor(ga::Color(1.0f, 1.0f, 1.0f, 1.0f));
        }
        else {
            pink.rect.setColor(ga::Color(1.0f, 0.0f, 0.0f, 1.0f));
        }

        c1.setPosition(pink.ro_points[0].x, pink.ro_points[0].y);
        c2.setPosition(pink.ro_points[1].x, pink.ro_points[1].y);
        c3.setPosition(pink.ro_points[2].x, pink.ro_points[2].y);
        c4.setPosition(pink.ro_points[3].x, pink.ro_points[3].y);
        window.getRenderer().Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello World");
        ImGui::SliderFloat("Position1", &position1, 0.0f, w);
        ImGui::SliderFloat("Position2", &position2, 0.0f, w);
        ImGui::SliderFloat("Rotation1", &rotation1, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation2", &rotation2, 0.0f, 360.0f);
        ImGui::Text("This: (%.3f, %.3f) , Other: (%.3f, %.3f)", pink.points[0].x, pink.points[1].x, blue.points[0].x, blue.points[1].x);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //window.getRenderer().Draw(pink.boundingBox);
        window.getRenderer().Draw(pink.rect);
        //window.getRenderer().Draw(blue.boundingBox);
        window.getRenderer().Draw(blue.rect);
        window.getRenderer().Draw(c1);
        window.getRenderer().Draw(c2);
        window.getRenderer().Draw(c3);
        window.getRenderer().Draw(c4);
        window.Draw();
        window.Poll();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
