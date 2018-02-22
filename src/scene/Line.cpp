//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Line.hpp"




ProjectedLine Line::projectLine(mat4 viewProjectionMatrix){
  ProjectedLine transformedEnds;

  transformedEnds.ends[0]=viewProjectionMatrix*ends[0];
  transformedEnds.ends[1]=viewProjectionMatrix*ends[1];

  return transformedEnds;



}
