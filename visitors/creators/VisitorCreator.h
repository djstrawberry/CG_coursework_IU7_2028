#pragma once

#include "../../concepts/concepts.h"
#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../../strategies/conversion/BaseCoordinateConvertStrategy.h"
#include "../../factories/draw/products/BasePainter.h"
#include "../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../vector/Vec3.h"
#include "../draw/DrawVisitor.h"
#include "../BaseVisitor.h"
#include <memory>

template <typename BaseVisitorT, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitorT>
          && ConstructibleWith<DerivedVisitor, Args...>
class VisitorCreator
{
public:
    VisitorCreator() = default;
    ~VisitorCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseVisitorT> create(CallArgs &&...args)
    {
        return std::make_shared<DerivedVisitor>(std::forward<CallArgs>(args)...);
    }
};

#include "VisitorCreator.hpp"

using DrawVisitorCreator = VisitorCreator<
    BaseVisitor,
    DrawVisitor,
    std::shared_ptr<BaseProjectionStrategy>,
    std::shared_ptr<BaseCoordinateConvertStrategy>,
    std::shared_ptr<BasePainter>,
    std::shared_ptr<CameraImpl>,
    const float*,
    Vec3<double>
>;