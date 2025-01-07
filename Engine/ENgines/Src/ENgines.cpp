#include "Precompiled.h"
#include "ENgines.h"

ENgines::App& ENgines::MainApp() 
{
    static ENgines::App sApp;
    return sApp;
}