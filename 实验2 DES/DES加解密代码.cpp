#include<iostream>
#include<cmath>
using namespace std;
static const struct des_test_case {
    int num, mode; // mode 1 = encrypt
    int key[8], txt[8], out[8];
} cases[] = {
    { 1, 1,   { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
    { 2, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 }, { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 3, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 }, { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 4, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA }, { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 5, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F }, { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 6, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 }, { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 7, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF }, { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 8, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F }, { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 9, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 }, { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    {10, 1,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A }, { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 1, 0,   { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A }, { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 2, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 } },
    { 3, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 } },
    { 4, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA } },
    { 5, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F } },
    { 6, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 } },
    { 7, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF } },
    { 8, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F } },
    { 9, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 } },
    {10, 0,   { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }, { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A } }
};

int p = 0;

int IP[64] = { 58,50,42,34,26,18,10,2,
               60,52,44,36,28,20,12,4,
               62,54,46,38,30,22,14,6,
               64,56,48,40,32,24,16,8,
               57,49,41,33,25,17, 9,1,
               59,51,43,35,27,19,11,3,
               61,53,45,37,29,21,13,5,
               63,55,47,39,31,23,15,7 };

int IP_1[64] = { 40,8,48,16,56,24,64,32,
                 39,7,47,15,55,23,63,31,
                 38,6,46,14,54,22,62,30,
                 37,5,45,13,53,21,61,29,
                 36,4,44,12,52,20,60,28,
                 35,3,43,11,51,19,59,27,
                 34,2,42,10,50,18,58,26,
                 33,1,41, 9,49,17,57,25 };

int E[48] = { 32, 1, 2, 3, 4, 5,
               4, 5, 6, 7, 8, 9,
               8, 9,10,11,12,13,
              12,13,14,15,16,17,
              16,17,18,19,20,21,
              20,21,22,23,24,25,
              24,25,26,27,28,29,
              28,29,30,31,32, 1 };

int P[32] = { 16, 7,20,21,
              29,12,28,17,
               1,15,23,26,
               5,18,31,10,
               2, 8,24,14,
              32,27, 3, 9,
              19,13,30, 6,
              22,11, 4,25 };

