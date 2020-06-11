def kolakoski(n, kol=[1,2,2]):
    if n <= len(kol):
        return kol[:n]
    else:
        i = 2
        while len(kol) < n:
            a = kol[i%2]
            for j in range(kol[i]):
                kol.append(a)
            i += 1
        return kol[:n]



def recursive_kolakoski(n):
    # return kolakoski sequence
    if n == 0:
        return [1]
    if n == 1:
        return [1, 2, 2]
    l = kolakoski(n-1)
    a = l[-1]%2 +1
    for i in range(l[n]):
        l.append(a)
    return l


if __name__ == "__main__":
    print(kolakoski(12,kol=[1,3,3,3]))