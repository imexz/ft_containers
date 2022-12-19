/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:18:54 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/23 13:50:08 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <functional>
# include "utils/Pair.hpp"
# include "utils/Algorithm.hpp"
# include "iterators/bst_bidirectional_iterator.hpp"
# include "utils/RedBlackTree.hpp"


namespace ft {

    template < class T,                         //set::key_type/value_type
           class Compare = std::less<T>,        //set::key_compare/value_compare
           class Alloc = std::allocator<T>      //set::allocator_type
           >
        class set {

            public:
                typedef T                                                       key_type;
                typedef T                                                       value_type;
                typedef Compare                                                 key_compare;
                typedef Compare                                                 value_compare;
                typedef Alloc                                                   allocator_type;
                typedef typename allocator_type::reference                      reference;
                typedef typename allocator_type::const_reference                const_reference;
                typedef typename allocator_type::pointer                        pointer;
                typedef typename allocator_type::const_pointer                  const_pointer;
                typedef typename allocator_type::size_type                      size_type;

            private:
                typedef RB_BST<value_type, value_compare, allocator_type> Tree;
            
            public:
                typedef typename Tree::const_iterator                           iterator;
                typedef typename Tree::const_iterator                           const_iterator;
                typedef typename Tree::const_reverse_iterator                   reverse_iterator;
                typedef typename Tree::const_reverse_iterator                   const_reverse_iterator;
                typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

            protected:
                Tree    _tree;
            
            public:
                /* ------ Constructor ------ */
                explicit set (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc) { }
			
				template <class InputIterator>
					set (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc) {
							for(; first  != last; first++) {
								_tree.insert(*first);
							}
					}

				set (const set& x) : _tree(x._tree) { }

				/* ------ Destructor ------ */
				~set() { }

				/* ------ Assignment operator overload ------ */
				set	&operator=(const set &other) {
					_tree = other._tree;
					return *this;
				}

				/* ------ Iterators ------ */
				iterator				begin()				{ return _tree.begin(); }
				const_iterator			begin()		const	{ return _tree.begin(); };
				iterator				end()				{ return _tree.end(); }
				const_iterator			end()		const	{ return _tree.end(); }
				reverse_iterator		rbegin() 			{ return _tree.rbegin(); }
				const_reverse_iterator	rbegin()	const	{ return _tree.rbegin(); }
				reverse_iterator		rend()				{ return _tree.rend(); }
				const_reverse_iterator	rend()		const	{ return _tree.rend(); }

				/* ------ Capacity ------ */
				bool		empty()		const	{ return _tree.empty(); }
				size_type	size()		const	{ return _tree.size(); }
				size_type	max_size()	const	{ return _tree.max_size(); }

				/* ------ Modifiers ------ */
				ft::pair<iterator,bool>	insert (const value_type& val) {
                     return(_tree.insert(val));
                }

				iterator	insert (iterator position, const value_type& val) {
                    (void)position;
                    return _tree.insert(_tree.begin(), val);
                }

				template <class InputIterator>
					void	insert (InputIterator first, InputIterator last) {
                        _tree.insert(first, last);
                    }

				void	erase (iterator position) {
                    _tree.deleteNode(*position);
                }

				size_type	erase (const value_type& val) {
                    return (_tree.deleteNode(val));
                }

				void	erase (iterator first, iterator last) { 
					while (first != last) {
						_tree.deleteNode(*first++);
					}
				}

				void	swap (set& x) { _tree.swap(x._tree); }

				void	clear()	{ _tree.clear(); }

				/* ------ Observers ------ */
				value_compare	value_comp() const	{ return _tree.value_comp(); };
				key_compare		key_comp() const	{ return _tree.value_comp(); };
				/* ------ Operations ------ */
				iterator    find (const value_type& val) const	{
                    return _tree.find(val);
                }

				size_type	count (const value_type& val) const	{
                    return _tree.count(val);
                }

				iterator    lower_bound (const value_type& val)	const {
                    return iterator(_tree.lower_bound(val).base());
                }

				iterator	upper_bound (const value_type& val)	const {
                    return iterator(_tree.upper_bound(val).base());
                }

				ft::pair<iterator,iterator>	equal_range (const value_type& val) const {
                    return _tree.equal_range(val);
                }

				/* ------ Allocator ------ */
				allocator_type get_allocator() const { return _tree.get_allocator(); }


		};

			template<class T, class Compare, class Alloc>
				void swap (set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) {
					x.swap(y);
				}

			template<class T, class Compare, class Alloc >
				bool operator==( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					if (lhs.size() != rhs.size())
						return false;
					return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
				}

			template<class T, class Compare, class Alloc >
				bool operator!=( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					return !(lhs == rhs);
				}
			template<class T, class Compare, class Alloc >
				bool operator<( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				}

			template<class T, class Compare, class Alloc >
				bool operator<=( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					return !(rhs < lhs);
				}

			template<class T, class Compare, class Alloc >
				bool operator>( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					return rhs < lhs;
				}

			template<class T, class Compare, class Alloc >
				bool operator>=( const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs ) {
					return !(rhs > lhs);
				}

} // namespace ft

#endif

