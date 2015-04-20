// comment
module jztest(a,b,u,v,w,x,y,z);
	input a;
	input b;

	output u;
	output v;
	output w;
	output x;
	output y;
	output z;

	and i1(a,b,u);
	or i2(a,b,v);
	nand i3(a,b,w);
	nor i4(a,b,x);
	not i5(a,y);
	xor i6(a,b,z);
endmodule
