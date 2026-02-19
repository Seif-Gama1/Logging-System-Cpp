#include "SomeIPTelemetrySrcImpl.hpp"

/* someip client class */
SomeIPTelemetrySourceImpl& SomeIPTelemetrySourceImpl::getInstance(){
    static SomeIPTelemetrySourceImpl instance;
    return instance;
}

SomeIPTelemetrySourceImpl::SomeIPTelemetrySourceImpl(){
    runtime = CommonAPI::Runtime::get();

    proxy = runtime->buildProxy<v1::omnimetron::gpu::GpuUsageDataProxy>(
        "local", 
        // "my.company.service.GpuUsageData"
        "omnimetron.gpu.GpuUsageData"
    );

    if (!proxy) {
        std::thread([this]() {
            while (!proxy) {
                try {
                    proxy = runtime->buildProxy<v1::omnimetron::gpu::GpuUsageDataProxy>(
                        "local",
                        "omnimetron.gpu.GpuUsageData"
                    );
                } catch (...) {
                    proxy.reset();
                }

                if (!proxy) {
                    try {
                        proxy = runtime->buildProxy<v1::omnimetron::gpu::GpuUsageDataProxy>(
                            "local",
                            "omnimetron.gpu.GpuUsageData:v1_0"
                        );
                    } catch (...) {
                        proxy.reset();
                    }
                }

                if (!proxy) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }

            // Wait until the proxy reports availability before subscribing
            while (!proxy->isAvailable()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "I'm here 1" << std::endl;
                std::cout << "Proxy not yet available" << std::endl;
            }

            std::cout<<"before subscribing to the event"<<std::endl;
            subscribeToEvents();
            std::cout<<"subscribed to the event"<<std::endl;
        }).detach();
    } else {
        while (!proxy->isAvailable()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Proxy not yet available" << std::endl;
        }

        subscribeToEvents();
    }
}    

SomeIPTelemetrySourceImpl::~SomeIPTelemetrySourceImpl(){
    proxy.reset();
    runtime.reset();
}

void SomeIPTelemetrySourceImpl::updateCache(float value){
    std::lock_guard<std::mutex> lock(dataMutex);
    latestLoad = value;
}    

void SomeIPTelemetrySourceImpl::subscribeToEvents(){
    if (!proxy)
        return;
    
    std::cout<<"About to subscribe"<<std::endl;
    proxy->getNotifyGpuUsageDataChangeEvent().subscribe(
        [this](float load){
            updateCache(load);
            // std::cout<<"Event has been triggered .. load="<<load<<std::endl;
            // call cbf to log events
            if (eventCallback) {
                try {
                    eventCallback(load);
                } catch (...) {
                    
                }
            }
        }
    );
    std::cout<<"finished subscribe to event"<<std::endl;
}    

float SomeIPTelemetrySourceImpl::fetchFromRpc() {
    if (!proxy) return -1;

    // Trigger an asynchronous RPC and return immediately so we don't
    // block the CommonAPI/vsomeip internal threads that also dispatch
    // incoming events. The async callback will update the cache when
    // the reply arrives.
    proxy->requestGpuUsageDataAsync(
        [this](const CommonAPI::CallStatus &_status, const float &_usage) {
            if (_status == CommonAPI::CallStatus::SUCCESS) {
                updateCache(_usage);
                std::cout << "Async RPC reply received: " << _usage << std::endl;
            } else {
                std::cout << "Async RPC failed: " << static_cast<int>(_status) << std::endl;
            }
        },
        nullptr
    );

    // Caller should fall back to cached value (or -1 if none available).
    return -1;
}

float SomeIPTelemetrySourceImpl::getLoadPercentage(){
    {
        std::lock_guard<std::mutex> lock(dataMutex);
        if (latestLoad >= 0.0f)
            return latestLoad;
    }

    // Trigger async fetch but don't block waiting for it.
    (void)fetchFromRpc();
    return -1;
}