/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

/*Driver name mapping*/
#define RTE_SPI0 0
#define RTE_SPI0_DMA_EN 0
#define RTE_SPI1 0
#define RTE_SPI1_DMA_EN 0
#define RTE_SPI2 0
#define RTE_SPI2_DMA_EN 0
#define RTE_SPI3 1
#define RTE_SPI3_DMA_EN 1
#define RTE_SPI4 0
#define RTE_SPI4_DMA_EN 0
#define RTE_SPI5 0
#define RTE_SPI5_DMA_EN 0
#define RTE_SPI6 0
#define RTE_SPI6_DMA_EN 0
#define RTE_SPI7 0
#define RTE_SPI7_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_SSEL_NUM kSPI_Ssel0
#define RTE_SPI0_DMA_TX_CH 1
#define RTE_SPI0_DMA_TX_DMA_BASE DMA0
#define RTE_SPI0_DMA_RX_CH 0
#define RTE_SPI0_DMA_RX_DMA_BASE DMA0

#define RTE_SPI1_SSEL_NUM kSPI_Ssel0
#define RTE_SPI1_DMA_TX_CH 3
#define RTE_SPI1_DMA_TX_DMA_BASE DMA0
#define RTE_SPI1_DMA_RX_CH 2
#define RTE_SPI1_DMA_RX_DMA_BASE DMA0

#define RTE_SPI2_SSEL_NUM kSPI_Ssel0
#define RTE_SPI2_DMA_TX_CH 5
#define RTE_SPI2_DMA_TX_DMA_BASE DMA0
#define RTE_SPI2_DMA_RX_CH 4
#define RTE_SPI2_DMA_RX_DMA_BASE DMA0

#define RTE_SPI3_SSEL_NUM kSPI_Ssel2
#define RTE_SPI3_DMA_TX_CH 7
#define RTE_SPI3_DMA_TX_DMA_BASE DMA0
#define RTE_SPI3_DMA_RX_CH 6
#define RTE_SPI3_DMA_RX_DMA_BASE DMA0

#define RTE_SPI4_SSEL_NUM kSPI_Ssel0
#define RTE_SPI4_DMA_TX_CH 9
#define RTE_SPI4_DMA_TX_DMA_BASE DMA0
#define RTE_SPI4_DMA_RX_CH 8
#define RTE_SPI4_DMA_RX_DMA_BASE DMA0

#define RTE_SPI5_SSEL_NUM kSPI_Ssel0
#define RTE_SPI5_DMA_TX_CH 11
#define RTE_SPI5_DMA_TX_DMA_BASE DMA0
#define RTE_SPI5_DMA_RX_CH 10
#define RTE_SPI5_DMA_RX_DMA_BASE DMA0

#define RTE_SPI6_SSEL_NUM kSPI_Ssel0
#define RTE_SPI6_DMA_TX_CH 13
#define RTE_SPI6_DMA_TX_DMA_BASE DMA0
#define RTE_SPI6_DMA_RX_CH 12
#define RTE_SPI6_DMA_RX_DMA_BASE DMA0

#define RTE_SPI7_SSEL_NUM kSPI_Ssel0
#define RTE_SPI7_DMA_TX_CH 15
#define RTE_SPI7_DMA_TX_DMA_BASE DMA0
#define RTE_SPI7_DMA_RX_CH 14
#define RTE_SPI7_DMA_RX_DMA_BASE DMA0
#endif /* __RTE_DEVICE_H */
