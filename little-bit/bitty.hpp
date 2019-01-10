/*
 * author: bayleaf
 * date: 1/8/2019
 * file: bitty.hpp
 * purpose: bitwise functions
 */
 
 
#ifndef BITTY_HPP
#define BITTY_HPP

#include <iostream>
#include <cstdint>
#include <utility>
#include <vector>
#include <array>

#define STL 1
#define FIXED 0
 
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
	
	/* reverse_bits
	 * reverse number 'n's bits
	 * return a new value
	 */
	template<typename T = uint64_t, int BYTESIZE = 8>
	constexpr T reverse_bits(T n)
	{
		T ret = 0;
		for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
		{
			ret = (ret << 1) | ((n >> i) & 1);
		}

		return ret;
	}

	/* count_ones
	 * count number of set bits in 'n'
	 * return set bit count
	 */
	template<typename T = uint64_t, int BYTESIZE = 8>
	constexpr uint32_t count_ones(T n)
	{
		uint32_t cnt = 0;
		for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
		{
			if(n & (1 << i)) cnt++;
		}
		 
		return cnt;
	}

	 
	/* count_zeroes
	 * count number of not set bits in 'n'
	 * return not set bit count
	 */
	template<typename T = uint64_t, int BYTESIZE = 8>
	constexpr uint32_t count_zeroes(T n)
	{
		uint32_t cnt = 0;
		for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
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
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr T check_bit(T n, int targ)
	{
	  if (targ < 1 || targ > sizeof(n) * BYTESIZE)
		return n;

	  return (n >> (targ - 1)) & 1;
	}

	/* set_bit
	 * sets bit targ in n
	 * returns new number
	 */
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr T set_bit(T n, int targ)
	{
	  if (targ < 1 || targ > sizeof(n) * BYTESIZE)
		return n;

	   return n | (1 << (targ - 1));
	}

	/* toggle_bit
	 * toggles bit on and off using xor (^)
	 * returns toggled number
	 */
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr T toggle_bit(T n, int targ)
	{

	 if (targ < 1 || targ > sizeof(n) * BYTESIZE)
		return n;

	  return n ^ (1 << (targ - 1));
	}

	/* clear_bit
	 * clears a bit targ in n
	 * returns new number
	 */
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr T clear_bit(T n, int targ)
	{
	  if (targ < 1 || targ > sizeof(n) * BYTESIZE)
		return n;

	   return n & (~(1 << (targ - 1)));
	}
	
	/* Only use the STL functions if its defined */
	#ifdef STL
	
		template <typename T = uint64_t, int BYTESIZE = 8>
		constexpr std::vector<int> as_vect(T n)
		{
			std::vector<int> v(sizeof(T) * BYTESIZE, 0);
			for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
				v[i] = (n >> i) & 1;
			
			return v;
		}
		
		
		template <typename T = uint64_t, int BYTESIZE = 8>
		constexpr std::vector<bool> as_bvect(T n)
		{
			std::vector<bool> v(sizeof(T) * BYTESIZE, 0);
			for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
				v[i] = ((n >> i) & 1) ? true : false;
			
			return v;
		}
		
	#endif
		
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr std::array<int, sizeof(T) * BYTESIZE> as_farray(T n)
	{
		std::array<int, sizeof(T) * BYTESIZE> arr;
		for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
			arr[i] = (n >> i) & 1;
		
		return arr;
	}
		
	
	
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr int hamming_distance(const T& x, const T& y)
	{
		int diff = 0;
		for(int i = 0; i < sizeof(T) * BYTESIZE; ++i)
		{
			if ((x & (1 << i)) != (y & (1 << i))) diff++;
		}
		
		return diff;
	}
	

	template <typename T = uint64_t, int BYTESIZE = 8>
	class Bittle;
	
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr std::ostream& operator<<(std::ostream& left, Bittle<T, BYTESIZE>& right);
	
	template <typename T = uint64_t, int BYTESIZE = 8>
	constexpr std::istream& operator>>(std::istream&, Bittle<T, BYTESIZE>& right);

	
	
	/* Friend operators Defined above */
	
	template <typename T, int BYTESIZE>
	class Bittle
	{
		using value_type = T;
		using ref_type = T&;
		
		/* Implement stuff to be an iterable class */
		public:
			constexpr Bittle(value_type num) noexcept : number(num) {} 
			
			template <typename G = uint64_t, int BZ = 8>
			constexpr Bittle(const Bittle<G, BZ>& right) noexcept 
			{
			    this->number = static_cast<value_type>(right.value());
			}
			
			template <typename G = uint64_t, int BZ = 8>
			constexpr Bittle(Bittle<G, BZ>&& right) noexcept 
			{
			    this->number = static_cast<value_type>(right.value());
			}
			
			template <typename G = uint64_t, int BZ = 8>
			constexpr Bittle& operator=(const Bittle<G, BZ>& right) noexcept 
			{
			    if(this == &right)
			        return *this;
			       
			    this->number = static_cast<value_type>(right.value());
			    return *this;
			}
			
			template <typename G = uint64_t, int BZ = 8>
			constexpr Bittle& operator=(Bittle<G, BZ>&& right) noexcept 
			{
			     if(this == &right)
			        return *this;
			       
			    this->number = static_cast<value_type>(right.value());
			    return *this;
			}
			
			~Bittle() = default;
			
			/* Member Methods */
			
			constexpr Bittle& reverseBits()
			{
				this->number = bitty::reverse_bits<value_type, BYTESIZE>(this->number);
				return *this;
			}
			
			constexpr Bittle& reverseBytes()
			{
				this->number = bitty::reverse_bytes<value_type>(this->number);
				return *this;
			}
			
			constexpr uint32_t ones() const
			{
				return bitty::count_ones<value_type>(this->number);
			}
			
			constexpr uint32_t zeroes() const
			{
				return bitty::count_zeroes<value_type>(this->number);
			}
			
			constexpr Bittle& toggleBit(int targ)
			{
				this->number = bitty::toggle_bit<value_type, BYTESIZE>(this->number, targ);
				return *this;
			}
			
			constexpr Bittle& setBit(int targ)
			{
				this->number = bitty::set_bit<value_type, BYTESIZE>(this->number, targ);
				return *this;
			}
			
			constexpr Bittle& clearBit(int targ)
			{
				this->number = bitty::clear_bit<value_type, BYTESIZE>(this->number, targ);
				return *this;
			}
			
			constexpr bool checkBit(int targ) const
			{
				return bitty::check_bit<value_type, BYTESIZE>(this->number, targ) != 0 ? true : false;
			}
			
			/* Only use the STL functions if its defined */
			#ifdef STL 
				constexpr std::vector<int> asVector() const
				{
					return bitty::as_vect<value_type, BYTESIZE>(this->number);
				}
				
				constexpr std::vector<bool> asBoolVector() const
				{
					return bitty::as_bvect<value_type, BYTESIZE>(this->number);
				}
				
			#endif
			
			constexpr std::array<int, sizeof(value_type) * BYTESIZE> asFixedArray() const
			{
				return bitty::as_farray<value_type, BYTESIZE>(this->number);
			}
		
			constexpr Bittle& negate()
			{
				this->number *= -1;
				return *this;
			}
			
			constexpr Bittle& add(const ref_type num)
			{
				this->number += num;
				return *this;
			}
			
			constexpr Bittle& subtract(const ref_type num)
			{
				this->number -= num;
				return *this;
			}
			
			constexpr Bittle& multiply(const ref_type num)
			{
				this->number *= num;
				return *this;
			}
			
			constexpr Bittle& divide(const ref_type num)
			{
				this->number /= num;
				return *this;
			}
			
			constexpr Bittle switchByteOrder() const
			{
				Bittle temp(this->number);
				temp.reverseBytes();
				return temp;
			}
			
			constexpr int hammingDistance(const Bittle& right)
			{
				
				return bitty::hamming_distance<value_type, BYTESIZE>(this->number, right.number);
			}
			
			constexpr value_type value() const
			{
				return this->number;
			}
			
			constexpr std::string toString() const
			{
				return std::to_string(this->number);
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
			
			friend std::ostream& operator<< <T, BYTESIZE> (std::ostream& left, Bittle<T, BYTESIZE>& right);
			friend std::istream& operator>> <T, BYTESIZE> (std::istream&, Bittle<T, BYTESIZE>& right);
			
			template <typename G, typename F, typename C, int BZ>
			constexpr friend Bittle<C, BZ> operator+ (Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, typename C, int BZ>
			constexpr friend Bittle<C, BZ> operator- (Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, typename C, int BZ>
			constexpr friend Bittle<C, BZ> operator* (Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, typename C, int BZ>
			constexpr friend Bittle<C, BZ> operator/ (Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, typename C, int BZ>
			constexpr friend Bittle<C, BZ> operator% (Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			
			
			/* Relational Operators */
			template <typename G, typename F, int BZ>
			constexpr friend bool operator==(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			constexpr friend bool operator!=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			constexpr friend bool operator<(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			constexpr friend bool operator>(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			constexpr friend bool operator>=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			constexpr friend bool operator<=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			/* Logical Operators */
			template <typename G, typename F, int BZ>
			friend bool operator&&(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
			template <typename G, typename F, int BZ>
			friend bool operator||(Bittle<G, BZ>& left, const Bittle<F, BZ>& right);
			
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
			
			Bittle& operator/=(const Bittle& rhs)
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
			
			/* Access the underlying number by byte */
			/* Change it as well */
			int8_t& operator[](std::size_t idx)       
			{ 
				if (idx >= 0 && idx < sizeof(value_type))
					return *(reinterpret_cast<int8_t*>(&(this->number)) + idx);
				else
					return *reinterpret_cast<int8_t*>(&(this->number));
			}
			
			
			/* Bitwise operators */
			
			
			
			/* Static Member Methods */
			static constexpr std::string systemByteOrder()
			{
				uint16_t i = 1;
				if(*reinterpret_cast<char*>(&i))
					return std::string("Little");
				else
					return std::string("Big");
			}
			
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
			char
			const int size = BYTESIZE * sizeof(T);
		
		
	};

	template <typename T, int BYTESIZE>
	constexpr std::ostream& operator<<(std::ostream& left, Bittle<T, BYTESIZE>& right)
	{
		left << right.number << '\n';
		return left;
	}
	
    template <typename T, int BYTESIZE>
	constexpr std::istream& operator>>(std::istream& left, Bittle<T, BYTESIZE>& right)
	{
		left >> right.number;
		return left;
	}
		
    template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t, int BZ = 8>
	constexpr Bittle<C, BZ> operator+(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		if (left.size > right.size)
		    return Bittle<C, BZ>(static_cast<G>(left.number + right.number));
		else
		    return Bittle<C, BZ>(static_cast<F>(left.number + right.number));
	}
	
	template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t, int BZ = 8>
	constexpr Bittle<C, BZ> operator-(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		if (left.size > right.size)
		    return Bittle<C, BZ>(static_cast<G>(left.number - right.number));
		else
		    return Bittle<C, BZ>(static_cast<F>(left.number - right.number));
	}
	
    template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t, int BZ = 8>
	constexpr Bittle<C, BZ> operator*(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    if (left.size > right.size)
		    return Bittle<C, BZ>(static_cast<G>(left.number * right.number));
		else
		    return Bittle<C, BZ>(static_cast<F>(left.number * right.number));
	}
	
	template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t, int BZ = 8>
	constexpr Bittle<C, BZ> operator/ (Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		 if (left.size > right.size)
		    return Bittle<C, BZ>(static_cast<G>(left.number / right.number));
		else
		    return Bittle<C, BZ>(static_cast<F>(left.number / right.number));
	}
	
	template <typename G = uint64_t, typename F = uint64_t, typename C = uint64_t, int BZ = 8>
	constexpr Bittle<C, BZ> operator% (Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		 if (left.size > right.size)
		    return Bittle<C, BZ>(static_cast<G>(left.number % right.number));
		else
		    return Bittle<C, BZ>(static_cast<F>(left.number % right.number));
	}
	
	template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator==(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number == right.number;
	}
			
    template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator!=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number != right.number;
	}
			
	template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator<(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number < right.number;
	}
			
	template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator>(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number > right.number;
	}
			
	template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator>=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number >= right.number;
	}
			
    template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	constexpr bool operator<=(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
	    return left.number <= right.number;
	}
	
	 template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	friend bool operator&&(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		 return bool(left) && bool(right)
	}
			
	 template <typename G = uint64_t, typename F = uint64_t, int BZ = 8>
	friend bool operator||(Bittle<G, BZ>& left, const Bittle<F, BZ>& right)
	{
		 return bool(left) || bool(right)
	}
	
	/* Declarations for ease of use */
	
	/* Unsigned */
	using Bittle64U = Bittle<uint64_t, 8>;
    using Bittle32U = Bittle<uint32_t, 8>;
    using Bittle16U = Bittle<uint16_t, 8>;
    using Bittle8U = Bittle<uint8_t, 8>;
    
    /* Signed */
    using Bittle64 = Bittle<int64_t, 8>;
    using Bittle32 = Bittle<int32_t, 8>;
    using Bittle16 = Bittle<int16_t, 8>;
    using Bittle8 = Bittle<int8_t, 8>;
    
    /* Other integral types */
    using BittleInt = Bittle<int, 8>;
    using BittleShort = Bittle<short, 8>;
    using BittleLong = Bittle<long, 8>;
    using BittleChar = Bittle<char, 8>;
	
}


 
 #endif
 