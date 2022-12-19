/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:31:09 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/26 10:42:11 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "utils/Pair.hpp"
# include "utils/Algorithm.hpp"
# include "iterators/bst_bidirectional_iterator.hpp"
# include "utils/RedBlackTree.hpp"

namespace ft {

template<class Key,
         class T,
         class Compare = std::less<const Key>,
         class Alloc = std::allocator<ft::pair<const Key, T> >
        >
        class map {

            public:
                typedef Key                                                         key_type;
                typedef T                                                           mapped_type;
                typedef ft::pair<const key_type, mapped_type>                       value_type;
                typedef Compare                                                     key_compare;
                typedef Alloc                                                       allocator_type;
                typedef typename allocator_type::reference                          reference;
                typedef typename allocator_type::const_reference                    const_reference;
                typedef typename allocator_type::pointer                            pointer;
                typedef typename allocator_type::const_pointer                      const_pointer;
                typedef typename allocator_type::size_type                          size_type;

                class value_compare {
                    friend class map;

                    protected:
                        key_compare _comp;
                        value_compare(Compare c) : _comp(c) { }
                    
                    public:
                        typedef bool        result_type;
                        typedef value_type  first_argument_type;
                        typedef value_type  second_argument_type;
                        bool    operator() (value_type const &x, value_type const &y) const {
                            return _comp(x.first, y.first);
                        }
                };

            private:
                typedef RB_BST<value_type, value_compare, allocator_type> Tree;
            
            public:
                typedef typename Tree::iterator                                 iterator;
                typedef typename Tree::const_iterator                           const_iterator;
                typedef typename Tree::reverse_iterator                         reverse_iterator;
                typedef typename Tree::const_reverse_iterator                   const_reverse_iterator;
                typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

            private:
                Tree    _tree;

            public:
            /* ---------- Constructors ------- */
                explicit map(const key_compare& comp = key_compare(),
                             const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc) { }

                template <class InputIterator>
                    map(InputIterator first, InputIterator last, 
                        const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc) {
                            for(; first != last; ++first) {
                                _tree.insert(*first);
                            }
                        }

                map(const map& x) : _tree(x._tree) { }

            /* ------- Destructor ------- */
                ~map() { }
            
            /* ------- CopyAssignment Operator Overload ------- */
                map &operator=(const map& x) {
                    _tree = x._tree;
                    return (*this);
                }

            /* ------- Iterators ------- */
                iterator    begin() { return _tree.begin(); }
                
                const_iterator  begin() const { return _tree.begin(); }
                
                iterator    end() { return _tree.end(); }

                const_iterator end() const { return _tree.end(); }

                reverse_iterator    rbegin() { return _tree.rbegin(); }
                
                const_reverse_iterator  rbegin() const { return _tree.rbegin(); }

                reverse_iterator    rend() { return _tree.rend(); }

                const_reverse_iterator  rend() const { return _tree.rend(); }

            /* ------- Capacity ------- */
                bool    empty() const { return _tree.empty(); }

                size_type   size() const { return _tree.size(); }

                size_type   max_size() const { return _tree.max_size(); }

            /* ------- Element Access ------- */
                mapped_type& operator[](const key_type& k) {
                    iterator    ret = insert(ft::make_pair(k, mapped_type())).first;
                    return ret->second;
                }

            /* ------- Modifiers ------- */
                pair<iterator, bool> insert(const value_type& val) {
                    return _tree.insert(val);
                }

                iterator    insert(iterator position, const value_type& val) {
                    return _tree.insert(position, val);
                }

                template <class InputIterator>
                    void    insert(InputIterator first, InputIterator last) {
                        _tree.insert(first, last);
                    }
            
                void    erase(iterator position) {
                    _tree.deleteNode(position.base()->data);
                }

                size_type   erase(const key_type& k) {
                    return _tree.deleteNode(ft::make_pair(k, mapped_type()));
                }

                void    erase(iterator first, iterator last) {
                    _tree.deleteNode(first, last);
                }

                void    swap(map& x) { _tree.swap(x._tree); }

                void    clear() { _tree.clear(); }

            /* ------- Observers ------- */
                key_compare key_comp() const {
                    return _tree.value_comp()._comp;
                }

                value_compare   value_comp() const {
                    return _tree.value_comp();
                }

            /* ------- Operations ------- */
                iterator   find(const key_type& k) {
                    return _tree.find(ft::make_pair(k, mapped_type()));
                }

                const_iterator find(const key_type& k) const {
                    return _tree.find(ft::make_pair(k, mapped_type()));
                }

                size_type   count(const key_type& k) const {
                    return _tree.count(ft::make_pair(k, mapped_type()));
                }
                
                iterator    lower_bound(const key_type& k) {
                    return _tree.lower_bound(ft::make_pair(k, mapped_type()));
                }

                const_iterator lower_bound(const key_type& k) const {
                    return _tree.lower_bound(ft::make_pair(k, mapped_type()));
                }

                iterator    upper_bound(const key_type& k) {
                    return _tree.upper_bound(ft::make_pair(k, mapped_type()));
                }

                const_iterator  upper_bound(const key_type& k) const {
                    return _tree.upper_bound(ft::make_pair(k, mapped_type()));
                }

                pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
                    return _tree.equal_range(ft::make_pair(k, mapped_type()));
                }
                
                pair<iterator, iterator>    equal_range(const key_type& k) {
                    return _tree.equal_range(ft::make_pair(k, mapped_type()));
                }
            
            /* ------- Allocator ------- */
                allocator_type  get_allocator() const {
                    return _tree.get_allocator() ;
                }
        };

    template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
			x.swap(y);
		}
	
	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return !(lhs == rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return !(rhs < lhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return rhs < lhs;
		}

	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
			return !(rhs > lhs);
		}

} // namespace ft

#endif // MAP_HPP