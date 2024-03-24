/////////////////////////////////////////////////////////
// SE271 - Assignment 1: Source file
// 0. Rename this file with your ID: "hw1_YOURSTUDENTID.cpp"
// 1. Implement each function 
/////////////////////////////////////////////////////////

#include "hw1.h"
#include <iostream>

int count_odd(const unsigned int* array, int size) {
    int oddnum{ 0 };
    for (int i = 0; i < size; i++) 
    {
        if (array[i]%2==0)
        {
            oddnum += 1;
        }
    }
    return oddnum;
}

int normalize(double* array, int size) {
    int max = array[0];
    int min = array[0];
    //max ���ϱ�
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    //min ���ϱ�
    for (int i = 0; i < size; i++) 
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    //division-by-zero
    if (max==min)
    {
        return 0;
    }
    //array �ٲ��ֱ�
    else
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = (array[i] - min) / (max - min);
        }
    }
    return 1;
}

int find_nth(const int* array, int size, int n) {
    //error
    if (size < n)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            int smaller{ 0 };
            for (int j = 0; j < size; j++)  
            {
                if (array[j] < array[i])
                {
                    smaller += 1;
                }
            }
            if (smaller == n - 1)
            {
                return array[i];
            }
        }

    }
    return 0;
}

int count_pattern(const char *str, const char * pattern) {
    int count = 0;
    int patL = strlen(pattern);
    int strL = strlen(str);
    int statement = 0;//i��°���� pattern�� �����ϴ��� �ƴ����� ��Ÿ��.(0�̸� true, 1�̸� false)
    for (int i = 0; i < strL - patL+1; i++)
    {
        statement=0; 
        for (int j = 0; j < patL; j++)
        {
            if (str[i + j] != pattern[j])
            {
                statement = 1;
            }
        }
        if (statement == 0)
        {
            count = count + 1;
        }
    }
    return count;
}

char* create_shortest_palindrome(const char *src, char* dst) {

    int srcl= strlen(src);
    for (int i = 0; i < srcl; i++)
    {
        dst[i] = src[i]; // �ϴ� src �״�� ����
    }
    int inDstCount = 1; // �ڿ������� �� ��°������ dst�ΰ�? �� �ڴ� �׻� dst�̹Ƿ� 1���� �����մϴ�. aabb->bb�� �ִ� dst�̹Ƿ� 2, aba->aba�� �ִ� dst�̹Ƿ� 3.
    for (int i = 2; i <= srcl; i++) //i�� Ȯ���� �κ� char�� ����
    {
        if (i % 2 == 0)  //���̰� ¦��
        {
            int stats = 0; //0�̸� �κ�char�� dst, 1�̸� dst�� �ƴ�
            for (int j = 1; j <= i / 2; j++)
            {
                if (src[srcl - j] != src[srcl -1- i + j])
                {
                    stats = 1;
                }
            }
            if (stats == 0)
            {
                inDstCount = i;
            }
        }
        else
        {
            int stats = 0;
            for (int j = 1; j <= i / 2; j++)
            {
                if (src[srcl - j] != src[srcl - 1 - i + j])
                {
                    stats = 1;
                }
            }
            if (stats == 0)
            {
                inDstCount = i;
            }
        }
    }
    int char_needs_reversed = srcl - inDstCount;
    std::cout << sizeof(dst) << std::endl;
    for (int i = 0; i < char_needs_reversed; i++)
    {
        dst[srcl+i]= src[char_needs_reversed - 1 - i];
    }
    dst[srcl + char_needs_reversed] = 0;
    return dst;
}

#ifdef SE271_HW1
int main() {
    using std::cout;
    using std::endl;

    // Problem 1
    unsigned int a[] = {0, 1, 2, 3, 5};
    std::size_t size_a = sizeof(a) / sizeof(int);
    cout << "Problem 1: " << count_odd(a, (int)size_a) << endl;
    // Problem 2
    double b[] = {1, 2, 2, 3, 2};
    std::size_t size_b = sizeof(b) / sizeof(double);
    normalize(b, (int)size_b);
    cout << "Problem 2: ";
    for (unsigned int i = 0; i < size_b; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;

    // Problem 3
    int c[] = {1, 5, 3, 2, 4};
    cout << "Problem 3: " << find_nth(c, sizeof(c) / sizeof(int), 3) << endl;

    // Problem 4
    cout << "Problem 4: ex1) " << count_pattern("AABBBBAA", "AA") << endl;
    cout << "Problem 4: ex2) " << count_pattern("AABBBBAA", "BB") << endl;


    // Problem 5
    char d[100] = {0};
    cout << "Problem 5: ex1) " <<create_shortest_palindrome("ABCD", d) << endl;
    cout << "Problem 5: ex2) " << create_shortest_palindrome("AABBCC", d) << endl;
}
#endif
