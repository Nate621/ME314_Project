#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

int main() {
    double T_inf = 20.0;     // Room Temperature (°C)
    double T0 = 37.0;        // Assumed Initial Body Temp (°C)
    double h = 8.0;          // Heat transfer coefficient (W/m^2·°C)

    double r = 0.15;         // Radius (m)
    double L = 1.70;         // Length (m)

    double Vol = M_PI * r * r * L;
    double Area = 2 * M_PI * r * L + 2 * M_PI * r * r;

    double density = 671.912;     // kg/m^3
    double c = 2980;       // J/kg·°C
    double k = (h * Area) / (density * c * Vol);
    double dt = 10.0;              // time step (seconds)
    double t_max = 15 * 3600.0;    // 15 hours

    vector<double> time;
    vector<double> temp;

    double T = T0;

    for (double t = 0; t <= t_max; t += dt) {
        time.push_back(t / 3600.0); // convert to hours
        temp.push_back(T);

        double dTdt = -k * (T - T_inf);
        T = T + dt * dTdt;
    }

    auto fig = figure(true);
    auto p = plot(time, temp);
    p->line_width(3);
    p->line_style("-");
    xlabel("Time (hours)");
    ylabel("Temperature (°C)");
    title("Body Cooling Curve (Newton's Law of Cooling)");
    xlim({0, 15});
    ylim({10, 40});

    grid(on);

    show();

    return 0;
}