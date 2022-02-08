## Generated SDC file "top.sdc"

## Copyright (C) 1991-2013 Altera Corporation
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, Altera MegaCore Function License 
## Agreement, or other applicable license agreement, including, 
## without limitation, that your use is for the sole purpose of 
## programming logic devices manufactured by Altera and sold by 
## Altera or its authorized distributors.  Please refer to the 
## applicable agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 13.1.0 Build 162 10/23/2013 SJ Full Version"

## DATE    "Sat Jan 29 22:32:42 2022"

##
## DEVICE  "EP4CE15F23C8"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {altera_reserved_tck} -period 100.000 -waveform { 0.000 50.000 } [get_ports {altera_reserved_tck}]
create_clock -name {clk} -period 20.000 -waveform { 0.000 10.000 } [get_ports {CLK}]


#**************************************************************
# Create Generated Clock
#**************************************************************

create_generated_clock -name {cpu_clk} -source [get_ports {CLK}] -master_clock {clk} [get_pins {pll_inst|altpll_component|auto_generated|pll1|clk[0]}] 
create_generated_clock -name {spi_clk} -source [get_ports {CLK}] -master_clock {clk} [get_pins {pll_inst|altpll_component|auto_generated|pll1|clk[3]}] 


#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -rise_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -fall_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -rise_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -rise_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -fall_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -rise_from [get_clocks {spi_clk}] -fall_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -rise_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -fall_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -rise_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -rise_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -fall_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -fall_from [get_clocks {spi_clk}] -fall_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -rise_from [get_clocks {clk}] -rise_to [get_clocks {spi_clk}] -setup 0.070  
set_clock_uncertainty -rise_from [get_clocks {clk}] -rise_to [get_clocks {spi_clk}] -hold 0.100  
set_clock_uncertainty -rise_from [get_clocks {clk}] -fall_to [get_clocks {spi_clk}] -setup 0.070  
set_clock_uncertainty -rise_from [get_clocks {clk}] -fall_to [get_clocks {spi_clk}] -hold 0.100  
set_clock_uncertainty -rise_from [get_clocks {clk}] -rise_to [get_clocks {clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {clk}] -fall_to [get_clocks {clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {clk}] -rise_to [get_clocks {cpu_clk}] -setup 0.070  
set_clock_uncertainty -rise_from [get_clocks {clk}] -rise_to [get_clocks {cpu_clk}] -hold 0.100  
set_clock_uncertainty -rise_from [get_clocks {clk}] -fall_to [get_clocks {cpu_clk}] -setup 0.070  
set_clock_uncertainty -rise_from [get_clocks {clk}] -fall_to [get_clocks {cpu_clk}] -hold 0.100  
set_clock_uncertainty -fall_from [get_clocks {clk}] -rise_to [get_clocks {spi_clk}] -setup 0.070  
set_clock_uncertainty -fall_from [get_clocks {clk}] -rise_to [get_clocks {spi_clk}] -hold 0.100  
set_clock_uncertainty -fall_from [get_clocks {clk}] -fall_to [get_clocks {spi_clk}] -setup 0.070  
set_clock_uncertainty -fall_from [get_clocks {clk}] -fall_to [get_clocks {spi_clk}] -hold 0.100  
set_clock_uncertainty -fall_from [get_clocks {clk}] -rise_to [get_clocks {clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {clk}] -fall_to [get_clocks {clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {clk}] -rise_to [get_clocks {cpu_clk}] -setup 0.070  
set_clock_uncertainty -fall_from [get_clocks {clk}] -rise_to [get_clocks {cpu_clk}] -hold 0.100  
set_clock_uncertainty -fall_from [get_clocks {clk}] -fall_to [get_clocks {cpu_clk}] -setup 0.070  
set_clock_uncertainty -fall_from [get_clocks {clk}] -fall_to [get_clocks {cpu_clk}] -hold 0.100  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -rise_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -fall_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -rise_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -rise_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -fall_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -fall_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -rise_to [get_clocks {cpu_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {cpu_clk}] -fall_to [get_clocks {cpu_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -rise_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -fall_to [get_clocks {spi_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -rise_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -rise_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -fall_to [get_clocks {clk}] -setup 0.100  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -fall_to [get_clocks {clk}] -hold 0.070  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -rise_to [get_clocks {cpu_clk}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {cpu_clk}] -fall_to [get_clocks {cpu_clk}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {altera_reserved_tck}] -rise_to [get_clocks {altera_reserved_tck}]  0.020  
set_clock_uncertainty -rise_from [get_clocks {altera_reserved_tck}] -fall_to [get_clocks {altera_reserved_tck}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {altera_reserved_tck}] -rise_to [get_clocks {altera_reserved_tck}]  0.020  
set_clock_uncertainty -fall_from [get_clocks {altera_reserved_tck}] -fall_to [get_clocks {altera_reserved_tck}]  0.020  


#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************

set_clock_groups -asynchronous -group [get_clocks {altera_reserved_tck}] 
set_clock_groups -asynchronous -group [get_clocks {altera_reserved_tck}] 
set_clock_groups -asynchronous -group [get_clocks {altera_reserved_tck}] 


#**************************************************************
# Set False Path
#**************************************************************



#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

