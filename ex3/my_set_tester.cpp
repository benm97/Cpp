
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
			//for(const auto i : c1)
			for (auto i=c1.cbegin(); i != c1.cend(); ++i)
            {
                c2.insert(*i);
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
        default:
            break;
    }
    return 0;
}
