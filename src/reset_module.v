
`timescale 1ns/10ps

module reset_module(
	input 		clkin,
	output 		init,
	output 		reset_n
);

reg [5:0] reset_init = 6'b0 /* synthesis syn_preserve = 1*/;
assign init = reset_init[5];

always @ (posedge clkin) begin
	if (!init) begin
		reset_init <= reset_init + 1'b1;
	end
end

assign reset_n = rst_n;
reg rst_n = 0;
always @(posedge clkin)
begin
	rst_n	<=	init; 
end

endmodule
