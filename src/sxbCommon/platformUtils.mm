
#import <UIKit/UIKit.h>

#include "sxbCommon/platformUtils.h"

SXB_NAMESPACE_BEGIN

std::string PlatformUtils::s_runtimeDirectory = "../../../runtime";

const std::string & PlatformUtils::getRuntimeDirectory()
{
#if defined(SXB_SYSTEM_IOS)
    NSString * bundlePath = [[ NSBundle mainBundle] pathForResource: @ "runtimes" ofType :@ "bundle"];
    if (bundlePath)
    {
        s_runtimeDirectory = [bundlePath UTF8String];
    }
    
#endif
    return s_runtimeDirectory;
}

SXB_NAMESPACE_END
