#pragma once
#include <string>
#include <iostream>
using namespace std;

class Str : public string {
public:
    using string::basic_string;

    Str* split(const char);
};


