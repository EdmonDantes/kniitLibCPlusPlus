/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Custom implementation set template
 *
 * Use binary tree for this.
 * You should implement comparator interface for your class which will be use in this set.
 */

#ifndef KNIITLIBRARY_SET_H
#define KNIITLIBRARY_SET_H
#include "../core/comparator.h"
#include "iterator.h"
#include "../core/exception.h"

KNIIT_LIB_NAMESPACE {
    template <class T, class Comp = Comparator<T>>
    KNIIT_LIB_CLASS Set {

    protected:

        class SetIterator;

        class Node {

        private:
            friend class Set::SetIterator;

            Node* parent = 0;
            Node* left = 0;
            Node* right = 0;
            T* value = 0;
            Comp* comparator = 0;

            Node(Node* parent, Comp* comparator) {
                this->parent = parent;
                this->comparator = comparator;
            }
        public:

            Node(Comp* comparator) {
                this->comparator = comparator;
            }


            bool contains(const T& value) {
                if (comparator != 0 && this->value != 0) {
                    int compareResult = comparator->compare(value, *this->value);

                    if (compareResult == 0) {
                        return true;
                    }

                    if (compareResult < 0 && left != 0) {
                        return left->contains(value);
                    } else if (compareResult > 0 && right != 0) {
                        return right->contains(value);
                    }
                }
                return false;
            }

            //FUTURE: add auto balance when add new value
            bool add(const T& value) {
                if (comparator != 0) {
                    if (this->value == 0) {
                        this->value = new T(value);
                        return true;
                    } else {
                        int compareResult = comparator->compare(value, *this->value);
                        if (compareResult != 0) {
                            if (compareResult < 0) {
                                if (left == 0) {
                                    left = new Node(this, comparator);
                                }
                                return left->add(value);
                            } else {
                                if (right == 0) {
                                    right = new Node(this, comparator);
                                }

                                return right->add(value);
                            }
                        }
                    }
                }
                return false;
            }

            bool remove(const T& value) {
                if (comparator != 0) {
                    if (this->value != 0) {
                        int compareResult = comparator->compare(value, *this->valuef);
                        if (compareResult == 0) {
                            return removeThis();
                        } else if (compareResult < 0 && left != 0) {
                            return left->remove(value);
                        } else if (compareResult > 0 && right != 0) {
                            return right->remove(value);
                        }
                    }
                }
                return false;
            }

            bool removeThis() {
                Node** parent_pointer = parent->left == this ? &parent->left : &parent->right;

                Node* remove_pointer = *parent_pointer;

                if (left == 0 && right == 0) {
                    *parent_pointer = 0;
                } else if (left == 0 && right != 0) {
                    *parent_pointer = right;
                } else if (right == 0 && left != 0) {
                    *parent_pointer = left;
                } else {
                    *parent_pointer = right;
                    Node* tmp = right;
                    while (right->left != 0) {
                        tmp = tmp->left;
                    }
                    tmp->left = this->left;
                }

                left = 0;
                right = 0;
                comparator = 0;
                parent = 0;

                delete remove_pointer;

                return true;
            }

            ~Node() {

                if (parent != 0) {
                    Node *tmp = parent;
                    while (tmp->parent != 0) {
                        tmp = tmp->parent;
                    }

                    delete tmp;
                    parent = 0;
                }

                if (left != 0) {
                    left->parent = 0;
                    left->comparator = 0;
                    delete left;
                    left = 0;
                }

                if (right != 0) {
                    right->parent = 0;
                    right->comparator = 0;
                    delete right;
                    right = 0;
                }

                if (value != 0) {
                    delete value;
                }

                if (comparator != 0) {
                    delete comparator;
                }
            }
        };

        class SetIterator : public Iterator<T> {
        private:
            Node* root = 0;
            int status = 0;

            bool hasNext(Node* node, int status) {
                return (status & 1) == 1 && (status & 4) == 0
                || (status & 1) == 0 && node->left != 0
                || ((status & 2) == 0) && node->right != 0
                || node->parent != 0 && hasNext(node->parent, node->parent->left == node ? 1 : 7);
            }

        public:

            SetIterator(const SetIterator& iterator) {
                this->root = iterator.root;
                this->toLeft = iterator.toLeft;
            }

            ~SetIterator(){}

            explicit SetIterator(Node* root) {
                this->root = root;
            }

            bool hasNext() {
                return this->root != 0 && hasNext(this->root, this->status);
            }

            //FIXME: to do output last element
            T& next() {
                if (!hasNext()) {
                    throw createException2("Set::SetIterator", "Has not next element in iterator");
                }

                while (true) {
                    if ((status & 1) == 0) {
                        if (this->root->left == 0) {
                            status |= 1;
                        } else {
                            while (this->root->left != 0) {
                                this->root = this->root->left;
                            }

                            return *this->root->value;
                        }
                    }

                    if ((status & 2) == 0) {
                        if (this->root->right == 0) {
                            status |= 2;
                        } else {
                            this->root = this->root->right;
                            status = 0;
                            if (this->root->left == 0) {
                                return *this->root->value;
                            }
                            continue;
                        }
                    }

                    if ((status & 3) == 3) {

                        if (this->root->parent == 0) {
                            throw createException2("Set::SetIterator", "Internal status error. Can not get parent of node");
                        }

                        status = (this->root->parent->left == this->root) ? 5 : 7;
                        this->root = this->root->parent;
                        if (status == 5) {
                            return *this->root->value;
                        }
                        continue;
                    }
                }
            }

            bool remove() {
                return false;
            }
        };

        Node* root = nullptr;
        uintmax _size = 0;



    public:

        class DefaultComparator : public Comparator<T> {
            int compare(const T& a, const T& b) const {
                return a > b ? 1 : (a < b ? -1 : 0);
            };
        };

        Set(){
            root = new Node(new DefaultComparator());
        }

        Set(Comp* comparator) {
            root = new Node(comparator);
        }

        Set(Set&& set) {
            operator=(std::move(set));
        }

        ~Set() {
            if (root != 0) {
                delete root;
            }
        }

        Set& operator=(Set&& set) {
            if (this->root != nullptr) {
                delete this->root;
            }

            this->root = set.root;
            this->_size = set._size;
            set.root = 0;
            set._size = 0;
            return *this;
        }

        bool contains(const T& value) {
            return root->contains(value);
        }

        bool add(const T& value) {
            if (root->add(value)) {
                _size++;
                return true;
            }
            return false;
        }

        bool remove(const T& value) {
            if (root->remove(value)) {
                _size--;
                return true;
            }
            return false;
        }

        uintmax size() {
            return _size;
        }

        Iterator<T>* iterator(){
            return new SetIterator(root);
        }
    };
}
#endif //KNIITLIBRARY_SET_H
