#ifndef RU_HPP
#define RU_HPP
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
const double eps = 1e-8;
const double PI = acos(-1.0);
int sgn(double x) {
    if (fabs(x) < eps) {
        return 0;
    }
    return (x < 0) ? -1 : 1;
}
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}
Vector operator * (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}
Vector operator / (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}
bool operator < (const Point A, const Point B) {
    return A.x < B.x || (sgn(A.x - B.x) == 0 && A.y < B.y);
}
bool operator == (const Point A, const Point B) {
    return sgn(A.x - B.x) == 0 && sgn(A.y - B.y) == 0;
}
double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
double Length(Vector A) {
    return sqrt(Dot(A, A));
}
double Angle(Vector A, Vector B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}
double AreaTriangle(Point A, Point B, Point C) {
    return fabs(Cross(B - A, C - A)) / 2;
}
Vector Rotate(Vector A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Normal(Vector A) {
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}
Point GetLineProjection(Point P, Point A, Point B) {
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}
double DistanceToSegment(Point P, Point A, Point B) {
    if (sgn(Dot(P - A, B - A)) < 0) {
        return Length(P - A);
    }
    if (sgn(Dot(P - B, A - B)) < 0) {
        return Length(P - B);
    }
    return fabs(Cross(B - A, P - A)) / Length(A - B);
}
bool SegmentProperIntersection(Point A, Point B, Point P, Point Q) {
    double c1 = Cross(B - A, P - A), c2 = Cross(B - A, Q - A);
    double c3 = Cross(Q - P, A - P), c4 = Cross(Q - P, B - P);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
bool OnSegment(Point P, Point A, Point B) {
    return sgn(Cross(A - P, B - P)) == 0 && sgn(Dot(A - P, B - P)) < 0;
}
struct Circle {
    Point O;
    double r;
    Circle(Point O, double r): O(O), r(r) {}
    Point point(double a) {
        return Point(O.x + cos(a) * r, O.y + sin(a) * r);
    }
};
int getLineCircleIntersection(Circle C, Point A, Point B, vector<Point>& sol) {
    double a = (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y);
    double b = 2 * (B.x - A.x) * (A.x - C.O.x) + 2 * (B.y - A.y) * (A.y - C.O.y);
    double c = (A.x - C.O.x) * (A.x - C.O.x) + (A.y - C.O.y) * (A.y - C.O.y) - C.r * C.r;
    double delta = b * b - 4 * a * c;
    if (sgn(delta) < 0) {
        return 0;//没有交点
    }
    if (sgn(delta) == 0) {
        double t = -b / (2 * a);
        sol.push_back(A + (B - A) * t);
        return 1;//1个交点
    }
    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
    sol.push_back(A + (B - A) * t1);
    sol.push_back(A + (B - A) * t2);
    return 2;//2个交点
}
double angle(Vector v) {
    return atan2(v.y, v.x);
}//极角：向量与x正半轴的夹角
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
    double d = Length(C1.O - C2.O);
    if (sgn(fabs(C1.r - C2.r) - d) > 0) {
        return 0;//内含，无交点
    }
    if (sgn(C1.r + C2.r - d) < 0) {
        return 0;//外离，无交点
    }
    double a = angle(C2.O - C1.O);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
    if (sgn(da) == 0) {
        sol.push_back(C1.point(a));
        return 1;
    }
    sol.push_back(C1.point(a - da));
    sol.push_back(C1.point(a + da));
    return 2;
}
int getPointCircleTangents(Point P, Circle C, vector<Vector>& v) {//过定点与圆的切线
    Vector u = C.O - P;
    double d = Length(u);
    if (sgn(d - C.r) < 0) {
        return 0;
    }
    if (sgn(d - C.r) == 0) {
        v.push_back(Rotate(u, PI / 2));
        return 1;
    }
    double ang = asin(C.r / d);
    v.push_back(Rotate(u, -ang));
    v.push_back(Rotate(u, ang));
    return 2;
}
int getCircleCircleTangents(Circle C1, Circle C2, vector<Point>& v1, vector<Point>& v2) {
    if (C1.r < C2.r) swap(C1, C2), swap(v1, v2);
    double d = Length(C1.O - C2.O);
    double rdiff = C1.r - C2.r, rsum = C1.r + C2.r;//半径之和与半径之差
    if (sgn(d - rdiff) < 0) return 0;//内含
    if (sgn(d) == 0 && sgn(C1.r - C2.r) == 0) return -1;//重合
    double base = angle(C2.O - C1.O);
    if (sgn(d - rdiff) == 0) {//两圆内切，切点是圆与圆心连线的交点
        v1.push_back(C1.point(base));
        v2.push_back(C2.point(base));
        return 1;
    }
    double ang = acos(rdiff / d);
    v1.push_back(C1.point(base + ang));
    v2.push_back(C2.point(base + ang));
    v1.push_back(C1.point(base - ang));
    v2.push_back(C2.point(base - ang));
    if (sgn(d - rsum) < 0) return 2; // 两圆相交
    if (sgn(d - rsum) == 0) {
        v1.push_back(C1.point(base));
        v2.push_back(C2.point(PI + base));
        return 3;
    }
    ang = acos(rsum / d);
    v1.push_back(C1.point(base + ang));
    v2.push_back(C2.point(PI + base + ang));
    v1.push_back(C1.point(base - ang));
    v2.push_back(C2.point(PI + base - ang));
    return 4; // 外离，四条公切线。
}
#endif