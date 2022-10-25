#pragma once
#ifndef _BUSYBIN_RUBIKS_CUBE_EXCEPTION_H_
#define _BUSYBIN_RUBIKS_CUBE_EXCEPTION_H_

#include <exception>
using std::exception;
#include <string>
using std::string;

namespace rubiks
{
    class RubiksCubeException : public exception
    {
        string msg;

        RubiksCubeException();
    public:
        RubiksCubeException(const char* const what);
        RubiksCubeException(const string& what);
        virtual const char* what() const throw();
        virtual ~RubiksCubeException() throw();
    };
}



class RubiksCubeException
{
};
#endif