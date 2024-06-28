import matplotlib.pyplot as plt
import numpy as np
import csv

puzzles = []
with open("./puzzles_res.csv") as f:
    csv_reader = csv.reader(f, delimiter=',')
    line_i = 0
    for row in csv_reader:
        if line_i == 0:
            line_i += 1
            continue
        puzzles.append(row)


puzzles = np.array(puzzles)
solutions = puzzles[0:, 1]
bfs = puzzles[0:, 2]
ash1 = puzzles[0:, 3]
ash2 = puzzles[0:, 4]

current = solutions[0]
num = 0
bfs_sum = 0
ash1_sum = 0
ash2_sum = 0
bfs_averages = []
ash1_averages = []
ash2_averages = []
solutions_simple = []
for i in range(0, len(solutions)):
    if current != solutions[i]:
        solutions_simple.append(current)
        bfs_averages.append(float(bfs_sum) / num)
        ash1_averages.append(float(ash1_sum) / num)
        ash2_averages.append(float(ash2_sum) / num)
        current = solutions[i]
        bfs_sum = 0
        ash1_sum = 0
        ash2_sum = 0
        num = 0

    num += 1
    bfs_sum += int(bfs[i])
    ash1_sum += int(ash1[i])
    ash2_sum += int(ash2[i])

solutions_simple.append(current)
bfs_averages.append(float(bfs_sum) / num)
ash1_averages.append(float(ash1_sum) / num)
ash2_averages.append(float(ash2_sum) / num)

bfs_averages = np.array(bfs_averages)
ash1_averages = np.array(ash1_averages)
ash2_averages = np.array(ash2_averages)

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

ax.plot(solutions_simple, bfs_averages, color='orange')
ax.plot(solutions_simple, ash1_averages, color='blue')
ax.plot(solutions_simple, ash2_averages, color='purple')
ax.legend(['BFS', 'A* H1', 'A* H2'])
ax.set_yscale('log')
fig.savefig('Sub7.pdf')
