#include "DataLogger.hpp"

int main(){
    AppConfig cfg;
    cfg.enableCpu = true;
    cfg.enableRam = true;
    cfg.enableGpu = true;
    cfg.enableConsoleSink = true;
    cfg.enableFileSink = true;
    cfg.parseRateMs = 1;
    cfg.logDelayMs = 0;
    cfg.numWorkers = 3;
    cfg.gpuWorkers = 2;

    DataLogger app(cfg, "data.txt");
    app.start();

    return 0;
}
