import random

start=1
end=10
file = open("botest2.txt", "w")
for i in range(10):
    random_numbers =str(([random.uniform(start, end) for _ in range(1000000)]))
    file.write(random_numbers+"\n")