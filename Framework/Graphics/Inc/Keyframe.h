#pragma once
#include "Common.h"
#include "../Engine/ENgines/Inc/Event.h"


namespace ENgines::Graphics
{
	template<class T>
	struct Keyframe
	{
		//Math::Vector3 position = Math::Vector3::Zero;
		//Math::Quaternion rotation = Math::Quaternion::Identity;
		//Math::Vector3 scale = Math::Vector3::One;

		Keyframe() = default;
		Keyframe(const T& k, float t)
			: key(k)
			, time(t)
		{

		}
		T key = T();
		float time = 0.0f;
	};

	template<class T>
	using Keyframes = std::vector<Keyframe<T>>;
	using AnimationCallback = std::function<void()>;
	using AnimationParameterCallback = std::function<void(const Event&)>;

	using PositionKeys = Keyframes<Math::Vector3>;
	using RotationKeys = Keyframes<Math::Quaternion>;
	using ScaleKeys = Keyframes<Math::Vector3>;
	using EventKeys = Keyframes<AnimationCallback>;
	using EventParameterKeys = Keyframes<AnimationParameterCallback>;
}