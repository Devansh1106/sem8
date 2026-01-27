#=      -∇^2 y = f(x), x ∈ (0,1) with y(0) = 0 = y(1)
=#

using LinearAlgebra, Plots

function f1(x)
    if 0.4 <= x <= 0.6
        return -1.0
    else
        0.0
    end
end

function f2(x)
    if x == 0.5
        return -1.0
    else
        0.0
    end
end

function f3(x)
    if x == 0.6 || x == 0.4
        return -1.0
    else
        0.0
    end
end

function fem1d(N, f)
    x = LinRange(0, 1, N+2)
    h = x[2] - x[1]
    Elem = zeros(Int64, (N+1,2))

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
    p1 = plot(x, uh, marker=:circle, label="FEM (N=$N)", title="1D FEM")
    xlabel!(p1, "x")
    ylabel!(p1, "u(x)")
    return p1
end

N = [32]
plt_list = []

for i in N
    p= fem1d(i, f1)
    push!(plt_list, p)

    p= fem1d(i, f2)
    push!(plt_list, p)

    p= fem1d(i, f3)
    push!(plt_list, p)
end

h = zeros(length(N))
h .= 1 ./(N .+ 1)
plot(plt_list..., layout=(2, 2), size=(900, 600))
gui()
readline()
