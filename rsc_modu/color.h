#ifndef COLOR_H
#define COLOR_H
#include <QtCore>

typedef struct stColorCfg_
{
    enum{G_COLOR_WHITE,
         G_COLOR_GREEN,
         G_COLOR_RED,
         G_COLOR_BLUE,
         G_COLOR_YELLOW,
         G_COLOR_PINK,
         G_COLOR_SKYBLUE,
         G_COLOR_ORANGE,
         G_COLOR_PURPLE,
         G_COLOR_GRAY
    } m_color;
} stColorCfg;
typedef enum EnumGlbColor_
{
             GLB_COLOR_WHITE,
             GLB_COLOR_GREEN,
             GLB_COLOR_RED,
             GLB_COLOR_BLUE,
             GLB_COLOR_YELLOW,
             GLB_COLOR_PINK,
             GLB_COLOR_SKYBLUE,
             GLB_COLOR_ORANGE,
             GLB_COLOR_PURPLE,
             GLB_COLOR_GRAY
}EnumGlbColor;

extern QColor g_Color[10] ;
extern QString g_ColorName[10];
#define GLB_COLOR(x) (((x>=0)&&(x<10))?g_Color[x]:(g_Color[1]))
#endif // COLOR_H
