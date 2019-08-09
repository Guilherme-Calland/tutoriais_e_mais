import Data.List
import System.IO
 
-- comment
 {-
 multi-line comment
-}

x = 50
somaDeDez = sum[1..10]
modEx = mod 10 4
y = 5 - 4
trueAndFalse = True && False
trueOrFalse = True || False
notTrue = not(True)
listaDeNums = [10,12,20,3,50,101]
outraLista = 5 : 10 : 12 : 7 : []
multList = [[1,2,3],[4,5,6]]
maisNums = 202 : listaDeNums
lengList = length maisNums
firstValue = head listaDeNums
lastValue = last listaDeNums
dropLast = init listaDeNums
primeiros3 = take 3 listaDeNums
dropPrimeiros3 = drop 3 listaDeNums
maxValue = maximum listaDeNums
minValue = minimum listaDeNums
somaLista = sum listaDeNums
evenList = [2,4..30]
seqList = [1,5..30]
infinList = [1,2..]
many2s = take 10 (repeat 2)
maisNums2 = 303 : listaDeNums
listTimes2 = [x * 2 | x <- listaDeNums]
listTimes3 = [x*3 | x <- [1..10]]
menorQue50 = [x | x <- [1..100], x <= 50]
sorted = sort [10,8..1]
list1 = [1,2,3]
list2 = [4,5,6]
uniao = zipWith (+) list1 list2
menorque10 = filter (<10) listaDeNums
listaAte50 = filter (<50) [1,5..100]
pow2List = [x^2 | x <- [1..100]]
multTable = [x*y | x <- [1..10], y <- [1..10]]
bobSmith = ("Bob",27)
bobsName = fst bobSmith
bobsAge = snd bobSmith
nomes = ["Bob","Carol"]
ages = [27,32]
pessoas = zip nomes ages


{-
main do
    putStrLn "Whats your name"
    name <- getLine
    putStrLn ("Hello " ++ name)

:q sair do ghci
ghc --make <nome do arquivo>
./<nome do aquivo>
-}

soma :: Int -> Int -> Int
soma x y = x + y

multiplicar a b = a * b

addVector :: (Int, Int) -> (Int, Int) -> (Int, Int)
addVector (x0,y0) (x1,y1) = (x0 + x1, y0 + y1)

idade :: Int -> String
idade 16 = "voce pode dirigir nos EUA"
idade 21 = "voce pode beber nos EUA"
idade 18 = "voce pode beber, dirigir e votar no Brasil"
idade _ = "nada demais"

{-
factorial :: Int -> Int
factorial 0 = 1
factorial n = n*factorial(n-1)
-}

isOdd :: Int -> Bool
isOdd n
    | n `mod` 2 == 0 = False
    |otherwise = True
    
maiorQue10 :: Int -> Bool
maiorQue10 x
 | x > 10 = True
 | otherwise = False

factorial :: Int -> Int
factorial n
 | n == 0 = 1
 | otherwise = n*factorial(n-1)

maiorQue100 :: Int -> Int -> Bool
maiorQue100 a b
 | soma > 100 = True
 | otherwise = False
 where soma = a + b

times4 :: Int -> Int
times4 x = x * 4

biggerThan5 :: Int -> Bool
biggerThan5 n
 | n > 5 = True
 | otherwise = False

listBiggerThan5 = map biggerThan5[1,2,3,4,5,6,7,8,9,10]

areStringsEq :: [Char] -> [Char] -> Bool
areStringsEq [] [] = True
areStringsEq (x:xs) (y:ys) = x == y && areStringsEq xs ys
areStringsEq _ _ = False

doMult :: (Int -> Int) -> Int
doMult func = func 3

num3Times4 = doMult times4

printHello = "Hello"

doubleEvenNumber x =
    if (x `mod` 2 /= 0)
        then x
        else x*2

getClass n = case n of
    5 -> "numero 5"
    6 -> "numero 6"
    _ -> "meh"

-- module SampFunctions (getClass, doubleEvenNumbers) where

-- import SampFunctions

data Cliente = Cliente String Int String
    deriving Show


tomSmith :: Cliente
tomSmith = Cliente "Tom" 23 "Arruda"

getAddress :: Cliente -> String
getAddress (Cliente _ _ a) = a

data RPS = Rock | Paper | Scissors

