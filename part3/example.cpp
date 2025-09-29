#include <fsm/utils/static_string.h>
#include <cstdio>

void test()
{
    constexpr static_string first{"<"};
    constexpr static_string second{"hello"};
    constexpr static_string third{">"};
    constexpr static_string result = first + second + third;
    puts(result.data());
}

int main()
{
    test();
    return 0;
}
