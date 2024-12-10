x1 = [0] * 11
x2 = [0] * 11
v1 = [0] * 11
v2 = [0] * 11
x1[0] = 5
x2[0] = 1
alpha = 0.1
theta = 0.5
a1 = 0.9
for i in range(1,11):
    x1[i] = a1 * x1[i - 1] + theta * v1[i - 1] 
    x2[i] = -x2[i - 1] + theta * v2[i - 1]
    v1[i] = theta * v1[i - 1] - alpha * x1[i - 1]
    v2[i] = theta * v2[i - 1] - 2 * x2[i - 1]
    print(i,x1[i],x2[i])
print("\n")
x11 = [0] * 11
x21 = [0] * 11
v11 = [0] * 11
v21 = [0] * 11
x11[0] = 5
x21[0] = 1
alpha = 0.1
theta = 0.5
a1 = 0.9
for i in range(1,11):
    sum1 = 0
    sum2 = 0
    for j in range(i):
        for k in range(j+1):
            sum1 += (x11[j - k]* pow(1/2,k))
            sum2 += (x21[j - k] * pow(1/2,k) * 20)
    x11[i] = 5 - 0.1 * sum1
    x21[i] = 1 - 0.1 *sum2
    print(i,x11[i],x21[i])    
         