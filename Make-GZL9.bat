@ECHO OFF
SET GZL9=C:\C0de\GZL9_TIP_b2\TA_BASE\code
SET COMM=C:\C0de\TA_Common_V1_TIP_b2\code
junction %GZL9%\cots														C:\COTS
junction %GZL9%\tools														%COMM%\tools
junction %GZL9%\transactive\bus												%COMM%\transactive\bus
junction %GZL9%\transactive\core											%COMM%\transactive\core
junction %GZL9%\transactive\app\alarm\alarm_agent							%COMM%\transactive\app\alarm\alarm_agent
junction %GZL9%\transactive\app\alarm\alarm_raiser							%COMM%\transactive\app\alarm\alarm_raiser
junction %GZL9%\transactive\app\alarm\alarm_store_service					%COMM%\transactive\app\alarm\alarm_store_service
junction %GZL9%\transactive\app\alarm\AlarmSharedMapReader					%COMM%\transactive\app\alarm\AlarmSharedMapReader
junction %GZL9%\transactive\app\alarm\AlarmStoreHarness						%COMM%\transactive\app\alarm\AlarmStoreHarness
junction %GZL9%\transactive\app\alarm\ATSInterface							%COMM%\transactive\app\alarm\ATSInterface
junction %GZL9%\transactive\app\checker										%COMM%\transactive\app\checker
junction %GZL9%\transactive\app\datalog										%COMM%\transactive\app\datalog
junction %GZL9%\transactive\app\dbsynch										%COMM%\transactive\app\dbsynch
junction %GZL9%\transactive\app\event\ATSBridgeUtil							%COMM%\transactive\app\event\ATSBridgeUtil
junction %GZL9%\transactive\app\event\event_agent							%COMM%\transactive\app\event\event_agent
junction %GZL9%\transactive\app\event\event_extractor						%COMM%\transactive\app\event\event_extractor
junction %GZL9%\transactive\app\event\EventGenerator						%COMM%\transactive\app\event\EventGenerator
junction %GZL9%\transactive\app\event\EventViewerSimulator					%COMM%\transactive\app\event\EventViewerSimulator
junction %GZL9%\transactive\app\event\online_printing_agent					%COMM%\transactive\app\event\online_printing_agent
junction %GZL9%\transactive\app\notification_service						%COMM%\transactive\app\notification_service
junction %GZL9%\transactive\app\response_plans\plan_agent					%COMM%\transactive\app\response_plans\plan_agent
junction %GZL9%\transactive\app\response_plans\plan_agent_test				%COMM%\transactive\app\response_plans\plan_agent_test
junction %GZL9%\transactive\app\response_plans\plan_mft_processor			%COMM%\transactive\app\response_plans\plan_mft_processor
junction %GZL9%\transactive\app\response_plans\plan_step_plugin				%COMM%\transactive\app\response_plans\plan_step_plugin
junction %GZL9%\transactive\app\scada\DataNodeAgent							%COMM%\transactive\app\scada\DataNodeAgent
junction %GZL9%\transactive\app\scada\DataNodeController					%COMM%\transactive\app\scada\DataNodeController
junction %GZL9%\transactive\app\scada\ModbusAgent							%COMM%\transactive\app\scada\ModbusAgent
junction %GZL9%\transactive\app\scada\ModbusServerAgent						%COMM%\transactive\app\scada\ModbusServerAgent
junction %GZL9%\transactive\app\scada\OpcBridgeLib							%COMM%\transactive\app\scada\OpcBridgeLib
junction %GZL9%\transactive\app\scada\OpcBridgeService						%COMM%\transactive\app\scada\OpcBridgeService
junction %GZL9%\transactive\app\scada\PMSAgent								%COMM%\transactive\app\scada\PMSAgent
junction %GZL9%\transactive\app\scada\PowerDemandEditor						%COMM%\transactive\app\scada\PowerDemandEditor
junction %GZL9%\transactive\app\scada\PScadaAgent							%COMM%\transactive\app\scada\PScadaAgent
junction %GZL9%\transactive\app\scada\SNMPStatusAgent						%COMM%\transactive\app\scada\SNMPStatusAgent
junction %GZL9%\transactive\app\scada\VirtualDataPointAgent					%COMM%\transactive\app\scada\VirtualDataPointAgent
junction %GZL9%\transactive\app\scheduling\scheduling_agent					%COMM%\transactive\app\scheduling\scheduling_agent
junction %GZL9%\transactive\app\security\authentication_agent				%COMM%\transactive\app\security\authentication_agent
junction %GZL9%\transactive\app\security\duty_agent							%COMM%\transactive\app\security\duty_agent
junction %GZL9%\transactive\app\security\rights_agent						%COMM%\transactive\app\security\rights_agent
junction %GZL9%\transactive\app\security\rights_service						%COMM%\transactive\app\security\rights_service
junction %GZL9%\transactive\app\simulator									%COMM%\transactive\app\simulator
junction %GZL9%\transactive\app\sound										%COMM%\transactive\app\sound
junction %GZL9%\transactive\app\system_control\dll_host						%COMM%\transactive\app\system_control\dll_host
junction %GZL9%\transactive\app\system_control\dummy_agent					%COMM%\transactive\app\system_control\dummy_agent
junction %GZL9%\transactive\app\system_control\system_controller			%COMM%\transactive\app\system_control\system_controller
junction %GZL9%\transactive\app\system_control\system_status_agent			%COMM%\transactive\app\system_control\system_status_agent
junction %GZL9%\transactive\app\system_control\transact_screensaver			%COMM%\transactive\app\system_control\transact_screensaver
junction %GZL9%\transactive\app\train_timetable								%COMM%\transactive\app\train_timetable
junction %GZL9%\transactive\app\trending									%COMM%\transactive\app\trending
junction %GZL9%\transactive\app\WebPortal									%COMM%\transactive\app\WebPortal
