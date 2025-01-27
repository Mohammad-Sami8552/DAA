#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <functional>
#include <random>
using namespace std;
using namespace chrono;
int n = 100000;
int i, j, k;
int arrb[100000];
int arrw[100000];
int arra[100000];
string myText_b,myText_w,myText_a;
string sb = "best_case.txt";
string sw = "worst_case.txt";
string sa = "average_case.txt";

int generateData()
{
    srand(time(0));

    ofstream best("best_case.txt");
    if (!best)
    {
        cerr << "Error! could not open best_case file for writing\n";
        return 1;
    }
    for (int i = 1; i <= n; i++)
    {
        best << i << "\n";
    }
    best.close();

    ofstream
        worst("worst_case.txt");
    if (!worst)
    {
        cerr << "Error! could not open worst_case file for writing\n";
        return 1;
    }
    for (int i = n; i >= 1; i--)
    {
        worst << i << "\n";
    }
    worst.close();

    ofstream
        average("average_case.txt");
    if (!average)
    {
        cerr << "Error! could not open average_case file for writing\n";
        return 1;
    }
    for (int i = 1; i <= n; i++)
    {
        average << (rand() % n) + 1 << "\n";
    }
    average.close();
}
void selection_sort(int *arr)
{
    int idx;
    for (int i = 0; i < n - 1; i++)
    {
        int min = arr[i];
        idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (min >= arr[j])
            {
                min = arr[j];
                idx = j;
            }
        }
        if (idx != i)
        {
            swap(arr[i], arr[idx]);
        }
    }
}

