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


def plotData(arg, val, figx=12, figy=8, title='', ylbl='', xlbl=''):
    plt.figure(figsize=[figx, figy])
    plt.plot(arg, val)
    if title != '':
        plt.title(title)
    if ylbl != '':
        plt.ylabel(ylbl)
    if xlbl != '':
        plt.xlabel(xlbl)
    plt.grid()
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
        labeled_data = {'y1' : [], "y2" : [], "y3" : [], "y4" : [], 't' : []}
        assignRows(labeled_data, table)
        return labeled_data


def run(input_file):
    lbl_data = data_from_csv(input_file)
    time = lbl_data['t']
    for y in lbl_data.keys():
        if y == 't':
            continue
        plotData(time, lbl_data[y], xlbl='t', ylbl=y, title=y+'(t)')
        if y == 'y1':
            plt.ylim(0.0017, 0.0018)
        plt.savefig(y + '.png', dpi=100)


if __name__ == '__main__':
    run('implicit.csv')
    plt.show()