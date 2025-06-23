
#include "cvec/iterator.h"

VecIterator init_vec_iter(Vec* vec) {
  return (VecIterator){
      .vec = vec,
      .index = 0,
      .current = (char*)vec->data,
  };
}

int next(VecIterator* iter, void* item) {
  if (iter->index >= iter->vec->length) {
    return 0;
  }

  memcpy(item, iter->current, iter->vec->elem_size);
  iter->index++;
  iter->current += iter->vec->elem_size;
  return 1;
}
