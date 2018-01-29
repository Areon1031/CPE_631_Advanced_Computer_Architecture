% Kyle Ray
% CPE 631 Advanced Computer Architecture
% Problem 5
% January 29, 2018

clear;
close all;
NUM_BCES = 64;


%% Symmetric
% f = [0.999 0.99 0.975 0.9 0.5];
f = [0.99 0.90];
r = 0:1:NUM_BCES;
perf = sqrt(r);
% perf = ones(1, length(r));
% perf = (r.^(2/3));

figure(1);

for k = 1:length(f)
    for i = 1:length(r)
        term1 = (1-f(k))/perf(i);
        term2 = (f(k)*r(i))/(perf(i)*max(r));
        S_sym(i) = 1/(term1 + term2);
    end
    plot(r(2:end), S_sym(2:end));
    hold on;
end
grid on;
title('Symmetric');
xlabel('rBCEs');
ylabel('Speedup_s_y_m_m_e_t_r_i_c');
legend('f1 = 0.99', 'f2 = 0.90');

hold off;


%% Asymmetric
figure(2);

for k = 1:length(f)
    for i = 1:length(r)
        term1 = (1-f(k))/perf(i);
        term2 = (f(k))/(perf(i) + max(r) - r(i));
        S_asym(i) = 1/(term1 + term2);
    end
    plot(r(2:end), S_asym(2:end));
    hold on;
end
grid on;
title('Asymmetric');
xlabel('rBCEs');
ylabel('Speedup_a_s_y_m_m_e_t_r_i_c');
legend('f1 = 0.99', 'f2 = 0.90');

hold off;

%% Dynamic
figure(3);

for k = 1:length(f)
    for i = 1:length(r)
        term1 = (1-f(k))/perf(i);
        term2 = (f(k))/(max(r));
        S_dyn(i) = 1/(term1 + term2);
    end
    plot(r(2:end), S_dyn(2:end));
    hold on;
end
grid on;
title('Dynamic');
xlabel('rBCEs');
ylabel('Speedup_d_y_n_a_m_i_c');
legend('f1 = 0.99', 'f2 = 0.90');
