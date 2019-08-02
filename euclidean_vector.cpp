// Coding by HAN LI, Z5176107
#include "assignments/ev/euclidean_vector.h"
#include <ostream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <utility>
#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm

// Constructors:

EuclideanVector::EuclideanVector(int i) noexcept {
  this->dimension = i;
  std::unique_ptr<double[]> ptr {new double[i]};
  for (int j = 0; j < i; j++) {
    ptr[j] = 0.0;
  }
  this->magnitudes_ = std::move(ptr);
}

EuclideanVector::EuclideanVector(int i, double d) noexcept {
  this->dimension = i;
  std::unique_ptr<double[]> ptr {new double[this->dimension]};
  for (int j = 0; j < i; j++) {
    ptr[j] = d;
  }
  this->magnitudes_ = std::move(ptr);
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end) noexcept {
  int i = 0;
  for (auto item = begin; item != end; item++) {
    i += 1;
  }
  std::unique_ptr<double[]> ptr {new double[i]};
  int j = 0;
  for (auto item = begin; item != end; item++) {
    ptr[j] = *item;
    j++;
  }
  this->dimension = i;
  this->magnitudes_ = std::move(ptr);
}


EuclideanVector::EuclideanVector(const EuclideanVector &o) noexcept {
  std::unique_ptr<double[]> ptr {new double[this->dimension]};
  this->dimension = o.dimension;
  for (int i = 0; i < o.dimension; ++i) {
    ptr[i] = o.at(i);
  }
  this->magnitudes_ = std::move(ptr);
}

EuclideanVector::EuclideanVector(EuclideanVector &&o) noexcept {
  this->dimension = o.dimension;
  o.dimension = 0;
  this->magnitudes_ = std::move(o.magnitudes_);
}

// Operators:

EuclideanVector &EuclideanVector::operator=(const EuclideanVector& o) noexcept {
  std::unique_ptr<double[]> ptr {new double[this->dimension]};
  this->dimension = o.dimension;
  for (int i = 0; i < o.dimension; i++) {
    ptr[i] = o.magnitudes_[i];
  }
  this->magnitudes_ = std::move(ptr);
  return *this;
}

EuclideanVector &EuclideanVector::operator=(EuclideanVector && o) noexcept {
  this->dimension = o.dimension;
  o.dimension = 0;
  this->magnitudes_ = std::move(o.magnitudes_);
  return *this;
}

EuclideanVector &EuclideanVector::operator+=(const EuclideanVector& a) {
  if (this->GetNumDimensions() != a.GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  } else {
    double *ptr1 = this->magnitudes_.get();
    double *ptr2 = a.magnitudes_.get();
    std::unique_ptr<double[]> ptr {new double[this->dimension]};  // watch out
    for (int i = 0; i < a.dimension; i++) {
      ptr[i] = *(ptr1 + i) + *(ptr2 + i);
    }
    this->magnitudes_ = std::move(ptr);
  }
  return *this;
}

EuclideanVector &EuclideanVector::operator-=(const EuclideanVector & a) {
  if (this->GetNumDimensions() != a.GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  } else {
    double *ptr1 = this->magnitudes_.get();
    double *ptr2 = a.magnitudes_.get();
    std::unique_ptr<double[]> ptr {new double[this->dimension]};  // watch out
    for (int i = 0; i < a.dimension; i++) {
      ptr[i] = *(ptr1 + i) - *(ptr2 + i);
    }
    this->magnitudes_ = std::move(ptr);
  }
  return *this;
}

EuclideanVector &EuclideanVector::operator*=(double a) noexcept {
  double *value1 = this->magnitudes_.get();
  std::unique_ptr<double[]> ptr {new double[this->dimension]};  // watch out
  for (int i = 0; i < this->dimension; i++) {
    ptr[i] = *(value1 + i) * a;
  }
  this->magnitudes_ = std::move(ptr);
  return *this;
}

