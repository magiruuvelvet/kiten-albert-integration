import os;
import out.lib.libkitenpy as kiten;

path = os.path.realpath(os.path.dirname(__file__));
print(path);

res = kiten.lookup("日本語", 15);

for i in res:
    print(i);
