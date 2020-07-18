#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include <initializer_list>
#include <algorithm>
#include <Color/Color.h>
#include <Vector/Vector.h>

#define PI 3.14159265358979323846

using namespace std;

//父类：所有图形
class Figure
{
    public:
        //图形的共有属性
        typedef struct Attribute
        {
            Color color;
            double roundedRadius;
            double annularRadius;
        }Attribute;

        typedef struct
        {
            double xMin;
            double yMin;
            double xMax;
            double yMax; 
        }AABBdata;

    protected:
        Attribute attribute;

        double segmentSDF(Vector& E1, Vector& E2, Vector& P);

    public:
        //构造函数，注意各个子类图形在构造时需调用父类的构造函数
        Figure(Attribute attribute) : attribute(attribute) {}

        virtual ~Figure(){}

        Attribute getAttribute()
        {
            return attribute;
        }

        //SDF接口
        virtual double SDF(Vector pos) = 0;
        virtual AABBdata AABB() = 0;

        double tSDF(Vector pos);
        AABBdata tAABB();
};

//圆，继承图形
class Circle : public Figure
{
    private:
        Vector center;      //圆心
        double radius;       //半径

    public:
        //构造函数，注意需调用父类构造函数
        Circle(Vector center, double radius, Attribute attribute) :
            center(center),
            radius(radius),
            Figure(attribute) {}

        //实现计算SDF的接口
        double SDF(Vector pos);
        AABBdata AABB();
};

//胶囊，继承图形
class Capsule : public Figure
{
    private:
        Vector endpoint1;       //端点1
        Vector endpoint2;       //端点2
        double radius;           //半径

    public:
        Capsule(Vector endpoint1, Vector endpoint2, double radius, Attribute attribute) :
            endpoint1(endpoint1),
            endpoint2(endpoint2),
            radius(radius),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

class UnevenCapsule : public Figure
{
    private:
        Vector endpoint1;
        Vector endpoint2;
        double radius1;
        double radius2;

    public:
        UnevenCapsule(Vector endpoint1, Vector endpoint2, double radius1, double radius2, Attribute attribute) : Figure(attribute)
        {
            if (radius1 > radius2)
            {
                this->endpoint1 = endpoint1;
                this->endpoint2 = endpoint2;
                this->radius1 = radius1;
                this->radius2 = radius2;
            }
            else
            {
                this->endpoint1 = endpoint2;
                this->endpoint2 = endpoint1;
                this->radius1 = radius2;
                this->radius2 = radius1;
            }
        }

        double SDF(Vector pos);
        AABBdata AABB();
};

class Rectangle : public Figure
{
    private:
        Vector center;
        Vector size;
        double theta;

    public:
        Rectangle(Vector center, Vector size, double theta, Attribute attribute) :
            center(center),
            size(size),
            theta(theta / 180 * PI),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

class Triangle : public Figure
{
    private:
        Vector vertex1;
        Vector vertex2;
        Vector vertex3;

    public:
        Triangle(Vector vertex1, Vector vertex2, Vector vertex3, Attribute attribute) :
            vertex1(vertex1),
            vertex2(vertex2),
            vertex3(vertex3),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

class Pie : public Figure
{
    private:
        Vector center;
        double radius;
        double theta1;
        double theta2;

    public:
        Pie(Vector center, double radius, double theta1, double theta2, Attribute attribute) :
            center(center),
            radius(radius),
            theta1(theta1 / 180 * PI),
            theta2(theta2 / 180 * PI),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

class Arc : public Figure
{
    private:
        Vector center;
        double radius1;
        double radius2;
        double theta1;
        double theta2;

    public:
        Arc(Vector center, double radius1, double radius2, double theta1, double theta2, Attribute attribute) :
            center(center),
            radius1(radius1),
            radius2(radius2),
            theta1(theta1 / 180 * PI),
            theta2(theta2 / 180 * PI),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

class Polygon : public Figure
{
    private:
        Vector* vertex;
        int vertexNumber;

    public:
        Polygon(initializer_list<Vector> vertexes, Attribute attribute) : Figure(attribute)
        {
            vertexNumber = vertexes.end() - vertexes.begin();
            vertex = new Vector[vertexNumber];
            memcpy(vertex, vertexes.begin(), vertexNumber * sizeof(Vector));
        }

        double SDF(Vector pos);
        AABBdata AABB();
};

class Ellipse : public Figure
{
    private:
        Vector center;
        double a;
        double b;
        double theta;

    public:
        Ellipse(Vector center, double a, double b, double theta, Attribute attribute) :
            center(center),
            a(a), b(b),
            theta(theta / 180 * PI),
            Figure(attribute) {}
        
        double SDF(Vector pos);
        AABBdata AABB();
};

class QuadraticBezier : public Figure
{
    private:
        Vector A;
        Vector B;
        Vector C;

    public:
        QuadraticBezier(Vector A, Vector B, Vector C, Attribute attribute) :
            A(A), B(B), C(C),
            Figure(attribute) {}

        double SDF(Vector pos);
        AABBdata AABB();
};

#endif