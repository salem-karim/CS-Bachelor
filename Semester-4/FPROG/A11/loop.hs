-- Define a data structure for sums
data Sums = Sums { evenSum :: Int, oddSum :: Int, totalSum :: Int } deriving (Show)

-- Naive summation with a loop equivalent
sumWithUsualLoop :: [Int] -> Int
sumWithUsualLoop = foldl (+) 0

-- Check if a number is even
isEven :: Int -> Bool
isEven n = n `mod` 2 == 0

-- Check if a number is odd
isOdd :: Int -> Bool
isOdd n = n `mod` 2 /= 0

-- Separate sums for even, odd, and total
sums :: [Int] -> Sums
sums numbers = Sums 
    { evenSum = sum $ filter isEven numbers
    , oddSum = sum $ filter isOdd numbers
    , totalSum = sum numbers
    }

-- Functional loops without explicit iteration
sumsWithFunctionalLoops :: [Int] -> Sums
sumsWithFunctionalLoops = sums -- Haskell inherently uses a functional approach

main :: IO ()
main = do
    let numbers = [1, 2, 3, 4, 5, 6, 7, 8]

    -- Summation with a naive loop equivalent
    putStrLn "==== Naive Sum ===="
    print $ sumWithUsualLoop numbers

    -- Sum of even numbers using a naive loop equivalent
    putStrLn "==== Sum of Even Numbers ===="
    print $ sum $ filter isEven numbers

    -- Summing odd, even, and total values
    putStrLn "==== Sums ===="
    let theTotals = sums numbers
    print $ "Odd Sum: " ++ show (oddSum theTotals)
    print $ "Even Sum: " ++ show (evenSum theTotals)
    print $ "Total Sum: " ++ show (totalSum theTotals)

    -- Functional loops for computing sums
    putStrLn "==== Functional Sums ===="
    let totals = sumsWithFunctionalLoops numbers
    print $ "Odd Sum: " ++ show (oddSum totals)
    print $ "Even Sum: " ++ show (evenSum totals)
    print $ "Total Sum: " ++ show (totalSum totals)
