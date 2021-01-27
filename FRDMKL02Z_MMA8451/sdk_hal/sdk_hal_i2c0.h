/*! @file : sdk_hal_i2c0.h
 * @author  Alexander Huertas Sanchez
 * @version 1.0.0
 * @date    11/01/2021
 * @brief   Driver for I2C0
 * @details
 *
 */
#ifndef SDK_HAL_I2C0_H_
#define SDK_HAL_I2C0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"


/*!
 * @addtogroup HAL
 * @{
 */
/*!
 * @addtogroup I2C
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
enum _i2c0_reg_address {
	///////////////////// ESTADO //////////////////////////
	STATUS_F_STATUS = 0x00,	//FMODE = 0, Estado en tiempo real. FMODE> 0, estado FIFO
	///////////////////// DIRECCIO DE REGISTRO X, Y, Z //////////////////////////
	OUT_X_MSB,				//Son Ocho MSB de muestra de 14 bits [7:0]
	OUT_X_LSB,				//Son Seis LSB de muestra de 14 bits [7:2]
	OUT_Y_MSB,				//Son Ocho MSB de muestra de 14 bits [7:0]
	OUT_Y_LSB,				//Son Seis LSB de muestra de 14 bits [7:2]
	OUT_Z_MSB,				//Son Ocho MSB de muestra de 14 bits [7:0]
	OUT_Z_LSB,				//Son Seis LSB de muestra de 14 bits [7:2]
//////////////////////////////////////////////////////////////
	F_SETUP = 0x09,			//Configuración FIFO
	TRIG_CFG,				//Mapa de eventos de captura de datos FIFO
	SYSMOD,					//Modo del sistema actual
	INT_SOURCE,				//Estado de interrupción
	WHO_AM_I,				//ID del dispositivo (0x1A)
	XYZ_DATA_CFG,			//Configuración de rango dinámico
	HP_FILTER_CUTOFF,		//La frecuencia de corte se establece en 16 Hz a 800 Hz
	PL_STATUS,				//Estado de orientación horizontal / vertical
	PL_CFG,					//Configuración horizontal / vertical.
	PL_COUNT,				//Contador antirrebote horizontal / vertical
	PL_BF_ZCOMP,			//Posterior / frontal, umbral de disparo de bloqueo en Z
	P_L_THS_REG,			//El ángulo de disparo vertical a horizontal es de 29°
	FF_MT_CFG,				//Configuración del bloque funcional de caída libre / movimiento
	FF_MT_SRC,				//Registro de origen de evento de caída libre / movimiento
	FF_MT_THS,				//Registro de umbral de caída libre / movimiento
	FF_MT_COUNT, 			//Contador antirrebote de caída libre / movimiento

	TRANSIENT_CFG = 0x1D, 	//Configuración transitoria del bloque funcional
	TRANSIENT_SCR,			//Registro de estado de evento transitorio
	TRANSIENT_THS,			//Umbral de evento transitorio
	TRANSIENT_COUNT, 		//Contador antirrebote transitorio
	PULSE_CFG,		 		//ELE, doble XYZ o simple XYZ
	PULSE_SRC,		 		//EA, XYZ doble o XYZ simple
	PULSE_THSX,		 		//X umbral de pulso
	PULSE_THSY,		 		//umbral de pulso Y
	PULSE_THSZ,		 		//umbral de pulso Z
	PULSE_TMLT,		 		//Límite de tiempo para el pulso
	PULSE_LTCY,		 		//Tiempo de latencia para el segundo pulso
	PULSE_WIND,		 		//Tiempo de ventana para el segundo pulso
	ASLP_COUNT,		 		//Configuración del contador para suspensión automática
	CTRL_REG1,		 		//ODR = 800 Hz, modo de espera.
	CTRL_REG2,		 		//Habilitación de suspensión, modos OS, RST, ST
	CTRL_REG3,		 		//Despertar de la suspensión, IPOL, PP_OD
	CTRL_REG4,		 		//Registro de habilitación de interrupciones
	CTRL_REG5,		 		//Mapa de pin de interrupción (INT1 / INT2)
	OFF_X,		 			//ajuste de compensación del eje X
	OFF_Y,		 			//Ajuste de compensación del eje Y
	OFF_Z,		 			//ajuste de compensación del eje Z




};

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
/*--------------------------------------------*/
/*!
 * @brief Inicializa I2C0 al baudrate especificado
 *
 * @param baud_rate   baudrate (bps) que se quiere configurado en I2C0
 * @return            resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterInit(uint32_t baud_rate);

/*!
 * @brief Lee 1 byte usando puerto I2C0
 *
 * @param data   			apuntador a memoria donde almacenar dato obtenido
 * @param device_address	direccion en bus I2C de dispositivo remoto a leer
 * @param memory_address	posicion de memoria en el dispositivo remoto que se quiere leer
 * @return            		resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t i2c0MasterReadByte(uint8_t *data, uint8_t device_address, int8_t memory_address);

status_t i2c0MasterWriteByte(uint8_t data, uint8_t deviceAddress);




/** @} */ // end of I2C0 group
/** @} */ // end of HAL group

#endif /* SDK_HAL_I2C0_H_ */
