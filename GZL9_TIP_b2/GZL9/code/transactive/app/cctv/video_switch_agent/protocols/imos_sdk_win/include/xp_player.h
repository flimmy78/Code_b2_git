 /*******************************************************************************
 Copyright (c) 2008, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              xp_player.h

  Project Code: IMOS通用媒体播放器
   Module Name: IMOS通用媒体播放器
  Date Created: 2010-07-12
        Author: shiyouhua/04562
   Description: IMOS通用媒体播放器XP接口头文件。XP：x-player通用播放器

--------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
  YYYY-MM-DD

*******************************************************************************/
#ifndef _IMOS_XP_PLAYER_H_
#define _IMOS_XP_PLAYER_H_

/* 包含IMOS基础平台的头文件 */
#include "imos_public.h"
#include "imos_errcode.h"
#include "imos_def.h"

/* 包含通用媒体播放器SDK数据结构头文件 */
#include "xp_datatype.h"

#ifdef  __cplusplus
extern "C"{
#endif

/** 编译选项 */
#if defined(WIN32)
    #if defined(XP_PLAYER_DLL_EXPORTS)
        #define IMOS_XP_PLAYER_EXPORT  __declspec( dllexport )
    #else
        #define IMOS_XP_PLAYER_EXPORT  __declspec( dllimport )
    #endif
#else
    #define IMOS_XP_PLAYER_EXPORT
#endif

/** 厂商标识 */
#define XP_DECODERTAG_H3C_V1       "h3c-v1"          /**< H3C V1版本 */
#define XP_DECODERTAG_H3C_V3       "h3c-v3"          /**< H3C V3版本，TS封装流 */
#define XP_DECODERTAG_H3C_V3_20    "h3c-v3@20"       /**< H3C V3版本，RTP + TS */
#define XP_DECODERTAG_H3C_V3_31    "h3c-v3@31"       /**< H3C V3版本，RTP + ES */
#define XP_DECODERTAG_HIK_SELF     "hikvision-self"  /**< 海康SELF */
#define XP_DECODERTAG_HIK_V1       "hikvision-v1"    /**< 海康V1版本 */
#define XP_DECODERTAG_HIK_V3       "hikvision-v3"    /**< 海康V3版本 */
#define XP_DECODERTAG_DAHUA_SELF   "dahua-self"      /**< 大华SELF */
#define XP_DECODERTAG_DAHUA_V1     "dahua-v1"        /**< 大华V1版本 */
#define XP_DECODERTAG_DAHUA_V3     "dahua-v3"        /**< 大华V3版本 */
#define XP_DECODERTAG_AXIS_V4      "axis-v4"         /**< Axis 4.00版本(Firmware版本) */
#define XP_DECODERTAG_AXIS_V5      "axis-v5"         /**< Axis 5.00版本(Firmware版本) */
#define XP_DECODERTAG_ALEC         "alec"            /**< 艾立克 */
#define XP_DECODERTAG_MOBOTIX      "mobotix"         /**< mobotix */
#define XP_DECODERTAG_APROUD_ONU   "aproud-onu"      /**< 亚邦老系统 */
#define XP_DECODERTAG_APROUD_OEM   "aproud-sivx"     /**< 亚邦OEM系统 */
#define XP_DECODERTAG_YAAN_V3      "yaan-v3"         /**< 亚安 */
#define XP_DECODERTAG_SONY         "sony"            /**< 索尼 */
#define XP_DECODERTAG_SAMSUNG      "samsung"         /**< 三星 */
#define XP_DECODERTAG_RUIMING      "ruiming"         /**< 锐明V3版本 */
#define XP_DECODERTAG_RUIMING_SELF "ruiming-self"    /**< 锐明SELF */
#define XP_DECODERTAG_NANZI        "nanzi"           /**< 南自 */

/**
* @enum tagXpLogLevel
* @brief 运行日志等级枚举类型
* @attention 无
*/
typedef enum tagXpLogLevel
{
    XP_DEBUG = 1,               /**< debug级别 */
    XP_INFO  = 2,               /**< info级别 */
    XP_WARN  = 3,               /**< warn级别 */
    XP_ERROR = 4,               /**< error级别 */
    XP_FATAL = 5                /**< fatal级别 */
}XP_LOGLEVEL_E;

/**
* @enum tagMediaPlayerRunInfoType
* @brief 独立播放器上报运行信息的类型的枚举定义
* @attention 无
*/
typedef enum tagMediaPlayerRunInfoType
{
    XP_PLAYER_RUN_INFO_RECORD_VIDEO  = 0,          /**< 本地录像过程中上报运行信息 */
    XP_PLAYER_RUN_INFO_MEDIA_PROCESS = 1,          /**< 视频媒体处理过程中的上报运行信息 */
    XP_PLAYER_RUN_INFO_SERIES_SNATCH = 2,          /**< 连续抓拍过程中上报运行信息 */
    XP_PLAYER_RUN_INFO_MEDIA_VOICE = 3             /**< 语音业务过程中上报运行信息 */
}XP_MEDIA_PLAYER_RUN_INFO_TYPE_E;

/**
* @struct tagRunInfo
* @brief 上报消息的结构体定义。
* @attention 无
*/
typedef struct tagPlayerRunInfo
{
    ULONG ulPort;                               /**< 媒体流处理通道ID */
    ULONG ulErrCode;                            /**< 上报的错误码 */
}PLAYER_RUN_INFO_S;

/**
* 记录日志的回调函数类型定义 \n
* @param [IN] ulLogLevel        日志级别, 对应#XP_LOGLEVEL_E枚举中的值。
* @param [IN] ulErrCode         日志信息错误码。
* @param [IN] ulCmdModuleID     命令行模块ID。
* @param [IN] pcFileName        代码文件名。
* @param [IN] ulFileLine        代码所在行数。
* @param [IN] pcLogDescription  日志描述字符串。
* @return VOID
* @note
* -    1、播放器内部记录日志级别。
* -    2、播放器内部多线程调用该回调函数，用户记录日志处理中需要做线程同步处理。
* -    3、播放器内部输出的日志描述字符串末尾没有带"\r\n"符。用户在写日志文件的时候需要做换行处理。
*/
typedef VOID (STDCALL* XP_WRITE_LOG_CALLBACK_PF)(IN ULONG ulLogLevel,
                                                 IN ULONG ulErrCode,
                                                 IN ULONG ulCmdModuleID,
                                                 IN const CHAR *pcFileName,
                                                 IN ULONG ulFileLine,
                                                 IN const CHAR *pcLogDescription);

/**
* 消息或异常消息回调函数的指针类型。\n
* @param [IN] enRunInfoType 消息或者异常消息类型，对应#XP_MEDIA_PLAYER_RUN_INFO_TYPE_E枚举中的值。
* @param [IN] pParam        存放消息或异常消息数据的缓冲区指针（所存放的数据与消息或异常消息类型有关）
* @return VOID
* @note
* -     1、用户需要确保该回调函数尽快返回。
* -     2、用户不允许在该回调函数中调用播放器SDK的任何接口函数。
* -     3、参数pParam所指的缓冲区中存放的数据的类型视消息或者异常消息类型而定，用户需要根据消息或者异常消息类型对其做类型转换。
* -        当ulRunInfoType值为 XP_RUN_INFO_RECORD_VIDEO
                               XP_RUN_INFO_MEDIA_PROCESS
                               XP_PLAYER_RUN_INFO_SERIES_SNATCH
                               XP_PLAYER_RUN_INFO_MEDIA_VOICE时，用户需将pParam转换为#PLAYER_RUN_INFO_S结构体类型指针。
*/
typedef VOID (STDCALL* XP_PLAYER_RUN_INFO_CALLBACK_PF)(IN ULONG ulRunInfoType,
                                                       IN VOID *pParam);

/**
* 拼帧前媒体流数据回调函数的指针类型。\n
* @param [IN] ulPort           播放通道号
* @param [IN] pucBuffer        存放拼帧前媒体流数据缓冲区指针
* @param [IN] ulBufSize        缓冲区大小
* @param [IN] ulMediaDataType  媒体数据类型，参见媒体类型枚举定义#XP_MEDIA_DATA_FORMAT_E
* @param [IN] lUserParam       用户设置参数，即客户在调用IMOS_XP_SetSourceMediaDataCB函数时指定的用户参数
* @param [IN] lReserved        存放拼帧前媒体流扩展信息缓冲区指针，用户需要转换为#XP_SOURCE_DATA_EX_INFO_S
*                              结构体指针类型，内含解码器标签（DecoderTag），当用户使用播放库解码和显示回调
*                              的媒体流时，可根据解码器标签指定解码器。
* @return 无。
* @note  客户应及时处理输出的媒体流数据，确保函数尽快返回，否则会影响播放器内的媒体流处理。
*/
typedef VOID (STDCALL* XP_PLAYER_SOURCE_MEDIA_DATA_CALLBACK_PF)(IN ULONG ulPort,
                                                                IN const UCHAR *pucBuffer,
                                                                IN ULONG ulBufSize,
                                                                IN ULONG ulMediaDataType,
                                                                IN LONG lUserParam,
                                                                IN LONG lReserved);

/**
* 拼帧后视频流数据回调函数的指针类型。\n
* @param [IN] ulPort                播放通道号
* @param [IN] pstParseVideoData     存放拼帧后视频流数据信息缓冲区指针
* @param [IN] lUserParam            用户设置参数，即客户在调用IMOS_XP_SetParseVideoDataCB函数时指定的用户参数
* @param [IN] lReserved             保留参数
* @return 无。
* @note
* -     客户应及时处理输出的数据，确保函数尽快返回，否则会影响播放器内的媒体流处理。
*/
typedef VOID (STDCALL *XP_PLAYER_PARSE_VIDEO_DATA_CALLBACK_PF)(IN ULONG ulPort,
                                                               IN const XP_PARSE_VIDEO_DATA_S *pstParseVideoData,
                                                               IN LONG lUserParam,
                                                               IN LONG lReserved);

/**
* 拼帧后音频流数据回调函数的指针类型。\n
* @param [IN] ulPort                播放通道号
* @param [IN] pstParseAudioData     存放拼帧后音频流数据信息缓冲区指针
* @param [IN] lUserParam            用户设置参数，即客户在调用IMOS_XP_SetParseAudioDataCB函数时指定的用户参数
* @param [IN] lReserved             保留参数
* @return 无。
* @note
* -     客户应及时处理输出的数据，确保函数尽快返回，否则会影响播放器内的媒体流处理。
*/
typedef VOID (STDCALL *XP_PLAYER_PARSE_AUDIO_DATA_CALLBACK_PF)(IN ULONG ulPort,
                                                               IN const XP_PARSE_AUDIO_DATA_S *pstParseAudioData,
                                                               IN LONG lUserParam,
                                                               IN LONG lReserved);

/**
* 解码后视频流数据回调函数的指针类型。\n
* @param [IN] ulPort         播放通道号
* @param [IN] pPictureData   存放解码后视频流数据信息缓冲区指针
* @param [IN] lUserParam     用户设置参数，即客户在调用IMOS_XP_SetDecodeVideoDataCB函数时指定的用户参数
* @param [IN] lReserved      保留参数
* @return 无。
* @note
* -     客户应及时处理输出的视频流数据，确保函数尽快返回，否则会影响播放器内的媒体流处理。
*/
typedef VOID (STDCALL* XP_PLAYER_DECODE_VIDEO_DATA_CALLBACK_PF)(IN ULONG ulPort,
                                                                IN const XP_PICTURE_DATA_S *pPictureData,
                                                                IN LONG lUserParam,
                                                                IN LONG lReserved);

/**
* 解码后音频流数据回调函数的指针类型。\n
* @param [IN] ulPort         播放通道号
* @param [IN] pWaveData      存放解码后音频流数据信息缓冲区指针
* @param [IN] lUserParam     用户设置参数，即客户在调用IMOS_XP_SetDecodeAudioDataCB函数时指定的用户参数
* @param [IN] lReserved      保留参数
* @return 无。
* @note
* -     客户应及时处理输出的音频流数据，确保函数尽快返回，否则会影响播放器内的媒体流处理。
*/
typedef VOID (STDCALL* XP_PLAYER_DECODE_AUDIO_DATA_CALLBACK_PF)(IN ULONG ulPort,
                                                                IN const XP_WAVE_DATA_S *pWaveData,
                                                                IN LONG lUserParam,
                                                                IN LONG lReserved);

/**
* 注册播放器内运行日志的回调函数。\n
* @param [IN] pfnWriteLogFunc 播放器内运行日志回调函数指针。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* @note
* -    1、为了防止日志信息记录遗漏，用户应在调用播放器其他接口函数之前调用该函数。
* -    2、如果用户不调用该函数设置运行日志的回调函数，则播放器内部不记录任何日志信息。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetWriteLogCB(IN XP_WRITE_LOG_CALLBACK_PF pfnWriteLogFunc);

/**
* 设置播放器库所在的根目录路径。\n
* @param [IN] pcRootPath 播放器库所在的根目录路径。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* @note 
*      1、该接口需要在IMOS_XP_Init之前调用。
*      2、如果用户不调用该函数设置播放器库所在的根目录路径，则播放器内部默认采用当前应用程序的运行路径。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPlayerRootPath(IN const CHAR *pcRootPath);

/**
* 初始化播放器SDK资源。\n
* @param [IN] 无。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_XP_FAIL_TO_INIT_XP          初始化播放器资源失败
* @note 
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_Init();

/**
* 释放播放器SDK资源，在结束使用播放器SDK之前最后调用。\n
* @param [IN] 无。
* @return 无
*/
IMOS_XP_PLAYER_EXPORT VOID STDCALL IMOS_XP_Cleanup();

/**
* 注册消息或异常消息回调函数。\n
* @param [IN] pfRunInfoFunc 消息或异常消息回调函数指针。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* @note 不允许在设置给播放器库的回调函数中调用播放器库接口。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPlayerRunMsgCB(IN XP_PLAYER_RUN_INFO_CALLBACK_PF pfnRunInfoFunc);

/**
* 设置视频显示模式。\n
* @param [IN] ulRenderMode 视频显示模式，需从#XP_RENDER_MODE_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* @note 
* -  1、该接口在IMOS_XP_Init之后调用，设置的视频显示模式将对所有播放通道起作用。
*    2、如果客户不调用该函数设置视频显示模式，则播放器内部默认使用D3D的显示模式。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetRenderMode(IN ULONG ulRenderMode);

/**
* 设置视频像素格式。\n
* @param [IN] ulPixelFormat 视频像素格式，需从#XP_PIXEL_FORMAT_EX_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* @note
* - 1、该接口在IMOS_XP_Init之后调用，设置的视频像素格式将对所有播放通道起作用。
* - 2、如果客户不调用该函数设置视频像素格式，则播放器内部默认使用YUV420视频像素格式。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPixelFormat(IN ULONG ulPixelFormat);

/**
* 打开本地播放文件。\n
* @param [IN] ulPort        播放通道号。
* @param [IN] pcFileName    本地文件的文件名（包括文件路径）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_PORT_NOT_AVAILABLE           播放通道不可用
* -         #ERR_COMMON_NO_MEMORY                系统内存不足
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道的资源失败
* -         #ERR_XP_NOT_SUPPORT_FILE_FORMAT      文件播放格式不支持
* -         #ERR_XP_FAIL_TO_GET_TOTAL_TIME       获得文件总的播放时间失败
* -         #ERR_XP_FAIL_TO_OPEN_FILE            启动本地文件播放失败(文件不存在或者正在被其他程序使用)
* -         #ERR_XP_FILE_DESTROY                 需要打开的文件太小或者已经损坏
* -         #ERR_XP_FILE_HAVE_OPEN               指定通道已经打开了文件
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_OpenFile(IN ULONG ulPort,
                                                     IN const CHAR *pcFileName);

/**
* 获得文件总的时间长度。\n
* @param [IN] ulPort        播放通道号。
* @param [OUT] pulTotalTime 存放文件总的时间长度的指针（单位为秒）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetFileTime(IN ULONG ulPort, 
                                                        OUT ULONG *pulTotalTime);

/**
* 关闭本地播放文件。\n
* @param [IN] ulPort        播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_CLOSE_FILE           关闭本地文件回放业务失败
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_CloseFile(IN ULONG ulPort);

/**
* 打开网络流数据播放。\n
* @param [IN] ulPort          播放通道号。
* @param [IN] pcLocalIP       本地IP地址。
* @param [IN] usLocalPort     本地监听端口。
* @param [IN] pcRemoteIP      远端IP地址。
* @param [IN] usRemotePort    远端端口。
* @param [IN] ulTransProtl    接收媒体流的传输层协议，需从#XP_PROTOCOL_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES     获得播放通道资源失败
* -         #ERR_XP_PORT_NOT_AVAILABLE       播放通道不可用
* -         #ERR_COMMON_NO_MEMORY            系统内存不足
* -         #ERR_XP_FAIL_TO_OPEN_STREAM      启动媒体流播放业务失败
* @note 
* -    1、目前仅支持UDP协议接收媒体数据流。
* -    2、该函数支持单播和组播两种方式。单播时，如果使用本地默认的IP地址，则本地IP地址传入空字符串即可，
* -       此时，远端的IP地址和端口可用于对接收到的数据包进行校验、过滤，防止串流，如果用户不需要防止串流，
* -       则可将远端IP地址和端口分别填写为“0.0.0.0”和0；组播时，远端的IP地址和端口必须填写组播地址和端口，
* -       此时，本地IP地址也必须要填写一个真实有效的本地IP地址，而本地端口可以填写任意值(不使用)。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_OpenNetStream(IN ULONG ulPort,
                                                          IN const CHAR *pcLocalIP,
                                                          IN USHORT usLocalPort,
                                                          IN const CHAR *pcRemoteIP,
                                                          IN USHORT usRemotePort,
                                                          IN ULONG ulTransProtl);

/**
* 关闭网络流数据播放。\n
* @param [IN] ulPort       播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_CLOSE_STREAM         关闭媒体流播放失败
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_CloseNetStream(IN ULONG ulPort);

/**
* 打开输入流数据播放。\n
* @param [IN] ulPort           播放通道号。
* @param [IN] pucFileHeadBuf   文件头数据。
* @param [IN] ulSize           文件头长度。
* @param [IN] ulBufPoolSize    设置播放器中存放媒体数据流的缓冲区大小。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_PORT_NOT_AVAILABLE               播放通道不可用
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_COMMON_NO_MEMORY                    系统内存不足
* -         #ERR_XP_FAIL_TO_OPEN_STREAM              启动输入流播放业务失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_OpenInputStream(IN ULONG ulPort,
                                                            IN const UCHAR *pucFileHeadBuf,
                                                            IN ULONG ulSize,
                                                            IN ULONG ulBufPoolSize);

/**
* 输入流数据；打开输入流后才能输入数据。\n
* @param [IN] ulPort          播放通道号。
* @param [IN] pucDataBuf      流数据缓冲区地址。
* @param [IN] ulDataLen       流数据缓冲区长度。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_PORT_NOT_OPEN                    通道未打开媒体业务
* -         #ERR_COMMON_NO_MEMORY                    系统内存不足
* -         #ERR_XP_FAIL_TO_INPUT_DATA               码流输入失败
* -         #ERR_XP_INPUTDATA_BUFFER_FULL            缓冲区满，码流输入失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_InputMediaData(IN ULONG ulPort,
                                                           IN const UCHAR *pucDataBuf,
                                                           IN ULONG ulDataLen);

/**
* 关闭输入流数据播放。\n
* @param [IN] ulPort    播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_CLOSE_STREAM             关闭媒体流播放失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_CloseInputStream(IN ULONG ulPort);

/**
* 设置播放图像流畅性或实时性。\n
* @param [IN] ulPort        播放通道号。
* @param [IN] ulFluency     播放图像是实时性优先还是流畅性优先，需从#XP_PICTURE_FLUENCY_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                    成功
* -         #ERR_COMMON_INVALID_PARAM              输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES           获得播放通道资源失败
* @note 
* - 1、该函数用于设置网络流和输入流播放时图像的流畅性，对本地文件回放时图像进行设置将不起作用；
*      且需要在IMOS_XP_StartPlay之前调用，设置仅对指定通道有效。
* - 2、如果用户不调用该函数设置播放图像流畅性，则播放器内部默认使用图像实时性优先；
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPictureFluency(IN ULONG ulPort,
                                                              IN ULONG ulFluency);

/**
* 设置拼帧前媒体流数据回调函数。\n
* @param [IN] ulPort                  播放通道号。
* @param [IN] pfnSourceMediaDataCBFun 拼帧前媒体流数据回调函数的指针。
* @param [IN] bContinue               是否继续进行后面的拼帧、解码和显示操作。
* @param [IN] lUserParam              用户设置参数。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_SET_PROCESS_DATA_CB      设置媒体流数据回调函数失败
* @note 
*      1、该函数在IMOS_XP_StartPlay之前或之后调用，在IMOS_XP_StopPlay时自动失效。
*      2、回调函数要尽快返回，如果要停止回调，可以把回调函数指针设为NULL。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetSourceMediaDataCB(IN ULONG ulPort,
                                                                 IN XP_PLAYER_SOURCE_MEDIA_DATA_CALLBACK_PF pfnSourceMediaDataCBFun,
                                                                 IN BOOL_T bContinue,
                                                                 IN LONG lUserParam);

/**
* 设置拼帧后视频数据回调函数。\n
* @param [IN] ulPort                    播放通道号。
* @param [IN] pfnParseVideoDataCBFun    拼帧后视频数据回调函数的指针。
* @param [IN] bContinue                 是否继续进行解码和显示操作。
* @param [IN] lUserParam                用户设置参数。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_SET_PROCESS_DATA_CB      设置媒体流数据回调函数失败
* @note 
*      1、该函数在IMOS_XP_StartPlay之前或之后调用，在IMOS_XP_StopPlay时自动失效。
*      2、回调函数要尽快返回，如果要停止回调，可以把回调函数指针设为NULL。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetParseVideoDataCB(IN ULONG ulPort,
                                                                IN XP_PLAYER_PARSE_VIDEO_DATA_CALLBACK_PF pfnParseVideoDataCBFun,
                                                                IN BOOL_T bContinue,
                                                                IN LONG lUserParam);

/**
* 设置拼帧后音频数据回调函数。\n
* @param [IN] ulPort                    播放通道号。
* @param [IN] pfnParseAudioDataCBFun    拼帧后音频数据回调函数的指针。
* @param [IN] bContinue                 是否继续进行解码和播放操作。
* @param [IN] lUserParam                用户设置参数。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_SET_PROCESS_DATA_CB      设置媒体流数据回调函数失败
* @note 
*      1、该函数在IMOS_XP_StartPlay之前或之后调用，在IMOS_XP_StopPlay时自动失效。
*      2、回调函数要尽快返回，如果要停止回调，可以把回调函数指针设为NULL。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetParseAudioDataCB(IN ULONG ulPort,
                                                                IN XP_PLAYER_PARSE_AUDIO_DATA_CALLBACK_PF pfnParseAudioDataCBFun,
                                                                IN BOOL_T bContinue,
                                                                IN LONG lUserParam);

/**
* 设置解码后视频媒体流数据回调函数。\n
* @param [IN] ulPort                    播放通道号。
* @param [IN] pfnDecodeVideoDataCBFun   解码后视频媒体流数据回调函数的指针。
* @param [IN] bContinue                 是否继续进行后面的显示操作。
* @param [IN] lUserParam                用户设置参数。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_SET_PROCESS_DATA_CB      设置媒体流数据回调函数失败
* @note 
*      1、该函数在IMOS_XP_StartPlay之前或之后调用，在IMOS_XP_StopPlay时自动失效。
*      2、回调函数要尽快返回，如果要停止回调，可以把回调函数指针设为NULL。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetDecodeVideoMediaDataCB(IN ULONG ulPort,
                                                                      IN XP_PLAYER_DECODE_VIDEO_DATA_CALLBACK_PF pfnDecodeVideoDataCBFun,
                                                                      IN BOOL_T bContinue,
                                                                      IN LONG lUserParam);

/**
* 设置解码后音频媒体流数据回调函数。\n
* @param [IN] ulPort                    播放通道号。
* @param [IN] pfnDecodeAudioDataCBFun   解码后音频媒体流数据回调函数的指针。
* @param [IN] bContinue                 是否继续进行后面的播放操作。
* @param [IN] lUserParam                用户设置参数。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_SET_PROCESS_DATA_CB      设置媒体流数据回调函数失败
* @note 
*      1、该函数在IMOS_XP_StartPlay之前或之后调用，在IMOS_XP_StopPlay时自动失效。
*      2、回调函数要尽快返回，如果要停止回调，可以把回调函数指针设为NULL。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetDecodeAudioMediaDataCB(IN ULONG ulPort,
                                                                      IN XP_PLAYER_DECODE_AUDIO_DATA_CALLBACK_PF pfnDecodeAudioDataCBFun,
                                                                      IN BOOL_T bContinue,
                                                                      IN LONG lUserParam);

/**
* 设置通道解码器的厂商标识。\n
* @param [IN] ulPort        播放通道号。
* @param [IN] pcDecoderTag  通道解码器的厂商标识，需从XP_DECODERTAG_XXXX一类的宏定义中取值。如XP_DECODERTAG_H3C_V3
*                           是H3C V3版本的标识，设置了该标识的播放通道将使用H3C V3版本的解码器。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                 成功
* -         #ERR_COMMON_INVALID_PARAM           输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES        获得播放窗口的资源失败
* @note 如果用户没有调用该函数设置指定通道解码器的厂商标识，则该通道默认使用H3C V3版本的解码器。     
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetDecoderTag(IN ULONG ulPort,
                                                          IN const CHAR *pcDecoderTag);

/**
* 获得通道解码器的厂商标识。\n
* @param [IN] ulPort         播放通道号。
* @param [OUT] pcDecoderTag  通道解码器的厂商标识，长度为#IMOS_STRING_LEN_32
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                 成功
* -         #ERR_COMMON_INVALID_PARAM           输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES        获得播放窗口的资源失败
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetDecoderTag(IN ULONG ulPort,
                                                          OUT CHAR *pcDecoderTag);

/**
* 设置播放视频的窗口句柄。\n
* @param [IN] ulPort    播放通道号。
* @param [IN] hWnd      播放窗口句柄。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPlayWnd(IN ULONG ulPort,
                                                       IN IMOS_HANDLE hWnd);

/**
* 开始播放。\n
* @param [IN] ulPort    播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_COMMON_NO_MEMORY                系统内存不足
* -         #ERR_XP_PORT_NOT_OPEN                通道未打开媒体业务
* -         #ERR_XP_FAIL_TO_START_PLAY           开始播放失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StartPlay(IN ULONG ulPort);

/**
* 暂停播放。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_FAIL_TO_PAUSE_MEDIA          暂停媒体播放处理失败
* -         #ERR_XP_FAIL_TO_PAUSE                暂停播放操作失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_PausePlay(IN ULONG ulPort);

/**
* 恢复播放，恢复播放已暂停的通道。\n
* @param [IN] ulPort    播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_FAIL_TO_RESUME_MEDIA         恢复媒体播放处理失败
* -         #ERR_XP_FAIL_TO_RESUME               恢复播放操作失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_ResumePlay(IN ULONG ulPort);

/**
* 根据时间设置文件播放位置。\n
* @param [IN] ulPort      播放通道号。
* @param [IN] ulTime      跳转目的时间（单位为秒）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体类型不支持该操作
* -         #ERR_XP_IN_RECORD_VIDEO_STATUS       当前正在本地录像
* -         #ERR_XP_FAIL_TO_DRAG_PLAY            跳转播放失败
* @note 
* -    1、如果当前正在本地录像，不支持根据时间设置文件播放位置操作。
* -    2、该函数只适用于本地文件回放时根据时间设置其播放位置。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPlayedTime(IN ULONG ulPort,
                                                          IN ULONG ulTime);

/**
* 获得文件当前播放时间。\n
* @param [IN]  ulPort       播放通道号。
* @param [OUT] pulTime      存放当前播放进度时间的指针（单位为秒）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体类型不支持该操作
* -         #ERR_XP_FAIL_TO_GET_PLAY_POSITION    获得当前播放进度失败
* @note 该函数只适用于本地文件回放时获得其当前播放时间。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetPlayedTime(IN ULONG ulPort,
                                                          OUT ULONG *pulTime);

/**
* 设置播放速度。\n
* @param [IN] ulPort        播放通道号。
* @param [IN] ulPlaySpeed   播放速度，需从#XP_PLAY_STATUS_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_NOT_START_PLAY               播放通道未开始播放操作
* -         #ERR_XP_IN_RECORD_VIDEO_STATUS       当前正在本地录像
* -         #ERR_XP_FAIL_TO_MULTIPL_SPEED_PLAY   倍速前进/后退播放失败
* @note 
* -    1、正在本地录像时，不支持倍速前进/后退播放操作。
* -    2、当前不支持本地文件播放的倍速播放。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPlaySpeed(IN ULONG ulPort,
                                                         IN ULONG ulPlaySpeed);

/**
* 单帧前进播放。\n
* @param [IN] ulPort   播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_NOT_START_PLAY               播放通道未开始播放操作
* -         #ERR_XP_IN_RECORD_VIDEO_STATUS       当前正在本地录像
* -         #ERR_XP_FAIL_TO_STEP_PLAY            单帧播放失败
* @note 
* -    1、正在本地录像时，不支持单帧播放操作。
* -    2、当前不支持本地文件播放的单帧播放。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_OneByOne(IN ULONG ulPort);

/**
* 清空所有缓冲区的剩余数据。\n
* @param [IN] ulPort        播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_NOT_START_PLAY               播放通道未开始播放操作
* -         #ERR_XP_FAIL_TO_RESET_BUFFER         清空缓冲区失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_ResetBuf(IN ULONG ulPort);

/**
* 停止播放。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_FAIL_TO_STOP_PLAY            停止播放操作失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StopPlay(IN ULONG ulPort);

/**
* 打开声音。\n
* @param [IN] ulPort   通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* -         #ERR_XP_DECODE_AUDIO_NOT_CONTINUE        音频流数据解码后不继续进行播放操作
* -         #ERR_XP_FAIL_TO_PLAY_SOUND               打开声音失败
* @note 同一时刻只能播放一路声音，如果现在已经有声音打开，则自动关闭原来已经打开的声音。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_PlaySound(IN ULONG ulPort);

/**
* 关闭声音。\n
* @param [IN] ulPort    通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* -         #ERR_XP_FAIL_TO_STOP_SOUND               关闭声音失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StopSound(IN ULONG ulPort);

/**
* 音量调节。\n
* @param [IN] ulVolume  音量值（范围从0到255，255为最大音量）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_FAIL_TO_ADJUST_VOLUME    调节音量操作失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetVolume(IN ULONG ulVolume);

/**
* 获得当前设置的音量值。\n
* @param [OUT] pulVolume    存放音量值的指针（范围从0到255，255为最大音量）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_FAIL_TO_GET_VOLUME       获得音量值失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetVolume(OUT ULONG *pulVolume);

/**
* 调整所有通道音频数据的WAVE波形，可以改变所有通道播放声音的大小。\n
* @param [IN] ulCoefficient 调整的参数（范围从0到255，255为最大调整参数值）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_FAIL_TO_ADJUST_VOLUME    调节音量操作失败
* @note
* -    1、此函数和IMOS_XP_SetVolume函数的不同之处在于，它是调整播放器所有通道声音数据的WAVE波形，对所有通道起作用；
          IMOS_XP_SetVolume是调整声卡音量，对整个操作系统起作用。
* -    2、如果用户不调用该函数调整所有通道音频数据的WAVE波形，则采用默认的调整参数值146。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_AdjustAllWaveAudio(IN ULONG ulCoefficient);

/**
* 设置指定播放通道的视频图像显示比例。\n
* @param [IN] ulPort            播放通道号。
* @param [IN] ulRenderScale     视频图像在播放通道上的显示比例，需从#XP_RENDER_SCALE_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                     成功
* -         #ERR_COMMON_INVALID_PARAM               输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES            获得播放通道资源失败  
* -         #ERR_XP_FAIL_TO_SET_RENDER_SCALE        设置图像显示比例参数失败
* @note 
* -    1、在不调用该接口的情况下，视频图像默认填充整个播放窗格。
* -    2、在启动播放之前调用该接口时，则设置的显示比例参数在后续启动该播放通道播放时生效。
* -    3、在播放过程中调用该接口时，则设置的显示比例参数实时生效。
* -    4、调用该接口对指定播放通道设置的显示比例参数在播放器运行期间一直有效。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetRenderScale(IN ULONG ulPort,
                                                           IN ULONG ulRenderScale);

/**
* 设置图象的对比度参数，即时起作用。\n
* @param [IN] ulPort             播放通道号。
* @param [IN] ulContrastMode     图象对比度模式，需从#XP_PICTURE_CONTRAST_MODE_E枚举中取值。
* @param [IN] ulContrastLevel    图象对比度级别，需从#XP_PICTURE_CONTRAST_LEVEL_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES     获得播放通道资源失败
* -         #ERR_XP_NOT_SUPPORT_SET_CONTRAST 播放通道不支持设置图象对比度参数
* -         #ERR_XP_FAIL_TO_SET_CONTRAST     设置图象对比度失败
* @note 
* -    1、在不调用该接口的情况下，视频图像默认不进行对比度调节处理。
* -    2、可以在开始播放IMOS_XP_StartPlay之前设置，但设置的对比度参数被保存，作为启动该通道播放时
* -       的初始值；在开始播放后调用该接口设置的对比度参数即时生效。
* -    3、调用该接口对指定播放通道设置的对比参数在播放器运行期间一直有效；当参数ulContrastMode
* -       传入XP_PICTURE_CONTRAST_MODE_NONE时，即停止对比度调节处理，此时ulContrastLevel参数传
* -       入的值将无效。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetPictureContrast(IN ULONG ulPort,
                                                               IN ULONG ulContrastMode, 
                                                               IN ULONG ulContrastLevel);

/**
* 设置解码场模式。\n
* @param [IN] ulPort      播放通道号。
* @param [IN] ulFieldMode 场模式，需从#XP_FIELD_MODE_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_SET_FIELD_MODE       设置解码场模式失败
* @note
* -    1、MPEG4解码方式没有场的概念。
* -    2、该函数需要在IMOS_XP_StartPlay之后调用。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetFieldMode(IN ULONG ulPort,
                                                         IN ULONG ulFieldMode);

/**
* 设置去交织处理模式。\n
* @param [IN] ulPort            播放通道号。
* @param [IN] ulDeinterlaceMode 去交织处理模式，需从#XP_DEINTERLACE_MODE_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                   通道未启动播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC            播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_ENABLE_DEINTERLACE       启动或关闭去交织处理失败
* @note
* -    1、如果用户不调用该函数设置去交织处理模式，则播放器内部默认使用混合模式启动去交织处理。
* -    2、该函数需要在IMOS_XP_StartPlay之后调用。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetDeinterlaceMode(IN ULONG ulPort,
                                                               IN ULONG ulDeinterlaceMode);

/**
* 单次实时抓拍。\n
* @param [IN] ulPort            播放通道号。
* @param [IN] pcFileName        保存图像的文件路径，包括文件名（不带后缀名）。
* @param [IN] ulPicFormat       图像格式，需从#XP_PICTURE_FORMAT_E枚举中取值。
* @param [OUT] pcFilePostfix    存放图像文件后缀的指针，缓冲区长度应不小于#IMOS_XP_FILE_POSTFIX_LEN。
*                               如果用户不需要返回后缀名，可将该参数设置为NULL。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_SNATCH_FORMAT    抓拍格式不支持
* -         #ERR_XP_DISK_CAPACITY_NOT_ENOUGH     硬盘空间不足
* -         #ERR_XP_NO_PICTURE_TO_SNATCH         没有解码过的图片可供抓拍
* -         #ERR_XP_FAIL_TO_SNATCH_ONCE          单次抓拍操作失败
* @note 播放器将根据图像格式在文件名后面追加对应的后缀名。如BMP图像文件的后缀为.bmp。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SnatchOnce(IN ULONG ulPort,
                                                       IN const CHAR *pcFileName,
                                                       IN ULONG ulPicFormat, 
                                                       OUT CHAR *pcFilePostfix);

/**
* 设置录像质量参数。\n
* @param [IN] ulPort                 播放通道号。
* @param [IN] ulRecordQuality        录像质量参数，需从#XP_RECORD_QUALITY_E枚举中取值。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* @note
* -    1、录像质量参数设置为XP_RECORD_PRIORITY时，录像处理优先；设置为XP_PLAY_PRIORITY时，播放处理优先，即录像可能会丢弃数据。
* -    2、不调用该接口时，播放器内部默认为XP_PLAY_PRIORITY。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetRecordQuality(IN ULONG ulPort,
                                                             IN ULONG ulRecordQuality);

/**
* 开始本地录像。\n
* @param [IN] ulPort            播放通道号。
* @param [IN] pcFileName        录像文件存放路径，包括文件名（不带后缀名）。
* @param [IN] ulMediaFileFormat 录像文件的格式，需从#XP_MEDIA_FILE_FORMAT_E枚举中取值。
* @param [OUT] pcFilePostfix    存放录像文件后缀的指针，缓冲区长度应不小于#IMOS_XP_FILE_POSTFIX_LEN。
*                               如果用户不需要返回后缀名，可将该参数设置为NULL。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                          成功
* -         #ERR_COMMON_INVALID_PARAM                    输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES                 获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                       通道未开始播放操作
* -         #ERR_XP_ALREADY_START_RECORD_VIDEO           指定的播放通道已经启动录像操作
* -         #ERR_XP_NOT_SUPPORT_RECORD_VIDEO_FORMAT      录像格式不支持
* -         #ERR_XP_DISK_CAPACITY_NOT_ENOUGH             硬盘空间不足
* -         #ERR_XP_IN_PAUSE_PLAY_STATUS                 当前正处于暂停播放状态
* -         #ERR_XP_IN_MULTIPL_SPEED_PLAY_STATUS         当前正处于倍速播放状态
* -         #ERR_XP_IN_STEP_PLAY_STATUS                  当前正处于单帧播放状态
* -         #ERR_XP_FAIL_TO_START_RECORD_VIDEO           启动本地录像失败
* @note
* -    1、播放器将根据媒体流格式在文件名后面追加对应的后缀名。如TS流录像文件的后缀为.ts。
* -    2、当播放处于暂停播放、快速播放、慢速播放或单帧播放状态时，不支持启动本地录像操作。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StartRecord(IN ULONG ulPort,
                                                        IN const CHAR *pcFileName,
                                                        IN ULONG ulMediaFileFormat, 
                                                        OUT CHAR *pcFilePostfix);

/**
* 停止本地录像。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                          成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES                 获得播放通道资源失败
* -         #ERR_XP_NOT_START_RECORD_VIDEO               通道未开始本地录像操作
* -         #ERR_XP_FAIL_TO_STOP_RECORD_VIDEO            停止本地录像失败
* -         #ERR_XP_NOT_START_PLAY                       通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StopRecord(IN ULONG ulPort);

/**
* 获得视频编码格式。\n
* @param [IN]  ulPort             播放通道号。
* @param [OUT] pulVideoEncodeType 存放视频编码格式的指针，值为#XP_VIDEO_ENCODE_TYPE_E枚举中一个。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                    成功
* -         #ERR_COMMON_INVALID_PARAM              输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES           获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                 通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC          播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_GET_VIDEO_ENCODE_TYPE  获得视频编码格式失败
* @note 该函数需要在IMOS_XP_StartPlay之后且IMOS_XP_StopPlay之前调用，才能准确获得指定播放通道的视频编码格式。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetVideoEncodeType(IN ULONG ulPort,
                                                               OUT ULONG *pulVideoEncodeType);

/**
* 获得丢包率。\n
* @param [IN]  ulPort        播放通道号。
* @param [OUT] pulRecvPktNum 存放已接收到包数的指针。
* @param [OUT] pulLostPktNum 存放丢弃包数的指针。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_GET_LOST_PKT_RATE    获得丢包率统计数据失败
* @note 该函数需要在IMOS_XP_StartPlay之后且IMOS_XP_StopPlay之前调用，才能准确获得指定播放通道的丢包率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetLostPacketRate(IN ULONG ulPort,
                                                              OUT ULONG *pulRecvPktNum,
                                                              OUT ULONG *pulLostPktNum);

/**
* 复位丢包率。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC            播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_RESET_LOST_PKT_RATE      复位丢包率统计数据失败
* @note 调用该函数后，将从复位时刻重新开始统计丢包率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_ResetLostPacketRate(IN ULONG ulPort);

/**
* 获得丢帧率。\n
* @param [IN] ulPort           播放通道号。
* @param [OUT] pulAllFrameNum  存放帧总数的指针。
* @param [OUT] pulLostFrameNum 存放丢弃的帧数的指针。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_GET_LOST_FRAME_RATE  获得丢帧率统计数据失败
* @note 该函数需要在IMOS_XP_StartPlay之后且IMOS_XP_StopPlay之前调用，才能准确获得指定播放通道的丢帧率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetLostFrameRate(IN ULONG ulPort,
                                                             OUT ULONG *pulAllFrameNum,
                                                             OUT ULONG *pulLostFrameNum);

/**
* 复位丢帧率。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC            播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_RESET_LOST_FRAME_RATE    复位丢帧率统计失败
* @note 调用该函数后，将从复位时刻重新开始统计丢帧率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_ResetLostFrameRate(IN ULONG ulPort);

/**
* 获得帧率。\n
* @param [IN]  ulPort       播放通道号。
* @param [OUT] pulFrameRate 存放帧率的指针，单位为fps。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_GET_FRAME_RATE       获得帧率数据失败
* @note 该函数需要在IMOS_XP_StartPlay之后且IMOS_XP_StopPlay之前调用，才能准确获得指定播放通道的帧率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetFrameRate(IN ULONG ulPort,
                                                         OUT ULONG *pulFrameRate);

/**
* 获得码率。\n
* @param [IN] ulPort        播放通道号。
* @param [OUT] pulBitRate   存放码率的指针，单位为bps。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               通道未开始播放操作
* -         #ERR_XP_NOT_SUPPORT_MEDIA_SVC        播放通道的媒体业务类型不支持此操作
* -         #ERR_XP_FAIL_TO_GET_BIT_RATE         获得码率数据失败
* @note 该函数需要在IMOS_XP_StartPlay之后且IMOS_XP_StopPlay之前调用，才能准确获得指定播放通道的码率；另外，
*       该函数不支持获得本地文件回放通道的码率。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetBitRate(IN ULONG ulPort,
                                                       OUT ULONG *pulBitRate);


/**
* 打开语音业务。\n
* @param [IN] ulVoiceSvcType  语音业务类型，需从#XP_VOICE_SERVICE_TYPE_E枚举中取值。
* @param [IN] pcLocalIP       本端IP地址。
* @param [IN] usLocalPort     本端监听端口。
* @param [IN] pcRemoteIP      远端IP地址。
* @param [IN] usRemotePort    远端端口。
* @param [IN] ulTransProtl    收发媒体流的传输层协议，需从#XP_PROTOCOL_E枚举中取值。
* @param [OUT] pulPort        返回语音业务通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数非法
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得语音通道资源失败
* -         #ERR_XP_FAIL_TO_OPEN_VOICE_SVC           启动语音业务失败
* @note 如果使用本地默认的IP地址，则本地IP地址参数pcLocalIP传入空字符串。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_OpenVoiceSvc(IN ULONG ulVoiceSvcType,
                                                         IN const CHAR *pcLocalIP,
                                                         IN USHORT usLocalPort,
                                                         IN const CHAR *pcRemoteIP,
                                                         IN USHORT usRemotePort,
                                                         IN ULONG ulTransProtl,
                                                         OUT ULONG *pulPort);

/**
* 开始语音业务。\n
* @param [IN] ulPort 语音业务通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得语音通道资源失败
* -         #ERR_XP_FAIL_TO_START_VOICE_SVC          启动语音业务失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StartVoiceSvc(IN ULONG ulPort);

/**
* 停止语音业务。\n
* @param [IN] ulPort 语音业务通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得语音通道资源失败
* -         #ERR_XP_FAIL_TO_STOP_VOICE_SVC           停止语音业务失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StopVoiceSvc(IN ULONG ulPort);

/**
* 关闭语音业务。\n
* @param [IN] ulPort 语音业务通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得语音通道资源失败
* -         #ERR_XP_FAIL_TO_CLOSE_VOICE_SVC          关闭语音业务失败
* -         #ERR_XP_NOT_START_PLAY                   通道未开始播放操作
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_CloseVoiceSvc(IN ULONG ulPort);

/**
* 启动或停止向语音对端发送语音数据。\n
* @param [IN] bSend     是否向语音对端发送语音数据（BOOL_TRUE：启动发送，BOOL_FALSE：停止发送）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数非法
* -         #ERR_XP_FAIL_TO_VOICE_SILENCE            启动/停止发送语音数据失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SendVoiceData(IN BOOL_T bSend);

/**
* 麦克风音量调节。\n
* @param [IN] ulVolume 音量值（范围从0到255，255为最大音量）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_MIC_NOT_EXIST            系统中麦克风适配不存在
* -         #ERR_XP_FAIL_TO_ADJUST_VOLUME    调节音量操作失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetMicVolume(IN ULONG ulVolume);

/**
* 获得麦克风音量值。\n
* @param [OUT] pulVolume 音量值的指针（范围从0到255，255为最大音量）。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED              成功
* -         #ERR_COMMON_INVALID_PARAM        输入参数非法
* -         #ERR_XP_MIC_NOT_EXIST            系统中麦克风适配不存在
* -         #ERR_XP_FAIL_TO_GET_VOLUME       获得音量值失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_GetMicVolume(OUT ULONG *pulVolume);

/**
* 启动连续实时抓拍。\n
* @param [IN] ulPort             播放通道号。
* @param [IN] pcFileName         图像文件存放的路径，包括文件名（不带扩展名）。
* @param [IN] ulPicFormat        图像文件的格式，需从#XP_PICTURE_FORMAT_E枚举中取值。
* @param [IN] ulInterval         抓拍间隔，单位为毫秒。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_COMMON_INVALID_PARAM            输入参数无效
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_DISK_CAPACITY_NOT_ENOUGH     硬盘空间不足
* -         #ERR_XP_NOT_START_PLAY               指定的播放通道未开始播放操作
* -         #ERR_XP_ALREADY_START_SERIES_SNATCH  播放通道已经启动了连续抓拍的操作
* -         #ERR_XP_NOT_SUPPORT_SNATCH_FORMAT    抓拍格式不支持
* -         #ERR_XP_FAIL_TO_START_SERIES_SNATCH  启动连续抓拍操作失败
* @note
* -      播放器XP会在文件名后面附加类似于"20080928(13-10-50-99)"格式的抓拍时间戳字符串。
* -      单位时间内成功抓拍的最多图片数和机器性能有关。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StartSnatchSeries(IN ULONG ulPort,
                                                              IN const CHAR *pcFileName,
                                                              IN ULONG ulPicFormat,
                                                              IN ULONG ulInterval);

/**
* 停止连续实时抓拍。\n
* @param [IN] ulPort 播放通道号。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                  成功
* -         #ERR_XP_FAIL_TO_GET_PORT_RES         获得播放通道资源失败
* -         #ERR_XP_NOT_START_PLAY               指定的播放通道未开始播放操作
* -         #ERR_XP_NOT_START_SERIES_SNATCH      指定的播放通道未启动连续抓拍操作
* -         #ERR_XP_FAIL_TO_STOP_SERIES_SNATCH   停止连续抓拍操作失败
* @note 无。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_StopSnatchSeries(IN ULONG ulPort);

/**
* 设置指定播放通道的NAT类型。\n
* @param [IN] ulPort            播放通道号。
* @param [IN] ulNatMode         NAT类型，需从#XP_NAT_MODE_E枚举中取值。
* @param [IN] pcNatSessionStr   NAT引流字符串。
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数无效
* -         #ERR_XP_FAIL_TO_GET_PORT_RES             获得播放通道资源失败
* @note 引流字符串可以自行定义，但是收发双方必须保持一致。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetNatParam(IN ULONG ulPort,
                                                        IN ULONG ulNatMode,
                                                        IN const CHAR *pcNatSessionStr);

/**
* 设置音频数据源与工作模式。\n
* @param [IN] enWaveInSource     设置音频输入源，需从#XP_WAVEIN_SOURCE_E枚举中取值。
* @param [IN] pWaveInParameter   附加参数信息，当音频输入源为XP_WAVEIN_SOURCE_FILE时，需要填写XP_WAVEIN_FILE_INFO_S结构体作附加参数
* @return 返回如下错误码：
* -         #ERR_COMMON_SUCCEED                      成功
* -         #ERR_COMMON_INVALID_PARAM                输入参数非法
* -         #ERR_XP_FAIL_TO_SET_WAVEIN_MOD           设置音频输入源失败
* @note
* -    1、默认为XP_WAVEIN_MODE_DEVICE作数据源。
* -    2、设置后需要下次启动语音业务才起效(如当前存在语音业务需要关闭)。
* -    3、音频文件只支持8K采样率+16bit位宽+单声道的wave格式音频文件。
* -    4、设置为XP_WAVEIN_MODE_FILE音频源时需要填写附加信息，参考#XP_WAVEIN_FILE_INFO_S。
*/
IMOS_XP_PLAYER_EXPORT ULONG STDCALL IMOS_XP_SetWaveInSourceMode(IN XP_WAVEIN_SOURCE_E enWaveInSource, IN VOID *pWaveInParameter);

#ifdef  __cplusplus
}
#endif /* end of __cplusplus */

#endif /* _IMOS_XP_PLAYER_H_ */
