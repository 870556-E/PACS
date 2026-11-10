# CMAKE compilation commands for linux

## Extra: Enable autocomplete
1. set +u

## SETUP:
0. Having PACS-repo as source
1. mkdir build-release
2. cd build-release

## COMPILATION:
0. Starting in PACS-repo/build-release
1. cmake -DCMAKE_CXX_FLAGS="-Wno-sign-compare" -DCMAKE_BUILD_TYPE=Release ../
2. cd Laboratory-3
3. make -j2 -k