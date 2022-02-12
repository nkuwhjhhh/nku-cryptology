#include <iostream>
using namespace std;
void ShiftPlainToCipher(char Text[])
{
    int shift = 0;
    cout << "Please input your shift:";
    cin >> shift;

    shift %= 26;
    int aftershift = 0;
    int shift_65 = shift + 65;
    int shift_90 = shift + 90;
    int shift_97 = shift + 97;
    int shift_122 = shift + 122;
    for (int i = 0; int(Text[i]) != 0; i++)
    {
        //计算移位后的ascii
        aftershift = int(Text[i]) + shift;
        //判断移位后的
        if (aftershift >= shift_65 && aftershift <= 90)
        {
            Text[i] = char(aftershift);
        }
        if (aftershift > 90 && aftershift <= shift_90)
        {
            Text[i] = char(aftershift - 26);
        }
        if (aftershift >= shift_97 && aftershift <= 122)
        {
            Text[i] = char(aftershift);
        }
        if (aftershift > 122 && aftershift <= shift_122)
        {
            Text[i] = char(aftershift - 26);
        }
    }
    cout << "密文为：" << endl << Text << endl;
    cout << "------------------------------------" << endl;
}

void ShiftCipherToPlain(char Text[])
{
    int shift = 1;
    int f = 0;
    while (shift < 26)
    {
        for (int i = 0; int(Text[i]) != 0; i++)
        {
            if (int(Text[i]) < 65 || (int(Text[i]) > 90 && int(Text[i]) < 97) || int(Text[i]) > 122)continue;
            Text[i] = char(int(Text[i]) + 1);
            if (char(Text[i]) == 91)Text[i] = char(65);
            if (char(Text[i]) == 123)Text[i] = char(97);
        }
        cout << "明文为：" << endl << Text << endl;
        cout << "找到了吗？找到请输1，没有的话输0:";
        cin >> f;
        if (f == 1)break;
        shift++;
    }
    cout << "------------------------------------" << endl;
}

void ReplacePlainToCipher(char Text[])
{
    char A[26];
    for (int i = 0; i < 26; i++)
    {
        A[i] = char(65 + i);
    }
    char B[26] = { 'H','K','W','T','X','Y','S','G','B','P','Q','E','J','A','Z','M','L','N','O','F','C','I','D','V','U','R' };
    for (int i = 0; int(Text[i]) != 0; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (Text[i] == A[j])
            {
                Text[i] = B[j];
                break;
            }
        }
    }
    cout << "密文为：" << endl << Text << endl;
    cout << "------------------------------------" << endl;
}

void ReplaceCipherToPlain(char Text[])
{
    char A[26];
    for (int i = 0; i < 26; i++)
    {
        A[i] = char(65 + i);
    }
    char B[26] = { 'H','K','W','T','X','Y','S','G','B','P','Q','E','J','A','Z','M','L','N','O','F','C','I','D','V','U','R' };
    for (int i = 0; int(Text[i]) != 0; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (Text[i] == B[j])
            {
                Text[i] = A[j];
                break;
            }
        }
    }
    cout << "明文为：" << endl << Text << endl;
    cout << "------------------------------------" << endl;
}

int main()
{
    char Text[1000];
    int a = 1;
    cout << "请输入你的文本" << endl;
    cin.getline(Text, 1000);
    while (a != 0)
    {
        cout << "请输入操作类型" << endl;
        cout << "移位加密1" << endl;
        cout << "移位解密2" << endl;
        cout << "单表置换加密3" << endl;
        cout << "单表置换解密4" << endl;
        cout << "退出0" << endl;
        cin >> a;
        if (a == 1)ShiftPlainToCipher(Text);
        else if (a == 2)ShiftCipherToPlain(Text);
        else if (a == 3)ReplacePlainToCipher(Text);
        else if (a == 4)ReplaceCipherToPlain(Text);
    }
}