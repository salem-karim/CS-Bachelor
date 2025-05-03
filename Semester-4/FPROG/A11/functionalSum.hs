import Data.List (foldl')

-- Define a data structure for sums
data Sums = Sums { evenSum :: Int, oddSum :: Int, totalSum :: Int } deriving (Show)

-- Check if a number is even
isEven :: Int -> Bool
isEven n = n `mod` 2 == 0

-- Check if a number is odd
isOdd :: Int -> Bool
isOdd n = n `mod` 2 /= 0

-- Calculate the sum of a list
sumList :: [Int] -> Int
sumList = foldl' (+) 0

-- Filter a list based on a predicate
filterList :: (a -> Bool) -> [a] -> [a]
filterList = filter

-- Calculate the sums
calculateSums :: [Int] -> Sums
calculateSums numbers = 
    Sums 
        { evenSum = sumList $ filterList isEven numbers
        , oddSum = sumList $ filterList isOdd numbers
        , totalSum = sumList numbers
        }

main :: IO ()
main = do
    -- Define a list of numbers
    let numbers = [1, 2, 3, 4, 5, 6, 7, 8]
    
    -- Calculate the sums
    let result = calculateSums numbers
    
    -- Print the results
    putStrLn $ "Odd Sum: " ++ show (oddSum result) ++ ", Even Sum: " ++ show (evenSum result) ++ ", Total: " ++ show (totalSum result)
