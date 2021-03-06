module top (

input       wire        			CLK				,
//input       wire        			RST_N				,

input       wire                 SWITCH         ,

// ____________ Configuration SPI Flash ____________
output      wire                	SPI1_SCK,		//FLASH_SCK       ,
output      wire                	SPI1_CS_N, 		//FLASH_CS_n      ,
output      wire                	SPI1_MOSI,		//FLASH_IO0_SI    ,
inout       wire                	SPI1_MISO,		//FLASH_IO1_SO    ,

//_____________ UART Interface _____________________
input 		wire 						UART0_RXD,
output 		wire 						UART0_TXD,

//_____________ SWD Debug Interface ________________
//input       wire				  		JTRST_N         ,			
input	      wire						JTCK      		,	// SDC
inout	      wire						JTMS 				,	// SDO
input	      wire						JTDI            ,
output      wire						JTDO            ,


//_____________ Key Board Interface ________________
input 		wire 	 [7:0] 			IO_KEYIN,
output 		wire 	 [7:0] 			IO_KEYOUT,

//______________ Misc Peripherals __________________
output 		wire 						BEEP,

//_____________ Printer IO Interface _______________
output 		wire 	 [31:0]			IO_PRINT
);

//__________________________ MCU Ports _______________________________

// AHB Slave Ports
wire                            ahb_response        ;
wire                            ahb_ready_out       ;
wire    [31:0]                  ahb_rdata           ;
wire    [1:0]                   ahb_trans           ;
wire    [31:0]                  ahb_addr            ;
wire                            ahb_write_en        ;	// write enable
wire                            ahb_sel             ;
wire    [31:0]                  ahb_wdata           ;
wire    [2:0]                   ahb_size            ;
wire                            ahb_ready_in        ;

// UART Interface
wire 									  UART_RXD;
wire 									  UART_TXD;


// GPIO Ports
wire    [7:0]                   GPIO0_O             ;
wire    [7:0]                   GPIO1_O             ;
wire    [7:0]                   GPIO2_O             ;
wire    [7:0]                   GPIO0_I             ;
wire    [7:0]                   GPIO1_I             ;
wire    [7:0]                   GPIO2_I             ;

// Flash Internal Ports
wire                            flash_io0_si_o      ;
wire                            flash_io1_so_o      ;
wire                            flash_io2_wpn_o     ;
wire                            flash_io3_holdn_o   ;
wire                            flash_si_oe         ;
wire                            flash_so_oe         ;
wire                            flash_wpn_oe        ;
wire                            flash_holdn_oe      ;

// User AHB RAM to SDRAM Interface
wire    [11:0]                  usr_address         /* synthesis keep = 1 */;
wire                            usr_clk             /* synthesis keep = 1 */;
wire    [31:0]                  usr_data_in         /* synthesis keep = 1 */;
wire                            usr_wren            /* synthesis keep = 1 */;
wire    [31:0]                  usr_data_out        /* synthesis keep = 1 */;

// remote_update
parameter        BOOT_ADDR             =  22'h10000                                ;
parameter        USR_DEFADDR_EN        =  1'b1                                     ;
parameter        USR_DEFADDR_DISEN     =  1'b0                                     ;



