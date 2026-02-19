#include <iostream>
#include <thread>
#include <chrono>

#include "CommonAPI/CommonAPI.hpp"
#include "GPUTelemetryServer.hpp"
#include "SomeIPTelemetrySourceImpl.hpp"

int main() {

    auto runtime = CommonAPI::Runtime::get();
    auto server = std::make_shared<GpuTelemetryServer>();

    bool success = runtime->registerService(
        "local",
        "omnimetron.gpu.GpuUsageData",
        server
    );

    if (!success) {
        std::cerr << "Failed to register GpuUsageData service" << std::endl;
        return 1;
    }

    std::cout << "GPU telemetry service registered." << std::endl;

    // Access your SOME/IP telemetry source
    auto& telemetrySource = SomeIPTelemetrySourceImpl::getInstance();

    while (true) {
        float load = telemetrySource.getLoadPercentage();

        if (load >= 0.0f) {
            server->updateLoad(load);
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
