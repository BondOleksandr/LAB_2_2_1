#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "source/all_matrix&vector.hpp"
#include "source/figure.hpp"
#include "source/RNG.hpp"
#include "source/point.hpp"
#include "source/line.hpp"
#include "source/triangle.hpp"
#include "source/rectangle.hpp"
#include "source/circle.hpp"
#include "source/comp_linked_list_matrix.hpp"
#include "source/comp_linked_list_vector.hpp"
#include "source/comp_array_vector.hpp"
#include "source/comp_array_matrix.hpp"

using Catch::Approx;
using namespace std;

////////////////////////////////////////////POINT//////////////////////////////////////////////////
TEST_CASE("Point GEN generates within expected bounds") {
    Point p = Point::GEN();
    REQUIRE(p.getX() >= 0);
    REQUIRE(p.getY() >= 0);
    REQUIRE(p.getX() <= 100);
    REQUIRE(p.getY() <= 100);
}

TEST_CASE("Point isOnLine detects collinearity") {
    Point a(0, 0);
    Point b(1, 1);
    Point c(2, 2);
    REQUIRE(Point::isOnLine(a, b, c) == true);

    Point d(2, 3);
    REQUIRE(Point::isOnLine(a, b, d) == false);
}

////////////////////////////////////////////LINE//////////////////////////////////////////////////
TEST_CASE("Line::isParalel works correctly") {
    Point a(0, 0), b(2, 2);
    Point c(1, 1), d(3, 3);
    Point e(0, 0), f(2, 1);

    Line ab(a, b);
    Line cd(c, d);
    Line ef(e, f);

    REQUIRE(Line::isParalel(ab, cd) == true);  // same slope
    REQUIRE(Line::isParalel(ab, ef) == false); // different slope
}

TEST_CASE("Line::crossing returns correct point") {
    Line ab(Point(0, 0), Point(4, 4));       // y = x
    Line cd(Point(0, 4), Point(4, 0));       // y = -x + 4

    Point p = Line::crossing(ab, cd);
    REQUIRE(p.getX() == Approx(2.0));
    REQUIRE(p.getY() == Approx(2.0));
}

TEST_CASE("Line::crossing returns fake point for parallel lines") {
    Line ab(Point(0, 0), Point(1, 1));
    Line cd(Point(0, 1), Point(1, 2));  // same slope
    Line ef(Point(0,0), Point(0,1));
    Line gh(Point(0,0), Point(1,0));

    Point nay = Line::crossing(ab, cd);
    REQUIRE(nay .getX() == Approx(14));
    REQUIRE(nay .getY() == Approx(88));

    Point yep = Line::crossing(ef,gh);
    REQUIRE(nay .getX() == Approx(0));
    REQUIRE(nay .getY() == Approx(0));
}

TEST_CASE("Line::angle returns correct value in radians") {
    Line l1(Point(0, 0), Point(1, 0));  // Horizontal
    Line l2(Point(0, 0), Point(0, 1));  // Vertical

    double angle = Line::angle(l1, l2);
    REQUIRE(angle == Approx(3.14159265 / 2));
}

TEST_CASE("Line::LLength returns Euclidean distance") {
    Line l(Point(1, 1), Point(4, 5));  // length = 5
    REQUIRE(Line::LLength(l) == Approx(5.0));
}

////////////////////////////////////////////TRIANGLE//////////////////////////////////////////////////
TEST_CASE("Triangle::area computes correct area") {
    // Right triangle: area = 1/2 * base * height = 6
    Triangle t(Point(0, 0), Point(4, 0), Point(0, 3));
    REQUIRE(Triangle::area(t) == Approx(6.0));
}

TEST_CASE("Triangle::perimeter computes correct perimeter") {
    // Triangle with sides: 3, 4, 5 => perimeter = 12
    Triangle t(Point(0, 0), Point(3, 0), Point(0, 4));
    REQUIRE(Triangle::perimeter(t) == Approx(12.0));
}

TEST_CASE("Triangle::incircle returns valid center inside triangle") {
    // Check if the incenter lies within a reasonable range
    Triangle t(Point(0, 0), Point(4, 0), Point(0, 4));
    Point incenter = Triangle::incircle(t);

    REQUIRE(incenter.getX() >= 0);
    REQUIRE(incenter.getX() <= 2);
    REQUIRE(incenter.getY() >= 0);
    REQUIRE(incenter.getY() <= 2);
}

TEST_CASE("Triangle::outcircle returns approximate center of circumcircle") {
    // For a triangle with vertices (0,0), (4,0), (0,3), the circumcenter is roughly at (2, 1.5)
    Triangle t(Point(0, 0), Point(4, 0), Point(0, 3));
    Point circum = Triangle::outcircle(t);

    REQUIRE(circum.getX() == Approx(2.0).margin(0.2));
    REQUIRE(circum.getY() == Approx(1.5).margin(0.2));
}

