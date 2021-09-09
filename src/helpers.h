/* date = September 8th 2021 10:52 pm */

#ifndef HELPERS_H
#define HELPERS_H

////////////////////////////////
// NOTE(allen): Clamps

#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)>(b))?(a):(b))

#define ClampTop(a,b) Min(a,b)
#define ClampBot(a,b) Max(a,b)

////////////////////////////////
// NOTE(allen): Linked Lists

#define SLLQueuePush(f,l,n) (((f)==0)?((f)=(l)=(n),(n)->next=0):(l)->next=(n),(n)->next=0)
#define SLLStackPush(f,n)   ((n)->next=(f),(f)=(n))
#define SLLStackPop(f)      (((f)==0)?(0):(f)=(f)->next)

#endif //HELPERS_H
