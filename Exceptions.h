#pragma once

#include "stdafx.h"
#include <exception>

using namespace std;

class notImplementedException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Not Implemented Exception Thrown!";
	}
};

class argumentException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Argument Exception Thrown!";
	}
};

class indexRangeException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Index Out of Bounds Exception Thrown!";
	}
};

class programmingErrorException : public exception
{
public:

	virtual const char* what() const throw()
	{
		return "Programming Error in an Assumption!";
	}
};

class memoryAllocationException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Memory Allocation Exception Thrown!";
	}
};