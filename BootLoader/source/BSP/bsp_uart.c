/**
  ****************************************************************************************
  * @file    bsp_uart.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-25
  * @brief   bsp uart
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_uart.h"
#include "nrf_gpio.h"


/* private function declares -------------------------------------------------*/
static void simple_uart_put(uint8_t cr);


static void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}


/**
  * @brief  uart_init 
  * @note   This function is called  automatically at the beginning of program 
  * @param  None
  * @retval None
  */
void uart_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    const app_uart_comm_params_t comm_params =  
    {
        UART_PIN_DISCONNECTED, 
        TX_PIN_NUMBER, 
        RTS_PIN_NUMBER, 
        CTS_PIN_NUMBER, 
        APP_UART_FLOW_CONTROL_DISABLED, 
        false, 
        UART_BAUDRATE_BAUDRATE_Baud115200
    }; 
        
    APP_UART_FIFO_INIT(&comm_params, 
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE, 
                       uart_error_handle, 
                       APP_IRQ_PRIORITY_LOWEST,
                       err_code);
    UNUSED_VARIABLE(err_code);
}

/**
  * @brief  simple_uart_config
  * @note   This function is implement the simple uart
  * @param  None
  * @retval None
  */
void simple_uart_config(void)
{
/** @snippet [Configure UART RX and TX pin] */
    nrf_gpio_cfg_output(TX_PIN_NUMBER);

    NRF_UART0->PSELTXD = TX_PIN_NUMBER;

    NRF_UART0->BAUDRATE      = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);
    NRF_UART0->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;
    NRF_UART0->EVENTS_RXDRDY = 0;
}

/**
  * @brief  simple_uart_put
  * @note   This function is implement the simple uart output a char
  * @param  cr
  * @retval None
  */
static void simple_uart_put(uint8_t cr)
{
    NRF_UART0->TXD = (uint8_t)cr;

    while (NRF_UART0->EVENTS_TXDRDY != 1)
    {
        // Wait for TXD data to be sent.
    }

    NRF_UART0->EVENTS_TXDRDY = 0;
}
/**
  * @brief  simple_uart_putstring
  * @note   This function is implement the simple uart output a string
  * @param  str
  * @retval None
  */
void simple_uart_putstring(uint8_t * str)
{
    uint_fast8_t i  = 0;
    uint8_t      ch = str[i++];

    while (ch != '\0')
    {
        simple_uart_put(ch);
        ch = str[i++];
    }
}

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/

