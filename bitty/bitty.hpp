/*
 * author: bayleaf
 * date: 1/8/2019
 * file: bitty.hpp
 * purpose: bitwise functions
 */


#ifndef BITTY_HPP
#define BITTY_HPP




#include <iostream>
#include <string>
#include <cstdint>
#include <utility>
#include <vector>
#include <array>


namespace bitty {

/* namespace: bitty
 * Contains bit/byte methods on generic cstdint integral types
 * and regular integral types.
 * The class Bittle is here as well.
 */

 /* To Do List:
	* Add Hamming Distance Methods
	* Add Total Hamming Distance Methods
	* Add other cool bitwise methods
	* Add the rest of the overloaded operators
	* Add Invert every other bit methods
	* Add rightNBits()
	* Add rightLBits()
	* Add rightNBytes()
	* Add leftNBytes()
	* Add toLittleEndian()
	* Add toBigEndian()
	* Static Method to check byte order
	* Make it iterable so the STL works on it
	* Research Above STL Requirements
	*/

static constexpr int BIT_SIZE = 8;

/* reverse_bits
 * reverse number 'n's bits
 * return a new value
 */
template<typename T = uint64_t>
constexpr T reverse_bits(T n)
{
	T ret = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		ret = (ret << 1) | ((n >> i) & 1);
	}

	return ret;
}

/* count_ones
 * count number of set bits in 'n'
 * return set bit count
 */
template<typename T = uint64_t>
constexpr uint32_t count_ones(T n)
{
	uint32_t cnt = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		if(n & (1 << i)) cnt++;
	}

	return cnt;
}


/* count_zeroes
 * count number of not set bits in 'n'
 * return not set bit count
 */
template<typename T = uint64_t>
constexpr uint32_t count_zeroes(T n)
{
	uint32_t cnt = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		if(!(n & (1 << i))) cnt++;
	}

	return cnt;
}

/* reverse_bytes
 * reverse bytes (size 8)
 * return reversed number
 */
template<typename T = uint64_t>
constexpr T reverse_bytes(T n)
{
	int l = 0;
	int r = sizeof(T) - 1;
	while(l < r)
			std::swap(*(reinterpret_cast<uint8_t*>(&n) + l++),
					  *(reinterpret_cast<uint8_t*>(&n) + r--));
	return n;
}


/* check_bit
 * checks if bit targ in n is set
 * returns 1 or 0
 */
template <typename T = uint64_t>
constexpr T check_bit(T n, int targ)
{
  if (targ < 0 || targ > sizeof(n) * BIT_SIZE)
	return n;

  return n >> (targ & 1);
}

/* set_bit
 * sets bit targ in n
 * returns new number
 */
template <typename T = uint64_t>
constexpr T set_bit(T n, int targ)
{
  if (targ < 0 || targ > sizeof(n) * BIT_SIZE)
	return n;

   return n | (1 << targ);
}

/* toggle_bit
 * toggles bit on and off using xor (^)
 * returns toggled number
 */
template <typename T = uint64_t>
constexpr T toggle_bit(T n, int targ)
{

 if (targ < 0 || targ > sizeof(n) * BIT_SIZE)
	return n;

  return n ^ (1 << targ);
}

/* clear_bit
 * clears a bit targ in n
 * returns new number
 */
template <typename T = uint64_t>
constexpr T clear_bit(T n, int targ)
{
  if (targ < 0 || targ > sizeof(n) * BIT_SIZE)
	return n;

   return n & (~(1 << targ));
}

/* Only use the STL functions if its defined */

/* as_vect
 * Return an int : vector of 1's and 0's
 */
template <typename T = uint64_t>
constexpr std::vector<int> as_vect(T n)
{
	std::vector<int> v(sizeof(T) * BIT_SIZE, 0);

	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
		v[i] = (n >> i) & 1;

	return v;
}

/* as_bvect
 * Return an bool : vector of 1's and 0's
 */
template <typename T = uint64_t>
constexpr std::vector<bool> as_bvect(T n)
{
	std::vector<bool> v(sizeof(T) * BIT_SIZE, 0);

	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
		v[i] = ((n >> i) & 1) ? true : false;

	return v;
}


/* as_farray
 * Return an int : array of 1's and 0's
 */
template <typename T = uint64_t>
constexpr std::array<int, sizeof(T) * 8> as_farray(T n)
{
	std::array<int, sizeof(T) * BIT_SIZE> arr;

	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
		arr[i] = (n >> i) & 1;

	return arr;
}


