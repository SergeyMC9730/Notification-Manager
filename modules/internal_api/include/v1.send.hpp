#pragma once

#include "APIRequest.hpp"

#include <memory>

using namespace httpserver;

namespace InternalAPI {
    namespace v1 {
        class SendRequest : public APIRequest {
        public:
            std::shared_ptr<http_response> render(const http_request&);

            SendRequest();
        };
    }
}