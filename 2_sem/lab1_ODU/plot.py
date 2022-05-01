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
        labeled_data = {'y' : [], "y'" : [], 't' : []}
        assignRows(labeled_data, table)
        return labeled_data


def time_decorator(data):
    timeddata = {
        't' : data['t'],
        "y" : data["y"]
    }
    return timeddata


def phase_decorator(data):
    phasedata = {
        'y' : data['y'],
        "y'" : data["y'"]
    }
    return phasedata


def run(input_files):
    params = [0.01, 0.1, 1, 2, 4, 8, 16, 32, 64, 80, 90, 100]
    method_plot = {}
    time_plot = {}
    for file in input_files:
        for plot in [method_plot, time_plot]:
            plot[file] = plt.subplots(4, 3)
            fig, axis = plot[file]
            fig.set_size_inches(12, 10)
            fig.tight_layout()
    for e in params:
        print('Calculating for e = {}'.format(e))
        subprocess.run(['./build/odu_lab1', str(e)])
        for file in input_files:
            for plot, decor in [(method_plot, phase_decorator), (time_plot, time_decorator)]:
                fig, axis = plot[file]
                data = data_from_csv(file + '.csv')
                pltdata = decor(data)
                addSubplot(axis.flat[params.index(e)], pltdata, title="$e = {}$".format(e))
    for file in input_files:
        fig, _ = method_plot[file]
        fig.savefig(file + '.png', dpi=100)
        fig, _ = time_plot[file]
        fig.savefig('time_' + file + '.png', dpi=100)


if __name__ == '__main__':
    # rk - Runge-Kutta
    # ad - Adams
    files = ['rk1', 'rk2', 'rk3', 'rk4', 'ad2', 'ad3', 'ad4']
    run(files)
    # plt.show()