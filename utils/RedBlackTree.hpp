/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:46:49 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/26 10:37:28 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_BST_HPP
# define RB_BST_HPP

// Red Black Tree Insertion Rules
// - Every node is red or black
// - Root is always black
// - New insertions are always red
// - Every path from root to leaf has the same number of BLACK nodes
// - No path can have two consecutive RED nodes (if a node is RED both of its children are BLACK)
// - Nulls are black (leaf nodes) (if key is searched that is not present you end up at a NULL node)

// Rebalance:
//  Parents "sister" node, has same parent as the currents nodes parent
//  Black Aunt -> do Rotate: Bar (?)
//  Red Aunt -> do Colorflip
//  After rotation: parent is black, children are red
//  After color flip: parent ends up red, children end up black
//

// Left-rotation: node x goes down in the left direction, right child goes up (left_rotate(T, x))
// Right-rotation: node x goes down in the right direction, left child goes up (right_rotate(T, x))
// Recolor: flips color of a node

// Operations:
//  Insertion
//      1. insert node K using ordinary BST insertion operation
//      2. color K red
//      3. check if insertion violated rbt properties. if so, fix it.
//
//      T tree
//      P parent node,
//      U uncle node,
//      S sibling node,
//      G grandparent node of K
//
//      Case 1: T is empty -> make K root node of T, color it black
//      Case 2: P is black -> no violation possible
//      Case 3: P is red -> violation, check U's color
//          Case 3.1: P is red and U is red -> flip color of P, U and G (take care that G isn't the root node)
//          Case 3.2: P is red and U is black
//              Case 3.2.1: R is right child of G and K is right child of P -> left-rotation at G (G is new sibling S of K), recolor S to red, P to black
//              Case 3.2.2: P is right child of G and K is left child of P -> right-rotation at P -> Case 3.2.1
//              Case 3.2.3: P is left child of G and K is left child of P -> mirror of case 3.2.1
//              Case 3.2.4: P is left child of G and K is right child of P -> mirror of case 3.2.2
//
//  Deletion
//      follow ordinary BST deletion process which makes sure that x is either a leaf node or has a single child.
//
//      Case 1: x is a red node -> simply delete x
//      Case 2: x has a red child -> replace x by its red child and change the color or the child to red
//      Case 3: x is a black node
//          Case 3.1: x's S is red -> switch colors of S and x.parent, perform left rotation on x.parent -> case 3.2, 3.3 or 3.4
//          Case 3.2: x's S is black, both S's children are black -> switch color or S to red, if color of x's parent is red, we change its color to black.
//              Otherwise: make x's parent new x and repeat process from case 3.1
//          Case 3.3: x's S is black, S's left child is red and S's right child is black -> switch colors of S and its left child S.left, right rotation on S -> case 3.4
//          Case 3.4: x's S is black, S's right child is red -> color change of S's right child to black, x's parent to black and perform left rotation at x's P

# include "../utils/Pair.hpp"
# include "../utils/Utils.hpp"
# include "TreeNode.hpp"
# include <functional>
# include <iostream>
# include "../iterators/bst_bidirectional_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft {

template < class T,
           class Compare = std::less<T>,
           class Alloc = std::allocator<T>
         >
    class RB_BST {

        public:
            typedef T                                                                   value_type;
            typedef Compare                                                             value_compare;
            typedef Alloc                                                               allocator_type;
            typedef typename Alloc::template rebind<tree_node<value_type> >::other      node_allocator_type;
            typedef tree_node<value_type>                                               Node;
            typedef bst_bidirectional_iterator<Node *, RB_BST, T>             iterator;
            typedef bst_bidirectional_iterator<const Node *, RB_BST, const T> const_iterator;
            typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;
            typedef size_t                                                              size_type;

        private:
            Node                _parent;
            Node                *_root;
            allocator_type      _alloc;
            node_allocator_type _node_alloc;
            value_compare       _cmp;
            size_type           _size;

            Node    *_createNode(value_type const &val) {
                Node    *ret = _node_alloc.allocate(1);
                _alloc.construct(&(ret->data), val);
                ret->parent = NULL;
                ret->left = NULL;
                ret->right = NULL;
                ret->color = RED;
                return (ret);
            }

            void    _removeNode(Node *root) {
                _alloc.destroy(&(root->data));
                _node_alloc.deallocate(root, 1);
            }

            void    _clear(Node *node) {
                if (node == NULL)
                    return ;
                _clear(node->left);
                _clear(node->right);
                _removeNode(node);
            }
            /* template <class _Tp>
            struct less : binary_function<_Tp, _Tp, bool>
            {
                bool operator()(const _Tp& __x, const _Tp& __y) const
                    {return __x < __y;}
            }; */
            bool    _equals(value_type const &first, value_type const &second) const {
                return (!_cmp(first, second) && !_cmp(second, first));
            }

            // Node *root must be the root of the BST you want to search the key for.
            Node    *_searchTreeHelper(Node *root, value_type const &key) const {
                if (root == NULL || _equals(root->data, key)) {
                    return root;
                }
                if (_cmp(key, root->data) && root->left == NULL) {
				    return root;
			    }
			    if (!_cmp(key, root->data) && root->right == NULL) {
				    return root;
			    }
                if (_cmp(key, root->data)) {
                    return (_searchTreeHelper(root->left, key));
                }
                return (_searchTreeHelper(root->right, key));
            }

            // returns node with minimum key of the BST defined by Node *root
            Node    *_minimum(Node *root) const {
                while (root && root->left && root != &_parent) {
                    root = root->left;
                }
                return root;
            }

            // returns node with maximum key of the BST defined by Node *root
            Node    *_maximum(Node *root) const {
                while (root && root->right) {
                    root = root->right;
                }
                return root;
            }

            // if curr is last element, _successor will be NULL (?)
            Node    *_successor(Node *curr) {
                if (curr == NULL)
                    return NULL;
                if (curr->right != NULL) {
                    return _minimum(curr->right);
                }
                Node    *currParent = curr->parent;
                while (currParent != NULL && curr == currParent->right) {
                    curr = currParent;
                    currParent = currParent->parent;
                }
                return currParent;
            }

            // if curr is first element, _predecessor will be NULL (?)
            Node    *_predecessor(Node *curr) {
                if (curr == NULL)
                    return NULL;
                if (curr->left != NULL) {
                    return _maximum(curr->left);
                }
                Node    *currParent = curr->parent;
                while (currParent != NULL && curr == currParent->left) {
                    curr = currParent;
                    currParent = currParent->parent;
                }
                return currParent;
            }

            void    _rotate_right(Node *z) {
                if (z == NULL || z->left == NULL)
                    return;
                Node    *tmp = z->left;
                if (z == _root) {
                    _root = tmp;
                    _root->parent = &_parent;
                    _parent.left = _root;
                }
                if (z->parent && z->parent != &_parent) {
                    if (z->parent->left == z) {
                        z->parent->left = tmp;
                    }
                    else {
                        z->parent->right = tmp;
                    }
                }
                tmp->parent = z->parent;
                z->parent = tmp;
                z->left = tmp->right;
                if (z->left) {
                    z->left->parent = z;
                }
                tmp->right = z;
            }

            void    _rotate_left(Node *x) {
                if (x == NULL || x->right == NULL)
                    return;
                Node    *tmp = x->right;
                if (x == _root) {
                    _root = tmp;
                    _root->parent = &_parent;
                    _parent.left = _root;
                }
                if (x->parent && x->parent != &_parent) {
                    if (x->parent->left == x) {
                        x->parent->left = tmp;
                    }
                    else {
                        x->parent->right = tmp;
                    }
                }
                tmp->parent = x->parent;
                x->parent = tmp;
                x->right = tmp->left;
                if (x->right) {
                    x->right->parent = x;
                }
                tmp->left = x;
            }

            void    _insert_fix(Node *root) {
                Node	*tmp;
			    while (root->parent && root->parent != &_parent && root->parent->color == RED) {
			    	if (root->parent == root->parent->parent->left) {
			    		tmp = root->parent->parent->right;
			    		if (tmp && tmp->color == RED) {
			    			root->parent->color = BLACK;
			    			tmp->color = BLACK;
			    			root->parent->parent->color = RED;
			    			root = root->parent->parent;
			    		} else if (root == root->parent->right) {
			    			root = root->parent;
			    			_rotate_left(root);
			    		}
			    		else {
			    			root->parent->color = BLACK;
			    			root->parent->parent->color = RED;
			    			_rotate_right(root->parent->parent);
			    		}
			    	}
			    	else {
			    		tmp = root->parent->parent->left;
			    		if (tmp && tmp->color == RED) {
			    			root->parent->color = BLACK;
			    			tmp->color = BLACK;
			    			root->parent->parent->color = RED;
			    			root = root->parent->parent;
			    		} else if (root == root->parent->left) {
			    			root = root->parent;
			    			_rotate_right(root);
			    		}
			    		else {
			    			root->parent->color = BLACK;
			    			root->parent->parent->color = RED;
			    			_rotate_left(root->parent->parent);
			    		}
			    	}
			    }
			    _root->color = BLACK;
            }

            //find node that does not have a left child
            // in the subtree of the given node
            Node    *_successor_in_subtree(Node *x) {
                Node    *tmp = x;
                while (tmp->left != NULL) {
                    tmp = tmp->left;
                }
                return (tmp);
            }

            Node    *_sibling(Node   *x) {
                if (x->parent == NULL)
                    return (NULL);
                if (x->parent->left == x)
                    return (x->parent->right);
                else
                    return (x->parent->left);
            }

            Node    *_replace(Node *x) {
                // when node has 2 children
                if (x->left != NULL && x->right != NULL) {
                    return (_successor_in_subtree(x->right));
                }
                // when node is leaf
                if (x->left == NULL && x->right == NULL) {
                    return (NULL);
                }
                // when node has single child
                if (x->left != NULL) {
                    return (x->left);
                }
                else {
                    return (x->right);
                }
            }

            bool    _hasRedChild(Node *x) {
                return ((x->left != NULL && x->left->color == RED) ||
                    (x->right != NULL && x->right->color == RED));
            }

            void    _fixDoubleBlack(Node *x) {
                if (x == _root)
                    return;
                
                Node    *sibling = _sibling(x);
                Node    *parent = x->parent;
                if (sibling == NULL) {
                    // No sibling, double black pushed up
                    _fixDoubleBlack(parent);
                }
                else {
                    if (sibling->color == RED) {
                        parent->color = RED;
                        sibling->color = BLACK;
                        if (sibling == sibling->parent->left) {
                            _rotate_right(parent);
                        }
                        else {
                            _rotate_left(parent);
                        }
                        _fixDoubleBlack(x);
                    }
                    else {
                        //Sibling black
                        if (_hasRedChild(sibling)) {
                            // at least 1 red children
                            if (sibling->left != NULL && sibling->left->color == RED) {
                                if (sibling == sibling->parent->left) {
                                    // left left
                                    sibling->left->color = sibling->color;
                                    sibling->color =parent->color;
                                    _rotate_right(parent);
                                }
                                else {
                                    // right left
                                    sibling->left->color = parent->color;
                                    _rotate_right(sibling);
                                    _rotate_left(parent);
                                }
                            }
                            else {
                                if (sibling == sibling->parent->left) {
                                    // left right
                                    sibling->right->color = parent->color;
                                    _rotate_left(sibling);
                                    _rotate_right(parent);
                                }
                                else {
                                    // right right
                                    sibling->right->color = sibling->color;
                                    sibling->color = parent->color;
                                    _rotate_left(parent);
                                }
                            }
                            parent->color = BLACK;
                        }
                        else {
                            // 2 black children
                            sibling->color = RED;
                            if (parent->color == BLACK)
                                _fixDoubleBlack(parent);
                            else
                                parent->color = BLACK;
                        }
                    }
                }
            }

            void    _deleteNode(Node *v) {
                if (v == NULL)
                    return ;
                Node    *u = _replace(v);

                //True when u and v are both black
                bool    uvBlack = ((u == NULL || u->color == BLACK) && v->color == BLACK);
                Node    *parent = v->parent;

                if (u == NULL) {
                    // u is NULL therefore v is leaf
                    if (v == _root) {
                        // v is root, makeing root NULL
                        _root = NULL;
                        _parent.left = &_parent;
                    }
                    else {
                        if (uvBlack) {
                            // u and v are both black
                            // v is leaf, fix double black at v
                            _fixDoubleBlack(v);
                        }
                        else {
                            // u or v is red
                            if (_sibling(v) != NULL) {
                                // sibling is not null, make it red
                                _sibling(v)->color = RED;
                            }
                        }

                        // delete v from the tree
                        if (v->parent->left == v)
                            parent->left = NULL;
                        else
                            parent->right = NULL;
                    }
                    _removeNode(v);
                    return ;
                }

                if (v->left == NULL || v->right == NULL) {
                    // v has one child
                    if (v == _root) {
                        // v is root, assign the value of u to v, and delete u
                        _root = u;
                        _root->parent = &_parent;
                        u->left = NULL;
                        u->right = NULL;
                        u->color = BLACK;
                        _removeNode(v);
                    }
                    else {
                        // Detach v from tree and move u up
                        if (v->parent->left == v) {
                            parent->left = u;
                        }
                        else {
                            parent->right = u;
                        }
                        _removeNode(v);
                        u->parent = parent;
                        if (uvBlack) {
                            //u and v both are black, fix double black at u
                            _fixDoubleBlack(u);
                        }
                        else {
                            // u or v are red, color u black
                            u->color = BLACK;
                        }
                    }
                    return ;
                }

                // v has 2 children, swap values with successor and recurse       
                if (v == _root) {
                    _root = u;
                }
                if (v->parent && v == v->parent->left) {
                    v->parent->left = u;
                }
                else if (v->parent && v->parent->right == v) {
				    v->parent->right = u;
			    }
			    if (v->right) {
			    	v->right->parent = u;
			    }
			    if (v->left) {
			    	v->left->parent = u;
			    }
			    if (u->parent && u == u->parent->left) {
			    	u->parent->left = v;
			    }
			    if (u->parent && u == u->parent->right) {
			    	u->parent->right = v;
			    }
			    ft::swap(u->parent, v->parent);
			    ft::swap(u->left, v->left);
			    ft::swap(u->right, v->right);
			    ft::swap(u->color, v->color);
			    _deleteNode(v);
            }

            void    _printTreeHelper(Node *root, std::string indent, bool end) {
                if (root != NULL) {
                    std::cout << indent;
                    if (end) {
                        std::cout << "└────";
                        indent += "     ";
                    }
                    else {
                        std::cout << "├────";
                        indent += "|    ";
                    }
                    std::cout << root->data.first << " " << root->data.second << " " << (root->color ? "black":"red") << std::endl;
                    _printTreeHelper(root->left, indent, false);
                    _printTreeHelper(root->right, indent, true);
                }
            }

            void    _insert_range_in_preorder(RB_BST &tree, Node *node) {
                if (node == NULL)
                    return ;
                tree.insert(node->data);
                _insert_range_in_preorder(tree, node->left);
                _insert_range_in_preorder(tree, node->right);
            }

/*             void    _inorder(Node *node) {
                if (node != NULL) {
                    if (node->left)
                        _inorder(node->left);
                    std::cout << " " << node->data << " ";
                    if (node->right)
                        _inorder(node->right);
                }
                else {}
            }

            void    _preorder(Node *node) {
                if (node != NULL) {
                    std::cout << " " << node->data << " ";
                    if (node->left)
                        _preorder(node->left);
                    if (node->right)
                        _preorder(node->right);
                }
                else {}
            }

            void    _postorder(Node *node) {
                if (node != NULL) {
                    if (node->left)
                        _postorder(node->left);
                    if (node->right)
                        _postorder(node->right);
                    std::cout << " " << node->data << " ";
                }
                else {}
            } */

        public:
            explicit RB_BST(const value_compare& cmp = value_compare(), const allocator_type &alloc = allocator_type()) : _parent(), _root(NULL), _alloc(alloc), _node_alloc(alloc), _cmp(cmp), _size(0) {
                _parent.left = &_parent;
                _parent.right = NULL;
            }

            RB_BST(RB_BST const &src) : _parent(), _root(), _alloc(src._alloc), _node_alloc(src._node_alloc), _cmp(src._cmp), _size() {
                _parent.left = &_parent;
                _parent.right = NULL;
                _insert_range_in_preorder(*this, src._root);
            }

            ~RB_BST() {
                clear();
            }

            RB_BST    &operator=(RB_BST const &rhs) {
                this->clear();
                _cmp = rhs._cmp;
                _alloc = rhs._alloc;
                _node_alloc = rhs._node_alloc;
                _insert_range_in_preorder(*this, rhs._root);
                return *this;
            }

            /* --- Iterators --- */
            iterator    begin() {
                return (iterator(_minimum(_parent.left)));
            }

            const_iterator begin() const {
                return (const_iterator(_minimum(_parent.left)));
            }

            iterator    end() {
                return (iterator(&_parent));
            }

            const_iterator  end() const {
                return (const_iterator(&_parent));
            }

            reverse_iterator    rbegin() {
                return (reverse_iterator(end()));
            }

            const_reverse_iterator  rbegin() const {
                return (const_reverse_iterator(end()));
            }

            reverse_iterator    rend() {
                return (reverse_iterator(begin()));
            }

            const_reverse_iterator  rend() const {
                return (const_reverse_iterator(begin()));
            }

            /* --- Capacity --- */
            bool    empty() const {
                return (begin() == end());
            }

            size_type   size() const {
                return _size;
            }

            size_type   max_size() const {
                return _node_alloc.max_size();
            }

            /* --- Element access --- */

            Node    *getRoot(void) const {
                return (_root);
            }

            /* --- Modifiers --- */
            ft::pair<iterator, bool>    insert(value_type const &to_insert) {
                Node    *tmp;
                Node    *ret;

                if (empty()) {
                    Node    *newNode = _createNode(to_insert);
                    _root = newNode;
                    _root->parent = &_parent;
                    _parent.left = _root;
                    _root->color = BLACK;
                    _size++;
                    return (ft::make_pair(iterator(_root), true));
                }
                tmp = _searchTreeHelper(_root, to_insert);
                if (_equals(to_insert, tmp->data)) {
                    return (ft::make_pair(iterator(tmp), false));
                }
                else if (_cmp(to_insert, tmp->data)) {
                    tmp->left = _createNode(to_insert);
                    ret = tmp->left;
                    tmp->left->parent = tmp;
                    _insert_fix(tmp->left);
                    _size++;
                    return (ft::make_pair(iterator(ret), true));
                }
                else {
                    tmp->right = _createNode(to_insert);
                    ret = tmp->right;
                    tmp->right->parent = tmp;
                    _insert_fix(tmp->right);
                    _size++;
                    return (ft::make_pair(iterator(ret), true));
                }
            }

            iterator    insert(iterator pos, value_type const &to_insert) {
                (void) pos;
                return insert(to_insert).first;
            }

            template<class InputIterator>
                void    insert(InputIterator first, InputIterator last) {
                    while (first != last) {
                        insert(*first);
                        ++first;
                    }
                }

            size_type    deleteNode(value_type const &to_delete) {
                Node    *v = _searchTreeHelper(_root, to_delete);
                if (_root == NULL || !_equals(to_delete, v->data))
                    return 0;
                _deleteNode(v);
                _size--;
                return 1;
            }

            void    deleteNode(iterator first, iterator last) {
                while(first != last) {
                    deleteNode(first++.base()->data);
                }
            }

            void    swap(RB_BST   &x) {
                ft::swap(_parent.left, x._parent.left);
                ft::swap(_root, x._root);
                ft::swap(_alloc, x._alloc);
                ft::swap(_node_alloc, x._node_alloc);
                ft::swap(_cmp, x._cmp);
                ft::swap(_size, x._size);
                _root->parent = &_parent;
                x._root->parent = &x._parent;
            }

            void    clear() {
                _clear(_root);
                _parent.left = &_parent;
                _root = NULL;
                _size = 0;
            }

            /* --- Observers --- */
            value_compare   value_comp() const { return _cmp; }

            /* --- Operations --- */
            iterator    find(value_type const &key) {
                Node    *res = _searchTreeHelper(_root, key);
                if (res == NULL || !_equals(res->data, key))
                    return (end());
                return(iterator(res));
            }

            const_iterator  find(value_type const &key) const {
                Node    *res = _searchTreeHelper(_root, key);
                if (res == NULL || !_equals(res->data, key))
                    return (end());
                return(const_iterator(res));
            }

            size_type   count(value_type const &key) const {
                return (find(key) != end());
            }

            iterator    lower_bound(value_type const &key) {
                iterator    b = begin();
                iterator    e = end();
                while (b != e && !_equals(*b, key) && !_cmp(key, *b))
                    ++b;
                return b;
            }

            const_iterator  lower_bound(value_type const &key) const {
                const_iterator  b = begin();
                const_iterator  e = end();
                while (b != e && !_equals(*b, key) && !_cmp(key, *b))
                    ++b;
                return b;
            }

            iterator    upper_bound(value_type const &key) {
                reverse_iterator    rb = rbegin();
                reverse_iterator    re = rend();
                while (rb != re && !_equals(*rb, key) && _cmp(key, *rb))
                    ++rb;
                return rb.base();
            }

            const_iterator  upper_bound(value_type const &key) const {
                const_reverse_iterator    rb = rbegin();
                const_reverse_iterator    re = rend();
                while (rb != re && !_equals(*rb, key) && _cmp(key, *rb))
                    ++rb;
                return rb.base();
            }

            ft::pair<const_iterator, const_iterator>    equal_range(value_type const &key) const {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            }

            ft::pair<iterator, iterator>    equal_range(value_type const &key) {
                return ft::make_pair(lower_bound(key), upper_bound(key));
            }

            void    prettyPrint() {
                _printTreeHelper(_root, "", true);
            }

/*          void    print__inorder() { _inorder(_root); }
            void    print__preorder() { _preorder(_root); }
            void    print__postorder() { _postorder(_root); } */

            /* --- Allocator --- */
            allocator_type  get_allocator() const {
                return (_alloc);
            }

            node_allocator_type get_node_allocator() const {
                return (_node_alloc);
            }
    };

} // namespace ft

#endif
