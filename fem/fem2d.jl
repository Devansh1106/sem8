# for triangulation: always anti-clock wise direction of elements in Elem vector.
# inside an element: Elem vector will have nodes in anti-clockwise direction

# FEM 2D code

using PyPlot, LinearAlgebra

# for square domain
coord = [0 0; 1 0; 1 1; 0 1; 0.5 0.5]
Elem = [1 2 5; 2 3 5; 3 4 5; 4 1 5]
DB = [1 2; 2 3; 3 4; 4 1] # edges (boundary data) 
triangles = Elem .- 1
# plt.triplot(coord[:, 1], coord[:, 2], triangles)
# plt.show()

# for L-shaped domain
# coord2 = [-1 -1; 0 -1; 0 0; 1 0; 1 1; 0 1; -1 1; -1 0; -0.5 -0.5; -0.5 0.5; 0.5 0.5]
# Elem2 = [1 2 9; 2 3 9; 3 8 9; 8 1 9; 8 3 10; 3 6 10; 6 7 10; 7 8 10; 3 4 11; 4 5 11; 5 6 11; 6 3 11]
# DB2 = [1 2; 2 3; 3 4; 4 1]
# triangles2 = Elem2 .- 1
# plt.triplot(coord2[:, 1], coord2[:, 2], triangles2)
# plt.show()

# coordinates of triangle 2
coordT2 = coord[Elem[2, :], :]

# list of edges of triangle 2
edgeT2 = [Elem[2,1] Elem[2,2]; Elem[2,2] Elem[2,3]; Elem[2,3] Elem[2,1]]

# length of edge between node 2 to 3
c = sqrt((coord[2, 1]-coord[2, 2])^2 + (coord[3, 1]-coord[3, 2])^2)

# area of the triangle
det_ = [1 1 1; transpose(coordT2)]
area_elem = 0.5*det(det_)

function f(cen)
    return exp(cen[1] + cen[2])
end

# Centroid of each triangle
area_total = 0.0
for i in 1:size(Elem, 1)
    coordTi = coord[Elem[i, :], :]
    a1 = sum(coordTi[:, 1])
    b1 = sum(coordTi[:, 2])
    centroid = [a1/3, b1/3]
    global area_total += area_elem*f(centroid)
    # println(centroid)
end
# println("Area is: $area_total")

# boundary nodes
boundary_nodes = unique(DB)
interior_nodes = setdiff(1:size(coord, 1), boundary_nodes)
println("Interior nodes are: $interior_nodes")
println("Boundary nodes are: $boundary_nodes")

# plotting the function
# uh = [1 1 1 1 2]
# plot_trisurf(coord[:, 1], coord[:, 2], triangles, vec(uh))
# show()

N = size(coord, 1)
num_elem = size(Elem, 1)
A = zeros(N, N)
B = [1 1 1; 1 1 1; 1 1 1]
# println(A[Elem[:, :], Elem[:, :]])
# println(B)
for i in 1:num_elem
    idx = Elem[i, :]
    A[idx, idx] += B
end
display(A)



# println(det_)
# println(area)


# println(c) 
# println(coordT2)
# println(edgeT2)