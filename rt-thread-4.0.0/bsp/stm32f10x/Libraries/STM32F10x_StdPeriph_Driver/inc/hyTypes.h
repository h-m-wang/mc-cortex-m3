/*******************************************************************************
*   All rights reserved              
*
*  This source code and any compilation or derivative thereof is the sole      
*  property of xxxx Technology Co., Ltd and is provided pursuant 
*  to a Software License Agreement.  This code is the proprietary information of      
*  xxxx and is confidential in nature.  Its use and dissemination by    
*  any party other than xxxx is strictly limited by the confidential information 
*  provisions of the Agreement referenced above.      
*
*******************************************************************************
*
* Rev   Date    Author          Comments
*      (yymmdd)
* -------------------------------------------------------------
* 001   160506  ICE WANG		Primary version 
* -------------------------------------------------------------
*
*  This source file contains the basic data type definition  
*
****************************************************************/

#ifndef ARMTYPE_DEFINITION_H
#define ARMTYPE_DEFINITION_H

// 用于PC simulation时
//#define PC_MP3_SIMULATION 

/* Boolean values */
/* #ifndef TRUE switch introduced to avoid compilation problems in the Visual studio enviroment*/
#ifndef TRUE
#define TRUE  (1==1)
#endif

/*#ifndef FALSE switch introduced to avoid compilation problems in the Visual studio enviroment*/
#ifndef FALSE
#define FALSE  (1==0)
#endif

/* #ifndef TRUE switch introduced to avoid compilation problems in the Visual studio enviroment*/
#ifndef True
#define True	TRUE
#endif

/*#ifndef FALSE switch introduced to avoid compilation problems in the Visual studio enviroment*/
#ifndef False
#define False   FALSE
#endif


#ifndef NULL	/* Null */
#define NULL  (0)
#endif 

#ifndef Null	/* Null */
#define Null  (0)
#endif 


#ifndef CONST	/* Const */
#define CONST  const
#endif 

#ifndef ASSERT
#define ASSERT(a,b)
#endif

#ifndef ROM
#define ROM const
#endif


#ifndef DATA
#define DATA
#endif

#ifndef BIT0
#define BIT0  (0x00000001)            
#define BIT1  (0x00000002)            
#define BIT2  (0x00000004)            
#define BIT3  (0x00000008)      
#define BIT4  (0x00000010)        
#define BIT5  (0x00000020)        
#define BIT6  (0x00000040)        
#define BIT7  (0x00000080)            
#define BIT8  (0x00000100)            
#define BIT9  (0x00000200)            
#define BIT10 (0x00000400)            
#define BIT11 (0x00000800)            
#define BIT12 (0x00001000)            
#define BIT13 (0x00002000)            
#define BIT14 (0x00004000)            
#define BIT15 (0x00008000)            
#define BIT16 (0x00010000)           
#define BIT17 (0x00020000)           
#define BIT18 (0x00040000)           
#define BIT19 (0x00080000)           
#define BIT20 (0x00100000)           
#define BIT21 (0x00200000)       
#define BIT22 (0x00400000)            
#define BIT23 (0x00800000)            
#define BIT24 (0x01000000)            
#define BIT25 (0x02000000)            
#define BIT26 (0x04000000)           
#define BIT27 (0x08000000)           
#define BIT28 (0x10000000)           
#define BIT29 (0x20000000)           
#define BIT30 (0x40000000)           
#define BIT31 (0x80000000)       
#endif //#ifndef BIT0


#ifndef MAX
/* The larger of __x and __y */
#define MAX( __x, __y ) \
    ((__x) > (__y) ? (__x) : (__y))
#endif

#ifndef MIN
/* The smaller of __x and __y */
#define MIN( __x, __y ) \
    ((__x) < (__y) ? (__x) : (__y))
#endif

#ifndef ABS
/* The absolute value of __x */
#define ABS( __x ) \
    (((__x) > 0) ? (__x) : -(__x))