/* hamming_distance
 * Find the number of different bits between
 * two fixed size numbers
 * returns the difference
 */
template <typename T = uint64_t>
constexpr int hamming_distance(const T& x, const T& y)
{
	int diff = 0;
	for(int i = 0; i < sizeof(T) * BIT_SIZE; ++i)
	{
		if ((x & (1 << i)) != (y & (1 << i))) diff++;
	}
	return diff;
}


template <typename T = uint64_t>
class Bittle;

template <typename T = uint64_t>
constexpr std::ostream& operator<<(std::ostream& left, Bittle<T>& right);

template <typename T = uint64_t>
constexpr std::istream& operator>>(std::istream&, Bittle<T>& right);

/* Friend operators Defined above */

template <typename T>
class Bittle
{
  /* The type must be integral */
  static_assert(std::is_integral<T>::value, "T must be an integral type");

	using value_type = T;
	using ref_type = T&;

	/* Implement stuff to be an iterable class */
	public:
		constexpr Bittle(value_type num) noexcept : number(num) {}

    /* Copy Ctor */
		template <typename G = uint64_t>
		constexpr Bittle(const Bittle<G>& right) noexcept
		{
		    this->number = static_cast<value_type>(right.value());
		}

    /* Move ctor */
		template <typename G = uint64_t>
		constexpr Bittle(Bittle<G>&& right) noexcept
		{
		    this->number = static_cast<value_type>(right.value());
		}

    /* Copy operator= */
		template <typename G = uint64_t>
		constexpr Bittle& operator=(const Bittle<G>& right) noexcept
		{
		    if(this == &right)
		        return *this;

		    this->number = static_cast<value_type>(right.value());
		    return *this;
		}

    /* Move operator= */
		template <typename G = uint64_t>
		constexpr Bittle& operator=(Bittle<G>&& right) noexcept
		{
		     if(this == &right)
		        return *this;

		    this->number = static_cast<value_type>(right.value());
		    return *this;
		}

    /* dtor */
		~Bittle() = default;

		/* Member Methods */

    /* name: reverseBits
     * desc: reverse the bits
     * returns: *this
     */
		constexpr Bittle& reverseBits()
		{
			this->number = bitty::reverse_bits<value_type>(this->number);
			return *this;
		}

    /* name: reverseBytes
     * desc: reverse the bytes
     * returns: *this
     */
		constexpr Bittle& reverseBytes()
		{
			this->number = bitty::reverse_bytes<value_type>(this->number);
			return *this;
		}

    /* name: ones
     * desc: counts the one bits
     * returns: number of one bits
     */
		constexpr uint32_t ones() const
		{
			return bitty::count_ones<value_type>(this->number);
		}

    /* name: zeroes
     * desc: counts the zero bits
     * returns: number of zero bits
     */
		constexpr uint32_t zeroes() const
		{
			return bitty::count_zeroes<value_type>(this->number);
		}

    /* name: toggleBit
     * desc: toggles the bit number targ (1 - 32)
     * returns: *this
     */
		constexpr Bittle& toggleBit(int targ)
		{
			this->number = bitty::toggle_bit<value_type>(this->number, targ);
			return *this;
		}

    /* name: setBit
     * desc: sets the bit number targ (1 - 32)
     * returns: *this
     */
		constexpr Bittle& setBit(int targ)
		{
			this->number = bitty::set_bit<value_type>(this->number, targ);
			return *this;
		}

    /* name: clearBit
     * desc: clears the bit number targ (1 - 32)
     * returns: *this
     */
		constexpr Bittle& clearBit(int targ)
		{
			this->number = bitty::clear_bit<value_type>(this->number, targ);
			return *this;
		}

    /* name: checkBit
     * desc: checks the bit number targ (1 - 32)
     * returns: bool
     */
		constexpr bool checkBit(int targ) const
		{
			return bitty::check_bit<value_type>(this->number, targ) != 0 ? true : false;
		}

    /* name: negate
     * desc: negate the number
     * returns: *this
     */
		constexpr Bittle& negate()
		{
			this->number *= -1;
			return *this;
		}

    /* name: add
     * desc: add num to *this
     * returns: *this
     */
		constexpr Bittle& add(const ref_type num)
		{
			this->number += num;
			return *this;
		}

    /* name: subtract
     * desc: subtract num to *this
     * returns: *this
     */
		constexpr Bittle& subtract(const ref_type num)
		{
			this->number -= num;
			return *this;
		}

