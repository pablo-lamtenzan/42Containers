
TESTER_IMPL_DIR=tests
TESTER_LOG_DIR=__TESTER__
MAIN=main.cpp
COMPILER=clang++
SAFE_FLAGS=
CHECK_CPP_VERSION=

set -e

rm -rf ${TESTER_LOG_DIR}
mkdir ${TESTER_LOG_DIR}
${COMPILER} ${SAFE_FLAGS} ${CHECK_CPP_VERSION} "${TESTER_IMPL_DIR}/${MAIN}"
./a.out
rm ./a.out
read -p "Do you you want to delete the test log ? [y/n] " -n1 -r ANSWER
echo
if [[ ${ANSWER} =~ ^[Yy]$ ]]; then
	echo "Test log has been cuccesfully deleted !"
	rm -rf ${TESTER_LOG_DIR}
fi
