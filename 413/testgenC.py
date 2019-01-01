
import random;
print (f"40 {random.randrange(10,21)} {random.randrange(10,21)}")
for i in range(40) :
    print(f'{random.randrange(1,21)} {random.randrange(1,31)} {"C" if random.random() < 0.5 else "D"}') 