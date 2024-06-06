#include "pch.h"
#include "Helper.h"

std::wstring Helper::ToWString(string value)
{
	return wstring(value.begin(), value.end());
}

std::string Helper::ToString(wstring value)
{
	return string(value.begin(), value.end());
}

vec3 Helper::GetAttenuationCoeff(float distance)
{
    const auto linear_coeff = vec4(
        8.4523112e-05,
        4.4712582e+00,
        -1.8516388e+00,
        3.3955811e+01
    );
    const auto quad_coeff = vec4(
        -7.6103583e-04,
        9.0120201e+00,
        -1.1618500e+01,
        1.0000464e+02
    );

    float kc = 1.0f;
    float d = 1.0f / distance;
    auto dvec = vec4(1.0f, d, d * d, d * d * d);
    float kl = linear_coeff.Dot(dvec);
    float kq = quad_coeff.Dot(dvec);

    return vec3(kc, max(kl, 0.0f), max(kq * kq, 0.0f));
}
