#include "base.h"

void testVec(){

    vec* v = vec_empty(int);
    //vec_push(v, color, rgb(1,2,3));
    vec_push(v, int, 1);
    vec_push(v, int, 2);

    //vec_printf_int(v);
    vec_free_lazy(v);
}

void test_debug()
{
        //SDL_Rect r = rectangle(0,10,2)
    //angle a = from_degree(180);
    //float degree = as_degree(a);
    //float rad = as_radian(a);
    //float cosinus = cos(a);
}