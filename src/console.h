//
//  console.h
//  texttennis
//
//  Created by Robert Dionne on 2/25/13.
//
//

#ifndef __texttennis__console__
#define __texttennis__console__

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

#endif /* defined(__texttennis__console__) */
