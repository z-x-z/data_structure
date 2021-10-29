#ifndef DS_LINEARLIST_LINKLIST_H
#define DS_LINEARLIST_LINKLIST_H

#include <iostream>
#include <initializer_list>
#include "tools/DescException.h"

template <typename ElementType>
class LinkList
{
private:
  struct LinkListNode
  {
    ElementType element_;
    LinkListNode *next_;

    inline static LinkListNode *new_ptr(
        ElementType element_value = ElementType(), LinkListNode *next = nullptr)
    {
      return new LinkListNode(element_value, next);
    }

    inline static void delete_ptr(LinkListNode *listnode)
    {
      if (listnode == nullptr)
        throw new NullPointerAccessException();
      delete listnode;
    }
    LinkListNode(ElementType element = ElementType(), LinkListNode *next = nullptr)
        : element_(element), next_(next){};
  };

  LinkListNode *list_head_;
  unsigned int size_;

  // -1默认表示伪表头，0表示第一个元素
  LinkListNode *get_point(unsigned int index) const
  {
    LinkListNode *tmp = list_head_->next_;
    for (int i = 0; i < index; i++)
      tmp = tmp->next_;
    return tmp;
  }

public:
  LinkList(unsigned int init_size = 0) : size_(init_size)
  {
    list_head_ = LinkListNode::new_ptr();
    LinkListNode *tmp = list_head_;
    for (int i = 0; i < size_; i++)
    {
      tmp->next_ = LinkListNode::new_ptr();
      tmp = tmp->next_;
    }
  }
  LinkList(const std::vector<ElementType> &elements) : size_(elements.size())
  {
    list_head_ = LinkListNode::new_ptr();
    LinkListNode *tmp = list_head_;
    for (const ElementType &element : elements)
    {
      tmp->next_ = LinkListNode::new_ptr(element);
      tmp = tmp->next_;
    }
  }
  LinkList(const std::initializer_list<ElementType> &elements)
      : LinkList((std::vector<ElementType>)elements) {}

  inline int size() const
  {
    return size_;
  }

  ElementType get_element(unsigned int index) const
  {
    LinkListNode *tmp = get_point(index);
    return tmp->element_;
  }

  void set_element(unsigned int index, ElementType element_value)
  {
    LinkListNode *tmp = get_point(index);
    tmp->element_ = element_value;
  }

  void push_element(ElementType element_value)
  {
    insert_element(size_, element_value);
  }

  void insert_element(unsigned int index, ElementType element_value)
  {
    LinkListNode *tmp = index == 0 ? list_head_ : get_point(index - 1);
    LinkListNode *new_node = LinkListNode::new_ptr(element_value, tmp->next_);
    tmp->next_ = new_node;
    size_++;
  }

  void remove_element(unsigned int index)
  {
    LinkListNode *tmp = index == 0 ? list_head_ : get_point(index - 1);
    LinkListNode *tmp_next = tmp->next_;
    tmp->next_ = tmp_next->next_;
    tmp_next->next_ = nullptr;
    LinkListNode::delete_ptr(tmp_next);
    size_--;
  }

  std::string to_string() const
  {
    std::stringstream res;
    LinkListNode *tmp = list_head_->next_;
    for (int i = 0; i < size() - 1; i++)
    {
      res << tmp->element_ << " ";
      tmp = tmp->next_;
    }
    if (size() > 0)
      res << tmp->element_;
    return res.str();
  }
};

#endif