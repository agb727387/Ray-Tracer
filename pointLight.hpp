#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"


namespace qbRT
{
	class pointLight : public lightbase
	{
	public:
		pointLight();

		// Override constructor...
		virtual ~pointLight() override;

		// Function to compute the illumination goes here...
		virtual bool computeIllumination(const qbVector<double>& intPoint, const qbVector<double>
			& localNormal, const std::vector<std::shared_ptr<qbRT::objectBase>>& objectList,
			const std::shared_ptr<qbRT::objectBase>& currentObject, qbVector<double>& color,
			double& intensity) override;
	};
}

#endif
