cmake_minimum_required(VERSION 3.16)
project(PlanetSystemDesigner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

set(PROJECT_SOURCES
    main.cpp
    facade/Facade.h
    facade/Facade.cpp
    commands/BaseCommand.h
    commands/object/ObjectCommand.h
    commands/object/ObjectCommand.cpp
    commands/camera/CameraCommand.h
    commands/camera/CameraCommand.cpp
    component/BaseObject.h
    component/composite/Composite.h
    component/composite/Composite.cpp
    component/primitive/visible/model/BaseModel.h
    component/primitive/visible/model/celestial/CelestialBody.h
    component/primitive/visible/model/celestial/CelestialBody.cpp
    component/primitive/visible/model/impl/SphereImpl.h
    component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h
    component/primitive/visible/model/impl/parametric/ParametricSphereImpl.cpp
    component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.h
    component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.cpp
    component/primitive/invisible/camera/BaseCamera.h
    component/primitive/invisible/camera/CameraAdapter.h
    component/primitive/invisible/camera/CameraAdapter.cpp
    visitors/BaseVisitor.h
    visitors/draw/DrawVisitor.h
    visitors/draw/DrawVisitor.cpp
    visitors/transform/TransformVisitor.h
    visitors/transform/TransformVisitor.cpp
    scene/Scene.h
    scene/Scene.cpp
    managers/ManagerProvider.h
    managers/ManagerProvider.cpp
    managers/draw/DrawManager.h
    managers/draw/DrawManager.cpp
    managers/camera/CameraManager.h
    managers/camera/CameraManager.cpp
    managers/scene/SceneManager.h
    managers/scene/SceneManager.cpp
    vector/Vec3.h
    qt/inc/mainwindow.h
    qt/src/mainwindow.cpp
    qt/inc/plane.h
    qt/src/plane.cpp
)

qt_add_executable(PlanetSystemDesigner ${PROJECT_SOURCES})
target_link_libraries(PlanetSystemDesigner PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)
