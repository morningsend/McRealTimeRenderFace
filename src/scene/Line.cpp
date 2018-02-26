//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Line.hpp"




Line Line::projectLine(mat4 viewProjectionMatrix){
  Line transformedEnds;

  transformedEnds.ends[0]=viewProjectionMatrix*ends[0];
  transformedEnds.ends[1]=viewProjectionMatrix*ends[1];

  transformedEnds.ends[0]/= transformedEnds.ends[0].w;
  transformedEnds.ends[1]/= transformedEnds.ends[1].w;

  return transformedEnds;



}
