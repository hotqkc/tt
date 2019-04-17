
#include "sxbCommon/platformUtils.h"

SXB_NAMESPACE_BEGIN

std::string PlatformUtils::s_runtimeDirectory = "../../../runtime";

const std::string & PlatformUtils::getRuntimeDirectory()
{
    return s_runtimeDirectory;
}

SXB_NAMESPACE_END
