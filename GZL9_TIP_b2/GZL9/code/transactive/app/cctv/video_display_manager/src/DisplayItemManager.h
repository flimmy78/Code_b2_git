/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/cctv/video_display_manager/src/DisplayItemManager.h $
  * @author:  Adam Radics
  * @version: $Revision: #6 $
  *
  * Last modification: $DateTime: 2013/11/18 19:40:33 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * This singleton is required to keep a reference to all display
  * items. It maps each type of display item by name and provides access to
  * the items that are shared throughout the GUI - their state is updated
  * via comms messages and the display refreshed to reflect this.
  */


#if !defined(DisplayItemManager_H)
#define DisplayItemManager_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// warnings for name truncated to 255 characters
#pragma warning ( disable : 4503 )

#include "app/cctv/video_display_manager/src/SwitchAgentCommunicator.h"
#include "app/cctv/video_display_manager/src/IDisplayItemLoader.h"
#include "app/cctv/video_display_manager/src/IVideoDisplayManagerDAI.h"
#include "app/cctv/video_display_manager/src/CCTVCommon.h"
#include "core/synchronisation/src/ReEntrantThreadLockable.h"
#include "core/configuration_updates/src/IOnlineUpdatable.h"
#include "core/message/src/SpecialisedMessageSubscriber.h"
#include "core/message/IDL/src/CommsMessageCorbaDef.h"
#include "core/message/types/VisualComms_MessageTypes.h"
#include "core/message/IDL/src/ConfigUpdateMessageCorbaDef.h"
#include "core/data_access_interface/src/ILocation.h"
#include "core/threads/src/IThreadPoolWorkerCallback.h"
#include "core/threads/src/Thread.h"

#include <string>
#include <map>
#include <vector>

const static int RL_MONITOR_SEQUENCE_NORMAL    = 12;
const static int RL_MONITOR_CAMERA_NORMAL      = 13;
const static int RL_MONITOR_SEQUENCE_HIGHLIGHT = 120;
const static int RL_MONITOR_CAMERA_HIGHLIGHT   = 130;

class CWnd;

namespace TA_IRS_App
{
    //    class BvsStage;

    class Camera;
    class Quad;
    class Sequence;
    class Monitor;
    class DisplayItem;
    class VideoInput;
    class VideoOutput;

