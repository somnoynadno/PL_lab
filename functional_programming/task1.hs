import Data.List
import System.Environment

summator :: [Int] -> Int
summator [] = 0
summator (x:nx) = x + (summator nx)

toInt :: String -> Int
toInt x = read x::Int

main = do
    args <- getArgs
    print (summator (map toInt args))
