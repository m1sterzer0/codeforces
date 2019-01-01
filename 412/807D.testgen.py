import random
random.seed(1)

def genNum(p) :
    if (random.random() >= p) : return str(-1)
    return str(random.randrange(0,120))

for i in range(100) :
    fn = f"tc{i}"
    with open(fn, 'w') as fp :
        fsolve = [random.uniform(0.05,1.0) for x in range(5)]
        people = random.randrange(110,120)
        print(people, file=fp)
        print ("117 69 19 90 57", file=fp)
        print ("35 61 98 69 33", file=fp)
        #print(" ".join([genNum(vsolve) for x in range(5)]), file=fp)
        #print(" ".join([genNum(psolve) for x in range(5)]), file=fp)
        for j in range(people-2) :
            print(" ".join([genNum(fsolve[i]) for i in range(5)]), file=fp)

