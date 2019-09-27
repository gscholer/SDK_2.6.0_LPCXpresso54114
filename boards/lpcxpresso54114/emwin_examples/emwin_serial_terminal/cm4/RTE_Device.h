/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/* Driver name mapping. */
#define RTE_SPI5 1
#define RTE_SPI5_DMA_EN 0

#define RTE_I2C4 1
#define RTE_I2C4_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI5_SSEL_NUM kSPI_Ssel2
#define RTE_SPI5_DMA_TX_CH 11
#define RTE_SPI5_DMA_TX_DMA_BASE DMA0
#define RTE_SPI5_DMA_RX_CH 10
#define RTE_SPI5_DMA_RX_DMA_BASE DMA0

#endif /* __RTE_DEVICE_H */
