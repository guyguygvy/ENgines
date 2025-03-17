#pragma once

namespace ENgines
{
	enum class EventType
	{
		None,
		SpacePressed,
		LShiftPressed,
		AnimationKey
	};

	class Event
	{
	public:
		Event() = default;
		Event(EventType et) : mEventType(et) {}
		virtual ~Event() = default;

		EventType GetType() const { return mEventType; }

	private:
		EventType mEventType = EventType::None;
	};

	class SpacePressedEvent : public Event
	{
	public:
		SpacePressedEvent() : Event(EventType::SpacePressed) {}
	};

	class LShiftPressedEvent : public Event
	{
	public:
		LShiftPressedEvent() : Event(EventType::LShiftPressed) {}
	};
	class AnimationKeyEvent : public Event
	{
	public:
		AnimationKeyEvent() : Event(EventType::AnimationKey) {}
		AnimationKeyEvent(int index) : Event(EventType::AnimationKey), mIndex(index) {}
		int GetIndex() const { return mIndex; }
		void SetIndex(int index) { mIndex = index; }

	private:
		int mIndex = 0;
	};
}