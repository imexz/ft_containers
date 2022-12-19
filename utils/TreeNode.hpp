/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeNode.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrantz <mstrantz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:52:45 by mstrantz          #+#    #+#             */
/*   Updated: 2022/04/02 13:52:47 by mstrantz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREENODE_HPP
# define TREENODE_HPP

enum tree_color { RED = false, BLACK = true };

template <class T>
    struct tree_node {

        typedef T   value_type;

        tree_node   *parent;
        tree_node   *left;
        tree_node   *right;
        value_type  data;
        tree_color  color;
    };

#endif