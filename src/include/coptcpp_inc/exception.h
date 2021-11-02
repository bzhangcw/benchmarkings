#pragma once
#include <string>
#include <stdexcept>

#define CHECKERROR(ptr)                                                   \
    if (ptr->GetLastError() != 0)                                         \
    {                                                                     \
        throw CoptException(ptr->GetLastError(), ptr->GetErrorMessage()); \
    }

class CoptException : public std::runtime_error
{
public:
    CoptException(int err, const char *szMsg)
        : runtime_error(szMsg),
          m_errCode(err)
    {
    }

    inline int GetCode() const { return m_errCode; }

private:
    int m_errCode;
};