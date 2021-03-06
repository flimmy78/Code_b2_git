/*******************************************************************************
 Copyright (c) 2008-2009, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              sdk_func.h

  Project Code: IMOS_SDK
   Module Name: SDK
  Date Created: 2009-02-27
        Author: sunyifan (s06966)
                zhuyi (KF1397)
                yangbin (07022)
   Description: SDK对外接口
                注意: 其中分页查询时，所需列表空间由外部申请，
                      大小根据分页查询时一页的个数进行申请。


--------------------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  2009-10-22  sunyifan (s06966) 根据review意见对接口描述类问题进行修改
--------------------------------------------------------------------------------
  YYYY-MM-DD

*******************************************************************************/
#ifndef _IMOS_SDK_INTERFACE_H_
#define _IMOS_SDK_INTERFACE_H_

/* 包含BP预编译宏以及基础类型的文件 */
/** 包含BP头文件*/
#include "imos_public.h"
#include "imos_def.h"
#include "imos_errcode.h"

#include "imos_bp_def.h"
#include "imos_terminal_def.h"
#include "imos_mp_def.h"
#include "imos_mm_def.h"
#include "imos_as_def.h"

/** 包含SDK头文件*/
#include "sdk_def.h"
#include "sdk_struct.h"
#include "sdk_func_obsolete.h"


#ifdef  __cplusplus
extern "C"{
#endif

#if 0
#endif
/*************************************************************************************
SDK INIT
***************************************************************************************/
/** @defgroup groupSDKInit SDK初始化和注销
*   SDK初始化，详细的调用依赖关系请参见SDK说明文档。该模块包含初始化接口和清空接口。
*   @{
*/
/**
* 对外初始化总入口。 \n
* @param [IN]   szServerAdd         服务器地址
* @param [IN]   ulServerPort        服务器端口
* @param [IN]   bUIFlag             SDK在UI侧启动的标记，BOOL_TRUE为在UI侧，BOOL_FALSE为在服务器侧
* @param [IN]   bXPFlag             SDK是否包含有XP的标记, BOOL_TRUE为包含XP; BOOL_FALSE为不包含XP
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_SDK_ONE_USER_IN_ONE_PROC_ONLY
* - #ERR_AS_SDK_CREATE_THREAD_FAIL
* -     返回操作结果码：见结果码文件sdk_err.h
* @note szServerAdd的取值为127.0.0.0,127.0.0.1,VM服务器地址
*       ulServerPort的取值为8800
*/
IMOS_EXPORT ULONG STDCALL IMOS_Initiate
(
    IN  CHAR    szServerAdd[IMOS_IPADDR_LEN],
    IN  ULONG   ulServerPort,
    IN  BOOL_T  bUIFlag,
    IN  BOOL_T  bXPFlag

);

/**
* SDK清空接口，主要实现发送用户登录消息以及回收SDK因为业务所申请的各种资源。 \n
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_CleanUp
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo
);
/** @} */ /* end of MG Module */

#if 0
#endif
/*************************************************************************************
User Login
***************************************************************************************/
/** @defgroup groupUserLogin 用户登录和退出
*   用户管理
*   @{
*/


/**
* 完成用户登录功能，支持多点登录功能。\n
* @param [IN]   szUserLoginName 用户输入的登录名
* @param [IN]   szPassword      用户输入的口令
* @param [IN]   szIpAddress     用户所在客户端的IP地址
* @param [OUT]  pstSDKLoginInfo 用户登录带出信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_ADMIN_HAS_LOGGED_IN
* - #ERR_DAO_USER_NOT_EXIST
* - #ERR_MM_USER_IS_LOCKED
* - #ERR_MM_USER_PASSWORD_INCORRECT
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_Login
(
    IN  CHAR           szUserLoginName[IMOS_NAME_LEN],
    IN  CHAR           szPassword[IMOS_PASSWD_ENCRYPT_LEN],
    IN  CHAR           szIpAddress[IMOS_IPADDR_LEN],
    OUT LOGIN_INFO_S   *pstSDKLoginInfo
);

/**
* 用户登出
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_LOGIN_ID_NOT_EXIST
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_Logout
(
   IN  USER_LOGIN_ID_INFO_S     *pstUserLogIDInfo
);

/**
* 完成用户保活功能。\n
* @param [IN]   pstUserLoginIDInfo 用户登录ID信息标识
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 该接口用于登录成功后的用户保活
*/
IMOS_EXPORT ULONG STDCALL IMOS_UserKeepAlive
(
    IN USER_LOGIN_ID_INFO_S   *pstUserLoginIDInfo
);

/**
* SDK自动保活功能。\n
* @param [IN] pstUserLoginIDInfo 用户登录ID信息标识
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.该接口要求调用者主动传入USER_LOGIN_ID_INFO_S，即：调用者应在登录成功后，才能调用该接口，
* -   并保证UserloginID的正确性。
* - 2.本接口只能在客户端调用才会成功。
* - 3.自动保护采用定时器方式实现，三次保活，一次30S。保活失败次数超过三次 或 收到服务器返回的保活失败的错误响应，
* -   都标识自动保活失败。
* - 4.自动保活失败，会调用第三方提供的回调函数，传出#PROC_TYPE_LOGOUT消息。但第三方提供的回调函数依然有效。
* - 5.一个进程内只支持一个登录用户的自动保活，若要再次调用，建议先调用IMOS_CleanUp()清空SDK，登出已经登录的用户
* - 6.本接口只反映自动保活启动是否成功和失败原因。
*/
IMOS_EXPORT ULONG STDCALL IMOS_AutoKeepAlive
(
    IN USER_LOGIN_ID_INFO_S   *pstUserLoginIDInfo
);

/**
* 完成订阅推送功能。\n
* @param [IN]   pstUserLoginIDInfo  用户登录ID信息标识
* @param [IN]   ulSubscribePushType 订阅类型，取值范围为#SUBSCRIBE_PUSH_TYPE_E，目前仅支持#SUBSCRIBE_PUSH_TYPE_ALL
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_SubscribePushInfo
(
    IN USER_LOGIN_ID_INFO_S   *pstUserLoginIDInfo,
    IN ULONG                  ulSubscribePushType
);

/** @} */ /* end of USER LOGIN MODULE */

#if 0
#endif
/**************************************************************************************************************
Role
***************************************************************************************************************/
/** @defgroup groupRoleMg 权限管理
*   权限管理
*   @{
*/
/**
* 添加角色，返回角色编码
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstSDKUserRoleInfo  角色信息
* @param [OUT]  szRoleCode          角色编码，角色的唯一标识
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_ROLE_NAME_EXIST
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddRole
(
    IN    USER_LOGIN_ID_INFO_S      *pstUserLogIDInfo,
    IN    USER_ROLE_INFO_S          *pstSDKUserRoleInfo,
    OUT   CHAR                      szRoleCode[IMOS_RES_CODE_LEN]
);


/**
* 根据角色编码，修改角色信息
* @param [IN]   pstUserLogIDInfo          用户登录ID信息标识
* @param [IN]   szRoleCode                角色编码，角色的唯一标识
* @param [IN]   pstSDKUserRoleInfo        角色信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_ROLE_NOT_EXIST
* - #ERR_DAO_ROLE_NAME_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyRole
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szRoleCode[IMOS_RES_CODE_LEN],
    IN  USER_ROLE_INFO_S            *pstSDKUserRoleInfo
);


/**
* 根据角色编码，设置角色权限
* @param [IN]   pstUserLogIDInfo      用户信息标识
* @param [IN]   szRoleCode            角色编码，对应唯一一个角色
* @param [IN]   pstSDKDomainAuthority 权限信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_ROLE_NOT_EXIST
* - #ERR_MM_AUTHORITY_NOT_DEFINED
* - #ERR_DAO_ROLE_RES_NOT_EXIST
* - #ERR_DAO_ROLE_RES_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* -     1.该接口配置的权限仅限于角色所属组织，即该接口仅能配置角色所属组织中是否具有某种权限
* -     2.调用该接口后, 以该次调用的权限为准; 角色之前的权限会被覆盖
*/
IMOS_EXPORT ULONG STDCALL IMOS_SetRoleAuthority
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szRoleCode[IMOS_RES_CODE_LEN],
    IN  ORG_AUTHORITY_S             *pstSDKDomainAuthority
);


/**
* 根据角色编码，删除角色。
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szRoleCode          角色编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_ROLE_NOT_EXIST
* - #ERR_MM_ROLE_IS_ASSIGNED
* - #ERR_MM_ROLE_IS_SYSTEM_MANAGER
* @note 如果角色已授予某用户，则不能删除
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelRole
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szRoleCode[IMOS_RES_CODE_LEN]
);


/**
* 分页查询角色列表 \n
* 条件为空时,查询所有角色,并默认按照"角色名称升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   bIsQuerySubOrg      是否查询本组织域及其下级组织域的所有权限, BOOL_TRUE为查询; BOOL_FALSE为不查询
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[角色名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstSDKUserRoleList  角色信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryRoleList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  BOOL_T                          bIsQuerySubOrg,
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT ROLE_QUERY_ITEM_S               *pstSDKUserRoleList
);


/**
* 根据角色编码，查询角色的详细信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szRoleCode                  待查询角色编码
* @param [OUT]  pstSDKUserRoleInfo          角色详细信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_ROLE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryRoleInfo
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szRoleCode[IMOS_RES_CODE_LEN],
    OUT USER_ROLE_INFO_S        *pstSDKUserRoleInfo
);


/**
* 根据角色编码，查询某个角色的权限信息
* @param [IN]  pstUserLogIDInfo     用户登录ID信息标识
* @param [IN]  szRoleCode           角色编码
* @param [OUT] pstAuthorityInfo     角色权限信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryAuthListByRole

(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szRoleCode[IMOS_RES_CODE_LEN],
    OUT ORG_AUTHORITY_S         *pstAuthorityInfo
);

/**
* 查询当前登录用户的所有权限. \n
* 如果当前登录用户是系统管理员,则只返回"是否是系统管理员"标识,不返回权限列表;
* 如果不是系统管理员,则返回权限列表(包括系统权限和资源权限).
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [OUT]  pbIsSystemMgr       "是否是系统管理员"标识, BOOL_TRUE为系统管理员; BOOL_FALSE为非系统管理员
* @param [OUT]  pstAuthorityInfo    权限列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_MM_AUTHORITY_NOT_DEFINED
* -     其它结果码,参见sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryAuthListByUser
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    OUT BOOL_T                  *pbIsSystemMgr,
    OUT ORG_AUTHORITY_S         *pstAuthorityInfo
);


/**
* 根据角色编码，分页查询此角色所关联的用户的信息
* 条件为空时,查询所有关联用户,并默认按照"用户名称升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szRoleCode          角色编码
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:
* -                                 #USER_CODE_TYPE[用户编码]、#USER_NAME_TYPE[用户名称]、#USER_FULL_NAME[用户全名]、
* -                                 #USER_TEL_PHONE[用户座机号码]、#USER_MOBILE_PHONE[用户移动电话号码]、
* -                                 #USER_EMAIL[用户电子邮件地址]、#USER_IS_LOCKED[用户是否被锁定])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstSDKUserList      用户信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryRelatedUserForRole
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szRoleCode[IMOS_RES_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT USER_QUERY_ITEM_S           *pstSDKUserList
);
/** @} */ /* end of ROLE MANAGEMENT MODULE */

