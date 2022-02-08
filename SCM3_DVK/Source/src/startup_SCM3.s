;******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
;* File Name          : startup_stm32f10x_hd.s
;* Author             : MCD Application Team
;* Version            : V3.1.2
;* Date               : 09/28/2009
;* Description        : STM32F10x High Density Devices vector table for RVMDK 
;*                      toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure external SRAM mounted on STM3210E-EVAL board
;*                        to be used as data memory (optional, to be enabled by user)
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>   
;*******************************************************************************
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

                                                  ; always internal RAM used 
                                                  
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp           	  ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     DMAIntHandler             ;	Dmac Controller
                DCD     0                         ; 
                DCD		0            			  ;	
                DCD		0             			  ;	
                DCD     Timer1IntHandler          ; Timer 1
				DCD     Timer2IntHandler          ; Timer 2
				DCD     WWDG_IRQHandler           ;	Watch Dog
				DCD     DINTC_IRQHandler          ; Dmac Interrupt Tc
				DCD     DINTE_IRQHandler          ; Dmac Interrupt Err
				DCD     GPIOC_IRQHandler          ; GPIO C
				DCD     UART_IRQHandler           ; UART
				DCD     GPIOA_IRQHandler          ; GPIO A
				DCD     GPIOB_IRQHandler          ; GPIO B
				DCD     FLASH_IRQHandler          ; FLASH
                
__Vectors_End

__Vectors_Size 	EQU 	__Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Dummy SystemInit_ExtMemCtl function                
SystemInit_ExtMemCtl     PROC
                EXPORT  SystemInit_ExtMemCtl      [WEAK]
                BX      LR
                ENDP
                
; Reset handler routine
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main

                LDR     R0, =__main
                BX      R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  DMAIntHandler       [WEAK]          ;Dmac Controller
                EXPORT	Timer1IntHandler    [WEAK]          ;Timer 0
				EXPORT	Timer2IntHandler    [WEAK]          ;Timer 1
				EXPORT  WWDG_IRQHandler     [WEAK]          ;Watch Dog
				EXPORT  DINTC_IRQHandler    [WEAK]          ;Dmac Interrupt Tc
				EXPORT  DINTE_IRQHandler    [WEAK]          ;Dmac Interrupt Err
				EXPORT  GPIOC_IRQHandler    [WEAK]          ;GPIO C
				EXPORT  UART_IRQHandler     [WEAK]          ;UART
				EXPORT  GPIOA_IRQHandler    [WEAK]          ;GPIO A
				EXPORT  GPIOB_IRQHandler    [WEAK]          ;GPIO B
				EXPORT  FLASH_IRQHandler    [WEAK]          ;FLASH
     

DMAIntHandler      
Timer1IntHandler   
Timer2IntHandler   
WWDG_IRQHandler  
DINTC_IRQHandler  
DINTE_IRQHandler  
GPIOC_IRQHandler
UART_IRQHandler
GPIOA_IRQHandler 
GPIOB_IRQHandler 
FLASH_IRQHandler 
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE*****
