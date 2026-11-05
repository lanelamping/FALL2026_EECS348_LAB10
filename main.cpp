/*
 * EECS 348 - Lab 10: C++ Programming
 * Uses a custom Matrix class to perform matrix operations.
 * Implements operator overloading, diagonal sums, row and column swapping,
 * and matrix element updates.
 * Author: Lane Lamping
 * KUID: 3158487
 * Contributors: ChatGPT
 * Lab Session: THURSDAY 11:00 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Matrix
{
private:
    int size;
    int data[100][100];

public:

    // Constructor
    Matrix()
    {
        size = 0;

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                data[i][j] = 0;
            }
        }
    }

    // Set the size of the matrix
    void setSize(int n)
    {
        size = n;
    }

    // Get the size of the matrix
    int getSize()
    {
        return size;
    }

    // Read matrix values from the file
    void readMatrix(ifstream &file)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                file >> data[i][j];
            }
        }
    }

    // Display the matrix
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << data[i][j];
            }

            cout << endl;
        }
    }

    // Add two matrices using operator overloading
    Matrix operator+(Matrix other)
    {
        Matrix result;

        result.size = size;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Multiply two matrices using operator overloading
    Matrix operator*(Matrix other)
    {
        Matrix result;

        result.size = size;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = 0;

                for (int k = 0; k < size; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Calculate the main diagonal sum
    int mainDiagonalSum()
    {
        int sum = 0;

        for (int i = 0; i < size; i++)
        {
            sum += data[i][i];
        }

        return sum;
    }

    // Calculate the secondary diagonal sum
    int secondaryDiagonalSum()
    {
        int sum = 0;

        for (int i = 0; i < size; i++)
        {
            sum += data[i][size - 1 - i];
        }

        return sum;
    }

    // Swap two rows
    void swapRows(int row1 = 0, int row2 = 1)
    {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size)
        {
            cout << "Invalid row indices." << endl;
            return;
        }

        for (int j = 0; j < size; j++)
        {
            int temp = data[row1][j];
            data[row1][j] = data[row2][j];
            data[row2][j] = temp;
        }
    }

    // Swap two columns
    void swapColumns(int col1 = 0, int col2 = 1)
    {
        if (col1 < 0 || col1 >= size || col2 < 0 || col2 >= size)
        {
            cout << "Invalid column indices." << endl;
            return;
        }

        for (int i = 0; i < size; i++)
        {
            int temp = data[i][col1];
            data[i][col1] = data[i][col2];
            data[i][col2] = temp;
        }
    }

    // Update a matrix element
    void updateElement(int row = 0, int col = 0, int value = 100)
    {
        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            cout << "Invalid matrix indices." << endl;
            return;
        }

        data[row][col] = value;
    }
};

// Swap rows by passing the Matrix by value
Matrix swapRows(Matrix matrix, int row1 = 0, int row2 = 1)
{
    matrix.swapRows(row1, row2);

    return matrix;
}

// Main function
int main()
{
    string filename;

    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    int n;
    file >> n;

    if (n <= 0 || n > 100)
    {
        cout << "Invalid matrix size." << endl;
        return 1;
    }

    // Create and initialize Matrix A and Matrix B
    Matrix A;
    Matrix B;

    A.setSize(n);
    B.setSize(n);

    A.readMatrix(file);
    B.readMatrix(file);

    file.close();

    // Display Matrix A
    cout << "Matrix A:" << endl;
    A.display();

    // Display Matrix B
    cout << "\nMatrix B:" << endl;
    B.display();

    // Practice 2: Add matrices
    Matrix addition = A + B;

    cout << "\nA + B:" << endl;
    addition.display();

    // Practice 3: Multiply matrices
    Matrix multiplication = A * B;

    cout << "\nA * B:" << endl;
    multiplication.display();

    // Practice 4: Calculate diagonal sums
    cout << "\nDiagonal sums for Matrix A:" << endl;

    cout << "Main diagonal sum: "
         << A.mainDiagonalSum() << endl;

    cout << "Secondary diagonal sum: "
         << A.secondaryDiagonalSum() << endl;

    // Practice 5: Swap rows 0 and 2
    Matrix rowSwapped = swapRows(A, 0, 2);

    cout << "\nProblem 5 - Rows 0 and 2 swapped:" << endl;
    rowSwapped.display();

    // Practice 6: Swap columns 0 and 2
    Matrix columnSwapped = A;

    columnSwapped.swapColumns(0, 2);

    cout << "\nProblem 6 - Columns 0 and 2 swapped:" << endl;
    columnSwapped.display();

    // Practice 7: Update row 1, column 2 to 99
    Matrix updated = A;

    updated.updateElement(1, 2, 99);

    cout << "\nProblem 7 - Updated matrix:" << endl;
    updated.display();

    return 0;
}