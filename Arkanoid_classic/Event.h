

#ifndef EVENT_H_
#define EVENT_H_

//https://habr.com/ru/post/424593/ 

#include <cassert>
#include <vector>

template<class ...TParams>
class AbstractEventHandler
{

	using MyType = AbstractEventHandler<TParams...>;

public:
	virtual void call(TParams ...params) = 0;

	bool operator==(const MyType& other) const
	{
		return isEquals(other);
	}

	bool operator!=(const MyType& other) const
	{
		return !(*this == other);
	}

protected:
	AbstractEventHandler() {}
	virtual bool isEquals(const MyType& other) const = 0;
};


template<class ...TParams>
class TEvent
{
	using TEventHandler = AbstractEventHandler<TParams...>;
	using TEventHandlerIt = typename std::vector<TEventHandler*>::const_iterator;

public:
	TEvent() : m_handlers() { }

	~TEvent()
	{
		for (TEventHandler* oneHandler : m_handlers)
			delete oneHandler;
		m_handlers.clear();
	}

	void operator()(TParams ...params)
	{
		for (TEventHandler* oneHandler : m_handlers)
			oneHandler->call(params...);
	}

	bool operator += (TEventHandler& eventHandler)
	{
		if (findEventHandler(eventHandler) == m_handlers.end())
		{
			m_handlers.push_back(&eventHandler);
			return true;
		}
		return false;
	}

	bool operator -= (TEventHandler& eventHandler)
	{
		{
			auto it = findEventHandler(eventHandler);
			if (it != m_handlers.end())
			{
				TEventHandler* removeEventHandler = *it;
				m_handlers.erase(it);
				delete removeEventHandler;
				return true;
			}
			return false;
		}
	}	

private:	
	inline TEventHandlerIt findEventHandler(TEventHandler& eventHandler) const
	{
		return std::find_if(m_handlers.cbegin(), m_handlers.cend(), [&eventHandler](const TEventHandler* oneHandler)
			{
				return (*oneHandler == eventHandler);
			});
	}
	std::vector<TEventHandler*> m_handlers;	
};

template<class TObject, class ...TParams>
class MethodEventHandler : public AbstractEventHandler<TParams...>
{
	using MyType = MethodEventHandler<TObject, TParams...>;
	using TMethod = void(TObject::*)(TParams...);

public:
	MethodEventHandler(TObject& object, TMethod method) :
		AbstractEventHandler<TParams...>(),
		m_object(object),
		m_method(method)
	{
		assert(m_method != nullptr);
	}

	virtual void call(TParams...params) override final
	{
		(m_object.*m_method)(params...);
	}

protected:
	virtual bool isEquals(const AbstractEventHandler<TParams...>& other) const override
	{
		const MyType* _other = dynamic_cast<const MyType*>(&other);
		return (_other != nullptr && &m_object == &_other->m_object && m_method == _other->m_method);
	}

private:
	TObject& m_object;
	TMethod m_method;
};

template<class TObject, class ...TParams>
AbstractEventHandler<TParams...>& createMethodEventHandler(TObject& object,
	void(TObject::* method)(TParams...))
{
	return *new MethodEventHandler<TObject, TParams...>(object, method);
}

#define METHOD_HANDLER(Object, Method) createMethodEventHandler(Object, &Method)

#endif // !EVENT_H_