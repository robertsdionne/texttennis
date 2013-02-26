//
//  describer.h
//  texttennis
//
//  Created by Robert Dionne on 2/25/13.
//
//

#ifndef __texttennis__describer__
#define __texttennis__describer__

#include <iostream>
#include <string>

#include "gamestate.h"

class Describer {
public:
  Describer();
  
  virtual ~Describer();
  
  std::string Describe(const GameState &state) const;
};

#endif /* defined(__texttennis__describer__) */
