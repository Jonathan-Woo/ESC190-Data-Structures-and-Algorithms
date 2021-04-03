#finds the minimum energy seam in a list of lists using dynamic programming

energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,     15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]

#initialize energy_cost array
energy_cost = []
energy_cost.append(energies[0])

for row in range(1, len(energies)):
    energy_cost.append([0] * len(energies[0]))

#Skip the first row since the min cost of the first row is the first row
#itself
row = 0
for row in range(1, len(energies)):
    for col in range(len(energies[0])):
        cur_min_energy = 10000
        for options in range(-1, 2):
            if (col + options) < 0 or (col + options) > (len(energies[0]) - 1):
                continue
            elif (energy_cost[row - 1][col + options] + energies[row][col]) < cur_min_energy:
                cur_min_energy = energy_cost[row - 1][col + options] + energies[row][col]
        energy_cost[row][col] = cur_min_energy

print(energy_cost)

#here's the solution to the lowest total cost
sol_col = energy_cost[len(energies) - 1].index(min(energy_cost[len(energies) - 1]))
print("Minimum Energy Cost:", energy_cost[len(energies) - 1][sol_col])
                
#Now we have the minimum energy cost for each position
#build the minimum path by choosing the minimum adjacent energy cost at each level 
#the corresponding energies from the energies array is the solution
sol = []
cur_col = energy_cost[len(energies) - 1].index(min(energy_cost[len(energies) - 1]))
sol.append(energies[len(energies) - 1][cur_col])
for row in range(len(energies) - 2, -1, -1):
    cur_min_energy = 10000
    cur_min_col = -1
    for options in range(-1, 2):
        if (cur_col + options) < 0 or (cur_col + options) > (len(energies[0]) - 1):
            continue
        elif energy_cost[row][cur_col + options] < cur_min_energy:
            cur_min_energy = energy_cost[row][cur_col + options]
            cur_min_col = cur_col + options
    cur_col = cur_min_col
    sol.append(energies[row][cur_col])

print(sol)
        

