import sys
import os

prefixes = {'0':'zero' ,'1': 'one', '2':'two', '3':'three', '4':'four', '5':'five', '6':'six',
				'7':'seven', '8':'eight', '9':'nine', '10': 'ten', '11':'eleven', '12':'twelve', '13':'thirteen', '14': 'fourteen', '15':'fifteen',
				'16':'sixteen', '17':'seventeen', '18':'eighteen','19':'nineteen'}
tens = {'2':'twenty', '3':'thirty', '4':'fourty', '5':'fifty', '6':'sixty',
				'7':'seventy', '8':'eighty', '9':'ninety'}
suffix = ["","thousands", "milions", "billions"]

def getNumber(number):
	length = number.__len__()
	firstDigits = length%3
	j = length/3
	i = 0
	res = ""
	if firstDigits != 0:
		res = res +" " +digits3(number[i:i+firstDigits]) +" "+ suffix[j]
	i = i+firstDigits
	j = j-1
	while i < length:
		res = res +" " +digits3(number[i:i+3]) +" " + suffix[j]
		j = j -1
		i = i+3
	return res
	
def digits3(number):
	if number.__len__() < 3:
		return digits2(number)
	if number[0] is '0':
		return digits2(number[1:])
	res = prefixes[number[0]] + ' hundred and '
	res = res + digits2(number[1:])
	return res
		
def digits2(number):
	if number.__len__() < 2:
		return digits1(number)
	if number[0] is '0':
		return digits1(number[1:])
	if number[0] is '1':
		return prefixes[number]
	return tens[number[0]] + " " + prefixes[number[1]]

def digits1(number):
	if number is '':
		return ''
	return prefixes[number]
		
	
res = getNumber("111111")
print(res)
