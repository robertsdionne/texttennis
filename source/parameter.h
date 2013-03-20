#ifndef TEXTTENNIS_PARAMETER_H_
#define TEXTTENNIS_PARAMETER_H_

#include <string>
#include <tr1/functional>

#define DEFINE_PARAMETER(type, name, value) \
  auto name = Parameter<type>(#name, value);

template <typename T>
class Parameter {
public:
  typedef std::tr1::function<T()> Getter;

  Parameter(T value) : name(), get_value(), value(value) {}

  Parameter(Getter get_value) : name(), get_value(get_value), value() {}

  Parameter(const std::string name) : name(name), get_value(), value(value) {
    AddParameter(this);
  }

  Parameter(const std::string name, T value) : name(name), get_value(), value(value) {
    AddParameter(this);
  }

  Parameter(const std::string name, Getter get_value) : name(name), get_value(get_value), value() {
    AddParameter(this);
  }

  virtual ~Parameter() {}

  const std::string &GetName() const {
    return name;
  }

  T GetValue() const {
    return get_value ? get_value() : value;
  };

  void MaybeSet(T value) {
    if (!get_value) {
      this->value = value;
    }
  }

  operator T() const {
    return GetValue();
  }

public:
  static const std::vector<Parameter<T> *> GetParameters() {
    return parameters;
  }

private:
  static void AddParameter(Parameter<T> *parameter) {
    parameters.push_back(parameter);
  }

  static std::vector<Parameter<T> *> parameters;

private:
  const std::string name;
  Getter get_value;
  T value;
};

template <typename T> std::vector<Parameter<T> *> Parameter<T>::parameters;

#endif  // TEXTTENNIS_PARAMETER_H_
