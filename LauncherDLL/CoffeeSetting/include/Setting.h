#pragma once

/**
 * 세팅 관련 인터페이스.
 */
class ISetting
{
public:
    virtual ~ISetting() = 0;
public:
    virtual bool Load() = 0;
    virtual bool Save() = 0;


};
