#include "Collider.hpp"

Collider::Collider(const Rect2DOptions& opt)
    : rect(opt.color, opt.width, opt.height), boundingBox(ga::Color(0.0f, 0.0f, 0.0f, 1.0f), opt.width, opt.height),
        width(opt.width), height(opt.height), rotation(ga::Rotation2D(0.0f)), position(0.0f, 0.0f)
{
    this->points[0] = ga::Vector2<float>(this->position.x - this->width / 2, this->position.y - this->height / 2); // top left
    this->points[1] = ga::Vector2<float>(this->position.x + this->width / 2, this->position.y - this->height / 2); // top right
    this->points[2] = ga::Vector2<float>(this->position.x + this->width / 2, this->position.y + this->height / 2); // bottom right
    this->points[3] = ga::Vector2<float>(this->position.x - this->width / 2, this->position.y + this->height / 2); // bottom left
}

void Collider::setPosition(const ga::Position2D<float>& pos) {
    this->rect.setPosition(pos.x, pos.y);
    this->boundingBox.setPosition(pos.x, pos.y);
    this->position = pos;
    calculatePoints();
}

void Collider::setRotation(const ga::Rotation2D& rotation) {
    this->rect.setRotation(rotation);
    this->rotation = rotation;
    calculatePoints();
}

const bool Collider::isColliding(const Collider& other) {
    // Step 1: We need the min-max points when projected onto each axis
    ga::Angle normal_angles[4] = {
        ga::Angle(other.rotation.angle), ga::Angle(90.0f + other.rotation.angle),
        ga::Angle(this->rotation.angle), ga::Angle(90.0f + this->rotation.angle)
    };

    // First check this collider against other's axes:
    for (int i = 0; i < 4; i++) {
        ga::Matrix2<float> mat(normal_angles[i]);
        ga::Vector2<float> r_points[4] = {
            mat.multiply(points[0]), mat.multiply(points[1]),
            mat.multiply(points[2]), mat.multiply(points[3])
        };
        ga::Vector2<float> o_points[4] = {
            mat.multiply(other.points[0]), mat.multiply(other.points[1]),
            mat.multiply(other.points[2]), mat.multiply(other.points[3])
        };
        // get min and max
        float tmin = r_points[0].x; float tmax = tmin;
        for (int i = 0; i < 4; i++) {
            if (r_points[i].x < tmin)
                tmin = r_points[i].x;
            if (r_points[i].x > tmax)
                tmax = r_points[i].x;
        }
        float omin = o_points[0].x; float omax = omin;
        for (int i = 0; i < 4; i++) {
            if (o_points[i].x < omin)
                omin = o_points[i].x;
            if (o_points[i].x > omax)
                omax = o_points[i].x;
        }
        if (tmax < omin || omax < tmin) {
            return false;
        }
    }
    return true;
}

void Collider::calculatePoints() {
    ga::Matrix2<float> rotationMatrix(ga::Angle(-this->rotation.angle));
    ga::Vector2<float> corners[4];
    // Rotate around center of box:
    corners[0] = rotationMatrix.multiply(ga::Vector2<float>(0.0f - this->width / 2, 0.0f - this->height / 2));
    corners[1] = rotationMatrix.multiply(ga::Vector2<float>(0.0f + this->width / 2, 0.0f - this->height / 2));
    corners[2] = rotationMatrix.multiply(ga::Vector2<float>(0.0f + this->width / 2, 0.0f + this->height / 2));
    corners[3] = rotationMatrix.multiply(ga::Vector2<float>(0.0f - this->width / 2, 0.0f + this->height / 2));
    // Set position according to position of box:
    for (int i = 0; i < 4; i++) {
        corners[i].x += this->position.x; corners[i].y += this->position.y;
        this->points[i] = corners[i];
    }
}

void Collider::printPoints() const {
    std::cout << "Points: (" << points[0].x << ", " << points[0].y << "), (" << points[1].x << ", " << points[1].y << "), ("
        << points[2].x << ", " << points[2].y << "), (" << points[3].x << ", " << points[3].y << ")\n";
}