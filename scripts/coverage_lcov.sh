#!/bin/bash
pushd $BUILD_DIR
lcov -b ../ -c -i -d . -o test.info
ctest -C Debug --verbose
lcov -b ../ -c -d . -o test2.info
lcov --add-tracefile test.info -t test -a test2.info -t test2 -o test_merged.info
lcov --remove test_merged.info '/Applications/Xcode.app/*' '*/Gitlab/osx_clang/*' '/usr/include/*' '*/tests/test_*' --output-file test_merged.info.clean
lcov -l test_merged.info.clean
genhtml -o ${GIT_COMMIT_HASH} test_merged.info.clean
git clone http://gitlabci:${GITLAB_CI_PASSWORD}@gitlab.robindegen.nl/aeon/coverage_results.git coverage_results
cd coverage_results
cd aeon_engine
rm -rf ${GIT_COMMIT_HASH}
mv ../../${GIT_COMMIT_HASH}/ .
git add -A
git commit -am "Code coverage for Aeon Engine ${GIT_COMMIT_HASH}"
git push origin master
echo Code coverage can be found here:
echo http://coverage.robindegen.nl/aeon_engine/${GIT_COMMIT_HASH}/
popd
