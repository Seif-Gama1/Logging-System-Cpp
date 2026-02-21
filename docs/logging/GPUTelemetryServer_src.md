File: logging/src/GPUTelemetryServer.cpp

Purpose
- Implementation of the `GpuTelemetryServer` test service. Contains a `main()` that can run a standalone telemetry server for local testing.

Highlights
- `startSimulatedLoadLoop()` spawns a detached thread that periodically generates random load values and calls `updateLoad`.
- `updateLoad` stores the new value and fires the broadcast event via the generated adapter.
- `main()` registers the service with CommonAPI runtime and runs an infinite loop.

Notes
- Useful for running a local emitter that the client code subscribes to. Not part of the app executable in normal builds unless invoked separately.
