import sys
import matplotlib.pyplot as plt
import csv


def assignRows(labeled_data, table):
    key_it = iter(labeled_data.keys())
    for row in table:
        key = next(key_it)
        for val in row:
            labeled_data[key].append(float(val))


def plotData(lbl_data, figx=12, figy=4, title=''):
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
        plt.plot(arg, vals, label=lbl)
        ylabel +=  lbl + ' '
    if title != '':
        plt.title(title)
    plt.ylabel(ylabel)
    plt.grid()
    plt.legend(loc='best', bbox_to_anchor=(1, 1))
    plt.tight_layout()
    plt.show()


def plot_from_csv(path):
    with open(path, 'r') as csv_data:
        table = csv.reader(csv_data, delimiter=';')
        labeled_data = {'t' : [], 'z(t)' : [], 'x(t)' : []}
        assignRows(labeled_data, table)
        plotData(labeled_data)
        

if __name__ == '__main__':
    path = 'solution.csv'
    if len(sys.argv) > 1:
        path = sys.argv[1]
    plot_from_csv(path)