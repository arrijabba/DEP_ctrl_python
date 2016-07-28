# senior
rPi code

I am unable to compile this code on my comp due to architecture/library differences but its not bad at all.

1. Open a terminal window (over SSH or on a display)
2. navigate to the "senior design" folder on the desktop

3. Run the following command after you update that file (over FTP? or USB or web)

```bash
g++ -Wall -o test_wave mainFn.cpp
```

and if that doesn't work its probably because the library needs to be statically linked. Run this:

```bash
g++ -Wall -o test_wave mainFn.cpp -lwiringPi
```


