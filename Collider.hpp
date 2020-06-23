#pragma once
#include <GaiaGL/Graphics.h>
#include <GaiaGL/System.h>

struct Rect2DOptions {
    ga::Color color;
    float width, height;
};

class Collider {
    public:
    Collider() = delete;
    Collider(const Rect2DOptions& opt);
    void setPosition(const ga::Position2D<float>& pos);
    void setRotation(const ga::Rotation2D& rotation);
    const bool isColliding(const Collider& other);
    void calculatePoints();

    void printPoints() const;

    public:
    ga::Rect2D rect, boundingBox;
    float width, height;
    ga::Rotation2D rotation;
    ga::Position2D<float> position;
    ga::Vector2<float> points[4];
    ga::Vector2<float> ro_points[4];
};