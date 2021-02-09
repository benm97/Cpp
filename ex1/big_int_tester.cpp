/**
 * @file catch-int-test.cpp
 * @author Asaf Kali <asaf.kali@mail.huji.ac.il>
 * @version 6
 * @date 28 Aug 2018
 *
 * @section DESCRIPTION
 * Big int tests.
 *
 * First time running the tests, put the `enableRnd` flag to false.
 * After passing all tests, put it back to true.
 *
 * V.4 Fixed div by 0 bug.
 *
 * V.5 Removed str method need, added random tests.
 *
 * V.6 Clearer compare messages.
 *
 */

/* ----------------- Includes ----------------- */

#include <ctime>
#include "big_integer.h"
#include <random>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::to_string;

/* --------------- Constants ---------------- */

#define RND_ITER 50
#define RADIUS 1000

/* ---------------- Globals ----------------- */

int totalCount;
int failCount;
bool enableRnd = true;
string testName;

/* ---------------- Functions ----------------- */

inline const char *const toStr(bool b)
{
    return b ? "true" : "false";
}

static void fail()
{
    cerr << "Check inside [" << testName << "] has failed!"
         << " Debug related methods to for details.   " << endl;
    failCount++;
}

static void pass()
{
    // cout << "Check [" << testName << "] passed!" << endl;
}

static void check(bool expected, bool actual)
{
    totalCount++;
    //message += " expected [" + to_string(expected) + "], got [" + to_string(actual) + "]";
    (expected == actual) ? pass() : fail();
    cout.flush();
}

static void assertEquals(big_integer actual, big_integer expected)
{
    cout << "Checking (actual) [" << actual << "] == [" << expected << "] (expected)" << endl;
    check(true, actual == expected);
}

static void assertEquals(big_integer actual, string expected)
{
    assertEquals(actual, big_integer(expected));
}

static void assertEquals(big_integer actual, int expected)
{
    assertEquals(actual, big_integer(expected));
}

static void assertLarger(big_integer n1, big_integer n2, bool expected)
{
    cout << "Checking that [" << n1 << "] > [" << n2 << "] is [" << toStr(expected) << "]" << endl;
    check(expected, n1 > n2);
}

static void assertSmaller(big_integer n1, big_integer n2, bool expected)
{
    cout << "Checking that [" << n1 << "] < [" << n2 << "] is [" << toStr(expected) << "]" << endl;
    check(expected, n1 < n2);
}

static void setTest(const string &name)
{
    cout << endl << "Starting test [" << name << "]" << endl;
    testName = name;
}

/**
 * Given a range, randomizes a number in that range in uniform distribution.
 * @param min the minimum allowed number (inclusive).
 * @param max the maximum allowed number (inclusive).
 * @return a random number in the given range.
 */
static int rndRange(int min, int max)
{
    //assert(max > min);
    double r = (double) random() / RAND_MAX;
    return (int) ((max - min + 1) * r + min);
}

static int rndNum()
{
    return rndRange(-RADIUS, RADIUS);
}

/* ------------ Constructors -------------- */

static void ctr(string name, string str, int expected)
{
    setTest("Ctr " + name);
    big_integer n1 = big_integer(str);
    assertEquals(n1, expected);
}

static void ctr1()
{
    ctr("1", "5", 5);
}

static void ctr2()
{
    ctr("2", "-5", -5);
}

static void ctr3()
{
    ctr("3", "0", 0);
}

static void ctr4()
{
    ctr("4", "000", 0);
}

static void ctr5()
{
    ctr("5", "000005", 5);
}

static void ctr6()
{
    ctr("6", "-000006", -6);
}

static void ctr7()
{
    ctr("7", "-000000", 0);
}

static void ctr8()
{
    ctr("8", "-", 0);
}

static void ctr9()
{
    ctr("9", "abc", 0);
}

static void ctr10()
{
    ctr("10", "123abc", 0);
}

static void ctr11()
{
    ctr("11", "abc123", 0);
}

static void ctr12()
{
    ctr("12", "0123a3210", 0);
}

static void ctr13()
{
    ctr("13", "13.5", 0);
}

static void ctr14()
{
    ctr("14", "--01", 0);
}

static void ctrSuite()
{
    ctr1();
    ctr2();
    ctr3();
    ctr4();
    ctr5();
    ctr6();
    ctr7();
    ctr8();
    ctr9();
    ctr10();
    ctr11();
    ctr12();
    ctr13();
    ctr14();
}

/* ----------------- Add ------------------ */

