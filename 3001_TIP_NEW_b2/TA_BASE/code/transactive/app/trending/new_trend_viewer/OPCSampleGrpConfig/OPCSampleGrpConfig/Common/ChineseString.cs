using System;
using System.Collections.Generic;
using System.Text;

namespace OPCSampleGrpConfig.Common
{
    /// <summary>
    /// Contains all the Display string of the application
    /// in Chinese Language.
    /// </summary>
    class ChineseString
    {
        // for OPCDataSelector.cs
        public const string OPC_DP_NAME = "OPC 数据点名称";
        public const string DESCRIPTION = "描述";
        public const string DATA_GROUP_NAME = "数据组名称";
        public const string SAVE_SUSSCCESSFUL_MSG = "保存成功!";

        public const string CAN_ADD_DATAPOINT_MSG = "The Datapoint {0} is already configured to OCC Sample Group. Do you want to override it?"; //todo
        public const string CANNOT_ADD_DATAPOINT_MSG = "The Datapoint {0} belongs to different location than that of Interval Group, hence cannot be included in this group!"; //todo



        // for OPCDataSelector.designer.cs
        public const string DP_LIST = "数据点列表";
        public const string ADD = "添加";
        public const string SAVE = "保存";
        public const string SERVER_NAME_LIST = "服务器名称表";
        public const string OPC_SERVER_NAME = "OPC 服务器名：";
        public const string DELETE = "删除";
        public const string SELECTED_DP = "已选择的数据点";
        public const string DATA_GRP_NAME = "数据组名：";
        public const string DP_NAME_SELECT = "数据点名称查询：";
        public const string SELECT_OPC_DP = "选择OPC数据点";

        // for OPCSampleGrpConfigStart.cs:
        public const string COLUMN_TIME_SPAN = "间隔长度";
        public const string COLUMN_TIME_FRAME = "间隔单位";
        public const string COLUMN_START_TIME = "开始时间";
        public const string COLUMN_DELTA_VALUE = "Delta值";
        public const string COLUMN_EDIT = "编辑";
        public const string COLUMN_DELETE = "删除";
        public const string COLUMN_CONFIG = "配置";

        public const string COLUMN_LOCATION = "配置"; //todo

        public const string SECOND = "秒";
        public const string MINITE = "分";
        public const string HOUR = "小时";
        public const string MSG_FOR_GRP_NAME = "请输入样本组名称";
        public const string MSG_FOR_INTERVAL = "间隔时间长度必须大于零";
        public const string MSG_NAME_EXIST = "样本组名称已存在!";
        public const string MSG_DELETE_CONFIRM = "确实要删除 {0} 吗?";
        //public const string MSG_DELETE_CONFIRM2 = "吗?";
        public const string MSG_DELETE_MSG = "删除操作失败。"; //todo

        

        // for OPCSampleGrpConfigStart.Designer.cs:
        public const string INTERVAL_UNIT = "间隔时间单位：";
        public const string INTERVAL_LENGTH = "间隔时间长度 ：";
        public const string DELTA_VALUE = "Delta值：";
        public const string DISABLE = "禁用";
        public const string START_TIME = "开始时间           ：";
        public const string CANCLE = "取消";
        public const string DP_GRP_DES = "数据组描述      ：";
        public const string DP_GRP_NAME = "数据组名称      ：";
        public const string TITLE = "OPC DataLogger 配置";
        public const string TOTAL_PAGE = "总页数 :    ";
        public const string MSG_SYSTEM_TITLE = "系统消息";

        public const string OPC_MSG_NODB = "数据库连接不上";

    }
}
