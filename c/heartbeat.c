

/*
  This program and the accompanying materials are
  made available under the terms of the Eclipse Public License v2.0 which accompanies
  this distribution, and is available at https://www.eclipse.org/legal/epl-v20.html

  SPDX-License-Identifier: EPL-2.0

  Copyright Contributors to the Zowe Project.
*/

#ifdef METTLE
#include <metal/metal.h>
#include <metal/stddef.h>
#include <metal/stdio.h>
#include <metal/stdlib.h>
#include <metal/string.h>
#include "metalio.h"
#include "qsam.h"
#else
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#endif

#include "zowetypes.h"
#include "alloc.h"
#include "bpxnet.h"
#include "zos.h"
#include "utils.h"
#include "socketmgmt.h"

#include "httpserver.h"
#include "dataservice.h"
#include "json.h"
#include "datasetjson.h"
#include "logging.h"
#include "zssLogging.h"

#include "datasetService.h"
#include "heartbeat.h"


static int serveDatasetHeartbeat(HttpService *service, HttpResponse *response) {
  zowelog(NULL, LOG_COMP_ID_MVD_SERVER, ZOWE_LOG_INFO, "begin %s\n", __FUNCTION__);
  HttpRequest *request = response->request;
  //if (strcmp(request->method, methodGET)) {
    setResponseStatus(response, HTTP_STATUS_NO_CONTENT, "OK");
    setContentType(response, "text/plain");
    addIntHeader(response, "Content-Length", 0);
    writeHeader(response);
    finishResponse(response);
  //}
  zowelog(NULL, LOG_COMP_ID_MVD_SERVER, ZOWE_LOG_INFO, "end %s\n", __FUNCTION__);
  return 0;
}

void installDatasetHeartbeatService(HttpServer *server) {
  zowelog(NULL, LOG_COMP_ID_MVD_SERVER, ZOWE_LOG_INFO, ZSS_LOG_INSTALL_MSG, "dataset heartbeat");
  zowelog(NULL, LOG_COMP_ID_MVD_SERVER, ZOWE_LOG_DEBUG2, "begin %s\n", __FUNCTION__);

  HttpService *httpService = makeGeneratedService("datasetHeartbeat", "/datasetHeartbeat");
  httpService->authType =  SERVICE_AUTH_NATIVE_WITH_SESSION_TOKEN;
  httpService->runInSubtask = TRUE;
  httpService->doImpersonation = TRUE;
  httpService->serviceFunction = serveDatasetHeartbeat;
  registerHttpService(server, httpService);
}

/*
  This program and the accompanying materials are
  made available under the terms of the Eclipse Public License v2.0 which accompanies
  this distribution, and is available at https://www.eclipse.org/legal/epl-v20.html

  SPDX-License-Identifier: EPL-2.0

  Copyright Contributors to the Zowe Project.
*/

