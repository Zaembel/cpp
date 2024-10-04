#pragma once
#include "Bill.h"
#include "Str.h"

class BillAdapter {
public:
	static Bill* getBill(Str data);
};

