//
// Created by User on 6.09.2021.
//

#include "ArraysStrings.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <cstdlib>

#define COND_Q1 4
#define COND_Q2 2
#define COND_Q4 3
#define COND_Q5 2
#define COND_Q6 1
#define COND_Q8 2
#define COND_Q9 2
using namespace std;

bool ArraysStrings::IsUniqueChars(string& str) {
#if COND_Q1 == 1
    unordered_map<char, bool> map;

    for (char c : str) {
        auto var = make_pair(c, true);
        if (map.contains(c))
            return false;
        map.insert(make_pair(c, true));
    }

#elif COND_Q1 == 2
    sort(str.begin(), str.end());
    for (int i = 0; i < str.size(); ++i)
        if (str[i] == str[i + 1])
            return false;

#elif COND_Q1 == 3
    bool chars[128]{false};
    for (int val : str) {
        if (chars[val])
            return false;
        chars[val] = true;
    }

#else
    // the string only uses the lowercase letters a through z
    int checker = 0;
    for (int i = 0; i < str.size(); ++i) {
        int val = str[i] - 'a';
        if (checker & (1 << val))
            return false;
        checker |= 1 << val;
    }
#endif
    return true;
}

bool ArraysStrings::CheckPermutation(const string &str1, const string &str2) {
    if (str1.size() != str2.size())
        return false;

#if COND_Q2 == 1
    unordered_map<char, int> map1;

    for (char c : str1) {
        if (map1.contains(c))
            map1[c]++;
        else
            map1.insert(make_pair(c, 0));
    }

    unordered_map<char, int> map2;

    for (char c : str2) {
        if (map2.contains(c))
            map2[c]++;
        else
            map2.insert(make_pair(c, 0));
    }
    return map1 == map2;
#else
    int chars[128]{0};
    for (char val : str1)
        chars[val]++;

    for (char val : str2) {
        chars[val]--;
        if (chars[val] < 0)
            return false;
    }
    return true;
#endif
}

void ArraysStrings::Urlify(string &str, int true_length) {
    int space_count = 0;
    for (int k = 0; k < true_length; ++k)
        if (str[k] == ' ')
            ++space_count;

    //int i = str.size() - 1;
    int i = true_length + space_count * 2 - 1;
    if (true_length < str.size())
        str[true_length] = '\0';

    for (int j = true_length - 1; j >= 0; --j) {
        if (str[j] != ' ')
            str[i--] = str[j];
        else {
            str[i--] = '0';
            str[i--] = '2';
            str[i--] = '%';
        }
    }
}

bool ArraysStrings::IsPalindromePermutation(string& str) {
#if COND_Q4 == 1
    unordered_map<char, int> map;

    std::for_each(str.begin(), str.end(), [](char & c){c = tolower(c);});
    for (char c : str) {
        if (map.contains(c))
            map[c]++;
        else {
            if (c != ' ')
                map.insert(make_pair(c, 1));
        }
    }

    int count{0};
    for (auto x : map) {
        if (x.second == 1)
            ++count;
    }

    int charCount = count_if(str.begin(), str.end(), [](char c){return c != ' ';});
    if (count > 1)
        return false;

    if (charCount % 2 == 0 && count == 1)
        return false;

    if (charCount % 2 != 0 && count == 0)
        return false;

    return true;
#elif COND_Q4 == 2
    int* arr = new int['z' - 'a' + 1];
    int oddCount{0};
    std::for_each(str.begin(), str.end(), [](char & c){c = tolower(c);});

    for (char c : str) {
        if (c == ' ')
            continue;

        arr[c - 'a']++;
        if (arr[c - 'a'] % 2 == 1)
            ++oddCount;
        else
            --oddCount;
    }

    return oddCount <= 1;
#else
    std::for_each(str.begin(), str.end(), [](char & c){c = tolower(c);});

    int bitVector{0}, index{0}, mask{0};
    for (char c : str) {
        if (c == ' ')
            continue;

        index = c - 'a';
        mask = 1 << index;
        if ((bitVector & mask) == 0)
            bitVector |= mask;
        else
            bitVector &= ~mask;
    }

    return (bitVector & (bitVector - 1)) == 0;
#endif
}

