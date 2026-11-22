#!/usr/bin/env python3
"""Charts for the report. Values are the measured counts printed by the programs
in Task02, Task05, Task06 and Task07 (copied from their output screenshots)."""
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

plt.rcParams.update({"font.size": 10, "axes.grid": True, "grid.alpha": .3})

def save(fig, path): fig.tight_layout(); fig.savefig(path, dpi=130); plt.close(fig); print("saved", path)

# Q2: slow-function calls vs probability that the cheap test is true
p  = ["2.5%", "10%", "25%", "81%"]
v1 = [964, 887, 738, 189]; v2 = [1000]*4
fig, ax = plt.subplots(figsize=(6.4, 3.8)); x = range(4)
ax.bar([i-.2 for i in x], v1, .4, label="V1 (cheap test first)"); ax.bar([i+.2 for i in x], v2, .4, label="V2 (slow call first)")
ax.set_xticks(list(x)); ax.set_xticklabels(p); ax.set_xlabel("P(senior && eligible) = P(cheap test true)")
ax.set_ylabel("slow verify_card() calls / 1000 passengers"); ax.set_title("Q2: effect of condition order"); ax.legend()
save(fig, "Task02/q2_calls_chart.png")

# Q5: divisions, naive vs i*i<=n  (log scale)
n = ["97", "7919", "999983", "1000003"]; naive = [95, 7917, 999981, 1000001]; sq = [8, 87, 998, 999]
fig, ax = plt.subplots(figsize=(6.4, 3.8)); x = range(4)
ax.bar([i-.2 for i in x], naive, .4, label="for 2..n-1"); ax.bar([i+.2 for i in x], sq, .4, label="for i*i<=n")
ax.set_yscale("log"); ax.set_xticks(list(x)); ax.set_xticklabels(n); ax.set_xlabel("ticket number n (primes)")
ax.set_ylabel("divisions (log scale)"); ax.set_title("Q5: O(n) vs O(sqrt n) divisions"); ax.legend()
save(fig, "Task05/q5_divisions_chart.png")

# Q6: months vs repayment
E = [5000, 2000, 1000, 500, 300, 250, 210, 205, 201, 200.5, 200.01]
M = [3, 6, 12, 26, 56, 82, 154, 188, 268, 303, 501]
fig, ax = plt.subplots(figsize=(6.4, 3.8)); ax.plot(E, M, "o-")
ax.axvline(200, color="r", ls="--", label="repayment = monthly interest (Rs 200): never repaid")
ax.set_xscale("log"); ax.set_xlabel("monthly repayment E (Rs, log scale)"); ax.set_ylabel("months to repay")
ax.set_title("Q6: months explode as E approaches r*P"); ax.legend(); save(fig, "Task06/q6_months_chart.png")

# Q7: original vs redesign
labels = ["97", "7919", "999983", "1000003"]; o = [8, 87, 998, 999]; r = [4, 30, 334, 334]
fig, (a1, a2) = plt.subplots(1, 2, figsize=(9.5, 3.8))
x = range(4); a1.bar([i-.2 for i in x], o, .4, label="original"); a1.bar([i+.2 for i in x], r, .4, label="6k+-1 redesign")
a1.set_xticks(list(x)); a1.set_xticklabels(labels); a1.set_title("Divisions per prime"); a1.set_ylabel("divisions"); a1.legend()
a2.bar(["original", "redesign"], [67741504/1e6, 23739568/1e6], color=["#4c72b0", "#dd8452"])
a2.set_title("All n <= 1,000,003 (total)"); a2.set_ylabel("million divisions")
for i, v in enumerate([67.74, 23.74]): a2.text(i, v + 1, f"{v:.1f} M", ha="center")
fig.suptitle("Q7: original vs redesigned prime test"); save(fig, "Task07/q7_comparison_chart.png")
