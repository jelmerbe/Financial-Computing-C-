//Copyright (c) Lajos Gergely Gyurko, 2023. All rights reserved.

#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/vec_ops.hpp"

using namespace vecop;
#include <cmath>

namespace vecop {


    vec_coefficient_function GeometricBM1D(scalar mu, scalar sigma) {
        // dX=mu X dt + sigma X dB
        vec_coefficient_function result;
        //drift
        auto v0 = [mu](bvector const& in, bvector& out)
        {
            out.resize(1);
            out[0] = mu * in[0];
        };
        //vol
        auto v1 = [sigma](bvector const& in, bvector& out)
        {
            out.resize(1);
            out[0] = sigma * in[0];
        };
        //Stratonovich correction
        //if (isStrat)
        //    V0 -= 0.5 * (V1 * V1).TruncateByLength(size_t(1));

        result.push_back(v0);
        result.push_back(v1);
        return result;
    }

    vec_coefficient_function GeometricBMnAverage1D(scalar mu, scalar sigma) {
        // dX=mu X dt + sigma X dB.
        // dA=X dt.
        vec_coefficient_function result;
        //drift
        auto v0 = [mu](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = mu * in[0];
            out[1] = in[0];
        };

        auto v1 = [sigma](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = sigma * in[0];
            out[1] = 0.0;
        };

        //Stratonovich correction
        //if (isStrat)
        //    V0 -= 0.5 * (V1 * V1).TruncateByLength(size_t(1));

        result.push_back(v0);
        result.push_back(v1);
        return result;
    }

    vec_coefficient_function GeometricBM2D(scalar mu1, scalar sigma1, scalar mu2,
                               scalar sigma2, scalar rho) {
        // dX1=mu1 X1 dt + sigma1 X1 dB1.
        // dX2=mu2 X2 dt + sigma2 rho X2 dB1 + sigma2 sqrt(1-rho^2) X2 dB2

        vec_coefficient_function result;
        //drift
        auto v0 = [mu1, mu2](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = mu1 * in[0];
            out[1] = mu2 * in[1];
        };

        // vol1
        auto v1 = [sigma1, sigma2, rho](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = sigma1 * in[0];
            out[1] = sigma2 * rho * in[1];
        };

        // vol2
        auto v2 = [sigma2, rho](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = 0.0;
            out[1] = sigma2 * std::sqrt(1.0 - rho * rho) * in[1];
        };

        //Stratonovich correction
        //if (isStrat) {
        //    V0 -= 0.5 * (V1 * V1).TruncateByLength(size_t(1));
        //    V0 -= 0.5 * (V2 * V2).TruncateByLength(size_t(1));
        //}

        result.push_back(v0);
        result.push_back(v1);
        result.push_back(v2);
        return result;
    }

    vec_coefficient_function StochasticCEVVol1D(scalar mu, scalar sigma, scalar a, scalar b,
                                    scalar c, scalar rho, scalar e) {
        // dX=mu X dt + sigma sqrt(V) X dB1.
        // dV=a(b-V)dt + c V^e(rho dB1+sqrt(1-rho^2) dB2)
        vec_coefficient_function result;
        //drift
        auto v0 = [mu, a, b](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = mu * in[0];
            out[1] = a * b - a * in[1];
        };

        //vol1
        auto v1 = [sigma, c, e, rho](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = sigma * in[0] * std::sqrt(in[1]);
            out[1] = c * rho * std::pow(in[1], e);
        };

        //vol2
        auto v2 = [c, e, rho](bvector const& in, bvector& out)
        {
            out.resize(2);
            out[0] = 0.0;
            out[1] = c * std::sqrt(1.0 - rho * rho) * std::pow(in[1], e);
        };

        //Stratonovich correction
        //if (isStrat) {
        //    V0 -= 0.5 * (V1 * V1).TruncateByLength(size_t(1));
        //    V0 -= 0.5 * (V2 * V2).TruncateByLength(size_t(1));
        //}

        result.push_back(v0);
        result.push_back(v1);
        result.push_back(v2);
        return result;
    }

    vec_coefficient_function StochasticCEVVolnAverage1D(scalar mu, scalar sigma, scalar a, scalar b,
                                            scalar c, scalar rho, scalar e) {
        // dX=mu X dt + sigma sqrt(V) X dB1.
        // dA=Xdt
        // dV=a(b-V)dt + c V^e(rho dB1+sqrt(1-rho^2) dB2)
        vec_coefficient_function result;
        //drift
        auto v0 = [mu, a, b](bvector const& in, bvector& out)
        {
            out.resize(3);
            out[0] = mu * in[0];
            out[1] = in[0];
            out[2] = a * b - a * in[2];
        };

        //vol1
        auto v1 = [sigma, c, e, rho](bvector const& in, bvector& out)
        {
            out.resize(3);
            out[0] = sigma * in[0] * std::sqrt(in[1]);
            out[1] = 0.0;
            out[2] = c * rho * std::pow(in[2], e);
        };

        //vol2
        auto v2 = [sigma, c, e, rho](bvector const& in, bvector& out)
        {
            out.resize(3);
            out[0] = 0.0;
            out[1] = 0.0;
            out[2] = c * std::sqrt(1.0 - rho * rho) * std::pow(in[2], e);
        };

        //Stratonovich correction
        //if (isStrat) {
        //    V0 -= 0.5 * (V1 * V1).TruncateByLength(size_t(1));
        //    V0 -= 0.5 * (V2 * V2).TruncateByLength(size_t(1));
        //}

        result.push_back(v0);
        result.push_back(v1);
        result.push_back(v2);
        return result;
    }
}