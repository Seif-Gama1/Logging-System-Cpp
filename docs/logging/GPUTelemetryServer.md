File: logging/inc/GPUTelemetryServer.hpp

Purpose
- Stubs a CommonAPI SOME/IP service that provides GPU usage telemetry for testing and local simulation.

Public API / classes
- class GpuTelemetryServer : public v1::omnimetron::gpu::GpuUsageDataStubDefault
  - GpuTelemetryServer()
  - ~GpuTelemetryServer() override
  - void requestGpuUsageData(const std::shared_ptr<CommonAPI::ClientId>&, requestGpuUsageDataReply_t _reply)
  - void updateLoad(float newLoad)
  - void startSimulatedLoadLoop()

Key behavior
- Maintains a currentLoad_ protected by a mutex.
- `requestGpuUsageData` replies with the current load (synchronous reply).
- `updateLoad` updates the cached value and fires the generated notify event via the generated stub adapter's helper.
- `startSimulatedLoadLoop` spawns a detached thread that updates the load periodically (used in the included `main()` inside `GPUTelemetryServer.cpp`).

Notes
- This file depends on generated CommonAPI headers (src-gen) and CommonAPI runtime.
- The public `main()` in `GPUTelemetryServer.cpp` registers the service and runs a simulation loop for local testing.

Related files
- src-gen generated CommonAPI headers (GpuUsageDataSomeIPStubAdapter)
- logging/src/GPUTelemetryServer.cpp
