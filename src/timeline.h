#pragma once

#include "kvec.h"

typedef float (*Easing)(float t, float b, float c, float d);    

typedef struct Key{
    int   frame;
    float value;
    Easing easing;
} Key;

typedef kvec_t(Key) Keys;

typedef struct  {
     float* prop;
     Keys keys;
} Channel;

typedef kvec_t(Channel) Timeline;

Timeline CreateTimeline();
void     DestroyTimeline(Timeline* tl);
void     AddChannel(Timeline* tl, Channel ch);
void     UpdateTimeline(Timeline* tl, int frame);

Channel* CreateTimelineChannel(Timeline* tl, float* prop);
void     DestroyChannel(Channel* ch);
void     AddKey(Channel* ch, int frame, float value, Easing easing);
void     UpdateChannel(Channel* ch, int frame);
