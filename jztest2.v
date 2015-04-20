// comment
module jztest2(a,b,c,d,y);
	input a;
	input b;
	input c;
	input d;

	output y;

	wire r;
	wire s;

	and i0(r,a,b);
	and i1(r,c,d);

	not i2(y,r);
endmodule
