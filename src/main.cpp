#include "../include/timer.hpp"
#include <string>
#include <iostream>

void eksdi()
{
}

int main()
{
	auto t{ Timer<void>(eksdi) };
	t.run();
}