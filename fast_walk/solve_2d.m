% Last Edited 13/05/2016
% Editor: Sapan Agrawal
% Takes ref to myode45 and takes COM height.
% Gives Output: theta max  
% Initial pos is taken at mistance phase: theta = 0; velocity = max = 1;
L = 218.7032;% Com= -144.55 mm ; Ankle = -338.7 mm = 194.15mm
g=9800;
T=2*pi*sqrt(L/g);
time_period = [0 T];
initial = [0  1];             
[t, y] = ode45(@myode45, time_period, initial);
plot(t,y(:,1))
T=2*pi*sqrt(L/g);
max_angle= max(y(:,1));            
Stride_time =T;        %total time period of pendulum
Step_time = Stride_time/2;                     %Time period of supporting phase 
step_len = 2*L*tan(max_angle);
Stride_len = 2*step_len;
DSP_ratio = 0.1
DSP_time = Step_time*DSP_ratio;
SSP_time = Step_time*(1-DSP_ratio);
%% Inferences
% max_ankle_pitch is directly proportional to L
% Stride_Time is directly proportional to L
% Step_len is directly proportional to L