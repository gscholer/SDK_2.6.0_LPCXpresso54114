/*
 * Copyright (c) 2014-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_manually_constructed.h"
#include "erpc_rpmsg_lite_transport.h"
#include "erpc_transport_setup.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static ManuallyConstructed<RPMsgTransport> s_transport;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

erpc_transport_t erpc_transport_rpmsg_lite_remote_init(unsigned long src_addr, unsigned long dst_addr,
                                                       void *start_address, int rpmsg_link_id, rpmsg_ready_cb ready,
                                                       char *nameservice_name)
{
    s_transport.construct();
    if (s_transport->init(src_addr, dst_addr, start_address, rpmsg_link_id, ready, nameservice_name) ==
        kErpcStatus_Success)
    {
        return reinterpret_cast<erpc_transport_t>(s_transport.get());
    }
    return NULL;
}
