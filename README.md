## Build and install

```
make [TEST]
```

Add crontab entry as root, with path adjusted to your repo location:  
```
$ sudo crontab -l | grep reboot
@reboot /home/hermann/9383761-digit-prime/doit &
$
```

In Bios set "Restore on AC/Power Loss" to "Power ON".
Have 90MB free disk space for TEST run (1.1h), 100GB free disk space for real run (75 days), both on 7600X CPU.
Initially remove all "\*.job" files, and then reboot to start.

See section [TEST](#test) below, and section [75 days sequential computation](#75-days-sequential-computation) — it has started already:  
```
$ stat 9383761-digit-prime/0.job | grep Birth
 Birth: 2023-07-20 17:33:45.443004722 +0200
$
```
Finally section [Power consumption](#power-consumption) forecasts power consumption of 75 days computation as 150KWh, with more than half powered green from roof top solar power.

## Motivation

I was an ultramarathon runner [when I was younger](https://statistik.d-u-v.org/getresultperson.php?runner=2493&Language=EN), and this repo is all about making my new AMD Ryzen 5 7600X CPU PC do an ultramarathon (sequential) computation of 70+ days!  

## Why 7600X CPU?
That CPU is rank 18 (4,221 CPU Mark, much more expensive rank 1 has 4,791) of PassMark Software's >3100 CPUs [Single Thread Performance](https://www.cpubenchmark.net/singleThread.html) list. Linux, macOS and mobile versions of PerformanceTEST are free. PerformanceTEST reports this on my Ubuntu 22.04 Desktop PC, not far away from list value:
```
...
CPU Single Threaded              4173 Million Operations/s
...
```

7600X CPU shows 2nd place on gmpbench list (sequential pure integer benchmark of GNU Multiple Precision arithmetic library):  
https://gmplib.org/gmpbench  
https://gmplib.org/list-archives/gmp-devel/2023-July/006184.html

More details on the PC used:  
https://github.com/Hermann-SW/7600X

## *sqrt(-1) (mod p)* for 9,383,761-digit prime p

Rank 9 of [THE LARGEST KNOWN PRIMES](https://t5k.org/primes/lists/all.txt) list is 9,383,761 decimal digit number *p=10223\*2^31172165+1*. It is the largest known prime *=1 (mod 4)*. For such primes there exists *sqrt(-1) (mod p)*, which is what the PC will compute. It does so by computing *3^((p-1)/4) (mod p)*, normally with just libgmpxx function call *mpz_powm(res, 3, (p-1)/4, p)*. Value *3* because it is (smallest) quadratic non-residue mod p. The exponent can be rewritten as *(p-1)/4 = (2^31172163)^10223*. So GMP library will have to do 31,172,163 squarings mod p, and then a fast exponentiation by less than *2^14* exponent. Doing 70+ days computation with a single GMP function call is a bit risky at least, as any interruption would require start from begin.

## Previous runtimes for up to 1,000,000-digit primes

I did compute *sqrt(-1) (mod p)* for lowest known 1,000,000 decimal digit prime before. With i7-11850H CPU that computation took 26.01h (19h expected for 7600X CPU based on runtimes for up to 388,342-digit prime):  
![sqrtm1___.png](sqrtm1___.png)

## Upper bound on 70+ days computation

I did compute upper bound of 74.13 days for computing *sqrt(-1) (mod p)* for the more than 9million-digit prime:  
[https://gmplib.org/list-archives/gmp-devel/2023-July/006189.html](https://gmplib.org/list-archives/gmp-devel/2023-July/006189.html)

## Basement ceiling computing center for 70+ days

For 70+ days sequential computation I decided not to use the UPS that I recently bought. It is able to continue PC operation with single thread running for 17:58min. But we have really seldom power outages here in Germany. Interestingly parts of my town had one recently (7/17/2023). We had no mains power for more than 2 hours, so the UPS I have would not have helped.

Instead the big computation is split into *loops* smaller jobs of *sqspl* squarings *(mod p)* [with loops \* sqspl == 31,172,163], and final small exponentiation *(mod p)* with exponent *10223*. Each job will store its result. Bios "Restore on AC/Power Loss" is set to "Power ON", and crontab "@reboot" will continue computation where it was interrupted, if such an interrupt will happen at all (if I will need to do an important other computation on that PC, I might kill the long computation, do whatever is needed, and finally "sudo reboot 0" will continue the big computation).

|in the dark|with flash|
|-----------|----------|
|![in the dark](20230717_214249.part.10%25.jpg)|![with flash](20230717_214236.part.10%25.jpg)|


## TEST

This diagram shows runtimes [s] for the jobs 1..322 of determining *sqrt(-1) (mod p)* for 272770-digit prime p. This much smaller prime results in total runtime of just above 1 hour (1689839637.20 - 1689835811.49 = 1:03:45.71h), instead of 75 days for the real run:  
![job.runtimes.TEST.png](TEST/job.runtimes.TEST.png)  
The runtime epoch timestamp from just before job *x* and after job *x* are here, for 0<=x<=323. 0.job contains just "3\n", 1.job contains *3^(2^2403) (mod p)* and 323.job contains *sqrt(-1) (mod p)*:  
[TEST/tstamps.txt](https://github.com/Hermann-SW/9383761-digit-prime/blob/main/TEST/tstamps.txt)  
[TEST/0.job](https://github.com/Hermann-SW/9383761-digit-prime/blob/main/TEST/0.job)  
[TEST/1.job](https://github.com/Hermann-SW/9383761-digit-prime/blob/main/TEST/1.job)  
[TEST/323.job](https://github.com/Hermann-SW/9383761-digit-prime/blob/main/TEST/323.job)  

## 75 days sequential computation

Has started:

```
$ stat 9383761-digit-prime/0.job | grep Birth
 Birth: 2023-07-20 17:33:45.443004722 +0200
$
```

Completed jobs 13..23 show 589s runtime per job.  
With 11122 jobs that is 589\*11122/3600/24 = 75.8 days minimal runtime.

## Power consumption

Photos taken 3min/3h after power meter and PC got powered:  
![20230720_173634.part.50%.jpg](20230720_173634.part.50%25.jpg) ![20230720_203332.part.66%.jpg](20230720_203332.part.66%25.jpg)  
Power factor 1.00, power consumption 77W and in total 0.23KWh consumed in 3h.

80W is 2KWh/day or 150KWh for expected 75 days computation.

We have solar power on roof top, and on good days (25KWh)  
![good.50%.jpg](good.75%25.jpg)  
as well as on not so good days (13.9KWh),  
![not_so_good.50%.jpg](not_so_good.75%25.jpg)  
80W = 0.08KW are easily produced for more than 12 hours per day. So more than half of the computation is green.
