/*
 * author: bayleaf
 * date: 1/8/2019
 * file: bittle.hpp
 * purpose: bitwise functions
 */


#ifndef BITTLE_TEST_HPP
#define BITTLE_TEST_HPP



#ifdef BITTLE_STANDARD
	#include <iostream>
	#include <string>
	#include <iomanip>
	#include <utility>
#endif

// Must include
#include <cstdint>
#include <type_traits>
#include <functional>



 /* If the BITTLE_STANDARD MACRO IS NOT DEFINED THEN STREAMS AND STRING
  * will be excluded */

namespace bittle {

/* namespace: bittle
 * Contains bit/byte methods on generic cstdint integral types
 * and regular integral types.
 * The class Bits is here as well.
 */

 /* To Do List:
	* Add Total Hamming Distance Methods
	* Invert every other bit method
	* Grab rightNBits as a Bits object method
	* Grab leftNBits as a Bits object methods
	* Make it iterable so the STL works on it but make it optional?
	*/

static constexpr int BIT_SIZE = 8;

/* name: reverse_bits
 * desc: everse number 'n's bits
 * returns: a new value
 */
template<typename T = uint64_t>
constexpr T reverse_bits(const T& n) noexcept
{
	T ret = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		ret = (ret << 1) | ((n >> i) & 1);
	}

	return ret;
}

/* name: count_ones
 * desc: count number of set bits in 'n'
 * returns: set bit count
 */
template<typename T = uint64_t>
constexpr uint32_t count_ones(const T& n) noexcept
{
	uint32_t cnt = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		if(n & (1 << i)) cnt++;
	}

	return cnt;
}


/* name: count_zeroes
 * desc: count number of not set bits in 'n'
 * returns: not set bit count
 */
template<typename T = uint64_t>
constexpr uint32_t count_zeroes(const T& n) noexcept
{
	uint32_t cnt = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		if(!(n & (1 << i))) cnt++;
	}

	return cnt;
}

/* name: reverse_bytes
 * desc: reverse bytes (size 8)
 * returns: reversed number
 */
template<typename T = uint64_t>
constexpr T reverse_bytes(const T& n) noexcept
{
	int l = 0;
	int r = sizeof(T) - 1;
	int t = n;
	while(l < r)
			std::swap(*(reinterpret_cast<uint8_t*>(&t) + l++),
					  *(reinterpret_cast<uint8_t*>(&t) + r--));
	return t;
}


/* name: check_bit
 * desc: checks if bit targ in n is set
 * returns: 1 or 0
 */
template <typename T = uint64_t>
constexpr T check_bit(const T& n, int8_t targ) noexcept
{
  if (targ < 1 || targ > sizeof(n) * BIT_SIZE)
	return n;

  return n >> ((targ - 1) & 1);
}

/* name: set_bit
 * desc: sets bit targ in n
 * returns: new number
 */
template <typename T = uint64_t>
constexpr T set_bit(const T& n, int8_t targ) noexcept
{
  if (targ < 1 || targ > sizeof(n) * BIT_SIZE)
	return n;

   return n | (1 << (targ - 1));
}

/* name: toggle_bit
 * desc: toggles bit on and off using xor (^)
 * returns: toggled number
 */
template <typename T = uint64_t>
constexpr T toggle_bit(const T n, int8_t targ) noexcept
{

 if (targ < 1 || targ > sizeof(n) * BIT_SIZE)
	return n;

  return n ^ (1 << (targ - 1));
}

/* name: clear_bit
 * desc: clears a bit targ in n
 * returns: new number
 */
template <typename T = uint64_t>
constexpr T clear_bit(const T& n, int8_t targ) noexcept
{
  if (targ < 1 || targ > sizeof(n) * BIT_SIZE)
	return n;

   return n & (~(1 << (targ - 1)));
}

/* name: flip_bit
 * desc: flips the bit in n at targ
 * returns: the modified number
 */
 template<typename T = uint64_t>
 constexpr T flip_bit(const T& n, int8_t targ) noexcept
 {
	 if((1 << (targ - 1)) & n)
		 return (~(1 << (targ - 1)) & n);
	 else
		 return ((1 << (targ - 1)) ^ n);
 }



