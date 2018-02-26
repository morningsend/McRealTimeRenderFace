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


    void clipLine3D(Line &line) {

        int outcode1 = computeOutcode3D(line.ends[0], vec4(-1,-1,-1,1), vec4(1,1,1,1));
        int outcode2 = computeOutcode3D(line.ends[1], vec4(-1,-1,-1,1), vec4(1,1,1,1));

        while(true){
            // both end points are inside the region.
            if((outcode1 | outcode2) == INSIDEMASK) {
                break;
            }
            // both ends points are outside the region
            else if (outcode1 & outcode2){
                break;
            }
            else{
              double x,y;

            }
        }
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
