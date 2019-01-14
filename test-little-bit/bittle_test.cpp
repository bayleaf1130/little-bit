/*
 * author: bayleaf
 * date: 1/8/2019
 * file: bittle_test.hpp
 * purpose: bitwise functions
 */






#include "bittle.hpp"
#include <cstdlib>


int main(int argc, char** argv)
{
  using namespace bittle;
  constexpr Bits64U a(100);
  Bits32 b(200);
  auto c = a + b;
  Bits64 d = c * a;
  constexpr Bits64 e = a;
  std::cout << c.value() << std::endl;
  std::cout << a.toString() << std::endl;
  std::cout << static_cast<uint64_t>(d) << std::endl;
  std::cout << Bits32(c).value() << std::endl;









  return EXIT_SUCCESS;
}
