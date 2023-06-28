#ifndef INPUT_H
#define INPUT_H
#include "base.h"

#define pull_up_masked(newState, oldState, mask)      ( (  (newState)  & (mask) )  && (!((oldState) & (mask))) )
#define pull_down_masked(newState, oldState, mask)    ( (!((newState)  & (mask)))  && (  (oldState) & (mask) ) )
#define pull_changed_masked(newState, oldState, mask) ( (  (newState)  & (mask) )  != (  (oldState) & (mask) ) )

#define pull_up(newState, oldState)      (  (newState)  && (!(oldState)))
#define pull_down(newState, oldState)    ((!(newState)) &&   (oldState) )
#define pull_changed(newState, oldState) (( (newState)) !=   (oldState) )

#define pressed(newState)
#endif