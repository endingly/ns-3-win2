clear all;
close all;

%% LTE pathloss model
%% ITU1411, ITU1238, COST231, OH, etc.

%f = 2114e6;  % carrier freq Hz, EARFCN = 500 (downlink)
%f = 1900e6;  % carrier freq Hz, EARFCN = 500 (downlink)
f = 869e6;
%f = 2620e6;
d = 2000;
hb = 30;
hm = 1;
hr = 20;
fmhz = f/1e6;

g = loss_OH_large_cities_urban (d, hb, hm, fmhz);
disp ("The value of OH for large cities is:"), disp (g)

g = loss_OH_small_cities_urban (d, hb, hm, fmhz);
disp ("The value of OH for small cities is:"), disp (g)

g = loss_OH_suburban (d, hb, hm, fmhz);
disp ("The value of OH in suburban is:"), disp (g)

g = loss_OH_openareas (d, hb, hm, fmhz);
disp ("The value of OH in openareas is:"), disp (g)

fmhz = 2114;
g = loss_COST231_large_cities_urban (d, hb, hm, fmhz);
disp ("The value of COST231 for large cities is:"), disp (g)

g = loss_COST231_small_cities_urban (d, hb, hm, fmhz);
disp ("The value of COST231 for small cities is:"), disp (g)

g = loss_OH_2_6GHz (d);
disp ("The value of OH at 2.6 GHz is:"), disp (g)

d = 100;
f = 2114e6;
g = loss_ITU1411_LOS (d, hb, hm, hr, f);
disp ("The value of ITU1411 in LOS is:"), disp (g)

d = 900;
l = 80;
b = 50;
st_w = 20;
phi = 45;
big = 1; % metropolitan centre
g = loss_ITU1411_NLOS_over_rooftop (d, hb, hm, hr, f, l, b, st_w, phi, big);
disp ("The value of ITU1411 in NLOS over the roof-top is:"), disp (g)

n_floors = 2;
built_t = 1;
d = 31.3209;
g = loss_ITU1238 (d, fmhz, n_floors, built_t);
disp ("The value of ITU1238 is:"), disp (g)


%%snr = txPsd + g - kT - nf ; % dB

      