    class DisplayItemManager  : public TA_Base_Core::SpecialisedMessageSubscriber< TA_Base_Core::CommsMessageCorbaDef >,
        public TA_Base_Core::Thread,
        public TA_Base_Core::IOnlineUpdatable,
        public TA_Base_Core::IThreadPoolWorkerCallback,
        public IDisplayItemLoader
    {

        public:

            ~DisplayItemManager();

            static DisplayItemManager& getInstance();

            static void removeInstance();

            // These return pointers to the display items
            // they are mapped on entity name and the pointers are owned
            // by this class - they can not be deleted.
            // if something is not found - you'll get NULL.
            // there is also the option to retrieve by pkey

            Camera* getCamera(std::string name);
            Camera* getCamera(unsigned long pkey);
            Camera* getCameraByAddress(const std::string& address);  // and also by Address, eg "1:26" (TD 13455)

            Quad* getQuad(std::string name);
            Quad* getQuad(unsigned long pkey);

            Sequence* getSequence(std::string name);
            Sequence* getSequence(unsigned long pkey);

            void updateSequence(Sequence * sequence);

            void updateSequenceDesc(Sequence * sequence, std::string description);

            //     BvsStage* getBvsStage(std::string name);
            //     BvsStage* getBvsStage(unsigned long pkey);
            //     BvsStage* getBvsStageForLocation(unsigned long locationKey);
            //     BvsStage* getBvsStageById( unsigned long stageId );

            Monitor* getMonitor(std::string name);
            Monitor* getMonitor(unsigned long pkey);
            //TD19471  lichao++
            std::vector<std::string> getConsoleMonitors();

            // get any matching input type
            VideoInput* getInput(std::string name);
            VideoInput* getInput(unsigned long pkey);

            // get any matching output type
            VideoOutput* getOutput(std::string name);
            VideoOutput* getOutput(unsigned long pkey);


            // used to retrieve all items - so that property pages can populate lists
            // items are mapped on name
            std::map<std::string, Camera*>      getAllCameras();
            std::map<std::string, Quad*>        getAllQuads();
            std::map<std::string, Sequence*>    getAllSequences();
            //     std::map<std::string, BvsStage*>    getAllStages();
            std::map<std::string, Monitor*>     getAllMonitors();
			

            //bihui
            /*
            retreive the sequences based on the location id
            */
            void getSequenceByLocation(unsigned long locationId , std::vector< VideoInput*>& sequences);


            /* These are used to register and deregister interest in certain
              types of display devices.
              when a device changes the the appropriate windows message will be sent to
              the window. If a device referenced by a device changes - windows listening
              for the parent device will also be notified.
              eg if a window is listening for monitor updates, and a camera is modified
              then the window will receive monitor updates for monitors displaying the camera
              and for monitors displaying quads or sequences that contain the camera.
              A pointer to the modified device will be sent as the lParam.
              */
            void registerForMonitorChanges(CWnd* window);
            void registerForSequenceChanges(CWnd* window);
            void registerForQuadChanges(CWnd* window);
            void registerForCameraChanges(CWnd* window);
            void registerForStageChanges(CWnd* window);

            void deregisterForMonitorChanges(CWnd* window);
            void deregisterForSequenceChanges(CWnd* window);
            void deregisterForQuadChanges(CWnd* window);
            void deregisterForCameraChanges(CWnd* window);
            void deregisterForStageChanges(CWnd* window);

            /**
              * notifyGUIofDisplayItemUpdate
              *
              * *ANY* time one of the DisplayItems are updated, then this
              * must be called. This will determine what has changed annd force the GUI
              * to update accordingly.
              *
              * @param itemThatChanged  A pointer to the item that changed
              */
            void notifyGUIofDisplayItemUpdate(DisplayItem* itemThatChanged);


            /**
              * isCurrentlyActiveTrain
              *
              * This checks each stage and returns if this train is active in any of them
              *
              * @param trainId  The train to check
              *
              * @return true if the train is active
              */
            //  bool isCurrentlyActiveTrain(unsigned char trainId);


            /* These are handlers for comms messages and online updates */

            /**
             * processUpdate
             *
             * When there is a configuration update of the type and key matching
             * one registered by this class, this method will be invoked
             * to process the update accordingly.
             */
            virtual void processUpdate(const TA_Base_Core::ConfigUpdateDetails& updateEvent);


            /**
              * receiveSpecialisedMessage
              *
              * Handle comms messages to update the state of objects.
              */
            virtual void receiveSpecialisedMessage(const TA_Base_Core::CommsMessageCorbaDef& message);

            /**
             * Starts the initialisation thread
             * As items are loaded, these messages will be sent to the window in order:
             * TA_INIT_CAMERAS
             * TA_INIT_QUADS
             * TA_INIT_SEQUENCES
             * TA_INIT_STAGES
             * TA_INIT_MONITORS
             * TA_INIT_CCTV
             */
            void initialiseDisplayItems(CWnd* callbackWindow);


            /**
             * Call back for threaded workers
             */
            virtual void workerFree();


            virtual void saveSequencesRelationship(unsigned long parentKey);
            /**
             * Loading methods to load display items in parallel
             */
            virtual void loadCamerasFromDatabase();
            virtual void loadQuadsFromDatabase();
            virtual void loadSequencesFromDatabase();
            virtual void loadMonitorsFromDatabase();
            virtual void loadStationsFromDatabase();
            virtual void loadStagesFromDatabase();

            virtual void loadCamerasFromAgent();
            virtual void loadQuadsFromAgent();
            virtual void loadSequencesFromAgent();
            virtual void loadStagesFromAgent();
            virtual void loadMonitorsFromAgent();
            virtual void loadStationsFromAgent();
            /**
             * Methods to load items from the agent
             */
            virtual void loadEntityRelationship(unsigned long parentKey, unsigned long& pkey, int* ptype = NULL);
            virtual void saveEntityRelationship(unsigned long parentkey, unsigned long pkey, int type = RL_MONITOR_CAMERA_NORMAL);
            virtual void delEntityRelationship(unsigned long parentKey);
            /**
             * Called by the start method.
             */
            virtual void run();


            /**
             * Terminates the thread
             */
            virtual void terminate();

            //bihui
            void setVideoDisplayManagerDAI(IVideoDisplayManagerDAI* videoDisplayManagerDAI)
            {
                m_videoDisplayManagerDAI = videoDisplayManagerDAI;
            }

            /*
              get the stations from the locations
              checking the locationType
            */
            std::vector<TA_Base_Core::ILocation*>&  getStations();

			// level: 0->over view, 1->station office, 2->up plt, 3->down plt, 4->b1, 5->b2
			void getGraphicfullPath(unsigned long stationId , std::string& fullpath, unsigned long level=0);

            void setVideoWallMonitorKeys(std::vector<unsigned long> keys);

            void loadStations();

            void LoadSequenceRelationFromDatabase();
			Monitor* getIMOSSingleMonitor();

			const VirtualQuadArray& getIMOSQuadMonitors();
			const AllMonitorsArray& getAllMonitorsArray();

        private:

            // These arent needed

            DisplayItemManager();
            DisplayItemManager(const DisplayItemManager&);
            DisplayItemManager& operator=(const DisplayItemManager&);

            static DisplayItemManager* m_theInstance; // pointer to the single instance of this class.
            static TA_Base_Core::ReEntrantThreadLockable m_singletonLock; // Semaphore to thread guard this singleton.


            /**
             * In case the agent is down this allows to load all items from the database
             */
            void loadItemsFromDatabase();



            /**
             * Methods to create display items whether loaded from agent or database
             */
            Camera* createCamera(unsigned long key,
                                 const std::string& name,
                                 const std::string& description,
                                 const std::string& group,
                                 const std::string& address ,
                                 unsigned long locationId,
                                 bool isMovementSupported);

            Quad* createQuad(unsigned long key,
                             const std::string& name,
                             const std::string& description,
                             const std::string& group ,
                             unsigned long locationId);

            Sequence* createSequence(unsigned long key,
                                     const std::string& name,
                                     const std::string& addr,
                                     const std::string& description,
                                     const std::string& group,
                                     bool readOnly,
                                     const std::string& sequenceDescription , unsigned long locationId);


            /*
                  BvsStage* createStage( unsigned long key,
                                         const std::string& name,
                                         const std::string& description,
                                         const std::string& group,
                                         const std::string& address,
                                         const TA_IRS_Bus::AtsZoneUtils::CctvZoneToLocationMap& cctvZoneToLocationMap );*/

            Monitor* createMonitor(unsigned long key,
                                   const std::string& name,
                                   const std::string& description,
                                   bool isConsoleMonitor,
                                   unsigned long consoleKey,
                                   int order,
								   const std::string& address);

            /**
              * deleteAllItems
              *
              * cleans up all objects
              */
            void deleteAllItems();

            /**
              * subscribeToMessages
              *
              * subscribes for comms messages and online updates
              * must be called after local objects are created
              */
            void subscribeToMessages();
            //bool CompareEntity(const EntityDataPtr& entity1,const EntityDataPtr& entity2);

            // Comms message handlers
            void processVideoOutputStateMessage(unsigned long outputKey, const TA_Base_Bus_GZL9::VideoOutputCorbaDef::VideoOutputState& videoOutputState);
            void processQuadStateMessage(unsigned long quadKey, const TA_Base_Bus_GZL9::QuadCorbaDef::QuadState& quadState);
            void processSequenceConfigMessage(unsigned long sequenceKey, const TA_Base_Bus_GZL9::SequenceCorbaDef::SequenceConfig& sequenceConfig);
            //  void processStageStateMessage( unsigned long stageKey, const TA_Base_Bus_GZL9::BVSStageCorbaDef::BVSStageState& stageConfig );


            // GUI update handlers
            void registerWindow(std::list<CWnd*>& list, CWnd* window);
            void deregisterWindow(std::list<CWnd*>& list, CWnd* window);
            void notifyMonitorListeners(Monitor* modifiedItem);
            void notifySequenceListeners(Sequence* modifiedItem);
            void notifyQuadListeners(Quad* modifiedItem);
            void notifyCameraListeners(Camera* modifiedItem);
            //     void notifyStageListeners(BvsStage* modifiedItem);
            void postMessageToWindows(const std::list<CWnd*>& windows, int message, DisplayItem* itemPtr);


			// local Monitor
			Monitor* m_imosSingleMonitor;
			// 4 virtual quad monitor
			/*
			-----------
			|  1 |  2 |
			-----------
			|  3 |  4 |
			-----------
			*/
            // inputs - mapped on name
            std::map<std::string, Camera*> m_cameras;
            std::map<unsigned long, Camera*> m_camerasByPkey;
            std::map<std::string, Camera*> m_camerasByAddress;
            std::map<std::string, Quad*> m_quads;
            std::map<unsigned long, Quad*> m_quadsByPkey;
            std::map<std::string, Sequence*> m_sequences;
            std::map<unsigned long, Sequence*> m_sequencesByPkey;
            //      std::map<std::string, BvsStage*> m_bvsStages;
            //      std::map<unsigned long, BvsStage*> m_bvsStagesByPkey;
            //      std::map<unsigned long, BvsStage*> m_bvsStagesByLocation;
            //      std::map<unsigned long, BvsStage*> m_bvsStagesByStageId;

            std::vector <Sequence *> m_seqVec;

            // outputs - mapped on name
            std::map<std::string, Monitor*> m_monitors;
            std::map<unsigned long, Monitor*> m_monitorsByPkey;

            std::map<unsigned long, std::string > m_GraphicByStation;
            std::vector<std::string> m_consoleMonitors;

            // windows to post changes to
            TA_Base_Core::ReEntrantThreadLockable m_windowListLock;
            std::list<CWnd*> monitorListeners;
            std::list<CWnd*> sequenceListeners;
            std::list<CWnd*> quadListeners;
            std::list<CWnd*> cameraListeners;
            std::list<CWnd*> stageListeners;

            std::vector<unsigned long> m_videoWallMonitorKeys;

            bool m_isConfigItems;

            CWnd* m_callbackWindow;

            std::vector<TA_Base_Core::ILocation*> m_stations;



            IVideoDisplayManagerDAI* m_videoDisplayManagerDAI;

            /*
             init the fullpath of graphic
            */
            void initGraphicFullPath();

			VirtualQuadArray m_imosQuadMonitors;
			AllMonitorsArray m_allMonitorsArray;
    };
}

#endif // !defined(DisplayItemManager_H)

