#include <iostream>
#include "source/point.hpp"
#include "source/line.hpp"
#include "source/figure.hpp"
#include "source/triangle.hpp"
#include "source/rectangle.hpp"
#include "source/circle.hpp"
#include "source/comp_array_matrix.hpp"
#include "source/comp_array_vector.hpp"
#include "source/comp_linked_list_matrix.hpp"
#include "source/comp_linked_list_vector.hpp"
#include "source/array_realization.hpp"
#include "source/list_realization.hpp"

using namespace std;

int main() {
    int OPT = 1;//option selector

    while (OPT) {

        cout << "<<<<<<<<<<<<<<<<<OPTIONS>>>>>>>>>>>>>>>>>>>" << endl << endl;
        cout << "1.To Check points operations" << endl;
        cout << "2.To Check Lines/segments operations" << endl;
        cout << "3.To Check Triangle operations" << endl;
        cout << "4.To Check Rectangle operations" << endl;
        cout << "5.To Check Circle operations" << endl;
        cout << "6.To Check Matrix operations" << endl;
        cout << "7.To Check Vector operations" << endl;
        cout << "0.To exit" << endl << endl;

        cin >> OPT;

        switch (OPT) {//partially written by Chatgpt, adjusted by me
        case 0:
            return 0;
            break;

        case 1: {//Operations on points
            Point A(0, 0), B(0, 0), C(0, 0);
            A = A.GEN();
            B = B.GEN();
            C = C.GEN();
            cout << "Points generated:\n";
            A.printInfo();
            B.printInfo();
            C.printInfo();
            cout << (Point::isOnLine(A, B, C) ? "Points are on a common line\n" : "Points are not on a common line\n");
            double x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            A.shift(x, y);
            cout << "After shift:\n";
            A.printInfo();

            break;
        }

        case 2: {//Operations on Lines
            Line line1(Point::GEN(), Point::GEN()), line2(Point::GEN(), Point::GEN());
            cout << "Line 1:\n";
            line1.printInfo();
            cout << "\nLine 2:\n";
            line2.printInfo();
            cout << (Line::isParalel(line1, line2) ? "Lines are parallel\n" : "Lines are not parallel\n");
            cout << "Angle between lines: " << Line::angle(line1, line2) << endl;
            if (!Line::isParalel(line1, line2)) {
                Point intersection = Line::crossing(line1, line2);
                cout << "Intersection point:\n";
                intersection.printInfo();
            }
            else {
                cout << "Lines are parallel; no intersection point.\n";
            }
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 3: {//Operations on triangles
            Triangle tri1(Point::GEN(), Point::GEN(), Point::GEN());
            Triangle tri2(Point::GEN(), Point::GEN(), Point::GEN());
            cout << "Triangle 1:\n";
            tri1.printInfo();
            cout << "Triangle area: " << Triangle::area(tri1) << endl;
            cout << "Triangle perimeter: " << Triangle::perimeter(tri1) << endl;
            cout << "\nTriangle 2:\n";
            tri2.printInfo();
            cout << "Triangle area: " << Triangle::area(tri2) << endl;
            cout << "Triangle perimeter: " << Triangle::perimeter(tri2) << endl;
            Point circumcenter(0, 0);
            circumcenter = Triangle::outcircle(tri1);
            cout << "\nCircumcenter (Outcircle center) of Triangle 1:\n";
            circumcenter.printInfo();
            Point incircleCenter(0, 0);
            incircleCenter = Triangle::incircle(tri1);
            cout << "Incircle center of Triangle 1:\n";
            incircleCenter.printInfo();
            cout << "\nChecking similarity between Triangle 1 and Triangle 2:\n";
            if (Triangle::issimilar(tri1, tri2)) {
                cout << "Triangle 1 and Triangle 2 are similar.\n";
            }
            else {
                cout << "Triangle 1 and Triangle 2 are not similar.\n";
            }
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            tri1.shift(x, y);
            cout << "After shifting Triangle 1:\n";
            tri1.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 4: {//Operations on rectangles
            Rectangle rect(Point::GEN(), Point::GEN(), Point::GEN(), Point::GEN());
            rect.printInfo();
            cout << "Rectangle perimeter: " << Rectangle::perimeter(rect) << endl;
            if (Rectangle::isconvex(rect)) {
                cout << "Rectangle is convex " << endl;
                cout << "Rectangle area: " << Rectangle::area(rect) << endl;
            }
            else cout << "rectangle is not convex" << endl;
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            rect.shift(x, y);
            cout << "After shift:\n";
            rect.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 5: {//Operations on circles
            Circle circle(Point::GEN(), dis(gen) * 10);
            circle.printInfo();
            cout << "Circle area: " << Circle::area(circle) << endl;
            cout << "Circle perimeter: " << Circle::perimeter(circle) << endl;
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            circle.shift(x,y);
            cout << "After shift:\n";
            circle.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 6: {//Operations on matrixes
            int size = rand() % 10 + 2;
            double** matA = MATGEN(size);
            double** matB = MATGEN(size);
            ListMatrix listMatrixA(size, matA);
            ListMatrix listMatrixB(size, matB);
            cout << "ListMatrix A:\n";
            listMatrixA.print();
            cout << "\n";
            cout << "\nListMatrix B:\n";
            listMatrixB.print();
            cout << "\n";
            cout << "\nSum of ListMatrix A and B:\n";
            ListMatrix::Summ(listMatrixA, listMatrixB).print();
            cout << "\n";
            size_t listMatrixMemory = sizeof(ListMatrix) + sizeof(Matrix_Node) * size * size;
            cout << "\nMemory used by ListMatrix A: " << listMatrixMemory << " bytes\n";
            ArrMatrix arrMatrixA(size, matA);
            ArrMatrix arrMatrixB(size, matB);
            cout << "\nArrMatrix A:\n";
            arrMatrixA.print();
            cout << "\n";
            cout << "\nArrMatrix B:\n";
            arrMatrixB.print();
            cout << "\n";
            size_t arrMatrixMemory = sizeof(ArrMatrix) + sizeof(Element_Matrix) * size * size;
            cout << "\nMemory used by ArrMatrix A: " << arrMatrixMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListMatrix A:\n";
            Matrix_Listnp listResult = listMatrixA.Valsearch(searchVal);
            if (listResult)
                cout << "Value found at (" << listResult->row << ", " << listResult->clmn << ")\n";
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrMatrix A:\n";
            Element_Matrix arrResult = arrMatrixA.ValSearch(searchVal);
            if (arrResult.row >= 0)
                cout << "Value found at (" << arrResult.row << ", " << arrResult.clmn << ")\n";
            else
                cout << "Value not found.\n";
            int rowIndex = rand() % size;
            int colIndex = rand() % size;
            cout << "\nSearching for element at index (" << rowIndex << ", " << colIndex << ") in ListMatrix A:\n";
            listResult = listMatrixA.INDsearch(rowIndex, colIndex);
            if (listResult)
                cout << "Element found with value: " << listResult->val << endl;
            else
                cout << "Element not found.\n";
            cout << "\nSearching for element at index (" << rowIndex << ", " << colIndex << ") in ArrMatrix A:\n";
            arrResult = arrMatrixA.IndSearch(rowIndex, colIndex);
            if (arrResult.row >= 0)
                cout << "Element found with value: " << arrResult.val << endl;
            else
                cout << "Element not found.\n";
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 7: {//Operations on vectors
            int size = rand() % 10 + 2;
            double* vecA = VECGEN(size);
            double* vecB = VECGEN(size);
            ListVector listVectorA(size, vecA, true);
            ListVector listVectorB(size, vecB, true);
            cout << "ListVector A:\n";
            listVectorA.print();
            cout << "\n";
            cout << "\nListVector B:\n";
            listVectorB.print();
            cout << "\n";
            size_t listVectorMemory = sizeof(ListVector) + sizeof(Vector_Node) * size;
            cout << "\nMemory used by ListVector A: " << listVectorMemory << " bytes\n";
            ArrVector arrVectorA(size, vecA, true);
            ArrVector arrVectorB(size, vecB, true);
            cout << "\nArrVector A:\n";
            arrVectorA.print();
            cout << "\n";
            cout << "\nArrVector B:\n";
            arrVectorB.print();
            cout << "\n";
            size_t arrVectorMemory = sizeof(ArrVector) + sizeof(Element_Vector) * size;
            cout << "\nMemory used by ArrVector A: " << arrVectorMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListVector A:\n";
            Vector_Listnp listVResult = listVectorA.Valsearch(searchVal);
            if (listVResult)
                cout << "Value found at index " << listVResult->index << endl;
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrVector A:\n";
            Element_Vector arrVResult = arrVectorA.ValSearch(searchVal);
            if (arrVResult.index >= 0)
                cout << "Value found at index " << arrVResult.index<< endl;
            else
                cout << "Value not found.\n";
            int searchIdx = rand() % size;
            cout << "\nSearching for element at index " << searchIdx << " in ListVector A:\n";
            listVResult = listVectorA.INDsearch(searchIdx);
            if (listVResult)
                cout << "Element found with value: " << listVResult->val << endl;
            else
                cout << "Element not found.\n";
            cout << "\nSearching for element at index " << searchIdx << " in ArrVector A:\n";
            arrVResult = arrVectorA.IndSearch(searchIdx);
            if (arrVResult.index >= 0)
                cout << "Element found with value: " << arrVResult.val << endl;
            else
                cout << "Element not found.\n";
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }
        }
    }

    return 0;
}