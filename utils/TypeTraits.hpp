/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTraits.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:02:18 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/26 11:07:50 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPETRAITS_HPP
# define TYPETRAITS_HPP

namespace ft {

template<bool Cond, class T = void>
	struct enable_if {};

template<class T>
	struct enable_if<true, T> {
		typedef T	type;
	};

template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
	};

typedef struct integral_constant<bool, true>	true_type;
typedef struct integral_constant<bool, false>	false_type;

template <class T>
	struct is_integral: public false_type {};

template <>
		struct is_integral<bool>: public true_type { };
template <>
	struct is_integral<char>: public true_type { };
template <>
	struct is_integral<wchar_t>: public true_type { };
template <>
	struct is_integral<signed char>: public true_type { };
template <>
	struct is_integral<short int>: public true_type { };
template <>
	struct is_integral<int>: public true_type { };
template <>
	struct is_integral<long int>: public true_type { };
template <>
	struct is_integral<long long int>: public true_type { };
template <>
	struct is_integral<unsigned char>: public true_type { };
template <>
	struct is_integral<unsigned short int>: public true_type { };
template <>
	struct is_integral<unsigned int>: public true_type { };
template <>
	struct is_integral<unsigned long int>: public true_type { };
template <>
	struct is_integral<unsigned long long int>: public true_type { };

} // ft
#endif // TYPETRAITS_HPP