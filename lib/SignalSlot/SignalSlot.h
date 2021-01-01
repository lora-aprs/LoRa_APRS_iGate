#ifndef SIGNAL_SLOT_H_
#define SIGNAL_SLOT_H_

#include <list>

class Slot0
{
public:
	virtual void action() = 0;
};

template <typename T>
class Slot1
{
public:
	virtual void action(T elem1) = 0;
};

template <typename T, typename H>
class Slot2
{
public:
	virtual void action(T elem1, H elem2) = 0;
};

template <typename T, typename H, typename K>
class Slot3
{
public:
	virtual void action(T elem1, H elem2, K elem3) = 0;
};

class Signal0
{
public:
	void emit()
	{
		for(Slot0 * slot: _slots)
		{
			slot->action();
		}
	}

	void connectSlot(Slot0 * slot)
	{
		_slots.push_back(slot);
	}

private:
	std::list<Slot0 *> _slots;
};

template <typename T>
class Signal1
{
public:
	void emit(T elem1)
	{
		for(Slot1<T> * slot: _slots)
		{
			slot->action(elem1);
		}
	}

	void connectSlot(Slot1<T> * slot)
	{
		_slots.push_back(slot);
	}

private:
	std::list<Slot1<T> *> _slots;
};

template <typename T, typename H>
class Signal2
{
public:
	void emit(T elem1, H elem2)
	{
		for(Slot2<T, H> * slot: _slots)
		{
			slot->action(elem1, elem2);
		}
	}

	void connectSlot(Slot2<T, H> * slot)
	{
		_slots.push_back(slot);
	}

private:
	std::list<Slot2<T, H> *> _slots;
};

template <typename T, typename H, typename K>
class Signal3
{
public:
	void emit(T elem1, H elem2, K elem3)
	{
		for(Slot3<T, H, K> * slot: _slots)
		{
			slot->action(elem1, elem2, elem3);
		}
	}

	void connectSlot(Slot3<T, H, K> * slot)
	{
		_slots.push_back(slot);
	}

private:
	std::list<Slot3<T, H, K> *> _slots;
};

#endif
