import matplotlib.pyplot as plt

plt.plot([100, 500, 1000, 1500, 2000], [
    0.07, 1.5, 5.3, 12.2, 19.5], 'b-', label='25% PRIM')
plt.plot([100, 500, 1000, 1500, 2000], [
         0.2, x, x, x, x], 'r-', label='50% PRIM')
plt.plot([100, 500, 1000, 1500, 2000], [
         x, x, x, x, x], 'k-', label='75% PRIM')
plt.plot([100, 500, 1000, 1500, 2000], [
         x, x, x, x, x], 'g-', label='99% PRIM')
plt.plot([100, 500, 1000, 1500, 2000], [
    0.06, 0.8, 3.1, 7.3, 12], 'c-', label='25% DIJKSTRA')
plt.plot([100, 500, 1000, 1500, 2000], [
         0.1, 1.22, 4.7, 10.5, 18.4], 'm-', label='50% DIJKSTRA')
plt.plot([100, 500, 1000, 1500, 2000], [
         0.12, 1.66, 6.5, 13.6, 23], 'y-', label='75% DIJKSTRA')
plt.plot([100, 500, 1000, 1500, 2000], [
         0.15, 2, 7.12, 14.7, 26.1], 'pink', label='99% DIJKSTRA')

plt.title('Time of algoritms execution in Adjency Matrix')
plt.xlabel('Number of vertices')
plt.ylabel('Time [ms]')
# plt.ylim([100, 200])

plt.legend()
plt.show()

# AdjencyLists
# plt.plot([100, 500, 1000, 1500, 2000], [
#     0.07, 1.5, 5.3, 12.2, 19.5], 'c-', label='25% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          9.5, x, x, x, x], 'm-', label='50% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          x, x, x, x, x], 'y-', label='75% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          x, x, x, x, x], 'pink', label='99% PRIM')

# AdjencyMatrix

# plt.plot([100, 500, 1000, 1500, 2000], [
#     0.15, 2.5, 8.9, 19.5, 31.1], 'b-', label='25% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.20, 4, 13.5, 34, 56.6], 'r-', label='50% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.24, 4.5, 16.5, 37, 67.2], 'k-', label='75% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.25, 4.6, 17.5, 41, 69], 'g-', label='99% PRIM')
# plt.plot([100, 500, 1000, 1500, 2000], [
#     0.06, 0.8, 3.1, 7.3, 12], 'c-', label='25% DIJKSTRA')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.1, 1.22, 4.7, 10.5, 18.4], 'm-', label='50% DIJKSTRA')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.12, 1.66, 6.5, 13.6, 23], 'y-', label='75% DIJKSTRA')
# plt.plot([100, 500, 1000, 1500, 2000], [
#          0.15, 2, 7.12, 14.7, 26.1], 'pink', label='99% DIJKSTRA')