/* name: hamming_distance
 * desc: Find the number of different bits between
 * two fixed size numbers
 * returns: the difference
 */
template <typename T = uint64_t>
constexpr int hamming_distance(const T& x, const T& y) noexcept
{
	int diff = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
		if ((x & (1 << i)) != (y & (1 << i))) diff++;

	return diff;
}

/* name: right_bits
 * desc: grabs the n right bits
 * returns: the new numbers
 */
 template <typename T = uint64_t>
 constexpr T right_bits(const T& num, const int num_bits)
 {
	 T ret = 0;
	 T temp = 0;
	 for(int i = 0; i < num_bits; i++)
	 {
		 temp = (num >> i) & 1;
		 ret |= temp << i;
	 }

	 return ret;
 }


 /* name: left_bits
  * desc: grabs the n left bits
  * returns: the new numbers
  */
  template <typename T = uint64_t>
  constexpr T left_bits(const T& num, const int num_bits)
  {
 	 return num >> (sizeof(T) * BIT_SIZE) - num_bits - 1;
  }

template <typename T = uint64_t>
class Bits;

#ifdef BITTLE_STANDARD

	template <typename T = uint64_t>
	constexpr std::ostream& operator<<(std::ostream& left, Bits<T>& right);

	template <typename T = uint64_t>
	constexpr std::istream& operator>>(std::istream&, Bits<T>& right);

#endif

/* Friend operators Defined above */

template <typename T>
class Bits
{

	using ReduceOperator = std::function<T(T , T)>;


	/* The type must be integral and not a character type */
	static_assert(std::is_integral<T>::value,
	                "Template type T must be an integral type in class Bits");


	public:

		/*  One param ctor */
		explicit constexpr Bits(const T& k) noexcept : number(k) {}

		/*  ctor for an addrress of things */
		template <typename F>
		constexpr Bits(const F* ptr, const std::size_t& len) noexcept
		{
			for(int i = 0; i < len; i++)
				this->number |= (ptr[i] << (tsize - i - 1));
		}

		/* Copy Ctor */
		template <typename G = uint64_t>
		constexpr Bits(const Bits<G>& right) noexcept
		{
		    this->number = static_cast<T>(right.value());
		}

		/* Move ctor */
		template <typename G = uint64_t>
		constexpr Bits(Bits<G>&& right) noexcept
		{
		    this->number = static_cast<T>(right.value());
		}

		/* Copy operator= */
		template <typename G = uint64_t>
		constexpr Bits& operator=(const Bits<G>& right) noexcept
		{
		    if(reinterpret_cast<Bits*>(this) == reinterpret_cast<Bits*>(&right))
		        return *this;

		    this->number = static_cast<T>(right.value());
		    return *this;
		}

		/* Move operator= */
		template <typename G = uint64_t>
		constexpr Bits& operator=(Bits<G>&& right) noexcept
		{
		    if(reinterpret_cast<Bits*>(this) == reinterpret_cast<Bits*>(&right))
		        return *this;

		    this->number = static_cast<T>(right.value());
		    return *this;
		}


		/* dtor */
		~Bits() = default;

		/*
		 *
		 *
		 * Member Methods
		 *
		 *
		 */

		/*
		 *
		 *
		 * Non-Mutators
		 *
		 *
		 */

		/* name: value
		 * desc: gets value
		 * returns: value
		 */
		constexpr T value() const noexcept
		{
			return this->number;
		}

		constexpr T bits() const noexcept
		{
			return this->tsize;
		}

		/* name: hammingDistance
		 * desc: finds number of different bits
		 * returns: number of different bits
		 */
		constexpr int hammingDistance(const Bits& right) noexcept
		{
			return bittle::hamming_distance<T>(this->number, right.number);
		}

		/* name: hammingDistance
		 * desc: finds number of different bits
		 * returns: number of different bits
		 */
		constexpr int hammingDistance(const T& right) noexcept
		{
			return bittle::hamming_distance<T>(this->number, right);
		}

