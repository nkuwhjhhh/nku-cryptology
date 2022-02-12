#include <ctime>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;
#define INT_MAX 4294967296
unsigned int LINEAR_M = INT_MAX - 1;
unsigned int LINEAR_A = 16807;
int change(char a);
class BigInt //十六进制
{
public:
    int num[512];
    BigInt();
    void copy(BigInt);
    void print();
    void set(unsigned int a);
    void set(int a);
    void set(string a);
    void set(string a, int x);
    void set(unsigned long long a);
    int getbit(int i);
};
BigInt add(BigInt a, BigInt b);//两个大数相加
BigInt sub(BigInt a, BigInt b);//两个大数相减
BigInt sub(BigInt a, BigInt b, int d);
int compare(BigInt a, BigInt b, int d);
int compare(BigInt a, BigInt b);
BigInt mul(BigInt a, BigInt b);//两个大数相乘
BigInt mod(BigInt a, BigInt b);
BigInt pow(BigInt a, BigInt b, BigInt n);
BigInt calculate_d(BigInt a, BigInt b);//计算乘法逆元
BigInt div(BigInt a, BigInt b, BigInt &c);

unsigned int smallprime[10000];
void getsmallprime();
class prime
{
public:
    BigInt number;
    prime();
    prime(string a);
    prime(string a, int x);
    void getarbitrary();
    void check2000();    //检查是否能被2000以内的素数整除,若不能则加2，直至可以
    void millerrabin();  //检查是否是素数
};

class RSA //加密
{
public:
    BigInt n, phi;
    BigInt q;
    BigInt p;
    BigInt d, e;
    RSA(BigInt p, BigInt q, BigInt e);
};

class encrypt //加密
{
public:
    BigInt n, e;
    BigInt c, m; //密文和明文
    encrypt(RSA a, BigInt m);
};

class decrypt //解密
{
public:
    BigInt n, d;
    BigInt c, m; //密文和明文
    decrypt(RSA a, BigInt c);
};

prime::prime(string a)
{
    number.set(a);
}
prime::prime(string a, int x)
{
    number.set(a, x);
}

void BigInt::copy(BigInt a)
{
    for (int i = 0; i < 512; i++)
        num[i] = a.num[i];
}

BigInt::BigInt()
{
    memset(this, 0, sizeof(BigInt));
}

void BigInt::print()
{
    int i;
    for (i = 511; i > 0; i--)
        if (num[i])
            break;
    cout << "0x";
    for (; i >= 0; i--) cout << hex << num[i];
    cout << endl;
}

//指数运算
BigInt pow(BigInt a, BigInt b, BigInt n)
{
    BigInt buffer[512];
    buffer[0].copy(a);
    int x;
    for (x = 511; x > 0; x--)
        if (b.num[x])
            break;
    for (int i = 1; i <= x; i++)
    {
        BigInt tempbuf[5];
        tempbuf[0].copy(buffer[i - 1]);
        for (int j = 1; j < 5; j++)
        {
            //计算平方
            BigInt temp = mul(tempbuf[j - 1], tempbuf[j - 1]);
            //得出的结果对n进行取模
            tempbuf[j] = mod(temp, n);
        }
        buffer[i].copy(tempbuf[4]);
    }
    BigInt product;
    product.num[0] = 1;
    for (int i = 511; i >= 0; i--)
    {
        BigInt temp;
        for (int j = 0; j < b.num[i]; j++)
        {
            temp = mul(product, buffer[i]);
            product = mod(temp, n);
        }
    }
    return product;
}

//按对应位置相加，如果出现加“过”了的情况，进位
BigInt add(BigInt a, BigInt b)
{
    BigInt c;
    for (int i = 0; i < 512; i++) c.num[i] = a.num[i] + b.num[i];
    for (int i = 0; i < 511; i++)
    {
        c.num[i + 1] += c.num[i] / 16;
        c.num[i] %= 16;
    }
    return c;
}

//按对应位置相加，如果出现减“过”了的情况，加回来
BigInt sub(BigInt a, BigInt b)
{
    BigInt c;
    for (int i = 0; i < 512; i++) c.num[i] = a.num[i] - b.num[i];
    for (int i = 0; i < 511; i++)
    {
        if (c.num[i] < 0)
        {
            c.num[i] += 16;
            c.num[i + 1] -= 1;
        }
    }
    return c;
}

