#include "InternalAPIModule.hpp"

#include "v1.send.hpp"

#include <iostream>

InternalAPIModule::InternalAPIModule(nlohmann::json config) : Module(config) {
    _name = "Internal API";
}

void InternalAPIModule::init() {
    _loadedRequests.push_back(new InternalAPI::v1::SendRequest());

    _loadedRequests[0]->request_url = _config["url"].get<std::string>().c_str();

    webserver ws = create_webserver()
        .port(_config["port"].get<int>())
        .max_threads(4)
        .memory_limit(256 * 1024)
        .debug()
        // .file_upload_target(FILE_UPLOAD_MEMORY_AND_DISK)
    ;

    std::cout << "[MOD Internal API] loading webserver at port 8080" << std::endl;

    for (auto request : _loadedRequests) {
        std::cout << "[MOD Internal API] registering " << request->request_url << std::endl;
        ws.register_resource(request->request_url, reinterpret_cast<http_resource *>(request));
    }

    ws.start(false);

    std::cout << "[MOD Internal API] loading complete" << std::endl;
}