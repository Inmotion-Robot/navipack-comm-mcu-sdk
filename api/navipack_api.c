/**
******************************************************************************
* @file    navipack_api.c
* @author  Jalon
* @date    2016.07.01
* @brief   通讯协议接口，该文件在移植过程中需要根据实际情况更改，
           部分函数需要用户实现
* @attention Copyright (C) 2016 Inmotion Corporation
******************************************************************************
*/

/** @addtogroup Navipack_MCU_SDK
* @{
*/

/** @defgroup MCU_SDK_API SDK API
* @brief Navipack MCU SDK API
* @{
*/

#include "navipack_api.h"

// TODO: 引入需要的头文件

/**
* @brief  初始化
* @retval 是否成功
*/
bool NaviPack_Init(void)
{
    // TODO: 用户可添加初始化处理
    return true;
}

/**
* @brief  通讯接收数据处理函数
* @param  comm : 通讯对象
* @param  data : 接收数据，1 byte
* @retval 是否成功处理了数据包
*/
bool NaviPack_RxProcessor(NavipackComm_Type *comm, u8 data)
{
    return NaviPack_SessionRxProcessor(comm, data);
}

/**
* @brief  接收到合法的寄存器请求时回调
* @param  comm : 通讯结构指针
* @param  head : 数据头指针
* @retval 是否处理了请求
*/
bool Navipack_RxCallback(NavipackComm_Type *comm, NaviPack_HeadType *head)
{
    switch(head->functionCode)
    {
    case FUNC_ID_READ_STATUS:
    case FUNC_ID_READ_CONTROL:
    case FUNC_ID_READ_CONFIG:
    case FUNC_ID_READ_USER:
        // TODO: 如果发送和接收不是同一个线程，则应改成通知发送线程调用该发送函数
        NaviPack_TxProcessor(comm, head);
        break;
    case FUNC_ID_WRITE_CONTROL:
        // TODO: 获得接收到的新值
        // comm->control.lineVelocity
        // comm->control.angularVelocity
        break;
    case FUNC_ID_WRITE_USER:
        // TODO: 写用户寄存器
        // RegisterWrite(head, (u8*)&UserReg, sizeof(UserReg), REG_ID_USER);
        break;
    default:
        return false;
    }
    return true;
}

/**
* @brief  通讯发送数据处理函数
* @param  comm : 通讯对象
* @param  head : 数据头指针
* @retval 是否成功处理了数据包
*/
bool NaviPack_TxProcessor(NavipackComm_Type *comm, NaviPack_HeadType *head)
{
    switch(head->functionCode)
    {
    case FUNC_ID_READ_USER:
        // TODO: 用户寄存器数据发送
        // RegisterRead(comm, head, 0, (u8*)&UserReg, sizeof(UserReg), REG_ID_USER);
        break;
    case FUNC_ID_READ_STATUS:
        return RegisterRead(comm, head, 0, (u8*)&comm->status, sizeof(comm->status), REG_ID_STATUS);
    case FUNC_ID_READ_CONTROL:
        return RegisterRead(comm, head, 0, (u8*)&comm->control, sizeof(comm->control), REG_ID_COTROL);
    case FUNC_ID_READ_CONFIG:
        return RegisterRead(comm, head, 0, (u8*)&comm->config, sizeof(comm->config), REG_ID_CONFIG);
    }
    
    return false;
}

/**
* @brief  实际发送数据的函数
* @param  pbuf : 数据指针
* @param  len  : 数据长度
* @retval 是否成功发送
*/
bool Navipack_TxCallback(u8* pbuf, u16 len)
{
    // TODO: 用户添加实际发送数据的处理，如发送到串口
}

/**
* @brief  实际发送数据的函数
* @param  head : 数据头指针
* @param  len  : 数据内容长度
* @retval 是否成功发送
*/
bool Navipack_CheckLength(NaviPack_HeadType *head, u16 len)
{
    return (head->functionCode != FUNC_ID_WRITE_CONTROL && head->functionCode != FUNC_ID_WRITE_USER) 
            || head->len == len - sizeof(NaviPack_HeadType);
}

/**
* @brief  寄存器操作上锁
* @param  reg_id : 寄存器 id，指示需要上锁的寄存器
* @retval 是否成功上锁
*/
bool Navipack_LockReg(u8 reg_id)
{
    // TODO: 上锁处理，若无多线程操作可留空
    switch(reg_id)
    {
    case REG_ID_STATUS:
        break;
    case REG_ID_COTROL:
        break;
    case REG_ID_CONFIG:
        break;
    case REG_ID_USER:
        break;
    default:
        return false;
    }
    
    return true;
}

/**
* @brief  寄存器操作解锁
* @param  reg_id : 寄存器 id，指示需要解锁的寄存器
* @retval None
*/
void Navipack_UnlockReg(u8 reg_id)
{
    // TODO: 解锁处理，若无多线程操作可留空
    switch(reg_id)
    {
    case REG_ID_STATUS:
        break;
    case REG_ID_COTROL:
        break;
    case REG_ID_CONFIG:
        break;
    case REG_ID_USER:
        break;
    default:
        break;
    }
}

/**
* @}
*/

/**
* @}
*/
