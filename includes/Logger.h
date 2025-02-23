#ifndef _LOGGER_H_DEFINED
#define _LOGGER_H_DEFINED

#include <stdio.h>

namespace doengine
{

enum class logger_type{
   Information,
   Warning,
   Error
};


void LogOuput(const logger_type& type,const char *msg, ...);

}


#endif