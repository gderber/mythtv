#ifndef DAAPSERVER_H_
#define DAAPSERVER_H_
/*
	daapserver.h

	(c) 2003 Thor Sigvaldason and Isaac Richards
	Part of the mythTV project
	
	Headers for the daap server
*/

#include <iostream>
using namespace std; 

#include <qvaluelist.h>

#include "mfd_plugin.h"
#include "../../mdserver.h"

struct httpd;

#include "daaplib/basic.h"
#include "daaplib/tagoutput.h"

#include "request.h"
#include "session.h"

class DaapServer: public MFDHttpPlugin
{

  public:

    DaapServer(MFD *owner, int identity);
    ~DaapServer();

    void    handleIncoming(HttpRequest *request, int client_id);
    void    parsePath(HttpRequest *http_request, DaapRequest *daap_request);
    void    sendServerInfo(HttpRequest *http_request);
    void    sendTag(HttpRequest *http_request, const Chunk& c);
    void    sendLogin(HttpRequest *http_request, u32 session_id);
    void    parseVariables(HttpRequest *http_request, DaapRequest *daap_request);
    void    sendUpdate(HttpRequest *http_request, u32 database_version);
    void    sendMetadata(HttpRequest *http_request, QString request_path, DaapRequest *daap_request);
    void    sendDatabaseList(HttpRequest *http_request);
    void    addItemToResponse(TagOutput &response, AudioMetadata *which_item, u64 meta_codes);
    void    sendDatabase(HttpRequest *http_request, DaapRequest *daap_request, int which_database);
    void    sendDatabaseItem(HttpRequest *http_request, u32 song_id, DaapRequest *daap_request);
    void    sendContainers(HttpRequest *http_request, DaapRequest *daap_request, int which_database);
    void    sendContainer(HttpRequest *http_request, u32 container_id, int which_database);
    void    handleMetadataChange(int which_collection);

    DaapSessions daap_sessions;

  private:
  
    MetadataServer              *metadata_server;
    QPtrList<MetadataContainer> *metadata_containers;
    QString                     service_name;
    QValueList<int>             hanging_updates;
    QMutex                      hanging_updates_mutex;
    bool                        first_update;
    QMutex                      first_update_mutex;
};

#endif  // daapserver_h_
