#pragma once

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;

class Point {
public:
    double x, y, z;
    Point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point(double x, double y) {
        this->x = x;
        this->y = y;
        this->z = 0;
    }

    double operator[](int i) const {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        return this->z;
    }

    double& operator[](int i) {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        return this->z;
    }
};

/* Matrix stuff*/

Matrix dot(const Matrix& a, const Matrix& b) {
    Matrix result = Matrix(a.size(), Vector(b[0].size(), 0));   // Need to check if a_cols = b_cols
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

Point myTransform(const Matrix& matrix, const Point& point) {
    Matrix p = { {point.x}, {point.y}, {point.z} };
    Matrix r = dot(matrix, p);
    return Point(r[0][0], r[1][0], r[2][0]);
}

Point myTranslate(const Point& shift, const Point& point) {
    return Point(
        point.x + shift.x,
        point.y + shift.y,
        point.z + shift.z
    );
}


Point transform(const Matrix& matrix, const Point& point) {
    Matrix p = { {point.x}, {point.y}, {point.z} };
    Matrix r = dot(matrix, p);
    return Point(r[0][0], r[1][0], r[2][0]);
}

Point translate(const Point& shift, const Point& point) {
    return Point(
        point.x + shift.x,
        point.y + shift.y,
        point.z + shift.z
    );
}

Matrix getRotationMatrix(double alpha, double beta, double gamma) {

    Matrix rotationX = {
        {1, 0, 0},
        {0, cos(alpha), -sin(alpha)},
        {0, sin(alpha), cos(alpha)}
    };


    Matrix rotationY = {
        {cos(beta), 0, sin(beta)},
        {0, 1, 0},
        {-sin(beta), 0, cos(beta)}
    };


    Matrix rotationZ = {
        {cos(gamma), -sin(gamma), 0},
        {sin(gamma), cos(gamma), 0},
        {0, 0, 1}
    };

    return dot(rotationZ, dot(rotationY, rotationX)); //WTF!
}
