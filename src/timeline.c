#include "timeline.h"

Timeline CreateTimeline() {
    return (Timeline) {0, 0, NULL};
}

void DestroyTimeline(Timeline* tl) {
    for(int i=0; i<tl->n; i++) {
        DestroyChannel(&tl->a[i]);
    }
    kv_destroy(*tl);
}

void UpdateTimeline(Timeline* tl, int frame) { 
    for(int i=0; i<tl->n; i++) {
        UpdateChannel(&tl->a[i], frame);
    }
}

Channel* CreateTimelineChannel(Timeline* tl, float* prop) {
    Channel ch = {prop, (Keys){0,0,NULL}};
    kv_push(Channel, *tl, ch);
    return &tl->a[tl->n-1];
}

Channel CreateChannel(float* prop){
    return (Channel){prop, (Keys){0,0,NULL}};
}

void DestroyChannel(Channel* ch){
    kv_destroy(ch->keys);
}

void AddKey(Channel* ch, int frame, float value, Easing easing){
    Key key = (Key){frame, value, easing}; 
    kv_push(Key, ch->keys, key);
}

void UpdateChannel(Channel* ch, int frame) {
    
    size_t n = ch->keys.n; // number of keys
    Key* k   = ch->keys.a; // vector of keys
    float* p = ch->prop;   // traget property

    // no keys, return
    if(n==0) return;

    // before first key
    if (frame<=k[0].frame) { 
        *p = k[0].value;
        return;
    }
    
    
    // after last key
    if (frame>=k[n-1].frame) {
        *p = k[n-1].value;
        return;
    }

    // find curent key
    for(int i=0; i<n-1; i++) {
        if (frame < k[i].frame) continue;
        if (frame>=k[i].frame && frame < k[i+1].frame) {
            float cur = frame - k[i].frame;
            float dur = k[i+1].frame - k[i].frame;
            float dif = k[i+1].value - k[i].value;
            if(k[i].easing!=NULL) {
                *p = k[i].easing(
                    cur, k[i].value, 
                    dif, dur);
            } else *p = k[i].value;
            return;
        }
    }
}
