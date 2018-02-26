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


bool clipLine3D(Line &line) {
        bool accept=true;
        int outcode0 = computeOutcode3D(line.ends[0], vec4(-1,-1,-1,1), vec4(1,1,1,1));
        int outcode1 = computeOutcode3D(line.ends[1], vec4(-1,-1,-1,1), vec4(1,1,1,1));


        while(true){

          // std::cout << "outcode0 : " << outcode0 << " outcode1 : " << outcode1 << '\n';

            // both end points are inside the region.
            if((outcode0 | outcode1) == INSIDEMASK) {
                break;
            }
            // both ends points share an otside region
            else if (outcode0 & outcode1){
                accept = false;
                break;
            }
            else{
              vec4 intersect;
              intersect.w=1;
              int outcodeOut = outcode0?outcode0:outcode1;

              if (outcodeOut & TOPMASK){
                intersect.x=line.ends[0].x + (line.ends[1].x - line.ends[0].x) / (line.ends[1].y - line.ends[0].y) * (1-line.ends[0].y);
                intersect.y=1;
                intersect.z=line.ends[0].z + (line.ends[1].z - line.ends[0].z) / (line.ends[1].y - line.ends[0].y) * (1-line.ends[0].y);
              }
              else if (outcodeOut & BOTTOMMASK){
                intersect.x=line.ends[0].x + (line.ends[1].x - line.ends[0].x) / (line.ends[1].y - line.ends[0].y) * (-1-line.ends[0].y);
                intersect.y=-1;
                intersect.z=line.ends[0].z + (line.ends[1].z - line.ends[0].z) / (line.ends[1].y - line.ends[0].y) * (-1-line.ends[0].y);
              }
              else if (outcodeOut & RIGHTMASK){
                intersect.x=1;
                intersect.y=line.ends[0].y + (line.ends[1].y - line.ends[0].y) / (line.ends[1].x - line.ends[0].x) * (1-line.ends[0].x);
                intersect.z=line.ends[0].z + (line.ends[1].z - line.ends[0].z) / (line.ends[1].x - line.ends[0].x) * (1-line.ends[0].x);
              }
              else if (outcodeOut & LEFTMASK){
                intersect.x=-1;
                intersect.y=line.ends[0].y + (line.ends[1].y - line.ends[0].y) / (line.ends[1].x - line.ends[0].x) * (-1-line.ends[0].x);
                intersect.z=line.ends[0].z + (line.ends[1].z - line.ends[0].z) / (line.ends[1].x - line.ends[0].x) * (-1-line.ends[0].x);
              }
              else if (outcodeOut & FRONTMASK){
                intersect.x=line.ends[0].x + (line.ends[1].x - line.ends[0].x) / (line.ends[1].z - line.ends[0].z) * (1-line.ends[0].z);
                intersect.y=line.ends[0].y + (line.ends[1].y - line.ends[0].y) / (line.ends[1].z - line.ends[0].z) * (1-line.ends[0].z);
                intersect.z=1;
              }
              else if (outcodeOut & BACKMASK){
                intersect.x=line.ends[0].x + (line.ends[1].x - line.ends[0].x) / (line.ends[1].z - line.ends[0].z) * (-1-line.ends[0].z);
                intersect.y=line.ends[0].y + (line.ends[1].y - line.ends[0].y) / (line.ends[1].z - line.ends[0].z) * (-1-line.ends[0].z);
                intersect.z=-1;
              }

              if (outcodeOut == outcode0){
                line.ends[0]=intersect;
                outcode0 = computeOutcode3D(line.ends[0], vec4(-1,-1,-1,1), vec4(1,1,1,1));
              }
              else {
                line.ends[1]=intersect;
                outcode1 = computeOutcode3D(line.ends[1], vec4(-1,-1,-1,1), vec4(1,1,1,1));
              }

            }
        }

        return accept;
    }

    int computeOutcode3D(vec4 point, vec4 min, vec4 max) {
        int outcode = INSIDEMASK;

        if(point.x < min.x) {
            outcode |= LEFTMASK;
        } else if(point.x > max.x) {
            outcode |= RIGHTMASK;
        }

        if(point.y < min.y) {
            outcode |= BOTTOMMASK;
        } else if(point.y > max.y) {
            outcode |= TOPMASK;
        }

        if(point.z < min.z) {
            outcode |= FRONTMASK;
        } else if(point.z > max.z) {
            outcode |= BACKMASK;
        }

        return outcode;
    }
