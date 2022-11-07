#include <iostream>
#include "list"
#include "vector"
using namespace std;
//======Task1============================================================================
void addElement(list<double>* list) 
{
    double average;
    double sum = 0;
    for (auto i : *list) 
    {
        sum += i;
    }
    average = sum / list->size();
    list->push_back(average);
}
//======Task2============================================================================
using d2Vector = vector<vector<int>>;

class Matrix 
{
public:
    Matrix() {}

    void getMatrixWithoutRowAndCol(d2Vector& matrix, int size, int row, int col, d2Vector& secondMatrix) 
    {
        int offsetRow = 0;
        int offsetCol = 0;

        for (int i = 0; i < size - 1; i++) 
        {
            if (i == row) 
            {
                offsetRow = 1;
            }

            offsetCol = 0;
            for (int j = 0; j < size - 1; j++) 
            {
                if (j == col) 
                {
                    offsetCol = 1;
                }
                secondMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
            }
        }
    }
    int matrixDet(d2Vector& matrix, int size) 
    {
        float det = 0;
        int degree = 1;

        if (size == 1) 
        {
            return matrix[0][0];
        }
        if (size == 2) 
        {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        d2Vector newMatrix(size - 1, vector<int>(size - 1, 0));

        for (int j = 0; j < size; j++) 
        {
            getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);
            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));

            degree = -degree;
        }
        return det;
    }
};
//======Task3============================================================================
template<typename T>
class myIterator : public iterator<input_iterator_tag, T>
{
public:
    myIterator<T>(T* m) : m(m) {}
    myIterator(const myIterator& o) 
    {
        m(o.m);
    };
    bool operator!=(myIterator const& o) const 
    {
        return m != o.m;
    };
    bool operator==(myIterator const& o) const 
    {
        return m == o.m;
    };
    typename myIterator::reference operator*() const 
    {
        return *m;
    };
    myIterator& operator++() 
    {
        ++m;
        return *this;
    };
private:
    T* m;
};
void task1()
{
    list<double>list{2,3,6,8,10};
    addElement(&list);
    for (auto i : list)
    {
        cout << "element: " << i << " " << endl;
    }
}
void task2()
{
    Matrix matrix;
    d2Vector MyVector1 = { {7} };
    d2Vector MyVector2 = { {7, 2}, {-4, -6} };
    d2Vector MyVector3 = { {-1,  7, -6}, {-8, -4, -1}, {2, 1, 5} };
    d2Vector MyVector4 = { {-1,  7, -6,  3}, {-8, -4, -1, 2}, {2, 1, 5, -4}, {6, -1, 3, -1} };

    cout << matrix.matrixDet(MyVector1, 1) << endl;
    cout << matrix.matrixDet(MyVector2, 2) << endl;
    cout << matrix.matrixDet(MyVector3, 3) << endl;
    cout << matrix.matrixDet(MyVector4, 4) << endl;
}
void task3()
{
    int Arr[6]{ 1, 2, 3, 4, 5, 6 };
    cout << "myIterator :";
    for (auto myIterator : Arr) 
    {
        cout << myIterator << "  ";
    }
    cout << endl;
}
int main()
{
    //task1();
    //task2();
    task3();
    return 0;
}

