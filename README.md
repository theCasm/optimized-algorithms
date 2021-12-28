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