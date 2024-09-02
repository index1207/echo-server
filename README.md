# Echo Server
netcpp를 사용해 개발한 에코서버입니다. 스트레스 테스트를 하기 위해 개발하였습니다.

## 종속성
- [vcpkg]()
- [netcpp]()

## 빌드
먼저 vcpkg를 설치해야 합니다. 그 뒤 아래의 스크립트에서 `CMAKE_TOOLCHAIN_FILE`값에 vcpkg/scripts/buildsystem/vcpkg.cmake의 경로를 입력하여 실행하면 빌드가 가능합니다.
```shell
cmake -B build -DENABLE_TEST=ON -DCMAKE_TOOLCHAIN_FILE={VCPKG_툴체인_파일_경로}
cmake --build build --config Release
```

## 테스트 결과
