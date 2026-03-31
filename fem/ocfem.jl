# ==============================================================================
# 2D Finite Element Method (FEM) for:
# - div(grad u) + u = f  in \Omega
#     grad(u) . n = u_N  on \partial\Omega_N
#               u = g    on \partial\Omega_D
# ==============================================================================

using LinearAlgebra
using SparseArrays
# using Plots
using PyPlot

# --- Exact Solution and Problem Definitions ---

function ue(z)
    x, y = z[1], z[2]
    return exp(x + y)
end

function f(z)
    x, y = z[1], z[2]
    return -exp(x + y)
end

function uxe(z)
    x, y = z[1], z[2]
    return exp(x + y), exp(x + y)
end

function u_N_func(P1, P2)
    # Normal vector components
    n_vec = [-(P2[2] - P1[2]), P2[1] - P1[1]]
    n_vec = -n_vec / norm(P2 - P1)
    
    MP = (P1 + P2) / 2.0
    ux, uy = uxe(MP)
    return ux * n_vec[1] + uy * n_vec[2]
end

# --- Mesh Generation and Refinement ---

function InitialMesh(N)
    if N == 1
        # Square Mesh
        Coord = [0.0 0.0; 1.0 0.0; 0.0 1.0; 1.0 1.0; 0.5 0.5]
        Elem = [1 2 5; 1 5 3; 3 5 4; 5 2 4]
        Db = [1 2; 2 4]
        Nb = [4 3; 3 1]
    elseif N == 2
        # Diamond Mesh
        Coord = [1.0 0.0; 0.0 1.0; -1.0 0.0; 0.0 -1.0]
        Elem = [1 2 3; 3 4 1]
        Db = [1 2; 2 3]
        Nb = [3 4; 4 1]
    else
        error("InitialMesh only supports N=1 or N=2")
    end
    return Coord, Elem, Nb, Db
end

function get_edges(element, coordinate)
    n_coord = size(coordinate, 1)
    n_elem = size(element, 1)
    
    nodes2element = spzeros(Int, n_coord, n_coord)
    for j in 1:n_elem
        for k in 1:3
            n1 = element[j, k]
            n2 = element[j, mod1(k+1, 3)]
            nodes2element[n1, n2] += j
        end
    end
    
    B = nodes2element + nodes2element'
    I, J, V = findnz(B)
    
    # Filter upper triangular part equivalent
    idx = findall(I .<= J)
    i_idx = I[idx]
    j_idx = J[idx]
    
    n_edges = length(i_idx)
    nodes2edge = sparse(i_idx, j_idx, 1:n_edges, n_coord, n_coord)
    nodes2edge = nodes2edge + nodes2edge'
    
    edge2element = zeros(Int, n_edges, 4)
    for m in 1:n_elem
        for k in 1:3
            n1 = element[m, k]
            n2 = element[m, mod1(k+1, 3)]
            p = nodes2edge[n1, n2]
            if edge2element[p, 1] == 0
                edge2element[p, 1] = n1
                edge2element[p, 2] = n2
                edge2element[p, 3] = nodes2element[n1, n2]
                edge2element[p, 4] = nodes2element[n2, n1]
            end
        end
    end
    
    return nodes2edge, edge2element
end

