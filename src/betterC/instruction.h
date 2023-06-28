#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define twice(x) x x
#define unless(cond) if(!(cond))

#define field(type, name1, name2) union { type name1; type name2; }
#define UNUSED(x) (void)(x)

#endif