#if 0
#endif
/**************************************************************************************************************
用户
***************************************************************************************************************/
/** @defgroup groupUserMg 用户管理
*   用户管理
*   @{
*/
/**
* 增加用户，此信息中包含用户编码，是用户的唯一标识
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               用户所属组织编码
* @param [IN]   pstUserPasswordInfo     用户信息(包含用户登录口令)
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_MM_USER_EXCEED_LIMIT_NUM
* - #ERR_DAO_USER_CODE_EXIST
* - #ERR_DAO_USER_NAME_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddUser
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  USER_INFO_PASSWORD_S        *pstUserPasswordInfo
);



/**
* 修改用户信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstUserInfo             用户信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 用户信息中的用户编码此处必须填写
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyUser
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  USER_INFO_S                 *pstUserInfo
);

/**
* 修改用户密码
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstUserModifyPassword   用户密码信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_OPERATOR_AND_PASSWD_MODIFIED_USER_NOT_SAME
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 用户只能修改自身的密码
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyUserPassword
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  USER_MODIFY_PASSWORD_S      *pstUserModifyPassword
);



/**
* 为用户赋予角色（列表）
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szUserCode                  用户编码
* @param [IN]   aszRoleCode                 赋予用户的角色编码数组
* @param [IN]   ulRoleCount                 赋予用户的角色编码数组中角色的实际个数,不能超过#IMOS_MAX_USER_ROLES_NUM
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* - #ERR_MM_USER_IS_ADMIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AssignRoleForUser
(
    IN  USER_LOGIN_ID_INFO_S                *pstUserLogIDInfo,
    IN  CHAR                                szUserCode[IMOS_USER_CODE_LEN],
    IN  CHAR                                aszRoleCode[IMOS_MAX_USER_ROLES_NUM][IMOS_RES_CODE_LEN],
    IN  ULONG                               ulRoleCount
);

/**
* 删除用户
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szUserCode                  用户编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_OPERATOR_SELF
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelUser
(
    IN   USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN   CHAR                           szUserCode[IMOS_USER_CODE_LEN]
);



/**
* 查询用户的详细信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szUserCode                  用户编码
* @param [OUT]  pstUserInfo                 用户信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryUserInfo
(
    IN   USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN   CHAR                           szUserCode[IMOS_USER_CODE_LEN],
    OUT  USER_INFO_S                    *pstUserInfo
);


/**
* 分页查询用户拥有的角色
* 条件为空时,查询用户拥有的所有角色,并默认按照"角色名称升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szUserCode          用户编码
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[角色名称]、#ROLE_PRIORITY[角色优先级])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstRoleList         角色信息列表　
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryUserAssignedRoles
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szUserCode[IMOS_USER_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT ROLE_QUERY_ITEM_S               *pstRoleList
);



/**
* 分页查询某个组织下的用户列表 \n
* 不填查询条件时,查所有,并默认排序(用户名称升序)
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织域编码
* @param [IN]   pstQueryCondition   通用查询条件(可填NULL;支持的查询条件包括:#USER_NAME_TYPE[用户名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstUserList         用户信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryUserList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT USER_QUERY_ITEM_S               *pstUserList
);



/**
* 查询某个组织下的在线用户列表  \n
* 不填查询条件时,查所有,并按照默认条件排序(用户名称升序)
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织域编码
* @param [IN]   bIsQuerySubOrg      是否查询本组织域以及下级组织域的所有在线用户, BOOL_TRUE为查询; BOOL_FALSE为不查询
* @param [IN]   pstQueryCondition   通用查询条件(可填NULL;支持的查询条件包括:#USER_NAME_TYPE[用户名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstUserList         用户在线信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryOnlineUserList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  BOOL_T                          bIsQuerySubOrg,
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT USER_QUERY_ITEM_S               *pstUserList
);

/**
* 重置用户登录密码
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  szUserCode               需要重置密码的用户编码
* @param [IN]  szPassword               新的登录密码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ResetUserPassword
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szUserCode[IMOS_USER_CODE_LEN],
    IN  CHAR                        szPassword[IMOS_PASSWD_ENCRYPT_LEN]
);


/**
* 强制某个登录用户点下线
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  szUserLoginID            被强制下线用户的登录ID
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_OPERATOR_SELF
* - #ERR_AS_EXPECTED_USER_NOT_EXIST
* - #ERR_MM_USER_IS_ADMIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.用户不能强制本身下线；
* -     2.不能强制admin用户下线
*/
IMOS_EXPORT ULONG STDCALL IMOS_KickOffLoginUser
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szUserLoginID[IMOS_RES_CODE_LEN]
);


/**
* 锁定用户
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  szUserCode               被锁定用户的编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* - #ERR_MM_USER_IS_ADMIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.被锁定的用户在解锁前不能够登录;
* -     2.用户被锁定后,其所有登录点(如果有)均被强制下线;
* -     3.admin用户不能被锁定
*/
IMOS_EXPORT ULONG STDCALL IMOS_LockUser
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szUserCode[IMOS_USER_CODE_LEN]
);


/**
* 用户解锁
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  szUserCode               被解锁用户的编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_USER_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_UnLockUser
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szUserCode[IMOS_USER_CODE_LEN]
);
/** @} */ /* end of USER MANAGEMENT MODULE */

#if 0
#endif
/*******************************************************************************
组织管理

*******************************************************************************/
/** @defgroup groupOrgMg 组织管理
*   组织管理
*   @{
*/
/**
* 添加组织节点 \n
* @param [IN]       pstUserLogIDInfo   用户登录ID信息标识
* @param [IN][OUT]  pstOrgNodeInfo     组织信息(作为入参时,组织编码可以为空;作为出参时, 若入参的组织编码为空, 则携带出内部生成的组织编码)
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_MM_DOMAIN_EXCEED_LIMIT_NUM
* - #ERR_MM_DOMAIN_PARENT_DOMAIN_NOT_EXIST
* - #ERR_MM_DOMAIN_TOO_DEEP
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 组织节点信息中的组织编码是组织的唯一标识
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddOrganization
(
    IN      USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    INOUT   ORG_NODE_INFO_S         *pstOrgNodeInfo
);


/**
* 修改组织节点信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstOrgNodeInfo      待修改组织节点信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* - #ERR_DAO_RES_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyOrganization
(
    IN   USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN   ORG_NODE_INFO_S                *pstOrgNodeInfo
);



/**
* 删除组织节点 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           待删除组织节点编码
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* - #ERR_DAO_RES_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.不能删除当前用户所在组织
* - 2.当某组织下有子组织及资源时, 该组织无法删除
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelOrganization
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN]
);


/**
* 分页查询组织下的子组织节点列表，只查询该组织下一层的子组织 \n
* 不填查询条件时,查所有,并按照默认条件排序(组织名称升序)
* @param [IN]   pstUserLogIDInfo   用户登录ID信息标识
* @param [IN]   szOrgCode          组织节点编码
* @param [IN]   pstQueryCondition  通用查询条件(可填NULL;支持的查询条件包括:#NAME_TYPE[组织名称])
* @param [IN]   pstQueryPageInfo   请求分页信息
* @param [OUT]  pstRspPageInfo     响应分页信息
* @param [OUT]  pstOrgNodeList     组织节点列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryOrgList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT ORG_NODE_INFO_S                 *pstOrgNodeList
);


/**
* 查询组织节点信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织节点编码
* @param [OUT]  pstOrgNodeInfo      组织节点信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryOrgInfo
(
    IN     USER_LOGIN_ID_INFO_S         *pstUserLogIDInfo,
    IN     CHAR                         szOrgCode[IMOS_DOMAIN_CODE_LEN],
    OUT    ORG_NODE_INFO_S              *pstOrgNodeInfo
);


/**
* 分页查询组织下的资源信息列表 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织节点编码
* @param [IN]   ulResType           待查询的资源类型
* @param [IN]   pstQueryCondition   查询条件(可填NULL;支持的查询条件包括:#RES_SUB_TYPE[资源子类型])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstResList          资源信息列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.如果需要查询特定种类域(如本域或外域)下的资源列表,可增加查询条件#DOMAIN_TYPE(域类型),并且查询内容中字符串"0"代表本域,"1"代表外域
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryResourceList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  ULONG                           ulResType,
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT ORG_RES_QUERY_ITEM_S            *pstResList
);

/**
* 查询组织下资源信息列表(V2,扩展返回"资源所属组织的名称") \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   pstQueryCondition   查询条件
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstResList          资源信息列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 过滤
* - 1.条件可以为NULL,表示查指定组织下所有资源(不查子组织)
* - 2.支持按"是否查子组织"条件查询:#IS_QUERY_SUB = 1 是;= 0 否
* - 3.支持按"资源名称"模糊查询:#NAME_TYPE
* - 4.支持按"是否外域资源"查询:#DOMAIN_TYPE = 1 是;= 0 否
* - 5.支持按"资源类型"查询:#RES_TYPE,取值为#IMOS_TYPE_E, 仅支持逻辑关系类型为#EQUAL_FLAG;
* - 6.支持按"资源子类型"查询:#RES_SUB_TYPE(资源类型为摄像机时,取值为#CAMERA_TYPE_E)
* - 排序
* - 1.不指定排序条件情况下,默认按"资源名称"升序排序
* - 2.支持的排序条件,包括:#NAME_TYPE(资源名称),#CODE_TYPE(资源编码),#RES_TYPE(资源类型),#RES_SUB_TYPE(资源子类型),
* -   #DOMAIN_TYPE(是否外域资源)
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryResourceListV2
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT RES_ITEM_V2_S                   *pstResList
);

/** @} */ /* end of ORG MANAGEMENT MODULE */

#if 0
#endif
/*******************************************************************************
设备-EC
*******************************************************************************/
/** @defgroup groupEC 编码器(EC),解码器(DC)管理
*   该模块包括EC的增删改查以及配置EC通道,串口,开关量等接口;同时也包括了DC的增删改查以及配置DC通道,串口,开关量等接口
*   @{
*/
/**
* @name 编码器(EC)
* @{    编码器(EC)
*/
/**
* 增加编码器
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstEcInfo                   EC设备信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* - #ERR_AS_EC_NUM_EXCEEDED
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.EC编码不能填空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddEc
(
    IN    USER_LOGIN_ID_INFO_S          *pstUserLogIDInfo,
    IN    EC_INFO_S                     *pstEcInfo
);



/**
* 修改编码器信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstEcInfo                   编码器信息
* @param [IN]   bIsEncodeChange             流套餐是否变更标识, BOOL_TRUE为变更了流套餐; BOOL_FALSE为未变更流套餐
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 编码器信息中的EC编码不可修改, 但需要填写
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyEc
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  EC_INFO_S                       *pstEcInfo,
    IN  BOOL_T                          bIsEncodeChange
);



/**
* 删除编码器
* @param [IN] pstUserLogIDInfo  用户登录ID信息标识
* @param [IN] szEcCode          EC的编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_HAS_CAMERA
* - #ERR_MM_DEV_CONTAIN_SUBDEVICE
* - #ERR_AS_HAS_TRANSCHNL
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelEc
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szEcCode[IMOS_DEVICE_CODE_LEN]
);


/**
* 重启设备（只支持EC、DC的重启） \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szDevCode           设备编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* - #ERR_MM_DEVICE_OFFLINE
* - #ERR_MM_CONFIGURE_DEVICE_FAIL
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_RebootDevice
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szDevCode[IMOS_CODE_LEN]
);


/**
* 分页查询某个组织下的编码器列表  \n
* 条件为空时,查询该组织下所有编码器,并默认按照"编码器名称升序"排序.
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szOrgCode                   组织编码
* @param [IN]   pstQueryCondition           查询信息条件(可为NULL;支持的查询条件包括:#NAME_TYPE[编码器名称]; #CODE_TYPE[编码器编码]; #RES_TYPE[资源类型])
* @param [IN]   pstQueryPageInfo            请求分页信息
* @param [OUT]  pstRspPageInfo              响应分页信息
* @param [OUT]  pstEcList                   编码器列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryEcList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT EC_QUERY_ITEM_S                 *pstEcList
);



/**
* 查询编码器的信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szEcCode                    编码器编码
* @param [OUT]  pstEcInfo                   编码器信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryEcInfo
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szEcCode[IMOS_DEVICE_CODE_LEN],
    OUT EC_INFO_S                       *pstEcInfo
);
/** @} */ /* End of EC */


#if 0
#endif
/***************************************************************************
设备-EC通道以及摄像机
****************************************************************************/
/**
* @name EC通道
* @{    EC通道
*/
/**
* 将摄像机绑定到编码器的某个通道上
* @param [IN]  pstUserLogIDInfo             用户登录ID信息标识
* @param [IN]  pstVinChnlAndCamInfo         摄像机及其绑定通道的信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.摄像机编码不能为空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_BindCameraToVideoInChannel
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  VINCHNL_BIND_CAMERA_S           *pstVinChnlAndCamInfo

);



/**
* 分页查询EC设备下的摄像机以及通道列表 \n
* 条件为空时,查所有,并按照默认条件(视频输入通道索引升序)排序
* @param [IN]   pstUserLogIDInfo       用户登录ID信息标识
* @param [IN]   szDevCode              编码器编码
* @param [IN]   pstQueryCondition      通用查询条件(可为NULL;支持的查询条件包括:INDEX_TYPE[通道索引])
* @param [IN]   pstQueryPageInfo       请求分页信息
* @param [OUT]  pstRspPageInfo         响应分页信息
* @param [OUT]  pstCamAndChannelList   摄像机以及通道信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIN_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryCameraAndChannelList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szDevCode[IMOS_DEVICE_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT CAM_AND_CHANNEL_QUERY_ITEM_S    *pstCamAndChannelList
);



/**
* 修改摄像机
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstCamInfo                  摄像机信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_CAMERA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyCamera
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CAMERA_INFO_S                   *pstCamInfo
);


/**
* 解除绑定摄像机
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szCamCode           摄像机编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_CAMERA_NOT_EXIST
* @note 1.调用解除绑定摄像机接口后，该摄像机的所有信息都将被删除；
* -     2.如该摄像机还配置存储资源，则调用该接口将失败
*/
IMOS_EXPORT ULONG STDCALL IMOS_UnBindCamera
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN]
);


/**
* 查询摄像机信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szCamCode                   摄像机编码
* @param [OUT]  pstCameraInfo               摄像机信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_CAMERA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryCamera
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    OUT CAMERA_INFO_S                   *pstCameraInfo
);



/**
* 设置EC输入通道信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstChannelIndex             设备通道索引信息
* @param [IN]   pstVideoInChannelInfo       输入通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIN_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigVideoInChannel
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S             *pstChannelIndex,
    IN  VIN_CHANNEL_S                   *pstVideoInChannelInfo
);


/**
* 查询EC输入通道信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstChannelIndex             设备通道索引信息
* @param [OUT]  pstVideoInChannelInfo       输入通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIN_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryECVideoInChannel
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S             *pstChannelIndex,
    OUT VIN_CHANNEL_S                   *pstVideoInChannelInfo
);


/**
* 设置EC视频输入通道流信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstChannelIndex             设备通道索引信息
* @param [IN]   pstVideoStreamInfo          视频输入通道流信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIN_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigECVideoStream
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S             *pstChannelIndex,
    IN  VIDEO_STREAM_S                  *pstVideoStreamInfo
);


/**
* 查询EC视频输入通道流信息
* @param [IN]       pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]       pstChannelIndex             设备通道索引信息
* @param [IN][OUT]  pulStreamNum                输入通道视频流的数量, 取决于编码器的流套餐选择, 最大取值为2
* @param [OUT]      pstVideoStreamInfo          视频流信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIDEO_STREAM_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryECVideoStream
(
    IN    USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN    DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    INOUT ULONG                       *pulStreamNum,
    OUT   VIDEO_STREAM_S              *pstVideoStreamInfo
);

/**
* 设置EC输入通道遮盖区域信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  ulMaskAreaNum            输入通道遮盖区域的个数, 最大取值为#IMOS_MASK_AREA_MAXNUM
* @param [IN]  pstMaskArea              输入通道遮盖区域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIDEO_AREA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigECMaskAreaOSD
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  ULONG                        ulMaskAreaNum,
    IN  VIDEO_AREA_S                *pstMaskArea
);

/**
* 查询EC输入通道遮盖区域信息
* @param [IN]       pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]       pstChannelIndex          设备通道索引信息
* @param [IN][OUT]  pulMaskAreaNum           输入通道遮盖区域的个数, 最大取值为#IMOS_MASK_AREA_MAXNUM
* @param [OUT]      pstMaskArea              输入通道遮盖区域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIDEO_AREA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryECMaskAreaOSD
(
    IN    USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN    DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    INOUT ULONG                       *pulMaskAreaNum,
    OUT   VIDEO_AREA_S                *pstMaskArea
);


/**
* 设置EC输入通道运动检测区域信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  ulMotionDetectAreaNum    输入通道运动检测区域的个数, 最大取值为#IMOS_DETECT_AREA_MAXNUM
* @param [IN]  pstMotionDetectArea      输入通道运动检测区域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIDEO_AREA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigECMotionDetectArea
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  ULONG                        ulMotionDetectAreaNum,
    IN  VIDEO_AREA_S                *pstMotionDetectArea
);

/**
* 查询EC输入通道运动检测区域信息
* @param [IN]       pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]       pstChannelIndex          设备通道索引信息
* @param [IN][OUT]  pulMotionDetectAreaNum   输入通道运动检测区域的个数, 最大取值为#IMOS_DETECT_AREA_MAXNUM
* @param [OUT]      pstMotionDetectArea      输入通道运动检测区域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VIDEO_AREA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryECMotionDetectArea
(
    IN    USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN    DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    INOUT ULONG                       *pulMotionDetectAreaNum,
    OUT   VIDEO_AREA_S                *pstMotionDetectArea
);

/**
* 设置设备的通道时间OSD信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  pstTimeOSD               输入通道时间OSD信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_OSD_TIME_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigDeviceTimeOSD
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  OSD_TIME_S                  *pstTimeOSD
);

/**
* 查询设备的通道时间OSD信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [OUT] pstTimeOSD               输入通道时间OSD信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_OSD_TIME_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDeviceTimeOSD
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    OUT OSD_TIME_S                  *pstTimeOSD
);

/**
* 设置设备的通道场名OSD信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  ulNameOSDNum             输入通道场名OSD的个数, 最大取值为#IMOS_OSD_NAME_MAXNUM;
*                                       该值与设备类型相关:当设备类型为EC2004-HF/VR2004/EC2016-HC[4CH]/EC2016-HC[8CH]/EC2016-HC时,该值为#IMOS_OSD_NAME_MAXNUM_II;
*                                       除以上几种类型的EC设备外,设备类型为其它类型EC时,该值为#IMOS_OSD_NAME_MAXNUM;
*                                       当设备类型为DC时,该值为#IMOS_OSD_NAME_MAXNUM_I
* @param [IN]  pstNameOSD               输入通道场名OSD信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_OSD_NAME_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigDeviceNameOSD
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  ULONG                        ulNameOSDNum,
    IN  OSD_NAME_S                  *pstNameOSD
);

/**
* 查询设备的通道场名OSD信息
* @param [IN]       pstUserLogIDInfo      用户登录ID信息标识
* @param [IN]       pstChannelIndex       设备通道索引信息
* @param [IN][OUT]  pulNameOSDNum         输入通道场名OSD个数, 最大取值为#IMOS_OSD_NAME_MAXNUM;
*                                         该值与设备类型相关:当设备类型为EC2004-HF/VR2004/EC2016-HC[4CH]/EC2016-HC[8CH]/EC2016-HC时,该值为#IMOS_OSD_NAME_MAXNUM_II;
*                                         除以上几种类型的EC设备外,设备类型为其它类型EC时,该值为#IMOS_OSD_NAME_MAXNUM;
*                                         当设备类型为DC时,该值为#IMOS_OSD_NAME_MAXNUM_I
* @param [OUT]      pstNameOSD            输入通道场名OSD信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_OSD_NAME_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDeviceNameOSD
(
    IN    USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN    DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    INOUT ULONG                       *pulNameOSDNum,
    OUT   OSD_NAME_S                  *pstNameOSD
);

/** @} */ /* end of CAMERA & CHANNEL MANAGEMENT MODULE */

#if 0
#endif
/*******************************************************************************
设备-DC
*******************************************************************************/
/**
* @name 解码器(DC)
* @{    解码器(DC)
*/
/**
* 增加解码器
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstDcInfo               解码器信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* - #ERR_AS_DC_NUM_EXCEEDED
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.DC编码不能填空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddDc
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DC_INFO_S                   *pstDcInfo
);



/**
* 修改解码器信息，其中设备编码不可能修改，但是需要带入。
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   pstDcInfo                   完整的解码器信息
* @param [IN]   bIsEncodeChange             流套餐是否变更标识, BOOL_TRUE为更改了流套餐; BOOL_FALSE为未更改流套餐
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyDc
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  DC_INFO_S                       *pstDcInfo,
    IN  BOOL_T                          bIsEncodeChange
);


/**
* 删除解码器
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szDcCode                    解码器编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_HAS_MONITOR
* - #ERR_MM_DEV_CONTAIN_SUBDEVICE
* - #ERR_AS_HAS_TRANSCHNL
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelDc
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szDcCode[IMOS_DEVICE_CODE_LEN]
);


/**
* 分页查询某个组织下的解码器列表  \n
* 条件为空时,查询所有解码器,并默认按照"解码器名称升序"排序.
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szOrgCode                   组织编码
* @param [IN]   pstQueryCondition           通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[解码器名称]; #CODE_TYPE[解码器编码])
* @param [IN]   pstQueryPageInfo            请求分页信息
* @param [OUT]  pstRspPageInfo              响应分页信息
* @param [OUT]  pstDcQueryList              解码器信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDcList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szcOrgCode[IMOS_RES_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT DC_QUERY_ITEM_S                 *pstDcQueryList
);



/**
* 查询解码器的信息
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szDcCode                    解码器的编码
* @param [OUT]  pstDcInfo                   解码器信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDcInfo
(
    IN   USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN   CHAR                           szDcCode[IMOS_DEVICE_CODE_LEN],
    OUT  DC_INFO_S                      *pstDcInfo
);
/** @} */ /* end of DC MANAGEMENT MODULE */



