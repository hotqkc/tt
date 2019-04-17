
#ifndef PLATFORMUTILS_H_030EAA738C5ADE7CAD57BC3362595D23
#define PLATFORMUTILS_H_030EAA738C5ADE7CAD57BC3362595D23

#include <string>

#include "sxbCommon/defines.h"

SXB_NAMESPACE_BEGIN

class PlatformUtils
{
public:
    static const std::string & getRuntimeDirectory();
    
    static bool getMem(double &residentMem_, double &virtualMem_);

private:
	PlatformUtils() {}
	~PlatformUtils() {}
    
private:
    static std::string s_runtimeDirectory;
};

SXB_NAMESPACE_END

#endif // PLATFORMUTILS_H_030EAA738C5ADE7CAD57BC3362595D23
