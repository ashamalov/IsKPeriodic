#include <iostream>
#include <string>

# define NO_OF_CHARS 256  

using namespace std;

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS])
{
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
    {
        badchar[i] = -1;
    }

    for (i = 0; i < size; i++)
    {
        badchar[(int)str[i]] = i;
    }
}

bool IsKPeriodic(string str, int k)
{
    // Находим длинну повторяющейся строки 
    int offset = -1;
    for (int i = 1; i < str.size(); ++i) 
    {
        if (str[i] == str[0])
        {
            offset = i;
            break;
        }
    }

    if (offset != k)
    {
        return false;
    }

    // Выделяем повторяющуюся строку и с помощью алгоритма Бойера-Мура проверяем, что она повторяется всю исходную строку
    string pat = str.substr(0, offset);

    int pSize = pat.size();
    int nSize = str.size();

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, pSize, badchar);

    int s = 0;
    while (s <= (nSize - pSize))
    {
        int j = pSize - 1;

        while (j >= 0 && pat[j] == str[s + j])
            j--;

        if (j < 0)
        {
            s += (s + pSize < nSize) ? pSize - badchar[str[s + pSize]] : 1;
        }
        else 
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << IsKPeriodic("kfckfckfckfc", 3) << endl;
    std::cout << IsKPeriodic("kfckfckfckfc", 5) << endl;
    std::cout << IsKPeriodic("abcdabcdabcdabcd", 4) << endl;
    std::cout << IsKPeriodic("abcdabFcdabcdabcd", 4) << endl;
}


