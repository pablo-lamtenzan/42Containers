
TESTER_IMPL_DIR=tests
TESTER_LOG_DIR=__TESTER__
MAIN=main.cpp
COMPILER=clang++
SAFE_FLAGS=
DEBUG_TOOL=
CHECK_CPP_VERSION= # remove auto and stop using it is c++11

set -e

rm -rf ${TESTER_LOG_DIR}
mkdir ${TESTER_LOG_DIR}
${COMPILER} ${SAFE_FLAGS} ${CHECK_CPP_VERSION} ${DEBUG_TOOL} "${TESTER_IMPL_DIR}/${MAIN}"
./a.out ; rm ./a.out
read -p "Do you want to delete the test log ? [y/n] " -n1 -r ANSWER
echo
if [[ ${ANSWER} =~ ^[Yy]$ ]]; then
	echo "The test log has been cuccesfully deleted !"
	rm -rf ${TESTER_LOG_DIR}
fi
