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
#define RTE_I2C0 1
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C3 1
#define RTE_I2C3_DMA_EN 0
#define RTE_SPI0 1
#define RTE_SPI0_DMA_EN 0
#define RTE_USART0 1
#define RTE_USART0_DMA_EN 0
#define RTE_USART1 1
#define RTE_USART1_DMA_EN 0

/* UART configuration. */
#define USART_RX_BUFFER_LEN 64
#define USART0_RX_BUFFER_ENABLE 1
#define USART1_RX_BUFFER_ENABLE 1

#define RTE_USART0_DMA_TX_CH 0
#define RTE_USART0_DMA_TX_PERI_SEL (uint8_t) kDmaRequestMux0LPUART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_TX_DMA_BASE DMA0
#define RTE_USART0_DMA_RX_CH 1
#define RTE_USART0_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMux0LPUART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_RX_DMA_BASE DMA0

#define RTE_USART1_DMA_TX_CH 0
#define RTE_USART1_DMA_TX_PERI_SEL (uint8_t) kDmaRequestMux0LPUART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_TX_DMA_BASE DMA0
#define RTE_USART1_DMA_RX_CH 1
#define RTE_USART1_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMux0LPUART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_RX_DMA_BASE DMA0

/* I2C configuration. */
#define RTE_I2C0_DMA_TX_CH 0
#define RTE_I2C0_DMA_TX_PERI_SEL (uint8_t) kDmaRequestMux0LPI2C0Tx
#define RTE_I2C0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_DMA_TX_DMA_BASE DMA0
#define RTE_I2C0_DMA_RX_CH 1
#define RTE_I2C0_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMux0LPI2C0Rx
#define RTE_I2C0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_DMA_RX_DMA_BASE DMA0

#define RTE_I2C3_DMA_TX_CH 0
#define RTE_I2C3_DMA_TX_PERI_SEL (uint8_t) kDmaRequestMux1LPI2C3Tx
#define RTE_I2C3_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_I2C3_DMA_TX_DMA_BASE DMA1
#define RTE_I2C3_DMA_RX_CH 1
#define RTE_I2C3_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMux1LPI2C3Rx
#define RTE_I2C3_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_I2C3_DMA_RX_DMA_BASE DMA1

/* SPI configuration. */
#define RTE_SPI0_PCS_TO_SCK_DELAY 1000
#define RTE_SPI0_SCK_TO_PSC_DELAY 1000
#define RTE_SPI0_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI0_MASTER_PCS_PIN_SEL (kLPSPI_MasterPcs2)
#define RTE_SPI0_SLAVE_PCS_PIN_SEL (kLPSPI_SlavePcs2)
#define RTE_SPI0_DMA_TX_CH 0
#define RTE_SPI0_DMA_TX_PERI_SEL (uint8_t) kDmaRequestMux0LPSPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_TX_DMA_BASE DMA0
#define RTE_SPI0_DMA_RX_CH 1
#define RTE_SPI0_DMA_RX_PERI_SEL (uint8_t) kDmaRequestMux0LPSPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_RX_DMA_BASE DMA0

#endif /* __RTE_DEVICE_H */
