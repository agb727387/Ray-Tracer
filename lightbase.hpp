#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "qbVector.h"
#include "ray.hpp"
#include "objectbase.hpp"

namespace qbRT
{
	class lightbase
	{
	public:
		// Constructor and destructor...
		lightbase();
		virtual ~lightbase();

		// Here is the function to compute illumination contribution...
		virtual bool computeIllumination(const qbVector<double>& intPoint, const qbVector<double>
			& localNormal, const std::vector<std::shared_ptr<qbRT::objectBase>>& objectList,
			const std::shared_ptr<qbRT::objectBase>& currentObject, qbVector<double>& color,
			double& intensity);

	public:
		qbVector<double> m_color{ 3 };
		qbVector<double> m_location{ 3 };
		double m_intensity;
	};
}

#endif
