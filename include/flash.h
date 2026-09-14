#include "driver_w25qxx.h"
#include <Arduino.h>

/**
 * @defgroup w25qxx_example_driver w25qxx example driver function
 * @brief    w25qxx example driver modules
 * @ingroup  w25qxx_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @param[in] interface chip interface
 * @param[in] dual_quad_spi_enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t w25qxx_basic_init(w25qxx_type_t type, w25qxx_interface_t interface, w25qxx_bool_t dual_quad_spi_enable);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t w25qxx_basic_deinit(void);

/**
 * @brief  basic example power down
 * @return status code
 *         - 0 success
 *         - 1 power down failed
 * @note   none
 */
uint8_t w25qxx_basic_power_down(void);

/**
 * @brief  basic example wake up
 * @return status code
 *         - 0 success
 *         - 1 wake up failed
 * @note   none
 */
uint8_t w25qxx_basic_wake_up(void);

/**
 * @brief  basic example chip erase
 * @return status code
 *         - 0 success
 *         - 1 chip erase failed
 * @note   none
 */
uint8_t w25qxx_basic_chip_erase(void);

/**
 * @brief      basic example get the manufacturer && device id information
 * @param[out] *manufacturer pointer to a manufacturer buffer
 * @param[out] *device_id pointer to a device id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get manufacturer device id failed
 * @note       none
 */
uint8_t w25qxx_basic_get_id(uint8_t *manufacturer, uint8_t *device_id);

/**
 * @brief     basic example write
 * @param[in] addr written address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t w25qxx_basic_write(uint32_t addr, uint8_t *data, uint32_t len);

/**
 * @brief      basic example read
 * @param[in]  addr read address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t w25qxx_basic_read(uint32_t addr, uint8_t *data, uint32_t len);
