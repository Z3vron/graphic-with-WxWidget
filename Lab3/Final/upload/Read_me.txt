compile with flags cppflags libs wx-config
for example:
g++ Main.cpp -o output `wx-config --cppflags --libs`