BigInt sub(BigInt a, BigInt b, int d)
{
    BigInt c;
    c.copy(a);
    //将模数按照相应的位数“左移”，然后被模的数减去左移后的模数
    for (int i = d; i < 512; i++) c.num[i] -= b.num[i - d];
    for (int i = 0; i < 511; i++)
    {
        //如果减“过”了，再给他加回来
        if (c.num[i] < 0)
        {
            c.num[i] += 16;
            c.num[i + 1] -= 1;
        }
    }
    return c;
}

//对两个大数进行相乘并存入num[512]中
BigInt mul(BigInt a, BigInt b)
{
    BigInt result;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            result.num[i + j] += a.num[i] * b.num[j];
        }
    }
    //对存在进位的情况进行进位处理
    for (int i = 0; i < 510; i++)
    {
        result.num[i + 1] += result.num[i] / 16;
        result.num[i] %= 16;
    }
    //最后返回结果
    return result;
}

BigInt div(BigInt a, BigInt b, BigInt &c)
{
    //比较除数与被除数
    BigInt q;
    int t = compare(a, b);
    if (t == -1)
        return q;
    if (t == 0)
    {
        BigInt c;
        c.set(1);
        return c;
    }
    int x, y;
    for (x = 511; x >= 0; x--)
        if (a.num[x])
            break;
    for (y = 511; y >= 0; y--)
        if (b.num[y])
            break;
    int d = x - y;

    //循环减，如果首先按照位减，高位减成功，按照相应的位加给得数
    c.copy(a);
    while (d >= 0)
    {
        while (c.num[x] > b.num[y])
        {
            c = sub(c, b, d);
            BigInt v1;
            v1.num[d] = 1;
            q = add(q, v1);
        }
        if (c.num[x] == b.num[y] && compare(c, b, d) == 1)
        {
            c = sub(c, b, d);
            BigInt v1;
            v1.num[d] = 1;
            q = add(q, v1);
        }
        d--;
        int t;
        while (compare(c, b) == 1 && c.num[x])
        {
            c = sub(c, b, d);
            BigInt v1;
            v1.num[d] = 1;
            q = add(q, v1);
        }
        if (c.num[x] == 0)
            x--;
        t = compare(c, b);
        if (t == -1)
            break;
        if (t == 0)
        {
            c = sub(c, b);
            BigInt v1;
            v1.num[d] = 1;
            q = add(q, v1);
            return q;
        }
    }
    return q;
}

BigInt mod(BigInt a, BigInt b) // a>b
{
    //首先比较a,b
    int t = compare(a, b);
    //不用计算模，前一个小于后一个，直接返回前一个
    if (t == -1)
        return a;
    //两个数相等，返回0
    if (t == 0)
    {
        BigInt zero;
        return zero;
    }
    //得出a和b的最高位
    int x, y;
    for (x = 511; x >= 0; x--)
        if (a.num[x])
            break;
    for (y = 511; y >= 0; y--)
        if (b.num[y])
            break;
    
    //计算两个数之间的相差位数
    int d = x - y;

    //将a存入c
    BigInt c;
    c.copy(a);
    while (d >= 0)
    {
        //按照位数，首先将第二个数右移到和第一最高位一样的地方，
        while (c.num[x] > b.num[y]) c = sub(c, b, d);
        if (c.num[x] == b.num[y] && compare(c, b, d) == 1) c = sub(c, b, d);
        d--;
        int t;
        while (compare(c, b) == 1 && c.num[x]) c = sub(c, b, d);
        if (c.num[x] == 0) x--;
        t = compare(c, b);
        if (t == -1) return c;
        if (t == 0)
        {
            BigInt s;
            return s;
        }
    }
    return c;
}

//比较大数，从上往下比，如果前一个大于后一个返回1，小于返回-1，等于返回0
int compare(BigInt a, BigInt b)
{
    for (int i = 511; i >= 0; i--)
    {
        if (a.num[i] > b.num[i])
            return 1;
        if (a.num[i] < b.num[i])
            return -1;
    }
    return 0;
}

