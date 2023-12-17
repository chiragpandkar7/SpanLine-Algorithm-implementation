#pragma once
class Point2D
{
public:
    Point2D();
    Point2D(float inX, float inY);
    ~Point2D();

    float x();
    float y();

    void setX(float x);
    void setY(float y);

private:
    float mX;
    float mY;
};