    /* name: multiply
     * desc: multiply num to *this
     * returns: *this
     */
		constexpr Bittle& multiply(const ref_type num)
		{
			this->number *= num;
			return *this;
		}

    /* name: divide
     * desc: divide num to *this
     * returns: *this
     */
		constexpr Bittle& divide(const ref_type num)
		{
			this->number /= num;
			return *this;
		}

    /* name: switchByteOrder
     * desc: reverses the bytes
     * returns: Bittle
     */
		constexpr Bittle switchByteOrder() const
		{
			Bittle temp(this->number);
			temp.reverseBytes();
			return temp;
		}

    /* name: hammingDistance
     * desc: finds number of different bits
     * returns: number of different bits
     */
		constexpr int hammingDistance(const Bittle& right)
		{

			return bitty::hamming_distance<value_type>(this->number, right.number);
		}

    /* name: hammingDistance
     * desc: finds number of different bits
     * returns: number of different bits
     */
    constexpr int hammingDistance(const ref_type right)
		{

			return bitty::hamming_distance<value_type>(this->number, right);
		}

    /* name: value
     * desc: gets value
     * returns: value
     */
		constexpr value_type value() const
		{
			return this->number;
		}

    /* name: asVector
     * desc: creates an int vector
     * returns: int vector
     */
    constexpr std::vector<int> asVector() const
    {
      return bitty::as_vect<value_type>(this->number);
    }

    /* name: asBoolVector
     * desc: creates an bool vector
     * returns: bool vector
     */
    constexpr std::vector<bool> asBoolVector() const
    {
      return bitty::as_bvect<value_type>(this->number);
    }

    /* name: asFixedArray
     * desc: creates a fixed size array
     * returns: fixed size array
     */
    constexpr std::array<int, sizeof(value_type) * BIT_SIZE> asFixedArray() const
    {
      return bitty::as_farray<value_type>(this->number);
    }

    /* name: toString
     * desc: creates a string version of the number from bits
     * returns: bit string
     */
		constexpr std::string toString() const
		{
			std::string temp;
            for(int i = size - 1; i >= 0; --i)
            {
                temp.append(std::to_string((this->number >> i) & 1));
            }

            return temp;
		}

