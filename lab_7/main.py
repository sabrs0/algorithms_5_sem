import csv
import random
import time
from matplotlib import pylab
def get_time(func, arg):
    sum = 0
    for i in range(100):
        start = time.time()
        func(arg)
        sum += (time.time() - start)
    return round(sum / 100, 6)
def get_time_sort(func, arg, reverse_):
    sum = 0
    for i in range(100):
        start = time.time()
        func(arg, reverse_)
        sum += (time.time() - start)
    return round(sum / 100, 6)

def get_time_search(func, key, dict):
    sum = 0
    for i in range(100):
        start = time.time()
        func(key, dict)
        sum += (time.time() - start)
    return sum / 100

def get_time_search_combined(func, key, dict, segs):
    sum = 0
    for i in range(100):
        start = time.time()
        func( segs, dict, key)
        sum += (time.time() - start)
    return sum / 100


def test_time(dict):
    time_simple = []
    time_bin = []
    time_combined = []

    #-------------------------------------------------
    print("Лексикографическая сортировка ", get_time_sort(sort_dict, dict, False), "cекунд")
    print("Частотный анализ и лексикографическая сортировка ", get_time(frequency_analysis, dict), "cекунд")

    sorted_dict = sort_dict(dict, False)
    segment_list = frequency_analysis(dict)

    print("\nЛучший случай поиска ключа")
    print("Алгоритм полного перебора", get_time_search(search_simple, 'emorriarty0@illinois.edu', dict), "cекунд")
    print('Aлгоритм бинарного поиска', get_time_search(bin_search, 'cizaksondv@blog.com', sorted_dict), "секунд")
    # print(list(sorted_dict.keys())[int(len(sorted_dict) / 2)]) - 201242 - лучший случай для бинарного поиска - центральный элемент отсортированного словаря

    #print(list(segment_list[0]['dict'].keys())[int(segment_list[0]['count'] / 2)]) - 203094
    print('Комбинированный алгоритм', get_time_search_combined(combined_search, 'cdavernee@ebay.co.uk', dict, segment_list), "секунд")

    print("\nХудший случай поиска ключа")
    print("Алгоритм полного перебора", get_time_search(search_simple, 'cscothornrr@bing.com', dict), "cекунд")
    print('Aлгоритм бинарного поиска', get_time_search(bin_search, 'clivingstonedt@ucoz.ru', sorted_dict), "секунд")
    #print(list(sorted_dict.keys())[len(sorted_dict.keys()) - 1]) #- 980 - худший случай для бинарного поиска - центральный элемент отсортированного словаря

   # print(list(segment_list[len(segment_list) - 1]['dict'].keys())[int(segment_list[len(segment_list) - 1]['count'] - 1)]) #- 500032
    print('Комбинированный алгоритм', get_time_search_combined(combined_search, 'zrasedl@merriam-webster.com', dict, segment_list), "секунд")

    print("\nПоиск несуществующего ключа")
    print("Алгоритм полного перебора", get_time_search(search_simple, '0', dict), "cекунд")
    print('Aлгоритм бинарного поиска', get_time_search(bin_search, '0', sorted_dict), "секунд")
    print('Комбинированный алгоритм', get_time_search_combined(combined_search, '0', dict, segment_list), "секунд")


    print("\nПоиск случайного ключа")
    print("Алгоритм полного перебора", get_time_search(search_simple, 'saskhamn@usatoday.com', dict), "cекунд")
    print('Aлгоритм бинарного поиска', get_time_search(bin_search, 'saskhamn@usatoday.com', sorted_dict), "секунд")
    print('Комбинированный алгоритм', get_time_search_combined(combined_search, 'saskhamn@usatoday.com', dict, segment_list), "секунд")

    x_list = [i for i in range(len(dict.keys()))]
    for d in list(dict.keys()):
        time_simple.append(get_time_search(search_simple,d, dict))
        time_bin.append(get_time_search(bin_search, d, sorted_dict))
        time_combined.append(get_time_search_combined(combined_search, d, dict, segment_list))

    pylab.xlabel('Индекс ключа')
    pylab.ylabel('Время, секунды')
    pylab.plot(x_list, time_simple, 'r--', label='Полный перебор')
    pylab.plot(x_list, time_bin, color='yellow', label='Бинарный поиск')
    pylab.plot(x_list, time_combined, 'b-.', label='Комбинированный')
    pylab.legend(loc='upper left')
    pylab.show()

    x1_list = []
    time_simple1 = []
    time_bin1 = []
    time_combined1 = []

    for i in range(len(x_list)):
        if i % 15 == 0:
            x1_list.append(i)
            time_simple1.append(time_simple[i])
            time_bin1.append(time_bin[i])
            time_combined1.append(time_combined[i])

    pylab.xlabel('Индекс ключа')
    pylab.ylabel('Время, секунды')
    pylab.plot(x1_list, time_simple1, 'r--', label='Полный перебор')
    pylab.plot(x1_list, time_bin1, color='yellow', label='Бинарный поиск')
    pylab.plot(x1_list, time_combined1, 'b-.', label='Комбинированный')
    pylab.legend(loc='upper left')
    pylab.show()

    print("\nАлгоритм перебором ")
    print("Максимальное время выполнения = ", max(time_simple))
    print("Минимальное время выполнения = ", min(time_simple))
    print("Среднее время выполнения = ", sum(time_simple) / len(time_simple))

    print("\nБинарный поиск ")
    print("Максимальное время выполнения = ", max(time_bin))
    print("Минимальное время выполнения = ", min(time_bin))
    print("Среднее время выполнения = ", sum(time_bin) / len(time_bin))

    print("\nКомбинированный алгоритм ")
    print("Максимальное время выполнения = ", max(time_combined))
    print("Минимальное время выполнения = ", min(time_combined))
    print("Среднее время выполнения = ", sum(time_combined) / len(time_combined))

