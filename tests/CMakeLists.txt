include(Unittests)

add_unit_test_suite(
    TARGET test_aeon_engine
    SOURCES
        test_render_queue.cpp
    LIBRARIES aeon_engine
    FOLDER engine/tests
)
