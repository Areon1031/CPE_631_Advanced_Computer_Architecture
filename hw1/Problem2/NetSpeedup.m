% Kyle Ray
% CPE 631 Advanced Computer Architecture
% Problem 2
% January 29, 2018

clear;

F_enh = (0:0.0001:1);
S_enh = 10;

S_overall = zeros(1, length(F_enh));

for i = 1:length(F_enh)
    S_overall(i) = 1/((1-F_enh(i)) + (F_enh(i)/S_enh));
end

plot(F_enh.*100, S_overall, '-b', 'LineWidth', 2);
grid on;
xlabel('Percent Vectorization');
ylabel('Net Speedup');
title('Net Speedup vs. Percent Vectorization');