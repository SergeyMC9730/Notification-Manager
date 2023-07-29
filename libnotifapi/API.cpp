#include "API.hpp"

#ifdef _MODULE_INTERNALAPI_
#include "InternalAPIModule.hpp"
#endif

using namespace NotificationAPI;

void API::init() {
    #ifdef _MODULE_INTERNALAPI_
    nlohmann::json j;

    _modules.push_back(new InternalAPIModule(j));
    #endif

    for (auto mod : _modules) {
        mod->init();
    }

    return;
}