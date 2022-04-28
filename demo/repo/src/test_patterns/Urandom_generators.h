#ifndef URANDOM_GENERATORS_H_INCLUDED
#define URANDOM_GENERATORS_H_INCLUDED

  void getRndSizes(size_t max_sample_value, size_t _sample_size, size_t *const& p_sample);
  void getRndValues(size_t _sample_size, double *const& p_sample);

#endif // URANDOM_GENERATORS_H_INCLUDED