TEST_CASE("Triangle::issimilar returns true for scaled triangle") {
    // t2 is a scaled version of t1
    Triangle t1(Point(0, 0), Point(4, 0), Point(0, 3));
    Triangle t2(Point(0, 0), Point(8, 0), Point(0, 6));

    REQUIRE(Triangle::issimilar(t1, t2) == true);
}

TEST_CASE("Triangle::issimilar returns false for different triangles") {
    Triangle t1(Point(0, 0), Point(3, 0), Point(0, 3));
    Triangle t2(Point(0, 0), Point(3, 0), Point(0, 2));

    REQUIRE(Triangle::issimilar(t1, t2) == false);
}

////////////////////////////////////////////RECTANGLE//////////////////////////////////////////////////
TEST_CASE("Rectangle::perimeter returns correct value") {
    // Rectangle: width = 4, height = 3 → perimeter = 2*(4+3) = 14
    Rectangle r(
        Point(0, 0),
        Point(4, 0),
        Point(4, 3),
        Point(0, 3)
    );
    REQUIRE(Rectangle::perimeter(r) == Approx(14.0));
}

TEST_CASE("Rectangle::area returns correct value using diagonals") {
    // Rectangle with sides 4 and 3 → area = 12
    Rectangle r(
        Point(0, 0),
        Point(4, 0),
        Point(4, 3),
        Point(0, 3)
    );
    REQUIRE(Rectangle::area(r) == Approx(12.0));
}

TEST_CASE("Rectangle::isconvex returns true for valid rectangle") {
    // Simple rectangle should be convex
    Rectangle r(
        Point(0, 0),
        Point(4, 0),
        Point(4, 3),
        Point(0, 3)
    );
    REQUIRE(Rectangle::isconvex(r) == true);
}

TEST_CASE("Rectangle::isconvex returns false for non-convex quadrilateral") {
    // Deliberately make one corner concave
    Rectangle r(
        Point(0, 0),
        Point(4, 0),
        Point(2, 1),
        Point(0, 3)
    );
    REQUIRE(Rectangle::isconvex(r) == false);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////MATRIX&VECTOR-PART//////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////MATRIXES////////////////////////////////////////////////////////////
////////////////////////////////////////////LINKED-LIST-MATRIX//////////////////////////////////////////////////


TEST_CASE("Valsearch finds value in matrix A") {
    double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ListMatrix A_list(4, matrix_A);
    ListMatrix B_list(4, matrix_B);

    auto node = A_list.Valsearch(3);
    REQUIRE(node != nullptr);
    REQUIRE(node->row == 1);
    REQUIRE(node->clmn == 1);
}

TEST_CASE("INDsearch returns correct values") {
    double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ListMatrix A_list(4, matrix_A);
    ListMatrix B_list(4, matrix_B);

    auto node1 = A_list.INDsearch(0, 3);
    auto node2 = A_list.INDsearch(1, 1);
    auto node3 = A_list.INDsearch(2, 2); // not present in A
    REQUIRE(node1->val == Approx(2));
    REQUIRE(node2->val == Approx(3));
    REQUIRE(node3->val == Approx(0));
}

TEST_CASE("Summ computes correct matrix sum") {
    double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ListMatrix A_list(4, matrix_A);
    ListMatrix B_list(4, matrix_B);

    ListMatrix C = ListMatrix::Summ(A_list, B_list);
    REQUIRE(C.INDsearch(0, 0)->val == Approx(5));
    REQUIRE(C.INDsearch(0, 3)->val == Approx(3));
    REQUIRE(C.INDsearch(1, 1)->val == Approx(4));
    REQUIRE(C.INDsearch(2, 2)->val == Approx(7));
    REQUIRE(C.INDsearch(3, 0)->val == Approx(10));
    REQUIRE(C.INDsearch(3, 3)->val == Approx(7));
}

TEST_CASE("xScalar multiplies all non-zero values") {
    double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ListMatrix A_list(4, matrix_A);
    ListMatrix B_list(4, matrix_B);

    ListMatrix scaled(4, matrix_A);
    scaled.xScalar(scaled, 2);
    REQUIRE(scaled.INDsearch(0, 0)->val == Approx(2));
    REQUIRE(scaled.INDsearch(0, 3)->val == Approx(4));
    REQUIRE(scaled.INDsearch(1, 1)->val == Approx(6));
    REQUIRE(scaled.INDsearch(3, 0)->val == Approx(8));
    REQUIRE(scaled.INDsearch(3, 3)->val == Approx(10));
}   

////////////////////////////////////////////ARRAY-MATRIX//////////////////////////////////////////////////

TEST_CASE("ValSearch returns correct non-zero element") {
        double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };

    ArrMatrix A_array(4, matrix_A);
    ArrMatrix B_array(4, matrix_B);

    Element_Matrix res1 = A_array.ValSearch(3);
    Element_Matrix res2 = B_array.ValSearch(7);
    REQUIRE(res1.row == 1);
    REQUIRE(res1.clmn == 1);
    REQUIRE(res2.row == 2);
    REQUIRE(res2.clmn == 2);
}

TEST_CASE("ValSearch returns default element for 0") {
            double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ArrMatrix A_array(4, matrix_A);
    ArrMatrix B_array(4, matrix_B);
    Element_Matrix res = A_array.ValSearch(0);
    REQUIRE(res.row == -1);
    REQUIRE(res.clmn == -1);
    REQUIRE(res.val == 0);
}

TEST_CASE("IndSearch returns existing element") {
            double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ArrMatrix A_array(4, matrix_A);
    ArrMatrix B_array(4, matrix_B);
    Element_Matrix res = A_array.IndSearch(0, 3);
    REQUIRE(res.val == Approx(2));
    REQUIRE(res.row == 0);
    REQUIRE(res.clmn == 3);
}

TEST_CASE("IndSearch returns zero-filled for missing element") {
            double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ArrMatrix A_array(4, matrix_A);
    ArrMatrix B_array(4, matrix_B);
    Element_Matrix res = A_array.IndSearch(2, 2); // zero in A
    REQUIRE(res.val == Approx(0));
    REQUIRE(res.row == 2);
    REQUIRE(res.clmn == 2);
}

TEST_CASE("IndSearch handles out-of-bounds indices") {
            double** matrix_A = new double*[4] {
        new double[4]{1, 0, 0, 2},
        new double[4]{0, 3, 0, 0},
        new double[4]{0, 0, 0, 0},
        new double[4]{4, 0, 0, 5}
    };

    double** matrix_B = new double*[4] {
        new double[4]{4, 0, 0, 1},
        new double[4]{0, 1, 0, 0},
        new double[4]{0, 0, 7, 0},
        new double[4]{6, 0, 0, 2}
    };
    
    ArrMatrix A_array(4, matrix_A);
    ArrMatrix B_array(4, matrix_B);
    Element_Matrix res = A_array.IndSearch(10, 10);
    REQUIRE(res.row == -1);
    REQUIRE(res.clmn == -1);
    REQUIRE(res.val == 0);
}

////////////////////////////////////////////VECTORS////////////////////////////////////////////////////////////
////////////////////////////////////////////LINKED-LIST-VECTOR//////////////////////////////////////////////////

 TEST_CASE("Valsearch returns correct non-zero element") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ListVector V_list(5, vec, true);

    Vector_Listnp res = V_list.Valsearch(3.0);
    REQUIRE(res != nullptr);
    REQUIRE(res->val == Approx(3.0));
    REQUIRE(res->index == 2);
}

TEST_CASE("Valsearch returns null for zero value") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ListVector V_list(5, vec, true);

    
    Vector_Listnp res = V_list.Valsearch(0.0);
    REQUIRE(res == nullptr);
}

TEST_CASE("INDsearch returns correct element at index") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ListVector V_list(5, vec, true);

    Vector_Listnp res = V_list.INDsearch(4);
    REQUIRE(res != nullptr);
    REQUIRE(res->val == Approx(5.0));
    REQUIRE(res->index == 4);
}

TEST_CASE("INDsearch returns null for zero element") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ListVector V_list(5, vec, true);

    Vector_Listnp res = V_list.INDsearch(1); // vector[1] == 0
    REQUIRE(res == nullptr);
}

TEST_CASE("INDsearch handles invalid index") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ListVector V_list(5, vec, true);

    Vector_Listnp res = V_list.INDsearch(10); // out of bounds
    REQUIRE(res == nullptr);
}

////////////////////////////////////////////ARRAY-VECTOR//////////////////////////////////////////////////

TEST_CASE("ValSearch returns correct non-zero element") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ArrVector V_array(5, vec, true);

    Element_Vector res = V_array.ValSearch(3.0);
    REQUIRE(res.val == Approx(3.0));
    REQUIRE(res.index == 2);
}

TEST_CASE("ValSearch returns default struct for zero") {
    
    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ArrVector V_array(5, vec, true);

    Element_Vector res = V_array.ValSearch(0.0);
    REQUIRE(res.val == 0.0);
    REQUIRE(res.index == -1);
}

TEST_CASE("IndSearch returns correct element at index") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ArrVector V_array(5, vec, true);

    Element_Vector res = V_array.IndSearch(4);
    REQUIRE(res.val == Approx(5.0));
    REQUIRE(res.index == 4);
}

TEST_CASE("IndSearch returns default struct for zero element") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ArrVector V_array(5, vec, true);

    Element_Vector res = V_array.IndSearch(1); // vector[1] == 0
    REQUIRE(res.val == 0.0);
    REQUIRE(res.index == -1);
}

TEST_CASE("IndSearch returns default struct for out of bounds") {

    double* vec = new double[5]{1.0, 0.0, 3.0, 0.0, 5.0};

    ArrVector V_array(5, vec, true);

    Element_Vector res = V_array.IndSearch(10); // out of bounds
    REQUIRE(res.val == 0.0);
    REQUIRE(res.index == -1);
}