#if 0
#endif
/***************************************************************************
设备-DC通道以及监视器
****************************************************************************/
/**
* @name DC通道
* @{    DC通道
*/
/**
* 将监视器绑定到DC的某个通道上
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstVOUTChnlAndScrInfo    监视器及其绑定通道的信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.监视器编码不能为空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_BindScreenToVideoOutChannel
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  VOUTCHNL_BIND_SCREEN_S  *pstVOUTChnlAndScrInfo

);

/**
* 查询某个DC设备的通道以及监视器信息列表 \n
* 条件为空时,查询所有通道以及监视器,并默认按照"视频输出通道索引升序"排序
* @param [IN]   pstUserLogIDInfo       用户登录ID信息标识
* @param [IN]   szDevCode              设备编码
* @param [IN]   pstQueryCondition      通用查询条件(可为NULL;支持的查询条件包括:INDEX_TYPE[视频输出通道索引])
* @param [IN]   pstQueryPageInfo       请求分页信息
* @param [OUT]  pstRspPageInfo         响应分页信息
* @param [OUT]  pstVOUTChnlAndScrList  监视器及其绑定通道的列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryScreenAndChannelList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szDevCode[IMOS_DEVICE_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT SCR_AND_CHANNEL_QUERY_ITEM_S    *pstVOUTChnlAndScrList
);



/**
* 修改监视器信息
* @param [IN]  pstUserLogIDInfo                     用户登录ID信息标识
* @param [IN]  pstScrInfo                           监视器信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 监视器信息中的监视器编码不可修改
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyScreen
(
    IN   USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN   SCREEN_INFO_S                  *pstScrInfo
);



/**
* 解除绑定监视器
* @param [IN] pstUserLogIDInfo                      用户登录ID信息标识
* @param [IN] szScrCode                             监视器编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_UnBindScreen
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szScrCode[IMOS_RES_CODE_LEN]
);


/**
* 查询某个监视器的具体信息
* @param [IN] pstUserLogIDInfo                          用户登录ID信息标识
* @param [IN] szScrCode                                 监视器编码
* @param [OUT]pstScrInfo                                监视器信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryScreen
(
    IN    USER_LOGIN_ID_INFO_S          *pstUserLogIDInfo,
    IN    CHAR                          szScrCode[IMOS_RES_CODE_LEN],
    OUT   SCREEN_INFO_S                 *pstScreenInfo
);


/**
* 设置DC的视频逻辑输出通道信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  ulVideoOutNum            物理通道包含逻辑通道的数量
* @param [IN]  pstVideoInChannelInfo    视频逻辑输出通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VOUT_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigDCVideoOutChannel
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S     *pstChannelIndex,
    IN  ULONG                    ulVideoOutNum,
    IN  VOUT_CHANNEL_S          *pstVideoOutChannelInfo
);


/**
* 查询DC的视频逻辑输出通道信息
* @param [IN]       pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]       pstChannelIndex          设备通道索引信息
* @param [IN][OUT]  pulVideoOutNum           物理通道包含逻辑通道的数量
* @param [OUT]      pstVideoOutChannelInfo    视频逻辑输出通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_VOUT_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDCVideoOutChannel
(
    IN    USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN    DEV_CHANNEL_INDEX_S     *pstChannelIndex,
    INOUT ULONG                   *pulVideoOutNum,
    OUT   VOUT_CHANNEL_S          *pstVideoOutChannelInfo
);



/**
* 设置DC物理输出通道信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [IN]  pstPhyoutChannelInfo     物理输出通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_PHYOUT_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigDCPhyOutChannel
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S     *pstChannelIndex,
    IN  PHYOUT_CHANNEL_S        *pstPhyoutChannelInfo
);


/**
* 查询DC的物理输出通道信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstChannelIndex          设备通道索引信息
* @param [OUT] pstPhyoutChannelInfo     物理输出通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_PHYOUT_CHANNEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDCPhyOutChannel
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S     *pstChannelIndex,
    OUT PHYOUT_CHANNEL_S        *pstPhyoutChannelInfo
);

/** @} */ /* end of DC Channel */

/** @} */ /* end of EC/DC Channel Module */

#if 0
#endif
/*******************************************************************************
 设备-EC,DC开关管理
*******************************************************************************/
/**
* @name 设备(EC,DC)开关管理
* @{    设备(EC,DC)开关管理
*/
/**
* 配置设备的输入开关量
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstChannelIndex         设备通道索引信息
* @param [IN]   pstSemaInputInfo        输入开关量信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SEMAPHORE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfInSwitch
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  SEMA_INPUT_INFO_S           *pstSemaInputInfo
);

/**
* 配置设备的输出开关量
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstChannelIndex         设备通道索引信息
* @param [IN]   pstSemaOutputInfo       输出开关量信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SEMAPHORE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfOutSwitch
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    IN  SEMA_OUTPUT_INFO_S          *pstSemaOutputInfo
);



/**
* 查询设备的开关量列表 \n
* 不填查询条件时,查所有,并默认排序(开关量索引升序)
* @param [IN]   pstUserLogIDInfo   用户登录ID信息标识
* @param [IN]   szDevCode          设备编码
* @param [IN]   ulDevType          设备类型, 取值为#IMOS_TYPE_EC或#IMOS_TYPE_DC
* @param [IN]   pstQueryCondition  通用查询条件(可填NULL;支持的查询条件包括:#INDEX_TYPE[开关量索引])
* @param [IN]   pstQueryPageInfo   请求分页信息
* @param [OUT]  pstRspPageInfo     响应分页信息
* @param [OUT]  pstSemaList        开关量信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QuerySwitchList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szDevCode[IMOS_DEVICE_CODE_LEN],
    IN  ULONG                       ulDevType,
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT SEMA_QUERY_ITEM_S           *pstSemaList
);

/**
* 查询输入开关量信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstChannelIndex         设备通道索引信息
* @param [OUT]  pstSemaInputInfo        输入开关量信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SEMAPHORE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryInSwitch
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    OUT SEMA_INPUT_INFO_S           *pstSemaInputInfo
);

/**
* 查询输出开关量信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstChannelIndex         设备通道索引信息
* @param [OUT]  pstSemaOutputInfo       输出开关量信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SEMAPHORE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryOutSwitch
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DEV_CHANNEL_INDEX_S         *pstChannelIndex,
    OUT SEMA_OUTPUT_INFO_S          *pstSemaOutputInfo
);
/** @} */ /* end of SWITCH MANAGEMENT MODULE */

#if 0
#endif
/**************************************************************************************************************
设备-DM
***************************************************************************************************************/
/** @defgroup groupDm 服务器管理
*   服务器管理包括DM,VX500,MS,存储设备管理等
*   @{
*/
/**
* @name DM管理
* @{    DM管理
*/
/**
* 增加DM服务器 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstSDKDMInfo        DM信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_LICENSE_EXCEEDED
* - #ERR_AS_DM_NUM_EXCEEDED
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.DM信息中的DM编码是DM服务器的唯一标识
* -     2.DM编码不能填空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddDM
(
    IN USER_LOGIN_ID_INFO_S         *pstUserLogIDInfo,
    IN DM_INFO_S                    *pstSDKDMInfo
);


/**
* 修改DM信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstSDKDMInfo        DM信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note DM信息中的DM编码不可修改, 但在修改DM信息时需要填写
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyDM
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  DM_INFO_S                   *pstSDKDMInfo
);


/**
* 删除DM服务器 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szDMCode            DM编码
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_HAS_STORAGE_DEV
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelDM
(
    IN USER_LOGIN_ID_INFO_S         *pstUserLogIDInfo,
    IN CHAR                         szDMCode[IMOS_DEVICE_CODE_LEN]
);


/**
* 分页查询某个组织下的DM列表  \n
* 支持按DM名进行模糊查询，目前只支持组织编码szOrgCode允许为空串的查询。
* 条件为空时,查询所有DM,并默认按照"DM名称升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   pstQueryCondition   通用查询条件(可填NULL;支持的查询条件包括:#NAME_TYPE[DM名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstSDKDMList        DM列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note  1、szOrgCode允许为空串，表示查询本系统所有的DM列表
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDMList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT DM_QUERY_ITEM_S             *pstSDKDMList
);


/**
* 查询某个DM的具体信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szDMCode            DM编码
* @param [OUT]  pstSDKDMInfo        DM信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDMInfo
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szDMCode[IMOS_DEVICE_CODE_LEN],
    OUT DM_INFO_S                   *pstSDKDMInfo
);
/** @} */ /* end of DEVICE DM MANAGEMENT MODULE */

#if 0
#endif
/***************************************************************************
设备-存储设备
****************************************************************************/
/**
* @name 存储设备管理
* @{    存储设备管理
*/
/**
* 增加存储设备 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstStoreDevInfo     存储设备信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_IPSAN_NUM_PER_DM_EXCEEDED
* - #ERR_MP_ISM_USERNAME
* - #ERR_MP_ISM_GET_CAPACITY
* - #ERR_DAO_STORAGE_CODE_EXIST
* - #ERR_DAO_STORAGE_NAME_EXIST
* - #ERR_DAO_STORAGE_ADDR_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 存储设备信息中的存储设备编码是存储设备的唯一标识
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddStorageDev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  STORE_DEV_INFO_S            *pstStoreDevInfo
);


/**
* 修改存储设备信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstStoreDevInfo     存储设备信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_NAME_EXIST
* - #ERR_DAO_STORAGE_ADDR_EXIST
* - #ERR_DAO_STORAGE_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 存储设备信息中的存储设备编码不可修改, 但修改存储设备信息时需要填写
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyStorageDev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  STORE_DEV_INFO_S            *pstStoreDevInfo
);


/**
* 删除存储设备 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szStorageDevCode    存储设备编码
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelStorageDev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szStorageDevCode[IMOS_DEVICE_CODE_LEN]
);


/**
* 扫描存储设备容量 \n
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szStorageDevCode        存储设备编码
* @param [IN]   ulStorageDevType        存储设备类型，取值为#STORE_DEV_TYPE_E
* @param [OUT]  pulStoreDevTotalSize    存储设备总容量(单位: MB)
* @param [OUT]  pulStoreDevUsedSize     存储设备已用容量(单位: MB)
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_CODE_NOT_EXIST
* - #ERR_DAO_ISC_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ScanStorageDevSize
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szStorageDevCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulStorageDevType,
    OUT ULONG                           *pulStoreDevTotalSize,
    OUT ULONG                           *pulStoreDevUsedSize
);


/**
* 分页查询某个组织下的存储设备列表  \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[存储设备名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstStoreDevList     存储设备列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1、szOrgCode为空串时表示查询本系统所有的存储设备列表。
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryOrgStorageDevList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT STORE_DEV_QUERY_ITEM_S      *pstStoreDevList
);


/**
* 查询某个存储设备信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szStorageDevCode    存储设备编码
* @param [OUT]  pstStoreDevInfo     存储设备信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryStorageDev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szStorageDevCode[IMOS_DEVICE_CODE_LEN],
    OUT STORE_DEV_INFO_S            *pstStoreDevInfo
);
/** @} */ /* end of DEVICE STORAGE MANAGEMENT MODULE */


