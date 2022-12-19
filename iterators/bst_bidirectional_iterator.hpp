/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_bidirectional_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:43:00 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/23 09:34:19 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_BIDIRECTIONAL_ITERATOR_HPP
# define BST_BIDIRECTIONAL_ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

namespace ft {

template <typename T, typename container, typename value>
class bst_bidirectional_iterator {

    public:
        typedef ptrdiff_t                                   difference_type;
        typedef T                                           Node;
        typedef value                                       value_type;
        typedef value_type*                                 pointer;
        typedef value_type&                                 reference;
        typedef typename ft::bidirectional_iterator_tag     iterator_category;

    private:
        Node    _curr;

    public:

        bst_bidirectional_iterator(void) : _curr() {}
        bst_bidirectional_iterator(Node const &in) : _curr(in) {}
        bst_bidirectional_iterator(const bst_bidirectional_iterator<typename container::Node *, container, typename container::value_type> &rhs)\
            : _curr(rhs.base()) {}
        ~bst_bidirectional_iterator(void) {}
        
        Node    &base() { return _curr; }
        
        const Node  &base() const { return _curr; };

        bst_bidirectional_iterator  &operator=(bst_bidirectional_iterator const &rhs) {
            _curr = rhs._curr;
            return (*this);
        }

        bst_bidirectional_iterator  &operator++() {
            if (_curr == NULL) {
            }
            else if (_curr->right != NULL) {
                _curr = _curr->right;
                while (_curr->left != NULL)
                    _curr = _curr->left;
            }
            else {
                Node    p = _curr->parent;
                while (p != NULL && _curr == p->right) {
                    _curr = p;
                    p = p->parent;
                }
                _curr = p;
            }
            return (*this);
        }
        
        bst_bidirectional_iterator  operator++(int) {
            bst_bidirectional_iterator  cpy(_curr);
            if (_curr == NULL) {
            }
            else if (_curr->right != NULL) {
                _curr = _curr->right;
                while (_curr->left) {
                    _curr = _curr->left;
                }
            }
            else {
                Node    p = _curr->parent;
                while (p != NULL && _curr == p->right) {
                    _curr = p;
                    p = p->parent;
                }
                _curr = p;
            }
            return (cpy);
        }

        bst_bidirectional_iterator  &operator--() {
            if (_curr == NULL) {
            }
            else if (_curr->left != NULL) {
                _curr = _curr->left;
                while (_curr->right) {
                    _curr = _curr->right;
                }
            }
            else {
                Node    p = _curr->parent;
                while (p != NULL && _curr == p->left) {
                    _curr = p;
                    p = p->parent;
                }
                _curr = p;
            }
            return (*this);
        }

        bst_bidirectional_iterator  operator--(int) {
            bst_bidirectional_iterator  cpy(_curr);
            if (_curr == NULL) {
            }
            else if (_curr->left != NULL) {
                _curr = _curr->left;
                while (_curr->right) {
                    _curr = _curr->right;
                }
            }
            else {
                Node    p = _curr->parent;
                while (p != NULL && _curr == p->left) {
                    _curr = p;
                    p = p->parent;
                }
                _curr = p;
            }
            return (cpy);
        }

        bst_bidirectional_iterator	operator-(int const &i) const {
		    bst_bidirectional_iterator ret = *this;
		    for (int j = 0; j < i; j++) {
		    	ret--;
		    }
		    return (ret);
	    }

	    bst_bidirectional_iterator	operator+(int const &i) const {
	    	bst_bidirectional_iterator ret = *this;
	    	for (int j = 0; j < i; j++) {
	    		ret++;
	    	}
	    	return (ret);
	    }

        bool    operator==(bst_bidirectional_iterator const &rhs) const {
            return _curr == rhs._curr;
        }

        bool    operator!=(bst_bidirectional_iterator const &rhs) const {
            return !(*this == rhs);
        }

        reference   operator*() {
            return _curr->data;
        }

        reference   operator*() const {
            return _curr->data;
        }

        pointer operator->() {
            return &(this->operator*());
        }
        
        pointer operator->() const {
            return &(this->operator*());
        }
};

} // namespace ft

#endif
