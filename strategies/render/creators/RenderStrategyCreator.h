#pragma once

#include "../../../concepts/concepts.h"
#include "../BaseRenderStrategy.h"
#include "../default/DefaultRenderStrategy.h"
#include <memory>

template <typename BaseRenderStrategyT, typename DerivedRenderStrategy, typename... Args>
requires Derivative<DerivedRenderStrategy, BaseRenderStrategyT>
         && ConstructibleWith<DerivedRenderStrategy, Args...>
class RenderStrategyCreator
{
public:
    RenderStrategyCreator() = default;
    ~RenderStrategyCreator() = default;

    template <typename... CallArgs>
    requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseRenderStrategyT> create(CallArgs &&...args)
    {
        return std::make_shared<DerivedRenderStrategy>(std::forward<CallArgs>(args)...);
    }
};

#include "RenderStrategyCreator.hpp"

using DefaultRenderStrategyCreator = RenderStrategyCreator<BaseRenderStrategy, DefaultRenderStrategy>;