		 #ifdef BITTLE_STANDARD

			/*
			 * name: toString
			 * desc: creates a string version of the number from bits
			 * returns: bit string
			 */
			constexpr std::string toString() const noexcept
			{
				std::string temp;
	            for(int i = size - 1; i >= 0; --i)
	            {
	                temp.append(std::to_string((this->number >> i) & 1));
	            }

	            return temp;
			}

			/*
			 * name: toStringReverse
			 * desc: creates a string version of the number from bits in reverse
			 * returns: bit string
			 */
			constexpr std::string toStringReverse() const noexcept
			{
					std::string temp;
					for(int i = 0; i < size; ++i)
					{
						temp.append(std::to_string((this->number >> i) & 1));
					}

					return temp;
			}

		#endif


		/* name: ones
		 * desc: counts the one bits
		 * returns: number of one bits
		 */
		constexpr uint32_t ones() const noexcept
		{
			return bittle::count_ones<T>(this->number);
		}

		/* name: zeroes
		 * desc: counts the zero bits
		 * returns: number of zero bits
		 */
		constexpr uint32_t zeroes() const noexcept
		{
			return bittle::count_zeroes<T>(this->number);
		}

		/* name: checkBit
		 * desc: checks the bit number n (1 - 32)
		 * returns: bool
		 */
		constexpr bool checkBit(const T& n) const noexcept
		{
			return bittle::check_bit<T>(this->number, n) != 0 ? true : false;
		}

		/*
		 *
		 *
		 * Mutators
		 *
		 *
		 */

		/* name: setValue
		 * desc: set the current value
		 * returns: *this
		 */
		constexpr Bits& value(const T& n) noexcept
		{
		    this->number = n;
		    return *this;
		}

		/* name: reverseBits
		 * desc: reverse the bits
		 * returns: *this
		 */
		constexpr Bits& reverseBits() noexcept
		{
			this->number = bittle::reverse_bits<T>(this->number);
			return *this;
		}

		/* name: reverseBytes
		 * desc: reverse the bytes
		 * returns: *this
		 */
		constexpr Bits& reverseBytes() noexcept
		{
			this->number = bittle::reverse_bytes<T>(this->number);
			return *this;
		}

		/* name: toggleBit
		 * desc: toggles the bit number n (1 - 32)
		 * returns: *this
		 */
		constexpr Bits& toggleBit(const T& n) noexcept
		{
			this->number = bittle::toggle_bit<T>(this->number, n);
			return *this;
		}

		/* name: setBit
		 * desc: sets the bit number n (1 - 32)
		 * returns: *this
		 */
		constexpr Bits& setBit(const T& n) noexcept
		{
			this->number = bittle::set_bit<T>(this->number, n);
			return *this;
		}

		/* name: clearBit
		 * desc: clears the bit number n (1 - 32)
		 * returns: *this
		 */
		constexpr Bits& clearBit(const T& n) noexcept
		{
			this->number = bittle::clear_bit<T>(this->number, n);
			return *this;
		}

		/* name: flipBit
		 * desc: flips the bit at n, 0 -> 1 ,1 -> 0
		 * returns *this
		 */
		 constexpr Bits& flipBit(const T& n) noexcept
		 {
			 this->number = bittle::flip_bit<T>(this->number, n);
			 return *this;
		 }

		 /* name: rightBits
			* desc: retrieves new Bits Object of bits
			* returns new Bits
			*/
			constexpr Bits& rightBits(const T& n) noexcept
			{
				return Bits(right_bits<T>(this->number));
			}

			/* name: leftBits
 			* desc: retrieves new Bits Object of bits
 			* returns new Bits
 			*/
 			constexpr Bits& leftBits(const T& n) noexcept
 			{
 				return Bits(left_bits<T>(this->number));
 			}

		/* name: negate
		 * desc: negate the number
		 * returns: *this
		 */
		constexpr Bits& negate() noexcept
		{
			this->number *= -1;
			return *this;
		}

