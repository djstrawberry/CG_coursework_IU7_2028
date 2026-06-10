cmake_minimum_required(VERSION 3.16)
project(PlanetSystemDesigner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

set(PROJECT_SOURCES
    main.cpp
    
    # Facade
    facade/Facade.h
    facade/Facade.cpp
    
    # Commands
    commands/BaseCommand.h
    commands/object/ObjectCommand.h
    commands/object/ObjectCommand.cpp
    commands/camera/CameraCommand.h
    commands/camera/CameraCommand.cpp
    
    # Component - base
    component/BaseObject.h
    component/BaseObject.cpp
    component/primitive/Primitive.h
    component/primitive/visible/VisibleObject.h
    component/primitive/invisible/InvisibleObject.h
    component/composite/Composite.h
    component/composite/Composite.cpp
    
    # Component - visible models
    component/primitive/visible/model/BaseModel.h
    component/primitive/visible/model/celestial/CelestialBody.h
    component/primitive/visible/model/celestial/CelestialBody.cpp
    component/primitive/visible/model/impl/SphereImpl.h
    component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h
    component/primitive/visible/model/impl/parametric/ParametricSphereImpl.cpp
    component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.h
    component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.cpp
    
    # Component - invisible camera
    component/primitive/invisible/camera/BaseCamera.h
    component/primitive/invisible/camera/CameraAdapter.h
    component/primitive/invisible/camera/CameraAdapter.cpp
    component/primitive/invisible/camera/impl/CameraImpl.h
    component/primitive/invisible/camera/default/DefaultCamera.h
    component/primitive/invisible/camera/default/DefaultCamera.cpp
    
    # Visitors
    visitors/BaseVisitor.h
    visitors/creators/VisitorCreator.h
    visitors/creators/VisitorCreator.hpp
    visitors/draw/DrawVisitor.h
    visitors/draw/DrawVisitor.cpp
    
    # Scene
    scene/Scene.h
    scene/Scene.cpp
    
    # Managers
    managers/ManagerProvider.h
    managers/ManagerProvider.cpp
    managers/draw/DrawManager.h
    managers/draw/DrawManager.cpp
    managers/camera/CameraManager.h
    managers/camera/CameraManager.cpp
    managers/scene/SceneManager.h
    managers/scene/SceneManager.cpp
    
    # Vector
    vector/Vec3.h
    vector/Vec3.hpp
    
    # Concepts
    concepts/concepts.h
    
    # Materials
    materials/Material.h
    
    # Factories - Draw
    factories/draw/BaseDrawFactory.h
    factories/draw/products/BasePainter.h
    factories/draw/qt/QtDrawFactory.h
    factories/draw/qt/QtDrawFactory.cpp
    factories/draw/qt/products/QtPainter.h
    factories/draw/qt/products/QtPainter.cpp
    
    # Strategies - Projection
    strategies/projection/BaseProjectionStrategy.h
    strategies/projection/creators/ProjectionStrategyCreator.h
    strategies/projection/creators/ProjectionStrategyCreator.hpp
    strategies/projection/default/DefaultProjectionStrategy.h
    strategies/projection/default/DefaultProjectionStrategy.cpp
    
    # Strategies - Conversion
    strategies/conversion/BaseCoordinateConvertStrategy.h
    strategies/conversion/creator/ConvertCoordsStrategyCreator.h
    strategies/conversion/creator/ConvertCoordsStrategyCreator.hpp
    strategies/conversion/default/DefaultConvertCoordinatesStrategy.h
    strategies/conversion/default/DefaultConvertCoordinatesStrategy.cpp
    
    # Exceptions
    exceptions/BaseException.h
    exceptions/BaseException.cpp
    exceptions/camera/CameraException.h
    exceptions/camera/CameraException.cpp
    exceptions/composite/CompositeException.h
    exceptions/composite/CompositeException.cpp
    exceptions/managers/BaseManagerException.h
    exceptions/managers/BaseManagerException.cpp
    exceptions/managers/camera/CameraManagerException.h
    exceptions/managers/camera/CameraManagerException.cpp
    exceptions/scene/SceneException.h
    exceptions/scene/SceneException.cpp
    exceptions/vector/VectorException.h
    exceptions/vector/VectorException.cpp
    
    # Qt UI
    qt/inc/mainwindow.h
    qt/src/mainwindow.cpp
    qt/inc/plane.h
    qt/src/plane.cpp
    ui/mainwindow.ui
)

qt_add_executable(PlanetSystemDesigner ${PROJECT_SOURCES})
target_include_directories(PlanetSystemDesigner PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(PlanetSystemDesigner PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)