#pragma once

class VanillaOption
{
private:
    void init();
    void copy(const VanillaOption &rhs);

    double K;     // Strike price
    double r;     // Risk-free interest rate
    double T;     // Expiry | Maturity time
    double S;     // Underlying asset price
    double sigma; // Volatility of the underlying asset

public:
    VanillaOption(); // Default constructor
    VanillaOption(const double &_K, const double &_r,
                  const double &_T, const double &_S,
                  const double &_sigma);                // Parametrized constructor
    VanillaOption(const VanillaOption &rhs);            // Copy constructor
    VanillaOption &operator=(const VanillaOption &rhs); // Assignment operator
    virtual ~VanillaOption();                           // Destructor

    // Selector methods for the option parameters
    double getK() const;
    double getr() const;
    double getT() const;
    double getS() const;
    double getsigma() const;

    // Option price calculation methods
    double calc_call_price() const;
    double calc_put_price() const;
};