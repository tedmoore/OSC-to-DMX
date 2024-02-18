//
//  Light.cpp
//  osc_to_dmx
//
//  Created by Theodore Moore on 3/14/18.
//
#include <stdio.h>
#include <stdlib.h>

#include "Light.hpp"

void Light::create(LightType lightType_, int indexOffset_){
    indexOffset = indexOffset_;
    setLightType(lightType_);
}

void Light::getColorValues(int* data, int* r, int* g, int* b, int* w){
    switch (lightType) {
        case SPOT:
            // 255 R G B W 0 0 0
            *r = data[indexOffset + rIndex];
            *g = data[indexOffset + gIndex];
            *b = data[indexOffset + bIndex];
            *w = data[indexOffset + wIndex];
            break;
        case SLIMPAR:
        {
            // R G B W 0 0 0 master
            double masterMul = data[indexOffset + masterIndex] / 255.0;
            *r = data[indexOffset + rIndex] * masterMul;
            *g = data[indexOffset + gIndex] * masterMul;
            *b = data[indexOffset + bIndex] * masterMul;
            *w = data[indexOffset + wIndex] * masterMul;
        }
            break;
        default:
            fprintf(stderr,"ERROR: Light::setLightType: lightType has bad value\n");
            exit(1);
            break;
    }
}

void Light::setLightType(LightType lightType_){
    lightType = lightType_;
    switch (lightType) {
        case SPOT:
            // 255 R G B W 0 0 0
            rIndex = 1;
            gIndex = 2;
            bIndex = 3;
            wIndex = 4;
            masterIndex = NULL;
            break;
        case SLIMPAR:
            // R G B W 0 0 0 master
            rIndex = 0;
            gIndex = 1;
            bIndex = 2;
            wIndex = 3;
            masterIndex = 7;
            break;
        default:
            fprintf(stderr,"ERROR: Light::setLightType: lightType has bad value\n");
            exit(1);
            break;
    }
}
