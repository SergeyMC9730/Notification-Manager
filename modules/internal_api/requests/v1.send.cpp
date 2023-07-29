#include "v1.send.hpp"

InternalAPI::v1::SendRequest::SendRequest() {
    this->request_name = "send notification";
    this->request_url = "/api/v1/send";
}

std::shared_ptr<http_response> InternalAPI::v1::SendRequest::render(const http_request &req) {
    auto a = req.get_arg("mykey");

    return generateResponse(a.get_flat_value());
}