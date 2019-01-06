

def doit(r) :
    sign = 1
    while (len(r) > 1) :
        s = [0] * (len(r)-1)
        for i in range(len(s)) :
            s[i] = r[i] + sign * r[i+1]
            sign = -1 * sign
        r = s
    return r[0]

for l in range(1,16) :
    for j in range(l) :
        r = [0] * l
        r[j] = 1
        ans = doit(r)
        print(ans,r)
    print("")
