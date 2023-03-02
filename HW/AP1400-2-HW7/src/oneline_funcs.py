def adjacent_largest_product(arr):
    max_product = float('-inf')
    n = len(arr)
    for i in range(n-1):
        product = arr[i]*arr[i-1]
        if product > max_product:
            max_product = product
    return max_product
 
def all_Longest_Strings(inputArray):
    max_length = 0
    res = []
    for i in range(len(inputArray)):
        if len(inputArray[i]) > max_length:
            max_length = len(inputArray[i])
            res.clear()
            res.append(inputArray[i])
        elif len(inputArray[i]) == max_length:
            res.append(inputArray[i])
    return res

def common_Character_Count(s1, s2):
    count = 0
    for i in s1:
        if i in s2:
            count = count + 1
    return count

def are_Similar(A, B):
    count = 0
    if len(A) != len(B):
        return False
    for i in range(len(A)):
        if A[i] != B[i]:
            count += 1
    return count <= 2

def can_form_palindrome(s):
    # Count the frequency of each character in the string
    freq = {}
    for c in s:
        freq[c] = freq.get(c, 0) + 1
    # Count the number of characters with odd frequency
    num_odd = 0
    for count in freq.values():
        if count % 2 == 1:
            num_odd += 1
    # If the number of characters with odd frequency is at most 1, the string can be rearranged to form a palindrome
    return num_odd <= 1

def array_Replace(inputArray, elemToReplace, substitutionElem):
    for i in range(len(inputArray)):
        if(inputArray[i] == elemToReplace):
            inputArray[i] = substitutionElem
    return inputArray
 
def even_DigitsOnly(n):
    while n > 0:
        m = n % 10
        if m % 2 != 0:
            return False
        m = int(m / 10)
    return True
 
def shift_string(s):
    result = ""
    for c in s:
        if c == 'z':
            result += 'a'
        else:
            result += chr(ord(c) + 1)
    return result

def first_Digit(inputString):
    for i in inputString:
        if i > '0' and i < '9':
            return i
 
def adjacentElementsProduct(inputArray):
    return adjacent_largest_product(inputArray)

 

def allLongestStrings(inputArray):
    return all_Longest_Strings(inputArray)

def checkPalindrome(inputString):
    return inputString == inputString.reverse()

def commonCharacterCount(s1, s2):
    return common_Character_Count

def areSimilar(A, B):
    return are_Similar(A, B)

def palindromeRearranging(inputString):
    return can_form_palindrome(inputString)

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return array_Replace(inputArray, elemToReplace, substitutionElem)

def evenDigitsOnly(n):
    return even_DigitsOnly(n)

def alphabeticShift(inputString):
    return shift_string(inputString)

def firstDigit(inputString):
    return first_Digit(inputString)




