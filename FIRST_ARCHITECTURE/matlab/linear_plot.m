frequency=100;
    t1=0:1/(frequency-1):1;
    t2=0:1/(frequency-1):2;
 for i=1:frequency
   angle1(i,1)=10*t1(1,i);
   angle2(i,1)=10;
   angle3(i,1)=10+10*t2(1,i);
 end
angle=[angle1;angle2;angle3];