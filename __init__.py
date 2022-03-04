# -*- coding: utf-8 -*-

"""Query the Kiten Japanese dictionary directly from Albert

Synopsis: <trigger><query>"""

from albert import *;

import os;
import sys;
path = os.path.realpath(os.path.dirname(__file__));
sys.path.append(path);

import out.lib.libkitenpy as kiten;

__title__ = "Kiten辞林の検索";
__version__ = "0.0.1";
__triggers__ = "kiten";
__authors__ = "マギルゥーベルベット";

iconPath = iconLookup("kiten");

def initialize():
    pass;

def finalize():
    pass;

def handleQuery(albertQuery: Query) -> list[Item]:
    # check if the query has a trigger
    if not albertQuery.isTriggered:
        return [];

    # get the actual query for kiten, abort when empty
    query = albertQuery.string
    if len(query) == 0:
        return [];

    info("Kiten Query: " + query);
    results = kiten.lookup(query, 15);

    albertItems = [];

    for res in results:
        item = Item(
            id=__title__,
            icon=iconPath,
            text=res,
            subtext="",
            completion=__triggers__,
            urgency=ItemBase.Normal,
            actions=[
                ClipAction(text="ClipAction", clipboardText=res)
            ]
        );
        albertItems.append(item);

    return albertItems;
