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
        //������λ���ascii
        aftershift = int(Text[i]) + shift;
        //�ж���λ���
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
    cout << "����Ϊ��" << endl << Text << endl;
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
        cout << "����Ϊ��" << endl << Text << endl;
        cout << "�ҵ������ҵ�����1��û�еĻ���0:";
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
    cout << "����Ϊ��" << endl << Text << endl;
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
    cout << "����Ϊ��" << endl << Text << endl;
    cout << "------------------------------------" << endl;
}

int main()
{
    char Text[1000];
    int a = 1;
    cout << "����������ı�" << endl;
    cin.getline(Text, 1000);
    while (a != 0)
    {
        cout << "�������������" << endl;
        cout << "��λ����1" << endl;
        cout << "��λ����2" << endl;
        cout << "�����û�����3" << endl;
        cout << "�����û�����4" << endl;
        cout << "�˳�0" << endl;
        cin >> a;
        if (a == 1)ShiftPlainToCipher(Text);
        else if (a == 2)ShiftCipherToPlain(Text);
        else if (a == 3)ReplacePlainToCipher(Text);
        else if (a == 4)ReplaceCipherToPlain(Text);
    }
}