/*file1.c -- 多文件项目的第一个文件*/
#include "shape.h"
#include <assert.h>
#include <stdio.h>

static uint32_t Shape_area_(const Shape * const me);
static void Shape_draw_(const Shape * const me);

void Shape_ctor(Shape * const me, int16_t x, int16_t y)
{
    // Shape 类的虚表
    static struct ShapeVtbl const vtbl = 
    {
        &Shape_area_,
        &Shape_draw_
    };

    me->vptr = &vtbl;
    me->x = x;
    me->y = y;
}

void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy)
{
    me->x += dx;
    me->y += dy;
}

int16_t Shape_getX(const Shape * const me)
{
    return me->x;
}

int16_t Shape_getY(const Shape * const me)
{
    return me->y;
}

// Shape 类的虚函数实现
static uint32_t Shape_area_(const Shape * const me)
{
    assert(0);  //类似纯虚函数
    return 0U; //避免警告
}

static void Shape_draw_(const Shape * const me)
{
    assert(0); // 纯虚函数不能被调用
}

const Shape * largestShape(const Shape * shapes[], uint32_t nShapes)
{
    const Shape * s = (Shape *) 0;
    uint32_t max = 0U;
    uint32_t i;
    for (i = 0U; i < nShapes; ++i)
    {
        uint32_t area = Shape_area(shapes[i]);
        if (area > max)
        {
            max = area;
            s = shapes[i];
        }
    }
    return s;
}

void drawAllShapes(const Shape * shapes[], uint32_t nShapes)
{
    uint32_t i;
    for (i = 0U; i < nShapes; ++i)
        Shape_draw(shapes[i]); //虚函数调用
}

// Rectangle's 虚函数
static uint32_t Rectangle_area_(const Shape * const me);
static void Rectangle_draw_(const Shape * const me);

// 构造函数
void Rectangle_ctor(Rectangle * const me, int16_t x, int16_t y,
                    uint16_t width, uint16_t height)
{
    static struct ShapeVtbl const vtbl = 
    {
        &Rectangle_area_,
        &Rectangle_draw_
    };
    Shape_ctor(&me->super, x, y);
    me->super.vptr = &vtbl;
    me->width = width;
    me->height = height;
}

// Rectangle's 虚函数实现
static uint32_t Rectangle_area_(const Shape * const me)
{
    const Rectangle * const me_ = (const Rectangle *)me; //显示的转换
    return (uint32_t)me_->width * (uint32_t)me_->height; 
}

static void Rectangle_draw_(const Shape * const me)
{
    const Rectangle * const me_ = (const Rectangle *)me; //显示的转换
    printf("Rectangle_draw_(x = %d, y = %d, width = %d, height = %d)\n",
            Shape_getX(me), Shape_getY(me), me_->width, me_->height); 
}

// Circle's 虚函数
static uint32_t Circle_area_(const Shape * const me);
static void Circle_draw_(const Shape * const me);

// 构造函数
void Circle_ctor(Circle * const me, int16_t x, int16_t y, uint16_t radius)
{
    static struct ShapeVtbl const vtbl =
    {
        &Circle_area_,
        &Circle_draw_
    };

    Shape_ctor(&me->super, x, y);
    me->super.vptr = &vtbl;
    me->radius = radius;    
}

// Circle's 的虚函数实现
static uint32_t Circle_area_(const Shape * const me)
{
    const Circle * const me_ = (const Circle *) me;
    return (uint32_t) (3.14 * (uint32_t)me_->radius * (uint32_t)me_->radius);
}

static void Circle_draw_(const Shape * const me)
{
    const Circle * const me_ = (const Circle *)me;
    printf("Circle_draw_(x = %d, y = %d, radius = %d)\n",
            Shape_getX(me), Shape_getY(me), me_->radius);
}