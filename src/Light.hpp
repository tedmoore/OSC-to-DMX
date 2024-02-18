//
//  Light.hpp
//  osc_to_dmx
//
//  Created by Theodore Moore on 3/14/18.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>

enum LightType { SPOT, SLIMPAR };

class Light{
public:
    void create(LightType lightType_, int indexOffset_);
    void getColorValues(int* data, int* r, int* g, int* b, int* w);
    void setLightType(LightType lightType_);
    
    LightType lightType;
    int indexOffset;
    int rIndex;
    int gIndex;
    int bIndex;
    int wIndex;
    int masterIndex;
};

#endif /* Light_hpp */