static void add(const string &name, int a, int b)
{
    setTest("Add " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    cout << "Calculating [" << a << "] + [" << b << "]" << endl;
    assertEquals(n1 + n2, a + b);
    cout << "Calculating [" << b << "] + [" << a << "]" << endl;
    assertEquals(n2 + n1, b + a);
}

static void add1()
{
    add("1", 5, 9);
}

static void add2()
{
    add("2", 5, -9);
}

static void add3()
{
    add("3", -5, -9);
}

static void add4()
{
    setTest("Add 4");
    big_integer n1 = big_integer(-5);
    big_integer n2 = big_integer(2);
    assertEquals(n1 + n1, -10);
    assertEquals(n2 + n2 + n2, 6);
}

static void add5()
{
    setTest("Add 5");
    big_integer n1 = big_integer(-5);
    big_integer n2 = big_integer(2);

    assertEquals(n1 += n2, -3);
    assertEquals(n1 += n2, -1);
    assertEquals(n1 += n1, -2);
}

static void add6()
{
    setTest("Add 6");
    big_integer n1 = big_integer(5);
    big_integer n2 = big_integer(2);

    n1 = (n1 + 2 + (n2 += 3));
    assertEquals(n1, 12);
    assertEquals(n2, 5);
}

static void add7()
{
    add("7", 1125, 475);
}

static void add8()
{
    setTest("Add 8");
    big_integer n1 = big_integer("123");
    big_integer n2 = big_integer("345");
    big_integer n3 = big_integer("0001");

    assertEquals(n1 + n2 + n3, 469);
}

static void add9()
{
    setTest("Add 9");
    big_integer n1 = big_integer(123);
    big_integer n2 = big_integer(345);
    big_integer n3 = big_integer(0001);

    assertEquals(n1 + n2 + n3, 469);
}

static void addRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        add("random " + to_string(i + 1), a, b);
    }
}

static void addSuite()
{
    add1();
    add2();
    add3();
    add4();
    add5();
    add6();
    add7();
    add8();
    add9();
}

/* ----------------- Sub ------------------ */

static void sub(const string &name, int a, int b)
{
    setTest("Sub " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    cout << "Calculating [" << a << "] - [" << b << "]" << endl;
    assertEquals(n1 - n2, a - b);
    cout << "Calculating [" << b << "] - [" << a << "]" << endl;
    assertEquals(n2 - n1, b - a);
}

static void sub1()
{
    sub("1", 5, 9);
}

static void sub2()
{
    sub("2", 5, -9);
}

static void sub3()
{
    sub("3", -5, -9);
}

static void sub4()
{
    setTest("Sub 4");
    big_integer n1 = big_integer(-5);
    big_integer n2 = big_integer("90230239468");
    big_integer n3 = big_integer("-643347349");
    assertEquals(n1 - n1 - n1 - n1, 10);
    assertEquals(n2 - n3, "90873586817");
}

static void sub5()
{
    setTest("Sub 5");
    big_integer n1 = big_integer(-52);
    big_integer n2 = big_integer("20");
    big_integer n3 = big_integer("-41");
    n1 -= n1;
    assertEquals(n1, "0");
    n2 -= n3;
    assertEquals(n2, 61);
    assertEquals(n3, "-41");
}

static void subRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        sub("random " + to_string(i + 1), a, b);
    }
}

static void subSuite()
{
    sub1();
    sub2();
    sub3();
    sub4();
    sub5();
}

/* ----------------- Mlt ------------------ */

static void mlt(const string &name, int a, int b)
{
    setTest("Mlt " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    cout << "Calculating [" << a << "] * [" << b << "]" << endl;
    assertEquals(n1 * n2, a * b);
    cout << "Calculating [" << b << "] * [" << a << "]" << endl;
    assertEquals(n2 * n1, b * a);
}

static void mlt1()
{
    mlt("1", 2, 8);
}

static void mlt2()
{
    mlt("2", 2, -4);
}

static void mlt3()
{
    mlt("3", -2, -4);
}

static void mlt4()
{
    mlt("4", 0, -4);
}

static void mlt5()
{
    mlt("5", 1, -4);
}

static void mlt6()
{
    mlt("6", -31, 517);
}

static void mlt7()
{
    setTest("Mlt 7");
    big_integer n1 = big_integer(-1);
    big_integer n2 = big_integer(5);
    n1 = (n2 *= n2) * n2;
    assertEquals(n1, 625);
    assertEquals(n2, 25);
    n1 *= (n2 * n1 * 2) * 0 * (-1 * -4 * -2 * 3);
    assertEquals(n1, 0);
}

static void mltRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        mlt("random " + to_string(i + 1), a, b);
    }
}

static void mltSuite()
{
    mlt1();
    mlt2();
    mlt3();
    mlt4();
    mlt5();
    mlt6();
    mlt7();
}

/* ----------------- Div ------------------ */

