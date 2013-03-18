#ifndef TEXTTENNIS_CONSOLE_H_
#define TEXTTENNIS_CONSOLE_H_

#include <iostream>
#include <list>
#include <string>

class Console {
public:
  Console();
  
  virtual ~Console();
  
  void Draw() const;
  
  void Log(const std::string &line);
  
private:
  static constexpr unsigned int kLineCount = 10;
  static constexpr float kLineSpacing = 10.0;
  
  std::list<std::string> lines;
};

#endif  // TEXTTENNIS_CONSOLE_H_
