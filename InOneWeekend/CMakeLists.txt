cmake_minimum_required(VERSION 3.5)

project(RayTracingInOneWeekend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    RayTracingInOneWeekend

    Camera.h
    Color.h
    Common.h
    lambertian.h
    Material.h
    metal.h
    Ray.h
    Sphere.h
    Surface.h
    SurfaceList.h
    Vec3.h

    main.cpp
)
