#pragma once
#include "coptcpp.idl.h"

// This client implemented class showing how to wrapper ProbBuffer class from copt cpp dll
class ProbBuffer
{
public:
    ProbBuffer(int sz) : m_buffer(CreateProbBuffer(sz)) {}
    ProbBuffer(Copt::IProbBuffer *ptr) : m_buffer(ptr) {}

    char *GetData() { return m_buffer->GetData(); }
    int Size() const { return m_buffer->Size(); }
    void Resize(int sz) { m_buffer->Resize(sz); }

private:
    std::shared_ptr<Copt::IProbBuffer> m_buffer;
};