#if 0
#endif
/***************************************************************************
设备-VX500
****************************************************************************/
/**
* @name VX500管理
* @{    VX500管理
*/
/**
* 增加VX500 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstVX500Info        VX500信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_NUM_EXCEEDED
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.VX500编码不能填空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddVX500Dev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  VX500_INFO_S                *pstVX500Info
);


/**
* 修改VX500信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstVX500Info        VX500信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyVX500Dev
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  VX500_INFO_S                *pstVX500Info
);


/**
* 删除VX500 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500设备编码
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_CODE_NOT_EXIST
* - #ERR_DAO_ISC_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelVX500Dev
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szVX500Code[IMOS_DEVICE_CODE_LEN]
);


/**
* 分页查询某个组织下的VX500列表  \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:#CODE_TYPE[VX500编码]; #NAME_TYPE(VX500名称))
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstVX500List        VX500列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1、szOrgCode允许为空串，表示查询本系统所有的VX500列表。
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryVX500List
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT VX500_QUERY_ITEM_S          *pstVX500List
);


/**
* 查询某个VX500信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [OUT]  pstVX500Info        VX500信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryVX500Info
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szVX500Code[IMOS_DEVICE_CODE_LEN],
    OUT VX500_INFO_S                *pstVX500Info
);


/**
* 分页查询某个VX500槽位列表 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstVX500SlotList    VX500槽位列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_DEV_NOT_ONLINE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryVX500SlotList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT SLOT_INFO_S                 *pstVX500SlotList
);


/**
* 添加磁盘阵列 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   pstArrayInfo        阵列信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_DEV_NOT_ONLINE
* - #ERR_MP_SS_OTHER_ARRAY_INSYNC
* - #ERR_MP_SS_ARRAY_CREATE
* - #ERR_MP_SS_ARRAY_EXIST
* - #ERR_MP_SS_DISK_NOT_FREE
* - #ERR_MP_SS_DISK_SIZE_ABNORMAL
* - #ERR_MP_SS_DISK_QUERY
* - #ERR_MP_SS_UPDATECFG_FAILED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddVX500Array
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  ARRAY_INFO_S                *pstArrayInfo
);


/**
* 查询磁盘阵列列表 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      返回分页信息
* @param [OUT]  pstArrayList        VX500磁盘阵列列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryVX500ArrayList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT ARRAY_STATUS_INFO_S         *pstArrayList
);


/**
* 虚拟化阵列，给阵列分配逻辑空间 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   szArrayName         阵列名称
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_DEV_NOT_ONLINE
* - #ERR_MP_SS_ARRAY_HASVIRTUALIZED
* - #ERR_MP_SS_ARRAY_INITIALIZING
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_VirtualizeVX500Array
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  CHAR                            szArrayName[IMOS_NAME_LEN]
);


/**
* 删除阵列 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   szArrayName         阵列名称
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_DEV_NOT_ONLINE
* - #ERR_MP_SS_ARRAY_NOEXIST
* - #ERR_MP_SS_ARRAY_DELETE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelVX500Array
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  CHAR                            szArrayName[IMOS_NAME_LEN]
);


/**
* 重建阵列，将一个良好的槽位，加入阵列，替代已损坏的槽位 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szVX500Code         VX500编码
* @param [IN]   szArrayName         阵列名称
* @param [IN]   ulSlotNum           槽位号
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_VX500_DEV_NOT_ONLINE
* - #ERR_MP_SS_ARRAY_NOEXIST
* - #ERR_MP_SS_OTHER_ARRAY_INSYNC
* - #ERR_MP_SS_DISK_NOT_FREE
* - #ERR_MP_SS_ARRAY_REBUILD
* - #ERR_MP_SS_DISK_QUERY
* - #ERR_MP_SS_DISK_SIZE_ABNORMAL
* - #ERR_MP_SS_UPDATECFG_FAILED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ReBuildVX500Array
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szVX500Code[IMOS_DEVICE_CODE_LEN],
    IN  CHAR                            szArrayName[IMOS_NAME_LEN],
    IN  ULONG                           ulSlotNum
);
/** @} */ /* end of DEVICE VX500 MANAGEMENT MODULE */


#if 0
#endif
/**************************************************************************************************************
设备-MS
***************************************************************************************************************/
/**
* @name MS设备管理
* @{    MS设备管理
*/
/**
* 增加MS服务器 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstSDKMSInfo        MS信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_MS_NUM_EXCEEDED
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* - #ERR_DAO_DEVICE_CODE_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1.MS信息中的MS编码是MS的唯一标识
* -     2.MS编码不能填空,且不能包含空格
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddMS
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  MS_INFO_S                   *pstSDKMSInfo
 );


/**
* 删除MS \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szMSCode            MS编码
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_MP_CODE_NOT_EXIST
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelMS
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szMSCode[IMOS_DEVICE_CODE_LEN]
);


/**
* 修改MS信息 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstSDKMSInfo        MS信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note MS信息中的MS编码不能修改, 在修改MS信息的时候需要传入
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyMS
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  MS_INFO_S                   *pstSDKMSInfo
);


/**
* 查询某个组织下的MS列表  \n
* 目前只支持组织编码szOrgCode允许为空串的查询。
* 条件为空时,查所有MS,并默认"MS名称升序排序"
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szOrgCode           组织编码
* @param [IN]   pstQueryCondition   通用查询条件(可填NULL;支持的查询条件包括:#NAME_TYPE[MS名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstSDKMSList        MS列表
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 1、szOrgCode允许为空串，表示查询本系统所有的MS列表。
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryMSList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT MS_QUERY_ITEM_S             *pstSDKMSList
);


/**
* 查询MS的详细信息
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szMSCode            MS编码
* @param [OUT]  pstSDKMSInfo        MS信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DEVICE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryMSInfo
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szMSCode[IMOS_DEVICE_CODE_LEN],
    OUT MS_INFO_S               *pstSDKMSInfo
);
/** @} */
/** @} */ /* end of DEVICE MS MANAGEMENT MODULE */

#if 0
#endif
/*******************************************************************************
 本域外域管理
*******************************************************************************/
/** @defgroup groupDomainMg 本域外域管理
*   本域外域管理
*   @{
*/
/**
* @name 本域外域
* @{    本域外域
*/

/**
* 查询本域信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [OUT]  pstLoDomain             本域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryLoDomain
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    OUT  LO_DOMAIN_S                *pstLoDomain
);



/**
* 增加外域
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstOutDomain            外域信息结构体
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_INTERDOMAIN_LEVEL_INVALID
* - #ERR_AS_LODOMAIN_INTERINFO_NOT_EXIST
* - #ERR_AS_EXDOMAIN_LEVEL_INVALID
* - #ERR_AS_INTER_DOMAIMCODE_ALREADY_EXIST
* - #ERR_AS_INTER_USERCODE_ALREADY_EXIST
* - #ERR_DAO_DOMAIN_CODE_EXIST
* - #ERR_DAO_INTER_DOMAIN_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddExDomain
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   EX_DOMAIN_S                *pstExDomain
);



/**
* 修改外域信息
* @param [IN]  pstUserLogIDInfo         用户登录ID信息标识
* @param [IN]  pstExDomain              外域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_DOMAIN_NOT_EXIST
* - #ERR_AS_EXDOMAIN_SERVICE_FAIL
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 外域信息中的外域编码不可修改, 在修改外域信息时需要填写
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyExDomain
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   EX_DOMAIN_S                *pstExDomain
);



/**
* 删除外域
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szExDomainCode          外域编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_EXDOMAIN_SERVICE_FAIL
* - #ERR_DAO_INTER_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelExDomain
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   CHAR                       szExDomainCode[IMOS_DOMAIN_CODE_LEN]
);



/**
* 查询外域信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szExDomainCode          外域编码
* @param [OUT]  pstExDomain             外域信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_EXDOMAIN_SERVICE_FAIL
* - #ERR_DAO_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryExDomain
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   CHAR                       szExDomainCode[IMOS_DOMAIN_CODE_LEN],
    OUT  EX_DOMAIN_S                *pstExDomain
);



/**
* 分页查询外域列表 \n
* 条件为空时,查询所有外域,并默认按照"外域名称升序"排序.
* @param [IN]   pstUserLogIDInfo       用户登录ID信息标识
* @param [IN]   pstQueryCondition      通用查询条件
* @param [IN]   pstQueryPageInfo       请求分页信息
* @param [OUT]  pstRspPageInfo         响应分页信息
* @param [OUT]  pstExDomainList        外域信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1. 支持按外域编码、名称、类型、IP、端口、干线数量、域间组播策略、引流标志排序，对应通用查询条件中的查询项类型分别为:
* -   #CODE_TYPE、#NAME_TYPE、#EXT_DOMAIN_TPYE、#EXT_DOMAIN_IP、#EXT_DOMAIN_TRUNK_NUM、#EXT_DOMAIN_TRUNK_NUM、
* -   #EXT_DOMAIN_MULTICAST、#EXT_DOMAIN_SESSION;
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryExDomainList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT EX_DOMAIN_S                 *pstExDomainList
);


/**
* 设置互联信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstInterConnectInfo     互联信息结构体
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_INTERDOMAIN_LEVEL_INVALID
* - #ERR_AS_INTERDOMAIM_PARAM_CANNOT_MODIFY
* - #ERR_AS_INTER_USERCODE_ALREADY_EXIST
* - #ERR_DAO_INTER_DOMAIN_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 目前只有对本域设置互联信息
*/
IMOS_EXPORT ULONG STDCALL IMOS_SetInterconnectInfo
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   INTERCONNECT_INFO_S        *pstInterConnectInfo
);


/**
* 查询互联信息
* @param [IN]   pstUserLogIDInfo                  用户登录ID信息标识
* @param [IN]   szResCode[IMOS_RES_CODE_LEN]      互联信息所属资源编码
* @param [IN]   ulInterInfoType                   互联信息类型，取值为#INTERCONNECT_INFO_TYPE_E
* @param [IN]   ulProtocolType                    互联协议类型，取值为#INTERDOMAIN_PROTOCOL_TYPE_E
* @param [OUT]  pstInterConnect                   互联信息结构体
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_INTER_DOMAIN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryInterconnectInfo
(
    IN   USER_LOGIN_ID_INFO_S       *pstUserLogIDInfo,
    IN   CHAR                       szResCode[IMOS_RES_CODE_LEN],
    IN   ULONG                      ulInterInfoType,
    IN   ULONG                      ulProtocolType,
    OUT  INTERCONNECT_INFO_S        *pstInterConnect
);


/***************************************************************************
共享摄像机管理
****************************************************************************/
/**
* @name 摄像机共享管理
* @{    摄像机共享管理
*/
/**
* 共享摄像机处理, 包括共享和取消共享
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szExDomainCode          外域编码
* @param [IN]   ulShareFlag             共享处理类型标识: 0为取消共享，1为共享
* @param [IN]   ulShareCamNum           摄像机的个数, 最大值为32
* @param [IN]   pstShareCamList         共享/取消摄像机列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_INTER_DOMAIN_NOT_EXIST
* - #ERR_AS_INTER_CAMCODE_ALREADY_EXIST
* - #ERR_MM_PARENT_DEIVCE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ProcessShareCamera
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szExDomainCode[IMOS_DOMAIN_CODE_LEN],
    IN  ULONG                   ulShareFlag,
    IN  ULONG                   ulShareCamNum,
    IN  SHARE_CAMERA_BASE_S     *pstShareCamList
);


/**
* 分页查询外域下的共享摄像机列表
* 条件为空时,查询所有共享摄像机,并默认按照"共享摄像机名称升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szExDomainCode      外域编码
* @param [IN]   ulQueryFlag         查询标记, 0为查本域共享给外域的摄像机，1为查外域共享给本域的摄像机
* @param [IN]   pstQueryCondition   通用查询条件(可为NULL;支持的查询条件包括:#CODE_TYPE[共享摄像机编码]、#NAME_TYPE[共享摄像机名称])
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstShareCamList     共享摄像机列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryShareCamera
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szExDomainCode[IMOS_DOMAIN_CODE_LEN],
    IN  ULONG                       ulQueryFlag,
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT SHARE_CAM_INFO_S            *pstShareCamList
);

/**
* 删除外域共享摄像机
* @param [IN]   pstUserLogIDInfo            用户登录ID信息标识
* @param [IN]   szCamCode                   待删除的摄像机编码
* @param [IN]   szExdomainCode              外域编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SHARE_CAMERA_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelCameraSharedInExdomain
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    IN  CHAR                            szExdomainCode[IMOS_DOMAIN_CODE_LEN]
);
/** @} */ /* end of 摄像机共享 */
/** @} */ /* end of DOMAIN MANAGEMENT MODULE */

