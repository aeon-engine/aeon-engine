#ifndef AeonSingleton_h__
#define AeonSingleton_h__

#define AeonInitializeSingleton(type)					template <> type * Aeon::Singleton <type>::instance_ = NULL

namespace Aeon
{

template <class type>
class Singleton
{
public:
	Singleton()
	{
		assert(instance_ == NULL);
		instance_ = static_cast<type *>(this);

		if (instance_ == NULL)
		{
			throw std::exception();
		}
	}

	virtual ~Singleton()
	{
		instance_ = NULL;
	}

	static type *create()
	{
		return new type;
	}

	static void dispose()
	{
		if (instance_ != NULL)
			delete (type *)instance_;
	}

	static type & getSingleton()
	{
		assert(instance_);

		if (instance_ == NULL)
		{
			throw std::exception();
		}

		return *instance_;
	}

	static type * getSingletonPtr()
	{
		return instance_;
	}

protected:
	static type * instance_;

};

} //namespace Aeon

#endif // AeonSingleton_h__
