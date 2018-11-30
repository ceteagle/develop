#pragma once

const int NAS_COMMAND_LENGTH = 4;

enum eFECommandsType
{
    eFECommandsProcessed = 1 << 0,
    eFECommandsUnProcessed = 1 << 1,
    eFECommandsAll = eFECommandsProcessed | eFECommandsUnProcessed
};

enum FieldDataType
{
    FieldDataTypeUndefined,
    FieldDataTypeInt,
    FieldDataTypeDouble,
    FieldDataTypeString
};
