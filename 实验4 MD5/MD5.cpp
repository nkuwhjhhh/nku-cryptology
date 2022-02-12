#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#define F(b,c,d) ((b & c) | (~b & d))
#define G(b,c,d) ((b & d) | (c & ~d))
#define H(b,c,d) (b ^ c ^ d)
#define I(b,c,d) (c ^ (b | (~d)))

#define FF(a,b,c,d,Mj,s,ti) b + (((a + F(b, c, d) + Mj + ti) << s) | ((a + F(b, c, d) + Mj + ti) >> (32 - s)))
#define GG(a,b,c,d,Mj,s,ti) b + (((a + G(b, c, d) + Mj + ti) << s) | ((a + G(b, c, d) + Mj + ti) >> (32 - s)))
#define HH(a,b,c,d,Mj,s,ti) b + (((a + H(b, c, d) + Mj + ti) << s) | ((a + H(b, c, d) + Mj + ti) >> (32 - s)))
#define II(a,b,c,d,Mj,s,ti) b + (((a + I(b, c, d) + Mj + ti) << s) | ((a + I(b, c, d) + Mj + ti) >> (32 - s)))

static const struct {
    char* msg;
    unsigned char hash[16];
}tests[] = {
    { "", { 0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e } },
    { "a", {0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61 } },
    { "abc", { 0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0, 0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72 } },
    { "message digest", { 0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d, 0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0 } },
    { "abcdefghijklmnopqrstuvwxyz", { 0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00, 0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b } },
    { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
      { 0xd1, 0x74, 0xab, 0x98, 0xd2, 0x77, 0xd9, 0xf5,
        0xa5, 0x61, 0x1c, 0x2c, 0x9f, 0x41, 0x9d, 0x9f } },
    { "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
      { 0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55,
        0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a } }
};

unsigned int A = 0x67452301, B = 0xEFCDAB89, C = 0x98BADCFE, D = 0x10325476;
int S[16] = { 7,12,17,22,5,9,14,20,4,11,16,23,6,10,15,21 };
int index[64] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
               1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
               5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
               0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9 };
unsigned int T[64] =
{
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

void output(int a)
{
    for (int i = 0; i < 4; i++)
    {
        int temp = a & 0xff;
        printf("0x%x, ", temp);
        a = a >> 8;
    }
}

int main()
{
    char* message = new char[10000];
    unsigned long long length = 0, lengthtian = 0;
    int id = 0;
    cout << "编号";
    cin >> id;
    length = strlen(tests[id].msg);
    const char* aa = "€";//1000 0000
    strcpy(message, tests[id].msg);
    strcat(message, aa);
    lengthtian = length;
    if (lengthtian % 64 < 56)
        lengthtian = (lengthtian / 64)*64 + 56;
    else
    {
        lengthtian += 120 - lengthtian % 64;
    }
    for (int i = length + 1; i < lengthtian; i++)
        message[i] = 0;
    for (int i = 0; i < 8; i++)
    {
        message[lengthtian + i] = (char)(length*8 >> 8 * i);
    }
    lengthtian += 8;
    unsigned int** M = new unsigned int* [lengthtian / 64];
    for (int i = 0; i < lengthtian / 64; i++)
    {
        M[i] = new unsigned int[16];
    }
    for (int i = 0; i < lengthtian / 64; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            M[i][j] = 0;
            for (int h = 0; h < 4; h++)
                M[i][j] += ((unsigned int)(unsigned char)message[64 * i + 4 * j + h] << 8 * h);
        }
    }
    unsigned int a, b, c, d;
    unsigned int temp;
    for (int i = 0; i < lengthtian / 64; i++)
    {
        a = A;
        b = B;
        c = C;
        d = D;
        for (int j = 0; j < 16; j++)
        {
            temp = b;
            b = FF(a, b, c, d, M[i][index[j]], S[j % 4], T[j]);
            a = d;
            d = c;
            c = temp;
        }
        for (int j = 16; j < 32; j++)
        {
            temp = b;
            b = GG(a, b, c, d, M[i][index[j]], S[j % 4 + 4], T[j]);
            a = d;
            d = c;
            c = temp;
        }
        for (int j = 32; j < 48; j++)
        {
            temp = b;
            b = HH(a, b, c, d, M[i][index[j]], S[j % 4 + 8], T[j]);
            a = d;
            d = c;
            c = temp;
        }
        for (int j = 48; j < 64; j++)
        {
            temp = b;
            b = II(a, b, c, d, M[i][index[j]], S[j % 4 + 12], T[j]);
            a = d;
            d = c;
            c = temp;
        }
        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
    }
    cout << "字符串内容为" ;
    for (int i = 0; i < strlen(tests[id].msg); i++)
        cout << tests[id].msg[i];
    cout << endl;
    cout << "计算";
    output(A);
    output(B);
    output(C);
    output(D);
    cout << endl;
    cout << "正确";
    for (int i = 0; i < 16; i++)
        cout <<"0x"<< hex << (unsigned int)(unsigned char)tests[id].hash[i] << ", ";
}