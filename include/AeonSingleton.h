#ifndef AeonSingleton_h__
#define AeonSingleton_h__

#define AeonInitializeSingleton(type)					template <> type * Aeon::Singleton <type>::mSingleton = NULL

namespace Aeon
{

template <class type>
class Singleton
{
public:
	Singleton()
	{
		assert(mSingleton == NULL);
		mSingleton = static_cast<type *>(this);

		if (mSingleton == NULL)
		{
			throw std::exception();
		}
	}

	virtual ~Singleton()
	{
		mSingleton = NULL;
	}

	static type *create()
	{
		return new type;
	}

	static void dispose()
	{
		if (mSingleton != NULL)
			delete (type *)mSingleton;
	}

	static type & getSingleton()
	{
		assert(mSingleton);

		if (mSingleton == NULL)
		{
			throw std::exception();
		}

		return *mSingleton;
	}

	static type * getSingletonPtr()
	{
		return mSingleton;
	}

protected:
	static type * mSingleton;

};

} //namespace Aeon

#endif // AeonSingleton_h__
