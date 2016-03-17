#include <audio/openal/openal_check.h>
#include <audio/openal/openal_includes.h>

#include <string>

struct al_error_desc
{
    const char *error;
    const char *description;
};

static al_error_desc al_error_lookup[] = {
    { "AL_INVALID_NAME" , "an unacceptable name has been specified" },
    { "AL_INVALID_ENUM", "an unacceptable value has been specified for an enumerated argument" },
    { "AL_INVALID_VALUE", "a numeric argument is out of range" },
    { "AL_INVALID_OPERATION", "the specified operation is not allowed in the current state" },
    { "AL_OUT_OF_MEMORY", "there is not enough memory left to execute the command" },
    {nullptr, nullptr}
};

void al_check_error(const char *file, unsigned int line)
{
    // Get the last error
    ALenum error_code = alGetError();

    if (error_code != AL_NO_ERROR)
    {
        int lookup_nr = error_code - AL_INVALID_NAME;
        al_error_desc error = {nullptr, nullptr};
        if (lookup_nr >= 0 && lookup_nr < 5)
            error = al_error_lookup[lookup_nr];
        printf("OpenAL call failed in %s (%u) : %s, %s\n", file, line, error.error, error.description);
    }
}
