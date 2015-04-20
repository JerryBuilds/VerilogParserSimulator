module jztest3(a,b,c,y);
	input a;
	input b;
	input c;
	output y;

	wire r;

	and i0(r,a,b);
	and i1(y,r,c);
endmodule
