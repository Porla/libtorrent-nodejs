#ifndef READRESUMEDATA_H
#define READRESUMEDATA_H

#include <nan.h>

namespace lt
{
    class ReadResumeData
    {
    public:
        static NAN_MODULE_INIT(Init);

    private:
        static NAN_METHOD(DoReadResumeData);
    };
}

#endif
