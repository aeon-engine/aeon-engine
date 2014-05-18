#include "Aeon/Aeon.h"
#include "Aeon/Resources/Resource.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

Resource::Resource(ResourceManager *creator, const std::string &name)
:
creator_(creator),
name_(name),
state_(State::Empty)
{

}

Resource::~Resource()
{

}

bool Resource::__load(StreamPtr stream)
{
	if (state_ != State::Empty)
	{
		Console::warning("[Resource]: Load called on resource while in wrong state: %u", (int) state_);
		return false;
	}

	return __load_impl(stream);
}

bool Resource::__unload()
{
	if(state_ != State::Loaded)
	{
		Console::warning("[Resource]: Unload called on resource while in wrong state: %u", (int) state_);
		return false;
	}

	state_ = State::Unloading;

	bool result = __unload_impl();

	if(result)
		state_ = State::Unloaded;

	return result;
}

bool Resource::__finalize()
{
	if (state_ != State::ReadyForFinalize)
	{
		Console::warning("[Resource]: Finalize called on resource while in wrong state: %u", (int) state_);
		return false;
	}

	bool result = __finalize_impl();

	if(result)
		state_ = State::Loaded;

	return result;
}

} /* namespace Aeon */
