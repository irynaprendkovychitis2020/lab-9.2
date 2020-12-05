// lab 9.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;
enum Speciality { ITIS, RE, KN, KI, PZ };

string speciality_str[] = { "Computer Science ",
                             "Radio Electronics", "Computer Science",
                             "Computer Engineering", "Software" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_pedagogy;
    union
    {
        int grade_programming;
        int grade_numerical_methods;
    };
};

void Create(Students* S, const int N);
void Print_first(Students* S, const int N);
double BestAverage(Students* s, const int N);
void Phys_Sort(Students* S, const int N);
int* Index_sort(Students* S, const int N);
void Print_Index_Sorted(Students* S, int* I, const int N);
bool Bin_Search(Students* S, const int N, const string surname, const int speciality, const int third_grade);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Enter the number of students: "; cin >> N;

    Students* S = new Students[N];

    string B_surname;
    int B_speciality;
    int B_third_grade;

    int MenuItem;
    do
    {

        cout << endl << endl << endl;
        cout << "Choose an action:" << endl;
        cout << "1 - Enter information about students" << endl;
        cout << "2 - Display information about students" << endl;
        cout << "3 - Physically organize information" << endl;
        cout << "4 - Index information" << endl;
        cout << "5 - Student Search"; cout << endl;
        cout << "0 - Shut down the program" << endl;
        cout << "Enter:"; cin >> MenuItem; cout << endl;
        switch (MenuItem)
        {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print_first(S, N);
            break;
        case 3:
            Phys_Sort(S, N);
            Print_first(S, N);
            break;
        case 4:
            Print_Index_Sorted(S, Index_sort(S, N), N);
            break;
        case 5:
            cout << "Enter search criteria:" << endl;
            cout << "Last name:";
            cin.get();
            cin.sync();
            getline(cin, B_surname); cout << endl;
            do
            {
                cout << "Specialty (0 - Informatics, 1 - Radio Electronics, 2 - Computer Science,";
                cout << "\ n3 - Computer Engineering, 4 - Software):"; cout << endl;
                cout << "Specialty:"; cin >> B_speciality;
            } while (B_speciality < 0 || B_speciality > 4);
            do
            {
                cout << "Grade from the third subject: "; cin >> B_third_grade; cout << endl;
            } while (B_third_grade < 0 || B_third_grade > 5);
            if (Bin_Search(S, N, B_surname, B_speciality, B_third_grade) == 1)
                cout << "Student is" << endl;
            else
                cout << "No student" << endl;
            break;
        case 0:
            return 0;
        default:
            cout << "You have entered an invalid value!" << endl;
        }
    } while (MenuItem != 0);
    return 0;
}
void Create(Students* S, const int N)
{
    int speciality;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    for (int i = 0; i < N; i++)
    {
        cout << "# Student: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Name: "; getline(cin, S[i].surname); cout << endl;
        do
        {
            cout << "Course: "; cin >> S[i].course; cout << endl;
        } while (S[i].course < 1 || S[i].course > 6);
        do
        {
            cout << "Specialty (0 - Informatics, 1 - Radio Electronics, 2 - Computer Science, ";
            cout << "3 - Computer Engineering, 4 - Software): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (speciality < 0 || speciality > 4);
        do
        {

            cout << "physics grade: "; cin >> S[i].grade_physics;
        } while (S[i].grade_physics < 0 || S[i].grade_physics > 5);
        do
        {
            cout << "math grade:: "; cin >> S[i].grade_math;
        } while (S[i].grade_math < 0 || S[i].grade_math > 5);

        switch (S[i].speciality)
        {
        case KN:
            do
            {
                cout << "programming grade:: "; cin >> S[i].grade_programming;
            } while (S[i].grade_programming < 0 || S[i].grade_programming > 5);
            break;
        case ITIS:
            do
            {
                cout << "methods grade: "; cin >> S[i].grade_numerical_methods;
            } while (S[i].grade_numerical_methods < 0 || S[i].grade_numerical_methods > 5);
            break;
        default:
            do
            {
                cout << "pedagogy grade: "; cin >> S[i].grade_pedagogy;
            } while (S[i].grade_pedagogy < 0 || S[i].grade_pedagogy > 5);
        }
        cout << endl;
    }
}
void Print_first(Students* S, const int N)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "==============================================================================================================================" << endl;
    cout << "| # | Last name    | Course    | Specialty      | Physics     |Mathematics   |   Programming | ";
    cout << "Numerical methods | Pedagogy |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(3) << S[i].surname << setw(3);
        cout << "|" << setw(4) << S[i].course << setw(4);
        cout << "|" << setw(3) << speciality_str[S[i].speciality] << setw(3);
        cout << "|" << setw(5) << S[i].grade_physics << setw(5);
        cout << "|" << setw(7) << S[i].grade_math << setw(7);
        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(7) << S[i].grade_programming << setw(7);
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(7) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(8) << S[i].grade_numerical_methods << setw(8);
            cout << "|" << setw(8) << "-" << setw(8) << "|";
            break;
        default:
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(7) << S[i].grade_pedagogy << setw(7) << "|";
        }
        cout << endl;
    }
    cout << "=============================================================================================================================" << endl;
}double BestAverage(Students* s, const int N) {
    double best = 0;  for (int i = 0; i < N; i++)
    {
        double tmp = (s[i].grade_physics + s[i].grade_math + s[i].grade_programming + s[i].grade_numerical_methods + s[i].grade_pedagogy) / 5.;
        if (tmp > best)
            best = tmp;
    }
    return best;
}
void Phys_Sort(Students* S, const int N)
{

    
        Students temp;
    int check, check_next;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            switch (S[i1].speciality)
            {
            case KN:
                check = S[i1].grade_programming;
                check_next = S[i1 + 1].grade_programming;
                break;
            case ITIS:
                check = S[i1].grade_numerical_methods;
                check_next = S[i1 + 1].grade_numerical_methods;
                break;
            default:
                check = S[i1].grade_pedagogy;
                check_next = S[i1 + 1].grade_pedagogy;
            }
            if ((check > check_next)
                ||
                ((check == check_next)
                    &&
                    (S[i1].speciality < S[i1 + 1].speciality))
                ||
                ((check == check_next)
                    &&
                    (S[i1].speciality == S[i1 + 1].speciality)
                    &&
                    (S[i1].surname < S[i1 + 1].surname)))
            {
                temp = S[i1];
                S[i1] = S[i1 + 1];
                S[i1 + 1] = temp;
            }
        }
}
int* Index_sort(Students* S, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    int check_index, check_value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        switch (S[I[i]].speciality)
        {
        case KN:
            check_index = S[I[i]].grade_programming;
            check_value = S[value].grade_programming;
            break;
        case ITIS:
            check_index = S[I[i]].grade_numerical_methods;
            check_value = S[value].grade_numerical_methods;
            break;
        default:
            check_index = S[I[i]].grade_pedagogy;
            check_value = S[value].grade_pedagogy;

        }
        for (j = i - 1;
            j > 0 && ((S[I[j]].speciality > S[value].speciality)
                ||
                ((S[I[j]].speciality == S[value].speciality)
                    &&
                    (check_index > check_value))
                ||
                ((S[I[j]].speciality == S[value].speciality)
                    &&
                    (check_index == check_value)
                    &&
                    (S[I[j]].surname < S[value].surname)));
        j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void Print_Index_Sorted(Students* S, int* I, const int N)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "==============================================================================================================================" << endl;
    cout << "| # | Last name    | Course   | Specialty | Physics|    Mathematics |   Programming | ";
    cout << "Numerical methods | Pedagogy |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

 
        for (int i = 0; i < N; i++)
        {
            cout << "|" << setw(3) << i + 1 << setw(3);
            cout << "|" << setw(4) << S[I[i]].surname << setw(4);
            cout << "|" << setw(6) << S[I[i]].course << setw(6);
            cout << "|" << setw(6) << speciality_str[S[I[i]].speciality] << setw(6);
            cout << "|" << setw(6) << S[I[i]].grade_physics << setw(6);
            cout << "|" << setw(6) << S[I[i]].grade_math << setw(6);
            switch (S[i].speciality)
            {
            case KN:
                cout << "|" << setw(6) << S[I[i]].grade_programming << setw(6);
                cout << "|" << setw(6) << "-" << setw(6);
                cout << "|" << setw(6) << "-" << setw(6) << "|" << endl;
                break;
            case ITIS:
                cout << "|" << setw(6) << "-" << setw(6);
                cout << "|" << setw(6) << S[I[i]].grade_numerical_methods << setw(6);
                cout << "|" << setw(6) << "-" << setw(6) << "|" << endl;
                break;
            default:
                cout << "|" << setw(6) << "-" << setw(6);
                cout << "|" << setw(6) << "-" << setw(6);
                cout << "|" << setw(6) << S[I[i]].grade_pedagogy << setw(6) << "|" << endl;
            }
        }
    cout << "==============================================================================================================================" << endl << endl;
}
bool Bin_Search(Students* S, const int N, const string surname, const int speciality, const int third_grade)
{
    int L = 0, R = N - 1, m, check;

    {
        m = (L + R) / 2;

        switch (S[m].speciality)
        {
        case KN:
            check = S[m].grade_programming;
            break;
        case ITIS:
            check = S[m].grade_numerical_methods;
            break;
        default:
            check = S[m].grade_pedagogy;
        }

        if ((S[m].surname == surname
            &&
            S[m].speciality == speciality)
            &&
            (check == third_grade))
        {
            return 1;
        }

        if ((check < third_grade)
            ||
            (check == third_grade
                &&
                S[m].speciality < speciality)
            ||
            (check == third_grade
                &&
                S[m].speciality == speciality
                &&
                S[m].surname > surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
