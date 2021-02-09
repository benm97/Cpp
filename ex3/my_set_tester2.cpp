
#include <string>
#include <iostream>
#include "my_set.h"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }
    int num = stoi(argv[1]);
    switch (num)
    {
        case 1:
        {
            my_set<int> s1;
            s1.insert(1);
            s1.insert(2);
            s1.insert(2);
            s1.insert(3);
            cout << (3 == s1.size());
            break;
        }

        case 2:
        {
            char a1[] = {'a', 'b', 'b', 'd', 'e'};
            my_set<char> c1(a1, a1 + 5);

            my_set<char> c2;
            for (auto it = c1.cbegin(); it != c1.cend(); ++it)
            {
                c2.insert(*it);
            }
            if (c2.size() != 4)
            {
                return 0;
            }
            c2.erase (c2.find('a'));
            c2.erase (c2.find('b'));
            c2.erase (c2.find('d'));
            c2.erase (c2.find('e'));
            cout << c2.empty();
            break;
        }

        case 3:
        {
            double a2[] = {0.1, 1.0, 0.0, 1.1};
            my_set<double> d1(a2, a2 + 4);
            d1.erase(d1.find(0.1));
            d1.erase(d1.find(0.0));
            d1.erase(d1.find(1.1));
            d1.erase(d1.find(1.0));
            cout << d1.empty();
            break;
        }

        case 4:
        {
            double a2[] = {0.1, 1.0, 0.0, 1.1};
            my_set<double> d1(a2, a2 + 4);
            my_set<double> d2(d1);
            d2.erase(d1.find(0.1));
            d2.erase(d1.find(0.0));
            d2.erase(d1.find(1.1));
            d2.erase(d1.find(1.0));
            cout << d2.empty();
            break;
        }

        case 5:
        {
            char a1[] = {'e', 'b', 'd', 'd', 'a'};
            my_set<char> c1(a1, a1 + 5);

            my_set<char> c2;
            for (auto it = c1.cbegin(); it != c1.cend(); ++it)
            {
                c2.insert(*it);
            }
            int i = 0;
            char a2[] = {'a', 'b', 'd', 'e'};
            for (auto it = c1.cbegin(); it != c1.cend(); ++it, i++)
            {
                if (*it != a2[i])
		{
                    return 0;
		}
            }
            i--;
            for (auto it = c1.crbegin(); it != c1.crend(); ++it, i--)
            {
                if (*it != a2[i])
		{
                    return 0;
		}
            }
            if (c2.size() != 4)
            {
                return 0;
            }
            c2.erase (c2.find('a'));
            c2.erase (c2.find('b'));
            c2.erase (c2.find('d'));
            c2.erase (c2.find('e'));
            cout << c2.empty();
            break;
        }
        case 6:
        {
            int myints[]={12,75,10,32,20,25};
            my_set<int> first (myints,myints+3);     // 10,12,75
            my_set<int> second (myints+3,myints+6);  // 20,25,32

            first.swap(second);

            int i = 0;
            int a[] = {20,25,32};
            int b[] = {10,12,75};
            for (auto it=first.cbegin(); it!=first.cend(); ++it, i++)
            {
                if (*it !=  a[i])
                    return 0;
            }
            i = 0;
            for (auto it=second.cbegin(); it!=second.cend(); ++it, i++)
            {
                if (*it !=  b[i])
                    return 0;
            }
            cout << (first.size() == second.size());
            break;
        }
        default:
            break;
    }
    return 0;
}
