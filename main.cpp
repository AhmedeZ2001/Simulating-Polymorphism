#include <iostream>
#define PI 3.14159265358979323846
using namespace std;
//Base Class(Shape)
struct ShapeVirtualTable;
struct Shape
{
    ShapeVirtualTable* vtable;
} ;
struct ShapeVirtualTable
{
    double (*GetArea)(Shape *obj);
    void (*PrintInfo)(Shape *obj);
};
double GetArea(Shape* obj)
{
    return obj->vtable->GetArea(obj);
}
void PrintInfo(Shape* obj)
{
    obj->vtable->PrintInfo(obj);
}
//First Shape (Circle)
struct Circle
{
    Shape parent;
    double Radius;
};
double CircleArea(Circle* obj)
{
    return PI* obj->Radius * obj->Radius;
}
void CirclePrintInfo(Circle* obj)
{
    cout<<"Circle Radius : "<<obj->Radius<<endl<<
    "======================================================="<<endl;
}
ShapeVirtualTable CircleVirtualTable=
{
    (double(*)(Shape*)) CircleArea,
    (void(*)(Shape*)) CirclePrintInfo

};
void CircleInitialize(Circle* obj,int n)
{
    obj->parent.vtable=&CircleVirtualTable;
    obj->Radius=n;
}
//End of Circle
//Second Shape (Rectangle)
struct Rectangle
{
    Shape parent;
    double length,width;
};
double RectangleArea(Rectangle* obj)
{
    return obj->length * obj->width;
}
void RectanglePrintInfo(Rectangle* obj)
{
    cout<<"Rectangle Length : "<<obj->length<<endl
        <<"Rectangle Width : " <<obj->width<<endl<<
        "======================================================="<<endl;
}
ShapeVirtualTable RectangleVirtualTable=
{
    (double(*)(Shape*)) RectangleArea,
    (void(*)(Shape*)) RectanglePrintInfo

};
void RectangleInitialize(Rectangle* obj,int len,int wid)
{
    obj->parent.vtable=&RectangleVirtualTable;
    obj->length=len;
    obj->width=wid;
}
//End of Rectangle
//Third Shape Ellipse
struct Ellipse
{
    Shape parent;
    double Radius1,Radius2;
};
double EllipseArea(Ellipse* obj)
{
    return PI * obj->Radius1 * obj->Radius2;
}
void EllipsePrintInfo(Ellipse* obj)
{
    cout<<"Ellipse Radius 1 : "<<obj->Radius1<<endl
        <<"Ellipse Radius 2 : "<<obj->Radius2<<endl<<
        "======================================================="<<endl;
}
ShapeVirtualTable EllipseVirtualTable=
{
    (double(*)(Shape*)) EllipseArea,
    (void(*)(Shape*)) EllipsePrintInfo

};
void EllipseInitialize(Ellipse* obj,int r1,int r2)
{
    obj->parent.vtable=&EllipseVirtualTable;
    obj->Radius1=r1;
    obj->Radius2=r2;
}
//End of Ellipse
int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;
    double total_area=0;
    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct
    return 0;
}

