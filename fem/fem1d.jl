# FEM 1D code
# - u'' = f in (0,1)
# u(0) = 0 = u(1)
# u_x = x^2*(1-x)^2;


using LinearAlgebra, Plots


function u_exact(x)
    return (x^2) * (1-x)^2
end

function u_exact_deriv(x)
    return 4*(x^3) - 6*(x^2) + 2*x
end

function f(x)
    return -12*(x^2) + 12*x - 2 
end

function err_L2(uh, x, N)
    _err = 0.0
    h = x[2] - x[1]
    for i in 1:N+1
        e_i = u_exact(x[i]) - uh[i]
        e_i1 = u_exact(x[i+1]) - uh[i+1]
        mid_pt = (x[i] + x[i+1])/2
        uh_mid = (uh[i] + uh[i+1])/2
        _err += (h/6)*(e_i^2 + 4(uh_mid - u_exact(mid_pt))^2 + e_i1^2)
    end
    _err = sqrt(_err)
    return _err
end

function err_H1(uh, x, N)
    _err = 0.0
    h = x[2] - x[1]
    for i in 1:N+1
        uh_dashi = (uh[i+1] - uh[i])/h
        e_i = u_exact_deriv(x[i]) - uh_dashi
        # uh_dashi1 = (uh[i+2] - uh[i+1])/h
        e_i1 = u_exact_deriv(x[i+1]) - uh_dashi
        mid_pt = (x[i] + x[i+1])/2
        # uh_mid = (uh[i] + uh[i+1])/2
        _err += (h/6)*(e_i^2 + 4(uh_dashi - u_exact_deriv(mid_pt))^2 + e_i1^2)
    end
    _err = sqrt(_err)
    return _err
end

function fem1d(N, x)
    Elem = zeros(Int64, (N+1,2))
    for i in 1:N+1
        Elem[i, :] = [i; i+1]
    end
    h = x[2] - x[1]
    A = zeros(N+2, N+2)
    B = zeros(N+2, 1)
    uh = zeros(N+2)

    for i in 1:N+1
        A[Elem[i,:], Elem[i,:]] += [1/h -1/h; -1/h 1/h]
        midpt = (x[i] + x[i+1])/2
        B[Elem[i,:], 1] += (h/2)*[f(midpt); f(midpt)]
    end
    uh[2:N+1] = A[2:N+1, 2:N+1]\B[2:N+1,1]
    error_L2 = err_L2(uh, x, N);
    error_H1 = err_H1(uh, x, N);
    println("L2 error for $(N) points is : ", error_L2);
    println("H1 error for $(N) points is : ", error_H1);
    p1 = plot(x, uh)
    plot!(p1, xfine, u_exact.(xfine))
    return error_L2, error_H1
end

xfine = LinRange(0, 1, 100)
lvl = 5
_h = zeros(lvl)
vec_error_L2 = zeros(length(lvl))
vec_error_H1 = zeros(length(lvl))

for i in 1:lvl
    N = 10
    x = LinRange(0, 1, (i*N)+2)
    _h[i] = x[2] - x[1]
    a, b = fem1d(i*N, x)
    push!(vec_error_L2, a);
    push!(vec_error_H1, b);
end
p = log(vec_error_L2[end]/vec_error_L2[end-1])/log(_h[end]/_h[end-1])
q = log(vec_error_H1[end]/vec_error_H1[end-1])/log(_h[end]/_h[end-1])

println("Convergence order L2: ", p)
println("Convergence order H1: ", q)