void insertion_sort(int *arr)
{
    for (int i = 0; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubble_sort(int *arr)
{
    bool swapped=false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void quick_sort(int *arr, int len)
{
    function<void(int *, int, int)> qksort;
    qksort = [&qksort](int *v, int start, int end)
    {
        if ((end - start) <= 1)
            return;
        int p = v[start + ((end - start - 1) / 2)];
        int i = start - 1;
        int j = end;
        while (true)
        {
            do
            {
                i++;
            } while (v[i] < p);
            do
            {
                j--;
            } while (v[j] > p);
            if (i >= j)
                break;
            swap(v[i], v[j]);
        }
        qksort(v, start, j + 1);
        qksort(v, j + 1, end);
    };
    qksort(arr, 0, len);
}
void insert(int *arr, string s)
{
    ofstream Myfile_(s);
    for (int i = 0; i < n; i++)
    {
        Myfile_ << arr[i] << "\n";
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void execution(string s)
{
    i = j = k = 0;
    ifstream MyFile_b("best_case.txt");
    while (getline(MyFile_b, myText_b))
    {
        arrb[i] = stol(myText_b);
        i++;
    }
    ifstream MyFile_w("worst_case.txt");
    while (getline(MyFile_w, myText_w))
    {
        arrw[j] = stol(myText_w);
        j++;
    }
    ifstream MyFile_a("average_case.txt");

    while (getline(MyFile_a, myText_a))
    {
        arra[k] = stol(myText_a);
        k++;
    }
    if (s == "mergeSort")
    {
        cout << "Merge Sort:-\n";
        auto start_b = high_resolution_clock::now();
        merge_sort(arrb, 0, n - 1);
        auto end_b = high_resolution_clock::now();
        auto duration_b = duration_cast<microseconds>(end_b - start_b);
        cout << "  Best Case: " << duration_b.count() / 1000.0 << " milliseconds" << endl;

        auto start_a = high_resolution_clock::now();
        merge_sort(arra, 0, n - 1);
        auto end_a = high_resolution_clock::now();
        auto duration_a = duration_cast<microseconds>(end_a - start_a);
        cout << "  Average Case: " << duration_a.count() / 1000.0 << " milliseconds" << endl;

        auto start_w = high_resolution_clock::now();
        merge_sort(arrw, 0, n - 1);
        auto end_w = high_resolution_clock::now();
        auto duration_w = duration_cast<microseconds>(end_w - start_w);
        cout << "  Worst Case: " << duration_w.count() / 1000.0 << " milliseconds\n"
             << endl;
    }
    if (s == "bubbleSort")
    {
        cout << "Bubble Sort:-\n";
        auto start_b = high_resolution_clock::now();
        bubble_sort(arrb);
        auto end_b = high_resolution_clock::now();
        auto duration_b = duration_cast<microseconds>(end_b - start_b);
        cout << "  Best Case: " << duration_b.count() / 1000.0 << " milliseconds" << endl;

        auto start_a = high_resolution_clock::now();
        bubble_sort(arra);
        auto end_a = high_resolution_clock::now();
        auto duration_a = duration_cast<microseconds>(end_a - start_a);
        cout << "  Average Case: " << duration_a.count() / 1000.0 << " milliseconds" << endl;

        auto start_w = high_resolution_clock::now();
        bubble_sort(arrw);
        auto end_w = high_resolution_clock::now();
        auto duration_w = duration_cast<microseconds>(end_w - start_w);
        cout << "  Worst Case: " << duration_w.count() / 1000.0 << " milliseconds\n"
             << endl;
    }
    if (s == "selectionSort")
    {
        cout << "Selection Sort:-\n";
        auto start_b = high_resolution_clock::now();
        selection_sort(arrb);
        auto end_b = high_resolution_clock::now();
        auto duration_b = duration_cast<microseconds>(end_b - start_b);
        cout << "  Best Case: " << duration_b.count() / 1000.0 << " milliseconds" << endl;

        auto start_a = high_resolution_clock::now();
        selection_sort(arra);
        auto end_a= high_resolution_clock::now();
        auto duration_a = duration_cast<microseconds>(end_a - start_a);
        cout << "  Average Case: " << duration_a.count() / 1000.0 << " milliseconds" << endl;

        auto start_w = high_resolution_clock::now();
        selection_sort(arrw);
        auto end_w = high_resolution_clock::now();
        auto duration_w = duration_cast<microseconds>(end_w - start_w);
        cout << "  Worst Case: " << duration_w.count() / 1000.0 << " milliseconds\n"
             << endl;
    }
    if (s == "insertionSort")
    {
        cout << "Insertion Sort:-\n";
        auto start_b = high_resolution_clock::now();
        insertion_sort(arrb);
        auto end_b = high_resolution_clock::now();
        auto duration_b = duration_cast<microseconds>(end_b - start_b);
        cout << "  Best Case: " << duration_b.count() / 1000.0 << " milliseconds" << endl;

        auto start_a = high_resolution_clock::now();
        insertion_sort(arra);
        auto end_a = high_resolution_clock::now();
        auto duration_a = duration_cast<microseconds>(end_a - start_a);
        cout << "  Average Case: " << duration_a.count() / 1000.0 << " milliseconds" << endl;

        auto start_w = high_resolution_clock::now();
        insertion_sort(arrw);
        auto end_w = high_resolution_clock::now();
        auto duration_w = duration_cast<microseconds>(end_w - start_w);
        cout << "  Worst Case: " << duration_w.count() / 1000.0 << " milliseconds\n"
             << endl;
    }
    if (s == "quickSort")
    {
        cout << "Quick Sort:-\n";
        auto start_b = high_resolution_clock::now();
        quick_sort(arrb, n);
        auto end_b = high_resolution_clock::now();
        auto duration_b = duration_cast<microseconds>(end_b - start_b);
        cout << "  Best Case: " << duration_b.count() / 1000.0 << " milliseconds" << endl;

        auto start_a = high_resolution_clock::now();
        quick_sort(arra, n);
        auto end_a = high_resolution_clock::now();
        auto duration_a = duration_cast<microseconds>(end_a - start_a);
        cout << "  Average Case: " << duration_a.count() / 1000.0 << " milliseconds" << endl;

        auto start_w = high_resolution_clock::now();
        quick_sort(arrw, n);
        auto end_w = high_resolution_clock::now();
        auto duration_w = duration_cast<microseconds>(end_w - start_w);
        cout << "  Worst Case: " << duration_w.count() / 1000.0 << " milliseconds\n"
             << endl;
    }
}
int main()
{
    generateData();
    execution("bubbleSort");
    execution("selectionSort");
    execution("insertionSort");
    execution("mergeSort");
    execution("quickSort");
    insert(arrb, sb);
    insert(arrw, sw);
    insert(arra, sa);
    return 0;
}