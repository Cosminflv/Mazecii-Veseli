#include "TestClass.h"

TestClass::TestClass(int value) : m_tempVariable(value)
{
}

int TestClass::GetValue()
{
	return m_tempVariable;
}