//除了位数之外同上
int compare(BigInt a, BigInt b, int d)
{
    for (int i = 511; i >= d; i--)
    {
        if (a.num[i] > b.num[i - d])
            return 1;
        if (a.num[i] < b.num[i - d])
            return -1;
    }
    return 0;
}

//使用欧几里得算法计算乘法逆元
BigInt calculate_d(BigInt a, BigInt b)
{
    b = mod(b, a);
    BigInt q[100], t[100], r[100];
    r[0].copy(a);
    r[1].copy(b);
    t[0].set(0);
    t[1].set(1);
    int i;
    BigInt v1;
    v1.set(1);
    for (i = 2; i < 500; i++)
    {
        //除法，计算出除数
        q[i - 1] = div(r[i - 2], r[i - 1], r[i]);
        //相乘
        BigInt temp = mul(q[i - 1], t[i - 1]);
        while (compare(temp, t[i - 2]) == 1) t[i - 2] = add(t[i - 2], r[0]);
        t[i] = sub(t[i - 2], temp);
        //乘到结果为1结束
        if (compare(r[i], v1) == 0) break;
    }
    return t[i];
}

void getsmallprime()
{
    //从4开始计算，2*2,2*3,2*4···，3*2，直到10000，这些数里对应到数组赋1,去除掉所有的合数
    int a[10001];
    memset(a, 0, sizeof(a));
    for (int i = 2; i <= 100; i++)
    {
        for (int j = 2; i * j <= 10000; j++)
        {
            a[i * j] = 1;
        }
    }
    //将这些非合数赋给想要存素数的数组
    int index = 0;
    for (int i = 2; i <= 10000; i++)
    {
        if (!a[i])
            smallprime[index++] = i;
    }
}

//使用线性同余计算出512位奇数
void prime::getarbitrary()
{
    unsigned long long num[16];
    srand((unsigned)time(NULL));
    num[0] = rand() % (INT_MAX - 1) + 1;
    for (int i = 1; i < 16; i++)
    {
        num[i] = (num[i - 1] * LINEAR_A) % LINEAR_M;//线性同余算法
    }
    //让最高位和最低位都变成1
    num[15] |= (1 << 31) & 0x0000000011111111;
    num[0] |= 1;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            number.num[i * 8 + j] = num[i] % 16;
            num[i] /= 16;
        }
    }
    int i;
}

void BigInt::set(unsigned int a)
{
    memset(this, 0, sizeof(BigInt));
    int i = 0;
    while (a)
    {
        num[i] = a % 16;
        a /= 16;
        i++;
    }
}

void BigInt::set(unsigned long long a)
{
    memset(this, 0, sizeof(BigInt));
    int i = 0;
    while (a)
    {
        num[i] = a % 16;
        a /= 16;
        i++;
    }
}

void BigInt::set(int a)
{
    memset(this, 0, sizeof(BigInt));
    if (a < 0)
        return;
    int i = 0;
    while (a)
    {
        num[i] = a % 16;
        a /= 16;
        i++;
    }
}

int BigInt::getbit(int i)
{
    if ((num[i / 4] & (1 << (i % 4))) == 0)
        return 0;
    return 1;
}

prime::prime()
{
    memset(this, 0, sizeof(prime));
    getarbitrary();//生成512的奇数
    check2000();    //检查是否能被2000以内的素数整除,若不能则加2，直至可以
    millerrabin();  //检查是否是素数
}

