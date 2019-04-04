
#include <iostream>
#include <type_traits>

//template<typename Ty>
//int32_t toStringSigned(char* _dst, int32_t _max, Ty _value, uint32_t _base, char _separator)
//{
//	if (_base == 10
//		&& _value < 0)
//	{
//		if (_max < 1)
//		{
//			return 0;
//		}
//
//		_max = toString(_dst + 1
//			, _max - 1
//			, typename std::make_unsigned<Ty>::type(-_value)
//			, _base
//			, _separator
//		);
//		if (_max == 0)
//		{
//			return 0;
//		}
//
//		*_dst = '-';
//		return int32_t(_max + 1);
//	}
//
//	return toString(_dst
//		, _max
//		, typename std::make_unsigned<Ty>::type(_value)
//		, _base
//		, _separator
//	);
//}
//
//int32_t toString(char* _dst, int32_t _max, int32_t _value, uint32_t _base, char _separator)
//{
//	return toStringSigned(_dst, _max, _value, _base, _separator);
//}
//
//int32_t toString(char* _dst, int32_t _max, int64_t _value, uint32_t _base, char _separator)
//{
//	return toStringSigned(_dst, _max, _value, _base, _separator);
//}


int main(int argc, char *argv[])
 {
	std::cout << "Hello World" << std::endl;
	return 0;
 }