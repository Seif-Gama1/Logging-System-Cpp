File: logging/inc/SomeIPTelemetrySrcImpl.hpp

Purpose
- SOME/IP client wrapper that builds a CommonAPI proxy for the generated GPU telemetry interface and provides cached access + event callback support.

Public API
- class SomeIPTelemetrySourceImpl
  - static SomeIPTelemetrySourceImpl& getInstance()
  - float getLoadPercentage()
  - void subscribeToEvents()
  - void setEventCallback(std::function<void(float)> cb)

Key behavior
- Singleton (`getInstance`) that builds a CommonAPI proxy via runtime->buildProxy for `omnimetron.gpu.GpuUsageData`.
- Maintains a `latestLoad` cache and `dataMutex` for thread safety.
- Subscribes to broadcast events and calls an optional `eventCallback` when new values arrive.
- `fetchFromRpc()` triggers an asynchronous RPC (`requestGpuUsageDataAsync`) and returns immediately — the reply updates the cache in the callback.

Notes
- Building the proxy may fail until the service is offered; the constructor spawns a retry thread to build the proxy and subscribes once available.
- Avoids synchronous RPC on internal CommonAPI threads to prevent dispatch starvation.

Related files
- src-gen generated proxy/stub headers
- logging/src/SomeIPTelemetrySrcImpl.cpp
