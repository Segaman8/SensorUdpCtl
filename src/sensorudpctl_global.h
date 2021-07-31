#ifndef SENSORUDPCTL_GLOBAL_H
#define SENSORUDPCTL_GLOBAL_H

#if defined(_MSC_VER)
#  define EXPORT extern "C" __declspec(dllexport)
#elif defined(__GNUC__)
#  define SENSORUDPCTL_EXPORT extern "C" __attribute__((visibility("default")))
#else
//  do nothing and hope for the best?
#  define SENSORUDPCTL_EXPORT
#  pragma warning Unknown dynamic link import/export semantics.
#endif


#endif // SENSORUDPCTL_GLOBAL_H
