import System.Environment

toInt :: String -> Integer
toInt x = read x::Integer


main = do
    args <- getArgs
    print args
    let arg = map toInt args
    print arg
