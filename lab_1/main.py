import time
import sys
import warnings
import random
import string
import matplotlib.pyplot as plt
warnings.filterwarnings("ignore")
def get_rand_str(length):
    letters = string.ascii_lowercase
    rand_string = ''.join(random.choice(letters) for i in range(length))
    return rand_string
def plot_results1(res_time):

    lengs = []
    for i in res_time.keys():
        lengs.append(int(i))
    colors = {
              'Матричный алгоритм нахождения расстояния Левенштейна' : 'green',
              'Матричный алгоритм нахождения расстояния Дамерау-Левенштейна' : 'orange'}
    for i in res_time[lengs[0]].keys():
        ordinate = []
        for j in res_time.keys():
            if (res_time[j][i] != None):
                ordinate.append(res_time[j][i])
        if i == 'Матричный алгоритм нахождения расстояния Левенштейна' or i == 'Матричный алгоритм нахождения расстояния Дамерау-Левенштейна': 
            plt.plot(lengs[:len(ordinate)], ordinate, color = colors[i], label = i)


    #plt.ylim([0.0,1])
    plt.xlabel("Количество символов в строке")
    plt.ylabel("Время выполнения (с)")
    plt.legend()
    plt.show()
        
def plot_results2(res_time):

    lengs = []
    for i in res_time.keys():
        lengs.append(int(i))
    colors = {'Рекурсивный алгоритм нахождения расстояния Левенштейна' : 'red',
              'Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна' : 'yellow'}
    for i in res_time[lengs[0]].keys():
        ordinate = []
        for j in res_time.keys():
            if (res_time[j][i] != None):
                ordinate.append(res_time[j][i])
        if i == 'Рекурсивный алгоритм нахождения расстояния Левенштейна' or i == 'Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна': 
            plt.plot(lengs[:len(ordinate)], ordinate, color = colors[i], label = i)


   # plt.ylim([0.0,1])
    plt.xlabel("Количество символов в строке")
    plt.ylabel("Время выполнения (с)")
    plt.legend()
    plt.show()
        
                
    
def time_analise():
    lens = [5, 10, 15, 20, 30, 50, 100, 200]
    res_time = {5: None, 10: None, 15: None, 20: None, 30: None, 50: None, 100: None, 200: None}
    times = 5
    for leng in lens:
        print("leng = ", leng)
        time_ = {'Рекурсивный алгоритм нахождения расстояния Левенштейна' : 0.0,
                 'Матричный алгоритм нахождения расстояния Левенштейна' : 0.0,
                 'Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна' : 0.0,
                 'Матричный алгоритм нахождения расстояния Дамерау-Левенштейна' : 0.0}
        for i in range(times):
            print("\t\t", i)
            s1 = get_rand_str(leng)
            s2 = get_rand_str(leng)
            if leng < 15:
                start = time.clock()
                lev_rec(leng,leng,s1,s2)
                stop = time.clock()

                time_['Рекурсивный алгоритм нахождения расстояния Левенштейна'] += (stop - start)
            else:
                time_['Рекурсивный алгоритм нахождения расстояния Левенштейна'] = None

            #2.
            start = time.clock()
            matr_lev(leng,leng,s1,s2)
            stop = time.clock()

            time_['Матричный алгоритм нахождения расстояния Левенштейна'] += (stop - start)
            

            #3.
            Matr = [[sys.maxsize] * (leng + 1) for i in range (leng + 1)]
            start = time.clock()
            rec_matr_lev(Matr, leng, leng, s1, s2)
            stop = time.clock()

            #time_['recur_matr_leven'] += (stop - start)
            

            #4.
            if leng < 15:
                start = time.clock()
                damer_leven(leng, leng, s1, s2)
                stop = time.clock()

                time_['Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна'] += (stop - start)
            else:
                time_['Рекурсивный алгоритм нахождения расстояния Дамерау-Левенштейна'] = None

            #5.
            Matr = [[sys.maxsize] * (leng + 1) for i in range (leng + 1)]
            start = time.clock()
            damer_leven_opt(leng, leng, s1, s2)
            stop = time.clock()

            time_['Матричный алгоритм нахождения расстояния Дамерау-Левенштейна'] += (stop - start)
        for i in time_.keys():
            if time_[i] != None:
                time_[i] /= times
        res_time[leng] = time_
    return res_time

            


def damer_leven_opt(M, N, s1, s2):
    cur_row = range(N + 1)
    for i in range (1, M + 1):
        if i >= 2:
            prev_prev_row = prev_row 
        prev_row, cur_row = cur_row, [i] + [0] * N
        for j in range (1, N + 1):
            err = 1
            if s1[i - 1] == s2[j - 1]:
                err = 0
            right, down, diag = prev_row[j] + 1, cur_row[j - 1] + 1, prev_row[j - 1] + err
            cur_row[j] = min(right, down, diag)
            if s1[i - 2] ==  s2[j - 1] and s1[i - 1] ==  s2[j - 2] and i > 1 and j > 1:
                cur_row[j] = min(cur_row[j], prev_prev_row[j - 2] + 1)   
    return cur_row[N]
