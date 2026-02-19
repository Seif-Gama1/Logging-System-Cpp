#include "GPUTelemetryServer.hpp"


GpuTelemetryServer::GpuTelemetryServer()
    : currentLoad_(0.0f),
      dist_(0.0f, 100.0f) {

    std::cout << "GpuTelemetryServer initialized" << std::endl;
}

GpuTelemetryServer::~GpuTelemetryServer() {
    std::cout << "GpuTelemetryServer destroyed" << std::endl;
}

void GpuTelemetryServer::requestGpuUsageData(
    const std::shared_ptr<CommonAPI::ClientId>&,
    requestGpuUsageDataReply_t _reply) {

    float loadCopy;
    {
        std::lock_guard<std::mutex> lock(loadMutex_);
        loadCopy = currentLoad_;
    }

    _reply(loadCopy);
}

void GpuTelemetryServer::updateLoad(float newLoad) {
    {
        std::lock_guard<std::mutex> lock(loadMutex_);
        currentLoad_ = newLoad;
    }

    fireNotifyGpuUsageDataChangeEvent(newLoad);
    // std::cout<<"Fired the event"<<std::endl;
}

void GpuTelemetryServer::startSimulatedLoadLoop() {
    std::thread([this]() {
        while (true) {
            float newLoad = dist_(rng_);
            updateLoad(newLoad);
            std::cout<<"Updated load with val "<<newLoad<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }).detach();
}

int main(){
    auto runtime = CommonAPI::Runtime::get();
    auto server = std::make_shared<GpuTelemetryServer>();

    bool success = runtime->registerService(
        "local",
        "omnimetron.gpu.GpuUsageData",
        server
    );

    if (!success){
        std::cerr << "Failed to register GpuUsageData service" << std::endl;
        return 1;
    }

    server->startSimulatedLoadLoop();

    std::cout << "GPU telemetry server running..." << std::endl;

    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
