#include <fstream>

#include "trase.hpp"

int main()
{

    // create figure and axis
    auto fig = trase::figure();
    auto ax = fig->axis();

    // set x steps, logistic parameter and create x and y vectors
    const int n = 100;
    const float dx = 12.f / static_cast<float>(n);
    const float k = 1.f;
    auto logistic = [k](const float x) {
        return 1.f / (1.f + std::exp(-k * x));
    };
    std::vector<float> x = {-6};
    std::vector<float> y = {logistic(x.back())};

    // create the initial dataset and then plot it using a line geometry
    auto data = trase::create_data().x(x).y(y);
    auto plt = ax->line(data);

    // loop through rest of the points, generating a new frame for every point
    for (int i = 1; i < n; ++i)
    {
        x.push_back(x.back() + dx);
        y.push_back(logistic(x.back()));
        auto data = trase::create_data().x(x).y(y);
        plt->add_frame(data, (x.back() - x[0]) / 4.f);
    }

    // label axis
    ax->xlabel("x");
    ax->ylabel("y");

    // output to chosen backend
    trase::BackendGL backend;
    fig->show(backend);
}
/// [animated line example]
