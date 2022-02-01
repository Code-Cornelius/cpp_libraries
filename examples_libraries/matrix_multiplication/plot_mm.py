import matplotlib.pyplot as plt
from matplotlib import cm  # color map
import numpy as np

FILE_NAME = "benchmark_gemm.txt"


# import the file
def process_line(line):
    elems = line.split()
    return [float(x) for x in elems]


def read_file(file_name):
    points = {}

    with open(file_name) as file:
        sizes = []
        name = ""
        for i, line in enumerate(file):
            if i == 0:
                # read the sizes
                sizes = [int(x) for x in line.split()]
            elif i % 3 == 1:
                # read the name of the function
                name = line
                points[name] = {}
            elif i % 3 == 2:
                # read the times
                points[name]["times"] = process_line(line)
            else:
                # read the gflops
                points[name]["gflops"] = process_line(line)

    return sizes, points


def main():
    sizes, points = read_file(FILE_NAME)
    nb_points = len(points)

    Reds, Blues = cm.get_cmap(name='Reds'), cm.get_cmap('Blues')
    color_plot_red = list(Reds(np.linspace(0.2, 1, nb_points//2)))  # color map for plot
    color_plot_blue = list(Blues(np.linspace(0.2, 1, nb_points - nb_points // 2)))  # color map for plot
    colors = color_plot_red + color_plot_blue
    for (name, function_info), c in zip(points.items(), colors):
        plt.plot(sizes, function_info["times"], label=name, color=c, linewidth = 2)

    plt.yscale('log')
    plt.xscale('log', base=2)
    plt.xlabel("The size of the matrix")
    plt.ylabel("Time")
    plt.legend(loc='best', fontsize=8)
    plt.grid()
    plt.savefig("Time", dpi=1000)

    plt.figure()
    for (name, function_info), c in zip(points.items(), colors):
        plt.plot(sizes, function_info["gflops"], label=name, color=c, linewidth=2)

    plt.yscale('log')
    plt.xscale('log', base=2)
    plt.xlabel("The size of the matrix")
    plt.ylabel("GFLOPs")
    plt.legend(loc='best', fontsize=8)
    plt.grid()
    plt.savefig("GFLOPS", dpi=1000)
    plt.show()


if __name__ == "__main__":
    main()