#endif

#ifndef LIMIT
/* The value __x or the bound __y or __z if outside them */
#define LIMIT( __x, __y, __z ) \
    MAX( MIN( (__x), MAX( (__y), (__z) )), MIN( (__y), (__z) ))
#endif

#ifndef LOW_BYTE
#define LOW_BYTE(word)      (   word & 0x00ff )
#endif

#ifndef HIGH_BYTE
#define HIGH_BYTE(word)     ( ( word & 0xff00 ) >> 8 )
#endif


/* Primitive types */
#ifdef PC_MP3_SIMULATION
	typedef int BOOL;
	typedef unsigned char  BOOLEAN; 
#else
	#ifdef BOOL
	#undef BOOL
	#endif
	typedef unsigned char	BOOL;
#endif


typedef signed char			S8,		*pS8,    Int8,   *pInt8;     /*  8 bit   signed integer */
typedef unsigned char		U8,		*pU8,    UInt8,  *pUInt8;    /*  8 bit unsigned integer */
typedef short				S16,	*pS16,   Int16,  *pInt16;    /* 16 bit   signed integer */
typedef long				S32,	*pS32,   Int32,  *pInt32;    /* 32 bit   signed integer */
typedef unsigned short		U16,	*pU16,   UInt16, *pUInt16;   /* 16 bit unsigned integer */
typedef unsigned long		U32,	*pU32,   UInt32, *pUInt32;   /* 32 bit unsigned integer */
typedef void            	Void,   *pVoid;     /* Void (typeless) */
typedef float           	Float,  *pFloat;    /* 32 bit floating point */
typedef double          	Double, *pDouble;   /* 32/64 bit floating point */
typedef unsigned char   	Bool,   *pBool;     /* Boolean (True/False) */
typedef char            	Char,   *pChar;     /* character, character array ptr */
typedef char           		*String, **pString; /* Null terminated 8 bit char str, */
typedef char const     		*ConstString;		/* Null term 8 bit char str ptr */
typedef void 		  		(* PFN)(void);      /* PFN is pointer to function */

