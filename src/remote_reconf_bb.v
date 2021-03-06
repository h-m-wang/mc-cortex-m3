// megafunction wizard: %ALTREMOTE_UPDATE%VBB%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: altremote_update 

// ============================================================
// File Name: remote_reconf.v
// Megafunction Name(s):
// 			altremote_update
//
// Simulation Library Files(s):
// 			cycloneive;lpm
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 13.0.1 Build 232 06/12/2013 SP 1 SJ Full Version
// ************************************************************

//Copyright (C) 1991-2013 Altera Corporation
//Your use of Altera Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Altera Program License 
//Subscription Agreement, Altera MegaCore Function License 
//Agreement, or other applicable license agreement, including, 
//without limitation, that your use is for the sole purpose of 
//programming logic devices manufactured by Altera and sold by 
//Altera or its authorized distributors.  Please refer to the 
//applicable agreement for further details.

module remote_reconf (
	clock,
	data_in,
	param,
	read_param,
	read_source,
	reconfig,
	reset,
	reset_timer,
	write_param,
	busy,
	data_out)/* synthesis synthesis_clearbox = 1 */;

	input	  clock;
	input	[21:0]  data_in;
	input	[2:0]  param;
	input	  read_param;
	input	[1:0]  read_source;
	input	  reconfig;
	input	  reset;
	input	  reset_timer;
	input	  write_param;
	output	  busy;
	output	[28:0]  data_out;

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Cyclone IV E"
// Retrieval info: PRIVATE: SIM_INIT_PAGE_SELECT_COMBO STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_STAT_BIT0_CHECK STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_STAT_BIT1_CHECK STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_STAT_BIT2_CHECK STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_STAT_BIT3_CHECK STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_STAT_BIT4_CHECK STRING "0"
// Retrieval info: PRIVATE: SIM_INIT_WATCHDOG_VALUE_EDIT STRING "1"
// Retrieval info: PRIVATE: SUPPORT_WRITE_CHECK STRING "1"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
// Retrieval info: PRIVATE: WATCHDOG_ENABLE_CHECK STRING "0"
// Retrieval info: CONSTANT: CHECK_APP_POF STRING "false"
// Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "Cyclone IV E"
// Retrieval info: CONSTANT: IN_DATA_WIDTH NUMERIC "22"
// Retrieval info: CONSTANT: OPERATION_MODE STRING "REMOTE"
// Retrieval info: CONSTANT: OUT_DATA_WIDTH NUMERIC "29"
// Retrieval info: USED_PORT: busy 0 0 0 0 OUTPUT NODEFVAL "busy"
// Retrieval info: USED_PORT: clock 0 0 0 0 INPUT NODEFVAL "clock"
// Retrieval info: USED_PORT: data_in 0 0 22 0 INPUT NODEFVAL "data_in[21..0]"
// Retrieval info: USED_PORT: data_out 0 0 29 0 OUTPUT NODEFVAL "data_out[28..0]"
// Retrieval info: USED_PORT: param 0 0 3 0 INPUT NODEFVAL "param[2..0]"
// Retrieval info: USED_PORT: read_param 0 0 0 0 INPUT NODEFVAL "read_param"
// Retrieval info: USED_PORT: read_source 0 0 2 0 INPUT NODEFVAL "read_source[1..0]"
// Retrieval info: USED_PORT: reconfig 0 0 0 0 INPUT NODEFVAL "reconfig"
// Retrieval info: USED_PORT: reset 0 0 0 0 INPUT NODEFVAL "reset"
// Retrieval info: USED_PORT: reset_timer 0 0 0 0 INPUT NODEFVAL "reset_timer"
// Retrieval info: USED_PORT: write_param 0 0 0 0 INPUT NODEFVAL "write_param"
// Retrieval info: CONNECT: @clock 0 0 0 0 clock 0 0 0 0
// Retrieval info: CONNECT: @data_in 0 0 22 0 data_in 0 0 22 0
// Retrieval info: CONNECT: @param 0 0 3 0 param 0 0 3 0
// Retrieval info: CONNECT: @read_param 0 0 0 0 read_param 0 0 0 0
// Retrieval info: CONNECT: @read_source 0 0 2 0 read_source 0 0 2 0
// Retrieval info: CONNECT: @reconfig 0 0 0 0 reconfig 0 0 0 0
// Retrieval info: CONNECT: @reset 0 0 0 0 reset 0 0 0 0
// Retrieval info: CONNECT: @reset_timer 0 0 0 0 reset_timer 0 0 0 0
// Retrieval info: CONNECT: @write_param 0 0 0 0 write_param 0 0 0 0
// Retrieval info: CONNECT: busy 0 0 0 0 @busy 0 0 0 0
// Retrieval info: CONNECT: data_out 0 0 29 0 @data_out 0 0 29 0
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf.inc FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf.bsf FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf_inst.v FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL remote_reconf_bb.v TRUE
// Retrieval info: LIB_FILE: cycloneive
// Retrieval info: LIB_FILE: lpm
