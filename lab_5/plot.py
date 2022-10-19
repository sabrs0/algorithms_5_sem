import matplotlib.pyplot as plt
def plot_results():
    plt.xlabel('Количество слов')
    plt.ylabel('Время, с')

    x_ths = [ 100, 500, 1000, 2500, 5000, 10000]
    y_th = [0.246199, 1.15154, 2.36791,5.80938, 11.7832, 24.1511]#[2.46199e+8, 1.15154e+9, 2.36791e+9,5.80938e+09, 1.17832e+10, 2.41511e+10]
    y_usual = [0.555688, 2.75488, 5.77721, 14.0969, 28.8174, 55.4429]#[5.55688e+08, 2.75488e+09, 5.77721e+09, 1.40969e+10, 2.88174e+10, 5.54429e+10]
    #plt.plot(x_ths, y_ths, color = 'g', label = 'сложение матриц')
    #plt.ylim([0.0,0.001])
    #plt.xlim([0,1000])
    #plt.legend()
    #plt.show()

    plt.xlabel('количество строк')
    plt.ylabel('Время, с')
    plt.plot(x_ths, y_th, color = 'b', label = 'конвейерный алгоритм')
    plt.plot(x_ths, y_usual, color = 'g', label = 'последовательный алгоритм')
    plt.legend()
    plt.show()
    

plot_results()
