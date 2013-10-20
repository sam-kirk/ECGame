#include "Graphics.h"

/*** Bitmap ***/

Bitmap::Bitmap(uint width, uint height)
{
    this->width = width;
    this->height = height;
    this->pixels = (void*)(new int[width * height]);
    this->create_graphics()->clear(0);
}

Bitmap::Bitmap(uint width, uint height, void* pixels)
{
    this->width = width;
    this->height = height;
    this->pixels = pixels;
}

Bitmap::~Bitmap(void)
{
    delete graphics;
}

void* Bitmap::get_pixels(void)
{
    return pixels;
}

Graphics* Bitmap::create_graphics()
{
    if (graphics != NULL)
        delete graphics;
    graphics = new Graphics(this);
    return graphics;
}

/*** Graphics ***/

Graphics::Graphics(Bitmap* b) 
{
    bitmap = b;
}

void Graphics::set_pixel(int x, int y, byte r, byte g, byte b)
{
    int* p = (int*)(bitmap->get_pixels()) + x + y * bitmap->width;
    *p = RGBINT(r, g, b);
}

void Graphics::set_pixel(int x, int y, int c)
{
    if (x < 0 | y < 0 | x >= bitmap->width | y >= bitmap->height)
        return;
    set_pixel(x, y, INTRGB(c));
}

int Graphics::get_pixel(int x, int y)
{
    return (int)((int*)(bitmap->get_pixels()))[x + y * bitmap->width];
}

void Graphics::clear(int c)
{
    for (int i = 0; i < bitmap->width * bitmap->height; i++) {
        int* p = (int*)(bitmap->get_pixels()) + i;
        *p = c;
    }
}
    
void Graphics::draw_rectangle(int x, int y, int w, int h, int c, int t)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            if (yy < t | yy >= h - t | xx < t | xx >= w - t)
                set_pixel(x + xx, y + yy, c);
}

void Graphics::fill_rectangle(int x, int y, int w, int h, int c)
{
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++)
            set_pixel(x + xx, y + yy, c);
}

void Graphics::draw_circle(int x, int y, int r, int c)
{
    for (double d = 0.0; d < PI * 2.0; d += PI / 180.0)
        set_pixel(x + r + sin(d) * r, y + r + cos(d) * r, c);
}

void Graphics::fill_circle(int x, int y, int r, int c)
{
    for (int yy = -r; yy < r; yy++)
        for (int xx = -r; xx < r; xx++)
            if (yy * yy + xx * xx < r * r)
                set_pixel(x + r + xx, y + r + yy, c);
}

void Graphics::draw_line(int x0, int y0, int x1, int y1, int c)
{
    int dx = abs(x1 - x0),
        dy = abs(y1 - y0),
        sx = x0 < x1 ? 1 : -1,
        sy = y0 < y1 ? 1 : -1,
        err = dx - dy;
    while (true) {
        set_pixel(x0, y0, c);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err << 1;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (x0 == x1 && y0 == y1) {
            set_pixel(x0, y0, c);
            break;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void Graphics::draw_bitmap(int x, int y, Bitmap* b)
{
    for (int yy = 0; yy < b->height; yy++)
        for (int xx = 0; xx < b->width; xx++) {
            int* p = (int*)(b->get_pixels()) + xx + yy * b->width;
            set_pixel(x + xx, y + yy, *p);
        }
}