//关于错误的定义，除了0以外，其余返回值均为错误。
#define HY_OK                     		0         	// Global success return status
#define HY_ERROR                   		0xFF      	// Global error return status
#define HY_ERR_COMPATIBILITY            0x01 /* SW Interface compatibility   */
#define HY_ERR_MAJOR_VERSION            0x02 /* SW Major Version error       */
#define HY_ERR_COMP_VERSION             0x03 /* SW component version error   */
#define HY_ERR_BAD_MODULE_ID            0x04 /* SW - HW module ID error      */
#define HY_ERR_BAD_UNIT_NUMBER          0x05 /* Invalid device unit number   */
#define HY_ERR_BAD_INSTANCE             0x06 /* Bad input instance value     */
#define HY_ERR_BAD_HANDLE               0x07 /* Bad input handle             */
#define HY_ERR_BAD_INDEX                0x08 /* Bad input index              */
#define HY_ERR_BAD_PARAMETER            0x09 /* Invalid input parameter      */
#define HY_ERR_NO_INSTANCES             0x0A /* No instances available       */
#define HY_ERR_NO_COMPONENT             0x0B /* Component is not present     */
#define HY_ERR_NO_RESOURCES             0x0C /* Resource is not available    */
#define HY_ERR_INSTANCE_IN_USE          0x0D /* Instance is already in use   */
#define HY_ERR_RESOURCE_OWNED           0x0E /* Resource is already in use   */
#define HY_ERR_RESOURCE_NOT_OWNED       0x0F /* Caller does not own resource */
#define HY_ERR_INCONSISTENT_PARAMS      0x10 /* Inconsistent input params    */
#define HY_ERR_NOT_INITIALIZED          0x11 /* Component is not initialized */
#define HY_ERR_NOT_ENABLED              0x12 /* Component is not enabled     */
#define HY_ERR_NOT_SUPPORTED            0x13 /* Function is not supported    */
#define HY_ERR_INIT_FAILED              0x14 /* Initialization failed        */
#define HY_ERR_BUSY                     0x15 /* Component is busy            */
#define HY_ERR_NOT_BUSY                 0x16 /* Component is not busy        */
#define HY_ERR_READ                     0x17 /* Read error                   */
#define HY_ERR_WRITE                    0x18 /* Write error                  */
#define HY_ERR_ERASE                    0x19 /* Erase error                  */
#define HY_ERR_LOCK                     0x1A /* Lock error                   */
#define HY_ERR_UNLOCK                   0x1B /* Unlock error                 */
#define HY_ERR_OUT_OF_MEMORY            0x1C /* Memory allocation failed     */
#define HY_ERR_BAD_VIRT_ADDRESS         0x1D /* Bad virtual address          */
#define HY_ERR_BAD_PHYS_ADDRESS         0x1E /* Bad physical address         */
#define HY_ERR_TIMEOUT                  0x1F /* Timeout error                */
#define HY_ERR_OVERFLOW                 0x20 /* Data overflow/overrun error  */
#define HY_ERR_FULL                     0x21 /* Queue (etc.) is full         */
#define HY_ERR_EMPTY                    0x22 /* Queue (etc.) is empty        */
#define HY_ERR_NOT_STARTED              0x23 /* Component stream not started */
#define HY_ERR_ALREADY_STARTED          0x24 /* Comp. stream already started */
#define HY_ERR_NOT_STOPPED              0x25 /* Component stream not stopped */
#define HY_ERR_ALREADY_STOPPED          0x26 /* Comp. stream already stopped */
#define HY_ERR_ALREADY_SETUP            0x27 /* Component already setup      */
#define HY_ERR_NULL_PARAMETER           0x28 /* Null input parameter         */
#define HY_ERR_NULL_DATAINFUNC          0x29 /* Null data input function     */
#define HY_ERR_NULL_DATAOUTFUNC         0x2A /* Null data output function    */
#define HY_ERR_NULL_CONTROLFUNC         0x2B /* Null control function        */
#define HY_ERR_NULL_COMPLETIONFUNC      0x2C /* Null completion function     */
#define HY_ERR_NULL_PROGRESSFUNC        0x2D /* Null progress function       */
#define HY_ERR_NULL_ERRORFUNC           0x2E /* Null error handler function  */
#define HY_ERR_NULL_MEMALLOCFUNC        0x2F /* Null memory alloc function   */
#define HY_ERR_NULL_MEMFREEFUNC         0x30 /* Null memory free  function   */
#define HY_ERR_NULL_CONFIGFUNC          0x31 /* Null configuration function  */
#define HY_ERR_NULL_PARENT              0x32 /* Null parent data             */
#define HY_ERR_NULL_IODESC              0x33 /* Null in/out descriptor       */
#define HY_ERR_NULL_CTRLDESC            0x34 /* Null control descriptor      */
#define HY_ERR_UNSUPPORTED_DATACLASS    0x35 /* Unsupported data class       */
#define HY_ERR_UNSUPPORTED_DATATYPE     0x36 /* Unsupported data type        */
#define HY_ERR_UNSUPPORTED_DATASUBTYPE  0x37 /* Unsupported data subtype     */
#define HY_ERR_FORMAT                   0x38 /* Invalid/unsupported format   */
#define HY_ERR_INPUT_DESC_FLAGS         0x39 /* Bad input  descriptor flags  */
#define HY_ERR_OUTPUT_DESC_FLAGS        0x3A /* Bad output descriptor flags  */
#define HY_ERR_CAP_REQUIRED             0x3B /* Capabilities required ???    */
#define HY_ERR_BAD_TMALFUNC_TABLE       0x3C /* Bad TMAL function table      */
#define HY_ERR_INVALID_CHANNEL_ID       0x3D /* Invalid channel identifier   */
#define HY_ERR_INVALID_COMMAND          0x3E /* Invalid command/request      */
#define HY_ERR_STREAM_MODE_CONFUSION    0x3F /* Stream mode config conflict  */
#define HY_ERR_UNDERRUN                 0x40 /* Data underflow/underrun      */
#define HY_ERR_EMPTY_PACKET_RECVD       0x41 /* Empty data packet received   */
#define HY_ERR_OTHER_DATAINOUT_ERR      0x42 /* Other data input/output err  */
#define HY_ERR_STOP_REQUESTED           0x43 /* Stop in progress             */
#define HY_ERR_PIN_NOT_STARTED          0x44 /* Pin not started              */
#define HY_ERR_PIN_ALREADY_STARTED      0x45 /* Pin already started          */
#define HY_ERR_PIN_NOT_STOPPED          0x46 /* Pin not stopped              */
#define HY_ERR_PIN_ALREADY_STOPPED      0x47 /* Pin already stopped          */
#define HY_ERR_PAUSE_PIN_REQUESTED      0x48 /* Pause of single pin in progrs*/
#define HY_ERR_ASSERTION                0x49 /* Assertion failure            */
#define HY_ERR_HIGHWAY_BANDWIDTH        0x4A /* Highway bandwidth bus error  */
#define HY_ERR_HW_RESET_FAILED          0x4B /* Hardware reset failed        */
#define HY_ERR_PIN_PAUSED               0x4C /* Pin paused                   */
#define HY_ERR_BAD_FLAGS                0x4D /* Bad flags                    */
#define HY_ERR_BAD_PRIORITY             0x4E /* Bad priority                 */
#define HY_ERR_BAD_REFERENCE_COUNT      0x4F /* Bad reference count          */
#define HY_ERR_BAD_SETUP                0x50 /* Bad setup                    */
#define HY_ERR_BAD_STACK_SIZE           0x51 /* Bad stack size               */
#define HY_ERR_BAD_TEE                  0x52 /* Bad tee                      */
#define HY_ERR_IN_PLACE                 0x53 /* In place                     */
#define HY_ERR_NOT_CACHE_ALIGNED        0x54 /* Not cache aligned            */
#define HY_ERR_NO_ROOT_TEE              0x55 /* No root tee                  */
#define HY_ERR_NO_TEE_ALLOWED           0x56 /* No tee allowed               */
#define HY_ERR_NO_TEE_EMPTY_PACKET      0x57 /* No tee empty packet          */
#define HY_ERR_NULL_PACKET              0x59 /* Null packet                  */
#define HY_ERR_FORMAT_FREED             0x5A /* Format freed                 */
#define HY_ERR_FORMAT_INTERNAL          0x5B /* Format internal              */
#define HY_ERR_BAD_FORMAT               0x5C /* Bad format                   */
#define HY_ERR_FORMAT_NEGOTIATE_SUBCLASS    0x5D /* Format negotiate subclass*/
#define HY_ERR_FORMAT_NEGOTIATE_DATASUBTYPE 0x5E /* Format negot. datasubtype*/
#define HY_ERR_FORMAT_NEGOTIATE_DATATYPE    0x5F /* Format negotiate datatype*/
#define HY_ERR_FORMAT_NEGOTIATE_DESCRIPTION 0x60 /* Format negot. description*/
#define HY_ERR_NULL_FORMAT              0x61 /* Null format                  */
#define HY_ERR_FORMAT_REFERENCE_COUNT   0x62 /* Format reference count       */
#define HY_ERR_FORMAT_NOT_UNIQUE        0x63 /* Format not unique            */
#define HY_ERR_NEW_FORMAT               0x64 /* New format                   */

typedef U8 hyErrorCode_t;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
#endif /* ARMTYPE_DEFINITION_H */
