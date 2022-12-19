/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:56:38 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/23 09:26:48 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

namespace ft {

template <typename _value, typename vector>
	class random_access_iterator {

		public:
			typedef ptrdiff_t						difference_type;
			typedef _value							value_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef ft::random_access_iterator_tag	iterator_category;

			random_access_iterator() : _ptr() {};
			random_access_iterator(pointer ptr) : _ptr(ptr) {};
			random_access_iterator(const random_access_iterator<typename vector::value_type, vector> &src) : _ptr(src.base()) {};

			random_access_iterator	&operator=(random_access_iterator const &rhs) {
				_ptr = rhs.base();
				return (*this);
			}

			pointer	base() const { return _ptr; };

			random_access_iterator	&operator++() {
				++_ptr;
				return (*this);
			}
			random_access_iterator	operator++(int) {
				random_access_iterator	it = *this;
				++(*this);
				return (it);
			}
			random_access_iterator	&operator--() {
				--_ptr;
				return (*this);
			}
			random_access_iterator	operator--(int) {
				random_access_iterator	it = *this;
				--(*this);
				return (it);
			}
			reference	operator[] (size_t idx) {
				return *(_ptr + idx);
			}
			pointer	operator->() {
				return &(this->operator*());
			}
			reference	operator*() {
				return (*_ptr);
			}
			reference	operator*() const {
				return (*_ptr);
			}
			int	operator-(random_access_iterator const &rhs) const {
				return (base() - rhs.base());
			}
			random_access_iterator	operator+(int const &value) const {
				return (base() + value);
			}
			random_access_iterator	operator-(int const &value) const {
				return (base() - value);
			}
			random_access_iterator	operator+=(int const &value) {
				_ptr += value;
				return *this;
			}
			random_access_iterator	operator-=(int const &value) {
				_ptr -= value;
				return *this;
			}
		private:
			pointer	_ptr;

	};

	template<typename p, typename vector>
		random_access_iterator<p, vector>	operator-(const int &lhs, random_access_iterator<p,vector> const &rhs) {
			return random_access_iterator<p,vector>(lhs - rhs.base());
		}
	template<typename p, typename vector>
		random_access_iterator<p, vector>	operator+(const int &lhs, random_access_iterator<p,vector> const &rhs) {
			return random_access_iterator<p,vector>(lhs + rhs.base()); }
	template<typename p, typename vector>
		bool	operator!=(random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (rhs.base() != lhs.base());
		}
	template<typename p, typename vector>
		bool	operator!=(random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (rhs.base() != lhs.base());
		}
	template<typename p, typename vector>
		bool	operator!=(random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (rhs.base() != lhs.base());
		}
	template<typename p, typename vector>
		bool	operator==(random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (rhs.base() == lhs.base());
		}
	template<typename p, typename vector>
		bool	operator==(random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (rhs.base() == lhs.base());
		}
	template<typename p, typename vector>
		bool	operator==(random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (rhs.base() == lhs.base());
		}
	template<typename p, typename vector>
		bool	operator< (random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() < rhs.base());
		}
	template<typename p, typename vector>
		bool	operator< (random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() < rhs.base());
		}
	template<typename p, typename vector>
		bool	operator< (random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (lhs.base() < rhs.base());
		}
	template<typename p, typename vector>
		bool	operator> (random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() > rhs.base());
		}
	template<typename p, typename vector>
		bool	operator> (random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() > rhs.base());
		}
	template<typename p, typename vector>
		bool	operator> (random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (lhs.base() > rhs.base());
		}
	template<typename p, typename vector>
		bool	operator>=(random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() >= rhs.base());
		}
	template<typename p, typename vector>
		bool	operator>=(random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() >= rhs.base());
		}
	template<typename p, typename vector>
		bool	operator>=(random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (lhs.base() >= rhs.base());
		}
	template<typename p, typename vector>
		bool	operator<=(random_access_iterator<p, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() <= rhs.base());
		}
	template<typename p, typename vector>
		bool	operator<=(random_access_iterator<const typename vector::value_type, vector> const &lhs, random_access_iterator<p, vector> const &rhs) {
			return (lhs.base() <= rhs.base());
		}
	template<typename p, typename vector>
		bool	operator<=(random_access_iterator<p, vector> const &lhs, random_access_iterator<const typename vector::value_type, vector> const &rhs) {
			return (lhs.base() <= rhs.base());
		}
	template<typename p, typename vector>
		std::ostream	&operator<<(std::ostream &o, const random_access_iterator<p, vector> &it) {
			o << *it.base();
			return (o);
		}

} // namespace ft

#endif
