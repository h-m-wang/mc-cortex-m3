//////////////////////////////////////////////////////////////////////////    
// Copyright (c)2017 ALTA Incorporated                                     //    
// All Rights Reserved                                                     //    
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of ALTA Inc.                //    
// The copyright notice above does not evidence any actual or intended     //    
// publication of such source code.                                        //    
// No part of this code may be reproduced, stored in a retrieval system,   //    
// or transmitted, in any form or by any means, electronic, mechanical,    //    
// photocopying, recording, or otherwise, without the prior written        //    
// permission of ALTA                                                      //    
/////////////////////////////////////////////////////////////////////////////    
/////////////////////////////////////////////////////////////////////////////    
// Name of module : ahb2ram                                                //    
// Func           : ahb interface                                          //    
// Author         : yinliang                                               //    
// Simulator      : Ncverilog/LINUX64                                      //    
// Synthesizer    : DC_2010 /LINUX64                                       //     
// version 1.0    : made in Date: 2017.05.23                               //    
/////////////////////////////////////////////////////////////////////////////    


module ahb2ram (
// AHB bus     
input   wire            hclk                ,
input   wire            hresetn             ,
input   wire [31:0]     hwdata              , 
input   wire [31:0]     haddr               , 
input   wire            hwrite              ,// 1 - Write, 0 - Read
input   wire [2:0]      hsize               ,
input   wire            hsel                ,  
input   wire [1:0]      htrans              , 
output  reg  [31:0]     hrdata              , 
output  reg             hready_out          ,

output	reg	[11:0]	usr_address         ,    
input   	wire           usr_clk             ,
input   	wire 	[31:0]   usr_data_in         ,
output	reg	         usr_wren            ,
output   wire 	[31:0]   usr_data_out   
); 
                              
//----------------------------------------------------
// Wire Decleration
// ---------------------------------------------------

reg     [11:0]          ram_addr            ;
reg                     ram_wren            ;
reg                     rd_en_d1            ;
reg                     rd_en_d2            ;
reg                     rd_en_d3            ;
wire    [31:0]          wm_ram_dout         ;
reg     [3:0]           byteena             ;



// ______________ MCU Domain to SDRAM Domain ______________  
ram_two_port u1_ram_two_port (
    // Port A -- AHB Slave MCU Port
    .address_a              (ram_addr           ),
    .byteena_a              (byteena            ),
    .clock_a                (hclk               ),
    .data_a                 (hwdata             ),
    .wren_a                 (ram_wren           ),
    .q_a                    (wm_ram_dout        ),
    
    // Port B -- User Access Port
    .address_b              (usr_address        ), 
    .clock_b                (usr_clk            ),   
    .data_b                 (usr_data_in        ),
    .wren_b                 (usr_wren           ),   
    .q_b                    (usr_data_out       )
    );  
  
// ____________________ Port A AHB Control ______________________
always@(posedge hclk or negedge hresetn)
    begin
        if(!hresetn)
            byteena <= 4'b1111;
        else if(hsel && htrans[1] && hwrite)
            begin
                if(hsize == 3'b000)//byte write  	        	
                    begin
                        case(haddr[1:0])
                            2'b00:	byteena <= 4'b0001;
				            2'b01:	byteena <= 4'b0010;
				            2'b10:	byteena <= 4'b0100;
				            2'b11:	byteena <= 4'b1000;
				            default:byteena <= 4'hX;
			            endcase
			        end
                else if(hsize == 3'b001)  //Halfword write             
                    begin
				        case (haddr[1])             
				            1'b0:	byteena <= 4'b0011;        
				            1'b1:	byteena <= 4'b1100;        
				            default:byteena <= 4'hX;      
				        endcase 
				    end
				else  //Word (including above) write
				        byteena <= 4'b1111;
            end   
    end				    
				            	                       
always@(posedge hclk or negedge hresetn)
    begin
        if(!hresetn)
            ram_wren <= 0;
        else if(hsel && htrans[1] && hwrite)
            ram_wren <= 1;
        else
            ram_wren <= 0;
    end
	 
	 

always@(posedge hclk or negedge hresetn)
    begin
        if(!hresetn)
            ram_addr <= 0;
        else if(hsel == 1'b1)
            ram_addr <= haddr[12:2];
    end

wire rd_en = hsel & htrans[1] & !hwrite && hready_out;

always@(posedge hclk or negedge hresetn)       
    begin                                      
        if(!hresetn)
            begin
                rd_en_d1 <= 0;                          
                rd_en_d2 <= 0;
                rd_en_d3 <= 0;
            end
        else
            begin
                rd_en_d1 <= rd_en;
                rd_en_d2 <= rd_en_d1;
                rd_en_d3 <= rd_en_d2;
            end
    end

always@(posedge hclk or negedge hresetn)
    begin
        if(!hresetn)
            hready_out <= 1;
        else if(rd_en && !rd_en_d1)
            hready_out <= 0; 
        else if(rd_en_d2 && !rd_en_d3)
            hready_out <= 1;
    end           

always@(posedge hclk or negedge hresetn)        
    begin                                       
        if(!hresetn) 
            hrdata <= 0;
        else if(rd_en_d2)                          
            hrdata <= wm_ram_dout ;
     end
// ______________________________________________________

// ____________________ Port B User RAM Interface __________________  

// _______________MCU AHB Slave Clock Domain to BRAM Clock Domain_____________
reg	[11:0]	usr_address_tmp1;
always@(posedge usr_clk or negedge hresetn)        
begin                                       
   if(!hresetn)
	begin
		usr_address_tmp1 	<= 12'b0 ;
	   usr_address			<=	12'b0	;
	end
	else
	begin                   
     usr_address_tmp1 	<= ram_addr 			;
	  usr_address			<=	usr_address_tmp1	;
	end
end

reg				usr_wren_tmp1;
always@(posedge usr_clk or negedge hresetn)        
begin                                       
   if(!hresetn)
	begin
		usr_wren_tmp1 	<= 1'b0 ;
	   usr_wren			<=	1'b0	;
	end
	else
	begin                   
     usr_wren_tmp1 	<= ram_addr 			;
	  usr_wren			<=	~usr_wren_tmp1	;
	end
end

   
     
endmodule
