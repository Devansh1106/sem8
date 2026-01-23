# FEM 1D code
# - u'' = f in (0,1)
# u(0) = 0 = u(1)
# u_x = x^2*(1-x)^2;


using LinearAlgebra, Plots

N = 10
x = LinRange(0, 1, N+2)
xfine = LinRange(0, 1, 100)
h = x[2] - x[1]
Elem = zeros(Int64, (N+1,2))

function u_exact(x)
    return (x^2) * (1-x)^2
end

function f(x)
    return -12*(x^2) + 12*x - 2 
end

for i in 1:N+1
    Elem[i, :] = [i; i+1]
end

A = zeros(N+2, N+2)
B = zeros(N+2, 1)
uh = zeros(N+2)

for i in 1:N+1
    A[Elem[i,:], Elem[i,:]] += [1/h -1/h; -1/h 1/h]
    midpt = (x[i] + x[i+1])/2
    B[Elem[i,:], 1] += (h/2)*[f(midpt); f(midpt)]
    
end
uh[2:N+1] = A[2:N+1, 2:N+1]\B[2:N+1,1]
p1 = plot(x, uh)
plot!(p1, xfine, u_exact.(xfine))