EuclideanVector &EuclideanVector::operator/=(double a) {
  if (a == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  double *value1 = this->magnitudes_.get();
  std::unique_ptr<double[]> ptr{new double[this->dimension]};  // watch out
  for (int i = 0; i < this->dimension; i++) {
    ptr[i] = *(value1 + i) / a;
  }
  this->magnitudes_ = std::move(ptr);
  return *this;
}

EuclideanVector::operator std::vector<double>() noexcept {
  std::vector<double> a;
  for (int i = 0; i < this->dimension; i++) {
    a.push_back(this->magnitudes_[i]);
  }
  return a;
}

EuclideanVector::operator std::list<double>() noexcept {
  std::list<double> a;
  for (int i = 0; i < this->dimension; i++) {
    a.push_back(this->magnitudes_[i]);
  }
  return a;
}

double& EuclideanVector::operator[](int i) noexcept  {
  assert(i <= this->dimension && i >= 0);
  return this->magnitudes_[i];
}
const double& EuclideanVector::operator[](int i) const noexcept {
  assert(i <= this->dimension - 1 && i >= 0);
  return this->magnitudes_[i];
}


// Friends:

std::ostream &operator<<(std::ostream &os, const EuclideanVector &v) noexcept {
  if (v.dimension == 0 && v.magnitudes_ == nullptr) {
    return os << "[]";
  }
  std::stringstream output;
  output << "[";
  // find the value of v and format the output as [ x y z ]
  double *value = v.magnitudes_.get();
  for (int i = 0; i < v.dimension - 1; i++) {
    output << *(value + i) << " ";
  }
  output << *(value + v.dimension - 1) << "]";
  os << output.str();
  return os;
}

// when there is 1 element diff, the program should end and return they r not equal.
bool operator==(const EuclideanVector &a, const EuclideanVector &b) noexcept {
  if (a.GetNumDimensions() == b.GetNumDimensions()) {
    for (int i = 0; i < a.GetNumDimensions(); i++) {
      if (a.at(i) != b.at(i)) {
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

// opposite of ==
bool operator!=(const EuclideanVector &a, const EuclideanVector &b) noexcept {
  if (a.GetNumDimensions() == b.GetNumDimensions()) {
    for (int i = 0; i < a.GetNumDimensions(); i++) {
      if (a.at(i) != b.at(i)) {
        return true;
      }
    }
    return false;
  } else {
    return true;
  }
}

EuclideanVector operator+(const EuclideanVector &a, const EuclideanVector &b) {
  if (a.dimension != b.dimension) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector c{a.dimension};
  std::unique_ptr<double[]> ptr{new double[a.dimension]};
  double *ptr1 = a.magnitudes_.get();
  double *ptr2 = b.magnitudes_.get();
  for (int i = 0; i < a.dimension; i ++) {
    ptr[i] = *(ptr1 + i) + *(ptr2 + i);  // add every elements in the vector.
  }
  c.magnitudes_ = std::move(ptr);
  return c;
}

EuclideanVector operator-(const EuclideanVector &a, const EuclideanVector &b) {
  if (a.dimension != b.dimension) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector c{a.dimension};
  std::unique_ptr<double[]> ptr{new double[a.dimension]};
  double *ptr1 = a.magnitudes_.get();
  double *ptr2 = b.magnitudes_.get();
  for (int i = 0; i < a.dimension; i ++) {
    ptr[i] = *(ptr1 + i) - *(ptr2 + i);  // minus every elements in the vector.
  }
  c.magnitudes_ = std::move(ptr);
  return c;
}


double operator*(const EuclideanVector &a, const EuclideanVector &b) {
  if (a.dimension != b.dimension) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  double product = 0;
  for (int i = 0; i < a.GetNumDimensions(); i++) {
    product += a.at(i) * b.at(i);  // time every elements in the vector and get the sum.
  }
  return product;
}

EuclideanVector operator*(const EuclideanVector &a, double b) noexcept {
  std::unique_ptr<double[]> ptr {new double[a.dimension]};
  double *value1 = a.magnitudes_.get();
  for (int i = 0; i < a.dimension; i++) {
    ptr[i] = *(value1 + i) * b;  // make every element time b.
  }
  EuclideanVector result {a.dimension};
  result.magnitudes_ = std::move(ptr);
  return result;
}

EuclideanVector operator*(double a, const EuclideanVector &b) noexcept {
  std::unique_ptr<double[]> ptr {new double[b.dimension]};
  double *value1 = b.magnitudes_.get();
  for (int i = 0; i < b.dimension; i++) {
    ptr[i] = *(value1 + i) * a;  // make every element time a. equals to b * a
  }
  EuclideanVector result {b.dimension};
  result.magnitudes_ = std::move(ptr);
  return result;
}

EuclideanVector operator/(const EuclideanVector &a, double b) {
  if (b == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  std::unique_ptr<double[]> ptr{new double[a.dimension]};
  double *value1 = a.magnitudes_.get();
  for (int i = 0; i < a.dimension; i++) {
    ptr[i] = *(value1 + i) / b;  //  make every element divided by b. equals to a * 1/b
  }
  EuclideanVector result {a.dimension};
  result.magnitudes_ = std::move(ptr);
  return result;
}

// Methods:

double EuclideanVector::at(int i) const {
  if (i < 0 || i > this->dimension) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  double *ptr = this->magnitudes_.get();
  double result = ptr[i];
  return result;
}

double& EuclideanVector::at(int i) {
  if (i < 0 || i > this->dimension) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  double *ptr = this->magnitudes_.get();
  return ptr[i];
}

int EuclideanVector::GetNumDimensions() noexcept {
  int a;
  a = this->dimension;
  return a;
}

int EuclideanVector::GetNumDimensions() const noexcept {
  int a = this->dimension;
  return a;
}

double EuclideanVector::GetEuclideanNorm() {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double Norm = 0;
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    Norm += (this->at(i) * this->at(i));
  }
  return sqrt(Norm);
}

EuclideanVector EuclideanVector::CreateUnitVector() {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  }
  if (this->GetEuclideanNorm() == 0) {
    throw EuclideanVectorError\
    ("EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }
  EuclideanVector UV {this->GetNumDimensions()};
  double *ptr1 = this->magnitudes_.get();
  std::unique_ptr<double[]> ptr{new double[this->dimension]};
  for (int i = 0; i < this->GetNumDimensions(); i++) {
    ptr[i] = *(ptr1 + i) / this->GetEuclideanNorm();
  }
  UV.magnitudes_ = std::move(ptr);
  return UV;
}








