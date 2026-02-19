#pragma once

#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <iostream>
#include <chrono>

#include "v1/omnimetron/gpu/GpuUsageDataStubDefault.hpp"
#include "CommonAPI/CommonAPI.hpp"

class GpuTelemetryServer : public v1::omnimetron::gpu::GpuUsageDataStubDefault{
    private:
        float currentLoad_;
        std::mutex loadMutex_;
        std::default_random_engine rng_;
        std::uniform_real_distribution<float> dist_;

    public:
        GpuTelemetryServer();
        ~GpuTelemetryServer() override;

        void requestGpuUsageData(
            const std::shared_ptr<CommonAPI::ClientId>& _client,
            requestGpuUsageDataReply_t _reply
        );

        void updateLoad(float newLoad);
        void startSimulatedLoadLoop();
};
