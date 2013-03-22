#ifndef TEXTTENNIS_PARAMETER_H_
#define TEXTTENNIS_PARAMETER_H_

#include <set>
#include <string>
#include <tr1/functional>
#include <vector>

#define DEFINE_PARAMETER(type, name, value) \
  auto name = Parameter<type>(#name, [] (Dependent *dependent) -> type {return (value);});

#define DEFINE_PARAMETER_RANGE(type, name, value, min, max) \
  auto name = Parameter<type>(#name, [] (Dependent *dependent) -> type {return (value);}, min, max);

#define DEPENDENCY(dependency) \
  dependency.GetValue(dependent)

class Dependent {
public:
  virtual ~Dependent() {}

  void SetStale(bool stale) {
    this->stale = stale;
  }

protected:
  Dependent() : stale(true) {}

  bool stale;
};

template <typename T>
class Parameter : public Dependent {
public:
  typedef std::tr1::function<T(Dependent *)> Getter;

  Parameter(const std::string name, Getter get_value, T min = T(), T max = T())
  : Dependent(), name(name), get_value(get_value), value(), dependents(), min(min), max(max) {
    AddParameter(this);
  }

  virtual ~Parameter() {}

  const std::string &GetName() const {
    return name;
  }

  T GetValue(Dependent *dependent = nullptr) {
    if (dependent) {
      dependents.insert(dependent);
    }
    if (stale) {
      value = get_value(this);
      stale = false;
    }
    return value;
  };

  void Set(T value) {
    this->value = value;
    NotifyDependents();
  }

  operator T() {
    return GetValue();
  }

  Parameter<T> &operator =(T value) {
    Set(value);
    return *this;
  }

  Parameter<T> &operator +=(T value) {
    Set(this->value + value);
    return *this;
  }

  Parameter<T> &operator -=(T value) {
    Set(this->value - value);
    return *this;
  }

  template <typename U>
  Parameter<T> &operator *=(U value) {
    Set(this->value * value);
    return *this;
  }

  template <typename U>
  Parameter<T> &operator /=(U value) {
    Set(this->value / value);
    return *this;
  }

  const T min;
  const T max;

public:
  static const std::vector<Parameter<T> *> &GetParameters() {
    return parameters;
  }

private:
  static void AddParameter(Parameter<T> *parameter) {
    parameters.push_back(parameter);
  }

  static std::vector<Parameter<T> *> parameters;

  void NotifyDependents() {
    for (auto dependent : dependents) {
      dependent->SetStale(true);
    }
  }

private:
  const std::string name;
  Getter get_value;
  T value;
  std::set<Dependent *> dependents;
};

template <typename T> std::vector<Parameter<T> *> Parameter<T>::parameters;

#endif  // TEXTTENNIS_PARAMETER_H_
