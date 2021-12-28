# My Optimized Algorithms
This is a collection of algorithms I've made to get more familiar with algorithm estimation. They're not    
the fastest or most accurate, but they're mine.

# Log2
I made two functions for this one, but they both use some basic principles. Because IEEE-754 specifies    
floats to use an exponent of two multiplied by a fractional part, I can easily find the log of the exponent    
and then use an algorithm for the much easier to handle 1 <= mantissa < 2.

## Linear approach

The first algorithm was just the very famous `log2(1 + x)` ~= `x`. I first convert the mantissa to a float with    
an exponent of 0, to just get the fractional part. This is the (1 + x) part we need, and because the log of the exponent    
is just the actual exponent, the approximate log is just exponent + mantissa - 1.    
    
although this is pretty fast, this is incredibly innacurate -- I need a better approximate

## Quadratic approach

In order to get a better approximate for log, I used a graphing calculator along with a couple systems of equations to    
play around and get some quadratic functions I could use. Knowing that I'm more concerned with the curve of a function    
over x=1 to x=2, I first made a system of the equations `a(1 - p)^2 + q = 0` and `a(2 - p)^2 + q = 1` then ignored q    
like all of my problems. After I simplified it to get a in terms of p, I played around until I got something that looked nice.
    
This is great and all, but I wanted to feel smart and this just wouldn't do. So, I created a system of the    
same two equations plus `a(sqrt(2) - p)^2 + q = 0.5` and solved for *all* variables. This took a lot of time and tears to    
get in exact form, but when my hard work finally paid off I found that it just really wasn't better than my    
first. I didn't want my hard work to go to waste though, so I decided to use it for lower values of x. It was more    
accurate there, anyway.
    
With my two functions in hand, I copied my code from the linear algorithm, but ran the mantissa through a     
function (depending on it's value) instead of just subracting one. Then I could just return the result plus
it's    
exponent. Easy, right? No? It's confusing and terribly explained? Hey, I tried my best.

# Square Root
Newton's Method is a well known way to calculate square roots. So we just need to use that, right? Well, not exactly.    
Newton's Method needs a guess for square root, which it will nudge closer and closer to the actual root. If we just use    
the number as it's guess, it will take ages to lower it enough that we can start getting an accurate answer.    
    
How can we fix this? Well, if we look at a number in binary, we can see that a square root will have around half as    
many bits as it's square. Why is this? When you multiply two numbers, the product will have about as many digits as    
the sum of the numbers digits. As we can see from doing multiplication by hand, this is because we need to multiply    
every digit with every other digit. So, a square will just have the square roots digits twice. Can we abuse this to    
Get a good guess?    
    
With how floats and doubles work, they store an exponent with them. This is just how many (binary) digits they have!    
So, if we take this number and divide it by two, we have the number of excess digits the square has. In order to cut    
them off, we just need to divide by 2^(excess digits).    
    
That was a lot of work! Thankfully, the rest is pretty simple. We just need to store our guess and run Newton's method    
a few times, then we'll have our guess!    
    
This isn't perfect, when we try very large numbers even the small difference between our guess and the actual root is    
too much, and our guess is innacurate. Thank god this is only meant to be a simple optimized algorithm, otherwise I'd    
have to deal with that! Kind of reminds me of my terrible error handling in most of my other programs.
