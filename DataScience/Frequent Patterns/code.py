import sys

from itertools import chain, combinations
from collections import Counter

#from time import time

class Node:
    def __init__(self, name, count, parent):
        self.name = name
        self.count = count
        self.link = None
        self.parent = parent
        self.children = {}

    def increase(self, num):
        self.count += num

def createFPTree(data, min_support):
    freqTable = dict(Counter(chain(*data)).most_common())

    headerTable = {}
    for i, v in freqTable.items():
        if v >= min_support:
            headerTable[i] = [v, None]
    freqSet = list(headerTable.keys())

    FPtree = Node('root', 0, None)
    for trans in data:
        cur = FPtree
        trans = list(set(trans).intersection(freqSet))
        if trans:
            trans.sort(key=lambda x: (freqTable[x], int(x)), reverse=True)
        else:
            continue

        for item in trans:
            if item in cur.children:
                cur.children[item].increase(1)
            else:
                cur.children[item] = Node(item, 1, cur)
                if headerTable[item][1] == None:
                    headerTable[item][1] = cur.children[item]
                else:
                    node = headerTable[item][1]
                    while node.link != None: node = node.link
                    node.link = cur.children[item]
            cur = cur.children[item]

    del freqTable
    del freqSet

    return FPtree, headerTable

def BasePatterns(cur):
    condBasePat = []
    table = dict()

    while cur != None:
        condBase = []
        node = cur.parent
        count = cur.count
        while node.name != 'root':
            condBase.append(node.name)
            table[node.name] = table.get(node.name, 0) + count
            node = node.parent
        condBasePat.append([condBase, count])
        cur = cur.link
        del condBase

    return condBasePat, table

def createConditionalTree(link, min_support):
    condBasePat, table = BasePatterns(link)

    headerTable = {}
    for i, v in table.items():
        if v >= min_support:
            headerTable[i] = [v, None]
    if len(headerTable) == 0:
        return None, None
    freqSet = list(headerTable.keys())

    FPtree = Node('root', 0, None)
    for data in condBasePat:
        trans, count = data
        trans = list(set(trans).intersection(freqSet))
        if trans:
            trans.sort(key=lambda x: (table[x], int(x)), reverse=True)
        else:
            continue

        cur = FPtree
        for item in trans:
            if item in cur.children:
                cur.children[item].increase(count)
            else:
                cur.children[item] = Node(item, count, cur)
                if headerTable[item][1] == None:
                    headerTable[item][1] = cur.children[item]
                else:
                    node = headerTable[item][1]
                    while node.link != None: node = node.link
                    node.link = cur.children[item]
            cur = cur.children[item]

    del condBasePat
    del table
    del freqSet

    return FPtree, headerTable

def singlePath(node):
    while len(node.children) != 0:
        if len(node.children) != 1: return False
        node = list(node.children.values())[0]
    return True

def mineTree(header, min_support, prefix):
    L = [i[0] for i in sorted(header.items(), key=lambda v: (v[1][0], int(v[0])))]
    for basePat in L:
        newFreqSet = prefix.copy()
        newFreqSet.add(basePat)
        print(f"{','.join(newFreqSet)}:{header[basePat][0]/n_trans:.4f}")
        CondTree, Header = createConditionalTree(header[basePat][1], min_support)

        if Header != None:
            if singlePath(CondTree):
                beta = list(Header.keys())
                for i in range(1, len(beta)+1):
                    comb = list(combinations(beta, i))
                    for line in comb:
                        count = min(list(map(lambda x: Header[x][0], line)))
                        print(f"{','.join(newFreqSet)},{','.join(line)}:{count/n_trans:.4f}")
                    del comb
                del beta
                        
            else:
                mineTree(Header, min_support, newFreqSet)
    return

if __name__ == '__main__':
    #start = time()
    minSup = float(sys.argv[1])
    inputFile = str(sys.argv[2])
    outputFile = str(sys.argv[3])

    Transactions = []
    with open(inputFile, 'r') as f:
        for line in f.readlines():
            Transactions.append(line.strip('\n').split(','))

    n_trans = len(Transactions)
    minSup *= n_trans
    FPtree, headerTable = createFPTree(Transactions, minSup)
    del Transactions

    with open(outputFile, 'w') as f:
        sys.stdout = f
        mineTree(headerTable, minSup, set([]))

    #print(f"time: {time()-start}s")