		/* name: clear
		 * desc: sets internal number to 0
		 * returns: *this
		 */
		constexpr Bits& clear() noexcept
		{
		    this->number = 0;
		    return *this;
		}

		/* name: add
		 * desc: add num to *this
		 * returns: *this
		 */
		constexpr Bits& add(const T& num) noexcept
		{
			this->number += num;
			return *this;
		}

		/* name: subtract
		 * desc: subtract num to *this
		 * returns: *this
		 */
		constexpr Bits& subtract(const T& num) noexcept
		{
			this->number -= num;
			return *this;
		}

		/* name: multiply
		 * desc: multiply num to *this
		 * returns: *this
		 */
		constexpr Bits& multiply(const T& num) noexcept
		{
			this->number *= num;
			return *this;
		}

		/* name: divide
		 * desc: divide num to *this
		 * returns: *this
		 */
		constexpr Bits& divide(const T& num) noexcept
		{
			this->number /= num;
			return *this;
		}

		/* name: mod
		 * desc: modulo on num
		 * returns: *this
		 */
		constexpr Bits& mod(const T& num) noexcept
		{
			this->number %= num;
			return *this;
		}


		/* name: invert
		 * desc: inverts bits
		 * returns: *this
		 */
		constexpr Bits& invert() noexcept
		{
			this->number = ~(this->number);
			return *this;
		}

		/* name: switchByteOrder
		 * desc: reverses the bytes
		 * returns: Bits
		 */
		constexpr Bits& switchByteOrder() const noexcept
		{
			this->reverseBytes();
			return *this;
		}

		/* Operators Below:
			Addition,
			Subtraction,
			Multiplication,
			Division,
			IAdd,
			ISubtract,
			IMultiplication,
			IDivision,
			Increment, Decrement,
			Stream Insertion, Extraction
			Bool Conversion Overload,
			Array Access,
			Bitwise ops,
			Relational Ops
		*/

		#ifdef BITTLE_STANDARD
			friend std::ostream& operator<< <T> (std::ostream& left, Bits<T>& right);
			friend std::istream& operator>> <T> (std::istream&, Bits<T>& right);
		#endif

