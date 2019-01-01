import random
random.seed(1)

def answerQuery(ss,x,y) :
    bestX = min(abs(x-1-s) for s in ss)
    bestY = min(abs(y-1-s) for s in ss)
    if bestX < bestY :
        #print(f"DEBUG: {x} is better or equal to {y}")
        return True
    else :
        #print(f"DEBUG: {y} is better or equal to {x}")
        return False

def checkAns(ss,x,y) :
    if x not in ss : return False
    if y not in ss : return False
    return True

def chooseK() :
    l,r = random.choice([  (2,100000), (2,2), (2,10), (99990,100000) ])
    #print("DEBUG: l:", l, " r:", r)
    return random.randrange(l,r+1)

def chooseRandomSubset(n,k) :
    x = list(range(1,n+1))
    random.shuffle(x)
    return x[0:k]

def doBinSearch(ss,l,r) :
    while(r != l) :
        mid = (r+l)//2
        if answerQuery(ss,mid+1,mid+1+1) : r = mid
        else                             : l = mid+1
    return r

for t in range(100) :
    n = 100000
    k = chooseK()
    ss = chooseRandomSubset(n,k)
    print("START")
    dish1 = doBinSearch(ss,0,n-1)
    if (dish1 == 0) :
        dish2 = doBinSearch(ss,1,n-1)
    elif (dish1 == n-1) :
        dish2 = doBinSearch(ss,0,n-2)
    else :
        dish2a = doBinSearch(ss,0,dish1-1)
        dish2b = doBinSearch(ss,dish1+1,n-1)
        dish2  = dish2a if answerQuery(ss,dish2a+1,dish2b+1) else dish2b
    print(f"ANS {dish1} {dish2} {checkAns(ss,dish1,dish2)}")
    print("")




    








