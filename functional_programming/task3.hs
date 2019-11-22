import Data.List

main = do
  mapM_ print(zip (sort [3, 6, 8, 9, 12]) (reverse (sort [32, 42, 20, 50, 31])))

