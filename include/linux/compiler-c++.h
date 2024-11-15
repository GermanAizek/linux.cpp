/* SPDX-License-Identifier: GPL-2.0 -*- c++ -*- */
/*
 * C++ type traits.  See http://en.cppreference.com/w/cpp/types
 */
#ifndef _LINUX_TYPE_TRAITS_H
#define _LINUX_TYPE_TRAITS_H

template<typename T, T v>
struct integral_constant {
	static constexpr T value = v;
	typedef T value_type;
	typedef integral_constant type; // using injected-typename-name
	constexpr operator value_type() const noexcept { return value; }
	constexpr value_type operator()() const noexcept { return value; } //since c++14
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

/*
 *  Determine if two types are the same.
 */
template<typename T, typename U>	struct is_same : false_type {};
template<typename T>			struct is_same<T, T> : true_type {};

/*
 * Strip const and volatile from type.
 */
template<typename T> struct remove_const		{ typedef T type; };
template<typename T> struct remove_const<const T>	{ typedef T type; };
template<typename T> struct remove_volatile		{ typedef T type; };
template<typename T> struct remove_volatile<volatile T>	{ typedef T type; };
template<typename T> struct remove_cv {
	typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

template<typename T> using remove_cv_t       = typename remove_cv<T>::type;
template<typename T> using remove_const_t    = typename remove_const<T>::type;
template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;

/*
 * Determine if a type is the NULL pointer type.
 */
template<typename T> struct is_null_pointer : is_same<nullptr_t, remove_cv_t<T>> {};

/*
 * Determine if a type is an array type.
 */
template<typename T>		struct is_array : false_type {};
template<typename T>		struct is_array<T[]> : true_type {};
template<typename T, size_t N>	struct is_array<T[N]> : true_type {};
#define __is_array(T) is_array<typeof(T)>::value

#endif /* _LINUX_TYPE_TRAITS_H */
