#ifndef functiontypes_hpp
#define functiontypes_hpp
#include<functional>
namespace graf
{
    using namespace std;

    using RenderFunction = function<void()>;

    using KeyboardFunction = function<void(int,int,int)>;
    using MouseFunction = function<void(double xpos,double ypos)>;
}

#endif