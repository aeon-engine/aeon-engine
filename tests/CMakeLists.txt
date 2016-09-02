include(Unittests)

add_unit_test_suite(
    TARGET test_aeon_engine
    SOURCES
        test_render_queue.cpp
        test_rectangle.cpp
		test_resource_file.cpp
    LIBRARIES aeon_engine
    FOLDER engine/tests
)
