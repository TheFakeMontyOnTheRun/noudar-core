lcov --capture --directory . --output-file lcov-output.info && genhtml lcov-output.info --output-directory coverage
rm lcov-output.info
