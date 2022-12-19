/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:50:33 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/26 11:01:08 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "../iterators/iterator_traits.hpp"

namespace ft {

template <class _InputIter>
	typename iterator_traits<_InputIter>::difference_type
		_distance(_InputIter first, _InputIter last, input_iterator_tag)
	{
		typename iterator_traits<_InputIter>::difference_type r(0);
		for (; first != last; ++first)
			++r;
		return r;
	}

template <class _RandIter>
	typename iterator_traits<_RandIter>::difference_type
		_distance(_RandIter first, _RandIter last, random_access_iterator_tag)
	{
		return last - first;
	}

template<typename iterator>
	typename iterator_traits<iterator>::difference_type distance(iterator first, iterator last) {
		typename ft::iterator_traits<iterator>::difference_type	count = 0;
		for (; first != last;) {
			++count;
			++first;
		}
		return (count);
	}

template<typename iterator, typename InputIterator>
	iterator	copy(InputIterator first, InputIterator last, iterator position) {
		while (first != last)
		{
			*position = *first;
			++first;
			++position;
		}
		return(position);
	}

template<typename iterator, typename InputIterator>
	iterator	copy_backward(InputIterator first, InputIterator last, iterator position) {
		--first;
		--last;
		size_t	n = ft::distance<InputIterator>(first, last);
		position = position + n - 1;
		while (last != first) {
			*position = *last;
			last--;
			position--;
		}
		return (position + n);
	}

template<typename iterator, typename InputIterator>
	iterator	uninitialized_copy(InputIterator first, InputIterator last, iterator result) {
		for (; first != last; ++result, ++first) {
			new (static_cast<void *>(&*result))
				typename ft::iterator_traits<iterator>::value_type(*first);
		}
		return result;
	}

template<typename iterator, typename T>
	void fill(iterator first, iterator last, const T& val) {
		while (first != last) {
			*first = val;
			++first;
		}
	}

template<typename iterator, typename Size, typename T>
	void	uninitialized_fill_n(iterator first, Size n, const T& x) {
		for (; n--; ++first) {
			new (static_cast<void *>(&*first))
				typename iterator_traits<iterator>::value_type(x);
		}
	}

template<typename T>
	void	swap(T &first, T &second) {
		T	tmp = first;
		first = second;
		second = tmp;
	}

} // namespace ft

#endif