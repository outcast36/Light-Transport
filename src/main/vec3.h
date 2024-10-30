#ifndef VEC3_H
#define VEC3_H

class vec3{
    public:
        //Constructors
        vec3();
        vec3(double c1, double c2, double c3);

        //Access elements
        double x() const;
        double y() const;
        double z() const;

        //Vector Operations
        vec3 operator-() const; // returns a new vector
        vec3& operator+=(const vec3& w);
        vec3& operator*=(double t);
        vec3& operator/=(double t);

        double operator[](int i) const; // called internally for some operations with const vector e.g. in += 
        double& operator[](int i); // modifies vector, used for operations *= and /=

        double length() const;
        double length_squared() const;
        
    private:
        double v[3];
};

//Commutative multiplication by scalar
vec3 operator*(const vec3& v, double t);
vec3 operator*(double t, const vec3& v);

vec3 operator*(const vec3& v, const vec3& w); //channelwise multiplication
vec3 operator+(const vec3& v, const vec3& w);
vec3 operator-(const vec3& v, const vec3& w);
vec3 operator/(const vec3& v, double t);

vec3 cross(const vec3& v, const vec3& w);
double dot(const vec3& v, const vec3& w);

#endif /*VEC3_H */