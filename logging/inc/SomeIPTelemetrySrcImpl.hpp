#pragma once
#include <memory>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
#include "CommonAPI/CommonAPI.hpp"
#include <v1/omnimetron/gpu/GpuUsageDataProxy.hpp>

class SomeIPTelemetrySourceImpl {    
    private:
        std::shared_ptr<CommonAPI::Runtime> runtime;
        std::shared_ptr<v1::omnimetron::gpu::GpuUsageDataProxy<>> proxy;
        std::mutex dataMutex;
    // start with a negative value to indicate "no data yet" so
    // the first call will try an RPC fetch instead of returning 0.0
    // which could be a valid load.
    float latestLoad {-1.0f};
    // Optional callback invoked when a new GPU load event arrives.
    std::function<void(float)> eventCallback;

        SomeIPTelemetrySourceImpl();
        ~SomeIPTelemetrySourceImpl();

        SomeIPTelemetrySourceImpl(const SomeIPTelemetrySourceImpl&) = delete;
        SomeIPTelemetrySourceImpl& operator=(const SomeIPTelemetrySourceImpl&) = delete;

        float fetchFromRpc();
        void updateCache(float value);

    public:
        static SomeIPTelemetrySourceImpl& getInstance();
        float getLoadPercentage();
        void subscribeToEvents();
    void setEventCallback(std::function<void(float)> cb) { eventCallback = std::move(cb); }
};