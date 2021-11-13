#include <cstddef>
template<typename T, std::size_t N>
constexpr std::size_t foo(T  (&)[N]); // { return N;}

int main()
{
	int a[5];
	foo(a);
}
