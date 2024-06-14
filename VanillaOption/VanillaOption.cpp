#include "VanillaOption.hpp"
#include <cmath>
#include <random>

// Initialize member data
void VanillaOption::init()
{
    K = 100.0;
    r = 0.05;    // 5% interest rate
    T = 1.0;     // One year until maturity
    S = 100.0;   // Option is "at the money"
    sigma = 0.2; // Volatility is 20%
}

// Copy member data
void VanillaOption::copy(const VanillaOption &rhs)
{
    K = rhs.getK();
    r = rhs.getr();
    T = rhs.getT();
    S = rhs.getS();
    sigma = rhs.getsigma();
}

// Default constructor
VanillaOption::VanillaOption()
{
    init();
}

// Parametrized constructor
VanillaOption::VanillaOption(const double &_K, const double &_r,
                             const double &_T, const double &_S,
                             const double &_sigma)
    : K(_K), r(_r), T(_T), S(_S), sigma(_sigma) {}

// Copy constructor
VanillaOption::VanillaOption(const VanillaOption &rhs)
{
    copy(rhs);
}

// Assignment operator
VanillaOption &VanillaOption::operator=(const VanillaOption &rhs)
{
    if (this == &rhs)
        return *this;
    copy(rhs);
    return *this;
}

// Destructor
VanillaOption::~VanillaOption() {}

// Getters
double VanillaOption::getK() const { return K; }
double VanillaOption::getr() const { return r; }
double VanillaOption::getT() const { return T; }
double VanillaOption::getS() const { return S; }
double VanillaOption::getsigma() const { return sigma; }

/**
 * Calculates the cumulative distribution function (CDF) of the standard normal distribution.
 *
 * @param value The value at which to calculate the CDF.
 * @return The CDF value at the given value.
 */
double normalCDF(double value)
{
    return 0.5 * std::erfc(-value * M_SQRT1_2);
}

/**
 * Calculates the price of a call option using the Black-Scholes formula.
 *
 * @return The price of the call option.
 */
double VanillaOption::calc_call_price() const
{
    double sigma_sqrt_T = sigma * sqrt(T);
    double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
    double d_2 = d_1 - sigma_sqrt_T;
    double result = S * normalCDF(d_1) - K * exp(-r * T) * normalCDF(d_2);
    return result;
}

double VanillaOption::calc_put_price() const
{
    double sigma_sqrt_T = sigma * sqrt(T);
    double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
    double d_2 = d_1 - sigma_sqrt_T;
    return K * exp(-r * T) * normalCDF(-d_2) - S * normalCDF(-d_1);
}