def damer_leven_matr(Matr, M, N, s1, s2):
    if Matr[M][N] == sys.maxsize:

        if min(M, N) == 0:
            Matr[M][N] = max(M, N)
            return Matr[M][N]
        elif (M > 1 and N > 1 and s1[M - 1] == s2[N - 2] and s1[M - 2] == s2[N - 1]):
            err = 1
            if (s1[M - 1] == s2[N - 1]):
                    err = 0
            Matr[M][N] = min (damer_leven(M - 1, N, s1,s2) + 1,\
                        damer_leven(M, N - 1, s1,s2) + 1,\
                        damer_leven(M - 1, N - 1, s1,s2) + err,\
                        damer_leven(M - 2, N - 2, s1,s2) + 1)
            return  Matr[M][N]
        else:
            err = 1
            if (s1[M - 1] == s2[N - 1]):
                    err = 0
            Matr[M][N] = min( damer_leven(M - 1, N, s1,s2) + 1,\
                        damer_leven(M, N - 1, s1,s2) + 1,\
                        damer_leven(M - 1, N - 1, s1,s2) + err)
            return  Matr[M][N]
    else:
        return Matr[M][N]
def damer_leven(M, N, s1, s2):
    if min(M, N) == 0:
        return max(M, N)
    elif (M > 1 and N > 1 and s1[M - 1] == s2[N - 2] and s1[M - 2] == s2[N - 1]):
        err = 1
        if (s1[M - 1] == s2[N - 1]):
                err = 0
        return min (damer_leven(M - 1, N, s1,s2) + 1,\
                    damer_leven(M, N - 1, s1,s2) + 1,\
                    damer_leven(M - 1, N - 1, s1,s2) + err,\
                    damer_leven(M - 2, N - 2, s1,s2) + 1)
    else:
        err = 1
        if (s1[M - 1] == s2[N - 1]):
                err = 0
        return min( damer_leven(M - 1, N, s1,s2) + 1,\
                    damer_leven(M, N - 1, s1,s2) + 1,\
                    damer_leven(M - 1, N - 1, s1,s2) + err)


def matr_lev(M, N, s1, s2):
    
    cur_row = range(N + 1)
    for i in range (1, M + 1):
        prev_row, cur_row = cur_row, [i] + [0] * N
        for j in range (1, N + 1):
            err = 1
            if s1[i - 1] == s2[j - 1]:
                err = 0
            right, down, diag = prev_row[j] + 1, \
                                cur_row[j - 1] + 1, \
                                prev_row[j - 1] + err
            cur_row[j] = min(right, down, diag)
    return cur_row[N]
            
def lev_rec(M,N, s1,s2):
    if (M == 0 and N == 0):
        return 0
    elif (M > 0 and N == 0):
        return M
    elif (M == 0 and N > 0):
        return N
    else:
        err = 1
        if s1[M - 1] == s2[N - 1]:
            err = 0
        return min(lev_rec(M, N - 1,s1,s2) + 1,\
                   lev_rec(M - 1, N,s1,s2) + 1,\
                   lev_rec(M - 1, N - 1,s1,s2) + err)

def rec_matr_lev(Matr, M, N, s1, s2):
    if Matr[M][N] == sys.maxsize:
        if (M == 0 and N == 0):
            Matr[M][N] = 0
            return Matr[M][N]
        elif (M > 0 and N == 0):
            Matr[M][N] = M
            return Matr[M][N]
        elif (M == 0 and N > 0):
            Matr[M][N] = N
            return Matr[M][N]
        else:
            err = 1
            if (s1[M - 1] == s2[N - 1]):
                err = 0
            Matr[M][N] =  min (rec_matr_lev(Matr,M, N - 1,s1,s2) + 1, \
                               rec_matr_lev(Matr,M - 1, N,s1,s2) + 1, \
                               rec_matr_lev(Matr,M - 1, N - 1,s1,s2) + err)
            return Matr[M][N]
    else:
        return Matr[M][N]
    
'''
res_time = time_analise()
for i in res_time.keys():
    print("for leng = ", i, ":")
    print("\t\t\t", res_time[i])
plot_results1(res_time)
plot_results2(res_time)

'''
s1 = input("s1: ")
s2 = input("s2: ")
M = len(s1)
N = len(s2)
if (N > M):
    M, N = N, M
    s1,s2 = s2,s1
print("s1 = ", s1, ", len = ", M)
print("s2 = ", s2, ", len = ", N)
#1.
start = time.process_time_ns()#time.perf_counter()#time.clock()
lev_rec(M,N,s1,s2)
print("1. lev_rec = ", lev_rec(M,N,s1,s2))
stop = time.process_time_ns()#time.perf_counter()#time.clock()
#print("proc. time = ", stop - start)

#2.
start = time.process_time_ns()#time.perf_counter()#time.clock()
matr_lev(M,N,s1,s2)
print("2. lev_matr = ", matr_lev(M,N,s1,s2))
stop = time.process_time_ns()#time.perf_counter()#time.clock()
#print("proc. time = ",stop - start)

#3.
Matr = [[sys.maxsize] * (N + 1) for i in range (M + 1)]
start = time.process_time_ns()#start = time.perf_counter()#time.clock()

rec_matr_lev(Matr, M, N, s1, s2)
print("3. rec_lev_matr = ", rec_matr_lev(Matr, M, N, s1, s2))
stop = time.process_time_ns()#stop = time.perf_counter()#time.clock()
#print("proc. time = ", stop - start)

#4.

start = time.process_time_ns()#start = time.perf_counter()#time.clock()
damer_leven(M, N, s1, s2)
print("4. damer_leven = ", damer_leven(M, N, s1, s2))
stop = time.process_time_ns()#stop = time.perf_counter()#time.clock()
#print("proc. time = ", stop - start)
#5.
Matr = [[sys.maxsize] * (N + 1) for i in range (M + 1)]
start = time.process_time_ns()#start = time.perf_counter()#time.clock()
damer_leven_opt(M, N, s1, s2)
print("5. damer_leven_opt = ", damer_leven_opt(M, N, s1, s2))
stop = time.process_time_ns()#stop = time.perf_counter()#time.clock()
#print("proc. time = ", stop - start)



            
