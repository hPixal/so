import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.cm as cm
import random

# PROCESS SIZE_PR START DURATION
# A         20KB    1       2
# B         40KB    1       5
# C         35KB    1       3
# D         25KB    2       5
# E         15KB    4       3
# F         35KB    5       2

# Algorithm: FIFO + Best Fit
# INPUT: list of allocations: (time_step, process_id, start_kb, size_kb)
allocations = [
    (0, "SO", 0, 10),
    (1, "SO", 0, 10), (1, "A", 10, 20), (1, "B", 30, 40), (1, "C", 70, 35),
    (2, "SO", 0, 10), (2, "A", 10, 20), (2, "B", 30, 40), (2, "C", 70, 35), 
    (3, "SO", 0, 10),                   (3, "B", 30, 40), (3, "C", 70, 35),
    (4, "SO", 0, 10), (4, "E", 10, 15), (4, "B", 30, 40), (4, "D", 70, 25),
    (5, "SO", 0, 10), (5, "E", 10, 15), (5, "B", 30, 40), (5, "D", 70, 25),
    (6, "SO", 0, 10), (6, "E", 10, 15), (6, "F", 25, 35), (6, "D", 70, 25),
    (7, "SO", 0, 10),                   (7, "F", 25, 35), (7, "D", 70, 25),
    (8, "SO", 0, 10),                                     (6, "D", 70, 25),
]

MEMORY_SIZE = 128  # in KB
TIME_STEPS = max([t for t, *_ in allocations]) + 1

# Assign a unique color to each process
process_ids = list(set([pid for _, pid, _, _ in allocations]))
color_map = cm.get_cmap('tab20', len(process_ids))
process_colors = {pid: color_map(i) for i, pid in enumerate(process_ids)}

# Create figure
fig, ax = plt.subplots(figsize=(1.5 * TIME_STEPS, 10))

# Draw rectangles for each allocation
for time, pid, start, size in allocations:
    rect = patches.Rectangle(
        (time, start),  # (x, y)
        1,              # width = 1 time unit
        size,           # height = size in KB
        linewidth=1,
        edgecolor='black',
        facecolor=process_colors[pid],
    )
    ax.add_patch(rect)
    ax.text(time + 0.5, start + size / 2, f"{pid}\n{size}KB",
            ha='center', va='center', fontsize=8, color='black')

# Set axis limits
ax.set_xlim(0, TIME_STEPS)
ax.set_ylim(0, MEMORY_SIZE)

# Axis labels and ticks
ax.set_xticks(range(TIME_STEPS))
ax.set_yticks(range(0, MEMORY_SIZE + 1, 8))
ax.set_xlabel("Time (T)")
ax.set_ylabel("Memory (KB)")
ax.set_title("Memory Allocation Over Time")
ax.invert_yaxis()  # Optional: match your chart direction
ax.grid(True, which='both', linestyle='--', linewidth=0.5)

plt.tight_layout()
plt.show()
