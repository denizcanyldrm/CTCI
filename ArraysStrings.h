//
// Created by User on 6.09.2021.
//

#ifndef CTCI_ARRAYSSTRINGS_H
#define CTCI_ARRAYSSTRINGS_H

#include <string>
#include <vector>

class ArraysStrings {
public:
    ArraysStrings() = default;
    ~ArraysStrings() = default;

    static bool IsUniqueChars(std::string& str);
    static bool CheckPermutation(const std::string& str1, const std::string& str2);
    static void Urlify(std::string& str, int true_length);
    static bool IsPalindromePermutation(std::string& str);
    static bool IsOneAway(std::string& str1, std::string& str2);
    static std::string CompressStr(std::string& str);
    static void RotateCW90(std::vector<std::vector<int>>& arr);

    static void Print2dArr(const std::vector<std::vector<int>>& arr);
    static void MakeZero(std::vector<std::vector<int>>& arr);
    static bool CheckStrRotation(std::string& str1, std::string& str2);

private:
    static void MakeZeroRow(std::vector<std::vector<int>>& arr, int index);
    static void MakeZeroCol(std::vector<std::vector<int>>& arr, int index);
};

#endif //CTCI_ARRAYSSTRINGS_H

/*
string s1{"asdfg"};
string s2{"abcbc"};
string s3{"ccbba"};
string s4{"ccbbadffddf"};
string s5{"Mr John Smith    "};
string s6{"as df  qwe klm        "};
string s7;
string s8{"Tact Coa"};
string s9{"tactcoapapa"};
string s10{"pale"};
string s11{"ple"};
string s12{"pales"};
string s13{"bale"};
string s14{"bake"};
string s15{"aabcccccaaa"};
vector<vector<int>> arr{{1, 2}, {3, 4}};
vector<vector<int>> arr2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
vector<vector<int>> arr3{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
vector<vector<int>> arr4{{1, 2, 3}, {4, 5, 6}, {7, 0, 9}, {10, 11, 12}};
vector<vector<int>> arr5{{1, 2, 3}, {0, 5, 6}, {7, 0, 9}, {10, 11, 12}};
vector<vector<int>> arr6{{1, 0, 3}, {4, 5, 6}, {7, 8, 9}};
vector<vector<int>> arr7{{1, 2, 3}, {0, 5, 6}, {7, 8, 9}};
string s16{"waterbottle"};
string s17{"erbottlewat"};

cout << "s inUnique: " << ArraysStrings::IsUniqueChars(s1) << endl;
cout << "s2 inUnique: " << ArraysStrings::IsUniqueChars(s2) << endl;

cout << ArraysStrings::CheckPermutation(s1, s2) << endl;
cout << ArraysStrings::CheckPermutation(s3, s2) << endl;
cout << ArraysStrings::CheckPermutation(s1, s4) << endl;

ArraysStrings::Urlify(s5, 13);
ArraysStrings::Urlify(s6, 14);
ArraysStrings::Urlify(s7, 0);
cout << s5 << endl;
cout << s6 << endl;
cout << s7 << endl;

cout << ArraysStrings::IsPalindromePermutation(s9) << endl;
cout << ArraysStrings::IsPalindromePermutation(s8) << endl;
cout << ArraysStrings::IsPalindromePermutation(s7) << endl;
cout << ArraysStrings::IsPalindromePermutation(s1) << endl;

cout << ArraysStrings::IsOneAway(s1, s2) << endl;
cout << ArraysStrings::IsOneAway(s10, s11) << endl;
cout << ArraysStrings::IsOneAway(s12, s10) << endl;
cout << ArraysStrings::IsOneAway(s10, s13) << endl;
cout << ArraysStrings::IsOneAway(s10, s14) << endl;

cout << ArraysStrings::CompressStr(s15) << endl;
cout << ArraysStrings::CompressStr(s9) << endl;

ArraysStrings::RotateCW90(arr);
ArraysStrings::Print2dArr(arr);
ArraysStrings::RotateCW90(arr2);
ArraysStrings::Print2dArr(arr2);
ArraysStrings::RotateCW90(arr3);
ArraysStrings::Print2dArr(arr3);

ArraysStrings::MakeZero(arr4);
ArraysStrings::Print2dArr(arr4);
ArraysStrings::MakeZero(arr5);
ArraysStrings::Print2dArr(arr5);
ArraysStrings::MakeZero(arr6);
ArraysStrings::Print2dArr(arr6);
ArraysStrings::MakeZero(arr7);
ArraysStrings::Print2dArr(arr7);

cout << ArraysStrings::CheckStrRotation(s16, s17) << endl;
cout << ArraysStrings::CheckStrRotation(s13, s14) << endl;
cout << ArraysStrings::CheckStrRotation(s13, s17) << endl;
*/