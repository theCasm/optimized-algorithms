# My Optimized Algorithms
This is a collection of algorithms I've made to get more familiar with algorithm estimation. They're not    
the fastest or most accurate, but they're mine.

# Log2
I made two functions for this one, but they both use the same basic principles. Because IEEE-754 specifies    
floats to use an exponent of two multiplied by a fractional part, I can easily find the log of the exponent    
and then use an algorithm for the much easier to handle 1 <= mantissa < 2.

## Linear approach

The first algorithm was just the very famous `log2(1 + x)` ~ `x`. I first converted the mantissa to a float with    
an exponent of 0 to get the fractional part. This is the (1 + x) part we need, and because the log of the exponent    
is just the actual exponent, the approximate log is just exponent + mantissa - 1.    
    
although this is pretty fast, this is painfully innacurate -- I need a better approximation-.

## Quadratic approach

In order to get a better approximate for log, I used a graphing calculator along with a couple systems of equations to    
play around and get some quadratic functions I could use. Knowing that I'm more concerned with the curve of a function    
over x=1 to x=2, I first made a system of the equations `a(1 - p)^2 + q = 0` and `a(2 - p)^2 + q = 1` then ignored q    
like all my other problems. After I simplified it to get a in terms of p, I played around until I got something that looked nice.
    
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
   
Newtons method has qaudratic convergence - that is, if our initial guess is
withing E of the actual answer, the new output will be within E^2. If our
error is above 1, this doesn't mean much. But if we get below one, we are
at least doubling the digits of accuracy every iteration.
    
First, lets understand the structure of a floating point number. The actual way
these numbers are stored doesn't matter, if I was smart I would have coded it
using a union and bit field. What does matter, is that floating point numbers
are stored in base 2 scientific notation. If we wanted to store a big
integer like 1234 in scientific notation, wed write 1.234 x 10^3. If there
were decimals, we might write 12.34 = 1.234 x 10^1. The only difference in
floating point is that we multiply by 2, and write the digits in base 2.
The first digit is always a 1, so we can cheat a little and just store
everything after.
    
So, we want sqrt(1.stuff x 2^e). This is just sqrt(1.stuff) x 2^(e/2), and
1.stuff is guaranteed to be between 1 and 2, so sqrt(1.stuff) is in (1, 1.414..)
and (1+sqrt(2))/2 as a first guess is already very close. The only problem is
that e might be odd.
    
Initially, this might seem easy. E = 2k+1 so
sqrt(1.stuff x 2^(2k+1)) = sqrt(1.stuff) x 2^k x sqrt(2) and we can just
store the value of sqrt(2). Unfortunately, multiplying by sqrt(2) can lose a lot
of accuracy, so this isn't really worth it.
    
Instead, we do something dumb and possibly not worth it. We write
1.stuff x 2^(2k+1) = 2(1.stuff) x 2^2k and do the same thing we do with
even numbers. The 2(1.stuff) is between 2 and 4, so sqrt() is in (sqrt(2), 2)
and in the worst case the guess 1 + sqrt(2)/2 is ~.3 off, but this is good
enough.
    
That was a lot of work! Thankfully, the rest is pretty simple. We just need to
run Newton's method a few times, then we'll have our guess!    
