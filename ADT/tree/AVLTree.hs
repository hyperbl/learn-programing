{- AVL.hs -- 二叉平衡树ADT-}
data AVLTree a = Empty | 
             AVLNode {
                key :: a,
                height :: Int,
                lchild :: (AVLTree a),
                rchild :: (AVLTree a)
             } deriving (Eq, Ord)

instance (Show a) => Show (AVLTree a) where
    show Empty = "Empty"
    show (AVLNode x _ l r) = "AVLNode " ++ show x ++ " (" ++ show l ++ ") (" ++ show r ++ ")"

singleton :: a -> AVLTree a
singleton x = AVLNode x 1 Empty Empty

getHeight :: AVLTree a -> Int
getHeight Empty = 0
getHeight (AVLNode _ h _ _) = h

updateHeight :: AVLTree a -> AVLTree a
updateHeight Empty = Empty
updateHeight (AVLNode x _ l r) = (AVLNode x (max (getHeight l) (getHeight r) + 1) l r)

-- case: RR
singleRotateWithRight :: AVLTree a -> AVLTree a
singleRotateWithRight Empty = Empty
singleRotateWithRight t@(AVLNode _ _ _ Empty) = t
singleRotateWithRight (AVLNode x h l (AVLNode xr hr lr rr)) = updateHeight (AVLNode xr hr new_l rr)
                                      where new_l = updateHeight (AVLNode x h l lr)

-- case: LL
singleRotateWithLeft :: AVLTree a -> AVLTree a
singleRotateWithLeft Empty = Empty
singleRotateWithLeft t@(AVLNode _ _ Empty _) = t
singleRotateWithLeft (AVLNode x h (AVLNode xl hl ll rl) r) = updateHeight (AVLNode xl hl ll new_r)
                                       where new_r = updateHeight (AVLNode x h rl r)

-- case: RL
doubleRotateWithRight :: AVLTree a -> AVLTree a
doubleRotateWithRight Empty = Empty
doubleRotateWithRight (AVLNode x h l r) = singleRotateWithRight new_AVL
                       where new_AVL = updateHeight (AVLNode x h l new_r) 
                              where new_r = (singleRotateWithLeft r)

-- case: LR
doubleRotateWithLeft :: AVLTree a -> AVLTree a
doubleRotateWithLeft Empty = Empty
doubleRotateWithLeft (AVLNode x h l r) = singleRotateWithLeft new_AVL
                      where new_AVL = updateHeight (AVLNode x h new_l r)
                                where new_l = (singleRotateWithRight l)

insert :: (Ord a) => AVLTree a -> a -> AVLTree a
insert Empty y = singleton y
insert t@(AVLNode x h l r) y
            | x > y  = balance $ updateHeight (AVLNode x h new_l r)
            | x < y  = balance $ updateHeight (AVLNode x h l new_r)
            | otherwise  = t
            where
                new_l = (insert l y)
                new_r = (insert r y)
                balance t@(AVLNode x h l r)
                    | bf == 2 && y < key l  = singleRotateWithLeft t
                    | bf == 2 && y > key l  = doubleRotateWithLeft t
                    | bf == -2 && y > key r  = singleRotateWithRight t
                    | bf == -2 && y < key r  = doubleRotateWithRight t
                    | otherwise  = updateHeight (AVLNode x h l r)
                  where
                    bf = (getHeight l - getHeight r)