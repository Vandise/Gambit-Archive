#ifndef __SHARED_INSTANCEOF
#define __SHARED_INSTANCEOF 1

template<typename Base, typename T>
inline bool instanceof(const T *ptr)
{
  return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif