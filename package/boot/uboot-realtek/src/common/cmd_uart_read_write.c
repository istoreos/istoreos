#include <common.h>
#include <command.h>
#include <serial.h>

extern int serial_init_uart(char uart);
extern void switch_into_mtmode(void);

static int do_uart_read_write (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	#if 0
	int port_num;
	int uart_offset;
	int send_receive_value = 0;
	#endif
	
	if (argc == 2)
	{
		if (strcmp(argv[1], "run") == 0)
		{
			printf ("Bring up UART1\n\n");	
			
			/* disable uart1 reset bits and uart1 clocl bits , then enable it */
			*(volatile unsigned int *)0x98000004 = (unsigned int)0xf840e01;
			*(volatile unsigned int *)0x98000010 = (unsigned int)0x4801e406;
			/* disable uart1 reset bits and uart1 clocl bits , then enable it */
			*(volatile unsigned int *)0x98000004 = (unsigned int)0x1f840e01;
			*(volatile unsigned int *)0x98000010 = (unsigned int)0x5801e406;	
			
			*(volatile unsigned int *)0x98007310 = (unsigned int)0x155400; 	/*Setup ISO MUX PAD0 for uart1 pins*/
			*(volatile unsigned int *)0x9801B200 = (unsigned int)0x90; 		/*UART1_LCR*/
			*(volatile unsigned int *)0x9801B200 = (unsigned int)0xea;		/*UART1_DLL Set baud rate to 115200 base on 432 MHz*/
			*(volatile unsigned int *)0x9801B204 = (unsigned int)0x0;		/*UART1_DLM*/
			*(volatile unsigned int *)0x9801B20c = (unsigned int)0x03;		/*UART1_LCR (8-N-1)*/
			*(volatile unsigned int *)0x9801B208 = (unsigned int)0xc7;		/*UART1_FCR*/
			*(volatile unsigned int *)0x9801B204 = (unsigned int)0x01;		/*UART1_IER*/

			serial_init_uart(UART1);	/*UART1 initialization and setting clock HZ.*/

			return CMD_RET_SUCCESS;
		}
	}
	else if (argc == 4)
	{
		#if 0
		if (strcmp(argv[1], "read") == 0)
		{
			port_num = (int)simple_strtoul(argv[2], NULL, 10);
			uart_offset = (int)simple_strtoul(argv[3], NULL, 10);
			if (port_num == 0){
				if (!serial_assign("eserial0"))
					printf("Success!\n");
				else
					printf("Failed!\n");
				serial_init();
				printf("The get char from uart0 is %d\n", serial_getc());
			}else if(port_num == 1){
				if (!serial_assign("eserial1"))
					printf("Success!\n");
				else
					printf("Failed!\n");
				serial_init();
				printf("The get char from uart0 is %d\n", serial_getc());
			}
			printf("The port num is %d\n", port_num);
			printf("The input offset is %d\n", uart_offset);
			printf("The read write value is %d\n", send_receive_value);
		}
		#endif
		return CMD_RET_SUCCESS;
	}
	else if (argc == 5)
	{
		#if 0
		if (strcmp(argv[1], "write") == 0)
		{
			port_num = (int)simple_strtoul(argv[2], NULL, 10);
			uart_offset = (int)simple_strtoul(argv[3], NULL, 10);
			char * send_cahr;
			send_cahr = argv[4];
			if (port_num == 0){
				if (!serial_assign("eserial0"))
					printf("Success!\n");
				else
					printf("Failed!\n");
				serial_puts((char *)(uintptr_t)send_cahr);
				printf("The get char from uart0 is %d\n", serial_getc());
			}else if(port_num == 1){
				if (!serial_assign("eserial1"))
					printf("Success!\n");
				else
					printf("Failed!\n");
				serial_puts((char *)(uintptr_t)send_cahr);
				printf("The get char from uart0 is %d\n", serial_getc());
			}
			printf("The port num is %d\n", port_num);
			printf("The input offset is %d\n", uart_offset);
			printf("The read write value is %s\n", send_cahr);
		}
		#endif
		return CMD_RET_SUCCESS;
	}

    return CMD_RET_USAGE;
}

U_BOOT_CMD
(
    uart_rw, 5, 0,   do_uart_read_write,
    "UART related operation",
	"run - running UART1 initialization\n"
    "uart_rw read [port] [offset]\n"
	"uart_rw write [port] [offset] [value]\n"
);