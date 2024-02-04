/*这是一个头文件, 通常包含明示常量、宏函数、函数声明、结构模板定义、类型定义*/
#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

typedef struct 
{
    struct ShapeVtbl const *vptr;

    int16_t x;
    int16_t y;
} Shape;

// Shape 的虚表
struct ShapeVtbl
{
    uint32_t (*area)(const Shape * const me);
    void (*draw)(const Shape * const me);
};

typedef struct
{
    Shape super; //继承Shape

    // 自己的属性
    uint16_t width;
    uint16_t height;
} Rectangle;

typedef struct
{
    Shape super;

    uint16_t radius;
} Circle;


void Shape_ctor(Shape * const me, int16_t x, int16_t y);
void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy);
int16_t Shape_getX(const Shape * const me);
int16_t Shape_getY(const Shape * const me);

static inline uint32_t Shape_area(const Shape * const me)
{
    return (*me->vptr->area)(me);
}

static inline void Shape_draw(const Shape * const me)
{
    (*me->vptr->draw)(me);
}

void Rectangle_ctor(Rectangle * const me, int16_t x, int16_t y,
                    uint16_t width, uint16_t height);
void Circle_ctor(Circle * const me, int16_t x, int16_t y, uint16_t radius);

const Shape * largestShape(const Shape * shapes[], uint32_t nShapes);
void drawAllShapes(const Shape * shapes[], uint32_t nshapes);

#endif