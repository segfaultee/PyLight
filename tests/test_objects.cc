#include <iostream>
#include <format>

#include <pylight/python.hh>

int main()
{
    python::init();

    auto list = python::List::create(0).get();
    auto dict = python::Dict::create().get();
}