#pragma once
#include "Animation.h"

namespace ENgines::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& AddPositionKey(const Math::Vector3& pos, float time);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rot, float time);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale, float time);
		AnimationBuilder& AddEventKey(AnimationCallback cb, float time);
		AnimationBuilder& AddParameterEventKey(AnimationParameterCallback cb, float time);
		[[nodiscard]] Animation Build();
	private:
		Animation mWorkingCopy;
	};
}