void prime::check2000() //检查是否能被2000以内的素数整除,若不能则加2，直至可以
{
    if (smallprime[0] == 0)
        getsmallprime();
    BigInt v0; // 0
    BigInt v2;
    v2.set(2);
    while (1)
    {
        int flag = 1;
        for (int i = 0; i < 303; i++)
        {
            BigInt temp;
            temp.set(smallprime[i]);
            BigInt s = mod(number, temp);
            if (compare(s, v0) == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            break;
        }
        else
        {
            number = add(number, v2);
        }
    }
}

void prime::millerrabin()//米勒罗宾算法检测，这里只检测5次
{
    int a[5] = {2, 3, 13, 17, 19};
    int flag = 0;
    BigInt n1;
    BigInt v1, v2;
    v1.set(1);
    v2.set(2);
    BigInt v0;
    v0.set(0);
    int high;
    while (!flag)
    {
        //将number-1存入n1
        flag = 1;
        n1 = sub(number, v1);
        //得到num中的最高位
        for (high = 127; high >= 0; high--)
        {
            if (number.num[high])
                break;
        }
        BigInt temp, d;

        for (int k = 0; k < 5; k++)
        {
            temp.set(a[k]);
            d.set(1);//d=1
            for (int i = high * 4 + 3; i >= 0; i--)
            {
                BigInt x;
                x.copy(d);//x=d
                d = mod(mul(d, d), number);//计算d的平方mod n
                if (compare(d, v1) == 0&&compare(x, v1) && compare(x, n1))//如果d=0,x≠1,,x≠n-1,并且返回失败
                {
                    flag = 0;
                    break;
                }
                if (n1.getbit(i)) d = mod(mul(d, temp), number);//如果b=1，将d=d*a mod n
            }
            if (compare(d, v1)) flag = 0;//如果d≠1，则返回失败
            if (!flag) break;//失败就退出循环，继续加2，继续检测
        }
        //如果检测出不是素数，则加2继续检测
        if (!flag)
        {
            number = add(number, v2);
            check2000();
        }
    }
}

//计算RSA中的n，φ(n)=(p-1)*(q-1),d(e对φ(n)的逆元)
RSA::RSA(BigInt p, BigInt q, BigInt e)
{
    BigInt v1;
    v1.set(1);
    this->p = p;
    this->q = q;
    this->e = e;
    n = mul(p, q);//乘法
    BigInt p1, q1;
    p1 = sub(p, v1);//p-1
    q1 = sub(q, v1);//q-1
    phi = mul(p1, q1);//计算欧拉函数
    d = calculate_d(phi, e);//取得逆元
}

//加密
encrypt::encrypt(RSA a, BigInt m)
{
    this->n = a.n;
    this->e = a.e;
    this->m = m;
    this->c = pow(m, e, n);
}

//解密
decrypt::decrypt(RSA a, BigInt c)
{
    this->n = a.n;
    this->d = a.d;
    this->c = c;
    this->m = pow(c, d, n);
}

int change(char a)
{
    if (a >= '0' && a <= '9') return (int)(a - 48);
    if (a == 'a' || a == 'A') return 10;
    if (a == 'b' || a == 'B') return 11;
    if (a == 'c' || a == 'C') return 12;
    if (a == 'd' || a == 'D') return 13;
    if (a == 'e' || a == 'E') return 14;
    if (a == 'f' || a == 'F') return 15;
}

void BigInt::set(string a) // 16进制输入
{
    for (int i = a.length() - 1; i >= 0; i--)
        num[a.length() - i - 1] = change(a[i]);
}

void BigInt::set(string a, int x) //字符串输入
{
    for (int i = a.length() - 1; i >= 0; i--)
    {
        num[2 * a.length() - 2 * i - 2] = (int)a[i] % 16;
        num[2 * a.length() - 2 * i - 1] = (int)a[i] / 16;
    }
}

int main()
{
    cout << "等待素数生成" << endl;
    BigInt e;
    e.set(0x10001);
    prime p,q;
    cout<<"素数生成成功"<<endl;
    cout << "第一个素数p= ";p.number.print();
    cout << "第二个素数q= ";q.number.print();
    cout<<endl;
    RSA jiami(p.number, q.number, e);
    cout << "素数乘积n= "; jiami.n.print();
    cout << "φ(n)= "; jiami.phi.print();
    cout << "随机数e= "; jiami.e.print();
    cout << "e的逆元d= "; jiami.d.print();
    cout<<endl;
    cout<<"输入加密消息"<<endl;
    string message;
    cin>>message;
    BigInt m;
    m.set(message, 0);
    encrypt temp(jiami, m);
    cout << "转换明文 m= "; temp.m.print();
    cout << "加密密文 c= "; temp.c.print();
    decrypt temp_(jiami, temp.c);
    cout << "密文解密 m\'= "; temp_.m.print();
}