#pragma once

#include "../../simple_module/Module.hpp"

#include "APIRequest.hpp"

#include <vector>

class InternalAPIModule : public Module {
public:
    InternalAPIModule(nlohmann::json config);

    std::vector<APIRequest *> _loadedRequests;

    InternalAPIModule();

    void init() override;
};