myHead :: [a] -> a 
myHead (x:xs) = x

myTail :: [a] -> [a]
myTail (x:xs) = xs

myFst :: (a, b) -> a
myFst (a,b) = a

myInv :: (a, b, c) -> (c, a, b)
myInv (a, b, c) = (c, a, b)

-- os a's são do mesmo tipo, os b's sao do mesmo tipo
-- e os c's sao do mesmo tipo

-- (+) :: Num x => x -> x -> x
{-
essa linha nao ta compilando, mas ta definindo x como sendo
numero, ou seja, Int, Double, Float. Num é uma classe
-}

-- outras clases : Eq, Ord

antes :: Ord a => (a, a) -> Bool
antes (x, y) = x < y
--Ord se refere à ordem no alfabeto ACII

iguais :: Eq a => (a, a) -> Bool
iguais (x, y) = x == y

-- aula do cin

(+*) :: [a] -> [a] -> [a]
[] +* y = y
(x:xs) +* y = x : (xs +* y) 

-- (==) :: t -> t -> Bool
-- (<) :: t -> t -> Bool
-- show :: t -> String








