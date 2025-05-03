import Data.List (sortBy)
import Data.Ord (comparing)

-- Define the Name data type
data Name = Name { firstName :: String, lastName :: String } deriving (Show)

-- Comparison function to sort by firstName
compareByFirstName :: Name -> Name -> Ordering
compareByFirstName = comparing firstName

main :: IO ()
main = do
    -- Define a list of Name objects
    let names = [Name "John" "Smith", Name "Alex" "Balboa"]
    
    -- Sort the names by firstName
    let sortedNames = sortBy compareByFirstName names
    
    -- Print the sorted names
    mapM_ (\name -> putStrLn $ firstName name ++ " " ++ lastName name ++ ", ") sortedNames
