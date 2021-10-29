#ifndef DS_LINEARLIST_SEQLIST_H
#define DS_LINEARLIST_SEQLIST_H

#include <vector>
#include <iostream>
#include <initializer_list>
#include "ds/LinearList/list_kit.h"

/*
  SeqList<ElementType>
    Constructor:
      SeqList(unsigned int init_size)
    Member variable:
      vector<ElementType> elements_.
    Member function:
      int size().
      int get_element(unsigned int index).
      void set_element(unsigned int index, ElementType element_value).
      void push_element(ElementType element_value).
      void print_elements().
*/
template <typename ElementType>
struct SeqList
{
  std::vector<ElementType> elements_;

  SeqList(unsigned int init_size) : elements_(init_size) {}
  SeqList(unsigned int init_size, ElementType element_value) : elements_(init_size, element_value) {}
  SeqList(std::vector<ElementType> elements) : elements_(elements) {}
  SeqList(std::initializer_list<ElementType> elements) : elements_(elements) {}

  inline unsigned int size() const { return elements_.size(); }

  ElementType get_element(unsigned int index) const { return elements_[index]; }

  void set_element(unsigned int index, ElementType element_value)
  {
    elements_[index] = element_value;
  }

  void push_element(ElementType element_value)
  {
    elements_.push_back(element_value);
  }

  void insert_element(unsigned int index, ElementType element_value)
  {
    list_kit::convey(elements_, index, 1);
    elements_[index] = element_value;
  }

  void remove_element(unsigned int index)
  {
    list_kit::convey(elements_, index + 1, -1);
  }

  ElementType &operator[](unsigned int index)
  {
    return elements_[index];
  }

  std::string to_string() const
  {
    std::stringstream res;
    for (int i = 0; i < size() - 1; i++)
      res << elements_[i] << " ";
    if (size()>0)
      res << elements_.back();
    return res.str();
  }
};

#endif