assign      SPI1_MOSI    =   (flash_si_oe 		== 1'b1)? flash_io0_si_o    :1'bz;
assign      SPI1_MISO    =   (flash_so_oe 		== 1'b1)? flash_io1_so_o    :1'bz;
assign      FLASH_IO2_WPN   =   (flash_wpn_oe 		== 1'b1)? flash_io2_wpn_o   :1'bz;
assign      FLASH_IO3_HOLDN =   (flash_holdn_oe 	== 1'b1)? flash_io3_holdn_o :1'bz;

assign 		UART_RXD 	= UART0_RXD;
assign 		UART0_TXD 	= UART_TXD;

// BEEP Control
assign 			BEEP = 0;

//SWD Interface
assign JTMS = SWDOEN ? SWDO : 1'bz;


// Heart Beat
reg [29:0] heart_cnt;
wire heart_beat;
always @ (posedge CLK or negedge reset_n) 
begin
  if (!reset_n)
    heart_cnt <= 1'b0;
  else
    heart_cnt <= heart_cnt + 1'b1;
end

assign heart_beat = heart_cnt[24];

wire reset_n, init;
reset_module rst_mod (
	.clkin(CLK),
	.init(init),
	.reset_n(reset_n)
);

wire mcu_clk, spi_clk, sdram_clk, clk_10M, clk_100M, locked;
//__________________ Clock Management _____________________
pll pll_inst (
  .inclk0(CLK),	// 50MHz
  .areset(!init),
  .c0(mcu_clk),	// 200MHz
  .c1(clk_100M),	// 100MHz
  .c2(sdram_clk),	// 125MHz
  .c3(spi_clk),	// 25MHz
  .c4(clk_10M), 	// 10MHz
  .locked(locked)
);

reg rst_sync1 = 1'b0, rst_sync2 = 1'b0, rst_sync3 = 1'b0;
always @ (posedge clk_100M or negedge init or negedge locked) begin
  if (!init) begin
    rst_sync1 <= 1'b0;
    rst_sync2 <= 1'b0;
    rst_sync3 <= 1'b0;
  end else if (!locked) begin
    rst_sync1 <= 1'b0;
    rst_sync2 <= 1'b0;
    rst_sync3 <= 1'b0;
  end else begin
    rst_sync1 <= 1'b1;
    rst_sync2 <= rst_sync1;
    rst_sync3 <= rst_sync2;
  end
end
//wire reset_n = rst_sync3;


//_____________________ MCU AHB Slave Ports to Block RAM ____________________________
ahb2ram u_ahb2ram(
        .hclk                           (mcu_clk                        ),
        .hresetn                        (reset_n                        ),
		  
        .hwdata                         (ahb_wdata                      ),
        .haddr                          (ahb_addr                       ),
        .hwrite                         (ahb_write_en                   ),
        .hsize                          (ahb_size                       ),
        .hsel                           (ahb_sel                        ),
        .htrans                         (ahb_trans                      ),
//		  .hready_in							 (ahb_ready_in							),
        .hrdata                         (ahb_rdata                      ),
        .hready_out                     (ahb_ready_out                  ),

		
       
        .usr_address                    (usr_address                    ), 
        .usr_clk                        (spi_clk                        ),      
        .usr_data_in                    (data_out                    ),  
        .usr_wren                       (usr_wren		                  ),    // write--1, read--0 
        .usr_data_out                   (usr_data_out                   )
        
);



// ________________________ remote update __________________________________
wire  busy                                   /* synthesis keep = 1 */;

reg   reconfig_d1                            ;
reg   reconfig_d2                            ;
reg   reconfig                               /* synthesis keep = 1 */;
reg   reconfig_lock                          ;
always @(posedge spi_clk or negedge reset_n)
begin
   if(!reset_n)
   begin
      reconfig_d1 <= 1'b0;
      reconfig_d2 <= 1'b0;
      reconfig    <= 1'b0;
   end
   else
   begin
      reconfig_d1 <= SWITCH;
      reconfig_d2 <= reconfig_d1;
      reconfig    <= reconfig_d1 & (!reconfig_d2);
   end
end


reg [3:0] reconfig_cnt;
always @(posedge spi_clk or negedge reset_n)
begin
   if(!reset_n)
      reconfig_cnt <= 4'b0;
   else if(reconfig_cnt[3] == 1'b1)
      reconfig_cnt <= reconfig_cnt;
   else if(reconfig)
      reconfig_cnt <= reconfig_cnt + 1'b1;
end



always @(posedge spi_clk or negedge reset_n)
begin
   if(!reset_n)
      reconfig_lock <= 1'b0;
   else if(!busy && reconfig_cnt[3])
      reconfig_lock <= 1'b1;
   else
      reconfig_lock <= reconfig_lock;
end



reg [2:0]     param                          /* synthesis keep = 1 */;
reg           write_param                    /* synthesis keep = 1 */;
reg           read_param                    /* synthesis keep = 1 */;
reg [21:0]    data_in                        /* synthesis keep = 1 */;
wire          w_write_param                  /* synthesis keep = 1 */;
wire          w_read_param                  /* synthesis keep = 1 */;
wire [21:0]    data_out                      /* synthesis keep = 1 */;
reg [1:0]      read_source                   /* synthesis keep = 1 */;
   
reg [3:0] counter ; 

reg write_param_d;
reg read_param_d; 


assign w_write_param = write_param && !write_param_d ;
assign w_read_param = read_param && !read_param_d ;

always@(posedge spi_clk or negedge reset_n)     
    begin                                     
        if(!reset_n)  
            counter <= 0;
        else if(counter == 4'b1110)
           counter <= counter;
        else if(w_write_param || w_read_param)
        	  counter <= counter + 1;
        
    end

always@(posedge spi_clk or negedge reset_n)     
    begin                                     
        if(!reset_n)  
           write_param_d <= 0;
        else
        	 write_param_d <= write_param ;
    end

    always@(posedge spi_clk or negedge reset_n)     
    begin                                     
        if(!reset_n)  
           read_param_d <= 0;
        else
        	 read_param_d <= read_param ;
    end

always@(posedge spi_clk or negedge reset_n) 
    begin                                 
        if(!reset_n)                      
            write_param <= 0;
        else if(!busy && counter < 4'b1000)
         	  write_param <= 1;
        else
         	  write_param <= 0;
    end

 always@(posedge spi_clk or negedge reset_n) 
    begin                                 
        if(!reset_n)                      
            read_source <= 2'b00;
        else if(counter >= 4'b1000)
         	  read_source <= 2'b11;
        else
         	  read_source <= 2'b00;
    end   
    
    
always@(posedge spi_clk or negedge reset_n) 
    begin                                 
        if(!reset_n)                      
            read_param <= 0;
        else if(!busy && (counter >= 4'b1000) && (counter < 4'b1110))
         	  read_param <= 1;
        else
         	  read_param <= 0;
    end

      

    
    
    
always@(posedge spi_clk or negedge reset_n)        
    begin                                        
        if(!reset_n)  
            begin
                param       <= 3'b0; 
                data_in     <= 22'b0;
            end
        else if((counter == 4'b0000) && w_write_param) 
            begin                    
                param       <= 3'b001;
                data_in     <= USR_DEFADDR_DISEN;//USR_DEFADDR_EN;
            end
        else if((counter == 4'b0001) && w_write_param) 
            begin                    
                param       <= 3'b100;
                data_in     <= 22'b0;
            end
           else if((counter == 4'b0010) && w_write_param) //vector[1]
            begin                    
                param       <= 3'b110;
                data_in     <= 22'b0;
            end
          else if((counter == 4'b0011) && w_write_param) //vector[0]
            begin                    
                param       <= 3'b011;
                data_in     <= BOOT_ADDR;
            end
        else if((counter == 4'b1000) && w_read_param) 
            begin                    
                param       <= 3'b001;
            end
        else if((counter == 4'b1001) && w_read_param) 
            begin                    
                param       <= 3'b100;
            end
     end
//        else if((counter == 4'b1001) && w_write_param)   //vector[1]                  
//            begin                                                      
//                param       <= 3'b110;            
//                data_in     <= 22'h01;         
//            end          
//        else if((counter == 4'b1010) && w_write_param)   //vector[0]                          
//            begin                                                                           
//                param       <= 3'b011;                         
//                data_in     <= 22'h00;                 
//            end 
//        else if((counter == 4'b1011) && w_write_param)   //FLASH BOOT ADDR                          
//            begin                                                                           
//                param       <= 3'b010 ;                         
//                data_in     <= 22'h386;                 
//            end        
            
//          // read param  
//        else if((counter == 4'b0001) && w_read_param)                         
//            begin                                                                           
//                param       <= 3'b001 ;                                      
//            end         
//        else if((counter == 4'b0010) && w_read_param)                         
//            begin                                                                           
//               param       <= 3'b110 ;                                    
//            end  
//        else if((counter == 4'b0011) && w_read_param)                         
//            begin                                                                           
//               param       <= 3'b011 ;                                        
//            end 
//        else if((counter == 4'b0011) && w_read_param)                         
//            begin                                                                           
//               param       <= 3'b100 ;                                        
//            end   
//        else if((counter == 4'b0100) && w_read_param)                         
//            begin                                                                           
//               param       <= 3'b010 ;                                        
//            end   
//        else
//            param       <= 3'b000; 
 //   end    	                                       


remote_reconf	remote_reconf_inst (
	.clock 				(spi_clk 			),
	.data_in 			(data_in    		),
	.param 				(param        		),
	.read_param 		(w_read_param  	            ),
	.read_source 		(read_source                 ),
	.reconfig 			(reconfig_lock        	),
	.reset 				(!reset_n 	   	),
	.reset_timer 		(                 ),
	.write_param 		(w_write_param      ),
	.busy 				(busy  		     	),
	.data_out 			(data_out	            	)
	);

//________________________________ MCU Module ______________________________________
alta_mcu_m3  #(
        .FLASH_BIAS(24'h60000),
        .CLK_FREQ  (8'h64    ),
        .BOOT_DELAY (1'b0   )
        )
mcu_inst (
        .CLK                           (mcu_clk                            ),
        .POR_n                         (reset_n                          ),
        .EXT_CPU_RST_n                 (1'b1                          ),
                            
        .JTRST_n                       (), //JTRST_N                        ),			
        .JTCK                          (JTCK                           ),
        .JTDI                          (JTDI                           ),
        .JTMS                          (JTMS                           ),
        .JTDO                          (JTDO                           ),
        
        .SWDO                          (SWDO                           ),
        .SWDOEN                        (SWDOEN                         ),
                    
        .UART_RXD             		   (UART_RXD                       ),
        .UART_CTS_n           		   (                               ),
        .UART_TXD             		   (UART_TXD                       ),
        .UART_RTS_n           		   (                               ),
                
        // On-Chip Memory Ports     
        .EXT_RAM_RDATA        		   (                               ),
        .EXT_RAM_EN           		   (1'b0                     ),
        .EXT_RAM_WR           		   (),//DIP                               ),
        .EXT_RAM_ADDR         		   (		  ),
        .EXT_RAM_BYTE_EN      		   (4'hf                           ),
        .EXT_RAM_WDATA        		   (                               ),
                
        // AHB Slave Ports	        
        .HRESP_EXT            		    (2'b00                   			),
        .HREADY_OUT_EXT       		    (ahb_ready_out                  ),
        .HRDATA_EXT           		    (ahb_rdata                      ),
        .HTRANS_EXT           		    (ahb_trans                      ),
        .HADDR_EXT            		    (ahb_addr                       ),
        .HWRITE_EXT           		    (ahb_write_en                   ),
        .HSEL_EXT             		    (ahb_sel                        ),
        .HWDATA_EXT           		    (ahb_wdata                      ),
        .HSIZE_EXT            		    (ahb_size                       ),
        .HREADY_IN_EXT        		    (ahb_ready_in                   ),
         
		  // AHB Master Ports
		  .HRESP_EXTM       					 (       ),
		  .HREADY_OUT_EXTM  					 (  ),
		  .HRDATA_EXTM      					 (      ),
		  .HTRANS_EXTM      					 (   ),
		  .HADDR_EXTM       					 (       ),
		  .HWRITE_EXTM      					 (      ),
		  .HSEL_EXTM        					 (       ),
		  .HWDATA_EXTM      					 (      ),
		  .HSIZE_EXTM       					 (       ),
		  .HREADY_IN_EXTM   					 ( ),
		  .HBURSTM          					 (          ),
		  .HPROTM           					 (         ),
  
            
        .FLASH_SCK            		    (SPI1_SCK                      ),
        .FLASH_CS_n           		    (SPI1_CS_N                     ),
        .FLASH_IO0_SI_i    			    (SPI1_MOSI                     ),
        .FLASH_IO1_SO_i    			    (SPI1_MISO                     ), 
                                    	
        .FLASH_IO0_SI      			    (flash_io0_si_o                 ),
        .FLASH_IO1_SO      			    (flash_io1_so_o                 ),
        .FLASH_IO2_WPn     			    (flash_io2_wpn_o                ),
        .FLASH_IO3_HOLDn   			    (flash_io3_holdn_o              ),
        .FLASH_IO2_WPn_i   			    (1'b1                           ),
        .FLASH_IO3_HOLDn_i 			    (1'b1                           ),	 
        .FLASH_SI_OE       			    (flash_si_oe                    ),
        .FLASH_SO_OE       			    (flash_so_oe                    ),
        .WPn_IO2_OE        			    (flash_wpn_oe                   ),
        .HOLDn_IO3_OE      			    (flash_holdn_oe                 ),
        		
            
        .GPIO0_I              		    (GPIO0_I                        ),
        .GPIO1_I              		    (GPIO1_I                        ),
        .GPIO2_I              		    (GPIO2_I                        ),
        .GPIO0_O              		    (GPIO0_O                        ),
        .GPIO1_O              		    (GPIO1_O                        ),
        .GPIO2_O              		    (GPIO2_O                        ),
        .nGPEN0               		    (                               ),
        .nGPEN1               		    (                               ),
        .nGPEN2               		    (                               )
) ;

wire 	[31:0] 	io_temp = { heart_beat, heart_cnt};

printer_io #(.WIDTH(32)) printer_io (
		.clkin(mcu_clk),
		.rst_n(reset_n),
		.io_input(io_temp),
		.io_output(IO_PRINT)
);

endmodule
