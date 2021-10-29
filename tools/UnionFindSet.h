#ifndef TOOLS_UNIONFINDSET_H
#define TOOLS_UNIONFINDSET_H

class unionFindSet
{
private:
  typedef int ElementType;
  typedef int SetType;
  SetType *disjSet;

public:
  unionFindSet(int numSet)
  {
    disjSet = new SetType[numSet + 1];
    for (int i = 1; i <= numSet; i++)
      disjSet[i] = -1;
  }

  SetType Find(ElementType x)
  {
    if (disjSet[x] <= 0)
      return x;
    // 路径压缩
    else
      return disjSet[x] = Find(disjSet[x]);
  }

  // 按高度优化
  void Union(SetType r1, SetType r2)
  {
    // r1比r2高度更高，r2插入到r1中，r1树高度不变
    if (disjSet[r1] < disjSet[r2])
      disjSet[r2] = r1;
    // 其他情况一律r1插入到r2中
    else
    {
      // 若两者高度一样，则此时r2树高度加1
      if (disjSet[r1] == disjSet[r2])
        disjSet[r2]--;
      disjSet[r1] = r2;
    }
  }
};

#endif