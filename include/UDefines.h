#ifndef _UDEFINES_H_
#define _UDEFINES_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    TypeName& operator=(const TypeName&);

#define UASSET(Condition) \
    if (!(Condition)) { abort(); }
#define UEMPTY_SIZE   (-1)
#endif // _UDEFINES_H_
