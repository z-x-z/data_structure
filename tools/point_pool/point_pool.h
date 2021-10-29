#ifndef DS_TOOLS_POINTPOOL_POINTPOOL_H
#define DS_TOOLS_POINTPOOL_POINTPOOL_H

#include "ds/LinearList/double_circular_link_list.h"
#include <cmath>
#include "unordered_map"

template <typename ElementType>
class PointPool
{
  typedef ElementType *PtrToType; // int*
  typedef DoubleCircularLinkListNode<PtrToType> PoolNode;
  typedef PoolNode *PtrToPoolNode;

private:
  unsigned int size_;     // 空闲节点数
  unsigned int capacity_; // 总的节点数
  DoubleCircularLinkList<PtrToType> points_pool_;
  std::unordered_map<PtrToType, PtrToPoolNode> type_to_poolnode_map_;

  PtrToPoolNode type_to_poolnode(PtrToType type_point)  const
  {
    auto iter= type_to_poolnode_map_.find(type_point);
    if (iter == type_to_poolnode_map_.end())
      throw new IllegalOperationException();
    return (*iter).second;
  }

  void increase_capacity(unsigned int increment)
  {
    ElementType* types = new ElementType[increment];
    PoolNode* poolnodes = new PoolNode[increment];
    PtrToPoolNode *poolnode_ptrs = new PtrToPoolNode[increment];
    for (int i = 0; i < increment; i++)
    {
      poolnodes[i].element_ = &types[i];
      poolnode_ptrs[i] = & poolnodes[i];
      points_pool_.insert_point(0, poolnode_ptrs[i]);
      type_to_poolnode_map_[poolnode_ptrs[i]->element_] = poolnode_ptrs[i];
    }
    capacity_ += increment;
    size_ += increment;
  }

  inline void check_size()
  {
    if (size_ == 0)
      increase_capacity(capacity_);
    else if (size_ > capacity_)
      throw new ProgramRunningLogicException();
  }

  unsigned int min_bigger_2pow(unsigned int num)
  {
    int t = log2(num);
    return pow(2, t+1);
  }
public:
  PointPool(unsigned int init_capacity)
      : size_(0), capacity_(0), points_pool_()
  {
    increase_capacity(min_bigger_2pow(init_capacity));
  }
  ~PointPool()
  {
  }

  int size() const
  {
    return size_;
  }

  int capacity() const
  {
    return capacity_;
  }

  PtrToType release_point()
  {
    // 从链表表头处删除一个节点
    PtrToPoolNode point = points_pool_.get_point(0);
    points_pool_.remove_element(0);
    size_--;
    check_size();
    return point->element_;
  }

  void recycle_point(PtrToType type_point)
  {
    PtrToPoolNode pool_node = type_to_poolnode(type_point);
    points_pool_.insert_point(points_pool_.size(), pool_node);
    size_++;
    check_size();
  }
};

#endif