def sort_dict(dict_, reverse_):
    list_keys = sorted(dict_.keys(), reverse = reverse_)
    new_dict = {}
    for i in list_keys:
         new_dict[i] = dict_[i]
    return new_dict
def read_data():
    p_dict = {}
    with open('people.csv') as f:
        reader = csv.DictReader(f)
        for row in reader:
            p_dict[row['email']] = row['name']
    return p_dict
def search_simple(key_, dict_):
    iters = 0
    for i in dict_.keys():
        if (i == key_):
            print("iters simple = ", iters )
            return dict_[i];
        iters += 1
    return None
def bin_search(key_, dict_):
    iters = 0
    sorted_keys = sorted ((dict_.keys()))
    left = 0; right = len(sorted_keys);
    cur = (left + right) // 2
    while(sorted_keys[cur] != key_):
        if (key_ < sorted_keys[cur]):
            right = cur - 1
        elif (key_ > sorted_keys[cur]):
            left = cur + 1
        cur = (left + right) // 2
        if (left > right):
            return None;
        iters += 1
    print("bin iters = ", iters)
    return dict_[sorted_keys[cur]]


def frequency_analysis(p_dict):
    Segments = {}
    Segments_by_count = {}
    for i in p_dict.keys():
        if i[0] in Segments.keys():
            Segments[i[0]]['count'] += 1
            Segments[i[0]]['values'].append(i)
        else:
            Segments[i[0]] = {'count' :0, 'values' : []}
            Segments[i[0]]['count'] += 1
            Segments[i[0]]['values'].append(i)
    for i in Segments.keys():
        Segments[i]['values'].sort()
        if Segments[i]['count'] in Segments_by_count.keys():
            Segments_by_count[Segments[i]['count']].append({'letter' :i, 'values' : Segments[i]['values']})
        else:
            Segments_by_count[Segments[i]['count']] = []
            Segments_by_count[Segments[i]['count']].append({'letter' :i, 'values' : Segments[i]['values']})
    #for i in Segments_by_count.keys():
        #print(Segments_by_count[i][0]['letter'])
    
    Segments_by_count = sort_dict(Segments_by_count, True)
    #for i in Segments_by_count.keys():
        #print(Segments_by_count[i]['values'][1])
    return Segments_by_count;
    
def combined_search(Segmented_dict, p_dict, key_):
    iters = 0
    for i in Segmented_dict.keys():
        for j in range(len(Segmented_dict[i])):
            #print(Segmented_dict[i][j]['letter'])
            if (Segmented_dict[i][j]['letter'] == key_[0]):
                
                left = 0; right = len(Segmented_dict[i][j]['values']);
                cur = (left + right) // 2
                while (Segmented_dict[i][j]['values'][cur] != key_):
                    if (key_ < Segmented_dict[i][j]['values'][cur]):
                        right = cur - 1
                    elif (key_ > Segmented_dict[i][j]['values'][cur]):
                        left = cur + 1
                    cur = (left + right) // 2
                    iters += 1
                print("combined iters = ", iters)
                return p_dict[Segmented_dict[i][j]['values'][cur]];
        


p_dict = read_data()
print(search_simple('saskhamn@usatoday.com', p_dict))
p_dict = sort_dict(p_dict, False)
print(bin_search('saskhamn@usatoday.com', p_dict))


Segs = frequency_analysis(p_dict)
print(combined_search(Segs, p_dict, 'saskhamn@usatoday.com'))
#test_time(p_dict)