static void div(const string &name, int a, int b)
{
    setTest("Div " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    cout << "Calculating [" << a << "] / [" << b << "]" << endl;
    assertEquals(n1 / n2, (b == 0 ? 0 : a / b));
    cout << "Calculating [" << b << "] / [" << a << "]" << endl;
    assertEquals(n2 / n1, (a == 0 ? 0 : b / a));
}

static void div1()
{
    div("1", 11, 5);
}

static void div2()
{
    div("2", -15, 5);
}

static void div3()
{
    div("3", -24, -8);
}

static void div4()
{
    div("4", 993, 8);
}

static void div5()
{
    div("5", -54326, -755);
}

static void divRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        div("random " + to_string(i + 1), a, b);
    }
}

static void divSuite()
{
    div1();
    div2();
    div3();
    div4();
    div5();
}

/* ----------------- Mod ------------------ */

static void mod(const string &name, int a, int b)
{
    setTest("Mod " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    cout << "Calculating [" << a << "] % [" << b << "]" << endl;
    assertEquals(n1 % n2, (b == 0 ? 0 : a % b));
    cout << "Calculating [" << b << "] % [" << a << "]" << endl;
    assertEquals(n2 % n1, (a == 0 ? 0 : b % a));
}

static void mod1()
{
    mod("1", 11, 5);
}

static void mod2()
{
    mod("2", -16, 5);
}

static void mod3()
{
    mod("3", -23, -8);
}

static void mod4()
{
    mod("4", 993, 8);
}

static void mod5()
{
    mod("5", -54326, -755);
}

static void mod6()
{
    setTest("Mod 6");
    big_integer n1 = big_integer(0);
    big_integer n2 = big_integer(5);
    big_integer n3 = big_integer(-5);
    assertEquals(n2 % n1, 0);
    assertEquals(n3 % n1, 0);
}

static void modRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        mod("random " + to_string(i + 1), a, b);
    }
}

static void modSuite()
{
    mod1();
    mod2();
    mod3();
    mod4();
    mod5();
    mod6();
}

/* ----------------- Otr ------------------ */

static void arith1()
{
    setTest("Arith 1");
    big_integer n1 = big_integer(5);
    big_integer n2 = big_integer(-1);
    big_integer n3 = big_integer(0);
    big_integer n4 = big_integer(9);

    assertEquals(n1 + n2 - n3 - n4, -5);
    assertEquals(n3 - n1 - n2 + n4, 5);
}

static void arithSuite()
{
    arith1();
}

/* ----------------- Cmp ------------------ */

static void cmp(const string &name, int a, int b)
{
    setTest("Cmp " + name);
    big_integer n1 = big_integer(a);
    big_integer n2 = big_integer(b);
    assertLarger(n1, n2, a > b);
    assertLarger(n2, n1, b > a);
    assertSmaller(n1, n2, a < b);
    assertSmaller(n2, n1, b < a);
}

static void cmp1()
{
    cmp("1", 7, 2);
}

static void cmp2()
{
    cmp("2", -7, -2);
}

static void cmp3()
{
    cmp("3", -7, 2);
}

static void cmp4()
{
    cmp("4", -1, -1);
}

static void cmp5()
{
    cmp("5", 3000, 2999);
}

static void cmp6()
{
    cmp("6", -3000, -2999);
}

static void cmpRnd()
{
    for (int i = 0; i < RND_ITER; i++)
    {
        int a, b;
        a = rndNum();
        b = rndNum();
        cmp("random " + to_string(i + 1), a, b);
    }
}

static void cmpSuite()
{
    cmp1();
    cmp2();
    cmp3();
    cmp4();
    cmp5();
    cmp6();
}

/* ---------------- Suites ----------------- */

static void rndSuite()
{
    if (!enableRnd)
    {
        return;
    }
    addRnd();
    subRnd();
    mltRnd();
    divRnd();
    modRnd();
    cmpRnd();
}

static void allSuites()
{
    ctrSuite();
    addSuite();
    subSuite();
    mltSuite();
    divSuite();
    modSuite();
    arithSuite();
    cmpSuite();
    rndSuite();
}

/* ---------------- Main ----------------- */

int main()
{
    std::srand(std::time(nullptr));
    failCount = totalCount = 0;
    cout << "\n\n ----------- C++ Ex1 Tests ----------- \n\n";
    allSuites();
    cout.flush();
    if (failCount == 0)
    {
        cout << "\n\nAll [" << totalCount << "] checks have passed!" << endl;
    }
    else
    {
        cout << "\n\n[" << failCount << "] out of [" << totalCount << "] checks have failed!"
             << endl << "Checks that failed are marked in red." << endl;
    }
    cerr.flush();
}