function redrefine(Coord, Elem, n2ed, ed2el, Db, Nb)
    nt = size(Elem, 1)
    ne = size(ed2el, 1)
    marker = zeros(Int, ne)
    
    new_nodes = size(Coord, 1)
    nCoord_list = Vector{Vector{Float64}}()
    
    # Create new nodes at edge midpoints
    for i in 1:ne
        inode = ed2el[i, 1]
        enode = ed2el[i, 2]
        coord1 = Coord[inode, :]
        coord2 = Coord[enode, :]
        nCoord = (coord1 + coord2) / 2.0
        new_nodes += 1
        marker[i] = new_nodes
        push!(nCoord_list, nCoord)
    end
    
    if !isempty(nCoord_list)
        Coord = vcat(Coord, hcat(nCoord_list...)')
    end
    
    # Subdivide elements
    new_Elem = zeros(Int, nt * 4, 3)
    for i in 1:nt
        ct = Elem[i, :]
        ce = [n2ed[ct[2], ct[3]], n2ed[ct[3], ct[1]], n2ed[ct[1], ct[2]]]
        m1 = marker[ce[1]]; m2 = marker[ce[2]]; m3 = marker[ce[3]]
        
        idx = (i - 1) * 4
        new_Elem[idx+1, :] = [m1, m2, m3]
        new_Elem[idx+2, :] = [ct[1], m3, m2]
        new_Elem[idx+3, :] = [ct[2], m1, m3]
        new_Elem[idx+4, :] = [ct[3], m2, m1]
    end
    Elem = new_Elem
    
    # Update Dirichlet Boundaries
    if !isempty(Db)
        nb = size(Db, 1)
        new_Db = zeros(Int, nb * 2, 2)
        count = 1
        for i in 1:nb
            base = n2ed[Db[i, 1], Db[i, 2]]
            if marker[base] > 0
                m = marker[base]
                new_Db[count, :] = [Db[i, 1], m]
                new_Db[count+1, :] = [m, Db[i, 2]]
                count += 2
            end
        end
        Db = new_Db[1:count-1, :]
    end
    
    # Update Neumann Boundaries
    if !isempty(Nb)
        nb = size(Nb, 1)
        new_Nb = zeros(Int, nb * 2, 2)
        count = 1
        for i in 1:nb
            base = n2ed[Nb[i, 1], Nb[i, 2]]
            if marker[base] > 0
                m = marker[base]
                new_Nb[count, :] = [Nb[i, 1], m]
                new_Nb[count+1, :] = [m, Nb[i, 2]]
                count += 2
            end
        end
        Nb = new_Nb[1:count-1, :]
    end
    
    return Coord, Elem, Db, Nb
end

# --- Core FEM Solvers and Error Tracking ---

function stima(vertices)
    MatT = vcat(ones(1, 3), vertices')'
    mk = 0.5 * abs(det(MatT'))
    
    L1 = MatT \ [1.0, 0.0, 0.0]
    L2 = MatT \ [0.0, 1.0, 0.0]
    L3 = MatT \ [0.0, 0.0, 1.0]
    
    M = mk * [
        L1[2]*L1[2]+L1[3]*L1[3]  L1[2]*L2[2]+L1[3]*L2[3]  L1[2]*L3[2]+L1[3]*L3[3];
        L2[2]*L1[2]+L2[3]*L1[3]  L2[2]*L2[2]+L2[3]*L2[3]  L2[2]*L3[2]+L2[3]*L3[3];
        L3[2]*L1[2]+L3[3]*L1[3]  L3[2]*L2[2]+L3[3]*L2[3]  L3[2]*L3[2]+L3[3]*L3[3]
    ]
       
    N_mat = mk * [1/6 1/12 1/12; 1/12 1/6 1/12; 1/12 1/12 1/6]
    return M + N_mat
end

function Err(Coord, Elem, uh, u)
    L2e = 0.0
    H1e = 0.0
    
    for j in 1:size(Elem, 1)
        curnodes = Elem[j, :]
        curcoords = Coord[curnodes, :]
        Cuh = uh[curnodes]
        Cu = u[curnodes]
        
        P1 = curcoords[1, :]; P2 = curcoords[2, :]; P3 = curcoords[3, :]
        mp12 = 0.5 * (P1 + P2); mp13 = 0.5 * (P1 + P3); mp23 = 0.5 * (P3 + P2)
        cg = (P1 + P2 + P3) / 3.0
        
        uhmp12 = 0.5 * (Cuh[1] + Cuh[2]); uhmp13 = 0.5 * (Cuh[1] + Cuh[3])
        uhmp23 = 0.5 * (Cuh[3] + Cuh[2]); uhcg = (Cuh[1] + Cuh[2] + Cuh[3]) / 3.0
        
        MatT = vcat(ones(1, 3), curcoords')'
        mk = 0.5 * abs(det(MatT'))
        
        L2e += mk / 60.0 * (
            8 * (ue(mp12) - uhmp12)^2 + 8 * (ue(mp13) - uhmp13)^2 + 8 * (ue(mp23) - uhmp23)^2 +
            3 * (Cu[1] - Cuh[1])^2 + 3 * (Cu[2] - Cuh[2])^2 + 3 * (Cu[3] - Cuh[3])^2 + 
            27 * (ue(cg) - uhcg)^2
        )
        
        L1 = MatT \ [1.0, 0.0, 0.0]
        L2 = MatT \ [0.0, 1.0, 0.0]
        L3 = MatT \ [0.0, 0.0, 1.0]
        
        uxh = Cuh[1]*L1[2] + Cuh[2]*L2[2] + Cuh[3]*L3[2]
        uyh = Cuh[1]*L1[3] + Cuh[2]*L2[3] + Cuh[3]*L3[3]
       
        uxev, uyev = uxe(cg)
        
        H1e += mk * (uxev - uxh)^2 + mk * (uyev - uyh)^2
    end
    
    return sqrt(L2e), sqrt(H1e)
end

# function show_solution(Coord, uh, u_exact)
#     x = Coord[:, 1]; y = Coord[:, 2]
    
#     # We use scatter plots as a basic surrogate for trisurf. 
#     # For a true triangulated surface, GLMakie's `mesh` is recommended.
#     p1 = scatter(x, y, zcolor=uh, m=(:heat, 0.8), markersize=5, 
#                  title="Computed Solution (uh)", label="", aspect_ratio=:equal)
                 
#     p2 = scatter(x, y, zcolor=u_exact, m=(:heat, 0.8), markersize=5, 
#                  title="Exact Solution (u)", label="", aspect_ratio=:equal)
                 
#     display(plot(p1, p2, layout=(1, 2), size=(900, 400)))
# end

function show_solution(Coord, Elem, uh, u_exact)
    x = Coord[:, 1]
    y = Coord[:, 2]
    
    # Convert Julia's 1-based indexing to Python's 0-based indexing for the triangles
    triangles = Elem .- 1

    # Create a figure with a specific size
    figure(figsize=(12, 5))
    
    # Subplot 1: Computed Solution
    ax1 = subplot(1, 2, 1, projection="3d")
    surf1 = ax1.plot_trisurf(x, y, triangles, uh, cmap="jet", edgecolor="none")
    ax1.set_title("Computed Solution (uh)")
    ax1.set_zlabel("u")
    
    # Subplot 2: Exact Solution
    ax2 = subplot(1, 2, 2, projection="3d")
    surf2 = ax2.plot_trisurf(x, y, triangles, u_exact, cmap="jet", edgecolor="none")
    ax2.set_title("Exact Solution (u)")
    ax2.set_zlabel("u")
    
    tight_layout()
    show()
end

# --- Main Driver Function ---

function main()
    Coord, Elem, Nb, Db = InitialMesh(1)
    
    n_levels = 6
    h = zeros(n_levels)
    L2e_arr = zeros(n_levels)
    H1e_arr = zeros(n_levels)
    
    global final_uh, final_u_exact # to pass out for plotting
    
    for nl in 1:n_levels
        # Edge-Node Connections & Refinement
        n2ed, ed2el = get_edges(Elem, Coord)
        Coord, Elem, Db, Nb = redrefine(Coord, Elem, n2ed, ed2el, Db, Nb)
        
        # Calculate maximum mesh size element h
        h[nl] = sqrt(abs(det(vcat(ones(1, 3), Coord[Elem[1, :], :]'))) / 2.0)
        
        n_nodes = size(Coord, 1)
        FullNodes = 1:n_nodes
        Dbnodes = unique(Db)
        FreeNodes = setdiff(FullNodes, Dbnodes)
        
        A = spzeros(n_nodes, n_nodes)
        b = zeros(n_nodes)
        
        # Assembly of Global Stiffness Matrix (A)
        for j in 1:size(Elem, 1)
            nodes = Elem[j, :]
            A[nodes, nodes] .+= stima(Coord[nodes, :])
        end
        
        # Assembly of Load Vector (b)
        for j in 1:size(Elem, 1)
            nodes = Elem[j, :]
            coords = Coord[nodes, :]
            area_det = det(vcat(ones(1, 3), coords'))
            cg = vec(sum(coords, dims=1) / 3.0)
            b[nodes] .+= area_det * f(cg) / 6.0
        end
        
        # Apply Neumann Boundary Conditions
        if !isempty(Nb)
            for j in 1:size(Nb, 1)
                p1 = Coord[Nb[j, 1], :]
                p2 = Coord[Nb[j, 2], :]
                val = norm(p1 - p2) * u_N_func(p1, p2) / 2.0
                b[Nb[j, 1]] += val
                b[Nb[j, 2]] += val
            end
        end
        
        uh = zeros(n_nodes)
        
        # Apply Dirichlet Boundary Conditions
        if !isempty(Db)
            for j in 1:length(Dbnodes)
                node = Dbnodes[j]
                uh[node] = ue(Coord[node, :])
            end
        end
        
        b .-= A * uh
        
        # Solve the linear system
        uh[FreeNodes] = A[FreeNodes, FreeNodes] \ b[FreeNodes]
        
        # Exact solution at the nodes
        u_exact = [ue(Coord[i, :]) for i in 1:size(Coord, 1)]
        
        # Compute Errors
        l2, h1 = Err(Coord, Elem, uh, u_exact)
        L2e_arr[nl] = l2
        H1e_arr[nl] = h1
        
        if nl == n_levels
            final_uh = uh
            final_u_exact = u_exact
        end
    end
    
    # Print Convergence Rates
    println("Convergence Rates:")
    println("--------------------------------------------------")
    for ml in 1:(n_levels-1)
        ocl2 = log(L2e_arr[ml] / L2e_arr[ml+1]) / log(h[ml] / h[ml+1])
        och1 = log(H1e_arr[ml] / H1e_arr[ml+1]) / log(h[ml] / h[ml+1])
        println("Level $ml -> $(ml+1): L2 Order = $(round(ocl2, digits=4)), H1 Order = $(round(och1, digits=4))")
    end
    
    # Show Visualizations
    # show_solution(Coord, final_uh, final_u_exact)
    show_solution(Coord, Elem, final_uh, final_u_exact)
    readline() # Pause to view plots
end

# Run the simulation
main()