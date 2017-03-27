# -*- coding:utf-8 -*-
import pandas as pd
import re
from collections import OrderedDict

def load_data(dpath):
    gift_list = []
    msg_list = []
    with open(dpath, 'r') as f:
        for line in f.xreadlines():
            line = unicode(line.strip(), 'utf-8')
            tuples = line.split('#')
            if len(tuples) != 3:
                continue
            if len(tuples[2]) > 0 and tuples[2][0] == u'@' and re.match(ur'.*[0-9]+.*', tuples[2]):
                tuples[2] = tuples[2][1:]
                gift_list.append(tuples)
            else:
                msg_list.append(tuples)
    return pd.DataFrame(gift_list, columns=['name', 'level', 'gift_id']), \
            pd.DataFrame(msg_list, columns=['name', 'level', 'content'])

def get_gift_dist(dgift):
    return dgift['gift_id'].value_counts()


def get_level_dist(dgift, gift_id):
    lists = dgift[dgift['gift_id']==gift_id]['level']
    lists = lists.value_counts() / lists.value_counts().sum()
    return lists.sort_values(ascending=False)