bool ArraysStrings::IsOneAway(std::string& str1, std::string& str2) {
    int diff = str1.length() - str2.length();
    if (abs(diff) > 1)
        return false;

#if COND_Q5 == 1
    int* arr = new int['z' - 'a' + 1];
    std::for_each(str1.begin(), str1.end(), [](char & c){c = tolower(c);});
    std::for_each(str2.begin(), str2.end(), [](char & c){c = tolower(c);});

    for (char c : str1)
        arr[c - 'a']++;

    for (char c : str2) {
        arr[c - 'a']--;
    }

    int count{0};
    for (int i = 0; i < ('z' - 'a' + 1); ++i)
        if (arr[i] == 1)
            ++count;

    return count == 1;
#else
    string s1 = str1.length() < str2.length() ? str1 : str2;
    string s2 = str1.length() < str2.length() ? str2 : str1;

    int index1{0}, index2{0};
    bool foundDiff{false};

    while (index2 < s2.length() && index1 < s1.length()) {
        if (s2[index2] != s1[index1]) {
            if (foundDiff)
                return false;

            foundDiff = true;
            if (s1.length() == s2.length())
                ++index1;
        } else
            ++index1;

        ++index2;
    }

    return true;
#endif
}

string ArraysStrings::CompressStr(string &str) {
#if COND_Q6 == 1
    int c1 = 0, c2 = 1;
    string res;
    while (c2 < str.length()) {
        while (c2 < str.length() && str[c1] == str[c2])
            ++c2;

        res += str[c1] + to_string(c2 - c1);
        c1 = c2++;
    }

    return str.length() > res.length() ? res : str;

#elif COND_Q6 == 2
    string res;
    int freq = 0;
    for (int i = 0; i < str.length(); ++i) {
        ++freq;

        if (i + 1 >= str.length() || str[i] != str[i + 1])  {
            res += str[i] + to_string(freq);
            freq = 0;
        }
    }

    return str.length() > res.length() ? res : str;
#endif
}

void ArraysStrings::RotateCW90(vector<vector<int>>& arr) {
    int n = arr.size();
    for (int i = 0; i < n / 2; ++i) {
        for (int j = i; j < n - i - 1; ++j) {
            int temp = arr[i][j];
            arr[i][j] = arr[n - j - 1][i];
            arr[n - j - 1][i] = arr[n - i - 1][n - j - 1];
            arr[n - i - 1][n - j - 1] = arr[j][n - i - 1];
            arr[j][n - i - 1] = temp;
        }
    }
}

void ArraysStrings::Print2dArr(const vector<vector<int>>& arr) {
    int n1 = arr.size();
    int n2 = arr[0].size();
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void ArraysStrings::MakeZero(vector<vector<int>>& arr) {
    int m = arr.size();
    int n = arr[0].size();
    cout << "m: " << m << " n: " << n << endl;

#if COND_Q8 == 1
    unordered_map<int, int> set;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == 0) {
                set.insert(make_pair(i, j));
            }
        }
    }

    for (auto& p : set) {
        MakeZeroRow(arr, p.first);
        MakeZeroCol(arr, p.second);
    }
#else
    bool hasRowZero = false;
    bool hasColZero = false;
    for (int i = 0; i < m; ++i) {
        if (arr[i][0] == 0) {
            hasColZero = true;
            break;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (arr[0][i] == 0) {
            hasRowZero = true;
            break;
        }
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (arr[i][j] == 0) {
                arr[i][0] = 0;
                arr[0][j] = 0;
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        if (arr[0][i] == 0)
            MakeZeroCol(arr, i);
    }

    for (int i = 1; i < m; ++i) {
        if (arr[i][0] == 0)
            MakeZeroRow(arr, i);
    }

    if (hasRowZero)
        MakeZeroRow(arr, 0);

    if (hasColZero)
        MakeZeroCol(arr, 0);
#endif
}

void ArraysStrings::MakeZeroRow(vector<vector<int>> &arr, int index) {
    for (int j = 0; j < arr[0].size(); ++j)
        arr[index][j] = 0;
}

void ArraysStrings::MakeZeroCol(vector<vector<int>> &arr, int index) {
    for (int i = 0; i < arr.size(); ++i)
        arr[i][index] = 0;
}

bool ArraysStrings::CheckStrRotation(std::string& str1, std::string& str2) {
    if (str1.length() != str2.length() && str1.length() == 0)
        return false;

#if COND_Q9 == 1
    size_t index = str2.find_first_of(str1[0]);
    bool f1 = str1.find(str2.substr(0, index)) != string::npos;
    bool f2 = str2.substr(index, str2.length()) == str1.substr(0, str1.length() - index);
    return f1 && f2;
#else
    return (str1 + str1).find(str2) != string::npos;
#endif
}
