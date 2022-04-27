from math import ceil
import sys
import matplotlib.pyplot as plt
import csv
import subprocess


def assignRows(labeled_data, table):
    key_it = iter(labeled_data.keys())
    for row in table:
        key = next(key_it)
        for val in row:
            labeled_data[key].append(float(val))


def plotData(lbl_data, figx=6, figy=6, title='', label=''):
    plt.figure(figsize=[figx, figy])
    lbl_num = 0
    ylabel = ''
    for lbl in lbl_data:
        lbl_num += 1
        if lbl_num == 1:
            arg = lbl_data[lbl]
            plt.xlabel(lbl)
            continue
        vals = lbl_data[lbl]
        plt.plot(arg, vals, label=label)
        ylabel +=  lbl + ' '
    if title != '':
        plt.title(title)
    plt.ylabel(ylabel)
    plt.grid()
    plt.legend(loc='best', bbox_to_anchor=(1, 1))
    plt.tight_layout()


def addSubplot(axis, lbl_data, title=''):
    axis.set_title(title)
    ylbl = ''
    lbl_num = 0
    for lbl in lbl_data:
        lbl_num += 1
        if lbl_num == 1:
            arg = lbl_data[lbl]
            axis.set(xlabel=lbl)
            continue
        vals = lbl_data[lbl]
        axis.plot(arg, vals)
        ylbl +=  lbl + ' '
    axis.set(ylabel=ylbl)


def data_from_csv(path):
    with open(path, 'r') as csv_data:
        table = csv.reader(csv_data, delimiter=',')
        # x = y, z = y'
        labeled_data = {'y' : [], "y'" : []}
        assignRows(labeled_data, table)
        return labeled_data


def run(path):
    params = [0.01, 0.1, 1, 2, 4, 8, 16, 32, 64, 80, 90, 100]
    fig, axis = plt.subplots(4, 3)
    fig.set_size_inches(12, 10)
    fig.suptitle(path)
    for e, ax in zip(params, axis.flat):
        print('Calculating for e = {}'.format(e))
        subprocess.run(['./build/odu_lab1', str(e)])
        data = data_from_csv(path)
        addSubplot(ax, data, title="$e = {}$".format(e))


if __name__ == '__main__':
    files = ['rk2.csv', 'rk3.csv', 'rk4.csv']
    for path in files:
        run(path)
    plt.show()