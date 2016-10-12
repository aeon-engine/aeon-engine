rd /s /q vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 14 2015 Win64" --graphviz=dependencies.dot
sfdp -Goverlap=prism -Gsize=50,50! -Gsplines=true -n -Tpng dependencies.dot 1>dependencies.png
cd ..
