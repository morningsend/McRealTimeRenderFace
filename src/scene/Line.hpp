//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_LINE_HPP
#define RENDERER_LINE_HPP

#include <glm/glm.hpp>

  using namespace glm;

  // struct ProjectedLine{
  //   vec4 ends[2];
  // };
  class Line {
  public:
    vec4 ends[2];
    Line projectLine(mat4 viewProjectionMatrix);


    Line() {}
    Line(vec4 endsIn[2]): ends{endsIn[0], endsIn[1]} {}
    Line(vec4 end1, vec4 end2): ends{end1, end2} {}
    Line(vec3 endsIn[2]): ends{{endsIn[0].x, endsIn[0].y, endsIn[0].z, 0}, {endsIn[1].x, endsIn[1].y, endsIn[1].z, 0}} {}
    Line(vec3 end1, vec3 end2): ends{{end1.x, end1.y, end1.z, 0}, {end2.x, end2.y, end2.z, 0}} {}


  };



#endif //RENDERER_LINE_HPP
