#ifndef DS_LINEARLIST_VECTORKITS_H
#define DS_LINEARLIST_VECTORKITS_H

#include <iostream>
#include <vector>

namespace list_kit
{
  template <typename ElementType>
  void convey(std::vector<ElementType> &elements,
              unsigned int start_position, int distance)
  {
    int old_size = elements.size();
    if (distance > 0)
    {
      elements.resize(old_size + distance);
      for (int i = old_size - 1; i >= start_position; i--)
      {
        elements[i + distance] = elements[i];
      }
    }
    else if (distance < 0)
    {
      for (int i = start_position; i < old_size; i++)
      {
        elements[i + distance] = elements[i];
      }
      elements.resize(old_size + distance);
    }
  }
} // namespace vector_kit

#endif