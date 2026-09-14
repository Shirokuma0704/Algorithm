# CLion 이 이 파일을 읽고 빌드 방법을 알아내요.
# 저장소 루트(Algorithm/)에 있어야 합니다. 하위 폴더에 두면 CLion 이 CMake
# 프로젝트로 인식을 못 하고 파일 단위 임시 컴파일로 떨어져요. 그러면 실행
# 파일이 소스 옆에 그대로 쌓입니다. Week4 에서 겪었던 그 문제예요.
#
# 문제 파일마다 main() 이 따로 있으니까, 파일 하나당 실행 파일 하나를 만들어요.
# 만들어진 건 전부 cmake-build-debug/ 안으로 들어가고요.
#
# 새 .c 를 추가했는데 실행 목록에 안 보이면, CLion 오른쪽 위
# "Reload CMake Project" 를 한 번 눌러주면 돼요.

cmake_minimum_required(VERSION 3.20)
project(Algorithm C)

set(CMAKE_C_STANDARD 11)

# 경고를 켜둬요. C 에서 조용히 넘어가면 나중에 런타임에 터지는 것들을
# 컴파일 단계에서 미리 보여주거든요. 초기화 안 한 변수, 리턴 빠진 함수 같은 거요.
if (NOT MSVC)
    add_compile_options(-Wall -Wextra)
endif ()

# 플랫폼 폴더(leetcode/, 나중에 boj/, programmers/) 아래의 .c 를 전부 모아요.
# 나중에 폴더가 늘어나도 이 줄은 안 건드려도 됩니다.
file(GLOB_RECURSE SOLUTION_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.c")

foreach (SOURCE_FILE ${SOLUTION_SOURCES})
    # leetcode/0206_reverse_linked_list.c  ->  타깃 이름 lc0206_reverse_linked_list
    #
    # 앞에 두 글자를 붙이는 이유가 두 개예요.
    # 하나는 나중에 백준에도 같은 번호가 생겼을 때 이름이 안 부딪히게 하려고,
    # 다른 하나는 CLion 실행 목록에서 플랫폼이 한눈에 보이게 하려고요.
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    get_filename_component(DIR_PATH ${SOURCE_FILE} DIRECTORY)
    get_filename_component(DIR_NAME ${DIR_PATH} NAME)

    if (DIR_NAME STREQUAL "leetcode")
        set(PREFIX "lc")
    elseif (DIR_NAME STREQUAL "boj")
        set(PREFIX "bj")
    elseif (DIR_NAME STREQUAL "programmers")
        set(PREFIX "pg")
    else ()
        set(PREFIX "${DIR_NAME}_")
    endif ()

    add_executable(${PREFIX}${FILE_NAME} ${SOURCE_FILE})
endforeach ()
