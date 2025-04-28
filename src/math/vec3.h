#ifndef VEC3_H
#define VEC3_H

template <typename T> class vec3 {
 public:
  //Constructors
  vec3();
  vec3(T c1, T c2, T c3);

  //Access elements
  T x() const;
  T y() const;
  T z() const;

  //Vector Operations
  vec3 operator-() const; // returns a new vector
  vec3& operator+=(const vec3& w);
  vec3& operator*=(T t);
  vec3& operator/=(T t);
  T operator[](int i) const; // called internally for some operations with const vector e.g. in += 
  T& operator[](int i); // modifies vector, used for operations *= and /=
  T length() const;
  T lengthSquared() const;

 private:
  T v[3];
};

//Commutative multiplication by scalar
template <typename T> vec3<T> operator*(const vec3<T>& v, T t);
template <typename T> vec3<T> operator*(T t, const vec3<T>& v);

template <typename T> vec3<T> operator*(const vec3<T>& v, const vec3<T>& w); //channelwise multiplication
template <typename T> vec3<T> operator+(const vec3<T>& v, const vec3<T>& w);
template <typename T> vec3<T> operator-(const vec3<T>& v, const vec3<T>& w);
template <typename T> vec3<T> operator/(const vec3<T>& v, T t);

template <typename T> vec3<T> cross(const vec3<T>& v, const vec3<T>& w);
template <typename T> T dot(const vec3<T>& v, const vec3<T>& w);
template <typename T> vec3<T> unitVector(const vec3<T>& v);

#endif /* VEC3_H */