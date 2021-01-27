/**
 * @file    FRDMKL02Z_MMA8451.c
 * @author  Alexander Huertas Sanchez
 * @version V0.2
 * @brief   Application entry point.
 */
/*  SDK Included Files */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

/*  SDK HAL Files */
#include "sdk_hal_gpio.h"
#include "sdk_hal_uart0.h"
#include "sdk_hal_i2c0.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MMA8451_I2C_DEVICE_ADDRESS	0x1D


/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	status_t status;
    uint8_t nuevo_byte_uart;
	uint8_t	nuevo_dato_i2c;
	uint8_t X_MSB;
	uint8_t X_LSB;
	uint16_t dato_x;
	uint8_t Y_MSB;
	uint8_t Y_LSB;
	uint16_t dato_y;
	uint8_t Z_MSB;
	uint8_t Z_LSB;
	uint16_t dato_z;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    (void)uart0Inicializar(115200U);	//115200bps
    (void)i2c0MasterInit(100000U);	//100kbps

    PRINTF("¡BIENVENIDO!\r\n");
    PRINTF("DIGITE UNA DE LAS SIGUIENTES OPCIONES \r\n");
    PRINTF("ENCENDER LED ROJO: R  APAGAR LED ROJO: r \r\n");
    PRINTF("ENCENDER LED VERDE: V  APAGAR LED VERDE: v \r\n");
    PRINTF("ENCENDER/APAGAR LED AZUL: a-A \r\n");
    PRINTF("BUSCAR ACELEROMETRO: M \r\n");
    PRINTF("DATOS DEL ACELEROMETRO EJE X: X-x \r\n");
    PRINTF("DATOS DEL ACELEROMETRO EJE Y: Y-y \r\n");
    PRINTF("DATOS DEL ACELEROMETRO EJE Z: Z-z \r\n");
    PRINTF("DATOS DE LOS EJES (X, Y, Z): T-t \r\n");
    while(1) {

    	if(uart0CuantosDatosHayEnBuffer()>0){
    		status=uart0LeerByteDesdeBuffer(&nuevo_byte_uart);
    		i2c0MasterWriteByte(MMA8451_I2C_DEVICE_ADDRESS, CTRL_REG1, 0x01);
    		if(status==kStatus_Success){
    			printf("dato:%c\r\n",nuevo_byte_uart);
    			switch (nuevo_byte_uart) {
				case 'a':
				case 'A':
					gpioPutToggle(KPTB10);
					break;

				case 'v':
					gpioPutHigh(KPTB7);
					break;
				case 'V':
					gpioPutLow(KPTB7);
					break;

				case 'r':
					gpioPutValue(KPTB6,1);
					break;
				case 'R':
					gpioPutValue(KPTB6,0);
					break;

				case 'm':
				case 'M':
				i2c0MasterReadByte(&nuevo_dato_i2c, MMA8451_I2C_DEVICE_ADDRESS, WHO_AM_I);


				if(nuevo_dato_i2c==0x1A)
			     	printf("MMA8451 encontrado!!\r\n");
					else
					printf("MMA8451 error\r\n");

					break;

				case 'x':
				case 'X':
				i2c0MasterReadByte(&X_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_MSB);
				i2c0MasterReadByte(&X_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_LSB);
				dato_x=(uint16_t)(X_MSB << 6 | X_LSB >> 2);
				printf("Valor en X: %i \r\n", dato_x);
				break;

				case 'y':
				case 'Y':
				i2c0MasterReadByte(&Y_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_MSB);
				i2c0MasterReadByte(&Y_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_LSB);
				dato_y=(uint16_t)(Y_MSB << 6 | Y_LSB >> 2);
				printf("Valor en Y: %i \r\n", dato_y);
				break;

				case 'z':
				case 'Z':
				i2c0MasterReadByte(&Z_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_MSB);
				i2c0MasterReadByte(&Z_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_LSB);
				dato_z=(uint16_t)(Z_MSB << 6 | Z_LSB >> 2);
				printf("Valor en Z: %i \r\n", dato_z);
				break;

				case 't':
				case 'T':
				/////////// Coordenada X ///////////
				i2c0MasterReadByte(&X_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_MSB);
				i2c0MasterReadByte(&X_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_X_LSB);
				dato_x=(uint16_t)(X_MSB << 6 | X_LSB >> 2);

				/////////// Coordenada Y ///////////
				i2c0MasterReadByte(&Y_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_MSB);
				i2c0MasterReadByte(&Y_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Y_LSB);
				dato_y=(uint16_t)(Y_MSB << 6 | Y_LSB >> 2);

				/////////// Coordenada Y ///////////
				i2c0MasterReadByte(&Z_MSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_MSB);
				i2c0MasterReadByte(&Z_LSB, MMA8451_I2C_DEVICE_ADDRESS, OUT_Z_LSB);
				dato_z=(uint16_t)(Z_MSB << 6 | Z_LSB >> 2);
				printf("Valor en (X, Y, Z): (%i, %i, %i) \r\n", dato_x, dato_y, dato_z);

				}
    		}else{
    			printf("error\r\n");
    		}
    	}
    }
    return 0 ;
}
