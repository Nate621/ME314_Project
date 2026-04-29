#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <matplot/matplot.h>

int main() {

    double T_inf = 20.0;
    double T0 = 37.0;
    double T_target = 25.0;

    double h = 8.0;
    double r = 0.15;
    double L = 1.70;

    // I calculated density of "person" based on cylinder model volume, and 
    // found average mass of North American Adult (~ 80.7 Kg)
    double rho = 671.912;
    double c = 2980;

    double V = M_PI * r * r * L;
    double A = 2 * M_PI * r * L + 2 * M_PI * r * r;

    double t_target =
        ((rho * c * V) / (h * A)) *
        std::log((T0 - T_inf) / (T_target - T_inf));

    double t_target_hours = t_target / 3600.0;

    std::cout << "Time to reach 25C: " << t_target_hours << " hours" << std::endl;

    double k = (h * A) / (rho * c * V);

    std::vector<double> time;
    std::vector<double> temp;

    for (double t = 0; t <= 30 * 3600; t += 10) {
        time.push_back(t / 3600.0);
        double T = T_inf + (T0 - T_inf) * std::exp(-k * t);
        temp.push_back(T);
    }

    auto fig = matplot::figure(true);
    auto p = matplot::plot(time, temp);
    p->line_width(3);

    matplot::xlabel("Time (hours)");
    matplot::ylabel("Temperature (°C)");
    matplot::title("Cooling Curve (Matched to Desmos Model)");

    matplot::xlim({0, 30});
    matplot::ylim({18, 40});

    matplot::grid(matplot::on);
    matplot::hold(matplot::on);

    std::vector<double> xh = {0, 30};
    std::vector<double> yh = {T_target, T_target};
    matplot::plot(xh, yh, "--r");

    std::vector<double> xv = {t_target_hours, t_target_hours};
    std::vector<double> yv = {18, 40};
    matplot::plot(xv, yv, "--k");

    std::vector<double> xpt = {t_target_hours};
    std::vector<double> ypt = {T_target};

    auto s = matplot::scatter(xpt, ypt);
    s->marker_face(true);
    s->marker_color("black");
    s->marker_size(8);

    char buf[100];
    snprintf(buf, sizeof(buf), " (%.2f hr, 25 °C)", t_target_hours);
    matplot::text(t_target_hours, T_target, buf);

    std::vector<double> diameters;
    std::vector<double> times_to_target;

    for (double r_param = 0.05; r_param <= 0.30; r_param += 0.01) {

        double Vp = M_PI * r_param * r_param * L;
        double Ap = 2 * M_PI * r_param * L + 2 * M_PI * r_param * r_param;

        double t_param =
            ((rho * c * Vp) / (h * Ap)) *
            std::log((T0 - T_inf) / (T_target - T_inf));

        diameters.push_back(2.0 * r_param);
        times_to_target.push_back(t_param / 3600.0);
    }

    auto fig2 = matplot::figure(true);
    matplot::plot(diameters, times_to_target);
    matplot::xlabel("Diameter (m)");
    matplot::ylabel("Time to reach 25°C (hours)");
    matplot::title("Effect of Body Diameter on Estimated Time of Death");
    matplot::grid(matplot::on);

    matplot::show();

    return 0;
}