# CG_coursework_IU7_2028
## Визуализация планетной системы на C++ 

Разработать ПО с пользовательским интерфейсом, моделирующее интерактивный конструктор планетных систем. На сцене находится центральная звезда. Пользователь может добавлять различные типы планет (в виде сфер разного радиуса), образующие иерархические композиции. Источник света расположен в центре звезды, есть возможность менять его цвет. Можно изменять положение камер. Пользователь должен иметь возможность изменять параметры материалов тел, а также изменять размеры орбит планет. 
 
```
CG_coursework_IU7_2028
├─ CMakeLists.txt
├─ PlanetSystemDesigner
├─ README.md
├─ build
│  ├─ .cmake
│  │  └─ api
│  │     └─ v1
│  │        ├─ query
│  │        │  └─ client-vscode
│  │        │     └─ query.json
│  │        └─ reply
│  │           ├─ cache-v2-b9e59c34fbbfb89cf636.json
│  │           ├─ cmakeFiles-v1-c851f29bc856a5680784.json
│  │           ├─ codemodel-v2-e64236a3d0fc679be157.json
│  │           ├─ directory-.-Debug-fd6451d79dc282e2f566.json
│  │           ├─ index-2026-06-18T10-41-35-0583.json
│  │           ├─ target-OpenGL__EGL-Debug-9a56c3cb4e4f37e486d3.json
│  │           ├─ target-OpenGL__GL-Debug-9c41419c4f871cdde32d.json
│  │           ├─ target-OpenGL__GLES2-Debug-eab299f858c77a9abf44.json
│  │           ├─ target-OpenGL__GLES3-Debug-ea444b056bfd80a06d58.json
│  │           ├─ target-OpenGL__GLX-Debug-d8a09728916e1cc29d39.json
│  │           ├─ target-OpenGL__OpenGL-Debug-fc11479005336f5d746d.json
│  │           ├─ target-PlanetSystemDesigner-Debug-fd98c35b623b50b52ff8.json
│  │           ├─ target-PlanetSystemDesigner_autogen-Debug-46dbe78e9e437a3f8a21.json
│  │           ├─ target-PlanetSystemDesigner_autogen_timestamp_deps-Debug-d88772d86eb69fcf34ba.json
│  │           ├─ target-Qt6__Core-Debug-4de8efed059d1a01527c.json
│  │           ├─ target-Qt6__DBus-Debug-a3616c2ecb62ee183f07.json
│  │           ├─ target-Qt6__DmaBufServerBufferPlugin-Debug-7e25e5ea904c5edc0621.json
│  │           ├─ target-Qt6__DrmEglServerBufferPlugin-Debug-785bf6cd78808d5a622f.json
│  │           ├─ target-Qt6__GlobalConfig-Debug-3dc76cc5d8a811d5f6a5.json
│  │           ├─ target-Qt6__GlobalConfigPrivate-Debug-d276e119528150469b12.json
│  │           ├─ target-Qt6__Gui-Debug-27b3947ee4096e729a37.json
│  │           ├─ target-Qt6__OpenGL-Debug-5dee15782cffdecb122a.json
│  │           ├─ target-Qt6__OpenGLWidgets-Debug-9a36c5cba5ae3d7eb493.json
│  │           ├─ target-Qt6__Platform-Debug-ab5df0f5c74827328fbe.json
│  │           ├─ target-Qt6__PlatformAppInternal-Debug-76a04e048b46431fe61b.json
│  │           ├─ target-Qt6__PlatformCommonInternal-Debug-a18ef3975db5fe73e5eb.json
│  │           ├─ target-Qt6__PlatformExampleInternal-Debug-4e7156a696f8a506fcbb.json
│  │           ├─ target-Qt6__PlatformModuleInternal-Debug-f7cfc7102f93c7314178.json
│  │           ├─ target-Qt6__PlatformPluginInternal-Debug-82460340ed349900b6d8.json
│  │           ├─ target-Qt6__PlatformToolInternal-Debug-a74a3fb1040080db11de.json
│  │           ├─ target-Qt6__QComposePlatformInputContextPlugin-Debug-9d7ca097a14667ff552f.json
│  │           ├─ target-Qt6__QEglFSEmulatorIntegrationPlugin-Debug-b3658f771897353f3f96.json
│  │           ├─ target-Qt6__QEglFSIntegrationPlugin-Debug-f5e8796c0c8d10f526d8.json
│  │           ├─ target-Qt6__QEglFSKmsEglDeviceIntegrationPlugin-Debug-a83f12722e9a64e8735a.json
│  │           ├─ target-Qt6__QEglFSKmsGbmIntegrationPlugin-Debug-2b016dd81d581d8b540b.json
│  │           ├─ target-Qt6__QEglFSX11IntegrationPlugin-Debug-f8fde248e8fd34350049.json
│  │           ├─ target-Qt6__QEvdevKeyboardPlugin-Debug-e7f41ce04581dc17f94d.json
│  │           ├─ target-Qt6__QEvdevMousePlugin-Debug-5bfe6779ad5badc8d744.json
│  │           ├─ target-Qt6__QEvdevTabletPlugin-Debug-5043a91cdaca3a953aa7.json
│  │           ├─ target-Qt6__QEvdevTouchScreenPlugin-Debug-f3c51825e8ba1a2611cb.json
│  │           ├─ target-Qt6__QGifPlugin-Debug-d41a7c0f505ed3e923ab.json
│  │           ├─ target-Qt6__QGtk3ThemePlugin-Debug-f04318eea02931fe8e31.json
│  │           ├─ target-Qt6__QICOPlugin-Debug-d21ff4fb4ec355d055ad.json
│  │           ├─ target-Qt6__QIbusPlatformInputContextPlugin-Debug-f48f3817ebf199e69769.json
│  │           ├─ target-Qt6__QJpegPlugin-Debug-55a838b1534bd752dc92.json
│  │           ├─ target-Qt6__QLibInputPlugin-Debug-c2f33ff7bcb4bff21099.json
│  │           ├─ target-Qt6__QLinuxFbIntegrationPlugin-Debug-c985e4a15cda83ab97b3.json
│  │           ├─ target-Qt6__QMinimalEglIntegrationPlugin-Debug-03393c40bd7c8adcc5b1.json
│  │           ├─ target-Qt6__QMinimalIntegrationPlugin-Debug-aa2269c3dcd379983555.json
│  │           ├─ target-Qt6__QOffscreenIntegrationPlugin-Debug-3f3705b60fadf035aad4.json
│  │           ├─ target-Qt6__QTsLibPlugin-Debug-7422f18c987e584250f1.json
│  │           ├─ target-Qt6__QTuioTouchPlugin-Debug-60714c2e8e92a8e28306.json
│  │           ├─ target-Qt6__QVkKhrDisplayIntegrationPlugin-Debug-ec1a893790a672dca226.json
│  │           ├─ target-Qt6__QVncIntegrationPlugin-Debug-4d6274186dc21aaeae2c.json
│  │           ├─ target-Qt6__QWaylandAdwaitaDecorationPlugin-Debug-792a2f79bc4de05dbb6a.json
│  │           ├─ target-Qt6__QWaylandBradientDecorationPlugin-Debug-bbec5ea31463daee10cf.json
│  │           ├─ target-Qt6__QWaylandEglClientBufferPlugin-Debug-dc2ecb3062a93978774b.json
│  │           ├─ target-Qt6__QWaylandFullScreenShellV1IntegrationPlugin-Debug-f8eb19e1df72fd2c22c2.json
│  │           ├─ target-Qt6__QWaylandIntegrationPlugin-Debug-da1b23996bc2d63f432b.json
│  │           ├─ target-Qt6__QWaylandWlShellIntegrationPlugin-Debug-671564a11bae82c290f6.json
│  │           ├─ target-Qt6__QWaylandXdgShellIntegrationPlugin-Debug-c61b3c7d79dcb279574d.json
│  │           ├─ target-Qt6__QXcbEglIntegrationPlugin-Debug-1319bef25b37b3622813.json
│  │           ├─ target-Qt6__QXcbGlxIntegrationPlugin-Debug-4a61f4633b8f71ac85cf.json
│  │           ├─ target-Qt6__QXcbIntegrationPlugin-Debug-33f67fb5af84a56304c0.json
│  │           ├─ target-Qt6__QXdgDesktopPortalThemePlugin-Debug-bf1d467194096259b1c2.json
│  │           ├─ target-Qt6__ShmServerBufferPlugin-Debug-26e1dc207fee71a7e43c.json
│  │           ├─ target-Qt6__VulkanServerBufferPlugin-Debug-fb36724cf31ec39cdb8b.json
│  │           ├─ target-Qt6__Widgets-Debug-7c238db553b2c2150de3.json
│  │           ├─ target-Qt6__androiddeployqt-Debug-33c44310551a392c2040.json
│  │           ├─ target-Qt6__androidtestrunner-Debug-743957a39bbf495e7117.json
│  │           ├─ target-Qt6__cmake_automoc_parser-Debug-07ce17a08dda3677c712.json
│  │           ├─ target-Qt6__moc-Debug-5f7d5a347967db0508d7.json
│  │           ├─ target-Qt6__qdbuscpp2xml-Debug-a05fb7af626bdab7eae2.json
│  │           ├─ target-Qt6__qdbusxml2cpp-Debug-ae2e3da3f28d3b99c8f0.json
│  │           ├─ target-Qt6__qlalr-Debug-000bfea3f80ca34c8b78.json
│  │           ├─ target-Qt6__qmake-Debug-25bbe03c753feaa155c5.json
│  │           ├─ target-Qt6__qtpaths-Debug-77b4c29974bd2dde0399.json
│  │           ├─ target-Qt6__qvkgen-Debug-0e290347cff332baff99.json
│  │           ├─ target-Qt6__rcc-Debug-93f9d120af28d3561af7.json
│  │           ├─ target-Qt6__syncqt-Debug-52a81ecf016fecf8d12d.json
│  │           ├─ target-Qt6__tracegen-Debug-6ea3622846235649c379.json
│  │           ├─ target-Qt6__tracepointgen-Debug-5f9488cea9bf777f754c.json
│  │           ├─ target-Qt6__uic-Debug-aadf0bd969f373f2b7d5.json
│  │           ├─ target-Qt6__wasmdeployqt-Debug-0e610bb4eaf6527f8eb4.json
│  │           ├─ target-Qt__androiddeployqt-Debug-37d482101f4dddbc1c8d.json
│  │           ├─ target-Qt__androidtestrunner-Debug-81a4e9a12e25ee0018bf.json
│  │           ├─ target-Qt__cmake_automoc_parser-Debug-80c2ebc9c955b56bf7a5.json
│  │           ├─ target-Qt__moc-Debug-8b37e570cd9d358cd4c0.json
│  │           ├─ target-Qt__qdbuscpp2xml-Debug-c48654b6794b76596158.json
│  │           ├─ target-Qt__qdbusxml2cpp-Debug-8ea557cd6cbbfc29dfc9.json
│  │           ├─ target-Qt__qlalr-Debug-27e0d8493b707b58a24a.json
│  │           ├─ target-Qt__qmake-Debug-f559edf535ce5fad6609.json
│  │           ├─ target-Qt__qtpaths-Debug-934fcf9e3a04806e4356.json
│  │           ├─ target-Qt__qvkgen-Debug-ee21ac44c00a2dd31bbc.json
│  │           ├─ target-Qt__rcc-Debug-13b8525a3e5d694a3be4.json
│  │           ├─ target-Qt__syncqt-Debug-527757e9cd4b7a817358.json
│  │           ├─ target-Qt__tracegen-Debug-3da3b4a037619f02f0f2.json
│  │           ├─ target-Qt__tracepointgen-Debug-a7717490264aad5691d6.json
│  │           ├─ target-Qt__uic-Debug-b17cb37dbe4f57d4f440.json
│  │           ├─ target-Qt__wasmdeployqt-Debug-7d077531f02abecde125.json
│  │           ├─ target-Threads__Threads-Debug-490a063aa4308b8b89e9.json
│  │           ├─ target-Vulkan__Headers-Debug-02302f3bb67085d4163b.json
│  │           ├─ target-Vulkan__Vulkan-Debug-df5cb6f160db2497ec5a.json
│  │           ├─ target-WrapAtomic__WrapAtomic-Debug-8ad33242bb4eacfaa518.json
│  │           ├─ target-WrapOpenGL__WrapOpenGL-Debug-5d520ae2978c735b583c.json
│  │           ├─ target-WrapVulkanHeaders__WrapVulkanHeaders-Debug-89c7cefaaca98f00d25c.json
│  │           ├─ target-qt_private_link_library_targets-Debug-c60c6b15441b933ce4ac.json
│  │           └─ toolchains-v1-911b88f7c63e1f5cf0de.json
│  ├─ .qt
│  │  ├─ QtDeploySupport.cmake
│  │  └─ QtDeployTargets.cmake
│  ├─ CMakeCache.txt
│  ├─ CMakeFiles
│  │  ├─ 4.3.0
│  │  │  ├─ CMakeCXXCompiler.cmake
│  │  │  ├─ CMakeDetermineCompilerABI_CXX.bin
│  │  │  ├─ CMakeSystem.cmake
│  │  │  └─ CompilerIdCXX
│  │  │     ├─ CMakeCXXCompilerId.cpp
│  │  │     ├─ a.out
│  │  │     └─ tmp
│  │  ├─ CMakeConfigureLog.yaml
│  │  ├─ CMakeDirectoryInformation.cmake
│  │  ├─ CMakeRuleHashes.txt
│  │  ├─ InstallScripts.json
│  │  ├─ Makefile.cmake
│  │  ├─ Makefile2
│  │  ├─ PlanetSystemDesigner.dir
│  │  │  ├─ DependInfo.cmake
│  │  │  ├─ PlanetSystemDesigner_autogen
│  │  │  │  ├─ mocs_compilation.cpp.o
│  │  │  │  └─ mocs_compilation.cpp.o.d
│  │  │  ├─ build.make
│  │  │  ├─ cmake_clean.cmake
│  │  │  ├─ commands
│  │  │  │  ├─ camera
│  │  │  │  │  ├─ CameraCommand.cpp.o
│  │  │  │  │  └─ CameraCommand.cpp.o.d
│  │  │  │  ├─ light
│  │  │  │  │  ├─ LightCommand.cpp.o
│  │  │  │  │  └─ LightCommand.cpp.o.d
│  │  │  │  └─ object
│  │  │  │     ├─ ObjectCommand.cpp.o
│  │  │  │     └─ ObjectCommand.cpp.o.d
│  │  │  ├─ compiler_depend.internal
│  │  │  ├─ compiler_depend.make
│  │  │  ├─ compiler_depend.ts
│  │  │  ├─ component
│  │  │  │  ├─ BaseObject.cpp.o
│  │  │  │  ├─ BaseObject.cpp.o.d
│  │  │  │  ├─ composite
│  │  │  │  │  ├─ Composite.cpp.o
│  │  │  │  │  └─ Composite.cpp.o.d
│  │  │  │  └─ primitive
│  │  │  │     ├─ invisible
│  │  │  │     │  ├─ camera
│  │  │  │     │  │  ├─ CameraAdapter.cpp.o
│  │  │  │     │  │  ├─ CameraAdapter.cpp.o.d
│  │  │  │     │  │  └─ default
│  │  │  │     │  │     ├─ DefaultCamera.cpp.o
│  │  │  │     │  │     └─ DefaultCamera.cpp.o.d
│  │  │  │     │  └─ light
│  │  │  │     │     ├─ default
│  │  │  │     │     │  ├─ DefaultLight.cpp.o
│  │  │  │     │     │  └─ DefaultLight.cpp.o.d
│  │  │  │     │     └─ impl
│  │  │  │     │        ├─ LightImpl.cpp.o
│  │  │  │     │        └─ LightImpl.cpp.o.d
│  │  │  │     └─ visible
│  │  │  │        └─ model
│  │  │  │           ├─ celestial
│  │  │  │           │  ├─ CelestialBody.cpp.o
│  │  │  │           │  └─ CelestialBody.cpp.o.d
│  │  │  │           └─ impl
│  │  │  │              ├─ parametric
│  │  │  │              │  ├─ ParametricSphereImpl.cpp.o
│  │  │  │              │  └─ ParametricSphereImpl.cpp.o.d
│  │  │  │              └─ tessellated
│  │  │  │                 ├─ TessellatedSphereImpl.cpp.o
│  │  │  │                 └─ TessellatedSphereImpl.cpp.o.d
│  │  │  ├─ depend.make
│  │  │  ├─ exceptions
│  │  │  │  ├─ BaseException.cpp.o
│  │  │  │  ├─ BaseException.cpp.o.d
│  │  │  │  ├─ camera
│  │  │  │  │  ├─ CameraException.cpp.o
│  │  │  │  │  └─ CameraException.cpp.o.d
│  │  │  │  ├─ composite
│  │  │  │  │  ├─ CompositeException.cpp.o
│  │  │  │  │  └─ CompositeException.cpp.o.d
│  │  │  │  ├─ managers
│  │  │  │  │  ├─ BaseManagerException.cpp.o
│  │  │  │  │  ├─ BaseManagerException.cpp.o.d
│  │  │  │  │  └─ camera
│  │  │  │  │     ├─ CameraManagerException.cpp.o
│  │  │  │  │     └─ CameraManagerException.cpp.o.d
│  │  │  │  ├─ matrix
│  │  │  │  │  ├─ MatrixException.cpp.o
│  │  │  │  │  └─ MatrixException.cpp.o.d
│  │  │  │  ├─ model
│  │  │  │  │  ├─ ModelException.cpp.o
│  │  │  │  │  └─ ModelException.cpp.o.d
│  │  │  │  ├─ scene
│  │  │  │  │  ├─ SceneException.cpp.o
│  │  │  │  │  └─ SceneException.cpp.o.d
│  │  │  │  └─ vector
│  │  │  │     ├─ VectorException.cpp.o
│  │  │  │     └─ VectorException.cpp.o.d
│  │  │  ├─ facade
│  │  │  │  ├─ Facade.cpp.o
│  │  │  │  └─ Facade.cpp.o.d
│  │  │  ├─ factories
│  │  │  │  └─ draw
│  │  │  │     └─ qt
│  │  │  │        ├─ QtDrawFactory.cpp.o
│  │  │  │        ├─ QtDrawFactory.cpp.o.d
│  │  │  │        └─ products
│  │  │  │           ├─ QtPainter.cpp.o
│  │  │  │           └─ QtPainter.cpp.o.d
│  │  │  ├─ flags.make
│  │  │  ├─ link.d
│  │  │  ├─ link.txt
│  │  │  ├─ main.cpp.o
│  │  │  ├─ main.cpp.o.d
│  │  │  ├─ managers
│  │  │  │  ├─ ManagerProvider.cpp.o
│  │  │  │  ├─ ManagerProvider.cpp.o.d
│  │  │  │  ├─ camera
│  │  │  │  │  ├─ CameraManager.cpp.o
│  │  │  │  │  └─ CameraManager.cpp.o.d
│  │  │  │  ├─ draw
│  │  │  │  │  ├─ DrawManager.cpp.o
│  │  │  │  │  └─ DrawManager.cpp.o.d
│  │  │  │  └─ scene
│  │  │  │     ├─ SceneManager.cpp.o
│  │  │  │     └─ SceneManager.cpp.o.d
│  │  │  ├─ progress.make
│  │  │  ├─ qt
│  │  │  │  └─ src
│  │  │  │     ├─ mainwindow.cpp.o
│  │  │  │     ├─ mainwindow.cpp.o.d
│  │  │  │     ├─ plane.cpp.o
│  │  │  │     └─ plane.cpp.o.d
│  │  │  ├─ scene
│  │  │  │  ├─ Scene.cpp.o
│  │  │  │  └─ Scene.cpp.o.d
│  │  │  ├─ strategies
│  │  │  │  ├─ conversion
│  │  │  │  │  └─ default
│  │  │  │  │     ├─ DefaultConvertCoordinatesStrategy.cpp.o
│  │  │  │  │     └─ DefaultConvertCoordinatesStrategy.cpp.o.d
│  │  │  │  ├─ projection
│  │  │  │  │  └─ default
│  │  │  │  │     ├─ DefaultProjectionStrategy.cpp.o
│  │  │  │  │     └─ DefaultProjectionStrategy.cpp.o.d
│  │  │  │  └─ render
│  │  │  │     └─ default
│  │  │  │        ├─ DefaultRenderStrategy.cpp.o
│  │  │  │        └─ DefaultRenderStrategy.cpp.o.d
│  │  │  └─ visitors
│  │  │     └─ draw
│  │  │        ├─ DrawVisitor.cpp.o
│  │  │        └─ DrawVisitor.cpp.o.d
│  │  ├─ PlanetSystemDesigner_autogen.dir
│  │  │  ├─ AutogenInfo.json
│  │  │  ├─ AutogenUsed.txt
│  │  │  ├─ DependInfo.cmake
│  │  │  ├─ ParseCache.txt
│  │  │  ├─ build.make
│  │  │  ├─ cmake_clean.cmake
│  │  │  ├─ compiler_depend.internal
│  │  │  ├─ compiler_depend.make
│  │  │  ├─ compiler_depend.ts
│  │  │  └─ progress.make
│  │  ├─ PlanetSystemDesigner_autogen_timestamp_deps.dir
│  │  │  ├─ DependInfo.cmake
│  │  │  ├─ build.make
│  │  │  ├─ cmake_clean.cmake
│  │  │  ├─ compiler_depend.make
│  │  │  ├─ compiler_depend.ts
│  │  │  └─ progress.make
│  │  ├─ TargetDirectories.txt
│  │  ├─ cmake.check_cache
│  │  ├─ pkgRedirects
│  │  └─ progress.marks
│  ├─ Makefile
│  ├─ PlanetSystemDesigner
│  ├─ PlanetSystemDesigner_autogen
│  │  ├─ KVXSJM6DYM
│  │  │  ├─ moc_mainwindow.cpp
│  │  │  ├─ moc_mainwindow.cpp.d
│  │  │  ├─ moc_plane.cpp
│  │  │  └─ moc_plane.cpp.d
│  │  ├─ deps
│  │  ├─ include
│  │  │  └─ ui_mainwindow.h
│  │  ├─ moc_predefs.h
│  │  ├─ mocs_compilation.cpp
│  │  └─ timestamp
│  ├─ cmake_install.cmake
│  └─ compile_commands.json
├─ commands
│  ├─ BaseCommand.h
│  ├─ camera
│  │  ├─ CameraCommand.cpp
│  │  └─ CameraCommand.h
│  ├─ light
│  │  ├─ LightCommand.cpp
│  │  └─ LightCommand.h
│  └─ object
│     ├─ ObjectCommand.cpp
│     └─ ObjectCommand.h
├─ component
│  ├─ BaseObject.cpp
│  ├─ BaseObject.h
│  ├─ composite
│  │  ├─ Composite.cpp
│  │  └─ Composite.h
│  └─ primitive
│     ├─ Primitive.h
│     ├─ invisible
│     │  ├─ InvisibleObject.h
│     │  ├─ camera
│     │  │  ├─ BaseCamera.h
│     │  │  ├─ CameraAdapter.cpp
│     │  │  ├─ CameraAdapter.h
│     │  │  ├─ default
│     │  │  │  ├─ DefaultCamera.cpp
│     │  │  │  └─ DefaultCamera.h
│     │  │  └─ impl
│     │  │     └─ CameraImpl.h
│     │  └─ light
│     │     ├─ BaseLight.h
│     │     ├─ default
│     │     │  ├─ DefaultLight.cpp
│     │     │  └─ DefaultLight.h
│     │     └─ impl
│     │        ├─ LightImpl.cpp
│     │        └─ LightImpl.h
│     └─ visible
│        ├─ VisibleObject.h
│        └─ model
│           ├─ BaseModel.h
│           ├─ celestial
│           │  ├─ CelestialBody.cpp
│           │  └─ CelestialBody.h
│           └─ impl
│              ├─ SphereImpl.h
│              ├─ parametric
│              │  ├─ ParametricSphereImpl.cpp
│              │  └─ ParametricSphereImpl.h
│              └─ tessellated
│                 ├─ TessellatedSphereImpl.cpp
│                 └─ TessellatedSphereImpl.h
├─ concepts
│  └─ concepts.h
├─ exceptions
│  ├─ BaseException.cpp
│  ├─ BaseException.h
│  ├─ camera
│  │  ├─ CameraException.cpp
│  │  └─ CameraException.h
│  ├─ composite
│  │  ├─ CompositeException.cpp
│  │  └─ CompositeException.h
│  ├─ managers
│  │  ├─ BaseManagerException.cpp
│  │  ├─ BaseManagerException.h
│  │  └─ camera
│  │     ├─ CameraManagerException.cpp
│  │     └─ CameraManagerException.h
│  ├─ scene
│  │  ├─ SceneException.cpp
│  │  └─ SceneException.h
│  └─ vector
│     ├─ VectorException.cpp
│     └─ VectorException.h
├─ facade
│  ├─ Facade.cpp
│  └─ Facade.h
├─ factories
│  ├─ draw
│  │  ├─ BaseDrawFactory.h
│  │  ├─ products
│  │  │  └─ BasePainter.h
│  │  └─ qt
│  │     ├─ QtDrawFactory.cpp
│  │     ├─ QtDrawFactory.h
│  │     └─ products
│  │        ├─ QtPainter.cpp
│  │        └─ QtPainter.h
│  └─ sphere
│     └─ SphereFactory.h
├─ main.cpp
├─ managers
│  ├─ ManagerProvider.cpp
│  ├─ ManagerProvider.h
│  ├─ camera
│  │  ├─ CameraManager.cpp
│  │  └─ CameraManager.h
│  ├─ draw
│  │  ├─ DrawManager.cpp
│  │  └─ DrawManager.h
│  └─ scene
│     ├─ SceneManager.cpp
│     └─ SceneManager.h
├─ materials
│  └─ Material.h
├─ qt
│  ├─ inc
│  │  ├─ mainwindow.h
│  │  └─ plane.h
│  └─ src
│     ├─ mainwindow.cpp
│     └─ plane.cpp
├─ scene
│  ├─ Scene.cpp
│  └─ Scene.h
├─ strategies
│  ├─ conversion
│  │  ├─ BaseCoordinateConvertStrategy.h
│  │  ├─ creator
│  │  │  ├─ ConvertCoordsStrategyCreator.h
│  │  │  └─ ConvertCoordsStrategyCreator.hpp
│  │  └─ default
│  │     ├─ DefaultConvertCoordinatesStrategy.cpp
│  │     └─ DefaultConvertCoordinatesStrategy.h
│  ├─ projection
│  │  ├─ BaseProjectionStrategy.h
│  │  ├─ creators
│  │  │  ├─ ProjectionStrategyCreator.h
│  │  │  └─ ProjectionStrategyCreator.hpp
│  │  └─ default
│  │     ├─ DefaultProjectionStrategy.cpp
│  │     └─ DefaultProjectionStrategy.h
│  └─ render
│     ├─ BaseRenderStrategy.h
│     ├─ creators
│     │  ├─ RenderStrategyCreator.h
│     │  └─ RenderStrategyCreator.hpp
│     └─ default
│        ├─ DefaultRenderStrategy.cpp
│        └─ DefaultRenderStrategy.h
├─ ui
│  └─ mainwindow.ui
├─ vector
│  ├─ Vec3.h
│  └─ Vec3.hpp
└─ visitors
   ├─ BaseVisitor.h
   ├─ creators
   │  ├─ VisitorCreator.h
   │  └─ VisitorCreator.hpp
   └─ draw
      ├─ DrawVisitor.cpp
      └─ DrawVisitor.h

```