cmake_minimum_required(VERSION 3.5)

project(RayTracingInOneWeekend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    RayTracingInOneWeekend

    camera.h
    color.h
    common.h
    lambertian.h
    material.h
    metal.h
    ray.h
    sphere.h
    surface.h
    surface_list.h
    vec3.h

    main.cpp
)
