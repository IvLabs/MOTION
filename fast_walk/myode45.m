function dy = myode45(t,y)
L = 218.7032;               % height of COM from ankle. 
dy = zeros(2,1);
dy(1) = y(2);
dy(2) = -(9.8100*1000/(2*L))*sin(2*y(1));

