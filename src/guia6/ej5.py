import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.cm as cm
import random

# PROCESS SIZE_PR START DURATION
#   A       8KB     1       4
#   B       14KB    2       5
#   C       18KB    3       3
#   D       6KB     4       3
#   E       14KB    5       2

# Algorithm: FIFO + Best Fit
# INPUT: list of allocations: (time_step, process_id, start_kb, size_kb)
allocations = [
    (0, "SO", 0, 10),
    (1, "SO", 0, 10), (1, "A", 10, 8),
    (2, "SO", 0, 10), (2, "A", 10, 8), (2, "B", 18, 14),
    (3, "SO", 0, 10), (3, "A", 10, 8), (3, "B", 18, 14), (3, "C", 32, 18),
    (4, "SO", 0, 10), (4, "A", 10, 8), (4, "B", 18, 14), (4, "C", 32, 18), (4, "D", 50, 6),
    (5, "SO", 0, 10),                  (5, "B", 18, 14), (5, "C", 32, 18), (5, "D", 50, 6),
    (6, "SO", 0, 10),                  (6, "B", 18, 14), (6, "E", 32, 14), (6, "D", 50, 6),
    (7, "SO", 0, 10),                                    (7, "E", 32, 14),
    (8, "SO", 0, 10), 
]

MEMORY_SIZE = 64  # in KB
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