    /* name: toStringReverse
     * desc: creates a string version of the number from bits in reverse
     * returns: bit string
     */
    constexpr std::string toStringReverse() const
    {
      std::string temp;
            for(int i = 0; i < size; ++i)
            {
                temp.append(std::to_string((this->number >> i) & 1));
            }

            return temp;
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

		friend std::ostream& operator<< <T> (std::ostream& left, Bittle<T>& right);
		friend std::istream& operator>> <T> (std::istream&, Bittle<T>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bittle<C> operator+ (Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bittle<C> operator- (Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bittle<C> operator* (Bittle<G>& left, const Bittle<F>& right);

	  template <typename G, typename F, typename C>
		constexpr friend Bittle<C> operator/ (Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F, typename C>
		constexpr friend Bittle<C> operator% (Bittle<G>& left, const Bittle<F>& right);



		/* Relational Operators */
		template <typename G, typename F>
	    constexpr friend bool operator==(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator!=(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator<(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator>(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator>=(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		constexpr friend bool operator<=(Bittle<G>& left, const Bittle<F>& right);

		/* Logical Operators */
		template <typename G, typename F>
		friend bool operator&&(Bittle<G>& left, const Bittle<F>& right);

		template <typename G, typename F>
		friend bool operator||(Bittle<G>& left, const Bittle<F>& right);

		/* Preincrement */
		constexpr Bittle& operator++()
		{
		    this->number++;
		    return *this;
		}

		/* Postincrement */
		constexpr Bittle operator++(int n)
		{
		    Bittle temp(*this);
		    operator++();
		    return temp;

		}

		/* Predecrement */
	    constexpr Bittle& operator--()
		{
		    this->number--;
		    return *this;
		}

		/* Postdeccrement */
		constexpr Bittle operator--(int n)
		{
		    Bittle temp(*this);
		    operator--();
		    return temp;

		}

		/* Bool operator */
		explicit operator bool()
		{
			return this-> number != 0 ? true : false;
		}

		/* Self Arithmitic Changing Operators */
		Bittle& operator*=(const Bittle& rhs)
		{
			this->number *= rhs.number;
			return *this;
		}

		Bittle& operator+=(const Bittle& rhs)
		{
			this->number += rhs.number;
			return *this;
		}

		Bittle& operator-=(const Bittle& rhs)
		{
			this->number -= rhs.number;
			return *this;
		}

		Bittle& operator/=(const Bittle& rhs)
		{
			this->number /= rhs.number;
			return *this;
		}

		Bittle& operator%=(const Bittle& rhs)
		{
			this->number %= rhs.number;
			return *this;
		}

		/* Logical Operators */
		bool operator!() const
		{
			return !(*this);
		}

		/* Access Operators */

		int8_t& operator[](std::size_t idx)
		{
			if (idx >= 0 && idx < sizeof(value_type))
				return *(reinterpret_cast<int8_t*>(&(this->number)) + idx);
			else
				return *reinterpret_cast<int8_t*>(&(this->number));
		}


		/* Bitwise operators */


     /* Static member methods */
		static constexpr bool isLittleEndian()
		{
			uint16_t i = 1;
			if(*reinterpret_cast<char*>(&i))
				return true;
			else
				return false;
		}

		static constexpr bool isBigEndian()
		{
			uint16_t i = 1;
			if(*reinterpret_cast<char*>(&i))
				return false;
			else
				return true;
		}


	private:
		T number = T();
		const int size = BIT_SIZE * sizeof(T);


};

template <typename T>
constexpr std::ostream& operator<<(std::ostream& left, Bittle<T>& right)
{
	left << "Decimal: " << right.number
       << "\nBinary: " << right.toString()
       << '\n';

	return left;
}

template <typename T>
constexpr std::istream& operator>>(std::istream& left, Bittle<T>& right)
{
	left >> right.number;
	return left;
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bittle<C> operator+(Bittle<G>& left, const Bittle<F>& right)
{
	if (left.size > right.size)
	    return Bittle<C>(static_cast<G>(left.number + right.number));
	else
	    return Bittle<C>(static_cast<F>(left.number + right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bittle<C> operator-(Bittle<G>& left, const Bittle<F>& right)
{
	if (left.size > right.size)
	    return Bittle<C>(static_cast<G>(left.number - right.number));
	else
	    return Bittle<C>(static_cast<F>(left.number - right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bittle<C> operator*(Bittle<G>& left, const Bittle<F>& right)
{
    if (left.size > right.size)
	    return Bittle<C>(static_cast<G>(left.number * right.number));
	else
	    return Bittle<C>(static_cast<F>(left.number * right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bittle<C> operator/ (Bittle<G>& left, const Bittle<F>& right)
{
	 if (left.size > right.size)
	    return Bittle<C>(static_cast<G>(left.number / right.number));
	else
	    return Bittle<C>(static_cast<F>(left.number / right.number));
}

template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t>
constexpr Bittle<C> operator% (Bittle<G>& left, const Bittle<F>& right)
{
	 if (left.size > right.size)
	    return Bittle<C>(static_cast<G>(left.number % right.number));
	else
	    return Bittle<C>(static_cast<F>(left.number % right.number));
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator==(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number == right.number;
}

 template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator!=(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number != right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator<(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number < right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator>(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number > right.number;
}

template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator>=(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number >= right.number;
}

  template <typename G = uint64_t, typename F = uint64_t>
constexpr bool operator<=(Bittle<G>& left, const Bittle<F>& right)
{
    return left.number <= right.number;
}

 template <typename G = uint64_t, typename F = uint64_t>
bool operator&&(Bittle<G>& left, const Bittle<F>& right)
{
	 return bool(left) && bool(right);
}

 template <typename G = uint64_t, typename F = uint64_t>
bool operator||(Bittle<G>& left, const Bittle<F>& right)
{
	 return bool(left) || bool(right);
}

/* Declarations for ease of use */

/* Unsigned */
using Bittle64U = Bittle<uint64_t>;
using Bittle32U = Bittle<uint32_t>;
using Bittle16U = Bittle<uint16_t>;
using Bittle8U = Bittle<uint8_t>;

/* Signed */
using Bittle64 = Bittle<int64_t>;
using Bittle32 = Bittle<int32_t>;
using Bittle16 = Bittle<int16_t>;
using Bittle8 = Bittle<int8_t>;

/* Other integral types */
using BittleInt = Bittle<int>;
using BittleShort = Bittle<short>;
using BittleLong = Bittle<long>;
using BittleChar = Bittle<char>;

}



 #endif
