#=      -∇^2 y + y = f(x), x ∈ (0,1) with y'(0) = 0 = y'(1)
        Ans(a): Exact sol: cos(π*x); f(x) = (π^2 + 1)* cos(π*x)
=#

using LinearAlgebra, Plots
function f(x)
    return (π^2 + 1)* cos(π*x)
end

function u_exact(x)
    return cos(π*x)
end

function fem1d(N)
    x = LinRange(0, 1, N+2)
    xfine = LinRange(0, 1, 100)
    h = x[2] - x[1]
    Elem = zeros(Int64, (N+1,2))

    for i in 1:N+1
        Elem[i, :] = [i; i+1]
    end

    A = zeros(N+2, N+2)
    B = zeros(N+2, 1)
    uh = zeros(N+2)

    for i in 1:N+1
        A[Elem[i,:], Elem[i,:]] += [1/h -1/h; -1/h 1/h] + [h/3 h/6; h/6 h/3]
        midpt = (x[i] + x[i+1])/2
        B[Elem[i,:], 1] += (h/2)*[f(midpt); f(midpt)]
    end
    # uh[2:N+1] = A[2:N+1, 2:N+1]\B[2:N+1,1]
    uh = A\B
    error = 0.0
    for i in 1:N+1
        e_i = u_exact(x[i]) - uh[i]
        e_i1 = u_exact(x[i+1]) - uh[i+1]
        mid_pt = (x[i] + x[i+1])/2
        uh_mid = (uh[i] + uh[i+1])/2
        e_mid = uh_mid - u_exact(mid_pt) 
        error += (h/6)*(e_i^2 + 4*(e_mid^2) + e_i1^2)
    end
    error = sqrt(error)
    p1 = plot(x, uh, marker=:circle, label="FEM (N=$N)", title="1D FEM")
    plot!(p1, xfine, u_exact.(xfine), label="Exact Sol")
    xlabel!(p1, "x")
    ylabel!(p1, "u(x)")
    return p1, error
end

N = [4, 8, 16, 32]
errors = []
plt_list = []

for i in N
    p, error = fem1d(i)
    push!(plt_list, p)
    push!(errors, error)
end

h = zeros(length(N))
h .= 1 ./(N .+ 1)
p = log(errors[1]/errors[2])/log(h[1]/h[2])
println("Convergence order: ", p)
display(plot(plt_list..., layout=(2, 2), size=(750, 400)))
gui()
println("L_2 errors for each N: ", errors)
readline()