/***************************************************************************
预置位
****************************************************************************/
/** @defgroup groupPresetMg 预置位管理
*   预置位管理
*   @{
*/
/**
* 设置预置位
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szCamCode           摄像机编码
* @param [IN]   stPreset            预置位信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_PRESET_INVALID
* - #ERR_AS_CAMERA_OFFLINE
* - #ERR_DAO_PRESET_VALUE_NOT_EXIST
* - #ERR_AS_CAMERA_NOT_PTZTYPE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_SetPreset
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szCamCode[IMOS_RES_CODE_LEN],
    IN  PRESET_INFO_S           *pstPreset
);


/**
* 删除预置位
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szCamCode           摄像头编码
* @param [IN]   ulPresetValue       预置位值
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAMERA_OFFLINE
* - #ERR_DAO_PRESET_VALUE_NOT_EXIST
* - #ERR_AS_CAMERA_NOT_PTZTYPE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelPreset
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szCamCode[IMOS_RES_CODE_LEN],
    IN  ULONG                       ulPresetValue
);


/**
* 分页查询摄像机的预置位
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          响应分页信息
* @param [OUT]  pstPresetList           预置位信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryPresetList
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szCamCode[IMOS_RES_CODE_LEN],
    IN  QUERY_PAGE_INFO_S       *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S         *pstRspPageInfo,
    OUT PRESET_INFO_S           *pstPresetList
);


/**
* 使用预置位
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szCamCode           摄像机编码
* @param [IN]   ulPresetNum         预置位值，取值范围为#PTZ_PRESET_MINVALUE~服务器配置文件里配置的预置位最大值
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_PRESET_VALUE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_UsePreset
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szCamCode[IMOS_RES_CODE_LEN],
    IN  ULONG                   ulPresetNum
);
/** @} */ /* end of PRESET MANAGEMENT MODULE */

#if 0
#endif
/***************************************************************************
存储资源管理
****************************************************************************/
/** @defgroup groupStorageResMg 存储业务
*   存储业务包括存储资源管理,存储计划管理
*   @{
*/
/**
* @name 存储资源管理
* @{    涉及存储资源的增删改查,以及查询存储资源列表接口
*/
/**
* 分配存储资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   pstStoreResInfo         存储资源信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAM_NOT_LOCAL_DOMAIN
* - #ERR_AS_STORE_RES_ALLOCATED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AssignStoreRes
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    IN  STORE_RES_INFO_S                *pstStoreResInfo
);


/**
* 扩大存储资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   pstStoreResInfo         存储资源信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAM_NOT_LOCAL_DOMAIN
* - #ERR_AS_STORE_RES_UNALLOCATED
* - #ERR_AS_STORE_DEV_OFFLINE
* - #ERR_MP_ISM_CAPACITY_NOT_ENOUGH
* - #ERR_DAO_CAM_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ExpandStoreRes
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    IN  STORE_RES_INFO_S                *pstStoreResInfo
);


/**
* 删除存储资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_STORE_RES_UNALLOCATED
* - #ERR_AS_STORE_DEV_OFFLINE
* - #ERR_DAO_CAM_CODE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelStoreRes
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN]
);


/**
* 查询存储资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [OUT]  pstStoreResInfo         分配的存储资源信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_NOT_EXIST
* - #ERR_DAO_STORE_RES_NOT_EXIST
* - #ERR_DAO_EVENT_STORAGE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryStoreRes
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    OUT STORE_RES_INFO_S                *pstStoreResInfo
);


/**
* 分页查询某个组织下摄像机存储资源分配情况列表
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               组织编码
* @param [IN]   pstQueryCondition       通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[摄像机名称])
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          响应分页信息
* @param [OUT]  pstStoreResList         摄像机存储资源分配信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryCamStoreResList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT STORE_RES_QUERY_ITEM_S      *pstStoreResList
);
/** @} */ /* end of name 存储资源管理 */
#if 0
#endif
/***************************************************************************
存储计划
****************************************************************************/
/**
* @name 存储计划管理
* @{    涉及存储计划的删改查,以及查询存储计划列表接口
*/

/**
* 修改存储计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szStorePlanCode         存储计划编码
* @param [IN]   pstStorePlan            存储计划信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_PLAN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 启动存储计划需要调用IMOS_ProcessStorePlan接口; 而通过修改计划时间的方式不能够自动使计划启动/停止
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifyStorePlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szStorePlanCode[IMOS_RES_CODE_LEN],
    IN  STORAGE_PLAN_INFO_S             *pstStorePlanInfo
);


/**
* 删除存储计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szStorePlanCode         存储计划编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_PLAN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelStorePlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szStorePlanCode[IMOS_RES_CODE_LEN]
);


/**
* 分页查询存储计划列表
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               组织编码
* @param [IN]   bConditionFlag          查询条件标志。BOOL_TRUE为要使用条件查询，BOOL_FALSE为不需要条件查询
* @param [IN]   pstQueryCondition       查询条件结构指针：包含名称和时间的查询条件。如果bConditionFlag为FALSE时，可以为NULL。
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          返回分页信息
* @param [OUT]  pstStorePlanList        存储计划列表信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryStorePlanList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  BOOL_T                      bConditionFlag,
    IN  QUERY_CONDITION_INFO_S      *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT STORY_PLAN_QUERY_ITEM       *pstStorePlanList
);


/**
* 查询存储计划信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szStorePlanCode         存储计划编码
* @param [OUT]  pstStorePlan            存储计划信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_PLAN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryStorePlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szStorePlanCode[IMOS_RES_CODE_LEN],
    OUT STORAGE_PLAN_INFO_S             *pstStorePlanInfo
);
/** @} */  /* 存储计划结束 */

/**
* @name 存储操作
* @{    存储计划的启动/停止和手动存储的启动停止与查询
*/
/**
* 启动/停止存储计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szStorePlanCode         存储计划编码
* @param [IN]   ulPlanMode              计划处理标记, 0为停止计划, 1为启动计划
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_STORAGE_PLAN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ProcessStorePlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szStorePlanCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulPlanMode
);


/**
* 开始/结束手动存储
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   ulManualRecordMode      手动存储处理标记，0为停止手动存储，1为启动手动存储
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAMERA_OFFLINE
* - #ERR_AS_CAM_NOT_LOCAL_DOMAIN
* - #ERR_AS_STORE_BEING_PROCESSING
* - #ERR_DAO_TRIGGER_STORAGE_NOT_EXIST
* - #ERR_AS_MANUAL_STRORE_ALREADY_STOPED
* - #ERR_AS_STRORE_ALREADY_STARTED
* - #ERR_AS_MANUAL_STRORE_USER_UNMATCH
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ProcessManualRecord
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCamCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulManualRecordMode
);

/**
* 查询手动存储状态信息 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szCameraCode            摄像机编码
* @param [OUT]  pulManStoStatus         手动存储状态, 取值为#MANUAL_STORE_STATUS_E
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAMERA_OFFLINE
* - #ERR_DAO_TRIGGER_STORAGE_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryManualStoreStatus
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN CHAR                             szCameraCode[IMOS_RES_CODE_LEN],
    OUT ULONG                           *pulManStoStatus
);
/** @} */ /* 存储操作结束 */
/** @} */ /* end of STORAGE PLAN MANAGEMENT MODULE */

#if 0
#endif
/***************************************************************************
轮切资源管理
****************************************************************************/
/** @defgroup groupSwitchResMg 轮切管理
*   轮切管理包括轮切资源管理，轮切计划管理和轮切操作
*   @{
*/
/**
* @name 轮切资源管理模块
* @{    轮切资源管理模块
*/
/**
* 增加轮切资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               组织编码
* @param [IN]   pstSwitchInfo           轮切资源信息
* @param [OUT]  szSwitchResCode         轮切资源编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_GUARDTOUR_TIMESLOT_EXCEEDED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddSwitchResource
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  SWITCH_RESOURE_S            *pstSwitchInfo,
    OUT CHAR                        szSwitchResCode[IMOS_RES_CODE_LEN]
);

/**
* 修改轮切资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchResCode         轮切资源编码
* @param [IN]   pstSwitchInfo           轮切资源信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_GUARDTOUR_TIMESLOT_EXCEEDED
* - #ERR_DAO_SWITCH_ID_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifySwitchResource
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szSwitchResCode[IMOS_RES_CODE_LEN],
    IN  SWITCH_RESOURE_S                *pstSwitchInfo
);

/**
* 删除轮切资源
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchResCode         轮切资源编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SWITCH_ID_NOT_EXIST
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelSwitchResource
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                             szSwitchResCode[IMOS_RES_CODE_LEN]
);


/**
* 查询轮切资源信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchResCode         轮切资源编码
* @param [OUT]  pstSwitchInfo           轮切资源信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_SWITCH_ID_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QuerySwitchResource
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szSwitchResCode[IMOS_RES_CODE_LEN],
    OUT SWITCH_RESOURE_S                *pstSwitchInfo
);

/**
* 分页查询某个组织下的轮切资源列表  \n
* 条件为空时,查询组织下所有轮切资源列表,并默认按照"轮切资源名称升序"排序.
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               组织编码
* @param [IN]   pstQueryCondition       通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[轮切资源名称])
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          响应分页信息
* @param [OUT]  pstSwitchResList        轮切资源列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QuerySwitchResList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT SWITCH_RES_QUERY_ITEM_S     *pstSwitchResList
);
/** @} */  //轮切资源管理模块
#if 0
#endif
/***************************************************************************
轮切计划
****************************************************************************/
/**
* @name 轮切计划管理模块
* @{    轮切计划管理模块
*/
/**
* 增加轮切计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstSwitchPlanInfo       轮切计划信息
* @param [OUT]  szSwitchPlanCode        轮切计划编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddSwitchPlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  SWITCH_PLAN_INFO_S              *pstSwitchPlanInfo,
    OUT CHAR                            szSwitchPlanCode[IMOS_RES_CODE_LEN]
);


/**
* 修改轮切计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchPlanCode        轮切计划编码
* @param [IN]   pstSwitchPlanInfo       轮切计划信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_GUARD_TOUR_PLAN_NOT_EXIST
* -     其它错误码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ModifySwitchPlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szSwitchPlanCode[IMOS_RES_CODE_LEN],
    IN  SWITCH_PLAN_INFO_S              *pstSwitchPlanInfo
);


/**
* 删除轮切计划
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchPlanCode        轮切计划编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_GUARD_TOUR_PLAN_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelSwitchPlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szSwitchPlanCode[IMOS_RES_CODE_LEN]
);


/**
* 分页查询轮切计划列表
* 条件为空时,查询所有轮切计划,并默认按照"轮切计划名称升序"排序.
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szOrgCode               组织编码
* @param [IN]   pstQueryCondition       通用查询条件(可为NULL;支持的查询条件包括:#NAME_TYPE[轮切计划名称])
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          响应分页信息
* @param [OUT]  pstSwitchPlanList       轮切计划列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QuerySwitchPlanList
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  CHAR                        szOrgCode[IMOS_DOMAIN_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S    *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT SWITCH_PLAN_QUERY_ITEM_S    *pstSwitchPlanList
);


/**
* 查询轮切计划信息
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szSwitchPlanCode        轮切计划编码
* @param [OUT]  pstSwitchPlanInfo       轮切计划信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_GUARD_TOUR_PLAN_NOT_EXIST
* -     其它错误码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QuerySwitchPlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szSwitchPlanCode[IMOS_RES_CODE_LEN],
    OUT SWITCH_PLAN_INFO_S              *pstSwitchPlanInfo
);
/** @} */  //轮切资源管理模块

