import Data.List
import System.IO

soma 1 = 1
soma n = n + soma(n-1)

-- ctrl + l limpa a tela

guarda x
 | x == 0 = "zero"
 | x == 1 = "um"
 | otherwise = "bleh"

and0 ::  Bool -> Bool -> Bool
and0 a b = (a && b)

and1 :: Bool -> Bool -> Bool
and1 False _ = False
and1 _ False = False
and1 True True = True

and2 :: Bool -> Bool -> Bool
and2 True True = True
and2 _ _ = False

-- #tuplas

tuplinha = ("jao",70)
--no ghci fast e snd

nomes :: (String, String, String)
nomes = ("jao","jao2","haskell")

selec_prim (x, _, _) = x
selec_sec (_, x, _) = x
selec_ter (_, _, x) = x

type Pessoa = (Nome, Idade, Linguagem)
type Nome = String
type Idade = Int
type Linguagem = String

pessoa :: Pessoa
pessoa = ("jao", 20, "Haskell")

pessoa2 :: Pessoa
pessoa2 = ("predo", 33, "Java")

my_fst :: Pessoa -> Nome
my_fst (n, i, l) = n

-- #listas

listinha = [1,3..30]
-- head, tail
listinhah = "12345'6'78910"

-- no ghci -> "bleh" : ["meh"]
-- 1:2:3:[]

saoIguais :: [Int] -> [Int] -> Bool
saoIguais l1 l2
 | the_size l1 /= the_size l2 = False
saoIguais [] [] = True
saoIguais (a:as) (b:bs)
 | (a /= b) = False
 | otherwise = saoIguais as bs

the_size :: [Int] -> Int
the_size [] = 0
the_size (x:xs) = 1 + the_size xs

saoIguais2 :: [Int] -> [Int] -> Bool
saoIguais2 [] [] = True
saoIguais2 _ [] = False
saoIguais2 [] _ = False
saoIguais2 (x:xs) (y:ys)
 | x == y = saoIguais2 xs ys
 | otherwise = False

inverso :: [t] -> [t]
inverso [] = []
inverso (x:xs) = inverso xs ++ [x]

--[1,2,3] ++ [4]

pertence :: [Int] -> Int -> Bool
pertence [] _ = False
pertence (x:xs) a
 | x == a = True
 | otherwise = pertence xs a

maior :: [Int] -> Int
maior [x] = x
maior (x:xs)
 | x > maior xs = x
 | otherwise = maior xs

ehPar :: Int -> Bool
ehPar a 
 | mod a 2 == 0 = True
 | otherwise = False

todosPares :: [Int] -> Bool
todosPares [] = True
todosPares (x:xs)
 | ehPar x = todosPares xs
 | otherwise = False

-- zip [1..10] [2,4..20]

-- ###############################################
-- ###############################################
-- ###############################################
-- ###############################################
--exercicio massa -> ordenaLista

listinha2 :: [Int]
listinha2 = [300,25,11,55,17,2,3,4,5,6,1,0]

getMenor :: [Int] -> Int
getMenor [x] = x
getMenor (x:xs)
 | x < getMenor xs = x
 | otherwise = getMenor xs

removeMenor :: [Int] -> [Int]
removeMenor [] = []
removeMenor (x:xs)
 | x == getMenor (x:xs) = xs
 | otherwise = x : removeMenor xs

ordenaAux :: [Int] -> [Int] -> [Int]
ordenaAux [] lista = lista
ordenaAux lista listaOrdenada = ordenaAux (removeMenor lista) (listaOrdenada ++ [getMenor lista])

ordenaLista :: [Int] -> [Int]
ordenaLista [] = []
ordenaLista lista = ordenaAux lista [] 

-- ###############################################
-- ###############################################
-- ###############################################
-- ###############################################

getHead :: [Int] -> Int
getHead (x:xs) = x

removeHead :: [Int] -> [Int]
removeHead (x:xs) = xs

inverterAux :: [Int] -> [Int] -> [Int]
inverterAux [] listaInv = listaInv
inverterAux lista listaInv = inverterAux (removeHead lista) (getHead lista : listaInv)

inverterLista :: [Int] -> [Int]
inverterLista [] = []
inverterLista lista = inverterAux lista []

inverterLista2 :: [Int] -> [Int]
inverterLista2 [] = []
inverterLista2 (x:xs) = inverterLista2 xs ++ [x]

-- #operadores e funcoes

-- show "hasjdkhjka"
-- putStr "hello world"
-- read "10" +  10

-- not True
-- not False

--import Data.Char
--ord 'g' , ord 'a', ord '8' --> valor para ASCII
-- chr --> ASCII para o valor
--isLower 'a' --> ver se é upper ou lowerCase
--isDigit '1'
--digitToInt '2' , intToDigit 2
-- log 10 , sqrt 25 , floor 3.8 , ceiling 3.8
--round 4.6

myLength :: [t] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

-- #if, then, case

ifPar :: Int -> Bool
ifPar num = if (mod num 2 == 0) then True else False

caseNum :: Int -> String
caseNum n = case n of
    0 -> "zero"
    1 -> "hum"
    _ -> "whatever"

-- #where

quadrado :: Int -> Int
quadrado x = x*x

somaQuadrados :: Int -> Int -> Int
somaQuadrados a b = quadA + quadB
    where
        quadA = quadrado a
        quadB = quadrado b

-- #funcoes lambdas
-- (\x -> (x*x))10 

func_lambda = \x -> (x*x)

-- #funcoes prontas


