import matplotlib.pyplot as plt
def plot_results_0(bubble, insert, choice):
    plt.xlabel = 'Размер массива'
    plt.ylabel = 'Время'

    
    plt.plot(bubble[0], bubble[1], color = 'g', label = 'bubble')
    plt.plot(insert[0], insert[1], color = 'b', label = 'insert')
    plt.plot(choice[0], choice[1], color = 'r', label = 'choice')
    #plt.ylim([0.0,0.001])
    #plt.xlim([0,1000])
    plt.legend()
    plt.show()
def plot_results_1(classic_1, vgd_1, vgd_opt_1):
    plt.xlabel = 'Размер матрицы'
    plt.ylabel = 'Время'

    
    plt.plot(classic_1[0], classic_1[1], color = 'g', label = 'bubble')
    plt.plot(vgd_1[0], vgd_1[1], color = 'b', label = 'insert')
    plt.plot(vgd_opt_1[0], vgd_opt_1[1], color = 'r', label = 'choice')
    #plt.ylim([0.0,10])
    plt.legend()
    plt.show()





f = open("random_time.txt", 'r')
bubble = [[],[]]
insert = [[],[]]
choice = [[],[]]
for i in range(6):
    for j in range(4):
        x = f.readline().split()
        for k in x:
            if (k[0].isdigit()):
                if j == 0:
                    bubble[0].append(int(k))
                    insert[0].append(int(k))
                    choice[0].append(int(k))
                elif j == 1:
                    bubble[1].append(float(k))
                elif j == 2:
                    insert[1].append(float(k))
                elif j == 3:
                    choice[1].append(float(k))

plot_results_0(bubble, insert, choice)

f.close()
