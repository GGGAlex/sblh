// coding by HAN LI, z5176107
/*

  == Explanation and rational of testing ==
  1) I need to make sure that the class should be run properly, so the first
  part is to check Vector could be created successfully;
  2) I need to make sure that operator << could run properly because with << I
  can easilly check the Vector and figure out what is wrong;
  3) I choose to test methods because methods would not have too much trouble and
  methods would be impossible bo use operators in this class;
  4) I choose to test operators in the right input way because it can be shown clearly;
  5) The last part is the exceptions and exceptions just need few words because it could
  raise properly in the clent.cpp and tell me what is wrong of my code, so it is
  most impossible part that have something wrong.

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include <iostream>
#include <string>
#include "assignments/ev/euclidean_vector.h"
#include "catch.h"


TEST_CASE("Create Euclidean Vector.") {
  EuclideanVector a(2);
  std::vector<double> l{1, 2, 3};
  EuclideanVector b{l.begin(), l.end()};
  EuclideanVector c(4, 5.5);
  EuclideanVector aCopy{a};
  //  test vectors dimension
  REQUIRE(a.GetNumDimensions() == 2);
  REQUIRE(b.GetNumDimensions() == 3);
  REQUIRE(c.GetNumDimensions() == 4);
}

TEST_CASE("The success of operator<<") {
  std::stringstream os;
  EuclideanVector a{5};
  os << a;
  REQUIRE(os.str() == "[0 0 0 0 0]");
  /*
 * when this section is proved done,
 * it means i can use << and os to get output.
   */
}

TEST_CASE("test the methods") {
  //  test the wrong use of GetEuclideanNorm()
  EuclideanVector a(5);
  EuclideanVector b{9, 1};
  std::vector<double> l{1, 2 , 4 , 8};
  EuclideanVector c{l.begin(), l.end()};
  std::vector<double> l1{3, 4};
  EuclideanVector d{l1.begin(), l1.end()};

  //  test the use of GetEuclideanNorm()
  REQUIRE(b.GetEuclideanNorm() == 3);
  //  test the use of at()
  REQUIRE(c.at(3) == 8);
  /*  the test of ths use of GetNumDimensions is done in first section to prove
   * euclidean Vector can be created properly.
   * test of CreateUnitVector()
   */
  std::stringstream os;
  os << d.CreateUnitVector();
  REQUIRE(os.str() == "[0.6 0.8]");
  REQUIRE_THROWS_AS(a.CreateUnitVector(), EuclideanVectorError);
}

TEST_CASE("the success of operators") {
  std::vector<double> a1{5, 4, 3, 2, 1};
  EuclideanVector a{a1.begin(), a1.end()};
  EuclideanVector d{a1.begin(), a1.end()};

  std::vector<double> a2{9, 0, 8, 6, 7};
  EuclideanVector e{a2.begin(), a2.end()};

  EuclideanVector f{5};


  // test of ==
  REQUIRE((a == d) == true);
  // test of !=
  REQUIRE((a != e) == true);
  // test of +=
  std::stringstream os1;
  d += a;
  os1 << d;
  REQUIRE(os1.str() == "[10 8 6 4 2]");
  // test of -=
  std::stringstream os2;
  d -= e;
  os2 << d;
  REQUIRE(os2.str() == "[1 8 -2 -2 -5]");
  // test of *=
  std::stringstream os3;
  d *= 2;
  os3 << d;
  REQUIRE(os3.str() == "[2 16 -4 -4 -10]");
  // test of /=
  std::stringstream os4;
  d /= 2;
  os4 << d;
  REQUIRE(os4.str() == "[1 8 -2 -2 -5]");
  //  this is not a good choice to have 2 same output in 1 section.
  // test of +
  std::stringstream os5;
  e = d + a;
  os5 << e;
  REQUIRE(os5.str() == "[6 12 1 0 -4]");
  // test of -
  f = e - a;
  REQUIRE(f == d);
  // test of * (1)
  double i = e * a;
  REQUIRE(i == 77);
  // test of * (2)
  EuclideanVector g{5};
  EuclideanVector h{5};
  std::stringstream os6;
  g = a * 4;
  os6 << g;
  REQUIRE(os6.str() == "[20 16 12 8 4]");
  // test of * (3)
  h = a * 4;
  REQUIRE(g == h);
  // test of /
  h = g / 2.5;
  std::stringstream os7;
  os7 << h;
  REQUIRE(os7.str() == "[8 6.4 4.8 3.2 1.6]");
  // test of = was test because of the use of it shows the success of test of others;
  // test of std::list<double>
  std::stringstream os8;
  auto list1 = std::list<double>{a};
  for (auto item : list1) {
    os8 << item << " ";
  }
  REQUIRE(os8.str() == "5 4 3 2 1 ");
  // test of std::vector<double>
  std::vector<double> v2{4, 5, 6, 7};
  EuclideanVector c{v2.begin(), v2.end()};
  std::stringstream os9;
  auto vector1 = std::vector<double>{c};
  for (auto item : vector1) {
    os9 << item << " ";
  }
  REQUIRE(os9.str() == "4 5 6 7 ");
  // test of operator[]
  auto element = c[3];
  REQUIRE(element == 7);
}

TEST_CASE("Exceptions") {
  std::vector<double> a1{5, 4, 3, 2, 1};
  EuclideanVector a{a1.begin(), a1.end()};
  EuclideanVector d{a1.begin(), a1.end()};

  std::vector<double> a2{9, 0, 8, 6, 7};
  EuclideanVector e{a2.begin(), a2.end()};

  EuclideanVector f{4};
  EuclideanVector wrong{0};
  // the exception caused by diff dimension:
  double jl;
  REQUIRE_THROWS_AS((a += f), EuclideanVectorError);
  REQUIRE_THROWS_AS((a -= f), EuclideanVectorError);
  REQUIRE_THROWS_AS((d = a + f), EuclideanVectorError);
  REQUIRE_THROWS_AS((d = a - f), EuclideanVectorError);
  REQUIRE_THROWS_AS((jl = a * f), EuclideanVectorError);
  // the exception caused by invalid int or double input;
  REQUIRE_THROWS_AS(a.at(-1), EuclideanVectorError);
  REQUIRE_THROWS_AS(a.at(6), EuclideanVectorError);
  REQUIRE_THROWS_AS((a /= 0), EuclideanVectorError);
  REQUIRE_THROWS_AS((d = a / 0), EuclideanVectorError);
  // the exceptinon of GetEuclideanNorm()
  REQUIRE_THROWS_AS(wrong.GetEuclideanNorm(), EuclideanVectorError);
}