/**
* @name 轮切操作
* @{    轮切操作
*/
/**
* 启动手动轮切 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szSwitchResCode         轮切资源编码
* @param [IN]   szMonitorCode           硬解轮切中为监视器编码, 软解轮切中为窗格编码
* @param [IN]   ulOperateCode           操作原因码, 取值为#USER_OPERATE_SERVICE
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_MONITOR_NOT_EXIST
* - #ERR_AS_MONITOR_OFFLINE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartSwitchManual
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szSwitchResCode[IMOS_RES_CODE_LEN],
    IN  CHAR                            szMonitorCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode
);

/**
* 停止手动轮切 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szMonitorCode           硬解轮切中为监视器编码, 软解轮切中为窗格编码
* @param [IN]   ulOperateCode           操作原因码, 取值为#USER_OPERATE_SERVICE
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_MONITOR_NOT_EXIST
* - #ERR_AS_MONITOR_OFFLINE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_StopSwitchManual
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szMonitorCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode
);

/**
* 调整轮切,调整动作包括切换到上一个或下一个摄像机、轮切暂停以及轮切恢复 \n
* @param [IN]   pstUserLoginIDInfo  用户登录ID信息标识
* @param [IN]   szMonitorCode       硬解轮切中为监视器编码, 软解轮切中为窗格编码
* @param [IN]   ulActionType        调整动作,取值为#CS_SWITCH_ADJUST_ACTION_E
* @param [IN]   ulOperateCode       操作原因码, 取值为#USER_OPERATE_SERVICE
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_CS_SWITCH_ABNORMAL_STOP
* - #ERR_CS_SWITCH_DELAY_SETUP
* - #ERR_CS_SWITCH_SUSPENDING
* - #ERR_CS_ALL_SWITCH_CAM_DELETED
* - #ERR_AS_MONITOR_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AdjustSwitch
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szMonitorCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulActionType,
    IN  ULONG                           ulOperateCode
);

/**
* 启动和停止轮切计划 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szSwitchPlanCode        轮切计划编码
* @param [IN]   ulOperateCode           操作模式
* @param [IN]   ulPlanMode              计划处理标记，0停止，1启动
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_CS_PSWITCH_NOT_EXIST
* - #ERR_CS_PLAN_SWITCH_STARTED
* - #ERR_CS_OTHER_PLANSWITCH_START
* -     返回操作结果码：见结果码文件sdk_err.h
* @note ulPlanMode取值参见#PLAN_OPER_MODE_E
*       ulOperateCode取值参见#CS_OPERATE_CODE_E
*/
IMOS_EXPORT ULONG STDCALL IMOS_ProcessSwitchPlan
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szSwitchPlanCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode,
    IN  ULONG                           ulPlanMode
);

/** @} */ /* end of 轮切操作*/
/** @} */ /* end of SWITCH MODULE */

#if 0
#endif
/*******************************************************************************************************
PTZ Ctrl
********************************************************************************************************/
/** @defgroup groupPtzMg 云台业务
*   云台业务
*   @{
*/
/**
* 设置全局云台自动释放的时间
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   ulReleaseTime           云台自动释放时间, 取值为#MIN_PTZ_RELEASE_TIME~#MAX_PTZ_RELEASE_TIME
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_PARAM_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_SetPtzReleaseTime
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  ULONG                           ulReleaseTime
);


/**
* 查询云台自动释放的时间
* @param [IN]    pstUserLogIDInfo        用户登录ID信息标识
* @param [OUT]   pulReleaseTime          云台自动释放时间, 取值为#MIN_PTZ_RELEASE_TIME~#MAX_PTZ_RELEASE_TIME
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryPtzReleaseTime
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    OUT ULONG                           *pulReleaseTime
);


/**
* 启动云台控制
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartPtzCtrl
(
    IN USER_LOGIN_ID_INFO_S             *pstUserLogIDInfo,
    IN CHAR                             szCamCode[IMOS_RES_CODE_LEN]
);


/**
* 释放云台控制权
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   bReleaseSelf            是否仅释放用户自身建立的云台链路, BOOL_TRUE为仅释放用户自身建立的链路; 反之为BOOL_FALSE
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note bReleaseSelf目前仅对系统管理员(admin)起作用，其他用户只能释放自身建立的云台链路
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_ReleasePtzCtrl
(
    IN USER_LOGIN_ID_INFO_S             *pstUserLogIDInfo,
    IN CHAR                             szCamCode[IMOS_RES_CODE_LEN],
    IN BOOL_T                           bReleaseSelf
);


/**
* 用户锁定云台
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_LockPtz
(
    IN USER_LOGIN_ID_INFO_S                 *pstUserLogIDInfo,
    IN CHAR                                 szCamCode[IMOS_RES_CODE_LEN]
);


/**
* 用户解锁云台
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_UnLockPtz
(
    IN USER_LOGIN_ID_INFO_S             *pstUserLogIDInfo,
    IN CHAR                             szCamCode[IMOS_RES_CODE_LEN]
);


/**
* 用户发送云台控制指令
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   szCamCode               摄像机编码
* @param [IN]   pstSDKPtzCtrlCommand    云台控制指令
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_PtzCtrlCommand
(
    IN USER_LOGIN_ID_INFO_S             *pstUserLogIDInfo,
    IN CHAR                             szCamCode[IMOS_RES_CODE_LEN],
    IN PTZ_CTRL_COMMAND_S               *pstSDKPtzCtrlCommand
);

/**
* 查询云台状态
* @param [IN]    pstUserLogIDInfo        用户信息结构
* @param [IN]    szCamCode               摄像机编码
* @param [OUT]   pulStatus               云台状态,取值含义为0代表空闲状态，1代表连接状态，
                                         2代表链接锁定状态，3代表状态最大值，0xFFFFFFFF为无效值
* @param [OUT]   pbQueryUserCtrl         当前查询用户是不是控制该云台，1代表在控制，0代表不在控制
* @return 返回如下结果：
* - 成功：
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryPtzStatus
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                             szCamCode[IMOS_RES_CODE_LEN],
    OUT ULONG                           *pulStatus,
    OUT BOOL_T                          *pbQueryUserCtrl
);

/** @} */ /* end of PTZ CONTROL MANAGEMENT MODULE */

#if 0
#endif
/************************************************************************************************************
检索回放 Record Retrieval, Edited by sunyifan (06966) 13.Mar.2009 Complete
************************************************************************************************************/
/** @defgroup groupRR 检索回放
*   检索回放
*   @{
*/
/**
* 分页检索录像 \n
* @param [IN]   pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]   pstSDKRecQueryInfo      回放检索消息数据结构
* @param [IN]   pstQueryPageInfo        请求分页信息
* @param [OUT]  pstRspPageInfo          响应分页信息
* @param [OUT]  pstSDKRecordFileInfo    录像文件信息列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 查询时间跨度不能越过一天中的24小时，且在录像检索流程中时间格式为："%Y-%m-%d %H:%M:%S"格式 ，信息长度限定为24字符
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_RecordRetrieval
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  REC_QUERY_INFO_S            *pstSDKRecQueryInfo,
    IN  QUERY_PAGE_INFO_S           *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S             *pstRspPageInfo,
    OUT RECORD_FILE_INFO_S          *pstSDKRecordFileInfo
);


/**
* 获取录像文件的URL信息 \n
* @param[IN]    pstUserLogIDInfo            用户登录ID信息标识
* @param[IN]    pstSDKGetUrlInfo            获取录像文件URL的请求
* @param[OUT]   pstSDKURLInfo               URL信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_LAST_QUERY_NOT_FINISH
* - #ERR_DAO_STORE_RES_NOT_EXIST
* - #ERR_AS_STORAGE_DEV_NOT_ONLINE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_GetRecordFileURL
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    IN  GET_URL_INFO_S              *pstSDKGetUrlInfo,
    OUT URL_INFO_S                  *pstSDKURLInfo
);

/**
* 添加录像标签 \n
* @param[IN]    pstUserLogIDInfo            用户登录ID信息标识
* @param[IN]    pstSDKGetUrlInfo            添加标签消息数据结构体
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_CAM_NOT_LOCAL_DOMAIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_AddRecordTag
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  ADD_TAG_INFO_S                  *pstSDKAddTagInfo
);

/**
* 删除录像标签 \n
* @param[IN]    pstUserLogIDInfo   用户登录ID信息标识
* @param[IN]    szTagCode          标签编码
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_DAO_LABEL_NOT_EXIST
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_DelRecordTag
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szTagCode[IMOS_RES_CODE_LEN]
);

/**
* 查询录像标签 \n
* 条件为空时,查询所有标签,并默认按照"标签时间升序"排序.
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szCameraCode        摄像机编码
* @param [IN]   pstQueryCondition   通用查询条件
* @param [IN]   pstQueryPageInfo    请求分页信息
* @param [OUT]  pstRspPageInfo      响应分页信息
* @param [OUT]  pstTagList          标签列表
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1. 支持查询结果按标签时间点、标签内容进行查询与排序，对应通用查询条件中的查询项类型分别为:#LABEL_TIME、#NAME_TYPE;
* - 2. 检索标签时间点的起始/结束时间的查询项LABEL_TIME，可以查询某段时间，#QUERY_CONDITION_ITEM_S中#ulLogicFlag中填写
* -    请参照#LOGIC_FLAG_E, 如:查询起始(或结束)时间为A至B的标签，那么查询项为#LABEL_TIME, 查询项列表中第一(或二)数组元素
* -    中查询项类型为检索起始(或结束)时间，查询条件逻辑关系类型为大于等于(或小于等于)，查询内容为A(或B);
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryRecordTagList
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  CHAR                            szCameraCode[IMOS_RES_CODE_LEN],
    IN  COMMON_QUERY_CONDITION_S        *pstQueryCondition,
    IN  QUERY_PAGE_INFO_S               *pstQueryPageInfo,
    OUT RSP_PAGE_INFO_S                 *pstRspPageInfo,
    OUT TAG_QUERY_ITEM_S                *pstTagList
);

/** @} */ /* end of RECORD RETRIEVAL MANAGEMENT MODULE */

