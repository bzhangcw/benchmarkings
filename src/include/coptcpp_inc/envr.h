#pragma once
#include "coptcpp.idl.h"
#include "envrconfig.h"
#include "model.h"

// This client implemented class showing how to wrapper envr class from copt cpp dll
class Envr
{
public:
    Envr() : m_env(CreateEnvr()) { CHECKERROR(m_env); }
    Envr(const char *szLicDir) : m_env(CreateEnvrWithPath(szLicDir)) { CHECKERROR(m_env); }
    Envr(const EnvrConfig &config) : m_env(CreateEnvrWithConfig(config.Get())) { CHECKERROR(m_env); }
    Envr(Copt::IEnvr *env) : m_env(env) {}

    Model CreateModel(const char *szName)
    {
        Model model = m_env->CreateModel(szName);
        CHECKERROR(m_env);
        return model;
    }

    void Close() { m_env->Close(); }

private:
    std::shared_ptr<Copt::IEnvr> m_env;
};
