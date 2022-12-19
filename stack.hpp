/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:25:43 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/23 09:39:50 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
    class stack {

        public:
            typedef Container                                   container_type;
            typedef typename container_type::value_type         value_type;
            typedef typename container_type::size_type          size_type;

        protected:
            container_type  c;

        public:
            ~stack() {
                c.clear();
            }

            stack   &operator=(const stack &q) {
                c = q.c;
                return (*this);
            }

            explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}

            bool            empty() const {
                return c.empty();
            }
            size_type       size() const {
                return c.size();
            }
            value_type&       top() {
                return c.back();
            }
            const value_type& top() const {
                return c.back();
            }
            void            push(const value_type& val) {
                c.push_back(val);
            }
            void            pop() {
                c.pop_back();
            }

            template <class T1, class _C1>
                friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
            template <class T1, class _C1>
                friend bool operator< (const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
    };

template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return lhs.c == rhs.c;
  }
template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return !(lhs == rhs);
  }
template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return lhs.c < rhs.c;
  }
template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return !(rhs < lhs);
  }
template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return rhs < lhs;
  }
template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
      return !(lhs < rhs);
  }

} // namespace ft

#endif