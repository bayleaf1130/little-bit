# little-bit
C++ 14 compile time and stack based bit library... </br>
<h4>Details:</h4> </br>
  1. Implemented using new C++ 11/14 features like constexpr and variadic templates </br>
  2. Completely templated for integral types especially standard types <cstdint> *cough* </br>
  3. Provides a complete set of bitwise procedural routines </br>
  4. 'Bits' class allows extreme manipulation and fine tuning of integral types in the bit form </br>
  5. Everything is included in the header files. No extra linking needed. </br>
  6. Does not rely on the STL and with a little modification can not rely on the Standard Library at all. </br>
  7. Variadic templates allow bit building and inserting at compile time.</br>
  8. The class and functions are type safe and require explicit casting to change types</br>
</br>
</br>
<h4>Ideas: </h4></br>
<p>
  I wanted to do some bit manipulation and learn some more C++ so I simply set out on my journey. The library has not been
  optimized as of yet but it is relatively fast since most of the computation can be dealt with at compile time. The library
  is also fully featured for each integral type.
 </br></br>
  In total size the library does not penalize you for what you don't use. Templates are only generated for the code that is   used. The function and 'Bits' class will only be generated if used in the code. The rest of the code will be left out of the 
  final executable.
</p>
</br></br>
<h4>Thoughts:</h4></br>
<p>
'little-bit' is my first library attempt, and I know its a bit daunting especially in C++ but I wanted to try it.
 I would appreciate any help or comments given to help me improve my library or 'attempt' at it. Any ideas or requests? Let me     know!
</p>  
</br></br>
 Email me @ bailey.kocin@gmail.com

