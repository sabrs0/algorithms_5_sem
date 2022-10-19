import matplotlib.pyplot as plt
def plot_results_0(classic_0, vgd_0, vgd_opt_0):

    
    plt.plot(classic_0[0], classic_0[1], color = 'g', label = 'Классический алгоритм')
    plt.plot(vgd_0[0], vgd_0[1], color = 'b', label = 'Алгоритм Винограда')
    plt.plot(vgd_opt_0[0], vgd_opt_0[1], color = 'r', label = 'Улучшенный алгоритм Винограда')
    #plt.ylim([0.0,10])
    plt.xlabel("Размер матрицы")
    plt.ylabel("Время (c)")
    plt.legend()
    plt.show()
def plot_results_1(classic_1, vgd_1, vgd_opt_1):


    
    plt.plot(classic_1[0], classic_1[1], color = 'g', label = 'Классический алгоритм')
    plt.plot(vgd_1[0], vgd_1[1], color = 'b', label = 'Алгоритм Винограда')
    plt.plot(vgd_opt_1[0], vgd_opt_1[1], color = 'r', label = 'Улучшенный алгоритм Винограда')
    #plt.ylim([0.0,10])
    plt.xlabel("Размер матрицы")
    plt.ylabel("Время (c)")
    plt.legend()
    plt.show()





f = open("time.txt", 'r')
classic_0 = [[],[]]
vgd_0 = [[],[]]
vgd_opt_0 = [[],[]]
for i in range(6):
    for j in range(4):
        x = f.readline().split()
        for k in x:
            if (k[0].isdigit()):
                if j == 0:
                    classic_0[0].append(int(k))
                    vgd_0[0].append(int(k))
                    vgd_opt_0[0].append(int(k))
                elif j == 1:
                    classic_0[1].append(float(k))
                elif j == 2:
                    vgd_0[1].append(float(k))
                elif j == 3:
                    vgd_opt_0[1].append(float(k))
classic_1 = [[],[]]
vgd_1 = [[],[]]
vgd_opt_1 = [[],[]]
for i in range(6):
    for j in range(4):
        x = f.readline().split()
        for k in x:
            if (k[0].isdigit()):
                if j == 0:
                    classic_1[0].append(int(k))
                    vgd_1[0].append(int(k))
                    vgd_opt_1[0].append(int(k))
                elif j == 1:
                    classic_1[1].append(float(k))
                elif j == 2:
                    vgd_1[1].append(float(k))
                elif j == 3:
                    vgd_opt_1[1].append(float(k))

plot_results_0(classic_0, vgd_0, vgd_opt_0)
plot_results_1(classic_1, vgd_1, vgd_opt_1)

f.close()
