// comment
module mux21(a,b,  s,y);
   input a;
   input b;
   input s;
   output y;

   wire   t1;
   wire   t0;
   wire   s_n;  

   not i0(s_n, s); 
   
   and #2 i1(t0, s_n, a);
   and #2 i2(t1, s, b);
   or i3(y,t0,t1);    
endmodule