/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:25:11 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/26 11:08:26 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <stdexcept>
# include <algorithm>
# include <iostream>
# include "utils/Pair.hpp"
# include "utils/TypeTraits.hpp"
# include "utils/Algorithm.hpp"
# include "utils/Utils.hpp"
# include "iterators/random_access_iterator.hpp"
# include "iterators/reverse_iterator.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			typedef T																value_type;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename ft::random_access_iterator<value_type, vector>			iterator;
			typedef typename ft::random_access_iterator<const value_type, vector>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type			difference_type;
			typedef typename allocator_type::size_type								size_type;

		private:

			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			size_type		_cap;

			size_type	_recommend_size(size_type new_size) {
				size_type	_max = max_size();
				if (new_size > _max)
					throw std::length_error("vector");
				if (_cap >= _max / 2)
					return (_max);
				return (std::max<size_type>(2 * _cap, new_size));
			}

			void	_delete(size_type cap) {
				for (size_type i = 0; i < size(); ++i)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, cap);
			}

			void	_destroy(allocator_type	&alloc, pointer p) {
				alloc.destroy(p);
			}

			void	_destruct_at_end(pointer _new_last) {
				pointer	end_cpy = _end;
				while (_new_last != end_cpy)
					_destroy(_alloc, --end_cpy);
				_end = _new_last;
			}

			void	_construct_at_end(size_type n, value_type val) {
				for (size_type i = 0; i != n; ++i) {
					_alloc.construct(_end + i, val);
				}
			}

			void	_append(size_type n, value_type val) {
				if (((_begin + _cap) - _end) >= static_cast<long>(n)) {
					_construct_at_end(n, val);
					_end = _end + n;
				}
				else {
					size_type	old_size = size();
					size_type	old_cap = _cap;
					size_type	new_size = _recommend_size(old_size + n);
					pointer		tmp = _alloc.allocate(new_size);
					for (size_type i = 0; i < old_size; ++i) {
						_alloc.construct(tmp + i, *(_begin + i));
					}
					for (size_type i = old_size; i < old_size + n; ++i) {
						_alloc.construct(tmp + i, val);
					}
					_delete(old_cap);
					_begin = tmp;
					_end = _begin + (old_size + n);
					_cap = new_size;
				}
			}

			void	_insert_helper(iterator position, const T &val) {
				if (_end != _begin + _cap) {
					_alloc.construct(_end, *(_end - 1));
					ft::copy_backward(position, end() - 1, position + 1);
					*position = val;
					++_end;
				}
				else {
					size_type	n;
					if (size())
						n = _recommend_size(size() + 1);
					else
						n = 10;
					pointer	tmp = _alloc.allocate(n);
					iterator	it(tmp);
					ft::copy(begin(), position, it);
					_alloc.construct(tmp + (position - begin()), val);
					ft::uninitialized_copy(position, end(), tmp + (position - begin()) + 1);
					for (pointer tmp = _begin; tmp != _end; ++tmp)
						_destroy(_alloc, tmp);
					_alloc.deallocate(_begin, _cap);
					_cap = n;
					_end = tmp + size() + 1;
					_begin = tmp;
				}
			}

		public:

		/* ----------- Constructors, Destructor, Assignment Operator Overload ----------- */
		explicit vector(const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _begin(NULL), _end(NULL), _cap(0) {}

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _begin(NULL), _end(NULL), _cap(n) {
				_begin = _alloc.allocate(n);
				_end = _begin;
				for (size_t i = 0; i < n; ++i) {
					_alloc.construct(_end, val);
					_end++;
				}
			}

		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) :
				_alloc(alloc), _begin(NULL), _end(NULL), _cap(0) {
					difference_type n = ft::distance(first, last);
					reserve(n);
					_end = _begin + n;
					ft::copy(first, last, iterator(_begin));
			}

		vector(const vector& x) : _alloc(x._alloc), _begin(NULL), _end(NULL), _cap(x._cap) {
			_begin = _alloc.allocate(_cap);
			_end = _begin;
			for (size_t i = 0; i < x.size(); ++i) {
				_alloc.construct(_end, x[i]);
				_end++;
			}
		}

		~vector(void) {
			clear();
			_alloc.deallocate(_begin, _cap);
		}

		vector	&operator=(const vector &x) {
			if (&x == this)
				return (*this);
			if (x.size() > _cap) {
				clear();
				_alloc.deallocate(_begin, _cap);
				_cap = x.end() - x.begin();
				_begin = _alloc.allocate(_cap);
				ft::copy(x.begin(), x.end(), begin());
				_end = _begin + x.size();
			}
			else if (size() >= x.size()) {
				size_type x_n = x.size();
				iterator i = ft::copy(x.begin(), x.end(), begin());
				for (; i != end(); ++i, ++x_n) {
					_alloc.destroy(_begin + x_n);
				}
			}
			else {
				ft::copy(x.begin(), x.end(), begin());
			}
			_end = _begin + x.size();
			return (*this);
		}

		/* ----------- Iterators ----------- */
		iterator				begin(void) {
			return (iterator(_begin));
		}

		const_iterator			begin() const {
			return (const_iterator(_begin));
		}

		iterator				end() {
			return (iterator(_end));
		}

		const_iterator			end() const {
			return (const_iterator(_end));
		}

		reverse_iterator		rbegin() {
			return (reverse_iterator(end()));
		}

		const_reverse_iterator	rbegin() const {
			return (const_reverse_iterator(end()));
		}

		reverse_iterator		rend() {
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator	rend() const {
			return (const_reverse_iterator(begin()));
		}

		/* ----------- Capacity ----------- */
		size_type	size() const {
			return (_end - _begin);
		}

		size_type	max_size() const {
			return (_alloc.max_size());
		}

		void		resize(size_type n, value_type val = value_type()) {
			if (n < size()) {
				_destruct_at_end(_begin + n);
			}
			else if (size() < n) {
				_append(n - size(), val);
			}
		}

		size_type	capacity() const {
			return (_cap);
		}

		bool		empty() const {
			return (!size());
		}

		void		reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("vector");
			else if (n > _cap) {
				size_type	new_size = n;
				pointer	tmp = _alloc.allocate(new_size);
				ft::copy(begin(), end(), tmp);
				for (pointer p = _begin; p != _end; ++p) {
					_destroy(_alloc, p);
				}
				_alloc.deallocate(_begin, _cap);
				_end = tmp + size();
				_begin = tmp;
				_cap = new_size;
			}
		}

		/* ----------- Element access ----------- */
		reference		operator[] (size_type n) {
			return *(begin() + n);
		}

		const_reference operator[] (size_type n) const {
			return *(begin() + n);
		}

		reference		at(size_type n) {
			if (n >= size() || n < 0)
				throw std::out_of_range("vector");
			return *(begin() + n);
		}

		const_reference	at(size_type n) const {
			if (n >= size() || n < 0)
				throw std::out_of_range("vector");
			return *(begin() + n);
		}

		reference		front() {
			return *begin();
		}

		const_reference	front() const {
			return *begin();
		}

		reference		back() {
			return *(end() - 1);
		}

		const_reference	back() const {
			return *(end() - 1);
		}

		/* ----------- Modifiers ----------- */
		template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
				if (static_cast<size_type>(ft::distance(first, last)) > max_size())
					throw std::length_error("vector");
				clear();
				for (; first != last; ++first) {
					push_back(*first);
				}
			}

		void	assign(size_type n, const value_type& val) {
			if (n <= _cap) {
				size_type	s = size();
				std::fill_n(_begin, std::min(n, s), val);
				if (n > s) {
					_construct_at_end(n - s, val);
				}
				else
					_destruct_at_end(_begin + n);
			}
			else {
				_delete(_cap);
				size_type new_cap = _recommend_size(n);
 				_begin = _alloc.allocate(new_cap);
				_end = _begin;
				_construct_at_end(n, val);
				_cap = new_cap;
			}
			_end = _begin + n;
		}

		void	push_back(const value_type& val) {
			_append(1, val);
		}

		void	pop_back() {
			if (empty())
				return ;
			else
				_destruct_at_end(_end - 1);
		}

		iterator	insert(iterator position, const value_type& val) {
			size_type	n = position - begin();
			if (_end != _begin + _cap && position == end()) {
				_alloc.construct(_end, val);
				_end++;
			}
			else
				_insert_helper(position, val);
			return (begin() + n);
		}

		void		insert(iterator position, size_type n, const value_type& val) {
			if (n == 0)
				return ;
			if ((_begin + _cap) - _end >= static_cast<long>(n)) {
				if (end() - position > static_cast<long>(n)) {
					ft::uninitialized_copy(end() - n, end(), end());
					ft::copy_backward(position, end() - n, end());
					ft::fill(position, position + n, val);
				}
				else {
					ft::uninitialized_copy(position, end(), position + n);
					ft::fill(position, end(), val);
					ft::uninitialized_fill_n(end(), n - (end() - position), val);
				}
				_end += n;
			}
			else {
				size_type	len = size() + std::max(size(), n);
				pointer	tmp = _alloc.allocate(len);
				ft::uninitialized_copy(begin(), position, tmp);
				ft::uninitialized_fill_n(tmp + (position - begin()), n, val);
				ft::uninitialized_copy(position, end(), tmp + (position - begin() + n));
				for (pointer start = _begin; start != _end; ++start)
					_destroy(_alloc, start);
				_alloc.deallocate(_begin, _cap);
				_cap = len;
				_end = tmp + size() + n;
				_begin = tmp;
			}
		}
		template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
				if (first == last)
					return;
				size_type n = 0;
				n = ft::distance(first, last);
				if (n > max_size() || size() + n > max_size())
					throw std::length_error("vector");
				if ((_begin + _cap) - _end >= static_cast<long>(n)) {
					ft::copy_backward(position, end(), position + n);
					ft::copy(first, last, position);
					_end += n;
				}
				else {
					size_type len = size() + std::max(size(), n);
					pointer	tmp = _alloc.allocate(len);
					ft::uninitialized_copy(begin(), position, tmp);
					ft::uninitialized_copy(first, last, tmp + (position - begin()));
					ft::uninitialized_copy(position, end(), tmp + (position - begin() + n));
					for (pointer tmp2 = _begin; tmp2 != _end; ++tmp2)
						_destroy(_alloc, tmp2);
					_alloc.deallocate(_begin, _cap);
					_cap = len;
					_end = tmp + size() + n;
					_begin = tmp;
				}
			}
		iterator	erase(iterator position) {
			erase(position, position + 1);
			return (position);
		}
		iterator	erase(iterator first, iterator last) {
			size_type	first_dst = ft::distance(begin(), first);
			size_type	last_dst = ft::distance(begin(), last);
			pointer		first_end = _begin + first_dst;

			for (iterator it = begin() + last_dst; it != end(); ++it) {
				*first_end = *it;
				++first_end;
			}
			while (last_dst != size()) {
				_alloc.destroy(_begin + last_dst);
				last_dst++;
			}
			_end = first_end;
			return (_begin + first_dst);
		}

		void		swap(vector& x) {
			pointer			tmp_begin = _begin;
			pointer			tmp_end	= _end;
			size_type		tmp_cap = _cap;
			allocator_type	tmp_alloc = _alloc;

			_begin = x._begin;
			_end = x._end;
			_cap = x._cap;
			_alloc = x._alloc;
			x._begin = tmp_begin;
			x._end = tmp_end;
			x._cap = tmp_cap;
			x._alloc = tmp_alloc;
		}

		void		clear() {
			_destruct_at_end(_begin);
		}

		/* ----------- Allocator ----------- */
		allocator_type	get_allocator() const {
			return (_alloc);
		}
	};

	/* ----------- Non-member function overloads ----------- */
	template <class T, class Alloc>
		bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			return (!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
			return (!(rhs > lhs));
		}

	template <class T, class Alloc>
		void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
			x.swap(y);
		}

	template <class T, class Alloc>
	std::ostream	&operator<<(std::ostream &o, const vector<T, Alloc> &v) {
		for (typename vector<T, Alloc>::const_iterator it = v.begin(); it != v.end(); ++it) {
			if (it == v.begin())
				o << *it;
			else
				o << " " << *it;
		}
		o << std::endl;
		return (o);
	}

} // namespace ft

#endif
