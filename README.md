# senior
rPi code

Ok this is gonna be a pain in the ass lol

1. Copy all of the files in the repo to the senior design folder

2. Now run the script file "runFirst.sh" from terminal in the folder. Use this:
```bash
sh ./runFirst.sh
```
Its just a bunch of Unix commands so if it fails,
just go in and run them manually. This script compliles/installs the library

3. Compilation:

```bash
 gcc -Wall -pthread -o mainPy mainPy.cpp -lpigpio -lrt
```

4. And to run: 

```bash
sudo ./mainPy
```

:] hopefully no errors


