#pragma once

#include "Flow/FlowNode.h"

#include <Matrix3x4.h>

namespace Nome::Scene
{

using tc::Vector3;
using tc::Quaternion;
using tc::Matrix3x4;

class CTransform : public Flow::CFlowNode
{
public:
};

class CTranslate : public CTransform
{
public:
    DEFINE_INPUT(Matrix3x4, Input)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, X)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, Y)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, Z)
    {
        Output.MarkDirty();
    }

    DEFINE_OUTPUT_WITH_UPDATE(Matrix3x4, Output)
    {
        RecomputeOutput();
    }

private:
    void RecomputeOutput();
};

class CRotate : public CTransform
{
public:
    DEFINE_INPUT(Matrix3x4, Input)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, AxisX)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, AxisY)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, AxisZ)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, Angle)
    {
        Output.MarkDirty();
    }

    DEFINE_OUTPUT_WITH_UPDATE(Matrix3x4, Output)
    {
        RecomputeOutput();
    }

private:
    void RecomputeOutput();
};

class CScale : public CTransform
{
public:
    DEFINE_INPUT(Matrix3x4, Input)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, X)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, Y)
    {
        Output.MarkDirty();
    }

    DEFINE_INPUT(float, Z)
    {
        Output.MarkDirty();
    }

    DEFINE_OUTPUT_WITH_UPDATE(Matrix3x4, Output)
    {
        RecomputeOutput();
    }

private:
    void RecomputeOutput();
};

}