#include "hnpch.h"

#include "Hina.h"

class PBR : public Hina::Application
{
public:
    PBR() {

    }

    ~PBR() {

    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
