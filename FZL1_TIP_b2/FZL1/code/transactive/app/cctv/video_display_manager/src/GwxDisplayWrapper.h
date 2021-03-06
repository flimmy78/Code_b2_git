#ifndef _GWX_DISPLAY_WRAPPER_H_FILE_
#define _GWX_DISPLAY_WRAPPER_H_FILE_
#pragma once


#import "app/cctv/video_display_manager/src/Gwx32.tlb" no_namespace
#include <string>
#include "app/cctv/video_display_manager/src/ILoadStationDiagramService.h"



namespace TA_IRS_App 
{
class GwxDisplayWrapper: public ILoadStationDiagramService 
{

public:

    virtual ~GwxDisplayWrapper();

    static bool createInstance();

    static void destroyInstance();

    // Static function for public invoke
    static GwxDisplayWrapper& getInstance();
    int loadStationDiagram( const std::string& strFileFullName,const CRect& rtPosition, HWND hParent );
	void stopSchematic();
    void closeSchematic();

    void refreshSchematic();

public:
    GwxDisplayWrapper();

private:
    // Disable operator = and copy constructor
    const GwxDisplayWrapper& operator=( GwxDisplayWrapper& );
    GwxDisplayWrapper( const GwxDisplayWrapper& );
enum GWX_MESSAGE_ID
{
    ERROR_NOT_DEFINE = -1,
    SUCCESS_NO_ERROR = 0,

    // Internal error message for log
    ERROR_INVALID_INPUT_PARAMETER,
    ERROR_DVA_MSG_NOT_EXIST,
    ERROR_CURRENT_EDIT_SCHEDULE_NOT_EXIST,
    ERROR_MAIN_WND_FOR_MSG_BOX_NOT_EXIST,
    ERROR_FAILED_TO_CREATE_INSTANCE,
    ERROR_COULD_NOT_FIND_EXPECTED_DATA,
    ERROR_UNEXPECTED_NULL_POINTER,
    ERROR_CATCHED_UNKNOWN_EXCEPTION,
    ERROR_UNAUTHORIZED_OPERATION,
    ERROR_UNEXPECTED_LOGIC,
    ERROR_NO_EXTERNAL_PA_INTERACTION_ALLOWED,
    ERROR_STATION_CANNOT_RUN_FOR_OVERALL,
    ERROR_FAILED_TO_INIT_COM,
    ERROR_NO_SCHEMATIC_FILE_NAME_IN_DATABASE,
    ERROR_INVALID_STRING,
    ERROR_RECEIVE_UNKNOWN_MESSAGE,

    // Error message show to operator
    ERROR_FAILED_TO_SAVE_NEW_SCHEDULE,
    ERROR_FAILED_TO_SAVE_DVA_MSG_DESCRIPTION,
    ERROR_FAILED_TO_SAVE_ZONG_GROUP,
    ERROR_FAILED_TO_DELETE_ZONG_GROUP,
    ERROR_FAILED_TO_START_DVA_BROADCAST,
    ERROR_FAILED_TO_STOP_DVA_BROADCAST,
    ERROR_FAILED_TO_START_LIVE_BROADCAST,
    ERROR_FAILED_TO_STOP_LIVE_BROADCAST,
    ERROR_FAILED_TO_START_DVA_MSG_PLAYBACK,
    ERROR_FAILED_TO_STOP_DVA_MSG_PLAYBACK,
    ERROR_FAILED_TO_SET_SIG_BROADCAST_DELAY,
    ERROR_FAILED_TO_GET_SIG_BROADCAST_DELAY,
    ERROR_FAILED_TO_ENABLE_SIG_BROADCAST,
    ERROR_FAILED_TO_GET_ENABLE_SIG_BROADCAST,
    ERROR_FAILED_TO_LOCATE_SCHEMATIC_FILE,
    ERROR_FAILED_TO_INVOKE_GWX_INTERFACE,
    ERROR_GWX_FAILED_TO_OPEN_SCHEMATIC_FILE,
    ERROR_FAILED_TO_SOLVE_AGENT_OBJECT,
    ERROR_FAILED_TO_CONNECT_TO_HARDWARE,
    ERROR_PA_FEP_CONFIG_NOT_FOUND,
    ERROR_ZONE_GROUP_DELETED_ALREADY,
    ERROR_FAILED_TO_READ_DATABASE,
    ERROR_FAILED_TO_WRITE_DATABASE,
    ERROR_NO_RIGHTS_TO_BROADCAST_DVA_PLAYBACK,
    ERROR_NO_RIGHTS_TO_BROADCAST_OCC_DVA_MSG,
    ERROR_NO_RIGHTS_TO_BROADCAST_STATION_DVA_MSG,
    ERROR_NO_RIGHTS_TO_STOP_STATION_DVA_MSG,
    ERROR_NO_RIGHTS_TO_BROADCAST_STATION_LIVE,
    ERROR_NO_RIGHTS_TO_MODIFY_ZONE_GROUP,
    ERROR_NO_RIGHTS_TO_MODIFY_DVA_MSG_DESCRIPTION,
    ERROR_AGENT_DATA_INVALID,
    ERROR_FAILED_TO_INIT_GWX_COM,
    ERROR_BACKUP_KEY_NOT_CONFIG,
    ERROR_FAILED_TO_RUN_SCHEDULE_MANAGER,

    // Warning message show to operator
    WARNING_SCHEDULE_NAME_NOT_SET,
    WARNING_FREQUENCY_NOT_SEL,
    WARNING_FREQUENCY_DETAIL_NOT_SEL,
    WARNING_GROUP_NAME_EMPTY,
    WARNING_GROUP_NAME_MAX_CHARS,
    WARNING_GROUP_NAME_SAME_AS_CUR_SEL,
    WARNING_ZONE_NOT_SELECTED,
    WARNING_ZONE_SELECTING_IN_LIVE_BROADCAST_MODE,
    WARNING_DELAY_TIME_OUT_OF_RANGE,
    WARNING_CYCLIC_TIMES_OUT_OF_RANGE,
    WARNING_CYCLIC_TIMES_IS_NOT_SET,
    WARNING_DVA_MSG_DESC_MAX_CHARS,
    WARNING_ZONE_GROUP_COUNT_MAX,

    // Confirm message show to operator
    CONFIRM_DELETE_ZONE_GROUP,
    CONFIRM_SWITCH_TO_DVA_BROADCAST_MODE,
    CONFIRM_SWITCH_TO_LIVE_BROADCAST_MODE,
    CONFIRM_START_DVA_BROADCAST,
    CONFIRM_STOP_DVA_BROADCAST,
    CONFIRM_START_DVA_MSG_PLAYBACK,
    CONFIRM_SET_SIG_BROADCAST_DELAY_TIME,
    CONFIRM_SET_SIG_BROADCAST_ENABLE,

    // The count must be the last one
    ERROR_MSG_COUNT
};
private:
    static GwxDisplayWrapper* s_pInstance;
    IGwx32Ptr m_pGwxDisplay;
    bool m_bSchematicOpen;
    HWND m_hPrevParent;
};
}
#endif
