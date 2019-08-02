#ifndef COMP6771_ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define COMP6771_ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <assert.h>
#include <sstream>
#include <math.h>
#include <utility>


class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors:
  explicit EuclideanVector(int i) noexcept;
  EuclideanVector(int i, double d) noexcept;
  EuclideanVector(std::vector<double>::const_iterator begin, std::vector<double>\
      ::const_iterator end) noexcept;
  EuclideanVector(const EuclideanVector& o) noexcept;
  EuclideanVector(EuclideanVector&& o) noexcept;

  // Operators:
  EuclideanVector& operator=(const EuclideanVector&o) noexcept;
  EuclideanVector& operator=(EuclideanVector&&o) noexcept;
  double& operator[](int i) noexcept;
  const double& operator[](int i) const noexcept;
  EuclideanVector& operator+=(const EuclideanVector& a);
  EuclideanVector& operator-=(const EuclideanVector& a);
  EuclideanVector& operator*=(double a) noexcept;
  EuclideanVector& operator/=(double a);
  explicit operator std::vector<double>() noexcept;
  explicit operator std::list<double>() noexcept;


  // Friends:
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept;
  friend bool operator==(const EuclideanVector& a, const EuclideanVector& b) noexcept;
  friend bool operator!=(const EuclideanVector& a, const EuclideanVector& b) noexcept;
  friend EuclideanVector operator+(const EuclideanVector& a, const EuclideanVector& b);
  friend EuclideanVector operator-(const EuclideanVector& a, const EuclideanVector& b);
  friend double operator*(const EuclideanVector& a, const EuclideanVector& b);
  friend EuclideanVector operator*(const EuclideanVector& a, double b) noexcept;
  friend EuclideanVector operator*(double a, const EuclideanVector& b) noexcept;
  friend EuclideanVector operator/(const EuclideanVector& a, double b);

  // Methods:
  double at(int i) const;
  double& at(int i);
  int GetNumDimensions() noexcept;
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm();
  EuclideanVector CreateUnitVector();

 private:
  std::unique_ptr<double[]> magnitudes_;
  int dimension;
};
#endif  // COMP6771_ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
