import math
import sys

def main():
	tc = int(input())
	for j in range(tc):
		tmp ,L = input().split(" ")
		tmp = int(tmp)
		L = int(L)
		arr = [int(x) for x in input().split(" ")]
		index = 0
		gcd_var = 0
		for i in range(1,L):
			if arr[i] != arr[i-1]:
				gcd_var = math.gcd(arr[i],arr[i-1])
				index = i
				
		plain = [0]*(L+1)
		primes = set()
		plain[index] = gcd_var
		primes.add(gcd_var)
		
		for i in range(index+1,L+1):
			plain[i]=int(arr[i-1]/plain[i-1])
			primes.add(int(plain[i]))
		for i in range(index-1,-1,-1):
			plain[i]=int(arr[i]/plain[i+1])
			primes.add(int(plain[i]))
			
		primes = sorted(primes)
		mapping = {}
		c ='ABCDEFGHIJKLMNOPQRSTUVWXYZ'


		index = 0
		for x in primes:
			mapping[x] = c[index]
			index += 1

		res = ""
		for y in plain:
			res += mapping[y]

		print("Case #"+ str(j+1)+": " +res)

if __name__ == '__main__':
	main()