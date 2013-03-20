#ifndef TEXTTENNIS_PARAMETER_H_
#define TEXTTENNIS_PARAMETER_H_

#include <tr1/functional>

template <typename T>
class Parameter {
public:
  typedef std::tr1::function<T()> Getter;

  Parameter() : get_value(), value(value) {}

  Parameter(T value) : get_value(), value(value) {}

  Parameter(Getter get_value) : get_value(get_value), value() {}

  virtual ~Parameter() {}

  T Get() const {
    return get_value ? get_value() : value;
  };

  void MaybeSet(T value) {
    if (!get_value) {
      this->value = value;
    }
  }

  operator T() const {
    return Get();
  }

private:
  Getter get_value;
  T value;
};

#endif  // TEXTTENNIS_PARAMETER_H_