int S[8][4][16] = { //S1
    {   {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    //S2
    {   {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    //S3
    {   {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    //S4
    {   {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    //S5
    {   {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    //S6
    {   {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    //S7
    {   {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    //S8
    {   {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

int PC_1[56] = { 57,49,41,33,25,17, 9,
                  1,58,50,42,34,26,18,
                 10, 2,59,51,43,35,27,
                 19,11, 3,60,52,44,36,
                 63,55,47,39,31,23,15,
                  7,62,54,46,38,30,22,
                 14, 6,61,53,45,37,29,
                 21,13, 5,28,20,12, 4 };

int PC_2[48] = { 14,17,11,24, 1, 5,
                  3,28,15, 6,21,10,
                 23,19,12, 4,26, 8,
                 16, 7,27,20,13, 2,
                 41,52,31,37,47,55,
                 30,40,51,45,33,48,
                 44,49,39,56,34,53,
                 46,42,50,36,29,32 };

int shift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

//明文初始置换
int plaintext_64[64];
int plaintext_64_IP[64];
void permuteIP(int x)
{
    int a = 0;
    for (int i = 0; i < 8; i++)
    {
        a = cases[x].txt[i];
        if (a >= 0x80)
        {
            plaintext_64[8 * i] = 1;
            a -= 0x80;
        }
        if (a >= 0x40)
        {
            plaintext_64[8 * i + 1] = 1;
            a -= 0x40;
        }
        if (a >= 0x20)
        {
            plaintext_64[8 * i + 2] = 1;
            a -= 0x20;
        }
        if (a >= 0x10)
        {
            plaintext_64[8 * i + 3] = 1;
            a -= 0x10;
        }
        if (a >= 0x8)
        {
            plaintext_64[8 * i + 4] = 1;
            a -= 0x8;
        }
        if (a >= 0x4)
        {
            plaintext_64[8 * i + 5] = 1;
            a -= 0x4;
        }
        if (a >= 0x2)
        {
            plaintext_64[8 * i + 6] = 1;
            a -= 0x2;
        }
        if (a >= 0x1)
        {
            plaintext_64[8 * i + 7] = 1;
            a -= 0x1;
        }
    }

    for (int i = 0; i < 64; i++)
    {
        plaintext_64_IP[i] = plaintext_64[IP[i] - 1];
    }
}

//密钥初始化置换   中指定PC-1置换表，传入初始密钥，返回置换后的结果，只使用一次
int key[64];                      //初始密钥
int key_56[56];                  //第一次置换后密钥
void permutekey_PC_1(int x)
{
    int a = 0;
    for (int i = 0; i < 8; i++)
    {
        a = cases[x].key[i];
        if (a >= 0x80)
        {
            key[8 * i] = 1;
            a -= 0x80;
        }
        if (a >= 0x40)
        {
            key[8 * i + 1] = 1;
            a -= 0x40;
        }
        if (a >= 0x20)
        {
            key[8 * i + 2] = 1;
            a -= 0x20;
        }
        if (a >= 0x10)
        {
            key[8 * i + 3] = 1;
            a -= 0x10;
        }
        if (a >= 0x8)
        {
            key[8 * i + 4] = 1;
            a -= 0x8;
        }
        if (a >= 0x4)
        {
            key[8 * i + 5] = 1;
            a -= 0x4;
        }
        if (a >= 0x2)
        {
            key[8 * i + 6] = 1;
            a -= 0x2;
        }
        if (a >= 0x1)
        {
            key[8 * i + 7] = 1;
            a -= 0x1;
        }
    }
    for (int i = 0; i < 56; i++)
    {
        key_56[i] = key[PC_1[i] - 1];
    }
}



int mkidkey[16][56];             //子秘钥中间产生
void shiftkey()
{
    for (int j = 0; j < 27; j++)
    {
        mkidkey[0][j] = key_56[j + 1];
        mkidkey[0][j + 28] = key_56[j + 29];
    }
    mkidkey[0][27] = key_56[0];
    mkidkey[0][55] = key_56[28];

    for (int i = 1; i < 16; i++)
    {
        if (shift[i] == 1)
        {
            for (int j = 0; j < 27; j++)
            {
                mkidkey[i][j] = mkidkey[i - 1][j + 1];
                mkidkey[i][j + 28] = mkidkey[i - 1][j + 29];
            }
            mkidkey[i][27] = mkidkey[i - 1][0];
            mkidkey[i][55] = mkidkey[i - 1][28];
        }
        if (shift[i] == 2)
        {
            for (int j = 0; j < 26; j++)
            {
                mkidkey[i][j] = mkidkey[i - 1][j + 2];
                mkidkey[i][j + 28] = mkidkey[i - 1][j + 30];
            }
            mkidkey[i][26] = mkidkey[i - 1][0];
            mkidkey[i][27] = mkidkey[i - 1][1];
            mkidkey[i][54] = mkidkey[i - 1][28];
            mkidkey[i][55] = mkidkey[i - 1][29];
        }
    }
}


int kidkey[16][48];               //子秘钥
void permutekey_PC_2()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            kidkey[i][j] = mkidkey[i][PC_2[j] - 1];
        }
    }
}


int luntext[17][64];
int kuo[16][48];
int huo[16][48];
int huan[16][32];
int phuan[16][32];
void lun()
{
    int a, b, c;
    int sum = 0;
    for (int i = 0; i < 64; i++)
    {
        luntext[0][i] = plaintext_64_IP[i];
    }
    for (int i = 1; i < 17; i++)
    {
        //左边等于右边上一次
        for (int j = 0; j < 32; j++)
            luntext[i][j] = luntext[i - 1][j + 32];
        //右边上一次E扩展,扩展后和密钥异或
        for (int j = 0; j < 48; j++)
        {
            kuo[i - 1][j] = luntext[i - 1][E[j] - 1 + 32];
            if (p == 0)
            {
                huo[i - 1][j] = kuo[i - 1][j] ^ kidkey[i - 1][j];
            }
            if (p == 1)
            {
                huo[i - 1][j] = kuo[i - 1][j] ^ kidkey[16 - i][j];
            }
        }
        //S盒置换
        for (int j = 0; j < 8; j++)
        {
            a = huo[i - 1][6 * j] * 2 + huo[i - 1][6 * j + 5];
            b = huo[i - 1][6 * j + 1] * 8 + huo[i - 1][6 * j + 2] * 4 + huo[i - 1][6 * j + 3] * 2 + huo[i - 1][6 * j + 4];
            c = S[j][a][b];
            if (c > 7)
            {
                huan[i - 1][4 * j] = 1;
                c -= 8;
            }
            else
                huan[i - 1][4 * j] = 0;
            if (c > 3)
            {
                huan[i - 1][4 * j + 1] = 1;
                c -= 4;
            }
            else
                huan[i - 1][4 * j + 1] = 0;
            if (c > 1)
            {
                huan[i - 1][4 * j + 2] = 1;
                c -= 2;
            }
            else
                huan[i - 1][4 * j + 2] = 0;
            if (c > 0)
            {
                huan[i - 1][4 * j + 3] = 1;
                c -= 1;
            }
            else
                huan[i - 1][4 * j + 3] = 0;
        }
        //p置换
        for (int j = 0; j < 32; j++)
            phuan[i - 1][j] = huan[i - 1][P[j] - 1];

        //置换后和左边上次异或

        for (int j = 0; j < 32; j++)
            luntext[i][j + 32] = luntext[i - 1][j] ^ phuan[i - 1][j];
    }
}

//交换左右
int temp_cipher[64];
void swap()
{
    for (int i = 0; i < 32; i++)
    {
        temp_cipher[i] = luntext[16][i + 32];
        temp_cipher[i + 32] = luntext[16][i];
    }
}

int cipher[64];
void permuteIP_1()
{
    for (int i = 0; i < 64; i++)
    {
        cipher[i] = temp_cipher[IP_1[i] - 1];
    }
}

int main()
{
    int x = 0;
    cout << "请输入(x,y)     x:加密0,解密1    y:加解密分别10组，输入第y组" << endl;
    cin >> p >> x;
    x = 10 * p + x;
    permuteIP(x);//得到IP置换后的文本
    permutekey_PC_1(x);//得到密钥PC-1置换后的文本
    shiftkey();//子秘钥移位
    permutekey_PC_2();//计算出每轮密钥K
    lun();
    swap();
    permuteIP_1();
    for (int i = 0; i < 16; i++)
    {
        x = cipher[4 * i] * 8 + cipher[4 * i + 1] * 4 + cipher[4 * i + 2] * 2 + cipher[4 * i + 3];
        if (i % 2 == 0)
        {
            printf("0x%X", x);
            continue;
        }
        printf("%X", x);
        if (i != 15)  cout << ",";
    }
}