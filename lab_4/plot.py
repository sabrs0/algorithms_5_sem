import matplotlib.pyplot as plt
def plot_results():
    plt.xlabel('Количество потоков')
    plt.ylabel('Время, с')

    x_ths = [1,2,4,8,16,32]
    y_ths = [0.107852, 0.056602, 0.056602, 0.038650, 0.042526, 0.048666]
    x_size = [100, 200, 500, 1000]
    y_size_par = [0.020617, 0.039583, 0.197411, 0.519283]
    y_size_std = [0.021534, 0.040475, 0.518521, 2.053641]
    plt.plot(x_ths, y_ths, color = 'g', label = 'сложение матриц')
    #plt.ylim([0.0,0.001])
    #plt.xlim([0,1000])
    plt.legend()
    plt.show()

    plt.xlabel('Размер матрицы')
    plt.ylabel('Время, с')
    plt.plot(x_size, y_size_par, color = 'b', label = 'параллельное сложение')
    plt.plot(x_size, y_size_std, color = 'g', label = 'последовательное сложение')
    plt.legend()
    plt.show()
    

plot_results()

