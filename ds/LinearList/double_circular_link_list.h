#ifndef DS_LINEARLIST_DOUBLECIRCULARLINKLIST_H
#define DS_LINEARLIST_DOUBLECIRCULARLINKLIST_H

#include <iostream>
#include <sstream>
#include <initializer_list>
#include "tools/DescException.h"

template <typename ElementType>
class DoubleCircularLinkListNode
{
public:
  ElementType element_;
  DoubleCircularLinkListNode *prior_;
  DoubleCircularLinkListNode *next_;
  DoubleCircularLinkListNode(ElementType element = ElementType(),
                             DoubleCircularLinkListNode *prior = nullptr, DoubleCircularLinkListNode *next = nullptr)
      : element_(element), prior_(prior), next_(next) {}
  inline static DoubleCircularLinkListNode *new_ptr(
      ElementType element_value = ElementType(),
      DoubleCircularLinkListNode *prior = nullptr, DoubleCircularLinkListNode *next = nullptr)
  {
    return new DoubleCircularLinkListNode(element_value, prior, next);
  }

  inline static void delete_ptr(DoubleCircularLinkListNode *listnode)
  {
    delete listnode;
  }
};

template <typename ElementType>
class DoubleCircularLinkList
{
public:
  typedef DoubleCircularLinkListNode<ElementType> *PtrToNode;
  PtrToNode list_head_;
  unsigned int size_;
  DoubleCircularLinkList() : list_head_(new DoubleCircularLinkListNode<ElementType>), size_(0)
  {
    list_head_->next_ = list_head_->prior_ = list_head_;
  }
  DoubleCircularLinkList(unsigned int init_size, const ElementType *elements = nullptr)
      : list_head_(DoubleCircularLinkListNode<ElementType>::new_ptr()), size_(init_size)
  {
    PtrToNode pre_tmp = list_head_;
    PtrToNode now_tmp;
    for (int i = 0; i < size_; i++)
    {
      if (elements == nullptr)
        now_tmp = new DoubleCircularLinkListNode<ElementType>();
      else
        now_tmp = new DoubleCircularLinkListNode<ElementType>(elements[i]);
      pre_tmp->next_ = now_tmp;
      now_tmp->prior_ = pre_tmp;
      pre_tmp = pre_tmp->next_;
      now_tmp = now_tmp->next_;
    }
    // 连接伪表头与队列尾部
    list_head_->prior_ = pre_tmp;
    pre_tmp->next_ = list_head_;
  }
  DoubleCircularLinkList(const std::vector<ElementType> &elements)
      : list_head_(DoubleCircularLinkListNode<ElementType>::new_ptr()), size_(elements.size())
  {
    PtrToNode pre_tmp = list_head_;
    PtrToNode now_tmp;
    for (int i = 0; i < size_; i++)
    {
      now_tmp = DoubleCircularLinkListNode<ElementType>::new_ptr(elements[i]);
      pre_tmp->next_ = now_tmp;
      now_tmp->prior_ = pre_tmp;
      pre_tmp = pre_tmp->next_;
      now_tmp = now_tmp->next_;
    }
    // 连接伪表头与队列尾部
    list_head_->prior_ = pre_tmp;
    pre_tmp->next_ = list_head_;
  }
  DoubleCircularLinkList(const std::initializer_list<ElementType> &elements)
      : DoubleCircularLinkList((std::vector<ElementType>)elements) {}

  inline int size() const
  {
    return size_;
  }

  PtrToNode get_point(unsigned int index) const
  {
    if (index >= size_)
      throw new ArrayIndexOutofRangeException();
    PtrToNode point = list_head_;
    if (index * 2 < size_)
      // 正向搜索
      for (int i = 0; i < 1 + index; i++)
        point = point->next_;
    else
      for (int i = 0; i < size_ - index; i++)
        // 反向搜索
        point = point->prior_;
    return point;
  }

  // 将被插入的节点(insert_point)插入到链表节点(point_prior)的后面
  inline void insert_point_next(PtrToNode point_prior, PtrToNode inserted_point)
  {
    if (point_prior == nullptr || inserted_point == nullptr)
      throw new NullPointerAccessException();
    PtrToNode point_next = point_prior->next_;
    point_prior->next_ = inserted_point;
    point_next->prior_ = inserted_point;
    inserted_point->prior_ = point_prior;
    inserted_point->next_ = point_next;
    size_++;
  }

  inline void insert_point(unsigned int index, PtrToNode point)
  {
    PtrToNode point_prior = index == 0 ? list_head_ : get_point(index - 1);
    insert_point_next(point_prior, point);
  }

  inline void remove_point(PtrToNode point)
  {
    if (point == nullptr)
      throw new NullPointerAccessException();
    PtrToNode point_prior = point->prior_, point_next = point->next_;
    point_prior->next_ = point_next;
    point_next->prior_ = point_prior;
    point->prior_ = point->next_ = nullptr; // 清空被删除节点的上下文信息
    size_--;
  }

  inline ElementType get_element(unsigned int index) const
  {
    PtrToNode point = get_point(index);
    return point->element_;
  }

  inline void set_element(unsigned int index, ElementType element_value)
  {
    PtrToNode point = get_point(index);
    point->element_ = element_value;
  }

  inline void push_element(ElementType element_value)
  {
    insert_element(size_, element_value);
  }

  inline void pushback_element(ElementType element_value)
  {
    insert_element(size_, element_value);
  }

  inline void pushfront_element(ElementType element_value)
  {
    insert_element(0, element_value);
  }

  // 将数据插入到指定的位置下标或队尾的后一位(index)里，原来下标对应的元素向后移动一位。
  inline void insert_element(unsigned int index, ElementType element_value)
  {
    PtrToNode point = DoubleCircularLinkListNode<ElementType>::new_ptr(element_value);
    insert_point(index, point);
  }

  inline void remove_element(unsigned int index)
  {
    PtrToNode point = get_point(index);
    remove_point(point);
  }

  // 不仅从链表中删除该节点，还要执行节点的销毁工作，以防止内存泄漏
  inline void delete_element(unsigned int index)
  {
    PtrToNode point = get_point(index);
    remove_point(point);
    DoubleCircularLinkListNode<ElementType>::delete_ptr(point);
  }

  std::string to_string() const
  {
    std::stringstream res;
    PtrToNode tmp = list_head_->next_;
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