/***************************************************************************
CS业务
****************************************************************************/
/** @defgroup groupMonitor 实时监控业务
*   实时监控业务
*   @{
*/
/**
* 开始实时监控 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szCameraCode            摄像机编码
* @param [IN]   szMonitorCode           在硬解实况中为监视器编码; 在软解实况中为窗格编码
* @param [IN]   ulStreamType            流类型, 取值为#IMOS_FAVORITE_STREAM_E
* @param [IN]   ulOperateCode           操作原因码, 取值为#CS_OPERATE_CODE_E
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_SERVER_BUSY
* - #ERR_AS_MONITOR_NOT_EXIST
* - #ERR_AS_MONITOR_OFFLINE
* - #ERR_CS_MONITOR_IS_NOT_LOCAL_DOMAIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartMonitor
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szCameraCode[IMOS_RES_CODE_LEN],
    IN  CHAR                            szMonitorCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulStreamType,
    IN  ULONG                           ulOperateCode
);

/**
* 停止实时监控 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szMonitorCode           在硬解实况中为监视器编码; 在软解实况中为窗格编码
* @param [IN]   ulOperateCode           操作原因码, 取值为#CS_OPERATE_CODE_E
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
* @attention 本接口支持跨域操作
*/
IMOS_EXPORT ULONG STDCALL IMOS_StopMonitor
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szMonitorCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode
);

/// @cond
//#if defined(WIN32)
/// @endcond
/**
* 启动播放器组件。\n
* @param [IN]       pstUserLoginIDInfo  用户登录ID信息标识
* @param [IN]       ulPlayWndNum        播放窗格数量。
* @param [IN][OUT]  pstPlayWndInfo      播放窗格编码结构体指针。
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 目前该接口仅在Windows环境中有效
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartPlayer
(
    IN USER_LOGIN_ID_INFO_S     *pstUserLoginIDInfo,
    IN ULONG                    ulPlayWndNum,
    INOUT PLAY_WND_INFO_S       *pstPlayWndInfo
 );

/**
* 停止播放器组件。\n
* @param [IN]   pstUserLoginIDInfo  用户登录ID信息标识
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 目前该接口仅在Windows环境中有效
*/
IMOS_EXPORT ULONG STDCALL IMOS_StopPlayer
(
    IN USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo
 );
/// @cond
//#endif
/// @endcond

/** @} */  //实时监控结束

/** @defgroup groupVoice 语音对讲和语音广播
*   开始和停止双向语音对讲和语音广播所需要调用的所有接口
*   @{
*/
/**
* 开始双向语音对讲 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szCameraCode            摄像机编码
* @param [IN]   szXPVoiceTalkCode       双向语音对讲编码
* @param [IN]   ulOperateCode           操作原因码, 取值为#CS_OPERATE_CODE_E
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_CS_SAME_ACTIVE_VOCTALK_EXIST
* - #ERR_AS_CAMERA_OFFLINE
* - #ERR_AS_CAM_NOT_LOCAL_DOMAIN
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.szXPVoiceTalkCode暂不使用, 可以为空串, 但不能为空指针
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartVoiceTalk
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szCameraCode[IMOS_RES_CODE_LEN],
    IN  CHAR                            szXPVoiceTalkCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode
);

/**
* 停止双向语音对讲 \n
* @param [IN]   pstUserLoginIDInfo      用户登录ID信息标识
* @param [IN]   szXPVoiceTalkCode       双向语音对讲编码
* @param [IN]   ulOperateCode           操作原因码, 取值为#CS_OPERATE_CODE_E
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.szXPVoiceTalkCode暂不使用, 可以为空串, 但不能为空指针
*/
IMOS_EXPORT ULONG STDCALL IMOS_StopVoiceTalk
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN  CHAR                            szXPVoiceTalkCode[IMOS_RES_CODE_LEN],
    IN  ULONG                           ulOperateCode
);

/**
* 开始语音广播 \n
* @param [IN]       pstUserLoginIDInfo  用户登录ID信息标识
* @param [IN]       szXPVocBrdCode      语音广播编码
* @param [IN]       ulOperateCode       操作原因码, 取值为#CS_OPERATE_CODE_E
* @param [IN]       ulCameraNum         摄像机数量, 可以支持同时最多和#MAX_VOCBRD_CAM_NUM个摄像机进行语音广播，但是这些摄像机必须都属于不同的EC，且摄像机必须属于本域
* @param [IN][OUT]  pstVocBrdUnit       语音广播单元列表
* @return ULONG 返回值,有如下结果：
* - 成功:
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_CS_SAME_ACTIVE_VOCTALK_EXIST
* -      返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.szXPVocBrdCode暂不使用, 可以为空串, 但不能为空指针
* - 2.仅当在所有摄像机上开始语音广播均失败时, 该接口返回失败
*/
IMOS_EXPORT ULONG STDCALL IMOS_StartVoiceBroadcast
(
    IN      USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN      CHAR                            szXPVocBrdCode[IMOS_RES_CODE_LEN],
    IN      ULONG                           ulOperateCode,
    IN      ULONG                           ulCameraNum,
    INOUT   VOC_BRD_UNIT_S                  *pstVocBrdUnit
);

/**
* 停止语音广播 \n
* @param [IN]       pstUserLoginIDInfo  用户登录ID信息标识
* @param [IN]       szXPVocBrdCode      语音广播编码
* @param [IN]       ulOperateCode       操作原因码, 取值为#CS_OPERATE_CODE_E
* @param [IN]       ulCameraNum         摄像机数量, 最大值为#MAX_VOCBRD_CAM_NUM
* @param [IN][OUT]  pstVocBrdUnit       语音广播单元列表
* @return ULONG 返回值,有如下结果：
* - 成功:
* - #ERR_COMMON_SUCCEED
* -      返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1.语音广播单元列表作为入参时，摄像机广播状态和摄像机名称不是必须填写的，只要有摄像机编码就可以
* - 2.szXPVocBrdCode暂不使用, 可以为空串, 但不能为空指针
*/
IMOS_EXPORT ULONG STDCALL IMOS_StopVoiceBroadcast
(
    IN      USER_LOGIN_ID_INFO_S            *pstUserLoginIDInfo,
    IN      CHAR                            szXPVocBrdCode[IMOS_RES_CODE_LEN],
    IN      ULONG                           ulOperateCode,
    IN      ULONG                           ulCameraNum,
    INOUT   VOC_BRD_UNIT_S                  *pstVocBrdUnit
);


/** @} */ /* end of CS SERVICES MANAGEMENT MODULE */

#if 0
#endif

/***************************************************************************
配置XP实时监控流信息接口
****************************************************************************/
/**
* @name 配置XP实时监控流信息接口管理
* @{    配置XP实时监控流信息接口管理
*/

/**
* 配置XP实时监控流信息
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   pstXpStreamInfo     XP实时监控流信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigXpStreamInfo
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  XP_STREAM_INFO_S                *pstXpStreamInfo
);

/**
* 查询XP实时监控流信息
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [OUT]  pstXpStreamInfo     XP实时监控流信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryXpStreamInfo
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    OUT XP_STREAM_INFO_S                *pstXpStreamInfo
);

/** @} */ /* end of XP STREAM MANAGEMENT MODULE */

#if 0
#endif
/***************************************************************************
其它
****************************************************************************/
/**
* @name 其它
* @{    其它
*/

/**
* IMOS用户密码加密算法\n
* @param [IN]   pcInput     待计算数据内容
* @param [IN]   ulInlen     待计算数据长度
* @param [OUT]  szOutput    加密后的数据缓存
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_Encrypt
(
    IN const CHAR *pcInput,
    IN ULONG ulInLen,
    OUT CHAR szOutput[IMOS_PASSWD_ENCRYPT_LEN]
);

/**
* 查询设备状态 \n
* @param [IN]       pstUserLogIDInfo        用户登录ID信息标识
* @param [IN]       ulDevNum                请求查询的设备数量
* @param [IN][OUT]  pstDevStatusList        设备状态列表，入参输入设备编码，
*                                           出参返回对应的设备类型及设备状态
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_QueryDevStatus
(
    IN    USER_LOGIN_ID_INFO_S           *pstUserLogIDInfo,
    IN    ULONG                          ulDevNum,
    INOUT DEV_STATUS_INFO_S              *pstDevStatusList
);

/**
* 注册推送信息处理的回调函数。 \n
* @param [IN] pstUserLoginIDInfo    用户登录ID信息标识
* @param [IN] pfnCallBackProc       回调处理函数指针
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_RegCallBackPrcFunc
(
    IN USER_LOGIN_ID_INFO_S     *pstUserLoginIDInfo,
    IN CALL_BACK_PROC_PF        pfnCallBackProc
);


/** @} */ /* end of ADDITIONAL MODULE */

#if 0
#endif
/**************************************************************************************************************
LICENCE
***************************************************************************************************************/
/**
* @name LICENCE管理
* @{    LICENCE管理
*/
/**
* 上传license文件时，获取FTP服务器用户，密码以及文件存放路径 \n
* @param [IN]   pstUserLogIDInfo   用户登录ID信息标识
* @param [OUT]  pstFtpInfo         FTP服务信息
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_GetUploadLicenseFTPInfo
(
    IN  USER_LOGIN_ID_INFO_S        *pstUserLogIDInfo,
    OUT FTP_INFO_S                  *pstFtpInfo
);


/**
* 将上传license文件的结果，通知服务器 \n
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   bIsSuccess          上传文件的结果，BOOL_TRUE为成功, BOOL_FALSE为失败
* @param [IN]   szLicenseFileName   license文件名
* @return ULONG 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_UPLOAD_LICENSE_FILE_FAIL
* - #ERR_BP_FAIL_PARSE_LICENSE_FILE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_NotifyUpLoadLicenseResult
(
    IN  USER_LOGIN_ID_INFO_S            *pstUserLogIDInfo,
    IN  BOOL_T                          bIsSuccess,
    IN  CHAR                            szLicenseFileName[IMOS_FILE_PATH_LEN]
);

/**
* 设置选项,如设置"CC的服务器地址" \n
* @param [IN]   ulOptionName    选项名(取值为#OPTION_NAME_E)
* @param [IN]   pOption         选项值指针
* @param [IN]   ulBufferLen     选项值内存块长度
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* -     返回操作结果码：见结果码文件sdk_err.h
* @note
* - 1. 通用接口,一次调用设置一个变量
* - 2. 设置的类型和匹配的pOption见#OPTION_NAME_E;
* - 3. 输入命令行OPTION_IMOS_ROOT_PATH时，必须在SDK初始化函数之前调用该函数；
*      如果pOption为NULL，则设置为当前加载的SDK库文件所在目录。
*/
IMOS_EXPORT ULONG STDCALL IMOS_SetOption
(
     IN ULONG    ulOptionName,
     IN VOID     *pOption,
     IN ULONG    ulBufferLen
 );

/**
* 设置DC VGA输出通道模式
* @param [IN]   pstUserLogIDInfo    用户登录ID信息标识
* @param [IN]   szScrCode           监视器编码
* @param [IN]   pstOutChannelInfo   输出通道信息
* @return 返回如下结果：
* - 成功：
* - #ERR_COMMON_SUCCEED
* - 失败：
* - #ERR_AS_DEVICE_OFFLINE
* -     返回操作结果码：见结果码文件sdk_err.h
* @note 无
*/
IMOS_EXPORT ULONG STDCALL IMOS_ConfigScreenOutMode
(
    IN  USER_LOGIN_ID_INFO_S    *pstUserLogIDInfo,
    IN  CHAR                    szScrCode[IMOS_CODE_LEN],
    IN  OUT_CHANNEL_INFO_S      *pstOutChannelInfo
);

#ifdef  __cplusplus
}
#endif /* end of __cplusplus */

#endif

