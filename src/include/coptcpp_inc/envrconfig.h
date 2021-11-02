#pragma once
#include "coptcpp.idl.h"
#include "exception.h"

// This client implemented class showing how to wrapper EnvrConfig class from copt cpp dll
class EnvrConfig
{
public:
    EnvrConfig() : m_envrConfig(CreateEnvrConfig()) { CHECKERROR(m_envrConfig); }
    EnvrConfig(Copt::IEnvrConfig *envConfig) : m_envrConfig(envConfig) {}

    void Set(const char *szName, const char *szValue)
    {
        m_envrConfig->Set(szName, szValue);
        CHECKERROR(m_envrConfig);
    }

    Copt::IEnvrConfig *Get() const { return &(*m_envrConfig); }
private:
    std::shared_ptr<Copt::IEnvrConfig> m_envrConfig;
};
