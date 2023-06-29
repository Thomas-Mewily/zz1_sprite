#include "base.h"

int input_mouse_x(context* c) { return c->mouse_x; }
int input_mouse_y(context* c) { return c->mouse_y; }
int input_mouse_old_x(context* c) { return c->mouse_old_x; }
int input_mouse_old_y(context* c) { return c->mouse_old_y; }
int input_mouse_delta_x(context* c) { return input_mouse_x(c)-input_mouse_old_x(c);  }
int input_mouse_delta_y(context* c) { return input_mouse_y(c)-input_mouse_old_y(c);  }
int32 input_mouse_flag(context* c) { return c->mouse_flag; }
const Uint8* input_kb_state(context* c) { return c->kb_state; }