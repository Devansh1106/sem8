# PART A
using LinearAlgebra

function f(x)
    return exp(-x^2)    
end

function mid_point(a, b, f, n)
    _h = (b-a) / n
    x = LinRange(a, b, n+1)
    sum = 0.0
    for i in 1:n
        sum += f((x[i]+x[i+1])/2) * _h
    end
    return sum
end

function simpsons(a, b, f, n)
    _h = (b-a) / n
    x = LinRange(a, b, n+1)
    sum = 0.0
    for i in 1:n
        sum += (_h/6)*(f(x[i]) + 4*f((x[i]+x[i+1])/2) + f(x[i+1]))
    end
    return sum
end

n = [10, 100, 1000, 10000]
a = 0.0; b = 3.0
h = zeros(length(n))
h .= (b-a) ./ n
# h = [0.3, 0.03, 0.003, 0.0003]

val_midpt = zeros(length(n))
val_simpson = zeros(length(n))
exact_val = zeros(length(n))
error_midpt = zeros(length(n))
error_simpson = zeros(length(n))

for i in eachindex(n)
    val_midpt[i] = mid_point(a, b, f, n[i])
    val_simpson[i] = simpsons(a, b, f, n[i])
end

exact_val .= 0.8862073482595212
error_midpt .=  abs.(exact_val .- val_midpt)
error_simpson .=  abs.(exact_val .- val_simpson)
println("Errors for mid-point rule: ", error_midpt)
println("Errors for mid-point rule: ", error_simpson)

# PART B
p = log(error_midpt[end-1]/error_midpt[end])/log(h[end-1]/h[end])
println("Order of convergence for mid-point rule: ", p)

p = log(error_simpson[1]/error_simpson[2])/log(h[1]/h[2])
println("Order of convergence for Simpsons rule: ", p)

# PART C
#= **COMPARISON OF ORDER OF CONVERGENCE OF BOTH RULES**
Mid-Point rule: Theoretical CO: 2   Obtained CO: 2.001049740357635
Simpsons rule: Theoretical CO: 4   Obtained CO: 3.9755381194263
Convergence rate of the code is approaching the theoretical values.
=#