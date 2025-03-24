#include <iostream>
#include <iomanip>
#include <cmath>

struct Capacitor {
    double *time;
    double *voltage;
    double *current;
    double C;
    int num_steps;
    
    Capacitor(double capacitance, int steps) {
        C = capacitance;
        num_steps = steps;
        time = new double[num_steps];
        voltage = new double[num_steps];
        current = new double[num_steps];
    }
    
    ~Capacitor() {
        delete[] time;
        delete[] voltage;
        delete[] current;
    }
};

void simulateConstantCurrent(Capacitor &cap, double I, double dt) {
    cap.voltage[0] = 0.0;
    for (int t = 1; t < cap.num_steps; ++t) {
        cap.time[t] = t * dt;
        cap.voltage[t] = cap.voltage[t - 1] + (I * dt / cap.C);
        cap.current[t] = I;
        if (t % 200 == 0)
            std::cout << "t: " << cap.time[t] << " V: " << cap.voltage[t] << " I: " << cap.current[t] << "\n";
    }
}

void simulateConstantVoltage(Capacitor &cap, double V0, double R, double dt) {
    cap.current[0] = V0 / R;
    for (int t = 1; t < cap.num_steps; ++t) {
        cap.time[t] = t * dt;
        cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] * dt / (R * cap.C));
        cap.voltage[t] = V0 - cap.current[t] * R;
        if (t % 200 == 0)
            std::cout << "t: " << cap.time[t] << " V: " << cap.voltage[t] << " I: " << cap.current[t] << "\n";
    }
}

int main() {
    const double dt = 1e-10;
    const double final_time = 5e-6;
    const int num_steps = static_cast<int>(final_time / dt);
    const double R = 1e3;
    const double C = 100e-12;
    const double I = 1e-2;
    const double V0 = 10.0;
    
    std::cout << "Simulating Constant Current Source:\n";
    Capacitor cap1(C, num_steps);
    simulateConstantCurrent(cap1, I, dt);
    
    std::cout << "\nSimulating Constant Voltage Source:\n";
    Capacitor cap2(C, num_steps);
    simulateConstantVoltage(cap2, V0, R, dt);
    
    return 0;
}