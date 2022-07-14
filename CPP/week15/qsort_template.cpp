#include <iostream>
#include <random>
using namespace std;
// Implement a qsort() template
// T can be: int, float, double, char, etc.

template <typename T>
void print(T &a)
{
    for (auto i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

template <typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

/* QUICK SORT FORMULA
 * numbers: Array with numbers to be sorted.
 * lowMark & highMark: the range to be sorted.
 * Yay, because range may change.
 * size: the size of the array, since C don't have &
 */
template <typename T>
void QuickSort(T numbers[], int lowMark, int highMark)
{
    // For the valid range...
    if (lowMark < highMark)
    {
        // Since range may change while sorting.
        int left = lowMark;
        int right = highMark;
        // As a flag, smaller left, bigger right.
        T flag = numbers[lowMark];
        while (left < right)
        {
            // Find the two invalid number, each on the one side.
            while (left < right && numbers[right] > flag)
            {
                right--;
            }
            while (left < right && numbers[left] <= flag)
            {
                left++;
            }
            // Then swap it.
            Swap(numbers[left], numbers[right]);
        }
        // Since left equals to right on the end, it is where we
        // put the flag on.
        Swap(numbers[left], numbers[lowMark]);
        // Then do the same thing, first on the left, then on the right.
        QuickSort(numbers, lowMark, left - 1);
        QuickSort(numbers, left + 1, highMark);
        return;
    }
    else
    {
        return;
    }
}

int main()
{
    int numbers[10] = {0};
    double double_numbers[10] = {0};
    char char_numbers[] = "1145141919810";
    // Generate random numbers.
    random_device rd;
    default_random_engine e{rd()};
    uniform_int_distribution<int> u(0, 100);
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = u(e);
        double_numbers[i] = u(e);
    }
    QuickSort(numbers, 0, 9);
    QuickSort(double_numbers, 0, 9);
    QuickSort(char_numbers, 0, sizeof(char_numbers) / sizeof(char) - 1);
    print(numbers);
    print(double_numbers);
    print(char_numbers);
}