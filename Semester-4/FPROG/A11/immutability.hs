-- Define a data type with immutability
data Add = Add { aMember :: Int } deriving (Show)

-- Pure addition
add :: Int -> Int -> Int
add first second = first + second

-- Demonstrating immutability (ugly behavior is avoided in Haskell)
-- Instead of modifying values, return new values explicitly
uglyAdd :: Add -> Int -> Int -> (Add, Int)
uglyAdd (Add _) first second = 
    let newFirst = first + second
        newAdd = Add 40
    in (newAdd, newFirst)

main :: IO ()
main = do
    -- Create an instance of Add
    let value = Add 42
    let first = 10
    let second = 20
    
    -- Demonstrate the `add` function
    putStrLn "==== add ==="
    print (add first second)
    print (aMember value)
    print first
    putStrLn "------------"
    
    -- Demonstrate the `uglyAdd` equivalent
    putStrLn "==== uglyAdd ==="
    let (newValue, newFirst) = uglyAdd value first second
    print newFirst
    print (aMember newValue)
    print newFirst
    putStrLn "------------"
