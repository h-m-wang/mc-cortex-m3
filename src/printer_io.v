module printer_io #(parameter WIDTH = 32)
(
	input 								clkin,
	input 								rst_n,
	input 	[WIDTH - 1 : 0]		io_input,
	output 	[WIDTH - 1 : 0] 		io_output
);

reg 	[WIDTH - 1 : 0] 	io_reg;

assign io_output = io_reg;

always @ (posedge clkin or negedge rst_n) begin
	if (!rst_n) begin
		io_reg <= 0;
	end
	else begin
		io_reg <= io_input;
	end
end

endmodule
