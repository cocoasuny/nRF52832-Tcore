/**
  ****************************************************************************************
  * @file    bsp_cli.c
  * @author  Jason
  * @version V1.0.0
  * @date    2017-7-10
  * @brief   the implement of common line interface
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_cli.h"

#if NRF_MODULE_ENABLED(NRF_CLI)     //if cli module enabled in sdk_config.h

/* privarite function declares */
static void nrf_cli_cmd_print(nrf_cli_t const * p_cli, size_t argc, char **argv);
static void nrf_cli_cmd_pyt(nrf_cli_t const * p_cli, size_t argc, char **argv);


/* privarite variables declares */
static const nrf_cli_cmd_t m_cmd_set[] = {      //Command set array
        NRF_CLI_BUILTIN_CMD_SET,
        NRF_CLI_CMD("print", "command history", nrf_cli_cmd_print),
        NRF_CLI_CMD("python", "python interpreter", nrf_cli_cmd_pyt),
};

NRF_CLI_DEF(m_cli_uart,    "nrf_cli:~$ ", nrf_cli_uart_transport, m_cmd_set);   //Command line interface instance

/**
  * @brief  initialize for CLI
  * @param  None
  * @retval Status
  */
ret_code_t cli_init(void)
{
    ret_code_t ret = NRF_ERROR_NULL;
    
    ret = nrf_cli_init(&m_cli_uart);
    APP_ERROR_CHECK(ret);
    
    return ret;
}
/**
  * @brief  cli start 
  * @param  None
  * @retval Status
  */
ret_code_t cli_start(void)
{
    ret_code_t ret;

    ret = nrf_cli_start(&m_cli_uart);
    APP_ERROR_CHECK(ret);

    return ret;
}
/**
  * @brief  cli process
  * @note   the function should be schedulered priodically to process the cli status
  * @param  None
  * @retval None
  */
void cli_process(void)
{
    nrf_cli_process(&m_cli_uart);
}

static void nrf_cli_cmd_print(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (argc != 2)
    {
        nrf_cli_fprintf(p_cli,
                        NRF_CLI_ERROR,
                        "print: bad param count\r\n");
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "%s\r\n", argv[1]);
}

static void nrf_cli_cmd_pyt(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Nice jokee;)\r\n");
}


#endif // NRF_MODULE_ENABLED(NRF_CLI)

/************************ (C) COPYRIGHT 2017 ShenZhen DBGJ Co., Ltd. *****END OF FILE****/



