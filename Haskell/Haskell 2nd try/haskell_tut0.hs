soma 1 = 1
soma n = n + soma(n-1)

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




