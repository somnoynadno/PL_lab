oddSelector :: Int -> Int
oddSelector 0 = 0
oddSelector x | odd (x `mod` 10) = (oddSelector (x `div` 10))*10 + (x `mod` 10)
              | otherwise = (oddSelector (x `div` 10))

main = do
  n <- getLine
  let x = read n::Int
  print(oddSelector x)