		/* Arithmitic and bit operators */
		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator+ (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator- (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator* (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator/ (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator% (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator& (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator| (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator^ (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator<< (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator>> (const Bits<G>& left, const Bits<F>& right);

		/*
		 * Declartions only so far
		 *
		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator+ (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator- (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator* (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator/ (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator% (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator& (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator| (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator^ (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator<< (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator>> (const Bits<G>& left, const F& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator+ (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator- (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator* (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator/ (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator% (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator& (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator| (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator^ (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator<< (const F& left, const Bits<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bits<C> operator>> (const F& left, const Bits<F>& right);

		*
		*
		*/



		/* Relational Operators */
		template <typename G, typename F>
	    constexpr friend bool operator== (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator!= (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator< (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator> (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator>= (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator<= (const Bits<G>& left, const Bits<F>& right);

		/*
		 * Declartions only so far
		 *
		template <typename G, typename F>
	    constexpr friend bool operator== (const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator!= (const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator< (const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator> (const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator>= (const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator<= (const Bits<G>& left, const F& right);

		template <typename G, typename F>
	    constexpr friend bool operator== (const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator!= (const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator< (const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator> (const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator>= (const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator<= (const F& left, const Bits<G>& right);
		*
		*
		*/


		/* Logical Operators */
		template <typename G, typename F>
		constexpr friend bool operator&& (const Bits<G>& left, const Bits<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator|| (const Bits<G>& left, const Bits<F>& right);

		/*
		 * Declartions only so far
		 *
		template <typename G, typename F>
		constexpr friend bool operator&&(const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator||(const Bits<G>& left, const F& right);

		template <typename G, typename F>
		constexpr friend bool operator&&(const F& left, const Bits<G>& right);

		template <typename G, typename F>
		constexpr friend bool operator||(const F& left, const Bits<G>& right);
		*
		*
		*/


		/* Invert the bits */
		template<typename G>
		constexpr friend Bits<G> operator~ (const Bits<G>& right);

		/* Preincrement */
		constexpr Bits& operator++() noexcept
		{
		    this->number++;
		    return *this;
		}

		/* Postincrement */
		constexpr Bits operator++(int n) noexcept
		{
		    Bits temp(*this);
		    operator++();
		    return temp;

		}

		/* Predecrement */
	    constexpr Bits& operator--() noexcept
		{
		    this->number--;
		    return *this;
		}

		/* Postdeccrement */
		constexpr Bits operator--(int n) noexcept
		{
		    Bits temp(*this);
		    operator--();
		    return temp;

		}

		/* Conversion Operators */

		/* Bool operator */
		explicit operator bool() noexcept
		{
			return this-> number != 0 ? true : false;
		}

		/* Unsigned Versions */
		explicit operator uint64_t() noexcept
		{
			return static_cast<uint64_t>(this->number);
		}

		explicit operator uint32_t() noexcept
		{
			return static_cast<uint32_t>(this->number);
		}

		explicit operator uint16_t() noexcept
		{
			return static_cast<uint16_t>(this->number);
		}

		explicit operator uint8_t() noexcept
		{
			return static_cast<uint8_t>(this->number);
		}

		/* Signed versions */

		explicit operator int64_t() noexcept
		{
			return static_cast<int64_t>(this->number);
		}

		explicit operator int32_t() noexcept
		{
			return static_cast<int32_t>(this->number);
		}

		explicit operator int16_t() noexcept
		{
			return static_cast<int16_t>(this->number);
		}

		explicit operator int8_t() noexcept
		{
			return static_cast<int8_t>(this->number);
		}


		/* Self Arithmitic Changing Operators */
		Bits& operator*=(const T& n) noexcept
		{
			this->number *= n;
			return *this;
		}

		Bits& operator+=(const T& n) noexcept
		{
			this->number += n;
			return *this;
		}

		Bits& operator-=(const T& n) noexcept
		{
			this->number -= n;
			return *this;
		}

		Bits& operator/=(const T& n) noexcept
		{
			this->number /= n;
			return *this;
		}

		Bits& operator%=(const T& n) noexcept
		{
			this->number %= n;
			return *this;
		}

		Bits& operator<<=(const T& n) noexcept
		{
			this->number <<= n;
			return *this;
		}

		Bits& operator>>=(const T& n) noexcept
		{
			this->number >>= n;
			return *this;
		}

		Bits& operator|=(const T& n) noexcept
		{
			this->number |= n;
			return *this;
		}

		Bits& operator&=(const T& n) noexcept
		{
			this->number &= n;
			return *this;
		}

		Bits& operator^= (const T& n) noexcept
		{
			this->number ^= n.value();
			return *this;
		}


		Bits& operator*=(const Bits& n) noexcept
		{
			this->number *= n.value();
			return *this;
		}

		Bits& operator+=(const Bits& n) noexcept
		{
			this->number += n.value();
			return *this;
		}

		Bits& operator-=(const Bits& n) noexcept
		{
			this->number -= n.value();
			return *this;
		}

		Bits& operator/=(const Bits& n) noexcept
		{
			this->number /= n.value();
			return *this;
		}

		Bits& operator%=(const Bits& n) noexcept
		{
			this->number %= n.value();
			return *this;
		}

		Bits& operator<<=(const Bits& n) noexcept
		{
			this->number <<= n.value();
			return *this;
		}

		Bits& operator>>=(const Bits& n) noexcept
		{
			this->number >>= n.value();
			return *this;
		}

		Bits& operator|=(const Bits& n) noexcept
		{
			this->number |= n.value();
			return *this;
		}

		Bits& operator&=(const Bits& n) noexcept
		{
			this->number &= n.value();
			return *this;
		}

		Bits& operator^= (const Bits& n) noexcept
		{
			this->number ^= n.value();
			return *this;
		}

		/* Logical Operators */
		bool operator!() const noexcept
		{
			return !(*this);
		}

		/* Access Operators */

		int8_t& operator[](std::size_t idx) noexcept
		{
			if (idx >= 0 && idx < sizeof(T))
				return *(reinterpret_cast<int8_t*>(&(this->number)) + idx);
			else
				return *reinterpret_cast<int8_t*>(&(this->number));
		}


		/* Assignment Methods */

		/* name: insertRight
         * desc: pushes bits in on the right side of the digit
         * returns: *this
        */
		template <typename F>
		constexpr Bits& insertRight(F k) noexcept
		{
		   static_assert(std::is_integral<F>::value, "The type T must be integral");

			if (k != 0)
	        {
				*this <<= 1;
				*this |= 1;
	        }
	        else
	        {
				*this <<= 1;
	        }
	        return *this;
		}


		/* name: insertRight
         * desc: pushes bits in on the right side of the digit
         * returns: *this
        */
		template <typename F, typename... Fs>
		constexpr Bits& insertRight(F k, Fs... bits) noexcept
		{
		    static_assert(std::is_integral<F>::value, "The type T must be integral");
		    constexpr int sz = sizeof(T) * 8;
		    static_assert(sizeof...(Fs) <= sz, "Bits exceed maximum amount");

			if (k != 0)
	        {
				*this <<= 1;
				*this |= 1;
	        }
	        else
	        {
				*this <<= 1;
	        }


	        return insertRight(bits...);
		}


		/* name: insertLeft
         * desc: pushes bits in on the left side of the digit
         * returns: *this
        */
		template <typename F>
		constexpr Bits& insertLeft(F k) noexcept
		{
		   static_assert(std::is_integral<F>::value, "The type T must be integral");

	        if (k != 0 && tsize > 0)
				this->setBit(tsize--);
	        else
	           this->clearBit(tsize--);

	        tsize = sizeof(T) * 8;
			return *this;
		}

		/* name: insertLeft
         * desc: pushes bits in on the left side of the digit
         * returns: *this
        */
		template <typename F, typename... Fs>
		constexpr Bits& insertLeft(F k, Fs... bits) noexcept
		{
		    static_assert(std::is_integral<F>::value, "The type T must be integral");
		    constexpr int sz = sizeof(T) * 8;
		    static_assert(sizeof...(Fs) <= sz, "Bits exceed maximum amount");

	        if (k != 0 && tsize > 0)
				this->setBit(tsize--);
	        else
	           this->clearBit(tsize--);

	        return insertLeft(bits...);
		}

		/* name: assign
         * desc: assigns new bits to current value, overwriting completley
         * returns: *this
        */
		template <typename F>
		constexpr Bits& assign(F k) noexcept
		{
		   static_assert(std::is_integral<F>::value, "The type T must be integral");


	     	if (k != 0)
				this->setBit(1);
	        else
				this->clearBit(1);

			return *this;
		}

		/* name: assign
         * desc: assigns new bits to current value, overwriting completley
         * returns: *this
        */
		template <typename F, typename... Fs>
		constexpr Bits& assign(F k, Fs... bits) noexcept
		{
		    static_assert(std::is_integral<F>::value  , "The type T must be integral");

		    constexpr int sz = sizeof(T) * 8;
		    static_assert(sizeof...(Fs) <= sz, "Bits exceed maximum amount");

			if (k != 0)
	        {
				this->setBit(1);
				*this <<= 1;
	        }
	        else
	        {
				*this <<= 1;
				this->clearBit(1);
	        }

	        return assign(bits...);
		}

		/* Functional Methods */


		/* name: reduce
		 * desc: reduces the bits using an operator
		 * Returns: a value reduced
		 */
		T reduce(ReduceOperator func, T init) const
		{
			T val = init;
			T n = this->number;
			for(int i = 0; i <  tsize - 1; i+=2)
				val += func((n >> i) & 1, (n >> (i + 1)) & 1);

			return val;
		}


		/*
		 *
		 *
		 * Static Member Methods
		 *
		 *
		 */

		static constexpr bool isLittleEndian() noexcept
		{
			uint16_t i = 1;
			if(*reinterpret_cast<char*>(&i))
				return true;
			else
				return false;
		}

		static constexpr bool isBigEndian() noexcept
		{
			uint16_t i = 1;
			if(*reinterpret_cast<char*>(&i))
				return false;
			else
				return true;
		}

		template <typename F = uint64_t>
		static constexpr Bits build(F n)
		{
		    return Bits<F>(n);
		}


	private:
		T number = T();	// Defaults to integral default
		int8_t tsize = BIT_SIZE * sizeof(T); // For some special methods

};

#ifdef BITTLE_STANDARD

	template <typename T>
	constexpr std::ostream& operator<<(std::ostream& left, Bits<T>& right)
	{
		left << "Decimal: " <<  std::dec << right.number
				<< "\nBinary: " <<  right.toString()
				<< "\nHex: " <<  std::hex << right.number
				<< "\nOctal: " <<  std::oct << right.number
				<< "\n\n";

		return left;
	}

	template <typename T>
	constexpr std::istream& operator>>(std::istream& left, Bits<T>& right)
	{
		left >> right.number;
		return left;
	}

#endif

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator+(const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number + right.number));
	else
	    return Bits<C>(static_cast<F>(left.number + right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator-(const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number - right.number));
	else
	    return Bits<C>(static_cast<F>(left.number - right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator*(const Bits<G>& left, const Bits<F>& right)
{
    if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number * right.number));
	else
	    return Bits<C>(static_cast<F>(left.number * right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator/ (const Bits<G>& left, const Bits<F>& right)
{
	 if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number / right.number));
	else
	    return Bits<C>(static_cast<F>(left.number / right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator% (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number % right.number));
	else
	    return Bits<C>(static_cast<F>(left.number % right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator& (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number & right.number));
	else
	    return Bits<C>(static_cast<F>(left.number & right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator| (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number | right.number));
	else
	    return Bits<C>(static_cast<F>(left.number | right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator^ (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number ^ right.number));
	else
	    return Bits<C>(static_cast<F>(left.number ^ right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator<< (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number << right.number));
	else
	    return Bits<C>(static_cast<F>(left.number << right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bits<C> operator>> (const Bits<G>& left, const Bits<F>& right)
{
	if (left.tsize > right.tsize)
	    return Bits<C>(static_cast<G>(left.number >> right.number));
	else
	    return Bits<C>(static_cast<F>(left.number >> right.number));
}


template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator==(const Bits<G>& left, const Bits<F>& right)
{
    return left.number == right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator!=(const Bits<G>& left, const Bits<F>& right)
{
    return left.number != right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator<(const Bits<G>& left, const Bits<F>& right)
{
    return left.number < right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator>(const Bits<G>& left, const Bits<F>& right)
{
    return left.number > right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator>=(const Bits<G>& left, const Bits<F>& right)
{
    return left.number >= right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator<=(const Bits<G>& left, const Bits<F>& right)
{
    return left.number <= right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator&&(const Bits<G>& left, const Bits<F>& right)
{
	 return bool(left) && bool(right);
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator||(const Bits<G>& left, const Bits<F>& right)
{
	 return bool(left) || bool(right);
}

template <typename G>
constexpr Bits<G> operator~ (const Bits<G>& right)
{
	return Bits<G>(static_cast<G>(~right.number));
}

/* Declarations for ease of use */

/* Unsigned */
using Bits64U = Bits<uint64_t>;
using Bits32U = Bits<uint32_t>;
using Bits16U = Bits<uint16_t>;
using Bits8U = Bits<uint8_t>;

/* Signed */
using Bits64 = Bits<int64_t>;
using Bits32 = Bits<int32_t>;
using Bits16 = Bits<int16_t>;
using Bits8 = Bits<int8_t>;

/* Other integral types */
using BitsInt = Bits<int>;
using BitsShort = Bits<short>;
using BitsLong = Bits<long>;
using BitsChar = Bits<char>;

}

/* Build some test code */
/* Build some examples for usauge */




 #endif
