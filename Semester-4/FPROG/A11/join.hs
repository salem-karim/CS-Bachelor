import Data.List (intercalate)

-- Generate a range of integers from 1 to count
range :: Int -> [Int]
range count = [1 .. count]

-- Concatenate an element with a delimiter
concatenate :: Int -> String
concatenate element = show element ++ ", "

-- Main function
main :: IO ()
main = do
    -- Generate a range of integers
    let myRange = range 10

    -- Create a concatenated string
    let concatenatedString = intercalate "" (map concatenate myRange)
    putStrLn concatenatedString

    -- Print each element followed by ", "
    putStrLn $ intercalate ", " (map show myRange)
