/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:48:26 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/10 13:59:01 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "random_access_iterator.hpp"

namespace ft {

	template <typename iterator>
		class reverse_iterator {

			public:

				typedef typename	iterator::value_type		value_type;
				typedef typename	iterator::difference_type	difference_type;
				typedef typename	iterator::pointer			pointer;
				typedef typename	iterator::reference			reference;
				typedef typename	iterator::iterator_category	iterator_category;

			private:

				iterator	_it;

			public:

				reverse_iterator(void) : _it() {}
				explicit reverse_iterator(iterator const &src) : _it(src) {}
				template<typename Iter>
					reverse_iterator(reverse_iterator<Iter> const &src) : _it(src.base()) {}
				~reverse_iterator() {}

				iterator	base() const {
					return (_it);
				}
				reverse_iterator	&operator++() {
					--_it;
					return (*this);
				}
				reverse_iterator	operator++(int) {
					reverse_iterator	it = *this;
					++(*this);
					return (it);
				}
				reverse_iterator	operator--() {
					++_it;
					return *this;
				}
				reverse_iterator	operator--(int) {
					reverse_iterator	it = *this;
					--(*this);
					return (it);
				}
				reference	operator[] (size_t idx) {
					return (_it[-idx - 1]);
				}
				pointer	operator->() {
					return (&(this->operator*()));
				}
				pointer	operator->() const {
					return (&(this->operator*()));
				}
				reference	operator*() {
					return *(_it - 1);
				}
				reference	operator*() const {
					return *(_it - 1);
				}
				reverse_iterator	operator=(reverse_iterator const &in)  {
					_it = in.base();
					return *this;
				}
				reverse_iterator	operator+=(int const &value) {
					_it -= value;
					return *this;
				}
				reverse_iterator	operator-=(int const &value) {
					_it += value;
					return *this;
				}
				int	operator-(reverse_iterator const &rhs) const {
					return rhs.base() - _it;
				}
				reverse_iterator	operator+(int const &value)	const {
					return reverse_iterator(_it - (value));
				}
				
				reverse_iterator	operator-(int const &value)	const {
					return reverse_iterator(_it + (value));
				}
		};

		template<typename iterator>
			reverse_iterator<iterator>	operator-(const int &lhs, reverse_iterator<iterator> const &rhs) {
				return rhs - lhs;
			}
		template<typename iterator>
			reverse_iterator<iterator>	operator+(const int &lhs, reverse_iterator<iterator> const &rhs) {
				return rhs + lhs;
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator==(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() == rhs.base());
			}
		template<typename iterator>
			bool	operator==(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() == rhs.base());
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator!=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() != rhs.base());
			}
		template<typename iterator>
			bool	operator!=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() != rhs.base());
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator<(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() > rhs.base());
			}
		template<typename iterator>
			bool	operator<(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() > rhs.base());
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator>(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() < rhs.base());
			}
		template<typename iterator>
			bool	operator>(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() < rhs.base());
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator>=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() <= rhs.base());
			}
		template<typename iterator>
			bool	operator>=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() <= rhs.base());
			}

		template <class Iterator_L, class Iterator_R>
			bool	operator<=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) {
				return (lhs.base() >= rhs.base());
			}
		template<typename iterator>
			bool	operator<=(reverse_iterator<iterator> const &lhs, reverse_iterator<iterator> const &rhs) {
				return (lhs.base() >= rhs.base());
			}

} //namespace ft

#endif
